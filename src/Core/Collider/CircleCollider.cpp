#include "CircleCollider.hpp"
#if defined(WIN32) && defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

CircleCollider::CircleCollider(Vector2<int> pos, int r)
    : Collider(pos, ColliderTypes::CIRCLE), radius(r) {}

CircleCollider::CircleCollider() : Collider(ColliderTypes::CIRCLE) {}

CircleCollider::~CircleCollider() = default;

bool CircleCollider::Intersect(RectangleCollider &col)  // top left axis
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    // get center point circle first
    Vector2<int> center(this->GetPosition());
    // calculate AABB info (center, half-extents)
    Vector2<int> aabb_half_extents(col.GetSize().x / 2, col.GetSize().y / 2);
    Vector2<int> aabb_center(col.GetPosition().x + aabb_half_extents.x,
                             col.GetPosition().y + aabb_half_extents.y);
    // get difference vector between both centers
    Vector2<int> difference = center - aabb_center;
    int cX =
        std::clamp(difference.x, -aabb_half_extents.x, aabb_half_extents.x);
    int cY =
        std::clamp(difference.y, -aabb_half_extents.y, aabb_half_extents.y);
    Vector2<int> clamped = Vector2<int>(cX, cY);
    // add clamped value to AABB_center and we get the value of box closest to
    // circle
    Vector2<int> closest = aabb_center + clamped;
    // retrieve vector between center circle and closest point AABB and check if
    // length <= radius
    difference = closest - center;
    return difference.Magnitude() < this->radius;
}

bool CircleCollider::Intersect(CircleCollider &col) { return false; }