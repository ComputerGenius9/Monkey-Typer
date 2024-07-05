#pragma once

//#include <SFML/Audio.hpp>
#include <iostream>

class SoundManager
{
public:
    SoundManager() = default;
    void playMoveSound();
    void playWinSound();
    void playLoseSound();

    void load(const std::string &extra_files_path);
private:
//    sf::SoundBuffer move_sound_;
//    sf::SoundBuffer game_won_sound_;
//    sf::SoundBuffer game_losed_sound_;
//    sf::Sound sound_;

    //For some reason, sound doesn't work properly, and make program not compilable
    const std::string move_sound_file_name_ = "monkey_typer_move.wav";
    const std::string success_sound_file_name_ = "monkey_typer_success.wav";
    const std::string failure_sound_file_name_ = "monkey_typer_failure.wav";
};