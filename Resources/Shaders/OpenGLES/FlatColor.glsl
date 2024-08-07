// BASIC FLAT COLOR TEXTURE

#type vertex
#version 300 es

// Vertex Shader
layout(location = 0) in vec3 ATTR_POS;

uniform mat4 UNI_VPM;
uniform mat4 UNI_MODELMAT;

out highp vec3 VAR_POS;

void main()
{
    VAR_POS = ATTR_POS;
    gl_Position = UNI_VPM * UNI_MODELMAT * vec4(ATTR_POS, 1.0);
}

#type fragment
#version 300 es

// Fragment Shader
precision mediump float;

in highp vec3 VAR_POS;

uniform mediump vec4 UNI_COLOR;

layout(location = 0) out mediump vec4 LOCAL_COLOR;

void main()
{
    LOCAL_COLOR = UNI_COLOR;
}
