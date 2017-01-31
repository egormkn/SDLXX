#include <sstream>
#include "SDLXX_mixer.h"
#include "Log.h"
#include "Exception.h"

std::mutex SDLXX::SDL_mixer::mutex;

bool SDLXX::SDL_mixer::initialized = false;

SDLXX::SDL_mixer::SDL_mixer(Uint32 flags) {
    Log::log("Initializing SDL audio mix system...");
    {
        std::lock_guard<std::mutex> lock(mutex);
        if(initialized) {
            throw Exception("SDL_mixer already initialized");
        }
        if((Mix_Init(flags) & flags) != flags) {
            throw Exception("Unable to initialize SDL_mixer", Mix_GetError());
        }
        initialized = true;
    }

    SDL_version compiled;
    const SDL_version *linked = Mix_Linked_Version();
    SDL_MIXER_VERSION(&compiled);
    std::stringstream compiledString, linkedString;
    compiledString << "Compiled against SDL_mixer v" << (int) compiled.major
                   << '.' << (int) compiled.minor << '.' << (int) compiled.patch;
    linkedString << "Linked against SDL_mixer v" << (int) linked->major
                 << '.' << (int) linked->minor << '.' << (int) linked->patch;
    Log::log(compiledString.str());
    Log::log(linkedString.str());
    Log::newline();
}

SDLXX::SDL_mixer::~SDL_mixer() {
    Log::log("Cleaning up SDL audio mix system...");
    std::lock_guard<std::mutex> lock(mutex);
    Mix_Quit();
    initialized = false;
}

/*
    if (-1 == Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, // audio rate
							MIX_DEFAULT_FORMAT,    // format
							2,                     // channels
							4096))                 // buffers
	{
		Log::warning("Mix_OpenAudio: Couldn't start Audio");
		Log::warning(Mix_GetError());
	}

	// Reserving 16 channels (meaning 16 simultaneous SFXs playing)
	Mix_AllocateChannels(16);



    // Destructor:
    Mix_AllocateChannels(0); // Frees all allocated channels
    //Mix_Quit(); segmentation fault! why?
	Mix_CloseAudio();
 */