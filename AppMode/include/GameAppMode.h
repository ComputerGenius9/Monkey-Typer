#pragma once

#include "ApplicationMode.h"
#include "../../App/include/GameState.h"
#include "../../App/include/Counter.h"
#include "../../App/include/GameSettings.h"
#include "../../App/include/GameStats.h"
#include "../../App/include/GameInternalState.h"
#include "../../App/include/GameMetadata.h"
#include "../../App/include/GameObserver.h"


class GameAppMode : public ApplicationMode
{
public:
    GameAppMode(GameSettings &settings, SoundManager &sound_manager, change_state_callback change_state_cb, std::vector<std::string> &loaded_words);

    void render(sf::RenderWindow &r_window) override;
    void handleEvent(sf::Event &event,sf::RenderWindow &window) override;
    void tick() override;
    void clearMetaData();
    void setInternalState(GameInternalState state);
    void end();

    GameStats collectStats();

private:
    void renderMenu(sf::RenderWindow &window);
    GameInternalState getInternalState() const;
    void start();

    GameObserver observer_;

    sf::String input_{};
    GameInternalState internal_game_state_;
};

