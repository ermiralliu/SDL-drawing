#include <SDL2/SDL_render.h>
#include <vector>

struct Renderer{
    SDL_Renderer* renderer = nullptr;
    Renderer(){}

    inline bool init(SDL_Window* window){
        renderer = SDL_CreateRenderer(window, -1, 0);
        return renderer != 0;
    }

    inline int clear(){
        return SDL_RenderClear(renderer);
    }
    inline void present(){
        SDL_RenderPresent(renderer);
    }
    inline int setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
        return SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }
    inline int setScale(float scaleX, float scaleY ){
        return SDL_RenderSetScale(renderer, scaleX, scaleY);
    }
    inline int drawPoint(int x, int y){
        return SDL_RenderDrawPoint(renderer,x,y);
    }
    inline int drawPoints(std::vector<SDL_Point> points){
        return SDL_RenderDrawPoints(renderer, &points[0], points.size());
    }
    inline int drawLine(int x1, int x2, int y1, int y2){
        return SDL_RenderDrawLine(renderer, x1, x2, y1, y2);
    }
    inline int drawLines(std::vector<SDL_Point>& points){
        return SDL_RenderDrawLines(renderer, &points[0], points.size());
    }

    inline int copy(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect){
        return SDL_RenderCopy(renderer, texture, srcRect, dstRect);
    }
    inline int copyEx(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, double angle, int x, int y, SDL_RendererFlip flip ){
        SDL_Point pt{x,y};
        return SDL_RenderCopyEx(renderer, texture, srcRect, dstRect, angle, &pt, flip);
    }
    
    ~Renderer(){    SDL_DestroyRenderer(renderer);  renderer= nullptr;}
};