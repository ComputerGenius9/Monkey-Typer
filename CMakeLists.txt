cmake_minimum_required(VERSION 3.24)
project(MonkeyTyper)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)

add_executable(MonkeyTyper
        main.cpp
        Game.cpp
        AppMode/src/MainMenuAppMode.cpp
        AppMode/src/GameAppMode.cpp
        AppMode/src/PauseAppMode.cpp
        AppMode/src/ApplicationMode.cpp
        AppMode/src/SettingAppMode.cpp
        App/src/GameSettings.cpp
        AppMode/src/EndGameAppMode.cpp
        App/src/SoundManager.cpp
        AppMode/src/MenuApplicationMode.cpp
        AppMode/src/HistoryAppMode.cpp
        App/src/GameObserver.cpp
        App/src/GameParam.cpp
        Utils/GenerateWord.cpp
        AppData/src/DataSaver.cpp
        AppData/include/DataSaver.h
)

target_link_libraries(MonkeyTyper sfml-graphics sfml-audio)
