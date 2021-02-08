#include "Collider.hpp"

Collider::Collider(Vector2<int> pos, ColliderTypes _type) : type(_type), position(pos)
{
}

Collider::Collider(ColliderTypes _type) : type(_type)
{
}

Collider::~Collider()
{
}

ColliderTypes Collider::GetType()
{
    return this->type;
}

Vector2<int> Collider::GetPosition()
{
    return this->position;
}

void Collider::SetPosition(Vector2<int> pos)
{
    this->position = pos;
}
