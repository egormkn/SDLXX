#include "Box2DDrawer.h"

#include <cmath>
#include <SDL.h>

Box2DDrawer::Box2DDrawer(const std::shared_ptr<sdlxx::core::Renderer>& r, float s = 1.f)
    : renderer_ptr(r->renderer_ptr), scale(s) {}

void Box2DDrawer::SetScale(float s) { scale = s; }

void Box2DDrawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount,
                              const b2Color& color) {
  SetColor(color);
  SDL_Point points[vertexCount + 1];
  for (int32 i = 0; i < vertexCount; i++) {
    points[i].x = (int)(vertices[i].x * scale);
    points[i].y = (int)(vertices[i].y * scale);
  }
  points[vertexCount].x = points[0].x;
  points[vertexCount].y = points[0].y;
  SDL_RenderDrawLines(static_cast<SDL_Renderer*>(renderer_ptr), points, vertexCount + 1);
}

void Box2DDrawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount,
                                   const b2Color& color) {
  DrawPolygon(vertices, vertexCount, color);
}

void Box2DDrawer::DrawCircle(const b2Vec2& center, float radius,
                             const b2Color& color) {
  SetColor(color);

  const float k_segments = 24.0f;
  const float k_increment = 2.0f * b2_pi / k_segments;
  float sinInc = sinf(k_increment);
  float cosInc = cosf(k_increment);
  b2Vec2 r1(1.0f, 0.0f);
  b2Vec2 v1 = center + radius * r1;
  for (int32 i = 0; i < k_segments; ++i) {
    // Perform rotation to avoid additional trigonometry.
    b2Vec2 r2;
    r2.x = cosInc * r1.x - sinInc * r1.y;
    r2.y = sinInc * r1.x + cosInc * r1.y;
    b2Vec2 v2 = center + radius * r2;
    SDL_RenderDrawLine(static_cast<SDL_Renderer*>(renderer_ptr), (int)(v1.x * scale), (int)(v1.y * scale),
                       (int)(v2.x * scale), (int)(v2.y * scale));
    r1 = r2;
    v1 = v2;
  }
}

void Box2DDrawer::DrawSolidCircle(const b2Vec2& center, float radius,
                                  const b2Vec2& axis, const b2Color& color) {
  DrawCircle(center, radius, color);
  int x = (int)(center.x * scale);
  int y = (int)(center.y * scale);
  int ax = (int)(axis.x * radius * scale);
  int ay = (int)(axis.y * radius * scale);
  SDL_RenderDrawLine(static_cast<SDL_Renderer*>(renderer_ptr), x, y, x + ax, y + ay);
}

void Box2DDrawer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2,
                              const b2Color& color) {
  SetColor(color);
  const int x1 = (int)(p1.x * scale);
  const int y1 = (int)(p1.y * scale);
  const int x2 = (int)(p2.x * scale);
  const int y2 = (int)(p2.y * scale);
  SDL_RenderDrawLine(static_cast<SDL_Renderer*>(renderer_ptr), x1, y1, x2, y2);
}

void Box2DDrawer::DrawTransform(const b2Transform& xf) {
  // TODO
}

void Box2DDrawer::DrawPoint(const b2Vec2& p, float size,
                            const b2Color& color) {
  SetColor(color);
  const int halfSize = (int)(size * scale / 2 + 1);
  const SDL_Rect point = {(int)(p.x * scale - halfSize),
                          (int)(p.y * scale - halfSize), halfSize * 2,
                          halfSize * 2};
  SDL_RenderDrawRect(static_cast<SDL_Renderer*>(renderer_ptr), &point);
}

void Box2DDrawer::SetColor(const b2Color& color) {
  SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(renderer_ptr), (Uint8)(255 * color.r),
                         (Uint8)(255 * color.g), (Uint8)(255 * color.b),
                         (Uint8)(255 * color.a));
}
