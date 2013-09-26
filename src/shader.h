#ifndef WIND_GL_SHADER_H_
#define WIND_GL_SHADER_H_

#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GL/gl.h>

namespace gfx {
	namespace gl {

		struct Exception {
			Exception(const std::string m) : msg(m) {}
			virtual ~Exception() {}

			std::string msg;
			virtual std::string str() const {
				return "GL: " + msg;
			}
		};

		std::ostream& operator<<(std::ostream& os, const Exception& e) {
			os << e.str();
			return os;
		}


		class Shader {
			public:
				typedef GLuint id_type;
				typedef GLenum type_type;
				struct Exception : public gl::Exception {
					Exception(id_type i, const std::string b, const std::string m)
						: gl::Exception(m), id(i), body(b)
					{}
					virtual ~Exception() {}

					id_type id;
					std::string body;

					virtual std::string str() const {
						std::stringstream ss("GL Shader:");
						ss << msg << "in shader #" << id << ": " << body;
						return ss.str();
					}
				};

				virtual ~Shader() {}

				id_type ref() { return ref_; }

			protected:
				Shader(const std::string body, type_type shader)
					: body_{body}
				{
					if (!(ref_ = glCreateShader(shader)))
						throw gl::Exception("glCreateShader: Incorrect type value when compiling shader");

					const char *src = body_.c_str();
					glShaderSource(ref_, 1, &src, NULL);
					glCompileShader(ref_);
					GLint res = GL_FALSE;
					glGetShaderiv(ref_, GL_COMPILE_STATUS, &res);
					if (!res) {
						GLint blen = 0;
						glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &blen);
						if (blen > 1) {
							GLchar *log = new GLchar[blen];

							GLint slen = 0;
							glGetShaderInfoLog(shader, blen, &slen, log);
							throw Exception(ref_, body, log);
						}

						throw Exception(ref_, body, "Unknown error");
					}
				}

				id_type ref_;
				std::string body_;
		};

		class VertexShader : public Shader {
			public:
				VertexShader(const std::string body)
					: Shader(body, GL_VERTEX_SHADER) {}
				virtual ~VertexShader() {}
		};

		class FragmentShader : public Shader {
			public:
				FragmentShader(const std::string body)
					: Shader(body, GL_FRAGMENT_SHADER) {}
				virtual ~FragmentShader() {}
		};

	} //namespace gl
} //namespace gfx

#endif //WIND_GL_SHADER_H_
