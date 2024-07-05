#include "../include/EndGameAppMode.h"

#include <SFML/Window/Event.hpp>

EndGameAppMode::EndGameAppMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb)
        : MenuApplicationMode(settings, sound_manager, change_state_cb, MenuSettings{.MIN_Y_INDEX = 0, .MAX_Y_INDEX = 1})
{
    auto scale = getWidth() / getHeight();

    menu_[0].setFont(getFont());
    menu_[0].setFillColor(sf::Color::White);
    menu_[0].setString("Save");
    menu_[0].setCharacterSize(30 * scale);
    {
        auto bounds = menu_[0].getLocalBounds();
        menu_[0].setOrigin(bounds.width / 2, bounds.height / 2);
    }
    menu_[0].setPosition(sf::Vector2f(getWidth() / 2, getHeight() / (RENDER_ARRAY_SIZE + 1) * 1));

    menu_[1].setFont(getFont());
    menu_[1].setFillColor(sf::Color(255,165,0));
    menu_[1].setString("Return");
    menu_[1].setCharacterSize(30 * scale);
    {
        auto bounds = menu_[1].getLocalBounds();
        menu_[1].setOrigin(bounds.width / 2, bounds.height / 2);
    }
    menu_[1].setPosition(sf::Vector2f(getWidth() / 2, getHeight() / (RENDER_ARRAY_SIZE + 1) * 2));
}

void EndGameAppMode::MoveUp()
{
    menu_[getY()].setFillColor(sf::Color(255,165,0));
    MenuApplicationMode::MoveUp();
    menu_[getY()].setFillColor(sf::Color::White);
}

void EndGameAppMode::MoveDown()
{
    menu_[getY()].setFillColor(sf::Color(255,165,0));
    MenuApplicationMode::MoveDown();
    menu_[getY()].setFillColor(sf::Color::White);
}

void EndGameAppMode::render(sf::RenderWindow &window)
{
    sf::Text game_result;
    game_result.setPosition(sf::Vector2f(getWidth() / 2, getHeight() / 5));
    game_result.setFont(getFont());
    if(settings_.getDeadlineParam().getValue() <= stats_.missed_words) {
        game_result.setString("Game over :(");
        game_result.setFillColor(sf::Color::White);
    }else{
        game_result.setString("You WON !");
        game_result.setFillColor(sf::Color::Green);
    }
    game_result.setCharacterSize(100);
    auto bounds = game_result.getLocalBounds();
    game_result.setOrigin(bounds.width / 2, bounds.height / 2);
    window.draw(game_result);

    for(const auto &text : menu_){
        window.draw(text);
    }
}

void EndGameAppMode::setStats(GameStats stats)
{
    stats_ = stats;
}

void EndGameAppMode::playSound() {
    if (stats_.missed_words < stats_.max_words){
        sound_manager_.playWinSound();
    }else{
        sound_manager_.playLoseSound();
    }
}

void EndGameAppMode::handleEvent(sf::Event &event, sf::RenderWindow &window)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed: {

            MenuApplicationMode::handleEvent(event,window);

            switch (event.key.code) {


                case sf::Keyboard::Escape: {
                    change_status_cb_(GameState::IDLE);
                    break;
                }

                case sf::Keyboard::Return: {
                    switch (getY()) {
                        case 0: {
                            change_status_cb_(GameState::SAVE_LAST_SESSION);
                            break;
                        }
                        case 1: {
                            change_status_cb_(GameState::CLEAR_DATA);
                            break;
                        }
                    }

                    break;
                }
            }
            break;
        }

        case sf::Event::Closed: {
            window.close();
            break;
        }
    }
}
