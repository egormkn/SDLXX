#include <sstream>
#include <sdlxx/mixer/SDLXX_mixer.h>
#include <sdlxx/core/Exception.h>
#include <sdlxx/core/Log.h>

std::mutex sdlxx::mixer::SDL_mixer::mutex;

bool sdlxx::mixer::SDL_mixer::initialized = false;

sdlxx::mixer::SDL_mixer::SDL_mixer(Uint32 flags) {
#ifndef SDLXX_RELEASE
    sdlxx::core::Log::log("Initializing SDL audio mix system...");
#endif
    {
        std::lock_guard<std::mutex> lock(mutex);
        if(initialized) {
            throw sdlxx::core::Exception("SDL_mixer already initialized");
        }
        if((Mix_Init(flags) & flags) != flags) {
            throw sdlxx::core::Exception("Unable to initialize SDL_mixer", Mix_GetError());
        }
        initialized = true;
    }
#ifndef SDLXX_RELEASE
    SDL_version compiled;
    const SDL_version *linked = Mix_Linked_Version();
    SDL_MIXER_VERSION(&compiled);
    std::stringstream compiledString, linkedString;
    compiledString << "Compiled against SDL_mixer v" << (int) compiled.major
                   << '.' << (int) compiled.minor << '.' << (int) compiled.patch;
    linkedString << "Linked against SDL_mixer v" << (int) linked->major
                 << '.' << (int) linked->minor << '.' << (int) linked->patch;
    sdlxx::core::Log::log(compiledString.str());
    sdlxx::core::Log::log(linkedString.str());
    sdlxx::core::Log::newline();
#endif
}

sdlxx::mixer::SDL_mixer::~SDL_mixer() {
#ifndef SDLXX_RELEASE
    sdlxx::core::Log::log("Cleaning up SDL audio mix system...");
#endif
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
