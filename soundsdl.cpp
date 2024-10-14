#include <SDL2/SDL.h>

#include "soundsdl.h"


// Constants
const int SAMPLE_RATE = 44100; // Sample rate
const int AMPLITUDE = 28000;    // Amplitude
const double FREQUENCY = 440.0; // Frequency of the sine wave (A4)

// Audio callback function
void audioCallback(void* userdata, Uint8* stream, int len) {
    static double phase = 0.0;
    double increment = (2.0 * M_PI * FREQUENCY) / SAMPLE_RATE;

    for (int i = 0; i < len; i += 2) {
        short sample = static_cast<short>(AMPLITUDE * sin(phase));
        phase += increment;

        if (phase > 2.0 * M_PI) {
            phase -= 2.0 * M_PI;
        }

        // Write the sample to the audio stream
        stream[i] = sample & 0xFF;       // Low byte
        stream[i + 1] = (sample >> 8) & 0xFF; // High byte
    }
}

TSoundSDL::TSoundSDL()
{
    m_logger = TLogger::getInstance();
}

TSoundSDL::~TSoundSDL()
{

}

void TSoundSDL::init()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::string errorSdl(SDL_GetError());
        m_logger->log("SDL Sound Initialization Error: " + errorSdl, ELogLevel::ERROR);
        exit(1);
    }

    m_audioSpec.freq = SAMPLE_RATE;
    m_audioSpec.format = AUDIO_S16SYS; // Signed 16-bit samples
    m_audioSpec.channels = 1;           // Mono audio
    m_audioSpec.samples = 4096;         // Buffer size
    m_audioSpec.callback = audioCallback;
    m_audioSpec.userdata = nullptr;

    if (SDL_OpenAudio(&m_audioSpec, nullptr) < 0)
    {
        std::string errorSdl(SDL_GetError());
        m_logger->log("Failed to open audio device: " + errorSdl, ELogLevel::ERROR);
        exit(1);
    }
}

void TSoundSDL::playTune()
{
    SDL_PauseAudio(0);
}

void TSoundSDL::pauseTune()
{
    SDL_PauseAudio(1);
}

void TSoundSDL::deinit()
{
    SDL_CloseAudio();
    SDL_Quit();
}
