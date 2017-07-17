#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>
#include <time.h>
#include "Shader.hpp"
#include "Camera.h"
#include "stb_image.h"

GLfloat deltaTime = 0.0f;	// time between current frame and last frame
GLfloat lastFrame = 0.0f;

const GLuint WIDTH = 800, HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0f;
GLfloat lastY = HEIGHT / 2.0f;
bool firstMouse = true;

const char *vertexShaderSource = "shader.vs";

const char *fragmentShaderSource = "shader.fs";

const char *lightsourceShaderSource = "lightsource.fs";

//lighting stuff
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

int main() {

	float something = 0.0f, other = 0.0f;
	
	//initialize glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create window and make sure that it was created successfully
	GLFWwindow *window = glfwCreateWindow(800, 600, "Test2", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed to create window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	//make window 
	glfwMakeContextCurrent(window);


	//initialize glew
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "failed to run glew" << std::endl;

		return EXIT_FAILURE;
	}

	//create view for window
	glViewport(0, 0, 800, 600);

	//add function to adjust size of view when resizing window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//create your vertex shader and compile
	Shader ourShader(vertexShaderSource, fragmentShaderSource);
	Shader lampShader("lightsource.vs", lightsourceShaderSource);

	glEnable(GL_DEPTH_TEST);

	//each point in the square
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
	};

	float lampvertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};
	//the indices of each triangle that wil make the square
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	GLuint VBO, VAO, lightVAO, lightVBO;
	//create vertex arrays
	glGenVertexArrays(1, &VAO);

	//create buffer
	glGenBuffers(1, &VBO);

	//bind the buffer and add the coorespinding data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glBindVertexArray(VAO);

	//this lets the shader know how to interperate the data from the vertices array.
	//set the first three floats in each row to layout = 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//set floats 4-6 in each row to layout = 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &lightVBO);

	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lampvertices), lampvertices, GL_STATIC_DRAW);
	//create vao for light source
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);


	//this lets the shader know how to interperate the data from the vertices array.
	//set the first three floats in each row to layout = 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//set floats 4-6 in each row to layout = 1


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//initialize texture
	GLuint texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	//set texture to flip when it repeats.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//set how you want texture to load when zoomed out/in
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load image
	GLint width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("container2.png", &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data) {
		//if successful, generate texture and generate mipmap
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load image" << std::endl;
	}

	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//set texture to flip when it repeats.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//set how you want texture to load when zoomed out/in
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("container2_specular.png", &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data) {
		//if successful, generate texture and generate mipmap
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load image" << std::endl;
	}

	stbi_image_free(data);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
					 // either set it manually like so:
	//ourShader.setInt("texture1", 0);
	// or set it via the texture class
	//ourShader.setInt("texture2", 1);

	ourShader.setVec3("material.ambient", glm::vec3(0.2f, 0.1f, 0.31f));
	ourShader.setInt("material.diffuse", 0);
	ourShader.setInt("material.specular", 1);
	ourShader.setFloat("material.shininess", 64.0f);
	ourShader.setVec3("light.direction", camera.Front);
	ourShader.setFloat("light.cutoff", glm::cos(glm::radians(12.5f)));
	ourShader.setFloat("light.constant", 1.0f);
	ourShader.setFloat("light.linear", 0.09f);
	ourShader.setFloat("light.quadratic", 0.032f);

	while (!glfwWindowShouldClose(window)) {

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		//set background color
		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();
		/*
		Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
		*/
		// directional light
		ourShader.setVec3("directional_light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		ourShader.setVec3("directional_light.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		ourShader.setVec3("directional_light.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		ourShader.setVec3("directional_light.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		// point light 1
		ourShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		ourShader.setVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		ourShader.setVec3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		ourShader.setVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		ourShader.setFloat("pointLights[0].constant", 1.0f);
		ourShader.setFloat("pointLights[0].linear", 0.09);
		ourShader.setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		ourShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		ourShader.setVec3("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		ourShader.setVec3("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		ourShader.setVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		ourShader.setFloat("pointLights[1].constant", 1.0f);
		ourShader.setFloat("pointLights[1].linear", 0.09);
		ourShader.setFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		ourShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		ourShader.setVec3("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		ourShader.setVec3("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		ourShader.setVec3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		ourShader.setFloat("pointLights[2].constant", 1.0f);
		ourShader.setFloat("pointLights[2].linear", 0.09);
		ourShader.setFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		ourShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		ourShader.setVec3("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		ourShader.setVec3("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		ourShader.setVec3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		ourShader.setFloat("pointLights[3].constant", 1.0f);
		ourShader.setFloat("pointLights[3].linear", 0.09);
		ourShader.setFloat("pointLights[3].quadratic", 0.032);
		// spotLight
		ourShader.setVec3("spotlight.position", camera.Position);
		ourShader.setVec3("spotlight.direction", camera.Front);
		ourShader.setVec3("spotlight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		ourShader.setVec3("spotlight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		ourShader.setVec3("spotlight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		ourShader.setFloat("spotLight.constant", 1.0f);
		ourShader.setFloat("spotlight.linear", 0.09);
		ourShader.setFloat("spotlight.quadratic", 0.032);
		ourShader.setFloat("spotlight.cutOff", glm::cos(glm::radians(12.5f)));
		ourShader.setFloat("spotlight.outerCutOff", glm::cos(glm::radians(15.0f)));


		//calculate green value for the image
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glm::mat4 trans;
		//trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::translate(trans, glm::vec3(0.3, -0.3, 0.0));
		//use the program we created 
		//glUniform4f(vertexColorLocation, 1.0f, greenValue, 0.0f, 1.0f);
		//bind texture for use

		glm::mat4 view;

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		ourShader.setMat4("projection", projection);

		view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);


		//bind the vertex array to VAO create before
		glBindVertexArray(VAO);
		//draw stuff according to your vertices and indices
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model;
			processInput(window);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;

			if (i % 2 == 1) {
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.3f, 0.5, 1.0f));
			}
			
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);
			ourShader.setMat4("inversemodel", glm::inverse(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glm::mat4 model;
		glBindVertexArray(0);
		glBindVertexArray(lightVAO);
		// be sure to activate shader when setting uniforms/drawing objects
		// also draw the lamp object
		lampShader.use();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);
		for (unsigned int i = 0; i < 4; i++)
		{
			model = glm::mat4();
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			lampShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glDrawArrays(GL_TRIANGLES, 0, 36);
	
		//swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//delete and terminate everything before closing the app
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}
