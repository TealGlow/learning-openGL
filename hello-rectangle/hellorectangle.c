/* Name: Alyssa Comstock
 * Language: C
 * Description: Program that utilizes openGL, GLFW, and GLAD
 * to create a window and render a simple triangle.
 * This is done while learning openGL using the resources and 
 * textbook provided at: https://learnopengl.com/. 
 * A majority of the code will be based on that but adapted 
 * for the C instead of C++
 * */



#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void user_input(GLFWwindow * window);


// GLSL shader programs
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";



const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";



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
	
	// send up shaders etc here
	// 1. vertex shader
	// set up vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// send in the vertexShaderSouce that we set up earlier
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// compile he shader
	glCompileShader(vertexShader);
	// check if shader compiled successfully
	int success;
	char infoLog[512];
	// notes from: https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glGetShaderiv.xml
	// glGetShaderiv(shader, pname, params)
	// shader = shader object to be queried
	// pname = object parameter
	// params = returns request object param, so based on pname
	// GL_COMPILE_STATUS = true if compile on shader was successful
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		// if the vertex shader did not compile successfully
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		fprintf(stderr, "Error with shader vertex - compliation failed\n%s\n", infoLog);
	}

	// 2. fragment shader - calclate the final color of all the pixels in the matrix
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check to see if there was an error compiling the fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		fprintf(stderr, "Error with shader fragment - compliation failed\n%s\n", infoLog);
	}

	// 3. link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		fprintf(stderr, "Error with shader program linking - compliation failed\n%s\n", infoLog);
	}

	// clean up
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 4. set up vertex data, x,y,z
	float vertices[] = {
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left

	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	
	// buffer and vertex array
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind array
	glBindVertexArray(VAO);

	// copy our vertices array in buffer for openGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// target, size, data, useage
	// GL_STATIC_DRAW = data store contents will be modified once and used
	// many times and the contents are modified by the app and used as the
	// source for GL drawing
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	// set the vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unbind
	glBindVertexArray(0);

	// runtime, render loop
	while(!glfwWindowShouldClose(window)){
		// while the window is open
		user_input(window);
		// this is where rending happens in the loop
		
		// setting the background color to a nice teal color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		// rec rendering
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// drawing 2 triangles
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// clean up buffers, and shader program
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

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


