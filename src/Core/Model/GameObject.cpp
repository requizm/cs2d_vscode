#include "GameObject.hpp"

GameObject::GameObject() : Object()
{
}

GameObject::GameObject(const Vector2<int>& pos, const Sprite& spr,
                       const Vector2<int>& size, ObjectType type)
    : Object(pos, size, 0)
{
    objType = type;
    sprite = spr;
    cellPos = Utils::PositionToCell(pos);
}

GameObject::~GameObject() = default;

void GameObject::DrawModel(SpriteRenderer& renderer)
{
    renderer.DrawSprite(this->sprite, this->GetTransform());
}

void GameObject::SetTransform(const Vector2<int>& pos, const Vector2<int>& size, int rot)
{
    this->size = size;
    this->rotation = rot;
    SetPosition(pos, true);
}

void GameObject::SetPosition(const Vector2<int>& pos, bool changeCell)
{
    Object::SetPosition(pos);
    if (changeCell)
    {
        Vector2<int> newCellPos =
            Utils::PositionToCell(this->GetPositionOfCenter());
        if (newCellPos != cellPos)
        {
            cellPos = newCellPos;
        }
    }
}

void GameObject::setCellPosition(const Vector2<int>& pos, bool changeCell)
{
    SetPosition(Vector2<int>(pos.x * GameParameters::SIZE_TILE,
                             pos.y * GameParameters::SIZE_TILE),
                changeCell);
}

ObjectType GameObject::GetObjectType() { return this->objType; }

Vector2<int> GameObject::GetCellPos() { return this->cellPos; }

bool GameObject::IsParent()
{
    bool returnn;
    if (parent != nullptr)
    {
        returnn = true;
    }
    else
    {
        returnn = false;
    }
    return returnn;
}

GLboolean GameObject::IsCollision() const { return isCollision; }

std::string GameObject::GetObjectTypeString()
{
    std::string str;
    switch ((int)this->objType)
    {
        case 0:
            str = "Player";
            break;
        case 1:
            str = "Weapon";
            break;
        case 2:
            str = "GameObject";
            break;
        case 3:
            str = "Tile";
            break;
        default:
            str = "Bilinmeyen";
            break;
    }
    return str;
}