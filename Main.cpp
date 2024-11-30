#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {

	//we'll create a window, will use GLFW to do same
	//we'll iniate glfw
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //the opengl profile we want to use
	
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);	//HEIGHT, WIDTH, NAME, FULLSCREEN?, NOT IMP
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;

		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL(); //load the needed configuration for opengl

	glViewport(0, 0, 800, 800);
		
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) {	//while loop used to avoid the window termination until we say it to close.
		glfwPollEvents();
	}

	glfwDestroyWindow(window); //the window will close when compiled and runned, to avoid this use while loop.
	glfwTerminate();

	return 0;
}