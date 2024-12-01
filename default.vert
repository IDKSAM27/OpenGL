// Shaders scene, no need to understand yet, maybe you can simply copy paste this code in gpt to know more,
// Basically I'm building my own shaders scene
// * : pointer, it stores the memory address of another variable, it "points to" the location of the value in the memory	
// Vertex Shader Source code

#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}