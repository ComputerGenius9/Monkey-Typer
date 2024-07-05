#include "../include/GameObserver.h"

#include "../../Utils/SelectRandom.h"
#include "../../Utils/GenerateWord.h"

#include <random>
#include <fstream>

#include <SFML/Graphics/Text.hpp>

GameObserver::GameObserver(sf::String &input, GameSettings &settings, std::vector<std::string> &loaded_words, set_game_status_cb set_status_cb, get_game_status_cb get_status_cb)
    : set_cb_(set_status_cb)
    , get_cb_(get_status_cb)
    , settings_(settings)
    , input_(input)
    , loaded_words_(loaded_words)
{

}

void GameObserver::loadWords(std::int32_t count)
{
    //Shuffle words to make them random for each game
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(loaded_words_.begin(), loaded_words_.end(), gen);

    auto it = loaded_words_.begin();
    while(it != loaded_words_.end()){
        if(metadata_.nonvisible_words.size() >= count){
            break;
        }

        if(checkWord((*it),settings_.getMaxWordLengthParam().getValue(), settings_.getMaxWordLengthParam().getMinValue())){
            metadata_.nonvisible_words.push(*it);
        }
        ++it;
    }

    std::uint32_t left = settings_.getWordsParam().getValue() - metadata_.nonvisible_words.size();

    while(metadata_.nonvisible_words.size() < settings_.getWordsParam().getValue()){
        metadata_.nonvisible_words.push(Utils::generate_word(settings_.getMaxWordLengthParam().getValue(), settings_.getMaxWordLengthParam().getMinValue()));
    }
}

void GameObserver::run()
{
    loadWords(settings_.getWordsParam().getValue());
    reset_clock();
}

void GameObserver::stop()
{
    update_time();
}

void GameObserver::push_words()
{
    for(auto &line : metadata_.visible_words) {
        for(auto &word : line.second) {
            word.setPosition(word.getPosition().x + 25, word.getPosition().y);
        }
    }
}

void GameObserver::update_time()
{
    session_time_ += clock_.getElapsedTime();
    reset_clock();
}

void GameObserver::reset_clock()
{
    clock_.restart();
}

sf::Time GameObserver::elapsed_time()
{
    return session_time_;
}

const Counter& GameObserver::getCounter()
{
    return session_counter_;
}

void GameObserver::clear()
{
    metadata_.nonvisible_words = {};
    metadata_.visible_words.clear();

    session_time_ = sf::Time::Zero;
    session_counter_.correct_words = 0;
    session_counter_.missed_words = 0;
    session_counter_.word_pushed = 0;
}

void GameObserver::handleInput()
{
    for(auto &line : metadata_.visible_words) {
        for(auto word_it = line.second.begin(); word_it != line.second.end();) {
            if(input_.toAnsiString() == word_it->getString().toAnsiString()){
                word_it = line.second.erase(word_it);
                session_counter_.correct_words++;
                input_.clear();
                break;
            }else{
                ++word_it;
            }
        }
    }
}

GameStats GameObserver::collectStats() const
{
    GameStats stats;

    stats.max_words = settings_.getWordsParam().getValue();
    stats.correct_words = session_counter_.correct_words;
    stats.missed_words = session_counter_.missed_words;
    stats.elapsed_time = session_time_;

    return stats;
}

std::map<std::uint32_t,std::deque<sf::Text>> &GameObserver::getWordsOnScreen()
{
    return metadata_.visible_words;
}

GameInternalState GameObserver::getStatus()
{
    return get_cb_();
}

void GameObserver::setStatus(GameInternalState new_status)
{
    set_cb_(new_status);
}

void GameObserver::words_observer()
{
    auto time_offset = 100 - (settings_.getSpeedParam().getValue() * 10);

    if(internal_speed_watcher_clock_.getElapsedTime().asMilliseconds() < time_offset){
        return;
    }else{
        internal_speed_watcher_clock_.restart();
    }

    for (auto &words_on_line: metadata_.visible_words) {
        for (auto it = words_on_line.second.begin(); it != words_on_line.second.end();) {
            (*it).setPosition((*it).getPosition().x + 1, (*it).getPosition().y);
            if ((*it).getPosition().x >= settings_.getScreenWidthParam().getValue()) {
                session_counter_.missed_words++;
                it = words_on_line.second.erase(it);
            } else {
                ++it;
            }
        }
    }

    if (session_counter_.missed_words >= settings_.getDeadlineParam().getValue() ||
        settings_.getWordsParam().getValue() == session_counter_.getSum()) {
        setStatus(GameInternalState::END);
    }
}

bool GameObserver::checkWord(const std::string &word, std::uint32_t max_size, std::uint32_t min_size) const
{
    return word.size() <= max_size && word.size() >= min_size && std::all_of(word.begin(), word.end(), [](const char &c) { return std::isalpha(static_cast<unsigned char>(c));});
}

void GameObserver::words_pusher()
{
    if (settings_.getWordsParam().getValue() <= getCounter().word_pushed) {
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr1(1, settings_.getScreenHeightParam().getValue() / 50);
    std::uniform_int_distribution<> distr2(1, 50);

    std::string dummy_str(settings_.getMaxWordLengthParam().getValue(), 'W');
    auto scale = settings_.getScreenWidthParam().getValue() / settings_.getScreenHeightParam().getValue();
    sf::Text dummy(dummy_str, settings_.getFont(), 20 * scale);
    float min_word_x_offset =
            (dummy.findCharacterPos(settings_.getMaxWordLengthParam().getValue() - 1).x - dummy.findCharacterPos(0).x) *
            0.6;

    if (metadata_.nonvisible_words.empty()) {
        return;
    }

    auto candidate = metadata_.nonvisible_words.top();


    std::vector<std::uint32_t> CONSTANT_LINE_Y_CORD{5, 7, 9, 11, 13, 15, 17, 19};
    const float LINE_Y_OFFSET = settings_.getScreenHeightParam().getValue() / 20.f;
    const float LINE_X_OFFSET = 100;

    auto iteration = 0;
    bool pos_found = false;
    while (iteration < CONSTANT_LINE_Y_CORD.size()) {
        ++iteration;
        float line = *Utils::select_random(CONSTANT_LINE_Y_CORD.begin(), CONSTANT_LINE_Y_CORD.end());

        sf::Text new_word(candidate, settings_.getFont(), 40 * scale);
        new_word.setOrigin(0, 0);
        new_word.setPosition(-new_word.getLocalBounds().width,
                             settings_.getScreenHeightParam().getValue() - LINE_Y_OFFSET * line);

        if (!metadata_.visible_words[line].empty()) {
            sf::Text last_word = metadata_.visible_words[line].back();
            last_word.setOrigin(0, last_word.getOrigin().y);

            if (last_word.getGlobalBounds().getPosition().x >
                new_word.getPosition().x + new_word.getLocalBounds().width + LINE_X_OFFSET) {
                pos_found = true;
            }
        } else {
            pos_found = true;
        }

        if(pos_found){
            metadata_.visible_words[line].push_back(new_word);
            session_counter_.word_pushed++;
            metadata_.nonvisible_words.pop();
            break;
        }
    }
}
