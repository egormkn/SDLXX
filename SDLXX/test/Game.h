#ifndef SDLXX_GAME_H
#define SDLXX_GAME_H

#include <fstream>
#include <SDL_timer.h>
#include <vector>
#include "../SDLXX_image.h"
#include "../base/Scene.h"
#include "../base/Texture.h"

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

            b2Vec2 gravity(0.0f, -9.8f);
            world = std::make_unique<b2World>(gravity);


            /*b2BodyDef groundBodyDef;
            groundBodyDef.position.Set(0.0f, -10.0f);
            b2Body *groundBody = m_world->CreateBody(&groundBodyDef);
            b2PolygonShape groundBox;
            groundBox.SetAsBox(50.0f, 10.0f);

            groundBody->CreateFixture(&groundBox, 0.0f);*/



            // Define the ground body.
            b2BodyDef groundBodyDef;
            groundBodyDef.position.Set(0.0f, -10.0f);

            // Call the body factory which allocates memory for the ground body
            // from a pool and creates the ground box shape (also from a pool).
            // The body is also added to the world.
            b2Body *groundBody = world->CreateBody(&groundBodyDef);

            // Define the ground box shape.
            b2PolygonShape groundBox;

            // The extents are the half-widths of the box.
            groundBox.SetAsBox(50.0f, 10.0f);

            // Add the ground fixture to the ground body.
            groundBody->CreateFixture(&groundBox, 0.0f);



            // Define the dynamic body. We set its position and call the body factory.
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.position.Set(0.0f, 10.0f);
            body = world->CreateBody(&bodyDef);

            // Define another box shape for our dynamic body.
            b2PolygonShape dynamicBox;
            dynamicBox.SetAsBox(1.0f, 1.0f);

            // Define the dynamic body fixture.
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;

            // Set the box density to be non-zero, so it will be dynamic.
            fixtureDef.density = 1.0f;

            // Override the default friction.
            fixtureDef.friction = 0.3f;

            // Add the shape to the body.
            body->CreateFixture(&fixtureDef);

            // Prepare for simulation. Typically we use a time step of 1/60 of a
            // second (60Hz) and 10 iterations. This provides a high quality simulation
            // in most game scenarios.
            float32 timeStep = 1.0f / 60.0f;

        }

        void onDestroy() override {
            Log::log("[" + getTitle() + "] Scene destroyed");
            // Free resources


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
                } else if(e.getEvent().key.keysym.sym == SDLK_SPACE) {
                    if(e.getEvent().key.repeat == 0) {
                        Log::log("JUMP");
                        body->ApplyLinearImpulse( b2Vec2(0,20), body->GetWorldCenter(), true );
                    }
                } else {
                    finish();
                }
            }
        }

        void update(Uint32 t, Uint32 dt) override {
            world->Step(((float32) dt) / 1000.0f, 6, 2);
            pos++;
            if(pos > 300) {
                pos = 0;
            }
        }

        void render(Renderer &renderer) override {
            renderer.setColor(Color(0xFFFFFFFF));
            renderer.clear();

            b2Vec2 position = body->GetPosition();
            float32 angle = body->GetAngle();

            SDL_Rect fillRect = {
                    10, 201 - (int) (position.y * 20), 100, 100
            };

            renderer.setColor(Color(0xFF8888FF));
            renderer.fillRect(&fillRect);
            renderer.render();
        }

    private:
        int pos = 0;
        Window *window = nullptr;

        std::unique_ptr<b2World> world;
        b2Body *body = nullptr;

    };
}

#endif // SDLXX_GAME_H
