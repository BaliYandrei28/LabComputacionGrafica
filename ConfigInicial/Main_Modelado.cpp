//Previo 4 Modelado Geometrico
//Bali Martinez Yandrei Guillermo
//Fecha de entrega 13 de septiembre de 2026
//No. de cuenta: 423035470

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.3f;
float movZ = -11.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado geometrico", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers



	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Fondo azul cielo como la referencia
		glClearColor(0.60f, 0.72f, 0.82f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);


		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));


		glBindVertexArray(VAO);
		glDisableVertexAttribArray(1); // Desactiva el color por vertice para asignar colores personalizados por pieza

		// ==================== TORSO Y PANTALLA ====================
		// 1. Torso principal (Gris cuerpo)
		glVertexAttrib3f(1, 0.62f, 0.64f, 0.68f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.15f, 0.95f, 0.70f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 2. Pantalla marco exterior (Celeste claro)
		glVertexAttrib3f(1, 0.0f, 0.85f, 0.98f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.05f, 0.36f));
		model = glm::scale(model, glm::vec3(0.82f, 0.52f, 0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 3. Pantalla interior (Azul rey)
		glVertexAttrib3f(1, 0.0f, 0.18f, 0.85f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.05f, 0.39f));
		model = glm::scale(model, glm::vec3(0.68f, 0.38f, 0.04f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ==================== CUELLO Y CABEZA ====================
		// 4. Cuello (Gris oscuro)
		glVertexAttrib3f(1, 0.48f, 0.50f, 0.54f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.56f, 0.0f));
		model = glm::scale(model, glm::vec3(0.32f, 0.18f, 0.32f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 5. Cabeza bloque principal (Gris cuerpo)
		glVertexAttrib3f(1, 0.62f, 0.64f, 0.68f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.22f, 0.0f));
		model = glm::scale(model, glm::vec3(1.25f, 1.12f, 0.95f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 6. Ojo derecho (Celeste)
		glVertexAttrib3f(1, 0.0f, 0.88f, 0.98f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.28f, 1.30f, 0.49f));
		model = glm::scale(model, glm::vec3(0.18f, 0.18f, 0.06f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 7. Ojo izquierdo (Celeste)
		glVertexAttrib3f(1, 0.0f, 0.88f, 0.98f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.28f, 1.30f, 0.49f));
		model = glm::scale(model, glm::vec3(0.18f, 0.18f, 0.06f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 8. Oreja derecha (Celeste)
		glVertexAttrib3f(1, 0.0f, 0.85f, 0.95f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.68f, 1.22f, 0.0f));
		model = glm::scale(model, glm::vec3(0.14f, 0.68f, 0.58f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 9. Oreja izquierda (Celeste)
		glVertexAttrib3f(1, 0.0f, 0.85f, 0.95f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.68f, 1.22f, 0.0f));
		model = glm::scale(model, glm::vec3(0.14f, 0.68f, 0.58f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 10. Escalon cabeza superior 1 (Gris)
		glVertexAttrib3f(1, 0.58f, 0.60f, 0.64f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.84f, 0.0f));
		model = glm::scale(model, glm::vec3(0.92f, 0.14f, 0.76f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 11. Escalon cabeza superior 2 (Gris)
		glVertexAttrib3f(1, 0.54f, 0.56f, 0.60f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.97f, 0.0f));
		model = glm::scale(model, glm::vec3(0.62f, 0.14f, 0.52f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 12. Antena cubo superior (Cyan brillante)
		glVertexAttrib3f(1, 0.10f, 0.92f, 0.98f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.14f, 0.0f));
		model = glm::scale(model, glm::vec3(0.32f, 0.22f, 0.32f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ==================== BRAZO DERECHO (PANTALLA IZQUIERDA) ====================
		// 13. Conector horizontal al torso (Gris oscuro)
		glVertexAttrib3f(1, 0.45f, 0.47f, 0.50f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.67f, 0.25f, 0.0f));
		model = glm::scale(model, glm::vec3(0.20f, 0.16f, 0.20f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 14. Placa vertical de hombro (Gris claro)
		glVertexAttrib3f(1, 0.68f, 0.70f, 0.74f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.80f, 0.25f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.36f, 0.36f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 15. Biceps (Gris cuerpo)
		glVertexAttrib3f(1, 0.62f, 0.64f, 0.68f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.95f, 0.16f, 0.0f));
		model = glm::scale(model, glm::vec3(0.24f, 0.22f, 0.24f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 16. Reborde del codo (Gris claro)
		glVertexAttrib3f(1, 0.70f, 0.72f, 0.76f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.95f, 0.02f, 0.0f));
		model = glm::scale(model, glm::vec3(0.30f, 0.08f, 0.30f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 17. Antebrazo (Gris cuerpo)
		glVertexAttrib3f(1, 0.62f, 0.64f, 0.68f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.95f, -0.22f, 0.0f));
		model = glm::scale(model, glm::vec3(0.24f, 0.40f, 0.24f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 18. Muñequera sobresaliente (Gris claro)
		glVertexAttrib3f(1, 0.72f, 0.74f, 0.78f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.95f, -0.46f, 0.0f));
		model = glm::scale(model, glm::vec3(0.34f, 0.10f, 0.34f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 19. Conector muñeca (Gris oscuro)
		glVertexAttrib3f(1, 0.45f, 0.47f, 0.50f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.95f, -0.54f, 0.0f));
		model = glm::scale(model, glm::vec3(0.24f, 0.08f, 0.24f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 20. Base mano pinza (Negro carbón)
		glVertexAttrib3f(1, 0.18f, 0.18f, 0.20f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.95f, -0.64f, 0.0f));
		model = glm::scale(model, glm::vec3(0.42f, 0.12f, 0.26f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 21. Dedo exterior (Negro carbón)
		glVertexAttrib3f(1, 0.18f, 0.18f, 0.20f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.10f, -0.84f, 0.0f));
		model = glm::scale(model, glm::vec3(0.12f, 0.28f, 0.26f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 22. Dedo interior (Negro carbón)
		glVertexAttrib3f(1, 0.18f, 0.18f, 0.20f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.80f, -0.84f, 0.0f));
		model = glm::scale(model, glm::vec3(0.12f, 0.28f, 0.26f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ==================== BRAZO IZQUIERDO (PANTALLA DERECHA) ====================
		// 23. Conector horizontal al torso (Gris oscuro)
		glVertexAttrib3f(1, 0.45f, 0.47f, 0.50f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.67f, 0.25f, 0.0f));
		model = glm::scale(model, glm::vec3(0.20f, 0.16f, 0.20f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 24. Placa vertical de hombro (Gris claro)
		glVertexAttrib3f(1, 0.68f, 0.70f, 0.74f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.80f, 0.25f, 0.0f));
		model = glm::scale(model, glm::vec3(0.08f, 0.36f, 0.36f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 25. Biceps (Gris cuerpo)
		glVertexAttrib3f(1, 0.62f, 0.64f, 0.68f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.95f, 0.16f, 0.0f));
		model = glm::scale(model, glm::vec3(0.24f, 0.22f, 0.24f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 26. Reborde del codo (Gris claro)
		glVertexAttrib3f(1, 0.70f, 0.72f, 0.76f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.95f, 0.02f, 0.0f));
		model = glm::scale(model, glm::vec3(0.30f, 0.08f, 0.30f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 27. Antebrazo (Gris cuerpo)
		glVertexAttrib3f(1, 0.62f, 0.64f, 0.68f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.95f, -0.22f, 0.0f));
		model = glm::scale(model, glm::vec3(0.24f, 0.40f, 0.24f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 28. Muñequera sobresaliente (Gris claro)
		glVertexAttrib3f(1, 0.72f, 0.74f, 0.78f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.95f, -0.46f, 0.0f));
		model = glm::scale(model, glm::vec3(0.34f, 0.10f, 0.34f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 29. Conector muñeca (Gris oscuro)
		glVertexAttrib3f(1, 0.45f, 0.47f, 0.50f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.95f, -0.54f, 0.0f));
		model = glm::scale(model, glm::vec3(0.24f, 0.08f, 0.24f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 30. Base mano pinza (Negro carbón)
		glVertexAttrib3f(1, 0.18f, 0.18f, 0.20f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.95f, -0.64f, 0.0f));
		model = glm::scale(model, glm::vec3(0.42f, 0.12f, 0.26f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 31. Dedo interior (Negro carbón)
		glVertexAttrib3f(1, 0.18f, 0.18f, 0.20f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.80f, -0.84f, 0.0f));
		model = glm::scale(model, glm::vec3(0.12f, 0.28f, 0.26f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 32. Dedo exterior (Negro carbón)
		glVertexAttrib3f(1, 0.18f, 0.18f, 0.20f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.10f, -0.84f, 0.0f));
		model = glm::scale(model, glm::vec3(0.12f, 0.28f, 0.26f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ==================== CADERA Y PIERNAS COMPLETAS ====================
		// 33. Cintura / Cadera base (Gris cuerpo)
		glVertexAttrib3f(1, 0.62f, 0.64f, 0.68f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.62f, 0.0f));
		model = glm::scale(model, glm::vec3(1.25f, 0.30f, 0.72f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// --- PIERNA DERECHA (PANTALLA IZQUIERDA) ---
		// 34. Conector cadera a muslo (Gris oscuro)
		glVertexAttrib3f(1, 0.45f, 0.47f, 0.50f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.35f, -0.79f, 0.0f));
		model = glm::scale(model, glm::vec3(0.20f, 0.08f, 0.20f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 35. Muslo (Gris cuerpo)
		glVertexAttrib3f(1, 0.62f, 0.64f, 0.68f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.35f, -0.98f, 0.0f));
		model = glm::scale(model, glm::vec3(0.28f, 0.30f, 0.28f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 36. Rodilla escalon superior (Gris claro)
		glVertexAttrib3f(1, 0.72f, 0.74f, 0.78f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.35f, -1.17f, 0.0f));
		model = glm::scale(model, glm::vec3(0.48f, 0.08f, 0.48f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 37. Rodilla escalon inferior (Gris intermedio)
		glVertexAttrib3f(1, 0.58f, 0.60f, 0.64f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.35f, -1.25f, 0.0f));
		model = glm::scale(model, glm::vec3(0.52f, 0.08f, 0.52f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 38. Pantorrilla (Gris cuerpo)
		glVertexAttrib3f(1, 0.62f, 0.64f, 0.68f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.35f, -1.55f, 0.0f));
		model = glm::scale(model, glm::vec3(0.44f, 0.52f, 0.44f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 39. Pie (Negro carbón)
		glVertexAttrib3f(1, 0.18f, 0.18f, 0.20f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.35f, -1.90f, 0.07f));
		model = glm::scale(model, glm::vec3(0.50f, 0.20f, 0.64f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// --- PIERNA IZQUIERDA (PANTALLA DERECHA) ---
		// 40. Conector cadera a muslo (Gris oscuro)
		glVertexAttrib3f(1, 0.45f, 0.47f, 0.50f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.35f, -0.79f, 0.0f));
		model = glm::scale(model, glm::vec3(0.20f, 0.08f, 0.20f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 41. Muslo (Gris cuerpo)
		glVertexAttrib3f(1, 0.62f, 0.64f, 0.68f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.35f, -0.98f, 0.0f));
		model = glm::scale(model, glm::vec3(0.28f, 0.30f, 0.28f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 42. Rodilla escalon superior (Gris claro)
		glVertexAttrib3f(1, 0.72f, 0.74f, 0.78f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.35f, -1.17f, 0.0f));
		model = glm::scale(model, glm::vec3(0.48f, 0.08f, 0.48f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 43. Rodilla escalon inferior (Gris intermedio)
		glVertexAttrib3f(1, 0.58f, 0.60f, 0.64f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.35f, -1.25f, 0.0f));
		model = glm::scale(model, glm::vec3(0.52f, 0.08f, 0.52f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 44. Pantorrilla (Gris cuerpo)
		glVertexAttrib3f(1, 0.62f, 0.64f, 0.68f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.35f, -1.55f, 0.0f));
		model = glm::scale(model, glm::vec3(0.44f, 0.52f, 0.44f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 45. Pie (Negro carbón)
		glVertexAttrib3f(1, 0.18f, 0.18f, 0.20f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.35f, -1.90f, 0.07f));
		model = glm::scale(model, glm::vec3(0.50f, 0.20f, 0.64f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glEnableVertexAttribArray(1); // Restaura el estado original
		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.4f;
}