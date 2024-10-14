#include <cstdint>
#include <SDL2/SDL.h>

#include "keyboardsdl.h"

TKeyboardSDL::TKeyboardSDL()
{
    m_logger = TLogger::getInstance();
}

TKeyboardSDL::~TKeyboardSDL()
{

}

void TKeyboardSDL::init()
{

}

void TKeyboardSDL::update(uint8_t* key_map, bool* running)
{
    SDL_Event e;
    if (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym) 
            {
                case SDLK_1: key_map[0x1] = 1; break;
                case SDLK_2: key_map[0x2] = 1; break;
                case SDLK_3: key_map[0x3] = 1; break;
                case SDLK_4: key_map[0xC] = 1; break;
                case SDLK_q: key_map[0x4] = 1; break;
                case SDLK_w: key_map[0x5] = 1; break;
                case SDLK_e: key_map[0x6] = 1; break;
                case SDLK_r: key_map[0xD] = 1; break;
                case SDLK_a: key_map[0x7] = 1; break;
                case SDLK_s: key_map[0x8] = 1; break;
                case SDLK_d: key_map[0x9] = 1; break;
                case SDLK_f: key_map[0xE] = 1; break;
                case SDLK_z: key_map[0xA] = 1; break;
                case SDLK_x: key_map[0x0] = 1; break;
                case SDLK_c: key_map[0xB] = 1; break;
                case SDLK_v: key_map[0xF] = 1; break;
            }
        }
        else if(e.type == SDL_KEYUP)
        {
            switch (e.key.keysym.sym) 
            {
                case SDLK_1: key_map[0x1] = 0; break;
                case SDLK_2: key_map[0x2] = 0; break;
                case SDLK_3: key_map[0x3] = 0; break;
                case SDLK_4: key_map[0xC] = 0; break;
                case SDLK_q: key_map[0x4] = 0; break;
                case SDLK_w: key_map[0x5] = 0; break;
                case SDLK_e: key_map[0x6] = 0; break;
                case SDLK_r: key_map[0xD] = 0; break;
                case SDLK_a: key_map[0x7] = 0; break;
                case SDLK_s: key_map[0x8] = 0; break;
                case SDLK_d: key_map[0x9] = 0; break;
                case SDLK_f: key_map[0xE] = 0; break;
                case SDLK_z: key_map[0xA] = 0; break;
                case SDLK_x: key_map[0x0] = 0; break;
                case SDLK_c: key_map[0xB] = 0; break;
                case SDLK_v: key_map[0xF] = 0; break;
            }
        }
        else if (e.type == SDL_QUIT) 
            *running = false;
            
    }
}

void TKeyboardSDL::deinit()
{
    
}