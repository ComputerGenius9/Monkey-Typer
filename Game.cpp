#include "Game.h"
#include "AppMode/include/MainMenuAppMode.h"
#include "AppMode/include/GameAppMode.h"
#include "AppMode/include/PauseAppMode.h"
#include "AppMode/include/SettingAppMode.h"
#include "AppMode/include/EndGameAppMode.h"
#include "AppMode/include/HistoryAppMode.h"

#include <filesystem>
#include <iostream>

//Automatically get current screen resolution (could be replaced by any value inside)
//@Note Window style should also be changed
#define GAME_WINDOW_WIDTH (sf::VideoMode::getDesktopMode().width)
#define GAME_WINDOW_HEIGHT (sf::VideoMode::getDesktopMode().height)

Game::Game(const std::string &extra_files_path, const std::string &cache_path)
        : main_window_(sf::RenderWindow(
        sf::VideoMode({GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT}), "MonkeyTyper",
        sf::Style::Fullscreen , sf::ContextSettings(0, 0, 8)))
        , settings_(GAME_WINDOW_WIDTH,GAME_WINDOW_HEIGHT)
        , data_saver_(extra_files_path,cache_path)
{

}

void Game::loadModes()
{
    ApplicationMode::change_state_callback callback = [this](GameState state){ setState(state);};

    game_modes_[GameState::IDLE] = std::make_shared<MainMenuAppMode>(settings_, sound_manager_, callback);
    game_modes_[GameState::RUN] = std::make_shared<GameAppMode>(settings_, sound_manager_, callback,on_run_loaded_words_);
    game_modes_[GameState::PAUSE] = std::make_shared<PauseAppMode>(settings_, sound_manager_, callback);
    game_modes_[GameState::SETTINGS] = std::make_shared<SettingAppMode>(settings_, sound_manager_, callback);
    game_modes_[GameState::GAME_ENDED_STAGE_2] = std::make_shared<EndGameAppMode>(settings_, sound_manager_, callback);
    game_modes_[GameState::HISTORY] = std::make_shared<HistoryAppMode>(settings_, sound_manager_, callback , history_);
}

void Game::prepare()
{
    if(not data_saver_.loadHistory(history_)){
        std::cerr<<"Error on loading history"<<'\n';
    }

    if(not data_saver_.loadSettings(settings_)){
        std::cerr<<"Error on loading settings"<<'\n';
    }

    if(not data_saver_.loadFonts(settings_)){
        std::cerr<<"[Critical Error] Error on loading font"<<'\n';
        throw std::logic_error("Font not present");
    }

    if(not data_saver_.loadWordsFromSet(on_run_loaded_words_))

    sound_manager_.load(data_saver_.getExtraFilesPath());

    loadModes();
}

void Game::start()
{
    setState(GameState::IDLE);

    while(main_window_.isOpen()){

        if(auto it = game_modes_.find(getState()); it != game_modes_.end()){
            it->second->tick();
        }

        if(getState() == GameState::CLEAR_DATA){
            std::static_pointer_cast<GameAppMode>(game_modes_[GameState::RUN])->end();
            setState(GameState::IDLE);
            continue;
        }

        if(getState() == GameState::GAME_ENDED_STAGE_1){
            last_stats_ = std::static_pointer_cast<GameAppMode>(game_modes_[GameState::RUN])->collectStats();
            std::static_pointer_cast<GameAppMode>(game_modes_[GameState::RUN])->end();
            setState(GameState::GAME_ENDED_STAGE_2);

            std::static_pointer_cast<EndGameAppMode>(game_modes_[GameState::GAME_ENDED_STAGE_2])->setStats(last_stats_);
            std::static_pointer_cast<EndGameAppMode>(game_modes_[GameState::GAME_ENDED_STAGE_2])->playSound();
            continue;
        }

        if(getState() == GameState::SAVE_LAST_SESSION){
            std::static_pointer_cast<HistoryAppMode>(game_modes_[GameState::HISTORY])->setMMode(SaveDataWindowMode::WRITE);
            std::static_pointer_cast<HistoryAppMode>(game_modes_[GameState::HISTORY])->setStats(last_stats_);

            setState(GameState::HISTORY);
        }

        if(getState() == GameState::HISTORY_SAVE){
            data_saver_.saveHistory(history_);
            setState(GameState::HISTORY);
        }

        if(getState() == GameState::CLOSE){
            main_window_.close();
            data_saver_.saveHistory(history_);
            data_saver_.saveSettings(settings_);
            return;
        }

        auto event = sf::Event();

        while (main_window_.pollEvent(event))
        {
            handleEvent(event);
        }
        main_window_.clear(sf::Color(128,128,128));

        render();

        main_window_.display();
    }
}

void Game::render()
{
    auto it = game_modes_.find(state_);
    if(it != game_modes_.end()){
        game_modes_[state_]->render(main_window_);
    }
}

void Game::handleEvent(sf::Event &event)
{
    if(event.type == sf::Event::Closed){
        state_ = GameState::CLOSE;
        return;
    }

    auto it = game_modes_.find(state_);
    if(it != game_modes_.end()){
        game_modes_[state_]->handleEvent(event,main_window_);
    }
}

GameState Game::getState() const
{
    return state_;
}

void Game::setState(GameState state)
{
    state_ = state;
}


