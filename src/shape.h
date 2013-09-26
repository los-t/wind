#ifndef WIND_SHAPE_H_
#define WIND_SHAPE_H_

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

#include "shader.h"

namespace gfx {

	const char *vert_shader =
		"#version 120\n"
		" attribute vec2 coord2d;"
		" void main(void) {"
		"   gl_Position = vec4(coord2d, 0.0, 1.0);"
		" }";

	const char *frag_shader =
		"#version 120\n"
		" void main(void) {"
		"   gl_FragColor[0] = 0.0;"
		"   gl_FragColor[1] = 0.0;"
		"   gl_FragColor[2] = gl_FragCoord[0]*0.001;"
		" }";

	struct ProgramException {};
	struct AttributeException {};

	class Shape {
		public:
			Shape() : vshader_(vert_shader), fshader_(frag_shader)
			{
				GLint res_link = GL_FALSE;

				prog_ = glCreateProgram();
				glAttachShader(prog_, vshader_.ref());
				glAttachShader(prog_, fshader_.ref());
				glLinkProgram(prog_);
				glGetProgramiv(prog_, GL_LINK_STATUS, &res_link);
				if (!res_link)
					throw ProgramException();

				attr_ = glGetAttribLocation(prog_, "coord2d");
				if (attr_ == -1)
					throw AttributeException();
			}

			virtual ~Shape() { glDeleteProgram(prog_); }

			void draw() {
				glUseProgram(prog_);
				glEnableVertexAttribArray(attr_);

				GLfloat triangle[] = {
					 0.0,  0.0,
					 0.0,  0.8,
					 0.8,  0.0,
					 0.8,  0.8,
				};

				glVertexAttribPointer(attr_, 2, GL_FLOAT, GL_FALSE, 0, triangle);
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
				glDisableVertexAttribArray(attr_);
			}

		private:
			gl::VertexShader vshader_;
			gl::FragmentShader fshader_;
			GLuint prog_;
			GLint attr_;
	};

} //namespace gfx

#endif //WIND_SHAPE_H_
