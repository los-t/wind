/***************************************************************************
 * Project: wind
 * File: gl/loader.h
 * Author: Vladimir 'dvn' Dranyonkov <los-t@ya.ru>
 * Description: OpenGl assets loader
 ***************************************************************************/

#ifndef WIND_GL_LOADER_H_
#define WIND_GL_LOADER_H_

#include <stdexcept>
#include <fstream>
#include <string>

#include <GL/glew.h>

#include "gl/model.h"
#include "gl/types.h"

namespace gl {
	const std::vector<float> vertices = {
		0.0, 0.0, 0.0,
		0.0, 0.8, 0.0,
		0.8, 0.0, 0.0,
		0.8, 0.8, 0.0,
	};

	class Loader {
		public:
			static Model load(const std::string& path) {

				const std::string vshader = read_shader(path + "/vertex.glsl");
				shader_t vs = compile_shader(vshader, GL_VERTEX_SHADER);

				const std::string fshader = read_shader(path + "/fragment.glsl");
				shader_t fs = compile_shader(fshader, GL_FRAGMENT_SHADER);

				Model mod = {
					.program = build_program({vs, fs}),
					.attribute = get_attribute(mod.program, "coord3d"),
					.vertices = &vertices[0],
					.vert_count = vertices.size()/3,
					.draw_as = GL_LINE_LOOP,
				};

				return mod;
			}

		private:
			static const size_t MAX_LOG_LEN = 512;

			static std::string read_shader(const std::string& path) {

				std::ifstream strm(path);
				std::string buf;

				for (std::string line; std::getline(strm, line); )
					buf += line + "\n";
				
				return buf;
			}

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
