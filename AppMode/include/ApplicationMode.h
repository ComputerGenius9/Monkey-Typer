#pragma once

#include "../../App/include/GameState.h"
#include "../../App/include/SoundManager.h"
#include "../../App/include/GameSettings.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <functional>


class ApplicationMode{
public:
    using change_state_callback = std::function<void(GameState)>;

    ApplicationMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_status_callback);

    virtual void render(sf::RenderWindow &r_window) = 0;
    virtual void handleEvent(sf::Event &event, sf::RenderWindow &window) = 0;
    virtual void tick();

    const sf::Font &getFont() const;
    float getHeight() const;
    float getWidth() const;

protected:
    change_state_callback change_status_cb_;
    GameSettings &settings_;
    SoundManager &sound_manager_;
};