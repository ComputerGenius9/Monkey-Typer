#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "../include/DataSaver.h"

DataSaver::DataSaver(const std::string &extra_files_path, const std::string &cache_path)
    : cache_path_(cache_path)
    , extra_files_path_(extra_files_path)
{
    //Creates new directory if not exists, otherwise should return false,
    //but it's also a possible case
    std::filesystem::create_directory(cache_path);
}

bool DataSaver::loadWordsFromSet(std::vector<std::string> &words_from_extra_files)
{
    std::ifstream words_set(extra_files_path_ + '/' +words_set_file_name_);

    if (!words_set) {
        std::cerr << "Error opening file for reading: " << words_set_file_name_ << std::endl;
        return false;
    }

    if(not words_set.fail()){
        std::string str;
        while (std::getline(words_set, str)) {
            if (!str.empty()) {
                words_from_extra_files.push_back(str);
            }
            str.clear();
        }
    }
    return true;
}

bool DataSaver::loadSettings(GameSettings &settings)
{
    std::int32_t deadline;
    std::int32_t words;
    std::int32_t speed;
    std::int32_t max_word_length;

    std::ifstream infile(cache_path_ + "/" + settings_file_name_);
    if (!infile) {
        std::cerr << "Error opening file for reading: " << data_file_name_ << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        iss >> deadline;
        iss >> words;
        iss >> speed;
        iss >> max_word_length;
    }

    settings.getDeadlineParam().setValue(deadline);
    settings.getWordsParam().setValue(words);
    settings.getSpeedParam().setValue(speed);
    settings.getMaxWordLengthParam().setValue(max_word_length);

    return true;
}

void DataSaver::saveSettings(GameSettings &settings)
{
    std::ofstream outfile(cache_path_ + "/" + settings_file_name_);
    if (!outfile) {
        std::cerr << "Error opening file for writing: " << settings_file_name_ << std::endl;
        return;
    }

    outfile << settings.getDeadlineParam().getValue() << " ";
    outfile << settings.getWordsParam().getValue() << " ";
    outfile << settings.getSpeedParam().getValue() << " ";
    outfile << settings.getMaxWordLengthParam().getValue() << " ";

    outfile.close();
}

bool DataSaver::loadHistory(std::vector<GameRecord> &history)
{
    std::ifstream infile(cache_path_ + "/" + data_file_name_);
    if (!infile) {
        std::cerr << "Error opening file for reading: " << data_file_name_ << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        GameRecord record;
        if (iss >> record.assigned_name >> record.max_words >> record.missed_words >> record.correct_words >> record.elapsed_time) {
            history.push_back(record);
        }
    }
    return true;
}

void DataSaver::saveHistory(const std::vector<GameRecord> &history)
{
    std::ofstream outfile(cache_path_ + "/" + data_file_name_);
    if (!outfile) {
        std::cerr << "Error opening file for writing: " << data_file_name_ << std::endl;
        return;
    }

    for (const auto &record : history) {
        outfile << record.assigned_name << " "
                << record.max_words << " "
                << record.missed_words << " "
                << record.correct_words << " "
                << record.elapsed_time << "\n";
    }

    outfile.close();
}

//https://stackoverflow.com/questions/11140483/how-to-get-list-of-files-with-a-specific-extension-in-a-given-folder
bool DataSaver::loadFonts(GameSettings &settings)
{
    sf::Font default_font;
    bool default_font_loaded = false;
    std::vector<std::pair<std::string, sf::Font>> fonts;
    if(default_font.loadFromFile(extra_files_path_ + '/' + default_font_file_name_)){
        fonts.push_back({default_font_file_name_.substr(0,default_font_file_name_.size()-4),default_font});
        default_font_loaded = true;
    }

    std::string ext(".ttf");
    for (auto &p : std::filesystem::directory_iterator(extra_files_path_))
    {
        if (p.path().extension() == ext) {
            std::string filename = p.path().stem().string();
            sf::Font font;
            if(font.loadFromFile(extra_files_path_ + '/' + filename + ".ttf")){
                fonts.push_back({filename, font});
            }
        }
    }

    if(fonts.empty()){
        return false;
    }
    settings.setFonts(fonts);
    return true;
}

const std::string &DataSaver::getExtraFilesPath() const
{
    return extra_files_path_;
}

const std::string &DataSaver::getCachePath() const
{
    return cache_path_;
}