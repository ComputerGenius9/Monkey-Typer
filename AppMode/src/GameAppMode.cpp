#include "../include/GameAppMode.h"

#include <iomanip>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

GameAppMode::GameAppMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb, std::vector<std::string> &loaded_words)
    : ApplicationMode(settings,sound_manager, change_state_cb)
    , internal_game_state_(GameInternalState::IDLE_GAME)
    , observer_(input_,settings,loaded_words,[this](GameInternalState state){ setInternalState(state);},[this](){return getInternalState();})
{
}

void GameAppMode::render(sf::RenderWindow &window)
{
    float scale = getWidth() / getHeight();
    if (getInternalState() == GameInternalState::RUN_GAME || getInternalState() == GameInternalState::SLEEP) {
        for (auto &line: observer_.getWordsOnScreen()) {
            for (auto &word: line.second) {
                if (word.getPosition().x < settings_.getScreenWidthParam().getValue() / 2) {
                    word.setFillColor(sf::Color::Green);
                } else if (word.getPosition().x < settings_.getScreenWidthParam().getValue() * 70 / 100) {
                    word.setFillColor(sf::Color::Yellow);
                } else {
                    word.setFillColor(sf::Color::Red);
                }
                window.draw(word);
            }
        }
    }

    if (getInternalState() == GameInternalState::IDLE_GAME) {
        auto text = sf::Text("Click ENTER to start", getFont(), 50 * scale);
        text.setPosition({getWidth() / 2, getHeight() / 2});
        text.setFillColor(sf::Color::White);
        auto bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2, bounds.height / 2);
        window.draw(text);
    }

    if (getInternalState() == GameInternalState::SLEEP) {
        auto text = sf::Text("Click ENTER to resume", getFont(), 50 * scale);
        text.setPosition({getWidth() / 2, getHeight() / 2});
        text.setFillColor(sf::Color::White);
        auto bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2, bounds.height / 2);
        window.draw(text);
    }
    renderMenu(window);
}


void GameAppMode::renderMenu(sf::RenderWindow &window)
{
    float scale = static_cast<float>(settings_.getScreenHeightParam().getValue()) / settings_.getScreenWidthParam().getValue();

    sf::RectangleShape menu_bar;
    menu_bar.setSize({static_cast<float>(settings_.getScreenWidthParam().getValue()), static_cast<float>(settings_.getScreenHeightParam().getValue()) / 7.0f});
    menu_bar.setOrigin(0,0);
    menu_bar.setPosition({0, static_cast<float>(settings_.getScreenHeightParam().getValue()) - static_cast<float>(settings_.getScreenHeightParam().getValue()) / 7.0f});
    menu_bar.setFillColor(sf::Color(255,165,0));
    menu_bar.setOutlineColor(sf::Color::Black);
    menu_bar.setOutlineThickness(2);

    sf::Text input_text(input_, getFont(), (settings_.getScreenHeightParam().getValue() / 20.f) * scale);
    input_text.setOrigin(input_text.getLocalBounds().width / 2, input_text.getLocalBounds().height / 2);
    input_text.setPosition(menu_bar.getLocalBounds().width /8, menu_bar.getPosition().y + menu_bar.getLocalBounds().height / 2);
    input_text.setFillColor(sf::Color(128,128,128));

    float elapsed_time = observer_.elapsed_time().asSeconds();
    std::uint32_t correct_words = observer_.getCounter().correct_words;
    std::uint32_t missed_words = observer_.getCounter().missed_words;
    std::uint32_t total_words = correct_words + missed_words;
    float words_per_minute = (elapsed_time > 0) ? (correct_words / elapsed_time) * 60.0f : 0;
    float accuracy = (total_words > 0) ? (static_cast<float>(correct_words) / total_words) * 100.0f : 0;

    std::ostringstream ss;
    ss << std::fixed << std::setprecision(1);
    ss << "Success: " << correct_words
       << " Failed: " << missed_words
       << " Time: " << elapsed_time
       << " WPM: " << words_per_minute
       << " Accuracy: " << accuracy << "%";

    sf::Text counter_text(ss.str(), getFont(), settings_.getScreenHeightParam().getValue() / 20.f * scale);
    counter_text.setOrigin(counter_text.getLocalBounds().width / 2, counter_text.getLocalBounds().height / 2);
    counter_text.setPosition(menu_bar.getLocalBounds().width /2, menu_bar.getPosition().y + menu_bar.getLocalBounds().height / 2);
    counter_text.setOutlineColor(sf::Color::Black);
    counter_text.setOutlineThickness(2);
    counter_text.setFillColor(sf::Color(128,128,128));

    window.draw(menu_bar);
    window.draw(input_text);
    window.draw(counter_text);
}

void GameAppMode::setInternalState(GameInternalState state){
    internal_game_state_ = state;

    switch (internal_game_state_) {
        case GameInternalState::END:{
            change_status_cb_(GameState::GAME_ENDED_STAGE_1);
            break;
        }
    }
}

GameInternalState GameAppMode::getInternalState() const{
    return internal_game_state_;
}

void GameAppMode::end()
{
    setInternalState(GameInternalState::END);
    observer_.stop();
    clearMetaData();
    setInternalState(GameInternalState::IDLE_GAME);
}

GameStats GameAppMode::collectStats()
{
    return observer_.collectStats();
}

void GameAppMode::start()
{
    setInternalState(GameInternalState::SLEEP);
    observer_.run();
    setInternalState(GameInternalState::RUN_GAME);
}

void GameAppMode::clearMetaData()
{
    observer_.clear();
    input_.clear();
}

void GameAppMode::handleEvent(sf::Event &event,sf::RenderWindow &window)
{
    switch (event.type) {
        case sf::Event::KeyPressed: {
            if (event.key.code == sf::Keyboard::Escape) {
                if(getInternalState() == GameInternalState::RUN_GAME) {
                    setInternalState(GameInternalState::SLEEP);
                }
                change_status_cb_(GameState::PAUSE);
                break;
            }

            if(event.key.code == sf::Keyboard::Enter){
                if(getInternalState() == GameInternalState::IDLE_GAME){
                    start();
                    break;
                }

                if(getInternalState() == GameInternalState::SLEEP){
                    setInternalState(GameInternalState::RUN_GAME);
                    observer_.reset_clock();
                    break;
                }
                break;
            }

            if(event.key.code == sf::Keyboard::Space){
                if(getInternalState() == GameInternalState::RUN_GAME) {
                    observer_.push_words();
                    break;
                }
            }

            if(event.key.code == sf::Keyboard::BackSpace){
                input_ = input_.substring(0, input_.getSize() - 1);
                break;
            }
            break;
        }

        case sf::Event::TextEntered: {

            if(getInternalState() != GameInternalState::RUN_GAME){
                break;
            }
            if (std::isalnum(event.text.unicode) && input_.getSize() < settings_.getMaxWordLengthParam().getValue()){
                input_.insert(input_.getSize(), event.text.unicode);
                observer_.handleInput();
            }

            break;
        }

        default:
            break;
    }
}

void GameAppMode::tick()
{
    if(getInternalState() == GameInternalState::RUN_GAME){
        observer_.update_time();
        observer_.words_pusher();
        observer_.words_observer();
    }
}
