#include "Game.hpp"

Game::Game(){

}

Game::~Game(){
    clean();
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button){
                case SDL_BUTTON_LEFT:
                    draw = !draw;
                    //current_points.push_back({x,y});
                    
                    break;
            }
            break;
        case SDL_MOUSEMOTION:
            if(draw){
                int x {event.motion.x/2};           //for some fucking reason they need to be divided by 5 to be accurate
                int y {event.motion.y/2};
                renderer.drawPoint(x,y);
                renderer.present();
            }
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_r:
                    //points.push_back(std::move(current_points));
                    break;
                case SDLK_c:
                    renderer.setDrawColor(0, 0, 0, 255);
                    renderer.clear();
                    renderer.setDrawColor(255, 255, 255, 255);
                    renderer.present();
                    break;
                
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void Game::update(){

}

void Game::render(){
    // renderer.setDrawColor(0, 0, 0, 255);
    // renderer.clear();
    renderer.setDrawColor(255, 255, 255, 255);
    // for(auto& group: points)
    //     renderer.drawLines(group);
    //stuff to render
    renderer.present();
    
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout<<"\ncleaned\n";
}