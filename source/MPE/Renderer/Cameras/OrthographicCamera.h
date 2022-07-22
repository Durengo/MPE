#pragma once

#include <glm/glm.hpp>

namespace MPE
{
    class OrthographicCamera
    {
    private:
        glm::mat4 PROJECTION_MATRIX;
        glm::mat4 VIEW_MATRIX;
        glm::mat4 PROJECTION_VIEW_MATRIX;

        glm::vec3 CAMERA_POSITION = {0.0f, 0.0f, 0.0f};
        float CAMERA_Z_AXIS_ROTATION = 0.0f;

        void COMPUTE_VIEW_MATRIX();

    public:
        // float near, float far
        OrthographicCamera(float left, float right, float bottom, float top);
        void SetProjection(float left, float right, float bottom, float top);

        void SetPosition(const glm::vec3 &position)
        {
            CAMERA_POSITION = position;
            COMPUTE_VIEW_MATRIX();
        }
        void SetRotation(float rotation)
        {
            CAMERA_Z_AXIS_ROTATION = rotation;
            COMPUTE_VIEW_MATRIX();
        }

        const glm::vec3 &GetPosition() const { return CAMERA_POSITION; }
        float GetRotation() const { return CAMERA_Z_AXIS_ROTATION; }

        const glm::mat4 &GetProjectionMatrix() const { return PROJECTION_MATRIX; }
        const glm::mat4 &GetViewMatrix() const { return VIEW_MATRIX; }
        const glm::mat4 &GetProjectionViewMatrix() const { return PROJECTION_VIEW_MATRIX; }
    };
}