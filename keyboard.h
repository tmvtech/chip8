#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <cstdint>

class TKeyboard
{
public:
    virtual void init() = 0;
    virtual void update(uint8_t* key_map, bool* running) = 0;
    virtual void deinit() = 0;
};

#endif
