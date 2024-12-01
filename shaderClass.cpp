#include"shaderClass.h"

// File Reader function
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Shader constructor: initialize objects of a class
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// First get the strings from the shader text files
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Then convert and store them into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create a value aka a reference to store our vertex shader
	// Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);	//GLuint: opengl version of unsigned integer
	//  Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);	//arg:	reference value, no. of string usage for shader, source code, NULL
	// The GPU does not understand the source code, so we have to compile it into machine code right now
	glCompileShader(vertexShader);


	// Exact same thing for the Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	//GLuint: opengl version of unsigned integer
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);	//arg:	reference value, no. of string usage for shader, source code, NULL
	// The GPU does not understand the source code, so we have to compile it into machine code right now
	glCompileShader(fragmentShader);

	// In order to actually use these shaders, we'll have to wrap them up into shader program
	// Create Shader Program Object and get its reference	
	ID = glCreateProgram();
	// Attack the Vertex and Fragment Shaders to shaderProgram
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Link or wrap all the shaders together into the Shader Program
	glLinkProgram(ID);

	// Delete the shaders after linking them to shaderProgram
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}
