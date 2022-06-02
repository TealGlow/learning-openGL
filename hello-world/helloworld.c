/* Name: Alyssa Comstock
 * Language: C
 * Description: Program that utilizes openGL, GLFW, and GLAD
 * to create a window and render. This is done while learning
 * openGL using the resources and textbook provided at 
 * https://learnopengl.com/.  A majority of the code will
 * be based on that but adapted for the C instead of C++
 * */



#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void user_input(GLFWwindow * window);



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
		
		// setting the background color to a nice teal color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// clean up
	glfwTerminate();

	return 0;
}



/* framebuffer_size_callback
 * function that sets the opengl viewport if the window
 * size changes
 *
 * @param: window: window struct object
 * @param: width: width of the window
 * @param: height: height of the window
 * */
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width,height);
}



/* user_input
 * function that handles when the user hits the enter key
 * this is checked every single frame.  When the user
 * hits escape the window is set to close.
 *
 * @param: window: window struct object
 * */
void user_input(GLFWwindow * window){
 	// if the user hits the esc key the window will cloaw
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		// set should close to true
		glfwSetWindowShouldClose(window, 1);
	}

}


