#pragma once

#include "MPE/Base/_CORE.h"
#include "MPE/Renderer/Pipeline/BufferLayout.h"

namespace MPE
{
    class VertexBuffer
    {
    private:
    public:
        virtual ~VertexBuffer() = default;

        // virtual void SetData() = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const BufferLayout &GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout &layout) = 0;

        static REF<VertexBuffer> Create(float *vertices, uint32_t size);
    };
}