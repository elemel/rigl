#ifndef RIGL_VERTEX_FORMAT_HPP
#define RIGL_VERTEX_FORMAT_HPP

#include <rigl/data_type.hpp>
#include <rigl/gl.hpp>

#include <cstddef>
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

namespace rigl {
    template <typename A, typename V>
    int getVertexAttributeCount(A (V::*attribute))
    {
        return DataTraits<A>::count;
    }

    template <typename A, typename V>
    DataType getVertexAttributeType(A (V::*attribute))
    {
        return DataTraits<A>::type;
    }

    template <typename A, typename V>
    int getVertexAttributeOffset(A (V::*attribute))
    {
        V *vertexPtr = nullptr;
        auto attributePtr = &(vertexPtr->*attribute);
        return int(reinterpret_cast<std::uint8_t *>(attributePtr) -
                   reinterpret_cast<std::uint8_t *>(vertexPtr));
    }

    template <typename A, typename V>
    bool isVertexAttributeNormalized(A (V::*attribute))
    {
        return DataTraits<A>::normalized;
    }

    class VertexAttribute {
    public:
        std::string name;
        int count = 1;
        DataType type = DataType::floatType;
        int offset = 0;
        bool normalized = false;

        explicit VertexAttribute(const std::string &name, int count,
                                 DataType type, int offset, bool normalized) :
        name{name}, count{count}, type{type}, offset{offset}
        { }

        template <typename A, typename V>
        explicit VertexAttribute(const std::string &name, A V::*attribute) :
        name{name},
        count{getVertexAttributeCount(attribute)},
        type{getVertexAttributeType(attribute)},
        offset{getVertexAttributeOffset(attribute)},
        normalized{isVertexAttributeNormalized(attribute)}
        {
            assert(count != 0);
            assert(type != DataType::nullType);
        }

        template <typename A, typename V>
        explicit VertexAttribute(const std::string &name, A V::*attribute,
                                 bool normalized) :
        name{name},
        count{getVertexAttributeCount(attribute)},
        type{getVertexAttributeType(attribute)},
        offset{getVertexAttributeOffset(attribute)},
        normalized{normalized}
        {
            assert(count != 0);
            assert(type != DataType::nullType);
        }
    };

    class VertexFormat {
    public:
        int getAttributeCount() const
        {
            return int(attributes_.size());
        }

        const VertexAttribute &getAttribute(int index) const
        {
            return attributes_[index];
        }

        void addAttribute(const std::string &name, int count, DataType type,
                          int offset, bool normalized)
        {
            attributes_.emplace_back(name, count, type, offset, normalized);
        }

        template <typename A, typename V>
        void addAttribute(const std::string &name, A V::*attribute)
        {
            attributes_.emplace_back(name, attribute);
        }

        template <typename A, typename V>
        void addAttribute(const std::string &name, A V::*attribute,
                          bool normalized)
        {
            attributes_.emplace_back(name, attribute, normalized);
        }

    private:
        std::vector<VertexAttribute> attributes_;
    };
}

#endif
