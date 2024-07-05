#pragma once

#include "GameRecord.h"
#include "../../App/include/GameSettings.h"

#include <string>
#include <vector>

class DataSaver
{
public:
    DataSaver(const std::string &extra_files_path, const std::string &cache_path);

    bool loadSettings(GameSettings &settings);
    void saveSettings(GameSettings &settings);

    bool loadFonts(GameSettings &settings);

    bool loadHistory(std::vector<GameRecord> &history);
    void saveHistory(const std::vector<GameRecord> &history);

    bool loadWordsFromSet(std::vector<std::string> &words_from_extra_files);

    const std::string &getExtraFilesPath() const;
    const std::string &getCachePath() const;
private:
    std::string extra_files_path_;
    std::string cache_path_;

    const std::string words_set_file_name_ = "monkey_typer_words_set.txt";
    const std::string data_file_name_ = "monkey_typer_records.dat";
    const std::string settings_file_name_ = "monkey_typer_settings.dat";
    const std::string default_font_file_name_ = "Regular_font.ttf";
};