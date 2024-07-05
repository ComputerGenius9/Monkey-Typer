#pragma once

#include "Counter.h"
#include "GameInternalState.h"
#include "GameSettings.h"
#include "GameMetadata.h"
#include "GameStats.h"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>
#include <functional>

class GameObserver
{
public:
    using set_game_status_cb = std::function<void(GameInternalState)>;
    using get_game_status_cb = std::function<GameInternalState()>;

    GameObserver(
        sf::String &input,
        GameSettings &settings,
        std::vector<std::string> &loaded_words,
        set_game_status_cb set_status_cb,
        get_game_status_cb get_status_cb);

    void handleInput();

    void run();
    void stop();
    void clear();
    void push_words();
    void update_time();
    void reset_clock();
    sf::Time elapsed_time();
    const Counter& getCounter();
    GameStats collectStats() const;
    std::map<std::uint32_t,std::deque<sf::Text>> &getWordsOnScreen();

    void words_observer();
    void words_pusher();
private:
    bool checkWord(const std::string &word, std::uint32_t max_size, std::uint32_t min_value) const;
    void loadWords(std::int32_t count);

    GameInternalState getStatus();
    void setStatus(GameInternalState status);

    GameMetadata metadata_;
    Counter session_counter_;

    //Speed management
    sf::Clock internal_speed_watcher_clock_;

    //Time management
    sf::Time session_time_;
    sf::Clock clock_;
    sf::String &input_;

    set_game_status_cb set_cb_;
    get_game_status_cb get_cb_;

    GameSettings &settings_;

    std::vector<std::string> &loaded_words_;
};