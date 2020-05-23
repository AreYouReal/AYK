// Basic Texture Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord; 
layout(location = 3) in float aTexIndex;

uniform mat4 uViewProjection;

out vec4 vColor;
out vec2 vTexCoord;
out float vTexIndex;

void main(){
	vTexCoord = aTexCoord;
	vColor = aColor;
	vTexIndex = aTexIndex;
	gl_Position = uViewProjection * vec4(aPosition, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 oColor;

in vec4 vColor;
in vec2 vTexCoord;
in float vTexIndex;

uniform float uTilingFactor;
uniform sampler2D uTextures[32];

void main(){
// TODO: uTilingFactor
	oColor = texture(uTextures[int(vTexIndex)], vTexCoord) * vColor;
}