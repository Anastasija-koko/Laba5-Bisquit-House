/*
 * Texture.h
 *
 *  Created on: 9 но€б. 2020 г.
 *      Author: unyuu
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/gl.h>
#include <GL/glu.h>

class Texture {
protected:
	GLuint _texture;
public:
	Texture(const char * filename);
	virtual ~Texture();

	void bind();
};

#endif /* TEXTURE_H_ */
