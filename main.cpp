#include "Game.h"

#include <iostream>
#include <filesystem>

//The whole project is a combination of ChatGPT with official SFML documentation.
//I only inserted sources that were used outside of these two things.

int main(int argc, char * argv[])
{
    std::string path_to_extra_files;
    std::string path_to_cache;

    if(argc < 2){
        //https://en.sfml-dev.org/forums/index.php?topic=29005.0
        std::cerr << "EXTRA_FILES path not present"<< '\n';

        return 1;
    }else if(argc < 3){
        path_to_extra_files = argv[1];
        path_to_cache = std::filesystem::current_path().string() + "/CACHE";
    }else{
        path_to_extra_files = argv[1];
        path_to_cache = argv[2];
    }

    try {
        Game game(path_to_extra_files, path_to_cache);
        game.prepare();
        game.start();
    }catch(std::exception &e){
        std::cerr << "Exception:" << e.what() << '\n';
    }
}
