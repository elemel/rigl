#ifndef RIGL_SHADER_HPP
#define RIGL_SHADER_HPP

#include <rigl/gl.hpp>

#include <string>
#include <vector>

namespace rigl {
    enum class ShaderType {
        vertex = int(GL_VERTEX_SHADER),
        geometry = int(GL_GEOMETRY_SHADER),
        fragment = int(GL_FRAGMENT_SHADER),
    };

    class Shader {
    public:
        explicit Shader(ShaderType type, const std::string &source = "") :
        type_(type),
        source_(source)
        { }

        ~Shader()
        {
            destroy();
        }
        
        void create()
        {
            if (handle_ == 0) {
                handle_ = glCreateShader(GLenum(type_));
                if (handle_ == 0) {
                    throw std::runtime_error("Failed to create OpenGL shader");
                }

                compiled_ = false;
            }

            if (!compiled_) {
                const GLchar *source = source_.c_str();
                glShaderSource(GLuint(handle_), 1, &source, nullptr);

                glCompileShader(GLuint(handle_));
                GLint compileStatus = GL_FALSE;
                glGetShaderiv(GLuint(handle_), GL_COMPILE_STATUS, &compileStatus);
                if (compileStatus == GL_FALSE) {
                    std::string message = "Failed to compile OpenGL shader";

                    GLint infoLogLength = 0;
                    glGetShaderiv(GLuint(handle_), GL_INFO_LOG_LENGTH, &infoLogLength);
                    if (infoLogLength != 0) {
                        std::vector<GLchar> infoLog(infoLogLength);
                        glGetShaderInfoLog(GLuint(handle_), infoLogLength, nullptr,
                                           &infoLog[0]);
                        message += ": ";
                        message += &infoLog[0];
                    }
                    
                    throw std::runtime_error(message);
                }
                
                compiled_ = true;
            }
        }
        
        void destroy()
        {
            if (handle_ != 0) {
                glDeleteShader(GLuint(handle_));
                handle_ = 0;
            }
        }
        
        void setSource(const std::string &source)
        {
            source_ = source;
            compiled_ = false;
        }

        int getHandle() const
        {
            return handle_;
        }
        
    private:
        ShaderType type_ = ShaderType::vertex;
        std::string source_;
        int handle_ = 0;
        bool compiled_ = false;
    };
}

#endif
