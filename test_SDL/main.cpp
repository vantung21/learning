#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

using namespace std;
int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *wd = SDL_CreateWindow("window test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 700, 500, SDL_WINDOW_SHOWN);
    if(!wd){
        cout << "loi! Ko tao duoc cua so." << SDL_GetError<< endl;
    }
    SDL_Renderer *render = SDL_CreateRenderer(wd, -1, SDL_RENDERER_ACCELERATED);
    if(!render){
        cout << "loi! Khong the tao renderere. SDL_ERROR " << SDL_GetError << endl;
    }
    SDL_SetRenderDrawColor(render, 255,100, 0, 255);
    SDL_RenderClear(render);
    SDL_RenderPresent(render);

    SDL_Delay(3000);

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(wd);
    wd = NULL;
    render = NULL;
    SDL_Quit();

    return 0;
}
