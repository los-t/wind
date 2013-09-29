/***************************************************************************
 * Project: wind
 * File: gl/loader.h
 * Author: Vladimir 'dvn' Dranyonkov <los-t@ya.ru>
 * Description: OpenGl assets loader
 ***************************************************************************/

#ifndef WIND_GL_LOADER_H_
#define WIND_GL_LOADER_H_

#include <stdexcept>

#include <GL/glew.h>

#include "gl/model.h"
#include "gl/types.h"

namespace gl {
	const std::string vshader =
		"#version 120\n"
		" attribute vec3 coord3d;"
		" void main(void) {"
		"   gl_Position = vec4(coord3d, 1.0);"
		" }";

	const std::string fshader =
		"#version 120\n"
		" void main(void) {"
		"   gl_FragColor[0] = 0.0;"
		"   gl_FragColor[1] = 0.0;"
		"   gl_FragColor[2] = gl_FragCoord[0]*0.001;"
		" }";

	const std::vector<float> vertices = {
		0.0, 0.0, 0.0,
		0.0, 0.8, 0.0,
		0.8, 0.0, 0.0,
		0.8, 0.8, 0.0,
	};

	class Loader {
		public:
			static Model load() {
				shader_t vs = compile_shader(vshader, GL_VERTEX_SHADER);
				shader_t fs = compile_shader(fshader, GL_FRAGMENT_SHADER);
				Model mod = {
					.program = build_program({vs, fs}),
					.attribute = get_attribute(mod.program, "coord3d"),
					.vertices = &vertices[0],
					.vert_count = vertices.size()/3,
					.draw_as = GL_TRIANGLE_STRIP,
				};

				return mod;
			}

		private:
			static const size_t MAX_LOG_LEN = 512;

			static shader_t compile_shader(const std::string &body, shader_type_t t) {
				shader_t shader = glCreateShader(t);
				const char *tmp = body.c_str();
				glShaderSource(shader, 1, &tmp, NULL);
				glCompileShader(shader);

				GLint res = GL_FALSE;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
				if (res) return shader;

				std::string errmsg =
					"Could not build shader: \""
					+ body + "\"";

				GLint blen = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &blen);
				if (blen < 1)
					throw std::logic_error(errmsg + " due to unknown error");

				GLchar log[MAX_LOG_LEN];
				GLint slen = 0;
				glGetShaderInfoLog(shader, MAX_LOG_LEN, &slen, log);

				throw std::logic_error(errmsg + ": " + log);
			}

			static program_t build_program(const std::vector<shader_t> &shaders) {

				program_t prog = glCreateProgram();
				for (auto &shader : shaders)
					glAttachShader(prog, shader);

				glLinkProgram(prog);

				GLint res = GL_FALSE;
				glGetProgramiv(prog, GL_LINK_STATUS, &res);
				if (!res)
					throw std::logic_error("Could not link program");

				return prog;
			}

			static attribute_t get_attribute(program_t prog, const std::string name) {
				attribute_t attr = glGetAttribLocation(prog, name.c_str());
				if (attr == -1)
					throw std::logic_error("Could not find attribute " + name);

				return attr;
			}
	};

} //namespace gl

#endif //WIND_GL_LOADER_H_
