/* ----------------   PROYECTO --------------------------*/
/*-----------------    2020-2   ---------------------------*/
/*------------- Alumno:  JAIME GARCIA FRANCISO
						SANCHEZ ESCOBAR FERNANDO
						SANCHEZ DÍAZ MARÍA BEATRIZ
---------------*/
#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>

#include "camera.h"
#include "Model.h"
//#include "Texture.h"

// Other Libs
#include "SOIL2/SOIL2.h"

void resize(GLFWwindow* window, int width, int height);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
//GLuint skyboxVBO, skyboxVAO;
GLuint VBO, VAO, EBO;
GLuint pastoVBO, pastoVAO, pastoEBO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX = 0.0f,
lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, 3.0f);
glm::vec3 lightDirection(0.0f, -1.0f, 0.0f);

void myData(void);
void myData2(void);
void display(Shader, Model, Model, Model, Model);
void getResolution(void);
void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);

//Texture
unsigned int t_dado,
			t_pasto;

//For model
bool animacion = false;
float movAuto_z = 0.0f;
bool avanza = true;


unsigned int generateTextures(const char* filename, bool alfa)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void LoadTextures()
{
	glActiveTexture(GL_TEXTURE2);
	t_dado = generateTextures("Texturas/casatextura.jpg", 0);
	t_pasto = generateTextures("Texturas/pasto.jpg", 0);


}

