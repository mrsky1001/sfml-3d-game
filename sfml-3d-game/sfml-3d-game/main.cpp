#include <SFML/Graphics.hpp>
#include "view.h"
#include <SFML/OpenGL.hpp>
using namespace sf; // подключаем пространство имён sf

int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(200, 200), "SFML Works!");
	Clock clock;
	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				window.close(); // тогда закрываем его
		}
		// Установка цвета фона
		window.clear(Color(250, 220, 100, 0));

		// Создаём фигуру: круг радиусом 50
		CircleShape circle(50.f);

		// Закрашиваем наш круг 
		circle.setFillColor(Color(230, 0, 230));

		// Отрисовка круга
		window.draw(circle);

		// Отрисовка окна
		window.display();

		viewmap(time);//функция скроллинга карты, передаем ей время sfml
		changeview();//прикалываемся с камерой вида
		window.setView(view);//"оживляем" камеру в окне sfml
		window.clear();
	}

	return 0;
}