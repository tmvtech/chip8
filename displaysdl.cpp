#include <cstdint>
#include <SDL2/SDL.h>

#include "displaysdl.h"

TDisplaySDL::TDisplaySDL()
{
    m_logger = TLogger::getInstance();
}

TDisplaySDL::~TDisplaySDL()
{

}
    
void TDisplaySDL::init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        std::string errorSdl(SDL_GetError());
        m_logger->log("SDL Initialization Error: " + errorSdl, ELogLevel::ERROR);
        exit(1);
    }

    // Create a window
    m_window = SDL_CreateWindow("TMVTech chip8",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                1280, 720, SDL_WINDOW_SHOWN);

    if(!m_window)
    {
        std::string errorWindow(SDL_GetError());
        m_logger->log("Window creation Error: " + errorWindow, ELogLevel::ERROR);
        exit(1);
    }

    m_surface = SDL_GetWindowSurface(m_window);
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
    if (x >= 0 && x < surface->w && y >= 0 && y < surface->h) {
        Uint32 *pixels = (Uint32 *)surface->pixels;
        pixels[(y * surface->w) + x] = color;
    }
}

void TDisplaySDL::draw(uint8_t framebuffer[][64], uint16_t width, uint16_t height)
{
    uint8_t zoomFactor = 10;

    if(SDL_MUSTLOCK(m_surface))
        SDL_LockSurface(m_surface);

    // Clear the screen
    Uint32 color = SDL_MapRGB(m_surface->format, 0x00, 0x00, 0x00); // Black

    // Fill the entire surface with the black color
    SDL_FillRect(m_surface, NULL, color);

    Uint32 white = SDL_MapRGB(m_surface->format, 255, 255, 255);  // White color
    Uint32 green = SDL_MapRGB(m_surface->format, 0, 255, 0);  // Green color

    for(auto i=0; i<height; i++)
    {
        for(auto j=0; j<width; j++)
        {
            if(framebuffer[i][j] == 1)
            {
                for (auto x = 0; x < zoomFactor; x++)
                {
                    for (auto y = 0; y < zoomFactor; y++)
                    {
                        setPixel(m_surface, j*zoomFactor+x, i*zoomFactor+y, green);
                    }
                }
            }
        }   
    }
        

    if(SDL_MUSTLOCK(m_surface))
        SDL_UnlockSurface(m_surface);
}

void TDisplaySDL::update()
{
    // Update the window with the surface
    SDL_UpdateWindowSurface(m_window);

    // Check events
    SDL_Event e;
    if (SDL_PollEvent(&e) != 0) 
    {
        // User requests quit
        if (e.type == SDL_QUIT) {
            m_logger->log("CLOSING: ", ELogLevel::ERROR);
        }
    }
}

void TDisplaySDL::deinit()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
