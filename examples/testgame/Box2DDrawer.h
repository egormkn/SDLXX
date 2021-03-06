#ifndef BOX2DDRAWER_H
#define BOX2DDRAWER_H

#include <box2d/b2_draw.h>
#include <sdlxx/core/renderer.h>

class Box2DDrawer : public b2Draw {
public:
  Box2DDrawer(const std::shared_ptr<sdlxx::core::Renderer>& renderer, float s);

  void SetScale(float s);

  void DrawPolygon(const b2Vec2* vertices, int32 vertexCount,
                   const b2Color& color) override;

  void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount,
                        const b2Color& color) override;

  void DrawCircle(const b2Vec2& center, float radius,
                  const b2Color& color) override;

  void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis,
                       const b2Color& color) override;

  void DrawSegment(const b2Vec2& p1, const b2Vec2& p2,
                   const b2Color& color) override;

  void DrawTransform(const b2Transform& xf) override;

  void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;

private:
  void* renderer_ptr = nullptr;
  float scale = 0.f;

  void SetColor(const b2Color& color);
};

#endif  // BOX2DDRAWER_H
