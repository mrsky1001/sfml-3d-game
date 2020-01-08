#include <SFML/Graphics.hpp>
#include "view.h"
#include <SFML/OpenGL.hpp>
using namespace sf; // ���������� ������������ ��� sf

int main()
{
	// ������, �������, ����������, �������� ������� ����� ����������
	RenderWindow window(VideoMode(200, 200), "SFML Works!");
	Clock clock;
	// ������� ���� ����������: �����������, ���� ������� ����
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		// ������������ ������� ������� � �����
		Event event;
		while (window.pollEvent(event))
		{
			// ������������ ����� �� �������� � ����� ������� ����?
			if (event.type == Event::Closed)
				window.close(); // ����� ��������� ���
		}
		// ��������� ����� ����
		window.clear(Color(250, 220, 100, 0));

		// ������ ������: ���� �������� 50
		CircleShape circle(50.f);

		// ����������� ��� ���� 
		circle.setFillColor(Color(230, 0, 230));

		// ��������� �����
		window.draw(circle);

		// ��������� ����
		window.display();

		viewmap(time);//������� ���������� �����, �������� �� ����� sfml
		changeview();//������������� � ������� ����
		window.setView(view);//"��������" ������ � ���� sfml
		window.clear();
	}

	return 0;
}