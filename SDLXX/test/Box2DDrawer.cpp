#include "Box2DDrawer.h"

void Box2DDrawer::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    SDL_SetRenderDrawColor(renderer, (Uint8) (255 * color.r), (Uint8) (255 * color.g), (Uint8) (255 * color.b), (Uint8) (255 * color.a));
    SDL_Point points[vertexCount];
    for (int32 i = 0; i < vertexCount; i++) {
        points[i].x = (int) (vertices[i].x * scale);
        points[i].y = (int) (vertices[i].y * scale);
    }
    SDL_RenderDrawLines(renderer, points, vertexCount);
}

void Box2DDrawer::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    // TODO: Fill
    SDL_SetRenderDrawColor(renderer, (Uint8) (255 * color.r), (Uint8) (255 * color.g), (Uint8) (255 * color.b), (Uint8) (255 * color.a));
    SDL_Point points[vertexCount];
    for (int32 i = 0; i < vertexCount; i++) {
        points[i].x = (int) (vertices[i].x * scale);
        points[i].y = (int) (vertices[i].y * scale);
    }
    SDL_RenderDrawLines(renderer, points, vertexCount);
}

void Box2DDrawer::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) {
    SDL_SetRenderDrawColor(renderer, (Uint8) (255 * color.r), (Uint8) (255 * color.g), (Uint8) (255 * color.b), (Uint8) (255 * color.a));
    int r = (int) (radius * scale);
    int x = (int) (center.x * scale);
    int y = (int) (center.y * scale);
    for (int i = x - r; i <= x + r; i++) {
        for (int j = (int) -std::sqrt(r * r - x * x); j <= (int) std::sqrt(r * r - x * x); j++) {
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }
}

void Box2DDrawer::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) {
    // TODO: Fill
    SDL_SetRenderDrawColor(renderer, (Uint8) (255 * color.r), (Uint8) (255 * color.g), (Uint8) (255 * color.b), (Uint8) (255 * color.a));
    int r = (int) (radius * scale);
    int x = (int) (center.x * scale);
    int y = (int) (center.y * scale);
    for (int i = x - r; i <= x + r; i++) {
        for (int j = (int) -std::sqrt(r * r - x * x); j <= (int) std::sqrt(r * r - x * x); j++) {
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }
}

void Box2DDrawer::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
    SDL_SetRenderDrawColor(renderer, (Uint8) (255 * color.r), (Uint8) (255 * color.g), (Uint8) (255 * color.b), (Uint8) (255 * color.a));
    int x1 = (int) (p1.x * scale);
    int y1 = (int) (p1.y * scale);
    int x2 = (int) (p2.x * scale);
    int y2 = (int) (p2.y * scale);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Box2DDrawer::DrawTransform(const b2Transform &xf) {

}

void Box2DDrawer::DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color) {
    SDL_SetRenderDrawColor(renderer, (Uint8) (255 * color.r), (Uint8) (255 * color.g), (Uint8) (255 * color.b), (Uint8) (255 * color.a));
    SDL_RenderDrawPoint(renderer, (int) (p.x * scale), (int) (p.y * scale));
}
