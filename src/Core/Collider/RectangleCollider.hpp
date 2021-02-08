#ifndef RECTANGLECOLLIDER_H
#define RECTANGLECOLLIDER_H

#include "Collider.hpp"

class RectangleCollider : public Collider
{
public:
    RectangleCollider(Vector2<int> pos, Vector2<int> siz);
    RectangleCollider();
    ~RectangleCollider();

    Vector2<int> GetSize();
    void SetSize(Vector2<int> siz);

private:
    Vector2<int> size = Vector2<int>(0);
};

#endif // RECTANGLECOLLIDER_H