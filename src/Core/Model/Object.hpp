#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "../Manager/Utils.hpp"
#include "../Math/Matrix4.hpp"
#include "../Math/Projection.hpp"
#include "../Math/Vector2.hpp"

class Object
{
   public:
    Object();
    Object(const Vector2<int> &pos, const Vector2<int> &siz, int rot);
    Object(Object &&) = default;
    Object(const Object &) = default;
    Object &operator=(Object &&) = default;
    Object &operator=(const Object &) = default;
    ~Object() = default;

    void BuildTransform();
    bool IsParent() const;
    Vector2<int> GetPositionOfCenter();
    void UpdateChilds();

    Vector2<int> GetLocalPosition() const;
    void SetLocalPosition(const Vector2<int> &value);

    Vector2<int> GetLocalSize() const;
    void SetLocalSize(const Vector2<int> &value);

    int GetLocalRotation() const;
    void SetLocalRotation(int value);

    Vector2<int> GetPosition() const;
    void SetPosition(const Vector2<int> &value);

    Vector2<int> GetSize() const;
    void SetSize(const Vector2<int> &value);

    int GetRotation() const;
    void SetRotation(int value);

    Matrix4<float> GetLocalTransform() const;
    void SetLocalTransform(const Matrix4<float> &value);

    Matrix4<float> GetTransform() const;
    void SetTransform(const Matrix4<float> &value);

    Object *GetParent() const;
    virtual void SetParent(Object *value);
    virtual void RemoveParent();

    int GetId() const;


   protected:
    Vector2<int> localPosition = Vector2<int>(0);
    Vector2<int> localSize = Vector2<int>(1);
    int localRotation = 0;

    Vector2<int> position = Vector2<int>(0);
    Vector2<int> size = Vector2<int>(1);
    int rotation = 0;

    Matrix4<float> localTransform = Matrix4<float>(1.0f);
    Matrix4<float> transform = Matrix4<float>(1.0f);

    Object *parent = nullptr;
    std::vector<Object *> childs;

    int id;

    private:
        void ChangeLocal();
};


#endif  // OBJECT_H