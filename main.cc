/*
 * main.cc
 *
 *  Created on: 7 нояб. 2020 г.
 *      Author: unyuu
 */

/*
 	 Список библиотек:
 	 Для Windows / MinGW:
 	 mingw32
 	 SDL2main
 	 SDL2
 	 SDL2_image
 	 opengl32
 	 glu32
 	 В остальных ОС (кроме Android, где SDL2main тоже нужен):
 	 SDL2
 	 SDL2_image
 	 GL
 	 GLU
 	 OpenGL - Open Graphics Language / Graphics Library
 	 SGI IRIS - Interactive Raster Imaging System
 	 IRIS GL -> OpenGL
 	 Текущая версия - 4.6
 	 "Старые" версии - 1.x - 2.x    - умеют рисовать сами
 	 "Новые"  версии - 3.x - 4.6    - VBO/VAO + шейдеры, сам OpenGL почти ничем не занят :)
 */

#include <iostream>
#include <stdexcept>
#include <SDL2/SDL.h>

#include "GLDemoWindow.h"

int main(int, char **)
{
	SDL_Init(SDL_INIT_EVERYTHING); // Инициализируем SDL, куда же мы без него~~

	try {
		GLDemoWindow w;

		w.main_loop();

	} catch (const std::exception &e) {
		std::cerr << "При выполнении программы произошла ошибка:"
				<< std::endl
				<< e.what()
				<< std::endl;
		return 1;
	} catch (...) {
		std::cerr << "При выполнении программы произошла неизвестная ошибка!"
				<< std::endl;
		return 1;
	}

	return 0;
}

