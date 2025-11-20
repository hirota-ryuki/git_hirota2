#include "stdafx.h"
#include "Transform.h"


namespace nsApp {
    Transform::Transform()
        :m_localPosition(Vector3::Zero)
        , m_localRotation(Quaternion::Identity)
        , m_localScale(Vector3::One)
        , m_position(Vector3::Zero)
        , m_rotation(Quaternion::Identity)
        , m_scale(Vector3::One)
        , m_worldMatrix(Matrix::Identity)
        , m_rotationMatrix(Matrix::Identity)
        , m_parent(nullptr)
    {
    }


    Transform::~Transform()
    {
    }


    void Transform::UpdateTransform()
    {
    }


    void Transform::UpdateWorldMatrix()
    {
    }
}
