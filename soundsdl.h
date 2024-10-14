#ifndef __SOUNDSDL_H__
#define __SOUNDSDL_H__

#include <SDL2/SDL.h>

#include "logger.h"
#include "sound.h"

class TSoundSDL : public TSound
{
    SDL_AudioSpec m_audioSpec;

    // Logging
    std::shared_ptr<TLogger> m_logger;

public:
    TSoundSDL();
    ~TSoundSDL();

    virtual void init() override;
    virtual void playTune() override;
    virtual void pauseTune() override;
    virtual void deinit() override;
};

#endif