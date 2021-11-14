// Basic Texture Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord; 
layout(location = 3) in float aTexIndex;
layout(location = 4) in float aTilingFactor;

uniform mat4 uViewProjection;

out vec4 vColor;
out vec2 vTexCoord;
out float vTexIndex;
out float vTilingFactor;

void main(){
	vTexCoord = aTexCoord;
	vColor = aColor;
	vTexIndex = aTexIndex;
	vTilingFactor = aTilingFactor;
	gl_Position = uViewProjection * vec4(aPosition, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 oColor;

in vec4 vColor;
in vec2 vTexCoord;
in float vTexIndex;
in float vTilingFactor;

uniform sampler2D uTextures[32];

void main(){
// TODO: uTilingFactor
	vec4 texColor = vColor;
	switch(int(vTexIndex)){
		case 0: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 1: texColor *= texture(uTextures[1], vTexCoord * vTilingFactor); break;
		case 2: texColor *= texture(uTextures[2], vTexCoord * vTilingFactor); break;
		case 3: texColor *= texture(uTextures[3], vTexCoord * vTilingFactor); break;
		case 4: texColor *= texture(uTextures[4], vTexCoord * vTilingFactor); break;
		case 5: texColor *= texture(uTextures[5], vTexCoord * vTilingFactor); break;
		case 6: texColor *= texture(uTextures[6], vTexCoord * vTilingFactor); break;
		case 7: texColor *= texture(uTextures[7], vTexCoord * vTilingFactor); break;
		case 8: texColor *= texture(uTextures[8], vTexCoord * vTilingFactor); break;
		case 9: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 10: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 11: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 12: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 13: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 14: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 15: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 16: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 17: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 18: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 19: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 20: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 21: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 22: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 23: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 24: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 25: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 26: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 27: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 28: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 29: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 30: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		case 31: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
		default: texColor *= texture(uTextures[0], vTexCoord * vTilingFactor); break;
	}
	oColor = texColor;
}