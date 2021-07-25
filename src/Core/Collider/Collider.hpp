#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>

#include "../Math/Vector2.hpp"

enum ColliderTypes
{
    CIRCLE,
    RECTANGLE
};

class Collider
{
   private:
    ColliderTypes type;

   protected:
    Vector2<int> position = Vector2<int>(0);

   public:
    explicit Collider(const Vector2<int> &pos, ColliderTypes _type);
    explicit Collider(ColliderTypes _type);
    ~Collider() = default;

    ColliderTypes GetType();

    Vector2<int> GetPosition();
    void SetPosition(const Vector2<int> &pos);
};

#endif  // COLLIDER_H