void myData()
{
	float vertices[] = {
		// positions		//Normals			// texture coords
		// Frontal								// S		T	
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 0.589f, 0.365f, //V0 -> top right
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 0.589f, 0.665f, //V1 -> bottom right 
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 0.389f, 0.665f, //V2 -> bottom left
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, -1.0f, 0.389f, 0.365f, //V3 -> top left


		// Derecha
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.787f, 0.665f, //V5 -> top right
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.787f, 0.365f, //V4 -> bottom right
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.589f, 0.365f, //V1 -> bottom left
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.589f, 0.365f, //V0 -> top left

		// Trasera
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.589f, 0.365f, //V6 -> bottom right
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.787f, 0.365f, //V4 -> bottom left
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.787f, 0.665f, //V5 -> top left
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.984f, 0.365f, //V7 -> top right

		// Izquierda
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.192f, 0.365f, //V6 -> bottom left
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	0.389f, 0.365f, //V2 -> bottom right
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	0.389f, 0.665f, //V3 -> top right
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.192f, 0.665f, //V7 -> top left

		// Inferior - y negativo
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	0.389f, 0.365f, //V2 -> top left   
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	0.589f, 0.365f, //V1 -> top right
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.589f, 0.173f, //V4 -> bottom right
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.389f, 0.173f, //V6 -> bottom left

		//Superior - y positivo
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	0.389f, 0.665f, //V3 ->	bottom left
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	0.589f, 0.665f, //V0 -> bottom right 
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.589f, 0.857f, //V5 -> top right
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.389f, 0.857f //V7 -> top left
	};

	unsigned int indices[] = {
		//Frontal
		0, 1, 3, //3
		1, 2, 3, //6
		//right
		4, 5, 6, //9
		6, 7, 4, //12
		// Trasera
		8, 9, 10, //15
		10, 11, 8, //18
		// Izquierda
		12, 13, 14, //21
		14, 15, 12, //24
		// Inferior
		16, 17, 18, //27
		18, 19, 16, //30
		// Superior
		20, 21, 22, //33
		22, 23, 20 //36
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void myData2()
{
	float vertices[] = {
		// positions		//Normals			// texture coords
		// Frontal								// S		T	
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 10.0f, 10.0f, //V0 -> top right
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 2.0f, 0.0f, //V1 -> bottom right 
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 0.0f, 0.0f, //V2 -> bottom left
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, -1.0f, 00.0f, 10.0f, //V3 -> top left


		// Derecha
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 10.0f, 10.0f, //V5 -> top right
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 2.0f, 0.0f, //V4 -> bottom right
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, //V1 -> bottom left
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 10.0f, //V0 -> top left

		// Trasera
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	10.0f, 10.0f, //V6 -> bottom right
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	2.0f, 10.0f, //V4 -> bottom left
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.0f, 0.0f, //V5 -> top left
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.0f, 10.0f, //V7 -> top right

		// Izquierda
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	10.0f, 10.0f, //V6 -> bottom left
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	2.0f, 10.0f, //V2 -> bottom right
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	0.0f, 0.0f, //V3 -> top right
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.0f, 10.0f, //V7 -> top left

		// Inferior - y negativo
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	10.0f, 10.0f, //V2 -> top left   
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	2.0f, 10.0f, //V1 -> top right
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.0f, 0.0f, //V4 -> bottom right
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.0f, 10.0f, //V6 -> bottom left

		//Superior - y positivo
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	10.0f, 10.0f, //V3 ->	bottom left
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	2.0f, 10.0f, //V0 -> bottom right 
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 0.0f, //V5 -> top right
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 10.0f, //V7 -> top left
	};

	unsigned int indices[] = {
		//Frontal
		0, 1, 3, //3
		1, 2, 3, //6
		//right
		4, 5, 6, //9
		6, 7, 4, //12
		// Trasera
		8, 9, 10, //15
		10, 11, 8, //18
		// Izquierda
		12, 13, 14, //21
		14, 15, 12, //24
		// Inferior
		16, 17, 18, //27
		18, 19, 16, //30
		// Superior
		20, 21, 22, //33
		22, 23, 20 //36
	};

	glGenVertexArrays(1, &pastoVAO);
	glGenBuffers(1, &pastoVBO);
	glGenBuffers(1, &pastoEBO);

	glBindVertexArray(pastoVAO);

	glBindBuffer(GL_ARRAY_BUFFER, pastoVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pastoEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void animate(void)
{
	if (animacion)
	{
		movAuto_z += 0.03f;

		printf("Posicion %f \n", movAuto_z);
	}
}

void display(Shader shader, Model modelo, Model llantas, Model piso, Model danny_phantom)
{
	shader.use();

	//Setup Advanced Lights
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("dirLight.direction", lightDirection);
	shader.setVec3("dirLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	shader.setVec3("pointLight[0].position", lightPosition);
	shader.setVec3("pointLight[0].ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("pointLight[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("pointLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[0].constant", 1.0f);
	shader.setFloat("pointLight[0].linear", 0.009f);
	shader.setFloat("pointLight[0].quadratic", 0.032f);

	shader.setVec3("pointLight[1].position", glm::vec3(0.0, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setFloat("pointLight[1].constant", 1.0f);
	shader.setFloat("pointLight[1].linear", 0.009f);
	shader.setFloat("pointLight[1].quadratic", 0.032f);

	shader.setFloat("material_shininess", 32.0f);

	// create transformations and Projection
	glm::mat4 tmp = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();

	// pass them to the shaders
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("projection", projection);

	//PASTO
	glBindVertexArray(pastoVAO);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(70.0f, 0.01f, 90.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_pasto); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);


	//CASAS
	glBindVertexArray(VAO);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f,1.5f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 2.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 0.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_dado); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 1.5f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 2.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_dado); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	

	glBindVertexArray(0);

	//DANNY PHANTOM
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.05f, -1.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	shader.setMat4("model", model);
	danny_phantom.Draw(shader);


	//CARRO
	model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	tmp = model = glm::translate(model, glm::vec3(15.0f, 0.0f, movAuto_z));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	//model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	shader.setMat4("model", model);
	modelo.Draw(shader);

	model = glm::translate(tmp, glm::vec3(0.85f, 0.25f, 1.29f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	shader.setMat4("model", model);
	llantas.Draw(shader);	//Izq delantera

	model = glm::translate(tmp, glm::vec3(-0.85f, 0.25f, 1.29f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	llantas.Draw(shader);	//Der delantera

	model = glm::translate(tmp, glm::vec3(-0.85f, 0.25f, -1.45f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	llantas.Draw(shader);	//Der trasera

	model = glm::translate(tmp, glm::vec3(0.85f, 0.25f, -1.45f));
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	shader.setMat4("model", model);
	llantas.Draw(shader);	//Izq trase


}

int main()
{

	glfwInit();


#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 9", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	LoadTextures();
	myData();
	myData2();
	glEnable(GL_DEPTH_TEST);

	//For Models
	Shader modelShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");

	//Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	// Load model
	Model ourModel = ((char *)"Models/Lambo/carroseria.obj");
	Model llantasModel = ((char *)"Models/Lambo/Wheel.obj");
	Model pisoModel = ((char *)"Models/piso/piso.obj");
	Model danny_phantomModel = ((char *)"Models/danny_phantom/Danny.obj");

	
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		//my_input(window);
		animate();

		// render
		// Backgound color
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//display(modelShader, ourModel, llantasModel);
		display(modelShader, ourModel, llantasModel, pisoModel, danny_phantomModel);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &pastoVAO);
	glDeleteBuffers(1, &pastoVBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		lightPosition.z -= 0.5f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		lightPosition.z += 0.5f;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		animacion = true;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}