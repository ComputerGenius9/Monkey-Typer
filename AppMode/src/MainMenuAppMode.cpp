#include "../include/MainMenuAppMode.h"

#include <SFML/Window/Event.hpp>

MainMenuAppMode::MainMenuAppMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb)
    : MenuApplicationMode(settings, sound_manager, change_state_cb,MenuSettings{.MIN_Y_INDEX = 0, .MAX_Y_INDEX = 3})
{
    auto scale= getWidth() / getHeight();

    menu_[0].setFont(getFont());
    menu_[0].setFillColor(sf::Color::White);
    menu_[0].setString("Play");
    menu_[0].setCharacterSize(30 * scale);
    {
        auto bounds = menu_[0].getLocalBounds();
        menu_[0].setOrigin(bounds.width / 2, bounds.height / 2);
    }
    menu_[0].setPosition(sf::Vector2f(getWidth() / 2, getHeight() / (RENDER_ARRAY_SIZE + 1) * 1));

    menu_[1].setFont(getFont());
    menu_[1].setFillColor(sf::Color(255,165,0));
    menu_[1].setString("History");
    menu_[1].setCharacterSize(30 * scale);
    {
        auto bounds = menu_[1].getLocalBounds();
        menu_[1].setOrigin(bounds.width / 2, bounds.height /2 );
    }
    menu_[1].setPosition(sf::Vector2f(getWidth() / 2, getHeight() / (RENDER_ARRAY_SIZE + 1) * 2));

    menu_[2].setFont(getFont());
    menu_[2].setFillColor(sf::Color(255,165,0));
    menu_[2].setString("Options");
    menu_[2].setCharacterSize(30 * scale);
    {
        auto bounds = menu_[2].getGlobalBounds();
        menu_[2].setOrigin(bounds.width / 2, bounds.height /2 );
    }
    menu_[2].setPosition(sf::Vector2f(getWidth() / 2, getHeight() / (RENDER_ARRAY_SIZE + 1) * 3));

    menu_[3].setFont(getFont());
    menu_[3].setFillColor(sf::Color(255,165,0));
    menu_[3].setString("Exit");
    menu_[3].setCharacterSize(30 * scale);
    {
        auto bounds = menu_[3].getLocalBounds();
        menu_[3].setOrigin(bounds.width / 2, bounds.height / 2);
    }
    menu_[3].setPosition(sf::Vector2f(getWidth() / 2, getHeight() / (RENDER_ARRAY_SIZE + 1) * 4));

}

void MainMenuAppMode::MoveUp()
{
    menu_[getY()].setFillColor(sf::Color(255,165,0));
    MenuApplicationMode::MoveUp();
    menu_[getY()].setFillColor(sf::Color::White);
}

void MainMenuAppMode::MoveDown()
{
    menu_[getY()].setFillColor(sf::Color(255,165,0));
    MenuApplicationMode::MoveDown();
    menu_[getY()].setFillColor(sf::Color::White);
}

void MainMenuAppMode::render(sf::RenderWindow &window)
{
    for (int i = 0; i < RENDER_ARRAY_SIZE; i++)
    {
        window.draw(menu_[i]);
    }
}

void MainMenuAppMode::handleEvent(sf::Event &event, sf::RenderWindow &window)
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
                            change_status_cb_(GameState::HISTORY);
                            break;
                        }
                        case 2: {
                            change_status_cb_(GameState::SETTINGS);
                            break;
                        }
                        case 3: {
                            change_status_cb_(GameState::CLOSE);
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
