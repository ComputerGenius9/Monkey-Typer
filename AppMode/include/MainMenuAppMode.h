#pragma once

#include "ApplicationMode.h"
#include "../../App/include/GameState.h"
#include "MenuApplicationMode.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class MainMenuAppMode : public MenuApplicationMode
{
private:
    static const std::uint32_t RENDER_ARRAY_SIZE = 4;
public:
    MainMenuAppMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb);

    void render(sf::RenderWindow &window) override;
    void handleEvent(sf::Event &event,sf::RenderWindow &window) override;

private:
    void MoveUp() override;
    void MoveDown() override;

    sf::Text menu_[RENDER_ARRAY_SIZE];
};