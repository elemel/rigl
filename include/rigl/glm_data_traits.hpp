#ifndef RIGL_GLM_VERTEX_ATTRIBUTE_HPP
#define RIGL_GLM_VERTEX_ATTRIBUTE_HPP

#include <rigl/data_type.hpp>

#include <glm/ext.hpp>
#include <glm/glm.hpp>

namespace rigl {
    template <> struct DataTraits<glm::i8vec2> : DataTraitsBase<2, signed char, false> { };
    template <> struct DataTraits<glm::i8vec3> : DataTraitsBase<3, signed char, false> { };
    template <> struct DataTraits<glm::i8vec4> : DataTraitsBase<4, signed char, false> { };

    template <> struct DataTraits<glm::i16vec2> : DataTraitsBase<2, short, false> { };
    template <> struct DataTraits<glm::i16vec3> : DataTraitsBase<3, short, false> { };
    template <> struct DataTraits<glm::i16vec4> : DataTraitsBase<4, short, false> { };

    template <> struct DataTraits<glm::i32vec2> : DataTraitsBase<2, int, false> { };
    template <> struct DataTraits<glm::i32vec3> : DataTraitsBase<3, int, false> { };
    template <> struct DataTraits<glm::i32vec4> : DataTraitsBase<4, int, false> { };

    template <> struct DataTraits<glm::u8vec2> : DataTraitsBase<2, unsigned char, false> { };
    template <> struct DataTraits<glm::u8vec3> : DataTraitsBase<3, unsigned char, false> { };
    template <> struct DataTraits<glm::u8vec4> : DataTraitsBase<4, unsigned char, false> { };

    template <> struct DataTraits<glm::u16vec2> : DataTraitsBase<2, unsigned short, false> { };
    template <> struct DataTraits<glm::u16vec3> : DataTraitsBase<3, unsigned short, false> { };
    template <> struct DataTraits<glm::u16vec4> : DataTraitsBase<4, unsigned short, false> { };

    template <> struct DataTraits<glm::u32vec2> : DataTraitsBase<2, unsigned int, false> { };
    template <> struct DataTraits<glm::u32vec3> : DataTraitsBase<3, unsigned int, false> { };
    template <> struct DataTraits<glm::u32vec4> : DataTraitsBase<4, unsigned int, false> { };

    template <> struct DataTraits<glm::f32vec2> : DataTraitsBase<2, float, false> { };
    template <> struct DataTraits<glm::f32vec3> : DataTraitsBase<3, float, false> { };
    template <> struct DataTraits<glm::f32vec4> : DataTraitsBase<4, float, false> { };

    template <> struct DataTraits<glm::f64vec2> : DataTraitsBase<2, double, false> { };
    template <> struct DataTraits<glm::f64vec3> : DataTraitsBase<3, double, false> { };
    template <> struct DataTraits<glm::f64vec4> : DataTraitsBase<4, double, false> { };
}

#endif
