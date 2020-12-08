/*
 * GLDemoWindow.cc
 *
 *  Created on: 7 но€б. 2020 г.
 *      Author: unyuu
 */

#include <cmath>
#include "GLDemoWindow.h"

#include "Primitives.h"

static constexpr double Pi = acos(-1.);

static VertexVector s_house_vertices {
	{  2.0, 2.0, 0.0 },
	{  2.0, 2.0, 2.0 },
	{  2.0, 0.0, 4.0 },
	{  2.0, -2.0, 2.0 },
	{  2.0, -2.0, 0.0 },
	{  -2.0, 2.0, 2.0 },
	{  -2.0, 2.0, 0.0 },
	{  -2.0, 0.0, 4.0 },
	{  -2.0, -2.0, 2.0 },
	{  -2.0, -2.0, 0.0 },
};

static FaceVector s_house_faces {
	{ 5, 4, 3, 2, 1, 0 },
	{ 5, 9, 8, 7, 5, 6 },
	{ 4, 0, 1, 5, 6 },
	{ 4, 4, 3, 8, 9 },
	{ 4, 1, 2, 7, 5 },
	{ 4, 3, 2, 7, 8 }
};

static NormalVector s_house_normals {
	{  1.0, 0.0, 0.0 },
	{  -1.0, 0.0, 0.0 },
	{  0.0, 1.0, 0.0 },
	{  0.0, -1.0, 0.0 },
	{  0.0, 1.0, 0.5 },
	{  0.0, -1.0, 0.5 },
};
static ColorVector s_house_colors {
	{  1.0f, 1.0f, 0.9f },
	{  0.9f, 0.9f, 1.0f },
	{  0.9f, 1.0f, 1.0f },
	{  1.0f, 0.9f, 0.9f },
	{  1.0f, 0.9f, 1.0f },
	{  1.0f, 1.0f, 0.9f },
};

static TexCoordVector s_house_tex_coords {
	{  { 0.50, 1.00 }, { 0.50, 0.50 }, { 0.75, 0.00 }, { 1.00, 0.50 }, { 1.00, 1.00 } },
	{  { 0.50, 1.00 }, { 0.50, 0.50 }, { 0.75, 0.00 }, { 1.00, 0.50 }, { 1.00, 1.00 } },
	{  { 0.00, 1.00 }, { 0.00, 0.50 }, { 0.50, 0.50 }, { 0.50, 1.00 } },
	{  { 0.00, 1.00 }, { 0.00, 0.50 }, { 0.50, 0.50 }, { 0.50, 1.00 } },
	{  { 0.00, 0.50 }, { 0.00, 0.00 }, { 0.50, 0.00 }, { 0.50, 0.50 } },
	{  { 0.00, 0.50 }, { 0.00, 0.00 }, { 0.50, 0.00 }, { 0.50, 0.50 } },
};


Model House { s_house_vertices, s_house_faces, s_house_normals, s_house_colors, s_house_tex_coords };

void draw_cristmas_tree(int n)
{
	ColorVector tree_colors{
		{0.99f, 0.43f, 0.97f}
	};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &tree_colors[0][0]);
	make_cone_smooth(20);
	for (int i = 0; i < n; ++i){
		glScaled(0.7, 0.7, 0.7);
		glTranslated(0.0, 0.0, 1.1);
		make_cone_smooth(16);
	}
}
void draw_color_snowman()
{
	ColorVector snowman_colors {
			{  0.71f, 0.00f, 0.94f },
			{  0.94f, 0.87f, 0.0f },
			{  0.95f, 1.00f, 0.37f },
			{  1.0f, 0.1f, 0.0f },
		};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &snowman_colors[0][0]);
	make_sphere_smooth(20,20);
	for (int i = 0; i < 2; ++i){
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &snowman_colors[i+1][0]);
			glScaled(0.7, 0.7, 0.7);
			glTranslated(0.0, 0.0, 2.0);
			make_sphere_smooth(20,20);
		}
	glScaled(0.5, 0.5, 0.5);
	glTranslated(0.0, -3.0, -3.0);
	make_sphere_smooth(20,20);

	glTranslated(0.0, 6.0, 0.0);
	make_sphere_smooth(20,20);

	glTranslated(2.7, -3.0, 3.0);
	glRotated(90, 0.0, 1.0, 0.0);
	glScaled(0.3, 0.3, 0.8);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &snowman_colors[3][0]);
	make_cone_smooth(10);
}

GLDemoWindow::GLDemoWindow(int width, int height)
: Window(width, height), _crate_texture("house.png")
{
	SDL_GL_SetSwapInterval(1); // VSync
//	SDL_GL_SetSwapInterval(0); // Ќемедленна€ отрисовка

	_turn_angle = 0.;
	_tilt_phase = 0.;
}

void GLDemoWindow::setup()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE);

	glClearColor(0.3f, 0.46f, 1.0f, 1.f);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, double(width()) / double(height()), 0.01, 30.0);
	glMatrixMode(GL_MODELVIEW);

//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
//	glFrontFace(GL_CW);
}

void GLDemoWindow::render()
{
	double house_x = 0.0, house_y = 0.0, house_z = 0.0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity(); // Identity matrix - единична€ матрица

	gluLookAt(4.0, 5.0, 2.0, 0.0, 0.0, 0.5, 0.0, 0.0, 4.0);

	glPushMatrix();

	_crate_texture.bind();
	glEnable(GL_TEXTURE_2D);
	glRotated(-10.0, 0.0, 0.0, 1.0);
	glTranslated(house_x, house_y, house_z);
	glScaled(0.7, 0.7, 0.7);
	draw_model(House);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glPushMatrix();
	glTranslated(house_x + 2.5, house_y + 1.0, house_z);
	glScaled(0.7, 0.7, 0.7);
	draw_cristmas_tree(3);

	glPopMatrix();
	glPushMatrix();
	glTranslated(house_x - 2.5, house_y + 1.2, house_z);
	glScaled(0.7, 0.7, 0.7);
	draw_cristmas_tree(5);

	glPopMatrix();
	glPushMatrix();

	glTranslated(house_x + 1.7, house_y + 1.5, house_z);
	glRotated(60.0, 0.0, 0.0, 1.0);
	glScaled(0.2, 0.2, 0.2);
	draw_color_snowman();
	glPopMatrix();
	glPushMatrix();
	glTranslated(house_x - 1.7, house_y + 1.5, house_z);
	glRotated(60.0, 0.0, 0.0, 1.0);
	glScaled(0.15, 0.15, 0.15);
	draw_color_snowman();


}

void GLDemoWindow::draw_model(Model &model)
{
	for (unsigned i = 0; i < model.faces.size(); ++i) {
		int count = model.faces[i][0];
		if (count == 3)
			glBegin(GL_TRIANGLES);
		else if (count == 4)
			glBegin(GL_QUADS);
		else
			glBegin(GL_POLYGON);

		glNormal3dv(&model.normals[i][0]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &model.colors[i][0]);
		for (int j = 1; j <= count; ++j) {
			glTexCoord2dv(&model.tex_coords[i][j-1][0]);
			glVertex3dv(&model.vertices[model.faces[i][j]][0]);
		}

		glEnd();
	}
}

void GLDemoWindow::do_logic()
{
	_turn_angle += 2.;
	if (_turn_angle >= 30.)
		_turn_angle -= 360.;

	_tilt_phase += Pi / 20.;
	if (_tilt_phase >= Pi * 2.)
		_tilt_phase -= Pi * 2.;
}


