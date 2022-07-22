#include "MPE/MPEPCH.h"
#include "Layer.h"

namespace MPE
{
    Layer::Layer(const std::string &debugName)
        : SYS_DebugName(debugName) {}

    Layer::~Layer() {}
}