#ifndef SDLXX_TEXTURE_H
#define SDLXX_TEXTURE_H

#include <string>
#include <SDL_render.h>

namespace SDL {
    class Texture {
    public:
        // Initializes variables
        Texture();

        // Deallocates memory
        ~Texture();

        //Loads image at specified path
        bool loadFromFile(SDL_Renderer *renderer, std::string path);

        #ifdef _SDL_TTF_H
        //Creates image from font string
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
        #endif

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue);

        //Set blending
        void setBlendMode(SDL_BlendMode blending);

        //Set alpha modulation
        void setAlpha(Uint8 alpha);

        //Renders texture at given point
        void render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);

        //Gets image dimensions
        int getWidth();

        int getHeight();

    private:
        SDL_Texture *texture;

        int width;
        int height;
    };
}

#endif // SDLXX_TEXTURE_H
