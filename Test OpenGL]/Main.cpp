
 
#include"OpenGLCommonHeaders.h"
#include <iostream>
#include <fstream>      // C++ file IO (secret: it's a wraper for the c IO)
#include <sstream>      // like a string builder

#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> 

#include <string>

#include "Shader.h"
#include "Camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
struct Vertices
{
	float x, y, z;
	float r, g, b;
};

struct VertexPlyFile
{
	float x;
	float y;
	float z;
	float nx, ny, nz;
	float r, g, b, a;
};

struct FacePlyFile
{
	unsigned int f0, f1, f2;
};



unsigned int numberOfVerticesInMesh;
unsigned int numberOfFacesInMesh;
unsigned int numberOfVerticesToDraw;
Vertices* finalAssetData=NULL;



//float vertices[] = {
//	// positions         // colors
// 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
//-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
// 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
//
//}; // triangle vertices


//float vertices[] = {
//		0.5f,  0.5f, 0.0f,  // top right
//		0.5f, -0.5f, 0.0f,  // bottom right
//	   -0.5f, -0.5f, 0.0f,  // bottom left
//	   -0.5f,  0.5f, 0.0f   // top left 
//	};//RECTANGLE vertices

//float vertices[] = {
//	// positions          // colors           // texture coords
//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
//}; //RECTANGLE vertices

//float vertices[] = {
//	// positions          // colors           // texture coords (note that we changed them to 'zoom in' on our texture image)
//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0, // bottom left
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0, 1.0f  // top left 
//};

