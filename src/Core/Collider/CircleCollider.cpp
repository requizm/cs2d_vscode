#include "CircleCollider.hpp"

CircleCollider::CircleCollider(Vector2<int> pos, int r) : Collider(pos, ColliderTypes::CIRCLE), radius(r)
{
}

CircleCollider::CircleCollider() : Collider(ColliderTypes::CIRCLE)
{
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::Intersect(RectangleCollider &col) //top left axis
{
    // clamp(value, min, max) - limits value to the range min..max

    // Find the closest point to the circle within the rectangle
    int closestX = std::clamp(this->position.x, col.GetPosition().x, col.GetPosition().x + col.GetSize().x);
    int closestY = std::clamp(this->position.y, col.GetPosition().y, col.GetPosition().y + col.GetSize().y);

    // Calculate the distance between the circle's center and this closest point
    int distanceX = this->position.x - closestX;
    int distanceY = this->position.y - closestY;

    // If the distance is less than the circle's radius, an intersection occurs
    int distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
    return distanceSquared < (this->radius * this->radius);
}

bool CircleCollider::Intersect(CircleCollider &col)
{
}