#pragma once


#include "App/include/GameState.h"
#include "App/include/Counter.h"
#include "AppMode/include/ApplicationMode.h"
#include "AppData/include/GameRecord.h"
#include "AppData/include/DataSaver.h"
#include "App/include/GameStats.h"

#include <memory>

#include <SFML/Graphics.hpp>

class Game{

public:
    Game(const std::string &extra_files_path, const std::string &cache_path);
    void prepare();
    void start();

private:
    void render();
    void handleEvent(sf::Event &event);
    GameState getState() const;
    void setState(GameState state);

    void loadModes();

    sf::RenderWindow main_window_;
    GameState state_;
    GameSettings settings_;

    DataSaver data_saver_;
    std::map<GameState,std::shared_ptr<ApplicationMode>> game_modes_;
    std::vector<std::string> on_run_loaded_words_;
    SoundManager sound_manager_;
    std::vector<GameRecord> history_;
    GameStats last_stats_;
};