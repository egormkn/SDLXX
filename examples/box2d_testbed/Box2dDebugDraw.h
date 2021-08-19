#ifndef SDLXX_BOX2D_DEBUG_DRAW_H
#define SDLXX_BOX2D_DEBUG_DRAW_H

#include <cstdint>

#include <box2d/b2_draw.h>
#include <sdlxx/core/color.h>
#include <sdlxx/core/renderer.h>

class Box2dDebugDraw : public b2Draw {
public:
  /// Construct debug drawer using the renderer and the scale (default: 1m = 100px)
  explicit Box2dDebugDraw(sdlxx::Renderer& renderer, float scale = 100.);

  /// Change scale.
  void SetScale(float new_scale);

  /// Draw a closed polygon provided in CCW order.
  void DrawPolygon(const b2Vec2* vertices, int32 vertex_count, const b2Color& color) override;

  /// Draw a solid closed polygon provided in CCW order.
  void DrawSolidPolygon(const b2Vec2* vertices, int32 vertex_count, const b2Color& color) override;

  /// Draw a circle.
  void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;

  /// Draw a solid circle.
  void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis,
                       const b2Color& color) override;

  /// Draw a line segment.
  void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

  /// Draw a transform. Choose your own length scale.
  void DrawTransform(const b2Transform& xf) override;

  /// Draw a point.
  void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;

private:
  sdlxx::Renderer& renderer;
  float scale;

  /// Convert Box2D OpenGL style color definition [0-1] to SDL color definition [0-255].
  static sdlxx::Color ConvertColor(const b2Color& color);
};

#endif  // SDLXX_BOX2D_DEBUG_DRAW_H
