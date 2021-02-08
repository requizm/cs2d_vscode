#include "RectangleCollider.hpp"

RectangleCollider::RectangleCollider(Vector2<int> pos, Vector2<int> siz) : Collider(pos, ColliderTypes::RECTANGLE), size(siz)
{
}

RectangleCollider::RectangleCollider() : Collider(ColliderTypes::RECTANGLE)
{
}

RectangleCollider::~RectangleCollider()
{
}

Vector2<int> RectangleCollider::GetSize()
{
    this->size;
}

void RectangleCollider::SetSize(Vector2<int> siz)
{
    this->size = siz;
}