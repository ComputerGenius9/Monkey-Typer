#pragma once

#include "../../AppData/include/GameRecord.h"
#include "../../App/include/GameStats.h"
#include "../../App/include/GameSettings.h"
#include "MenuApplicationMode.h"

#include <SFML/Graphics/Text.hpp>

enum SaveDataWindowMode{
    WRITE,
    SHOW
};

class HistoryAppMode : public MenuApplicationMode
{
public:
    HistoryAppMode(GameSettings &settins, SoundManager &sound_manager, change_state_callback change_state_cb, std::vector<GameRecord> &history);

    void render(sf::RenderWindow &r_window) override;
    void handleEvent(sf::Event &event,sf::RenderWindow &window) override;
    void setStats(GameStats stats);

    SaveDataWindowMode getMMOde() const;
    void setMMode(SaveDataWindowMode mode);

private:
    void saveRecord();
    void eraseRecord();

    std::vector<GameRecord> &history_;
    SaveDataWindowMode mode_ = SHOW;
    sf::String name_field_;
    GameStats stats_;
};