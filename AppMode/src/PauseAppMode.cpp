#include "../include/PauseAppMode.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Window/Event.hpp>

PauseAppMode::PauseAppMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb)
        : MenuApplicationMode(settings, sound_manager, change_state_cb, MenuSettings{.MIN_Y_INDEX = 0, .MAX_Y_INDEX = 1})
{
    auto scale = getWidth()/getHeight();

    menu_[0].setFont(getFont());
    menu_[0].setFillColor(sf::Color::White);
    menu_[0].setString("Resume");
    menu_[0].setCharacterSize(scale * 30);
    {
        auto bounds = menu_[0].getLocalBounds();
        menu_[0].setOrigin(bounds.width / 2, bounds.height / 2);
    }
    menu_[0].setPosition(sf::Vector2f(getWidth() / 2, getHeight() / (RENDER_ARRAY_SIZE + 1) * 1));

    menu_[1].setFont(getFont());
    menu_[1].setFillColor(sf::Color(255,165,0));
    menu_[1].setString("Exit");
    menu_[1].setCharacterSize(scale * 30);
    {
        auto bounds = menu_[1].getLocalBounds();
        menu_[1].setOrigin(bounds.width / 2, bounds.height / 2);
    }
    menu_[1].setPosition(sf::Vector2f(getWidth() / 2, getHeight() / (RENDER_ARRAY_SIZE + 1) * 2));
}

void PauseAppMode::MoveUp()
{
    menu_[getY()].setFillColor(sf::Color(255,165,0));
    MenuApplicationMode::MoveUp();
    menu_[getY()].setFillColor(sf::Color::White);
}

void PauseAppMode::MoveDown()
{
    menu_[getY()].setFillColor(sf::Color(255,165,0));
    MenuApplicationMode::MoveDown();
    menu_[getY()].setFillColor(sf::Color::White);
}
void PauseAppMode::render(sf::RenderWindow &window)
{
    for (int i = 0; i < RENDER_ARRAY_SIZE; i++)
    {
        window.draw(menu_[i]);
    }
}

void PauseAppMode::handleEvent(sf::Event &event, sf::RenderWindow &window)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed: {
            MenuApplicationMode::handleEvent(event,window);
            switch (event.key.code) {
                case sf::Keyboard::Return: {
                    switch (getY()) {
                        case 0: {
                            change_status_cb_(GameState::RUN);
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
