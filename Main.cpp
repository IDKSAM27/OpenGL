#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Shaders scene, no need to understand yet, maybe you can simply copy paste this code in gpt to know more,
// Basically I'm building my own shaders scene
// * : pointer, it stores the memory address of another variable, it "points to" the location of the value in the memory	
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPosz, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() {

	// We'll create a window, will use GLFW to do same
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we're using version 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Mention that we'll be using core profile, i.e., use only modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //the opengl profile we want to use
	
	// You may think why not use normal float, but this float and GLfloat are different
	// https://www.khronos.org/opengl/wiki/OpenGL_Type visit this site to know more about OpenGL data types
	GLfloat vertices[] =
	{
		 0.5f, 0.5f * float(sqrt(3)) / 3, 0.0f,	// Left corner
		 0.4f, 0.5f * float(sqrt(3)) / 3, 0.0f,	// Right corner
		 0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Top corner
	};
	// All OpenGL objects are accessed by a reference

	// Create GLFWwindow obj
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);	//HEIGHT, WIDTH, NAME, FULLSCREEN?, NOT IMP
	// Error Handling, if the window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;

		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD
	gladLoadGL(); //load the needed configuration for opengl

	// Specify the viewport of OpenGL in the window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);
		

	// Create a value aka a reference to store our vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);	//GLuint: opengl version of unsigned integer
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);	//arg:	reference value, no. of string usage for shader, source code, NULL
	// The GPU does not understand the source code, so we have to compile it into machine code right now
	glCompileShader(vertexShader);

	// Exact same thing for the Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	//GLuint: opengl version of unsigned integer
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);	//arg:	reference value, no. of string usage for shader, source code, NULL
	// The GPU does not understand the source code, so we have to compile it into machine code right now
	glCompileShader(fragmentShader);

	// In order to actually use these shaders, we'll have to wrap them up into shader program
	GLuint shaderProgram = glCreateProgram();
	// Attack shaders to shaderProgram
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link or wrap the shader programs
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	GLuint VBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);




	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it, there two types of buffer - back and front
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window)) {	// While loop used to avoid the window termination until we say it to close.
		// Take care of all GLFW events
		glfwPollEvents();
	}

	glfwDestroyWindow(window); // The window will close when compiled and runned, to avoid this use while loop.
	glfwTerminate();

	return 0;
}