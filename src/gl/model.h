/***************************************************************************
 * Project: wind
 * File: gl/model.h
 * Author: Vladimir 'dvn' Dranyonkov <los-t@ya.ru>
 * Description: A 3d model representation
 ***************************************************************************/

#ifndef WIND_GL_MODEL_H_
#define WIND_GL_MODEL_H_

#include "gl/types.h"

namespace gl {

	struct Model {
		program_t program;
		attribute_t attribute;
		const vertex_t *vertices;
		size_t components;
		size_t vert_count;
		drawable_t draw_as;
	};

} //namespace gl

#endif //WIND_GL_MODEL_H_
