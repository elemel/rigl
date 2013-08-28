#ifndef RIGL_DATA_TYPE_HPP
#define RIGL_DATA_TYPE_HPP

#include <rigl/gl.hpp>

namespace rigl {
    enum class DataType {
        nullType = 0,

        byteType = int(GL_BYTE),
        shortType = int(GL_SHORT),
        intType = int(GL_INT),

        unsignedByteType = int(GL_UNSIGNED_BYTE),
        unsignedShortType = int(GL_UNSIGNED_SHORT),
        unsignedIntType = int(GL_UNSIGNED_INT),

        floatType = int(GL_FLOAT),
        doubleType = int(GL_DOUBLE)
    };

    template <typename T>
    struct DataTypeOf;

    template <>
    struct DataTypeOf<signed char> {
        static const DataType type = DataType::byteType;
    };

    template <>
    struct DataTypeOf<short> {
        static const DataType type = DataType::shortType;
    };

    template <>
    struct DataTypeOf<int> {
        static const DataType type = DataType::intType;
    };

    template <>
    struct DataTypeOf<unsigned char> {
        static const DataType type = DataType::unsignedByteType;
    };

    template <>
    struct DataTypeOf<unsigned short> {
        static const DataType type = DataType::unsignedShortType;
    };

    template <>
    struct DataTypeOf<unsigned int> {
        static const DataType type = DataType::unsignedIntType;
    };

    template <>
    struct DataTypeOf<float> {
        static const DataType type = DataType::floatType;
    };

    template <>
    struct DataTypeOf<double> {
        static const DataType type = DataType::doubleType;
    };

    template <int N, typename T, bool Z>
    struct DataTraitsBase {
        static const int count = N;
        static const DataType type = DataTypeOf<T>::type;
        static const bool normalized = Z;
    };

    template <typename T>
    struct DataTraits;

    template <> struct DataTraits<signed char> : DataTraitsBase<1, signed char, false> { };
    template <> struct DataTraits<short> : DataTraitsBase<1, short, false> { };
    template <> struct DataTraits<int> : DataTraitsBase<1, int, false> { };

    template <> struct DataTraits<unsigned char> : DataTraitsBase<1, unsigned char, false> { };
    template <> struct DataTraits<unsigned short> : DataTraitsBase<1, unsigned short, false> { };
    template <> struct DataTraits<unsigned int> : DataTraitsBase<1, unsigned int, false> { };

    template <> struct DataTraits<float> : DataTraitsBase<1, float, false> { };
    template <> struct DataTraits<double> : DataTraitsBase<1, double, false> { };

    template <typename T, int N>
    struct DataTraits<T[N]> {
        static const int count = N * DataTraits<T>::count;
        static const DataType type = DataTraits<T>::type;
        static const bool normalized = DataTraits<T>::normalized;
    };
}

#endif
