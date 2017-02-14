#ifndef SDLXX_BOX2DDRAWER_H
#define SDLXX_BOX2DDRAWER_H

#include <Box2D/Common/b2Draw.h>
#include "../base/Renderer.h"

class Box2DDrawer : public b2Draw {
public:
    Box2DDrawer(SDL_Renderer *r, float s);

    void SetScale(float s);

    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;

    void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) override;

    void DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) override;

    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override;

    void DrawTransform(const b2Transform &xf) override;

    void DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color) override;

private:
    SDL_Renderer *renderer = nullptr;
    float scale = 0.f;

    void SetColor(const b2Color &color);
};


#endif // SDLXX_BOX2DDRAWER_H
