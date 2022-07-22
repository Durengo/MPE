#pragma once

#include "MPE/Renderer/Shaders/Shader.h"

#include <glm/glm.hpp>

// TEMP
typedef unsigned int GLenum;
// TEMP

namespace MPE
{
    class OpenGLShader : public Shader
    {
    private:
        uint32_t SYS_Renderer_ID;
        std::string SHADER_NAME;

        std::string ValidateFile(const std::string &filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);
        void Compile(std::unordered_map<GLenum, std::string> &shaders);

    public:
        OpenGLShader(const std::string &filepath);
        OpenGLShader(const std::string &name, const std::string &vertexSource, const std::string &fragmentSource);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        // DEBUG
        virtual void Unbind() const override;
        // DEBUG

        virtual const std::string &GetName() const override { return SHADER_NAME; };

        void InjectUniformInt1(const std::string &name, int value);
        // void InjectUniformInt2(const std::string &name, int values[2]);
        // void InjectUniformInt3(const std::string &name, int values[3]);
        // void InjectUniformInt4(const std::string &name, int values[4]);

        void InjectUniformFloat1(const std::string &name, float value);
        void InjectUniformFloat2(const std::string &name, const glm::vec2 &vector2);
        void InjectUniformFloat3(const std::string &name, const glm::vec3 &vector3);
        void InjectUniformFloat4(const std::string &name, const glm::vec4 &vector4);

        void InjectUniformMat3(const std::string &name, const glm::mat3 &matrix);
        void InjectUniformMat4(const std::string &name, const glm::mat4 &matrix);
    };
}