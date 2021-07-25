#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include <algorithm>

#include "Collider.hpp"
#include "RectangleCollider.hpp"

class CircleCollider : public Collider
{
   public:
    CircleCollider(const Vector2<int> &pos, int r);
    CircleCollider();
    ~CircleCollider() = default;

    bool Intersect(RectangleCollider &col);

    int GetRadius() const;
    void SetRadius(int radius_);

   private:
    int radius = 1;
};

#endif  // CIRCLECOLLIDER_H