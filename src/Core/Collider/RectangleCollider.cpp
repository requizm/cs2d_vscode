#include "RectangleCollider.hpp"

RectangleCollider::RectangleCollider(const Vector2<int> &pos, const Vector2<int> &siz)
    : Collider(pos, ColliderTypes::RECTANGLE), size(siz) {}

RectangleCollider::RectangleCollider() : Collider(ColliderTypes::RECTANGLE) {}

Vector2<int> RectangleCollider::GetSize() { return this->size; }

void RectangleCollider::SetSize(const Vector2<int> &siz) { this->size = siz; }