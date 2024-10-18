#include <iostream>
#include <chrono>
#include <thread>

#include "chip8.h"
#include "cpu.h"
#include "logger.h"

TChip8::TChip8()
{
    m_logger = TLogger::getInstance();
    m_cpu = new TCpu(this);
    m_emulatorRunning = true;
    m_display = nullptr;
    m_keyboard = nullptr;
    m_sound = nullptr;
}

TChip8::~TChip8()
{

}

void TChip8::init(std::string rom_path)
{
	// Clear frame buffer
    for(auto i = 0; i < SCREEN_HEIGHT; i++)
        for(auto j = 0; j < SCREEN_WIDTH; j++)
            m_screen[i][j] = 0;

    // Clear stack
    for(auto i = 0; i < STACK_SIZE; i++)
        m_stack[i] = 0;

    // Clear RAM
    for(auto i = 0; i < TOTAL_RAM; i++)
        m_ram[i] = 0;

    // Load font set into memory
    for(auto i = 0; i < FONTSET_SIZE; i++)
        m_ram[i] = FONTSET[i];

    // Reset timers
    m_delay_timer = 0;
    m_sound_timer = 0;

    // Start keyboard state as all unpressed
    for (auto i = 0; i < NUM_KEYS; i++)
        m_keys[i] = 0;
    
    // Init cpu registers
    m_cpu->init();
    
    // Load ROM to the ram
    m_loader = new TRomLoader();
    m_loader->loadRom(rom_path, m_ram+PROGRAM_START_ADDR);
    delete m_loader;
    
    // Initialize display lib
    m_display->init();

    // Initialize sound lib
    m_sound->init();
    
    // Initialize keyboard lib
    m_keyboard->init();
}

void TChip8::run()
{
	using clock = std::chrono::high_resolution_clock;
    clock::time_point start, end;
    const std::chrono::milliseconds desired_cycle_time(1);

    int display_update_delay_time = 0;

	while(m_emulatorRunning)
    {
    	start = clock::now();
    	
    	m_cpu->fetch();
        m_cpu->decode();
        m_cpu->execute();
        
        if(display_update_delay_time >= 20)
        {
        	display_update_delay_time = 0;
        	m_display->draw(m_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        	m_display->update();
        
        	// Update timers ~60Hz
        	if(m_delay_timer > 0)
            	m_delay_timer--;

        	if(m_sound_timer > 0)
            {
                m_sound_timer--;
                m_sound->playTune();
            }
            else
                m_sound->pauseTune();
            	
        }
        
        m_keyboard->update(m_keys, &m_emulatorRunning);
        
        end = clock::now();
        
        std::chrono::duration<double, std::micro> loop_time = end - start;
        // Calculate the elapsed time in milliseconds
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        // Calculate the remaining time to reach the desired cycle time
        auto sleep_time = desired_cycle_time - elapsed_time;

		m_logger->log("SLEEP: "+std::to_string(sleep_time.count()), ELogLevel::DEBUG);

        // If the loop logic took less than the desired time, wait for the remaining time
        if (sleep_time.count() > 0) {
            std::this_thread::sleep_for(sleep_time);
        }

        // update tick counter
        display_update_delay_time++;
    }
}

void TChip8::deinit()
{
	m_cpu->deinit();
	
    m_display->deinit();
    
    m_keyboard->deinit();

    m_sound->deinit();
}

void TChip8::setDisplay(TDisplay* display)
{
    m_display = display;
}

void TChip8::setKeyboard(TKeyboard* keyboard)
{
    m_keyboard = keyboard;
}

void TChip8::setSound(TSound* sound)
{
    m_sound = sound;
}