float vertices[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

//float vertices[] = {
//	// positions          // colors           
//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    // top right
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    // bottom right
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,    // bottom left
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f    // top left 
//}; //RECTANGLE vertices

int width, height, nrChannels;
glm::vec3 cameraEye = glm::vec3(0, 0.0f, -0.5f);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = (float)width / 2.0;
float lastY = (float)height / 2.0;
float fov = 45.0f;

Camera camera(cameraPos);


float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;


void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
glm::vec3 colors[] = {
	glm::vec3(1.0f, 0.0f, 0.0f),  // Red
	glm::vec3(0.0f, 1.0f, 0.0f),  // Green
	glm::vec3(0.0f, 0.0f, 1.0f)   // Blue
};

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

unsigned int numberOfStripes = 4;
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

std::string assetFileToLoad;
void LoadMesh_XYZ(std:: string assetFile)
{
	/*if (assetFile.empty())
	{
		return;
	}*/
	std::ifstream fileToLoad("bun_zipper_res2_xyz.ply");
	if (!fileToLoad.is_open())
	{
		// file did not open
		return;
	}
	std::string readFile;
	while (fileToLoad >> readFile)
	{
		if (readFile=="vertex")
		{
			break;
		}
	}
	fileToLoad >> numberOfVerticesInMesh;
	while (fileToLoad >> readFile)
	{
		if (readFile == "face")
		{
			break;
		}
	}
	fileToLoad >> numberOfFacesInMesh;

	while (fileToLoad >> readFile)
	{
		if (readFile == "end_header")
		{
			break;
		}
	}

	VertexPlyFile* dataOfVerticesInMesh = new VertexPlyFile[numberOfVerticesInMesh];
	for (unsigned int i = 0; i != numberOfVerticesInMesh; i++)
	{
		VertexPlyFile temp;
		fileToLoad >> temp.x;
		fileToLoad >> temp.y;
		fileToLoad >> temp.z;

		dataOfVerticesInMesh[i] = temp;
	}

	FacePlyFile* dataOfFacesInMesh = new FacePlyFile[numberOfFacesInMesh];
	for (unsigned int i = 0; i < numberOfFacesInMesh; i++)
	{
		FacePlyFile temp;
		unsigned int discard;
		fileToLoad >> discard;  // "3" in the file 
		fileToLoad >> temp.f0;
		fileToLoad >> temp.f1;
		fileToLoad >> temp.f2;

		dataOfFacesInMesh[i] = temp;
	}

	numberOfVerticesToDraw = 3 * numberOfFacesInMesh;
	finalAssetData = new Vertices[numberOfVerticesToDraw];
	unsigned int vertexIndex = 0;

	/*for (unsigned int  i = 0; i != numberOfFacesInMesh; i++)
	{
		finalAssetData[vertexIndex + 0].x = dataOfVerticesInMesh[dataOfFacesInMesh[i].f0].x;
		finalAssetData[vertexIndex + 0].y = dataOfVerticesInMesh[dataOfFacesInMesh[i].f0].y;
		finalAssetData[vertexIndex + 0].z = dataOfVerticesInMesh[dataOfFacesInMesh[i].f0].z;	
		
		
		
		finalAssetData[vertexIndex + 0].r = 1.0f;
		finalAssetData[vertexIndex + 0].g = 1.0f;
		finalAssetData[vertexIndex + 0].b = 0.0f;
		
		finalAssetData[vertexIndex + 1].x = dataOfVerticesInMesh[dataOfFacesInMesh[i].f1].x;
		finalAssetData[vertexIndex + 1].y = dataOfVerticesInMesh[dataOfFacesInMesh[i].f1].y;
		finalAssetData[vertexIndex + 1].z = dataOfVerticesInMesh[dataOfFacesInMesh[i].f1].z;

		
		finalAssetData[vertexIndex + 1].r = 1.0f;
		finalAssetData[vertexIndex + 1].g = 1.0f;
		finalAssetData[vertexIndex + 1].b = 1.0f;


		finalAssetData[vertexIndex + 2].x = dataOfVerticesInMesh[dataOfFacesInMesh[i].f2].x;
		finalAssetData[vertexIndex + 2].y = dataOfVerticesInMesh[dataOfFacesInMesh[i].f2].y;
		finalAssetData[vertexIndex + 2].z = dataOfVerticesInMesh[dataOfFacesInMesh[i].f2].z;

		
		finalAssetData[vertexIndex + 2].r = 1.0f;
		finalAssetData[vertexIndex + 2].g = 1.0f;
		finalAssetData[vertexIndex + 2].b = 1.0f;


		vertexIndex += 3;
	}*/
	bool reverseStripes = true; // Set to true to reverse the stripe direction

	for (unsigned int i = 0; i != numberOfFacesInMesh; i++)
	{
		// Calculate the normalized vertical position of the vertices in the face
		float minY = std::min(dataOfVerticesInMesh[dataOfFacesInMesh[i].f0].y,
			std::min(dataOfVerticesInMesh[dataOfFacesInMesh[i].f1].y,
				dataOfVerticesInMesh[dataOfFacesInMesh[i].f2].y));
		float maxY = std::max(dataOfVerticesInMesh[dataOfFacesInMesh[i].f0].y,
			std::max(dataOfVerticesInMesh[dataOfFacesInMesh[i].f1].y,
				dataOfVerticesInMesh[dataOfFacesInMesh[i].f2].y));
		float normalizedY = (maxY + minY) / 2.0f; // Use the average vertical position

		// Calculate the stripe index based on the normalized vertical position
		int stripeIndex = static_cast<int>((normalizedY + 1.0f) * 0.5f * numberOfStripes);

		// Use the stripe index to determine the color
		glm::vec3 currentColor = reverseStripes ? colors[numberOfStripes - stripeIndex - 1] : colors[stripeIndex];

		// Assign the color to the vertices in the face
		for (int j = 0; j < 3; j++)
		{
			
			if (j == 0)
			{
				finalAssetData[vertexIndex + j].x = dataOfVerticesInMesh[dataOfFacesInMesh[i].f0].x;
				finalAssetData[vertexIndex + j].y = dataOfVerticesInMesh[dataOfFacesInMesh[i].f0].y;
				finalAssetData[vertexIndex + j].z = dataOfVerticesInMesh[dataOfFacesInMesh[i].f0].z;
			}
			if (j==1)
			{
				finalAssetData[vertexIndex + j].x = dataOfVerticesInMesh[dataOfFacesInMesh[i].f1].x;
				finalAssetData[vertexIndex + j].y = dataOfVerticesInMesh[dataOfFacesInMesh[i].f1].y;
				finalAssetData[vertexIndex + j].z = dataOfVerticesInMesh[dataOfFacesInMesh[i].f1].z;
			}																				   
			if (j==2)
			{
				finalAssetData[vertexIndex + j].x = dataOfVerticesInMesh[dataOfFacesInMesh[i].f2].x;
				finalAssetData[vertexIndex + j].y = dataOfVerticesInMesh[dataOfFacesInMesh[i].f2].y;
				finalAssetData[vertexIndex + j].z = dataOfVerticesInMesh[dataOfFacesInMesh[i].f2].z;
			}



			

			finalAssetData[vertexIndex + j].r = currentColor.r;
			finalAssetData[vertexIndex + j].g = currentColor.g;
			finalAssetData[vertexIndex + j].b = currentColor.b;
		}

		vertexIndex += 3;
	}


}

// to process inputs of keyboards
void processInput(GLFWwindow* window)
{
	 float  CAMERA_MOVEMENT_SPEED = 2.5f*deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//if (glfwGetKey (window, GLFW_KEY_W) == GLFW_PRESS)
	//{
	//	cameraPos += CAMERA_MOVEMENT_SPEED*cameraFront;
	//}
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//{
	//	
	//	cameraPos -= CAMERA_MOVEMENT_SPEED*cameraFront;
	//}
	//if (glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
	//{
	//	cameraPos -= glm::normalize(glm::cross(cameraFront,cameraUp))*CAMERA_MOVEMENT_SPEED;
	//}
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//{
	//	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * CAMERA_MOVEMENT_SPEED;
	//}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, CAMERA_MOVEMENT_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{

		camera.ProcessKeyboard(BACKWARD, CAMERA_MOVEMENT_SPEED);

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, CAMERA_MOVEMENT_SPEED);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, CAMERA_MOVEMENT_SPEED);
	}

}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

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

	//float sensitivity = 0.1f; // change this value to your liking
	//xoffset *= sensitivity;
	//yoffset *= sensitivity;

	//yaw += xoffset;
	//pitch += yoffset;

	//// make sure that when pitch is out of bounds, screen doesn't get flipped
	//if (pitch > 89.0f)
	//	pitch = 89.0f;
	//if (pitch < -89.0f)
	//	pitch = -89.0f;

	//glm::vec3 front=glm::vec3(0.0f,0.0f,0.0f);
	//front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//front.y = sin(glm::radians(pitch));
	//front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//cameraFront = glm::normalize(front);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS)
	{
		camera.ProcessMouseMovement(xoffset, yoffset);
	}
	//camera.ProcessMouseMovement(xoffset,yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	/*fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;*/

	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
