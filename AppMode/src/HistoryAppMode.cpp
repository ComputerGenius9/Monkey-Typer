#include "../include/HistoryAppMode.h"

#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

HistoryAppMode::HistoryAppMode(GameSettings &settins, SoundManager &sound_manager, change_state_callback change_state_cb, std::vector<GameRecord> &history)
    : MenuApplicationMode(settins, sound_manager, change_state_cb,MenuSettings{.MIN_Y_INDEX = 0, .MAX_Y_INDEX = static_cast<int32_t>(history.size()-1)})
    , history_(history)
{
    
}

void HistoryAppMode::render(sf::RenderWindow &window) {
    auto scale = getWidth()/getHeight();

    sf::RectangleShape header_field;
    header_field.setFillColor(sf::Color(255,165,0));
    header_field.setSize({getWidth(), getHeight() / 10});
    header_field.setPosition(0, 0);
    header_field.setOutlineThickness(3);
    header_field.setOutlineColor(sf::Color::Black);
    window.draw(header_field);

    float header_text_y_position =
            header_field.getPosition().y + header_field.getSize().y / 2 - 10;

    sf::Text header_name("Name", getFont(), scale * 30);
    header_name.setFillColor(sf::Color::Black);
    header_name.setPosition(getWidth() * 0.05f, header_text_y_position);
    window.draw(header_name);

    sf::Text header_max("Max Words", getFont(), scale * 30);
    header_max.setFillColor(sf::Color::Black);
    header_max.setPosition(getWidth() * 0.25f, header_text_y_position);
    window.draw(header_max);

    sf::Text header_correct("Correct Words", getFont(), scale * 30);
    header_correct.setFillColor(sf::Color::Black);
    header_correct.setPosition(getWidth() * 0.45f, header_text_y_position);
    window.draw(header_correct);

    sf::Text header_missed("Missed Words", getFont(), scale * 30);
    header_missed.setFillColor(sf::Color::Black);
    header_missed.setPosition(getWidth() * 0.65f, header_text_y_position);
    window.draw(header_missed);

    sf::Text header_time("Elapsed Time", getFont(), scale * 30);
    header_time.setFillColor(sf::Color::Black);
    header_time.setPosition(getWidth() * 0.85f, header_text_y_position);
    window.draw(header_time);

    float offset_y = header_field.getSize().y + 10;

    if (getMMOde() == WRITE) {
        sf::RectangleShape record_field;
        record_field.setFillColor(sf::Color::White);
        record_field.setSize({getWidth(), getHeight() / 10});
        record_field.setPosition(0, offset_y);
        record_field.setOutlineThickness(3);
        record_field.setOutlineColor(sf::Color::Black);
        window.draw(record_field);

        float text_y_position = record_field.getPosition().y + record_field.getSize().y / 2 - 10;

        sf::Text who(name_field_, getFont(), scale * 30);
        who.setFillColor(sf::Color::Black);
        who.setPosition(getWidth() * 0.05f, text_y_position);
        window.draw(who);

        sf::Text max_w(std::to_string(stats_.max_words), getFont(), scale * 30);
        max_w.setFillColor(sf::Color::Black);
        max_w.setPosition(getWidth() * 0.25f, text_y_position);
        window.draw(max_w);

        sf::Text correct_w(std::to_string(stats_.correct_words), getFont(), scale * 30);
        correct_w.setFillColor(sf::Color::Black);
        correct_w.setPosition(getWidth() * 0.45f, text_y_position);
        window.draw(correct_w);

        sf::Text missed_w(std::to_string(stats_.missed_words), getFont(), scale * 30);
        missed_w.setFillColor(sf::Color::Black);
        missed_w.setPosition(getWidth() * 0.65f, text_y_position);
        window.draw(missed_w);

        sf::Text elapsed_time(std::to_string(stats_.elapsed_time.asSeconds()), getFont(), scale * 30);
        elapsed_time.setFillColor(sf::Color::Black);
        elapsed_time.setPosition(getWidth() * 0.85f, text_y_position);
        window.draw(elapsed_time);

        offset_y += record_field.getSize().y + 10;
    }

    auto offset = 0;
    if (getMMOde() == WRITE) {
        offset = 1;
    }

    for (auto i = 0 + offset; i < history_.size() + offset; ++i) {
        if (getMMOde() == WRITE && i == 0) {
            continue;
        }
        sf::RectangleShape record_field;
        if(i == getY()){
            record_field.setFillColor(sf::Color(255, 165, 100));
        }else {
            record_field.setFillColor(sf::Color(255, 165, 0));
        }
        record_field.setSize({getWidth(), getHeight() / 10});
        record_field.setPosition(0, (i - offset) * record_field.getSize().y + offset_y);
        record_field.setOutlineThickness(3);
        record_field.setOutlineColor(sf::Color::Black);
        window.draw(record_field);

        auto text_y_position = record_field.getPosition().y + record_field.getSize().y / 2 - 10;

        sf::Text who(history_[i - offset].assigned_name, getFont(), scale * 30);
        who.setFillColor(sf::Color::Black);
        who.setPosition(getWidth() * 0.05f, text_y_position);
        window.draw(who);


        sf::Text max_w(std::to_string(history_[i - offset].max_words), getFont(), scale * 30);
        max_w.setFillColor(sf::Color::Black);
        max_w.setPosition(getWidth() * 0.25f, text_y_position);
        window.draw(max_w);

        sf::Text correct_w(std::to_string(history_[i - offset].correct_words), getFont(), scale * 30);
        correct_w.setFillColor(sf::Color::Black);
        correct_w.setPosition(getWidth() * 0.45f, text_y_position);
        window.draw(correct_w);

        sf::Text missed_w(std::to_string(history_[i - offset].missed_words), getFont(), scale * 30);
        missed_w.setFillColor(sf::Color::Black);
        missed_w.setPosition(getWidth() * 0.65f, text_y_position);
        window.draw(missed_w);

        sf::Text elapsed_time(std::to_string(history_[i - offset].elapsed_time), getFont(), scale * 30);
        elapsed_time.setFillColor(sf::Color::Black);
        elapsed_time.setPosition(getWidth() * 0.85f, text_y_position);
        window.draw(elapsed_time);
    }
}

