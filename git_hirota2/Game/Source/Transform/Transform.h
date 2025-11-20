/**
 * トランスフォームクラス
 */
#pragma once


namespace nsApp {
    class Transform
    {
    private:
        /** 自信のパラメータ */
        Vector3	m_localPosition;
        Quaternion	m_localRotation;
        Vector3 m_localScale;

        /** 親トランスフォームを考慮したパラメータ */
        Vector3	m_position;
        Quaternion	m_rotation;
        Vector3 m_scale;


    private:
        /** ワールド座標行列 */
        Matrix m_worldMatrix;
        /** 回転行列 */
        Matrix m_rotationMatrix;


    public:
        /** NOTE:親は球体のステージ、子は手に持つ剣のイメージ */
        /** 親のトランスフォーム */
        Transform* m_parent;
        /** 子のトランスフォーム群 */
        std::vector<Transform*> m_children;

    public:
        Transform();
        ~Transform();

    public:
        /** 更新 */
        void UpdateTransform();


    private:
        /** ワールド行列更新、UpdateTransform()で使用 */
        void UpdateWorldMatrix();


    public:

    };
}
