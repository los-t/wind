/***************************************************************************
 * Project: wind
 * File: gl/types.h
 * Author: Vladimir 'dvn' Dranyonkov <los-t@ya.ru>
 * Description: OpenGl-related typedefs
 ***************************************************************************/

#ifndef WIND_GL_TYPES_H_
#define WIND_GL_TYPES_H_

#include <GL/glew.h>

namespace gl {

	typedef GLuint  program_t;
	typedef GLuint  shader_t;
	typedef GLint   attribute_t;
	typedef GLfloat vertex_t;
	typedef GLenum  shader_type_t;
	typedef GLenum  drawable_t;

} //namespace gl

#endif //WIND_GL_TYPES_H_
