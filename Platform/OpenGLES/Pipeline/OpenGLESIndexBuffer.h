#pragma once

#include "MPE/Core/_CORE.h"
#include "MPE/Renderer/Pipeline/IndexBuffer.h"

namespace MPE
{
class MPE_API OpenGLESIndexBuffer : public IndexBuffer
{
  public:
    OpenGLESIndexBuffer(uint32_t *indices, uint32_t count);
    virtual ~OpenGLESIndexBuffer();

    // virtual void SetData() = 0;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual uint32_t GetCount() const override { return SYS_COUNT; }

  private:
    uint32_t SYS_Renderer_ID;
    uint32_t SYS_COUNT;
};
}