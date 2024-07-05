#pragma once

#include "ApplicationMode.h"
#include "../../App/include/GameState.h"
#include "../../App/include/GameSettings.h"
#include "../../App/include/GameStats.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

struct MenuSettings{
    std::int32_t MIN_X_INDEX = 0;
    std::int32_t MIN_Y_INDEX = 0;
    std::int32_t MAX_X_INDEX = 0;
    std::int32_t MAX_Y_INDEX = 0;
};

class MenuApplicationMode : public ApplicationMode
{
protected:
    MenuApplicationMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb, MenuSettings menu_settings);

    virtual void handleEvent(sf::Event &event, sf::RenderWindow &window) override;

    virtual void MoveUp();
    virtual void MoveDown();
    virtual void MoveLeft();
    virtual void MoveRight();

    virtual void updateMenuSettings(MenuSettings settings);

    std::int32_t getX() const;
    std::int32_t getY() const;

protected:
    MenuSettings menu_settings_;
private:
    std::int32_t current_x_pos_ = 0;
    std::int32_t current_y_pos_ = 0;
};