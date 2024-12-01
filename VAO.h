#ifndef VAO_CLASS_H
#define VAO_CLASS_H
	
#include<glad/glad.h>
// We will have to link VBO to VAO so include VBO
#include"VBO.h"

class VAO
{
	public:
		GLuint ID;
		VAO;

		void LinkVBO(VBO VBO, GLuint layout);
		void Bind();
		void Unbind();
		void Delete();
};

#endif