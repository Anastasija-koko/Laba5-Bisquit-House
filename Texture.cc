/*
 * Texture.cc
 *
 *  Created on: 9 но€б. 2020 г.
 *      Author: unyuu
 */

#include "Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <stdexcept>

Texture::Texture(const char * filename)
{
	glGenTextures(1, &_texture); // генерируем "им€" дл€ новой текстуры

	auto surf = std::shared_ptr<SDL_Surface>(
			IMG_Load(filename),
			SDL_FreeSurface);
	if (surf == nullptr)
		throw std::runtime_error(
				std::string("Ќе удалось загрузить текстуру: ") +
				std::string(SDL_GetError()));

	auto tex_surf = std::shared_ptr<SDL_Surface>(
			SDL_CreateRGBSurfaceWithFormat(
					0, surf->w, surf->h, 32, SDL_PIXELFORMAT_ABGR8888),
			SDL_FreeSurface);
	if (tex_surf == nullptr)
		throw std::runtime_error(
				std::string("Ќе удалось создать временную текстуру: ") +
				std::string(SDL_GetError()));

	SDL_BlitSurface(surf.get(), nullptr, tex_surf.get(), nullptr);

	glBindTexture(GL_TEXTURE_2D, _texture); // прив€зываем им€ нашей текстуры к цели GL_TEXTURE_2D
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex_surf->w, tex_surf->h,
			GL_RGBA, GL_UNSIGNED_BYTE, tex_surf->pixels);
	// Ќастройка правил масштабировани€ текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Ќастройка правил замощени€
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_texture); // удал€ем текстуру с указанным "именем"
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _texture); // прив€зываем им€ нашей текстуры к цели GL_TEXTURE_2D
}
