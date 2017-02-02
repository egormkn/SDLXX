#ifndef SDLXX_GAME_H
#define SDLXX_GAME_H

#include <fstream>
#include <SDL_timer.h>
#include <vector>
#include "../SDLXX_image.h"
#include "../base/Scene.h"
#include "../base/Texture.h"
#include "../physics/Object.h"

#include <Box2D/Box2D.h>

namespace SDLXX {
    class Game : public Scene {
    public:

        Game(const std::string &title) : Scene(title) {
            Log::log("[" + getTitle() + "] Scene constructed");
        }

        ~Game() {
            Log::log("[" + getTitle() + "] Scene destructed");
        }

        void onCreate(Window &w) override {
            Log::log("[" + getTitle() + "] Scene created");


            window = &w;
            // Init resources

            // Define the gravity vector.
            /*gravity = new b2Vec2(0.0f, -10.0f);

            // Construct a world object, which will hold and simulate the rigid bodies.
            world = new b2World(*gravity);

            // Define the ground body.
            groundBodyDef = new b2BodyDef;
            groundBodyDef->position.Set(0.0f, -10.0f);

            // Call the body factory which allocates memory for the ground body
            // from a pool and creates the ground box shape (also from a pool).
            // The body is also added to the world.
            groundBody = world->CreateBody(groundBodyDef);

            // Define the ground box shape.
            groundBox = new b2PolygonShape;

            // The extents are the half-widths of the box.
            groundBox->SetAsBox(50.0f, 10.0f);

            // Add the ground fixture to the ground body.
            groundBody->CreateFixture(groundBox, 0.0f);

            // Define the dynamic body. We set its position and call the body factory.
            bodyDef = new b2BodyDef;
            bodyDef->type = b2_dynamicBody;
            bodyDef->position.Set(0.0f, 20.0f);
            body = world->CreateBody(bodyDef);

            // Define another box shape for our dynamic body.
            dynamicBox = new b2PolygonShape;
            dynamicBox->SetAsBox(1.0f, 1.0f);

            // Define the dynamic body fixture.
            fixtureDef = new b2FixtureDef;
            fixtureDef->shape = dynamicBox;

            // Set the box density to be non-zero, so it will be dynamic.
            fixtureDef->density = 1.0f;

            // Override the default friction.
            fixtureDef->friction = 0.3f;

            // Add the shape to the body.
            body->CreateFixture(fixtureDef);

            // Prepare for simulation. Typically we use a time step of 1/60 of a
            // second (60Hz) and 10 iterations. This provides a high quality simulation
            // in most game scenarios.
            float32 timeStep = 1.0f / 60.0f;*/

        }

        void onDestroy() override {
            Log::log("[" + getTitle() + "] Scene destroyed");
            // Free resources
            SDL_DestroyTexture(image);
            image = nullptr;





            /*delete world;
            world = nullptr;

            delete groundBodyDef;
            groundBodyDef = nullptr;

            delete groundBox;
            delete bodyDef;
            delete dynamicBox;
            delete fixtureDef;

            delete gravity;
            gravity = nullptr;*/
        }

        void onPause() override {
            // Save state
            // After: setPaused(true);
        }

        void onResume() override {
            // Restore state
            // After: setPaused(false);
        }

        void handleEvent(Event &e) override {
            if(e.getType() == SDL_KEYDOWN) {
                if(e.getEvent().key.keysym.sym == SDLK_UP) {
                    Log::log("[" + getTitle() + "] UP");
                    //runIntent(new Menu("New title"));
                    // finish();
                    // My changes
                } else {
                    finish();
                }
            }
            if(e.getType() == SDL_WINDOWEVENT) {
                window->getRenderer().render();
            }
        }

        void update(Uint32 t, Uint32 dt) override {
            //world->Step(((float32) dt) / 1000.0f, 6, 2);
        }

        void render(Renderer &renderer) override {
            renderer.setColor(Color(0xFFFFFFFF));
            renderer.clear();

            /*b2Vec2 position = body->GetPosition();
            float32 angle = body->GetAngle();*/

            SDL_Rect fillRect = {
                    (int) (position.x * 10), 10, 100, 100
            };

            renderer.setColor(Color(0xFF8888FF));
            SDL_RenderFillRect(renderer.getSDLRenderer(), &fillRect);
            renderer.render();
        }

    private:
        int pos = 0;
        bool loaded = false;
        std::vector<Object *> objects;
        SDL_Texture *image = nullptr;
        Window *window = nullptr;



        /*b2Vec2 *gravity = nullptr;
        b2World *world = nullptr;
        b2BodyDef *groundBodyDef = nullptr;
        b2Body* groundBody = nullptr;
        b2PolygonShape *groundBox = nullptr;
        b2BodyDef *bodyDef = nullptr;
        b2Body *body = nullptr;
        b2PolygonShape *dynamicBox = nullptr;
        b2FixtureDef *fixtureDef = nullptr;*/


    };
}

#endif // SDLXX_GAME_H
