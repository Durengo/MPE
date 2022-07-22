#pragma once

namespace MPE
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        // DEBUG
        virtual void Unbind() const = 0;
        // DEBUG

        virtual const std::string &GetName() const = 0;

        static REF<Shader> Create(const std::string &filepath);
        static REF<Shader> Create(const std::string &name, const std::string &vertexSource, const std::string &fragmentSource);

        // virtual void InjectUniformBuffer
    };
}