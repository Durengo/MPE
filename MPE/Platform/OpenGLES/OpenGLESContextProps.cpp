#include "OpenGLESContextProps.h"
#include "MPEPCH.h"

namespace MPE
{
std::string OpenGLESContextProps::ToString() const
{
    std::string OpenGlInfo = "OpenGLES Info:\n";
    OpenGlInfo += "\tOpenGLES Version: " + std::to_string(MajorVersion) + "." + std::to_string(MinorVersion) + "\n";
    OpenGlInfo += "\tVendor: " + Vendor + "\n";
    OpenGlInfo += "\tRenderer: " + Renderer + "\n";
    OpenGlInfo += "\tHardcode shader type limit: " + std::to_string(ShaderTypeAmount);

    return OpenGlInfo;
}
}