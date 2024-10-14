#ifndef __CHIP8_H__
#define __CHIP8_H__

#include <cstdint>
#include <iostream>

#include "display.h"
#include "keyboard.h"
#include "logger.h"
#include "romLoader.h"
#include "sound.h"

#define NUM_KEYS 16
#define TOTAL_RAM 4096
#define STACK_SIZE 16
#define FONTSET_SIZE 80
#define TIMER_MAX 255

#define CHIP8_RAM_START_ADDR 0x000
#define CHIP8_RAM_END_ADDR 0x1FF
#define PROGRAM_START_ADDR 0x200
#define PROGRAM_END_ADDR 0xFFF

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

const static uint8_t FONTSET[] = { 
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

class TCpu;

class TChip8
{
	friend class TCpu;

	// CPU handler
    TCpu* m_cpu;
    
    // screen
    uint8_t m_screen[SCREEN_HEIGHT][SCREEN_WIDTH];

    // keyboard
    uint8_t m_keys[NUM_KEYS];

    // memory
    uint8_t m_ram[TOTAL_RAM];
    uint16_t m_stack[STACK_SIZE];

    // timers
    uint8_t m_delay_timer;
    uint8_t m_sound_timer;

    // Control var
    bool m_emulatorRunning;
    
    // Logging
    std::shared_ptr<TLogger> m_logger;
    
    // ROM Loader
    TRomLoader* m_loader;
    
    // Display
    TDisplay* m_display;
    
    // Keyboard
    TKeyboard* m_keyboard;

    // Sound
    TSound* m_sound;

public:
    TChip8();
    ~TChip8();

    void init(std::string rom_path);
    void run();
    void deinit();

	void setDisplay(TDisplay* display);
	void setKeyboard(TKeyboard* keyboard);
    void setSound(TSound* sound);
};

#endif
