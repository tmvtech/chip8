#ifndef __SOUND_H__
#define __SOUND_H__

class TSound
{
public:
    virtual void init() = 0;
    virtual void playTune() = 0;
    virtual void pauseTune() = 0;
    virtual void deinit() = 0;
};

#endif