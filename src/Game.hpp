#ifndef GAME_hpp
#define GAME_hpp

#include <SDL2/SDL.h>
#include "Render.hpp"
#include <iostream>

class Game{
    public:
        Game();
        ~Game();
        
        template<const char* title, int X_POS, int Y_POS, int WIDTH, int HEIGHT, bool FULLSCR> void init(){
            int flags{0};
            if(FULLSCR)
                flags = SDL_WINDOW_FULLSCREEN;
            if(SDL_Init(SDL_INIT_EVERYTHING) ==0){
                window = SDL_CreateWindow(title, X_POS, Y_POS, WIDTH, HEIGHT, flags);
            }
            if(!window){
                std::cout<<"window not created successfully\n";
                return;
            }

            if(!renderer.init(window)){
                std::cout<<"renderer not created successfully\n";
                return;
            }
            renderer.setScale(2.0, 2.0);
            renderer.setDrawColor(0, 0, 0, 255);
            renderer.clear();
            renderer.setDrawColor(255, 255, 255, 255);
            isRunning = true;
        };
        
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running(){return isRunning;};

    private:
        //std::vector<std::vector<SDL_Point>> points;
        //std::vector<SDL_Point> current_points;
        bool draw{false};
        bool isRunning{false};
        SDL_Window* window;
        Renderer renderer;
};

#endif