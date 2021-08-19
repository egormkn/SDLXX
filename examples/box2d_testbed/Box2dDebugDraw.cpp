#include "Box2dDebugDraw.h"

#include <vector>

using namespace std;

Box2dDebugDraw::Box2dDebugDraw(sdlxx::Renderer& renderer, float scale)
    : renderer(renderer), scale(scale) {}

void Box2dDebugDraw::SetScale(float new_scale) {
  scale = new_scale;
}

void Box2dDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertex_count, const b2Color& color) {
  renderer.SetDrawColor(ConvertColor(color));
  vector<sdlxx::Point> points(vertex_count + 1);
  for (auto i = 0; i < vertex_count; ++i) {
    points[i].x = static_cast<int>(vertices[i].x * scale);
    points[i].y = static_cast<int>(vertices[i].y * scale);
  }
  points[vertex_count] = points[0];
  renderer.DrawLines(points);
}
void Box2dDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertex_count,
                                      const b2Color& color) {
  DrawPolygon(vertices, vertex_count, color);
}

void Box2dDebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
  renderer.SetDrawColor(ConvertColor(color));
  const float k_segments = 24.0f;
  const float k_increment = 2.0f * b2_pi / k_segments;
  float sinInc = sinf(k_increment);
  float cosInc = cosf(k_increment);
  b2Vec2 r1(1.0f, 0.0f);
  b2Vec2 v1 = center + radius * r1;
  for (auto i = 0; i < static_cast<int>(k_segments); ++i) {
    // Perform rotation to avoid additional trigonometry.
    b2Vec2 r2;
    r2.x = cosInc * r1.x - sinInc * r1.y;
    r2.y = sinInc * r1.x + cosInc * r1.y;
    b2Vec2 v2 = center + radius * r2;
    renderer.DrawLine({static_cast<int>(v1.x * scale), static_cast<int>(v1.y * scale)},
                      {static_cast<int>(v2.x * scale), static_cast<int>(v2.y * scale)});
    r1 = r2;
    v1 = v2;
  }
}

void Box2dDebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis,
                                     const b2Color& color) {
  DrawCircle(center, radius, color);
  int x = static_cast<int>(center.x * scale);
  int y = static_cast<int>(center.y * scale);
  int ax = static_cast<int>(axis.x * radius * scale);
  int ay = static_cast<int>(axis.y * radius * scale);
  renderer.DrawLine({x, y}, {x + ax, y + ay});
}

void Box2dDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
  renderer.SetDrawColor(ConvertColor(color));
  int x1 = static_cast<int>(p1.x * scale);
  int y1 = static_cast<int>(p1.y * scale);
  int x2 = static_cast<int>(p2.x * scale);
  int y2 = static_cast<int>(p2.y * scale);
  renderer.DrawLine({x1, y1}, {x2, y2});
}

void Box2dDebugDraw::DrawTransform(const b2Transform& xf) {}

void Box2dDebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color) {
  renderer.SetDrawColor(ConvertColor(color));
  int half_size = static_cast<int>(size * scale / 2 + 1);
  const sdlxx::Rectangle point = {static_cast<int>(p.x * scale - half_size),
                                  static_cast<int>(p.y * scale - half_size), half_size * 2,
                                  half_size * 2};
  renderer.DrawRectangle(point);
}

sdlxx::Color Box2dDebugDraw::ConvertColor(const b2Color& color) {
  return {static_cast<uint8_t>(color.r * 255), static_cast<uint8_t>(color.g * 255),
          static_cast<uint8_t>(color.b * 255), static_cast<uint8_t>(color.a * 255)};
}
