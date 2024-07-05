#pragma once

#include "MenuApplicationMode.h"
#include "../../App/include/GameState.h"
#include "../../App/include/GameSettings.h"
#include "../../App/include/GameStats.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class EndGameAppMode : public MenuApplicationMode
{
private:
    static const std::uint32_t RENDER_ARRAY_SIZE = 2;

public:
    EndGameAppMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb);

    void render(sf::RenderWindow &window) override;
    void handleEvent(sf::Event &event,sf::RenderWindow &window) override;

    void setStats(GameStats stats);
    void playSound();

private:

    void MoveDown() override;
    void MoveUp() override;

    sf::Text menu_[RENDER_ARRAY_SIZE];

    GameStats stats_;
};