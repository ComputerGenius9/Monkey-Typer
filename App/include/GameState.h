#pragma once


//Enum CLASS instead of enum for avoiding such errors like "setting GameInternalState by GameState value"
enum class GameState{
    IDLE,
    RUN,
    SETTINGS,
    PAUSE,
    SAVE_LAST_SESSION,
    CLEAR_DATA,
    GAME_ENDED_STAGE_1,
    GAME_ENDED_STAGE_2,
    HISTORY,
    HISTORY_SAVE,
    CLOSE
};