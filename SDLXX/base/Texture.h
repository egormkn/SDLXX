#ifndef SDLXX_TEXTURE_H
#define SDLXX_TEXTURE_H

#include <string>
#include <SDL_render.h>
#include <SDL_image.h>

namespace SDLXX {
    class Texture {
    public:
        // Initializes variables
        Texture() {
            //Initialize
            texture = nullptr;
            width = 0;
            height = 0;
        }

        Texture(SDL_Texture *t) {
            //Initialize
            texture = t;
            width = 0;
            height = 0;
        }


        // Deallocates memory
        ~Texture() {
            //Deallocate
            free();
        }

        //Loads image at specified path
        bool loadFromFile(SDL_Renderer *renderer, std::string path) {
            //Get rid of preexisting texture
            free();

            //The final texture
            SDL_Texture *newTexture = nullptr;

            //Load image at specified path
            SDL_Surface *loadedSurface = IMG_Load(path.c_str());
            if(loadedSurface == nullptr) {
                printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
            } else {
                //Color key image
                SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

                //Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
                if(newTexture == nullptr) {
                    printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
                } else {
                    //Get image dimensions
                    width = loadedSurface->w;
                    height = loadedSurface->h;
                }

                //Get rid of old loaded surface
                SDL_FreeSurface(loadedSurface);
            }

            //Return success
            texture = newTexture;
            return texture != nullptr;
        }

#ifdef _SDL_TTF_H
        /*//Creates image from font string
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor) {
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface != nullptr )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == nullptr )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }


    //Return success
    return mTexture != nullptr;
}*/
#endif

        //Deallocates texture
        void free() {
            //Free texture if it exists
            if(texture != nullptr) {
                SDL_DestroyTexture(texture);
                texture = nullptr;
                width = 0;
                height = 0;
            }
        }

        //Set color modulation
        void setColor(Uint8 red, Uint8 green, Uint8 blue) {
            //Modulate texture rgb
            SDL_SetTextureColorMod(texture, red, green, blue);
        }

        //Set blending
        void setBlendMode(SDL_BlendMode blending) {
            //Set blending function
            SDL_SetTextureBlendMode(texture, blending);
        }

        //Set alpha modulation
        void setAlpha(Uint8 alpha) {
            //Modulate texture alpha
            SDL_SetTextureAlphaMod(texture, alpha);
        }

        //Renders texture at given point
        void render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = nullptr, double angle = 0.0,
                    SDL_Point *center = nullptr,
                    SDL_RendererFlip flip = SDL_FLIP_NONE) {
            //Set rendering space and render to screen
            SDL_Rect renderQuad = {x, y, width, height};

            //Set clip rendering dimensions
            if(clip != nullptr) {
                renderQuad.w = clip->w;
                renderQuad.h = clip->h;
            }

            //Render to screen
            SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
        }

        //Gets image dimensions
        int getWidth() {
            return width;
        }

        int getHeight() {
            return height;
        }

        SDL_Texture *getSDLTexture() const {
            return texture;
        }

    private:
        SDL_Texture *texture;

        int width;
        int height;
    };
}

#endif // SDLXX_TEXTURE_H