int main(void)
{

	if (!glfwInit())
	{
		// Initialization failed
		std::cout << "Initialization Failed";
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!window)
	{
		// Window or OpenGL context creation failed
		glfwTerminate();
	}
	glfwSetErrorCallback(error_callback);
	glfwMakeContextCurrent(window);
	
	 glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_HAND_CURSOR);


	//Loading GLAD here ...
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	//LoadMesh_XYZ(assetFileToLoad);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//unsigned int vertex_buffer;

	 float test = sizeof(vertices[0]);
	 std::cout << "size of vertices[0] : " << test << std::endl;
	//creating buffers in a location
	/*glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);*/
	//this buffer data would hold the rendering part

	

	//glBufferData(GL_ARRAY_BUFFER, number_of_bytes_in_array, finalAssetData, GL_STATIC_DRAW);

	//ShaderClass shaderProgram = ShaderClass("VertexShader.glsl.txt", "FragmentShader.glsl.txt");
	ShaderClass shaderProgram = ShaderClass("VertexShaderGraph.vert", "FragmentShader.frag");


	//Vertexshader compiling method
//	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//
//	//FragmentShader compiling method
//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	// combining both the shaders in a single Program
//	unsigned int shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	//Linking both shaders together in a single program
//	glLinkProgram(shaderProgram);
//
//	// deleting shader cuz this has been combined as a single program so 
//// not required to allocate an extra memory in GPU
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);

	//float vertices[] = {
	//	0.5f,  0.5f, 0.0f,  // top right
	//	0.5f, -0.5f, 0.0f,  // bottom right
	//   -0.5f, -0.5f, 0.0f,  // bottom left
	//   -0.5f,  0.5f, 0.0f   // top left 
	//};

	
	

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangl
		1, 2, 3   // second Triangle
	};

	
	unsigned int VBO, VAO/*,EBO*/;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	/*glGenBuffers(1, &EBO);*/
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	//position atrribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  5* sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color attribute
	/*glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);*/

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);


	unsigned int texture, texture2;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load("Images/wall.jpg", &width, &height, &nrChannels, 0);
	stbi_set_flip_vertically_on_load(true);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);


	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	 data = stbi_load("Images/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	shaderProgram.UseProgram();

	shaderProgram.SetInt("texture1", 0);
	shaderProgram.SetInt("texture2", 1);

 


	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		//glBindVertexArray(VAO);
		//glUseProgram(shaderProgram);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		

		
		
		shaderProgram.UseProgram();


		
		glm::mat4 model = glm::mat4(1.0f);

		// transform = glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f));
		 //transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model,(float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		glm::mat4 view = glm::mat4(1.0f);
		// note that we're translating the scene in the reverse direction of where we want to move
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		float radius = 10.0f;
		float camX = static_cast<float>(sin(glfwGetTime()) * radius);
		float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
		glm::mat4 projection;
		//view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
		//shaderProgram.SetInt("Texture1", 0);
		//shaderProgram.SetInt("Texture2", 1);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
	
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);*/
		//glBindVertexArray(VAO);
		
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			float angle = 20.0f * i;
			glm::vec3 rotationAngle;
			if (i % 3 == 0)
			{
				
				rotationAngle = glm::vec3(1.0f, 0.0f, 0.0f);
				//model = glm::rotate(model, glm::radians(angle), rotationAngle);
			}
			else
			{
				rotationAngle = glm::vec3(1.0f, 0.3f, 0.5f);
			}
			angle = glfwGetTime() * 25.0f;
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(angle), rotationAngle);
			shaderProgram.SetMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//unsigned int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
		
		//shaderProgram.SetMat4("model", model);
		shaderProgram.SetMat4("view", view);
		shaderProgram.SetMat4("projection", projection);
	
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	
	//    while (!glfwWindowShouldClose(window))
