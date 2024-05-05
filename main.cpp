#define SDL_MAIN_HANDLED
#include "Game.hpp"
#include <memory>

constexpr const char title[10] = "test"; //for some reason the template didn't accept it if declared in main
constexpr int STARTING_X { 100 };
constexpr int STARTING_Y { 100 };
constexpr int RES_X { 720 };
constexpr int RES_Y { 1280 }; 
constexpr bool  FULLSCREEN {false};

int main(int argv, char** args){
    Game game;
    game.init<title, STARTING_X  ,STARTING_Y  ,RES_Y, RES_X ,FULLSCREEN>();         //since they're all known at compile time
    while(game.running()){
        game.handleEvents();
        game.update();
    }
    return 0;
}