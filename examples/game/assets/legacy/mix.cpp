

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
