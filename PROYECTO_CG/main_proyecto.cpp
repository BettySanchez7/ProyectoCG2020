/* ----------------   PROYECTO --------------------------*/
/*-----------------    2020-2   ---------------------------*/
/*------------- Alumno: JAIME GARCIA FRANCISO
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
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f;
GLFWmonitor *monitors;
//GLuint skyboxVBO, skyboxVAO;
GLuint VBO, VAO, EBO;
GLuint pastoVBO, pastoVAO, pastoEBO;
GLuint EBOrampa, VAOrampa, VBOrampa;

//Camera
Camera camera(glm::vec3(0.0f, 2.0f, 0.0f)); //0 0 3

double	lastX = 0.0f,
lastY = 0.0f;
bool firstMouse = true;
bool luz = false;

//Timing
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, 3.0f);
glm::vec3 lightDirection(0.0f, -10.0f, 0.0f);

void casas(void);
void planos(void);
void display(Shader, Model, Model, Model, Model);
void getResolution(void);
void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);


//Animacion Eva
float   movTorso_x = 0.0f,
movTorso_z = 0.0f,
movTorso_y = 0.0f,
dirTorso = 0.0f;

bool	road1 = true,
road2 = false,
road3 = false,
descenso = false,
reproducir = false;


//Texture
unsigned int t_dado,
			t_pasto,
			t_edificio,
			t_edificio21,
			t_edificio22,
			t_edificio23,
			t_piso1,
			t_torrel1,
			t_torrel2,
			t_torrel3,
			t_edificio3,
			t_carretera,
			t_carretera2,
			t_blanco,
			t_iglesia1,
			t_iglesia2,
			t_edificio5,
			t_edificio7_1,
			t_edificio7_2,
			t_edificio7_3,
			t_edificio8,
			t_edificio9,
			t_edificio10,
			t_edificio11,
			t_edificio12,
			t_sky;

//For model

//COCHE EN LA RAMPA
bool	animacion = false,
animacion2 = false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false,
recorrido5 = false;
float movAuto_z = 0.0f, 
	movAuto_y=0.0f, 
	movAuto_x=0.0f, i=0.0, 
	orienta = 0.0f;
bool avanza = true;


//CARRITO DE HOTDOGS
float	movHotDog_x = 28.0f,
movHotDog_y = 0.05f,
movHotDog_z = 0.0f,
orientaHotDog = 0.0f,
grados_circulo = 10.0f;
bool	animacionHotDog = false,
recorrido1HotDog = true,
recorrido2HotDog = false,
recorrido3HotDog = false,
recorrido4HotDog = false,
recorrido5HotDog = false;

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
	t_pasto = generateTextures("Texturas/pasto.jpg", 0);
	t_edificio = generateTextures("Texturas/edificio1.jpg", 0);
	t_edificio21 = generateTextures("Texturas/edificio2_1.jpg", 0);
	t_edificio22 = generateTextures("Texturas/edificio2_2.jpg", 0);
	t_edificio23 = generateTextures("Texturas/edificio2_3.jpg", 0);
	t_piso1 = generateTextures("Texturas/gris2.jpg", 0);
	t_torrel1= generateTextures("Texturas/Partebajotorre.jpg", 0);
	t_torrel2= generateTextures("Texturas/Parteenmediotorre.jpg", 0);
	t_torrel3= generateTextures("Texturas/Partearribatorre.jpg", 0);
	t_edificio3= generateTextures("Texturas/edificio3.jpg", 0);
	t_carretera = generateTextures("Texturas/carretera.jpg", 0);
	t_carretera2 = generateTextures("Texturas/carretera2.jpg", 0);
	t_blanco = generateTextures("Texturas/blanco.jpg", 0);
	t_iglesia1= generateTextures("Texturas/iglesia1.jpg", 0);
	t_iglesia2 = generateTextures("Texturas/iglesia1_2.jpg", 0);
	t_edificio5 = generateTextures("Texturas/edificio5.jpg", 0);
	t_edificio7_1 = generateTextures("Texturas/edificio7_1.jpg", 0);
	t_edificio7_2= generateTextures("Texturas/edificio7_2.jpg", 0);
	t_edificio7_3= generateTextures("Texturas/edificio7_3.jpg", 0);
	t_edificio8 = generateTextures("Texturas/edificio8.jpg", 0);
	t_edificio9 = generateTextures("Texturas/edificio9.jpg", 0);
	t_edificio10= generateTextures("Texturas/edificio10.jpg", 0);
	t_edificio11= generateTextures("Texturas/edificio11.jpg", 0);
	t_edificio12 = generateTextures("Texturas/edificio12.jpg", 0);
	t_sky= generateTextures("Texturas/skybox.png", 0);
}
void casas2()
{
	float vertices[] = {
		// positions		//Normals			// texture coords
		// Frontal								// S		T	
		0.2f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 0.5f, 0.5f, //V0 -> top right
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 0.5f, 0.75f, //V1 -> bottom right 
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 0.25f, 0.75f, //V2 -> bottom left
	   -0.2f,  0.5f,  0.5f,  0.0f,  0.0f, -1.0f, 0.25f, 0.5f, //V3 -> top left

		// Derecha
		0.2f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.75f, 0.5f, //V5 -> top right
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.75f, 0.75f, //V4 -> bottom right
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.5f,  0.75f, //V1 -> bottom left
		0.2f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.5f,  0.5f, //V0 -> top left

		// Trasera
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 0.75f, //V6 -> bottom right
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.75f, 0.75f, //V4 -> bottom left
		 0.2f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.75f, 0.5f, //V5 -> top left
		-0.2f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 0.5f, //V7 -> top right

		// Izquierda
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.75f,  0.75f, //V6 -> bottom left
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 0.75f, //V2 -> bottom right
		-0.2f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 0.5f, //V3 -> top right
		-0.2f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.75f,  0.5f, //V7 -> top left

		// Inferior - y negativo
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	0.25f, 0.75f, //V2 -> top left   
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	0.5f, 0.75f, //V1 -> top right
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.5f, 1.0f, //V4 -> bottom right
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.25f, 1.0f, //V6 -> bottom left

		//Superior - y positivo
		-0.2f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	0.25f, 0.5f, //V3 ->	bottom left
		 0.2f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	0.5f, 0.5f, //V0 -> bottom right 
		 0.2f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.5f, 0.25f, //V5 -> top right
		-0.2f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.25f, 0.25f //V7 -> top left

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

	glGenVertexArrays(1, &VAOrampa);
	glGenBuffers(1, &VBOrampa);
	glGenBuffers(1, &EBOrampa);

	glBindVertexArray(VAOrampa);

	glBindBuffer(GL_ARRAY_BUFFER, VBOrampa);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOrampa);
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
void casas()
{
	float vertices[] = {
		// positions		//Normals			// texture coords
		// Frontal								// S		T	
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 0.5f, 0.5f, //V0 -> top right
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 0.5f, 0.75f, //V1 -> bottom right 
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f, 0.25f, 0.75f, //V2 -> bottom left
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, -1.0f, 0.25f, 0.5f, //V3 -> top left

		// Derecha
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.75f, 0.5f, //V5 -> top right
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.75f, 0.75f, //V4 -> bottom right
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.5f,  0.75f, //V1 -> bottom left
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.5f,  0.5f, //V0 -> top left

		// Trasera
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 0.75f, //V6 -> bottom right
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.75f, 0.75f, //V4 -> bottom left
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.75f, 0.5f, //V5 -> top left
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 0.5f, //V7 -> top right

		// Izquierda
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.75f,  0.75f, //V6 -> bottom left
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 0.75f, //V2 -> bottom right
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 0.5f, //V3 -> top right
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.75f,  0.5f, //V7 -> top left

		// Inferior - y negativo
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	0.25f, 0.75f, //V2 -> top left   
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	0.5f, 0.75f, //V1 -> top right
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.5f, 1.0f, //V4 -> bottom right
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.25f, 1.0f, //V6 -> bottom left

		//Superior - y positivo
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	0.25f, 0.5f, //V3 ->	bottom left
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	0.5f, 0.5f, //V0 -> bottom right 
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.5f, 0.25f, //V5 -> top right
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.25f, 0.25f //V7 -> top left

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

void planos()
{
	float vertices[] = {

		//BASE
		-0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 0.0f, //V3 ->	bottom left
		 0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,	10.0f, 0.0f, //V0 -> bottom right 
		 0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,	10.0f, 5.0f, //V5 -> top right
		-0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 5.0f, //V7 -> top left

		//CARRETERA
		- 0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 0.0f, //V3 ->	bottom left
		 0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 0.0f, //V0 -> bottom right 
		 0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 10.0f, //V5 -> top right
		-0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 10.0f ,//V7 -> top left

		- 0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 0.0f, //V3 ->	bottom left
		 0.5f,  0.0f,  0.5f,  0.0f,  1.0f,  0.0f,	10.0f, 0.0f, //V0 -> bottom right 
		 0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,	10.0f, 1.0f, //V5 -> top right
		-0.5f,  0.0f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 1.0f, //V7 -> top left
		
		//PASILLOS ALAMEDA
		   22.0f,  0.0f,  20.0f,  0.0f,  1.0f,  0.0f,	0.0f, 0.0f, //V3 ->	bottom left
		  24.0f,  0.0f,  20.0f, 0.0f,  1.0f,  0.0f,	  10.0f, 0.0f, //V0 -> bottom right 
		  -24.0f,  0.0f, -20.0f,  0.0f,  1.0f,  0.0f,	10.0f, 5.0f, //V5 -> top right
		 -26.0f,  0.0f, -20.0f, 0.0f,  1.0f,  0.0f,	0.0f, 5.0f, //V7 -> top left

		 -26.0f,  0.0f,  20.0f,  0.0f,  1.0f,  0.0f,	0.0f, 0.0f, //V3 ->	bottom left
		 -24.0f,  0.0f,  20.0f, 0.0f,  1.0f,  0.0f,	  10.0f, 0.0f, //V0 -> bottom right 
		  26.0f,  0.0f,  -20.0f,  0.0f,  1.0f,  0.0f,	10.0f, 5.0f, //V5 -> top right
		 24.0f,  0.0f,  -20.0f,  1.0f,  0.0f,	0.0f, 5.0f //V7 -> top left
	};

	unsigned int indices[] = {
		//PISO
		0, 1, 2, //3
		0, 2, 3, //6
		//CARRETERA
		4,5,6,//9
		4,6,7,//12

		8,9,10,//15
		8,10,11,//18
		
		12,13,14,//
		12,14,15,//

		16,17,18,
		16,18,19


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
	//Vehículo  14.0f, 2.0f, 6.0f
	if (animacion)
	{
		if (recorrido1)
		{
			movAuto_z += 1.0f;
			orienta = 0.0f;
			if (movAuto_z > 21.0f)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{
			movAuto_z += 0.5f;
			movAuto_y += 0.3f;
			orienta = -33.69;  
			if (movAuto_z > 28.0f && movAuto_y > 3.0f)
			{
				recorrido2 = false;
				recorrido3 = true;
			}
		}
		if (recorrido3)
		{
			movAuto_z += 1.0f;
			orienta = 0.0f;
			if (movAuto_z > 36.0f)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}

		if (recorrido4)
		{
			movAuto_z += 0.5f;
			movAuto_y -= 0.3f;
			orienta = 33.69;
			if (movAuto_z > 41.0f && movAuto_y < 0.8f)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}

		if (recorrido5)
		{
			movAuto_z += 1.0f;
			orienta = 0.0;
			if (movAuto_z > 52.0f)
			{
				recorrido5 = false;
				recorrido1 = false;
			}
		}
		

	}

	//Eva
	if (reproducir)
	{
		if (road1)
		{
			movTorso_x -= 0.3f;
			dirTorso = -90.0f;
			if (movTorso_x < -12.0f)
			{
				road1 = false;
				road2 = true;
			}
		}
		if (road2)
		{
			movTorso_z += 0.3f;
			dirTorso = 0.0f;
			if (movTorso_z > 22.0f)
			{
				road2 = false;
				road3 = true;
			}
		}
		if (road3)
		{
			movTorso_z -= 0.3f;
			movTorso_x += 0.162f;
			dirTorso = 118.61f;
			if (movTorso_z > 12.5f) {
				movTorso_y += 0.2f;
				descenso = true;
			}
			if (movTorso_z < 12.5f && descenso)
				movTorso_y -= 0.12f;
			if (movTorso_z < 0.0f)
			{
				road3 = false;
				road1 = false;
				descenso = false;
			}
		}
	}

}

void display(Shader shader, Model danny_phantom, Model mansionLego, Model legoHouse, Model legoHome, 
		Model legoEhouse, Model legoGas, Model legoArbol, Model legoTree, Model legoBanca, Model boteBasura,
		Model lampara, Model coche, Model kiosko, Model arbol2, Model perro, Model hotdogs, Model cuerpoEva, Model pierDerEva, Model pierIzqEva,
		Model braDerEva, Model braIzqEva, Model cabezaEva)
{
	shader.use();

	//Setup Advanced Lights


	//DIA
	//DIRECCIONAL
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("dirLight.direction", lightDirection);
	shader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));


	shader.setVec3("pointLight[0].position", glm::vec3(0.0, 4.0f, 0.0f));
	shader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[0].constant", 1.0f);
	shader.setFloat("pointLight[0].linear", 0.009f);
	shader.setFloat("pointLight[0].quadratic", 0.032f);


	shader.setVec3("pointLight[1].position", glm::vec3(-32.0f, 0.5f, -21.0f));
	shader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[1].constant", 1.0f);
	shader.setFloat("pointLight[1].linear", 0.009f);
	shader.setFloat("pointLight[1].quadratic", 0.042f);
	
	shader.setVec3("pointLight[2].position", glm::vec3(-32.0f, 0.5f, 21.0f));
	shader.setVec3("pointLight[2].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[2].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[2].constant", 1.0f);
	shader.setFloat("pointLight[2].linear", 0.009f);
	shader.setFloat("pointLight[2].quadratic", 0.042f);

	shader.setVec3("pointLight[3].position", glm::vec3(28.0f, 0.0f, 21.0f));
	shader.setVec3("pointLight[3].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[3].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[3].constant", 1.0f);
	shader.setFloat("pointLight[3].linear", 0.009f);
	shader.setFloat("pointLight[3].quadratic", 0.042f);

	shader.setVec3("pointLight[4].position", glm::vec3(28.0f, 0.0f, -21.0f));
	shader.setVec3("pointLight[4].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[4].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[4].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[4].constant", 1.0f);
	shader.setFloat("pointLight[4].linear", 0.009f);
	shader.setFloat("pointLight[4].quadratic", 0.042f);

	shader.setFloat("material_shininess", 32.0f);

	if (luz) {
		shader.setVec3("viewPos", camera.Position);
		shader.setVec3("dirLight.direction", lightDirection);
		shader.setVec3("dirLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		shader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));


		shader.setVec3("pointLight[0].position", glm::vec3(0.0, 4.0f, 0.0f));
		shader.setVec3("pointLight[0].ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("pointLight[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("pointLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setFloat("pointLight[0].constant", 1.0f);
		shader.setFloat("pointLight[0].linear", 0.009f);
		shader.setFloat("pointLight[0].quadratic", 0.032f);


		shader.setVec3("pointLight[1].position", glm::vec3(-32.0f, 0.5f, -21.0f));
		shader.setVec3("pointLight[1].ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("pointLight[1].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("pointLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setFloat("pointLight[1].constant", 1.0f);
		shader.setFloat("pointLight[1].linear", 0.009f);
		shader.setFloat("pointLight[1].quadratic", 0.042f);

		shader.setVec3("pointLight[2].position", glm::vec3(-32.0f, 0.5f, 21.0f));
		shader.setVec3("pointLight[2].ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("pointLight[2].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("pointLight[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setFloat("pointLight[2].constant", 1.0f);
		shader.setFloat("pointLight[2].linear", 0.009f);
		shader.setFloat("pointLight[2].quadratic", 0.042f);

		shader.setVec3("pointLight[3].position", glm::vec3(28.0f, 0.0f, 21.0f));
		shader.setVec3("pointLight[3].ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("pointLight[3].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("pointLight[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setFloat("pointLight[3].constant", 1.0f);
		shader.setFloat("pointLight[3].linear", 0.009f);
		shader.setFloat("pointLight[3].quadratic", 0.042f);

		shader.setVec3("pointLight[4].position", glm::vec3(28.0f, 0.0f, -21.0f));
		shader.setVec3("pointLight[4].ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("pointLight[4].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setVec3("pointLight[4].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.setFloat("pointLight[4].constant", 1.0f);
		shader.setFloat("pointLight[4].linear", 0.009f);
		shader.setFloat("pointLight[4].quadratic", 0.042f);

		shader.setFloat("material_shininess", 32.0f);
	}

	// create transformations and Projection
	glm::mat4 tmp = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f,300.0f);
	view = camera.GetViewMatrix();
	view = glm::translate(view, glm::vec3(movX, movY, movZ));

	// pass them to the shaders
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("projection", projection);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////								OBJETOS											///////////////////////////////////////////////////////////////////////
	
	//BASE
	glBindVertexArray(pastoVAO);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(104.0f, 0.0f, 72.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_piso1); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	//--------------ALAMEDA
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-11.0f, 0.01f, 0.0f));
	model = glm::scale(model, glm::vec3(82.0f, 0.0f, 44.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_blanco); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.03f, 0.0f));
	model = glm::scale(model, glm::vec3(60.0f, 0.0f, 40.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_pasto); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//PASILLOS
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.05f, 0.0f));
	model = glm::scale(model, glm::vec3(60.0f, 0.0f, 4.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_blanco); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.05f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0f, 0.0f, 44.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_blanco); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.05f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_blanco); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(float))); 

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.05f, 0.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 0.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_blanco); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(float)));

	//CARRETERA

	model = glm::translate(glm::mat4(1.0f), glm::vec3(34.0f, 0.02f, 0.0f));
	model = glm::scale(model, glm::vec3(8.0f, 0.01f, 72.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_carretera); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(float)));

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-49.0f, 0.02f, 0.0f));
	model = glm::scale(model, glm::vec3(8.0f, 0.01f, 72.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_carretera); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(float)));

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 0.02f, -25.0f));
	model = glm::scale(model, glm::vec3(76.0f, 0.01f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_carretera2); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(float)));

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 0.02f, 25.0f));
	model = glm::scale(model, glm::vec3(76.0f, 0.01f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_carretera2); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(float)));

	glBindVertexArray(0);


	
	glBindVertexArray(VAO);

	//base
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(200.0f, 150.0f, 150.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_sky); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//EDIF1
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.0f, 10.0f, -33.0f));
	model = glm::scale(model, glm::vec3(6.0f, 20.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	//EDIF2
	model = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 5.0f, -33.0f));
	model = glm::scale(model, glm::vec3(12.0f, 10.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio3); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//EDIF3
	model = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 3.0f, -33.0f));
	model = glm::scale(model, glm::vec3(16.0f, 6.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio7_2); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 16.0f, -33.0f));
	model = glm::scale(model, glm::vec3(10.0f, 20.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio7_1); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(14.0f, 13.5f, -33.0f));
	model = glm::scale(model, glm::vec3(2.0f, 15.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio7_3); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(26.0f, 13.5f, -33.0f));
	model = glm::scale(model, glm::vec3(2.0f, 15.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio7_3); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//EDIF4
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-30.0f, 7.5f, 33.0f));
	model = glm::scale(model, glm::vec3(8.0f, 15.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio21); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.0f, 12.5f, 33.0f));
	model = glm::scale(model, glm::vec3(12.0f, 5.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio22); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.0f, 5.0f, 33.0f));
	model = glm::scale(model, glm::vec3(2.0f, 10.0f, 3.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio23); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//EDIF5 TORRE LATINOAMERICANA
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 4.0f, 32.0f));
	model = glm::scale(model, glm::vec3(12.0f, 8.0f, 8.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_torrel1); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 10.0f, 32.0f));
	model = glm::scale(model, glm::vec3(11.0f, 4.0f, 7.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_torrel1); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 24.0f, 32.0f));
	model = glm::scale(model, glm::vec3(10.0f, 24.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_torrel2); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 37.0f, 32.0f));
	model = glm::scale(model, glm::vec3(9.0f, 2.0f, 5.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_torrel3); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 38.5f, 32.0f));
	model = glm::scale(model, glm::vec3(8.0f, 1.0f, 4.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_torrel2); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 39.5f, 32.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_torrel1); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 44.0f, 32.0f));
	model = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_torrel2); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//EDIFICIO 6
	model = glm::translate(glm::mat4(1.0f), glm::vec3(43.0f, 7.5f, 24.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 15.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_iglesia1); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(43.0f, 16.5f, 24.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_iglesia2); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//EDIFICIO 7
	model = glm::translate(glm::mat4(1.0f), glm::vec3(27.0f, 15.0f, 33.0f));
	model = glm::scale(model, glm::vec3(6.0f, 30.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio8); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//EDIFICIO 8
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0f, 15.0f, 34.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(12.0f, 30.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio9); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	//EDIFICIO 9
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 10.0f, -34.0f));
	model = glm::scale(model, glm::vec3(13.0f, 20.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio10); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//EDIFICIO 10
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 17.0f, 34.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(8.0f, 34.0f, 4.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio11); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//EDIFICIO 11
	model = glm::translate(glm::mat4(1.0f), glm::vec3(44.0f, 10.0f, -4.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10.0f, 20.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_edificio12); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	glBindVertexArray(VAOrampa);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 25.0f));
	model = glm::scale(model, glm::vec3(20.0f, 4.0f, 6.0f));
	shader.setMat4("model", model);
	shader.setVec3("aColor", 1.0f, 0.0f, 0.0f); //Aplicamos color
	glBindTexture(GL_TEXTURE_2D, t_carretera); //Aplicamos una textura
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//-----------------------------MODELOS--------------------------------------------
	//DANNY PHANTOM
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, -1.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	shader.setMat4("model", model);
	danny_phantom.Draw(shader);

	//Mansion -> Models/legoHouse/legoHouse.obj
	//46	
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.8f, 1.4f, 2.0f)); //24*6
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	mansionLego.Draw(shader);

	//Lego House -> Models/LegoHouseW/legoHouse.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 0.0f, 33.0f));
	model = glm::scale(model, glm::vec3(1.7f, 1.85f, 0.7f)); //16*4
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	legoHouse.Draw(shader);

	//Lego Home -> Models/legoHome/legoHome.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(44.0f, 0.0f, -19.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.5f, 2.5f, 2.0f)); //8*4
	shader.setMat4("model", model);
	legoHome.Draw(shader);

	//Lego E House -> Models/LegoEhouse/legoEhouse.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(44.0f, 0.0f, 10.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.2f, 2.0f, 1.5f)); //8*4
	shader.setMat4("model", model);
	legoEhouse.Draw(shader);

	//Lego Gas Station -> Models/LegoGas/legoGas.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-26.0f, -1.7f, -34.0f));
	model = glm::scale(model, glm::vec3(0.318f, 0.26f, 0.066f)); 
	shader.setMat4("model", model);
	legoGas.Draw(shader);

	//Arbol2 -> Models/LegoObjects/legoTree.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 0.0f, -3.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
			model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
			shader.setMat4("model", model);
			legoTree.Draw(shader);
	}
	model = glm::translate(glm::mat4(1.0f), glm::vec3(11.0f, 0.0f, -5.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(14.0f, 0.0f, -7.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(17.0f, 0.0f, -9.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(22.0f, 0.0f, -13.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);



	//Arbol2 -> Models/LegoObjects/legoTree.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, 0.0f, 3.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}
	model = glm::translate(glm::mat4(1.0f), glm::vec3(11.0f, 0.0f, 5.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(14.0f, 0.0f, 7.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(17.0f, 0.0f, 9.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(20.0f, 0.0f, 11.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(22.0f, 0.0f, 13.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	//Arbol2 -> Models/LegoObjects/legoTree.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 0.0f, -3.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-11.0f, 0.0f, -5.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-14.0f, 0.0f, -7.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.0f, 0.0f, -9.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-22.0f, 0.0f, -13.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);


	//Arbol2 -> Models/LegoObjects/legoTree.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-8.0f, 0.0f, 3.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-11.0f, 0.0f, 5.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-14.0f, 0.0f, 7.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-17.0f, 0.0f, 9.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-20.0f, 0.0f, 11.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-4.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		legoTree.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-22.0f, 0.0f, 13.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	legoTree.Draw(shader);

	//////
	
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 18.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 16.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 14.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 12.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 10.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 8.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	//////

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 18.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 16.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 14.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 12.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 10.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 8.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	//////

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -18.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -16.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -14.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -12.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -10.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -8.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	//////

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -18.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -16.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -14.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 3.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -12.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 2.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -10.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -8.0f));
	model = glm::scale(model, glm::vec3(1.5f, 2.5f, 1.5f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	for (int i = 0.0f; i < 1.0f; i++)
	{
		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		arbol2.Draw(shader);
	}
	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-28.0f, 0.0f, 1.8f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);

	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-18.0f, 0.0f, -1.8f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);

	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 1.8f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);


	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 1.8f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);

	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(16.0f, 0.0f, -1.8f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);

	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(22.0f, 0.0f, 1.8f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);


	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.0f, -8.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);

	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.8f, 0.0f, -13.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);

	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.0f, -18.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);
	
	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.0f, -8.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);

	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.8f, 0.0f, -13.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);

	//Banca -> Models/LegoObjects/legoBanca.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.0f, -18.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.55f, 0.5f));
	shader.setMat4("model", model);
	legoBanca.Draw(shader);


	//Lampara -> Models/LegoObjects/lampara.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-32.0f, 0.0f, -21.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.30f, 0.25f));
	shader.setMat4("model", model);
	lampara.Draw(shader);

	//Lampara -> Models/LegoObjects/lampara.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-32.0f, 0.0f, 21.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.25f));
	shader.setMat4("model", model);
	lampara.Draw(shader);

	//Lampara -> Models/LegoObjects/lampara.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(28.0f, 0.0f, 21.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.25f));
	shader.setMat4("model", model);
	lampara.Draw(shader);

	//Lampara -> Models/LegoObjects/lampara.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(28.0f, 0.0f, -21.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.25f));
	shader.setMat4("model", model);
	lampara.Draw(shader);

	//Bote de basura -> Models/LegoObjects/boteBasura.obj
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-4.0f, 0.0f, -10.0f));
	model = glm::scale(model, glm::vec3(0.1f, 0.07f, 0.1f));
	shader.setMat4("model", model);
	boteBasura.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	shader.setMat4("model", model);
	kiosko.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-25.0f + movAuto_x, movAuto_y, -32.0f + movAuto_z));
	model = glm::rotate(model, glm::radians(orienta), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
	shader.setMat4("model", model);
	coche.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(movHotDog_x, 0.05f, 0.0f + movHotDog_z));
	model = glm::rotate(model, glm::radians(orientaHotDog), glm::vec3(0.0f, 0.5f, 0.0f));
	model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
	shader.setMat4("model", model);
	hotdogs.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(orientaHotDog), glm::vec3(0.0f, 0.5f, 0.0f));
	model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
	shader.setMat4("model", model);
	perro.Draw(shader);


	//Eva 01
	model = glm::mat4(1.0f);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0 + movTorso_x, movTorso_y, movTorso_z));
	tmp = model = glm::rotate(model, glm::radians(dirTorso), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	cuerpoEva.Draw(shader);

	//Pierna Derecha
	model = glm::translate(tmp, glm::vec3(0.0f, 0.01f, 0.0f));
	shader.setMat4("model", model);
	pierDerEva.Draw(shader);

	//Pierna Izquierda
	model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	pierIzqEva.Draw(shader);

	//Brazo Derecho
	model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	braDerEva.Draw(shader);

	//Brazo Izquierdo
	model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	braIzqEva.Draw(shader);

	//Cabeza Eva
	model = glm::translate(tmp, glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	cabezaEva.Draw(shader);
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
	casas();
	planos();
	casas2();
	glEnable(GL_DEPTH_TEST);

	//For Models
	Shader modelShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");

	//Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	// Load model
	Model ourModel = ((char *)"Models/Lambo/carroseria.obj");
	Model llantasModel = ((char *)"Models/Lambo/Wheel.obj");
	Model danny_phantomModel = ((char *)"Models/danny_phantom/Danny.obj");
	Model mansionLego = ((char *)"Models/LegoHouse/legoHouse.obj");
	Model legoHouse = ((char *)"Models/LegoHouseW/legoHouse.obj");
	Model legoHome = ((char *)"Models/LegoHome/legoHome.obj");
	Model legoEhouse = ((char *)"Models/LegoEhouse/legoEhouse.obj");
	Model legoGas = ((char *)"Models/LegoGas/legoGas.obj");
	Model legoArbol = ((char *)"Models/LegoObjects/legoArbol.obj");
	Model legoTree = ((char *)"Models/LegoObjects/legoTree.obj");
	Model legoBanca = ((char *)"Models/LegoObjects/legoBanca.obj");
	Model boteBasura = ((char *)"Models/LegoObjects/boteBasura.obj");
	Model lampara = ((char *)"Models/LegoObjects/lampara.obj");
	Model coche = ((char *)"Models/carro1_lego/carro1_lego.obj");
	Model kiosko = ((char *)"Models/kiosko/kiosko.obj");
	Model arbol2 = ((char *)"Models/LegoObjects/arbol2.obj");
	Model perro = ((char *)"Models/perro/perro.obj");
	Model hotdogs = ((char *)"Models/hotdogs/carrito_hotdogs.obj");
	Model cuerpoEva = ((char *)"Models/legoEva/cuerpoEva.obj");
	Model pierDerEva = ((char *)"Models/legoEva/pierDerEva.obj");
	Model pierIzqEva = ((char *)"Models/legoEva/pierIzqEva.obj");
	Model braDerEva = ((char *)"Models/legoEva/braDerEva.obj");
	Model braIzqEva = ((char *)"Models/legoEva/braIzqEva.obj");
	Model cabezaEva = ((char *)"Models/legoEva/cabezaLego.obj");

	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 200.0f);
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

		//display(modelShader, ourMosdel, llantasModel);
		display(modelShader, danny_phantomModel, 
				mansionLego, legoHouse, legoHome, legoEhouse, legoGas, legoArbol, 
			legoTree, legoBanca, boteBasura, lampara, coche, kiosko, arbol2, perro, hotdogs, cuerpoEva, pierDerEva, 
			pierIzqEva, braDerEva, braIzqEva, cabezaEva);

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
	glDeleteVertexArrays(1, &VAOrampa);
	glDeleteBuffers(1, &VBOrampa);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		movX += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		movX -= 0.4f;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		movY += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		movY -= 0.4f;
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		movZ -= 0.4f;
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		movZ += 0.4f;


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

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		animacion = true;
		if (movAuto_z >= 50) {
			movAuto_z = 0.0f;
			recorrido1 = true;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		luz ^= true;

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		reproducir = true;

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