#include "../include/SettingAppMode.h"

#include <random>

#include <SFML/Window/Event.hpp>


SettingAppMode::SettingAppMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb)
    : MenuApplicationMode(settings, sound_manager, change_state_cb, MenuSettings{.MAX_X_INDEX = RENDER_ARRAY_SIZE -1})
{
    auto scale = getWidth() / getHeight();

    menu_[0].setFont(getFont());
    menu_[0].setFillColor(sf::Color::White);
    menu_[0].setString("Words");
    menu_[0].setCharacterSize(30 * scale);
    {
        auto bounds = menu_[0].getLocalBounds();
        menu_[0].setOrigin(bounds.width / 2, 0);
    }
    menu_[0].setPosition(sf::Vector2f(getWidth() / (RENDER_ARRAY_SIZE + 1) * 1, getHeight() /2));

    menu_[1].setFont(getFont());
    menu_[1].setFillColor(sf::Color(255,165,0));
    menu_[1].setString("Speed");
    menu_[1].setCharacterSize(30 * scale);
    {
        auto bounds = menu_[1].getLocalBounds();
        menu_[1].setOrigin(bounds.width / 2, 0);
    }
    menu_[1].setPosition(sf::Vector2f(getWidth() / (RENDER_ARRAY_SIZE + 1) * 2, getHeight() /2));

    menu_[2].setFont(getFont());
    menu_[2].setFillColor(sf::Color(255,165,0));
    menu_[2].setString("Deadline");
    menu_[2].setCharacterSize(30 * scale);
    {
        auto bounds = menu_[2].getLocalBounds();
        menu_[2].setOrigin(bounds.width / 2, 0);
    }
    menu_[2].setPosition(sf::Vector2f(getWidth() / (RENDER_ARRAY_SIZE + 1) * 3, getHeight() /2));

    menu_[3].setFont(getFont());
    menu_[3].setFillColor(sf::Color(255,165,0));
    menu_[3].setString("Max length");
    menu_[3].setCharacterSize(30 * scale);
    {
        auto bounds = menu_[3].getLocalBounds();
        menu_[3].setOrigin(bounds.width / 2, 0);
    }
    menu_[3].setPosition(sf::Vector2f(getWidth() / (RENDER_ARRAY_SIZE + 1) * 4, getHeight() /2));

    menu_[4].setFont(getFont());
    menu_[4].setFillColor(sf::Color(255,165,0));
    menu_[4].setString("Font");
    menu_[4].setCharacterSize(30 * scale);
    {
        auto bounds = menu_[4].getLocalBounds();
        menu_[4].setOrigin(bounds.width / 2, 0);
    }
    menu_[4].setPosition(sf::Vector2f(getWidth() / (RENDER_ARRAY_SIZE + 1) * 5, getHeight() /2));
}


//https://gist.github.com/marukrap/7c361f2c367eaf40537a8715e3fd952a
sf::Color HSVtoRGB(float H, float S, float V)
{
    float C = S * V; //Chroma
    float HPrime = std::fmod(H / 60, 6.f); //H'
    float X = C * (1 - std::fabs(std::fmod(HPrime, 2.f) - 1));
    float M = V - C;

    float R = 0.f;
    float G = 0.f;
    float B = 0.f;

    switch (static_cast<int>(HPrime))
    {
        case 0: R = C; G = X;        break; //[0, 1)
        case 1: R = X; G = C;        break; //[1, 2)
        case 2:        G = C; B = X; break; //[2, 3)
        case 3:        G = X; B = C; break; //[3, 4)
        case 4: R = X;        B = C; break; //[4, 5)
        case 5: R = C;        B = X; break; //[5, 6)
    }

    R += M;
    G += M;
    B += M;

    sf::Color color;
    color.r = static_cast<sf::Uint8>(std::round(R * 255));
    color.g = static_cast<sf::Uint8>(std::round(G * 255));
    color.b = static_cast<sf::Uint8>(std::round(B * 255));

    return color;
}

void SettingAppMode::render(sf::RenderWindow &window)
{
    auto scale = getWidth() / getHeight();

    const auto horizontal_spacing = getWidth() / (RENDER_ARRAY_SIZE + 1);
    const auto vertical_offset = 100.0f;

    for (auto i = 0; i < RENDER_ARRAY_SIZE; i++) {
        //Calculating the position for each menu item
        auto x_position = horizontal_spacing * (i + 1);
        sf::Vector2f menu_position(x_position, getHeight() / 2);
        menu_[i].setPosition(menu_position); //Ensuring menu items are positioned correctly
        window.draw(menu_[i]);

        //Setting the corresponding parameter value text
        sf::Text param;
        switch (i) {
            case 0:
                param.setString(std::to_string(settings_.getWordsParam().getValue()));
                break;
            case 1:
                param.setString(std::to_string(settings_.getSpeedParam().getValue()));
                break;
            case 2:
                param.setString(std::to_string(settings_.getDeadlineParam().getValue()));
                break;
            case 3:
                param.setString(std::to_string(settings_.getMaxWordLengthParam().getValue()));
                break;
            case 4:
                param.setString(settings_.getFontName());
                break;
        }

        param.setFont(getFont());
        param.setFillColor(sf::Color(255,165,0));
        param.setCharacterSize(scale * 30);

        //Setting position for the parameter text
        sf::Vector2f param_position(x_position, getHeight() / 2 + vertical_offset);
        param.setPosition(param_position);

        //Centering the parameter text
        auto bounds = param.getLocalBounds();
        param.setOrigin(bounds.width / 2, 0);

        window.draw(param);
    }
}

void SettingAppMode::handleEvent(sf::Event &event, sf::RenderWindow &window)
{
    switch (event.type) {
        case sf::Event::KeyPressed: {

            MenuApplicationMode::handleEvent(event,window);

            switch (event.key.code) {

                case sf::Keyboard::Escape: {
                    change_status_cb_(GameState::IDLE);
                    break;
                }
            }
        }

        break;
    }
}

void SettingAppMode::MoveUp()
{
    if(getX() == 0){
        settings_.getWordsParam().increase();
    }else if(getX() == 1){
        settings_.getSpeedParam().increase();
    }else if(getX() == 2 && settings_.getDeadlineParam().getValue() < settings_.getWordsParam().getValue()){
        settings_.getDeadlineParam().increase();
    }else if(getX() == 3){
        settings_.getMaxWordLengthParam().increase();
    }else if(getX() == 4){
        settings_.changeFont(true);
    }
}

void SettingAppMode::MoveDown()
{
    if(getX() == 0){
        settings_.getWordsParam().decrease();
        if(settings_.getDeadlineParam().getValue() > settings_.getWordsParam().getValue()){
            settings_.getDeadlineParam().setValue(settings_.getWordsParam().getValue());
        }
    }else if(getX() == 1){
        settings_.getSpeedParam().decrease();
    }else if(getX() == 2){
        settings_.getDeadlineParam().decrease();
    }else if(getX() == 3){
        settings_.getMaxWordLengthParam().decrease();
    }else if(getX() == 4){
        settings_.changeFont(false);
    }
}

void SettingAppMode::MoveLeft()
{
    menu_[getX()].setFillColor(sf::Color(255,165,0));
    MenuApplicationMode::MoveLeft();
    menu_[getX()].setFillColor(sf::Color::White);
}

void SettingAppMode::MoveRight()
{
    menu_[getX()].setFillColor(sf::Color(255,165,0));
    MenuApplicationMode::MoveRight();
    menu_ [getX()].setFillColor(sf::Color::White);
}