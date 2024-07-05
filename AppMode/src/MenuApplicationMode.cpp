#include "../include/MenuApplicationMode.h"

#include <SFML/Window/Event.hpp>


MenuApplicationMode::MenuApplicationMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb, MenuSettings menu_settings)
    : ApplicationMode(settings,sound_manager, change_state_cb)
    , menu_settings_(menu_settings)
{

}

void MenuApplicationMode::MoveUp()
{
    if(current_y_pos_ > menu_settings_.MIN_Y_INDEX){
        current_y_pos_--;
        sound_manager_.playMoveSound();
    }
}

void MenuApplicationMode::MoveDown()
{
    if(current_y_pos_ < menu_settings_.MAX_Y_INDEX){
        current_y_pos_++;
        sound_manager_.playMoveSound();
    }
}

void MenuApplicationMode::MoveLeft()
{
    if(current_x_pos_ > menu_settings_.MIN_Y_INDEX){
        current_x_pos_--;
        sound_manager_.playMoveSound();
    }
}

void MenuApplicationMode::MoveRight()
{
    if(current_x_pos_ < menu_settings_.MAX_X_INDEX){
        current_x_pos_++;
        sound_manager_.playMoveSound();
    }
}

void MenuApplicationMode::updateMenuSettings(MenuSettings settings)
{
    menu_settings_ = settings;
}

std::int32_t MenuApplicationMode::getX() const
{
    return current_x_pos_;
}

std::int32_t MenuApplicationMode::getY() const
{
    return current_y_pos_;
}

void MenuApplicationMode::handleEvent(sf::Event &event, sf::RenderWindow &window) {
    if(event.type == sf::Event::KeyPressed){
        switch(event.key.code){
            case(sf::Keyboard::Up):{
                MoveUp();
                break;
            }

            case(sf::Keyboard::Down):{
                MoveDown();
                break;
            }

            case(sf::Keyboard::Right):{
                MoveRight();
                break;
            }

            case(sf::Keyboard::Left):{
                MoveLeft();
                break;
            }
        }
    }
}
