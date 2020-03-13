// GLEW ����� ���������� �� GLFW.
// GLEW
//#define GLEW_STATIC glew32s.lib
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

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
	int widthW = 1336, heightW = 800;
	GLFWwindow* window = glfwCreateWindow(widthW, heightW, "sfml-3d-cube", nullptr, nullptr);
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

	cout << "Start engine..." << endl;
	// ������� ����
	while (!glfwWindowShouldClose(window))
	{
		// ��������� ������� � �������� ������� ��������� ������.
		glfwPollEvents();

		// ������� ��������� �����


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// ������ ������ �������
		glfwSwapBuffers(window);
	}

	cout << "Shutdown..." << endl;
	glfwTerminate();
	return 0;
}