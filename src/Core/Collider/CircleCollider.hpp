#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include <algorithm>

#include "Collider.hpp"
#include "RectangleCollider.hpp"

class CircleCollider : public Collider
{
   public:
    CircleCollider(Vector2<int> pos, int r);
    CircleCollider();
    ~CircleCollider() = default;

    bool Intersect(RectangleCollider &col);
    bool Intersect(CircleCollider &col);

    int radius = 1;  // FIXME: private olacak

   private:
};

#endif  // CIRCLECOLLIDER_H