//    {
//		processInput(window);
//		float ratio;
//		int width, height;
//		//        mat4x4 m, p, mvp;
//		glm::mat4 m, p, v, mvp;
//
//		glfwGetFramebufferSize(window, &width, &height);
//		ratio = width / (float)height;
//		glViewport(0, 0, width, height);
//		glClear(GL_COLOR_BUFFER_BIT /*| GL_DEPTH_BUFFER_BIT*/);
//
//		// While drawing a pixel, see if the pixel that's already there is closer or not?
//		//glEnable(GL_DEPTH_TEST);
//
//		//         mat4x4_identity(m);
//		m = glm::mat4(1.0f);
////
////		//mat4x4_rotate_Z(m, m, (float) glfwGetTime());
//////        glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f),
//////                                        -0.5f, // (float)glfwGetTime(),
//////                                        glm::vec3(0.0f, 0.0, 1.0f));
////
//		
////
////		////        yaxisRotation += 0.01f;
////		////        yaxisRotation += ( (2.0 * 3.1415) * deltaTime );
////
//		glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f),
//			yaxisRotation, // (float)glfwGetTime(),
//			glm::vec3(0.0f, 1.0, 0.0f));
////
////
////		//        m = m * rotateZ;
//		m = m * rotateY;
////		//        m = m * rotateZ;
////
////				//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//		p = glm::perspective(0.6f,
//			ratio,
//			0.1f,
//			1000.0f);
////
//		v = glm::mat4(1.0f);
////
////		//        glm::vec3 cameraEye = glm::vec3(0.0, 0.0, -4.0f);
//		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//		glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
////
////		//        cameraEye.z += 0.001f;
////
//		v = glm::lookAt(cameraEye,
//			cameraTarget,
//			upVector);
////
//		//mat4x4_mul(mvp, p, m);
//		mvp = p * v * m;
//
//		glUseProgram(shaderProgram);
//		
//		//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
//		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
//
//		     //   glPolygonMode(GL_FRONT_AND_BACK, GL_POINT /*GL_LINE*/ /*GL_FILL*/);
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL /*GL_LINE*/ /*GL_FILL*/);
//		        glPointSize(10.0f);
//
//		glDrawArrays(GL_TRIANGLES, 0, numberOfVerticesToDraw);
//		
//		//glClearColor(1.0f, 0.0f, 0.0f, 0.1f);
//		
//		
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
	glfwTerminate();
	
	
}