#ifndef RIGL_VERTEX_BUFFER_HPP
#define RIGL_VERTEX_BUFFER_HPP

#include <rigl/gl.hpp>
#include <rigl/vertex_format.hpp>

#include <vector>

namespace rigl {
    class VertexBuffer {
    public:
        explicit VertexBuffer(int vertexSize,
                              const std::shared_ptr<VertexFormat> &format) :
        vertexSize_{vertexSize},
        vertexFormat_{format}
        { }

        ~VertexBuffer()
        {
            destroy();
        }

        void create()
        {
            if (handle_ == 0) {
                GLuint handle = 0;
                glGenBuffers(1, &handle);
                if (handle == 0) {
                    throw std::runtime_error("Failed to allocate OpenGL "
                                             "vertex buffer");
                }
                handle_ = handle;

                glBindBuffer(GL_ARRAY_BUFFER, GLuint(handle_));
                auto size = vertexSize_ * getVertexCount();
                auto data = getVertexData();
                glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }
        }

        void destroy()
        {
            if (handle_ != 0) {
                GLuint handle = handle_;
                glDeleteBuffers(1, &handle);
                handle_ = 0;
            }
        }

        int getVertexSize() const
        {
            return vertexSize_;
        }

        const VertexFormat &getVertexFormat() const
        {
            return *vertexFormat_;
        }

        int getVertexCount() const
        {
            return vertexCount_;
        }

        void setVertexCount(int vertexCount)
        {
            vertexData_.resize(vertexSize_ * vertexCount);
            vertexCount_ = vertexCount;
        }

        std::uint8_t *getVertexData()
        {
            return &vertexData_[0];
        }

        const std::uint8_t *getVertexData() const
        {
            return &vertexData_[0];
        }

        void write()
        {
            writeRange(0, getVertexCount());
        }

        void writeRange(int first, int last)
        {
            create();

            glBindBuffer(GL_ARRAY_BUFFER, GLuint(handle_));
            auto offset = vertexSize_ * first;
            auto size = vertexSize_ * (last - first);
            const GLvoid *data = getVertexData() + vertexSize_ * first;
            glBufferSubData(GL_ARRAY_BUFFER, GLintptr(offset),
                            GLsizeiptr(size), data);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        int getHandle() const
        {
            return handle_;
        }

    private:
        int vertexSize_ = 1;
        std::shared_ptr<VertexFormat> vertexFormat_;
        int vertexCount_ = 0;
        std::vector<std::uint8_t> vertexData_;
        int handle_ = 0;
    };

    template <typename V>
    class VertexBufferView {
    public:
        typedef V Vertex;

        explicit VertexBufferView(const std::shared_ptr<VertexFormat> &format) :
        buffer_{std::make_shared<VertexBuffer>(sizeof(Vertex), format)}
        { }

        int getVertexCount() const
        {
            return buffer_->getVertexCount();
        }

        void setVertexCount(int vertexCount)
        {
            buffer_->setVertexCount(vertexCount);
        }

        Vertex *getVertices()
        {
            return reinterpret_cast<Vertex *>(buffer_->getVertexData());
        }

        const Vertex *getVertices() const
        {
            return reinterpret_cast<Vertex *>(buffer_->getVertexData());
        }

        void write()
        {
            buffer_->write();
        }

        void writeRange(int first, int last)
        {
            buffer_->writeRange(first, last);
        }

        const std::shared_ptr<VertexBuffer> &getBufferPtr()
        {
            return buffer_;
        }

    private:
        std::shared_ptr<VertexBuffer> buffer_;
    };
}

#endif
