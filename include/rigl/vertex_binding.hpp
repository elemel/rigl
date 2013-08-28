#ifndef RIGL_VERTEX_BINDING_HPP
#define RIGL_VERTEX_BINDING_HPP

#include <rigl/gl.hpp>
#include <rigl/shader_program.hpp>
#include <rigl/vertex_buffer.hpp>

#include <memory>
#include <vector>

namespace rigl {
    class VertexBinding {
    public:
        explicit VertexBinding(const std::shared_ptr<VertexBuffer> &vertexBuffer,
                               const std::shared_ptr<ShaderProgram> &shaderProgram) :
        vertexBuffer_{vertexBuffer},
        shaderProgram_{shaderProgram}
        { }

        void create()
        {
            updateAttributeLocations();

            const auto &format = vertexBuffer_->getVertexFormat();

            auto stride = vertexBuffer_->getVertexSize();
            const char *zeroOffset = nullptr;

            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_->getHandle());
            for (auto i = 0; i < attributeLocations_.size(); ++i) {
                auto location = attributeLocations_[i];
                if (location != -1) {
                    const auto &attribute = format.getAttribute(i);
                    const GLvoid *offset = zeroOffset + attribute.offset;

                    glEnableVertexAttribArray(GLuint(location));
                    glVertexAttribPointer(GLuint(location), GLint(attribute.count),
                                          GLenum(attribute.type),
                                          GLboolean(attribute.normalized),
                                          GLsizei(stride), offset);
                }
            }
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        void destroy()
        {
            for (auto location : attributeLocations_) {
                if (location != -1) {
                    glDisableVertexAttribArray(location);
                }
            }
        }

    private:
        std::shared_ptr<VertexBuffer> vertexBuffer_;
        std::shared_ptr<ShaderProgram> shaderProgram_;
        std::vector<int> attributeLocations_;

        void updateAttributeLocations()
        {
            auto programHandle = shaderProgram_->getHandle();
            const auto &format = vertexBuffer_->getVertexFormat();
            attributeLocations_.resize(format.getAttributeCount());
            for (auto i = 0; i < attributeLocations_.size(); ++i) {
                const GLchar *name = format.getAttribute(i).name.c_str();
                attributeLocations_[i] = glGetAttribLocation(GLuint(programHandle),
                                                             name);
            }
        }
    };
}

#endif
