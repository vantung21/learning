#include "include.h"
#include"color.h"



SDL_Color curent_color;
void SetColor(SDL_Renderer* renderer, SDL_Color c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    curent_color =c;
}

void click(int mx, int my, int farm[][100]){
    mx = (mx - goc_x)/size_block;
    my =( my - goc_y)/size_block;
    if(mx < 0 || mx >= farm_cols || my < 0 || my >= farm_rows) return;
    if(farm[my][mx] == 0) farm[my][mx] = 1;
    else if(farm[my][mx] == 1) farm[my][mx] = 0;
    else if(farm[my][mx] == -1) farm[my][mx] = 0;
}

int main(int argc, char* argv[]){
    //khoi tao
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    SDL_Window *window = SDL_CreateWindow("farm bobo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1500, 900, SDL_WINDOW_SHOWN);
    if(!window){
        cout << "loi! Ko tao duoc cua so." << SDL_GetError<< endl;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        cout << "loi! Khong the tao renderere. SDL_ERROR " << SDL_GetError << endl;
    }

    
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color red = {255, 0 , 0, 255};
    SDL_Color green = {0, 255, 0, 255};
    SDL_Color blue = {0, 0, 255, 255};
    SDL_Color orange = {200, 100, 0, 255};

    //tai font chu
    TTF_Font* font = TTF_OpenFont("font.ttf", 32);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "bo", blue);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    textSurface = TTF_RenderText_Solid(font, "name", white);
    SDL_Texture* nameTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    
    //tai anh
    SDL_Texture* texture = IMG_LoadTexture(renderer, "cow.png");

    //tai sound
    Mix_Chunk* sound = Mix_LoadWAV("gun.wav");

    //farm
    int farm[100][100];
    for(int i = 0; i<100; i++){
        for(int j = 0; j<100; j++){
            if(i < farm_rows && j < farm_cols){
                farm[i][j] = 0;
            }
            else farm[i][j] = -1;
        }
    }

    // vong lap chinh
    SDL_Event e;
    SDL_Rect rect{20, 20, 40, 60};
    SDL_Rect name{10, 10, 200, 40};
    bool running = true;

    while(running){
           
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) running = false;
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP: rect.y -=10; SetColor(renderer, white); break;
                    case SDLK_DOWN: rect.y +=10;SetColor(renderer, red); break;
                    case SDLK_RIGHT: rect.x +=10;SetColor(renderer, green); break;
                    case SDLK_LEFT: rect.x -=10;SetColor(renderer, blue); break;
                    case SDLK_c: SetColor(renderer, orange); break;
                    case SDLK_1 : 
                        size_block*=1.2;
                        if(size_block > max_size) size_block = max_size;
                        break;
                    case SDLK_2 : 
                        size_block/=1.2;
                        if(size_block < min_size) size_block = min_size;
                        break;
                    case SDLK_w : goc_y += 30; break;
                    case SDLK_s : goc_y -= 30; break;
                    case SDLK_a : goc_x += 30; break;
                    case SDLK_d : goc_x -= 30; break;
                    case SDLK_SPACE: 
                        Mix_PlayChannel(-1, sound , 0);
                        break;
                }
            }
            else if(e.type == SDL_KEYUP){
                cout << "key up\n";
            }
            else if(e.type == SDL_MOUSEMOTION){
                SDL_GetMouseState(&rect.x , &rect.y);
                rect.x -= 20;
                rect.y -=30;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                if(e.button.button == SDL_BUTTON_LEFT){
                    int mx = e.button.x;
                    int my = e.button.y;
                    click(mx, my, farm);
                    //mo rong
                    if(my >= goc_y + farm_rows*size_block && my < goc_y + (farm_rows+1)*size_block){
                        farm_rows++;
                        click(mx, my, farm);
                    } 
                    Mix_PlayChannel(-1, sound , 0);
                }
                else if(e.button.button == SDL_BUTTON_RIGHT){
                    farm_rows--;
                    for(int i = 0; i< farm_cols; i++){
                        farm[farm_rows][i] = -1;
                    }                  
                }
            }
            else if(e.type == SDL_MOUSEWHEEL){
                int kc_x = e.wheel.mouseX - goc_x;
                int kc_y = e.wheel.mouseY - goc_y;
                if(e.wheel.y > 0 && size_block > min_size){
                    goc_x = e.wheel.mouseX - kc_x/1.2;
                    goc_y = e.wheel.mouseY - kc_y/1.2;
                    size_block/=1.2;
                    if(size_block < min_size) size_block = min_size;
                }
                if(e.wheel.y < 0 && size_block < max_size){
                    goc_x = e.wheel.mouseX - kc_x*1.2;
                    goc_y = e.wheel.mouseY - kc_y*1.2;
                    size_block*=1.2;
                    if(size_block > max_size) size_block = max_size;
                }
            }
        }
        SetColor(renderer, curent_color);
        SDL_RenderClear(renderer);
        
        
        for(int i = 0; i< farm_rows; i++){
            for(int j = 0; j < farm_cols; j++){
                SDL_Rect slot;
                slot.x = goc_x +size_block*j;
                slot.y = goc_y + size_block*i;
                slot.w = slot.h = size_block;
                if(farm[i][j] == 0){
                    SDL_SetRenderDrawColor(renderer, 225, 200 , 0, 225);
                    SDL_RenderFillRect(renderer, &slot);
                    SDL_SetRenderDrawColor(renderer, 55, 55 , 55, 225);
                    SDL_RenderDrawRect(renderer, &slot);
                    //SDL_RenderCopy(renderer, textTexture, nullptr, &slot);
                }
                else if(farm[i][j] == 1){
                    SDL_SetRenderDrawColor(renderer, 255, 0 , 0, 225);
                    SDL_RenderFillRect(renderer, &slot);
                    SDL_SetRenderDrawColor(renderer, 55, 55 , 55, 225);
                    SDL_RenderDrawRect(renderer, &slot);
                    SDL_RenderCopy(renderer, textTexture, NULL, &slot);
                }
                else if(farm[i][j] == -1) continue;
            }
        }
        // SDL_SetRenderDrawColor(renderer, 225, 0 , 0, 225);
        // SDL_RenderFillRect(renderer, &rect);

        //khung tên
        SDL_SetRenderDrawColor(renderer, 255, 0 , 200, 225);
        SDL_RenderFillRect(renderer, &name);
        SDL_SetRenderDrawColor(renderer, 25, 20 , 200, 225);
        SDL_RenderDrawRect(renderer, &name);
        SDL_RenderCopy(renderer, nameTexture, NULL, &name);

        SDL_RenderCopy(renderer, texture, NULL, &rect);
        

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    

    SDL_DestroyTexture(texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;
    SDL_Quit();

    return 0;

