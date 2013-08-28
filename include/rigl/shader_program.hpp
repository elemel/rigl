#ifndef RIGL_SHADER_PROGRAM_HPP
#define RIGL_SHADER_PROGRAM_HPP

#include <rigl/gl.hpp>
#include <rigl/shader.hpp>

#include <memory>
#include <stdexcept>
#include <vector>

namespace rigl {
    class ShaderProgram {
    public:
        ~ShaderProgram()
        {
            destroy();
        }
        
        void create()
        {
            if (handle_ == 0) {
                handle_ = int(glCreateProgram());
                if (handle_ == 0) {
                    throw std::runtime_error("Failed to create OpenGL shader program");
                }

                for (auto &shader : shaders_) {
                    shader->create();
                    glAttachShader(GLuint(handle_), shader->getHandle());
                }

                glLinkProgram(GLuint(handle_));
                GLint linkStatus = GL_FALSE;
                glGetProgramiv(GLuint(handle_), GL_LINK_STATUS, &linkStatus);
                if (linkStatus == GL_FALSE) {
                    std::string message = "Failed to link OpenGL shader program";

                    GLint infoLogLength = 0;
                    glGetProgramiv(GLuint(handle_), GL_INFO_LOG_LENGTH,
                                   &infoLogLength);
                    if (infoLogLength != 0) {
                        std::vector<GLchar> infoLog(infoLogLength);
                        glGetProgramInfoLog(GLuint(handle_), infoLogLength,
                                            nullptr, &infoLog[0]);
                        message += ": ";
                        message += &infoLog[0];
                    }
                    
                    throw std::runtime_error(message);
                }
            }
        }

        void destroy()
        {
            if (handle_ != 0) {
                glDeleteProgram(GLuint(handle_));
                handle_ = 0;
            }
        }

        void addShader(const std::shared_ptr<Shader> &shader)
        {
            shaders_.push_back(shader);
        }

        int getHandle() const
        {
            return handle_;
        }
        
    private:
        std::vector<std::shared_ptr<Shader>> shaders_;
        int handle_ = 0;
    };
}

#endif
