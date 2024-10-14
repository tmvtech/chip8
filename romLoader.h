#ifndef __ROMLOADER_H__
#define __ROMLOADER_H__

#include <cstdint>
#include <iostream>

#include "logger.h"

class TRomLoader
{
    // Logging
    std::shared_ptr<TLogger> m_logger;
    
public:
    TRomLoader();
    ~TRomLoader();

    void loadRom(std::string& file_path, uint8_t* mem);
};

#endif