void HistoryAppMode::setStats(GameStats stats)
{
    stats_ = stats;
}

void HistoryAppMode::saveRecord()
{
    GameRecord record;
    record.assigned_name = name_field_;
    record.correct_words = stats_.correct_words;
    record.missed_words = stats_.missed_words;
    record.max_words = settings_.getWordsParam().getValue();
    record.elapsed_time = stats_.elapsed_time.asSeconds();

    history_.push_back(record);

    change_status_cb_(GameState::HISTORY_SAVE);
}

void HistoryAppMode::eraseRecord()
{
    history_.erase(history_.begin() + getY());

    change_status_cb_(GameState::HISTORY_SAVE);
}

void HistoryAppMode::handleEvent(sf::Event &event, sf::RenderWindow &window)
{
    switch (event.type) {
        case sf::Event::KeyPressed: {

            MenuApplicationMode::handleEvent(event,window);

            if (event.key.code == sf::Keyboard::Escape) {
                change_status_cb_(GameState::IDLE);
                break;
            }

            if(event.key.code == sf::Keyboard::Enter){
                if(getMMOde() == WRITE){
                    saveRecord();
                    MenuSettings new_settigns{
                        .MIN_X_INDEX = 0,
                        .MIN_Y_INDEX = 0,
                        .MAX_X_INDEX = 0,
                        .MAX_Y_INDEX = static_cast<int32_t>(history_.size()-1)
                    };
                    updateMenuSettings(new_settigns);
                    name_field_ = "";
                    mode_ = SHOW;
                    change_status_cb_(GameState::HISTORY_SAVE);
                    break;
                }
            }

            if(event.key.code == sf::Keyboard::BackSpace){
                if(getMMOde() == WRITE) {
                    name_field_ = name_field_.substring(0, name_field_.getSize() - 1);
                    break;
                }else{
                    if(history_.size() > getY()){
                        eraseRecord();
                        MenuSettings new_settigns{
                                .MIN_X_INDEX = 0,
                                .MIN_Y_INDEX = 0,
                                .MAX_X_INDEX = 0,
                                .MAX_Y_INDEX = static_cast<int32_t>(history_.size()-1)
                        };
                        updateMenuSettings(new_settigns);
                        change_status_cb_(GameState::HISTORY_SAVE);
                        break;
                    }
                }
            }
        }

        case sf::Event::TextEntered: {

            if(getMMOde() == WRITE && std::isalnum(event.text.unicode)){
                name_field_.insert(name_field_.getSize(), event.text.unicode);
            }

            break;
        }

        default:
            break;
    }
}

SaveDataWindowMode HistoryAppMode::getMMOde() const
{
    return mode_;
}

void HistoryAppMode::setMMode(SaveDataWindowMode mode)
{
    mode_ = mode;
}

