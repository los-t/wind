// Project: wind
// File: assets/sphere/vertex.glsl
// Author: Vladimir 'dvn' Dranyonkov <los-t@ya.ru>
// Description: A simple vertex shader
#version 120

attribute vec3 coord3d;

void main(void) {
	gl_Position = vec4(coord3d, 1.0);
}
