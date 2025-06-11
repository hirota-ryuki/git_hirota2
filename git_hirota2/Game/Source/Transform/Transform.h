#pragma once
namespace nsEngine {
    class Transform
    {
    public:
        Transform();
        ~Transform();
        void SetPosition(const Vector3& pos) {
            m_position = pos;
        }
        void SetRotation(const Quaternion& m_rot) {
            m_rotation = m_rot;
        }
    private:
        Vector3		m_position = Vector3::Zero; // Position in 3D space
        Quaternion	m_rotation = Quaternion::Identity; // Rotation in 3D space
    };
}
