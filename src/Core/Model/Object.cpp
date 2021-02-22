#include "Object.hpp"

Object::Object()
{
    id = Utils::GenerateID();
    BuildTransform();
}

Object::Object(const Vector2<int> &pos, const Vector2<int> &siz, int rot)
{
    position = pos;
    size = siz;
    rotation = rot;
    id = Utils::GenerateID();
    BuildTransform();
}

void Object::BuildTransform()
{
    Matrix4<float> model = Matrix4<float>(1.0F);
    model = Projection::translate(
        model, Vector3<float>(static_cast<float>(position.x),
                              static_cast<float>(position.y), 0.0F));
    model = Projection::translate(
        model, Vector3<float>(0.5F * static_cast<float>(size.x),
                              0.5F * static_cast<float>(size.y),
                              0.0F));  // Move origin of rotation to center of quad
    model = Projection::rotate(
        model, Projection::radians(static_cast<float>(rotation)),
        Vector3<float>(0.0F, 0.0F, 1.0F));  // Then rotate
    model = Projection::translate(
        model, Vector3<float>(-0.5F * static_cast<float>(size.x),
                              -0.5F * static_cast<float>(size.y),
                              0.0F));  // Move origin back
    model = Projection::scale(model,
                              Vector3<float>(static_cast<float>(size.x),
                                             static_cast<float>(size.y), 1.0F));
    SetTransform(model);
    UpdateChilds();
}

bool Object::IsParent() const
{
    return parent != nullptr;
}

Vector2<int> Object::GetPositionOfCenter()
{
    return Vector2<int>(position.x + size.x / 2,
                        position.y + size.y / 2);
}

void Object::UpdateChilds()
{
    for (auto &child : childs)
    {
        Matrix4 chi = child->GetLocalTransform();
        child->SetTransform(transform * chi);
    }
}

Vector2<int> Object::GetLocalPosition() const { return localPosition; }

void Object::SetLocalPosition(const Vector2<int> &value) { localPosition = value; }

Vector2<int> Object::GetLocalSize() const { return localSize; }

void Object::SetLocalSize(const Vector2<int> &value) { localSize = value; }

int Object::GetLocalRotation() const { return localRotation; }

void Object::SetLocalRotation(int value) { localRotation = value; }

Vector2<int> Object::GetPosition() const { return position; }

void Object::SetPosition(const Vector2<int> &value)
{
    position = value;
    BuildTransform();
}

Vector2<int> Object::GetSize() const { return size; }

void Object::SetSize(const Vector2<int> &value)
{
    size = value;
    BuildTransform();
}

int Object::GetRotation() const { return rotation; }

void Object::SetRotation(int value)
{
    rotation = value;
    BuildTransform();
}

Matrix4<float> Object::GetLocalTransform() const { return localTransform; }

void Object::SetLocalTransform(const Matrix4<float> &value) { localTransform = value; }

Matrix4<float> Object::GetTransform() const { return transform; }

void Object::SetTransform(const Matrix4<float> &value) { transform = value; }

Object *Object::GetParent() const { return parent; }

void Object::SetParent(Object *value)
{
    value->childs.push_back(this);
    parent = value;
    localTransform =
        Projection::inverse(parent->GetTransform()) * transform;
}

void Object::RemoveParent()
{
    int i = 0;
    for (std::vector<int>::size_type i = 0; i != parent->childs.size(); i++)
    {
        if (parent->childs[i]->GetId() == GetId())
        {
            parent->childs.erase(parent->childs.begin() + i);
            break;
        }
    }
    localTransform = transform;
    parent = nullptr;
}

int Object::GetId() const { return id; }
