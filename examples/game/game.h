#ifndef SDLXX_GAME_H
#define SDLXX_GAME_H

#include <box2d/box2d.h>

#include "Box2DDrawer.h"

namespace sdlxx {

class Game : public Scene {
public:
  explicit Game() : Scene("The game") {
    b2Vec2 gravity(0.0f, 9.8f);
    world = std::make_unique<b2World>(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(3.5f, 15.0f);
    groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(3.0f, 2.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(5.0f, 4.0f);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
  }

  ~Game() {
    world->DestroyBody(groundBody);
    world->DestroyBody(body);
    body = nullptr;
    groundBody = nullptr;
  }

protected:
  void OnActivate() override {
    Scene::OnActivate();
    drawer = std::make_unique<Box2DDrawer>(GetContext()->renderer, 30.f);
    drawer->SetFlags(0xFF);
    world->SetDebugDraw(drawer.get());
  }

  void OnDeactivate() override {
    world->SetDebugDraw(nullptr);
    drawer.reset(nullptr);
    Scene::OnDeactivate();
  }

public:
  bool HandleEvent(const Event& e) override { return ParentNode::HandleEvent(e); }

  void Update(Time dt) override { world->Step(dt.AsSeconds(), 6, 2); }

  void Render(Renderer& renderer) const override {
    world->DebugDraw();
  }

private:
  std::unique_ptr<b2World> world;
  std::unique_ptr<Box2DDrawer> drawer;

  b2Body* body = nullptr;
  b2Body* groundBody = nullptr;
};

}  // namespace sdlxx

#endif  // SDLXX_GAME_H
