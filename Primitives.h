/*
 * Primitives.h
 *
 *  Created on: 9 нояб. 2020 г.
 *      Author: unyuu
 */

#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

// Задание:
// 1) Реализовать все остальные функции
// 2) Добавить генерацию текстурных координат
// 3) Нарисовать снеговика и ёлочку возле домика :)



// Из декартовой в цилиндрическую
void cart2cyl(
		double x, double y, double z,
		double &cr, double &cphi, double &cz);
// Из цилиндрической в декартову
void cyl2cart(
		double cr, double cphi, double cz,
		double &x, double &y, double &z);

// Из декартовой в сферическую
void cart2sph(
		double x, double y, double z,
		double &sr, double &sphi, double &stheta);
// Из сферической в декартову
void sph2cart(
		double sr, double sphi, double stheta,
		double &x, double &y, double &z);



void make_cylinder_flat(int sides); // на самом деле это призма
void make_cylinder_smooth(int sides);
void make_cone_flat(int sides); // на самом деле это пирамида, только тссссс~~~
void make_cone_smooth(int sides);
void make_sphere_flat(int rows, int cols); // сфера на основе глобуса
void make_sphere_smooth(int rows, int cols);
void make_icosphere_flat(int rows, int cols); // сфера на основе икосаэдра
void make_icosphere_smooth(int rows, int cols);


#endif /* PRIMITIVES_H_ */
