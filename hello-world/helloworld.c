#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//void framebuffer_size_callback(GLFWWindow* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0,0,width,height);
}

void user_input(GLFWwindow * window){
 	// if the user hits the esc key the window will cloaw
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, 1);
	}

}


int main(){

	
	// init GLFW
	glfwInit();

	// a lot of glfw init stuff
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create the window object
	GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if(window == NULL){
		// failed to create window
		glfwTerminate();
		fprintf(stderr, "Failed to create glfw window\n");
		exit(1);
	}

	// create the window and handle the window size
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//let glad set all GL pointers
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		fprintf(stderr, "Failed to init GLAD\n");
		exit(1);
	}
	
	// runtime
	while(!glfwWindowShouldClose(window)){
		// while the window is open
		user_input(window);
		// this is where rending happens in the loop

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// clean up
	glfwTerminate();

	return 0;
}



