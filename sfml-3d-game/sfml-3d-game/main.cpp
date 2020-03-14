// GLEW ����� ���������� �� GLFW.
// GLEW
//#define GLEW_STATIC glew32s.lib
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
using namespace std;
using namespace sf;

const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// ����� ������������ �������� ESC, �� ������������� �������� WindowShouldClose � true, 
	// � ���������� ����� ����� ���������
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	//������������� GLFW
	cout << "Initialize GLFW..." << endl;
	glfwInit();

	cout << "Settings GLFW..." << endl;
	//��������� GLFW
	//�������� ����������� ��������� ������ OpenGL. 
	//�������� 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//��������� �������� ��� �������� ��������� ��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//���������� ����������� ��������� ������� ����
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	cout << "Creating GLFW window..." << endl;
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "sfml-3d-cube", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	cout << "Initialize GLEW..." << endl;
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	cout << "Setting Viewport..." << endl;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	cout << "Initialize shaders..." << endl;
	GLfloat vertices[] = {
	 0.5f,  0.5f, 0.0f,  // ������� ������ ����
	 0.5f, -0.5f, 0.0f,  // ������ ������ ����
	-0.5f, -0.5f, 0.0f,  // ������ ����� ����
	-0.5f,  0.5f, 0.0f   // ������� ����� ����
	};

	GLuint indices[] = {  // �������, ��� �� �������� � 0!
		0, 1, 3,   // ������ �����������
		1, 2, 3    // ������ �����������
	};

	GLuint EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	GLuint VAO;	
	glGenVertexArrays(1, &VAO);
	
	// 1. ����������� VAO
	glBindVertexArray(VAO);
	// 2. �������� ���� ������� � ����� ��� OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. �������� ���� ������� � � ����� ��� OpenGL
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 3. ������������� ��������� �� ��������� ��������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// 4. ���������� VAO (�� EBO)
	glBindVertexArray(0);


	Shader vertexShaderSource;
	if (!vertexShaderSource.loadFromFile("vertex_shader.vert", sf::Shader::Vertex))
	{
		// error...
	}
	vertexShaderSource.
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &((GLcharh)vertexShaderSource), NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	if (!success)
	{
		glGetProgramInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::SHADERPROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	cout << "Start engine..." << endl;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 5. ������������ ������
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		someOpenGLFunctionThatDrawsOurTriangle();
		glBindVertexArray(0);
		
		q	glfwSwapBuffers(window);
	}

	cout << "Shutdown..." << endl;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glfwTerminate();
	return 0;
}