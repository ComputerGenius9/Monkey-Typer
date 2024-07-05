#pragma once

#include "MenuApplicationMode.h"
#include "../../App/include/GameSettings.h"
#include "../../App/include/SoundManager.h"

#include <SFML/Graphics/Text.hpp>


class SettingAppMode : public MenuApplicationMode
{
private:
    static const std::uint32_t RENDER_ARRAY_SIZE = 5;
public:
    SettingAppMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb);

    void render(sf::RenderWindow &r_window) override;
    void handleEvent(sf::Event &event,sf::RenderWindow &window) override;

    void MoveDown() override;
    void MoveUp() override;
    void MoveLeft() override;
    void MoveRight() override;
private:
    sf::Text menu_[RENDER_ARRAY_SIZE];
};