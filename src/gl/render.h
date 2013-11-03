/***************************************************************************
 * Project: wind
 * File: gl/render.h
 * Author: Vladimir 'dvn' Dranyonkov <los-t@ya.ru>
 * Description: A renderer abstraction
 ***************************************************************************/

#ifndef WIND_GL_RENDER_H_
#define WIND_GL_RENDER_H_

#include <GL/glew.h>

#include "gl/scene.h"

namespace gl {

	class Render {
		public:
			Render() { }
			virtual ~Render() { }

			void update(const Scene& scn) {
				glClearColor(0.0, 0.0, 0.0, 1.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				for (auto& model: scn.visible_objects()) {
					glUseProgram(model.program);
					glEnableVertexAttribArray(model.attribute);
					glVertexAttribPointer(
							model.attribute,
							model.components,
							GL_FLOAT,
							GL_FALSE, 0,
							model.vertices);

					glDrawArrays(model.draw_as, 0, model.vert_count);
					glDisableVertexAttribArray(model.attribute);
				}
			}
	};

} //namespace gl

#endif //WIND_GL_RENDER_H_
