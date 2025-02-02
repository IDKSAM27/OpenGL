// This is file is purely for understanding and study purpose, this code has nothing to do with the Main file 
// or this project


#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Shaders scene, no need to understand yet, maybe you can simply copy paste this code in gpt to know more,
// Basically I'm building my own shaders scene
// * : pointer, it stores the memory address of another variable, it "points to" the location of the value in the memory	
// Vertex Shader Source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// Fragment Shader Source code 
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
	// Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);	//GLuint: opengl version of unsigned integer
	//  Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);	//arg:	reference value, no. of string usage for shader, source code, NULL
	// The GPU does not understand the source code, so we have to compile it into machine code right now
	glCompileShader(vertexShader);


	// Exact same thing for the Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);	//GLuint: opengl version of unsigned integer
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);	//arg:	reference value, no. of string usage for shader, source code, NULL
	// The GPU does not understand the source code, so we have to compile it into machine code right now
	glCompileShader(fragmentShader);

	// In order to actually use these shaders, we'll have to wrap them up into shader program
	// Create Shader Program Object and get its reference	
	GLuint shaderProgram = glCreateProgram();
	// Attack the Vertex and Fragment Shaders to shaderProgram
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link or wrap all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the shaders after linking them to shaderProgram
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// You may think why not use normal float, but this float and GLfloat are different
	// https://www.khronos.org/opengl/wiki/OpenGL_Type visit this site to know more about OpenGL data types
	// Vertices coordinates
	GLfloat vertices[] =
	{
		 -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	// Lower Left corner
		 0.5, -0.5f * float(sqrt(3)) / 3, 0.0f,	// Lower Right corner
		 0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		 -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		 0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	// These Indices tells us the corners of the 3 triangles and the order in which is should be displayed
	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};


	// Create reference containers for the Vertex Array Object and the Vertex Buffer 
	GLuint VAO, VBO, EBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);	//VAO should be mentioned before VBO, the chronology is very important
	glGenBuffers(1, &VBO);	//args: no. of objects i.e., 1 here, reference
	glGenBuffers(1, &EBO);
	// Types of buffer: https://www.khronos.org/opengl/wiki/Buffer_Object

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	//args: type of buffer we want to use, reference

	// Now lets actually store the vertices in the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// args: type of buffer, total size of the data in bytes, actual data, use of the data(static: means it will created once and used many times, dynamic: means the vertices will modified multiple times
	// DRAW, READ, COPY where Draw: means that the vertices will be modified and be used to draw an image on the screen
	// OpenGL does'nt know where to find the vertices, to do that we make use of another object i.e., vertex array object(VAO): THIS SOURCE POINTERS TO ONE OR MORE VBO's and tells opengl how to interpret them

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Now find the VAO and configure so that opengl knows how to find and read VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// args: position of the vertex attribute, how many values we have per vertex i.e., we have 3 floats, the value we have, integer value?: no so GL_FALSE, stride of the other vertices i.e., the amt of data btw each vertex, offset
	// In order to use the above, we have to enable
	glEnableVertexAttribArray(0);

	// This step is not mandatory, but it's a good practise to have 
	// We bind VAO and VBO 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it, there two types of buffer - back and front
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);


	// Main while loop
	while (!glfwWindowShouldClose(window)) {	// While loop used to avoid the window termination until we say it to close.
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Activate the shaderProgram, tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle

		//glDrawArrays(GL_TRIANGLES, 0, 3);	//args: type of primitive we want to use, starting index of vertices, amount of vertices we want to draw

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);	// args: primitive, no. of indices, data type, index of the indices

		// Lastly swap the buffer so that the image gets updated at each frame
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}


	// Delete all the objects we'll created so far
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window); // The window will close when compiled and runned, to avoid this use while loop.
	glfwTerminate();

	return 0;
}