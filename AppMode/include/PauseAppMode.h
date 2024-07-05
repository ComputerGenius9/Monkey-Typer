#pragma once

#include "MenuApplicationMode.h"

#include <SFML/Graphics/Text.hpp>

class PauseAppMode : public MenuApplicationMode
{
private:
    static const std::uint32_t RENDER_ARRAY_SIZE = 2;
public:
    PauseAppMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb);

    void render(sf::RenderWindow &r_window) override;
    void handleEvent(sf::Event &event,sf::RenderWindow &window) override;

private:
    void MoveDown() override;
    void MoveUp() override;

    sf::Text menu_[RENDER_ARRAY_SIZE];
};