#ifndef __KEYBOARDSDL_H__
#define __KEYBOARDSDL_H__

#include <cstdint>

#include "keyboard.h"
#include "logger.h"

class TKeyboardSDL : public TKeyboard
{
    // Logging
    std::shared_ptr<TLogger> m_logger;

public:
    TKeyboardSDL();
    ~TKeyboardSDL();

    virtual void init() override;
    virtual void update(uint8_t* key_map, bool* running) override;
    virtual void deinit() override;
};

#endif
