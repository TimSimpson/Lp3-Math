#ifndef LP3_MATH_VECTOR3
#define LP3_MATH_VECTOR3

#include <algorithm>
#include <cmath>

namespace Lp3 { namespace Math {


template<typename T>
class Vector3
{
public:
    typedef T NumberType;

    NumberType X;
    NumberType Y;
    NumberType Z;

    inline Vector3()
    :   X(0),
        Y(0),
        Z(0)
    {
    }

    inline Vector3(NumberType X, NumberType Y, NumberType Z)
    :   X(X),
        Y(Y),
        Z(Z)
    {
    }

    inline bool const operator == (Vector3 const & other) const
    {
        return (X == other.X && Y == other.Y && Z == other.Z);
    }

    inline bool operator != (const Vector3 & other) const
    {
        return !operator==(other);
    }

    inline Vector3 operator + (const Vector3 & rhs) const
    {
        return Vector3(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
    }

    inline void operator += (const Vector3 & rhs)
    {
        this->X += rhs.X;
        this->Y += rhs.Y;
        this->Z += rhs.Z;
    }

    inline Vector3 operator - (const Vector3 &rhs) const
    {
        return Vector3(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
    }

    inline Vector3 operator - (const NumberType scalar) const
    {
        return Vector3(X - scalar, Y - scalar, Z - scalar);
    }

    inline Vector3 operator * (const NumberType scalar) const
    {
        return Vector3(X * scalar, Y * scalar, Z * scalar);
    }

    inline Vector3 operator / (const NumberType scalar) const
    {
        return Vector3(X / scalar, Y / scalar, Z / scalar);
    }

    inline NumberType & operator[](int index)
    {
        switch(index) {
            case 0: return X;
            case 1: return Y;
            case 2: return Z;
            default: LP3_FAIL("Bad index."); return X;
        }
    }

    inline const NumberType & operator[](int index) const
    {
        return (index > 1 ?
                    (index == 0 ? X : Y)
                :
                    Z
                );
    }


    inline NumberType Magnitude() const
    {
        return std::abs(X) + std::abs(Y) + std::abs(Z);
    }

    // TODO: Not sure if this works.
    inline void MakeUnitVector()
    {

        NumberType sum = std::abs(X) + std::abs(Y) + std::abs(Z);
        if (sum == 0.0f)
        {
            return;
        }

        X /= sum;
        Y /= sum;
        Z /= sum;
    }

    inline void MultiplyByScalar(NumberType scalar)
    {
        this->X *= scalar;
        this->Y *= scalar;
        this->Z *= scalar;
    }


    inline void PointTo(const Vector3 & from, const Vector3 & pointTo)
    {
        X = pointTo.X - from.X;
        Y = pointTo.Y - from.Y;
        Z = pointTo.Z - from.Z;
        MakeUnitVector();
    }

    /**
     * Takes the normal vector and the incident and returns reflected vector.
     */
    /*~global Vector3 Reflect(const Vector3 & normal,
                                   const Vector3 & incident)
    {
        const Vector3 nIncident = Normalize(incident);
        return nIncident - (normal * (2*DotProduct(nIncident, normal)));
    }*/
};


template<typename VectorType>
VectorType Normalize(const VectorType & v)
{
    const NumberType vLength = Length(v);
    return Vector3(v.X / vLength, v.Y / vLength, v.Z / vLength);
}

template<typename VectorType, typename NumberType>
VectorType Normalize(const VectorType & v, const NumberType length)
{
    return VectorType(v.X / length, v.Y / length, v.Z / length);
}

template<typename VectorType>
std::ostream & operator << (std::ostream & output, const VectorType & v)
{
    output << "(" << v.X << ", " << v.Y << ", " << v.Z << ")";
    return output;
}

template<typename VectorType>
VectorType CrossProduct(const VectorType & a, const VectorType & b)
{
    // Area of the parallelogram *sic* created by two vectors.
    const auto x = (a.Y * b.Z) - (a.Z * b.Y);
    const auto y = (a.Z * b.X) - (a.X * b.Z);
    const auto z = (a.X * b.Y) - (a.Y * b.X);
    return VectorType(x, y, z);
}

template<typename VectorType>
typename VectorType::NumberType DotProduct(
    const VectorType & a, const VectorType & b)
{
    return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
}

template<typename VectorType>
typename VectorType::NumberType Length(const VectorType & v)
{
    return std::sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}


template<typename T>
class Vector4 : public Vector3<T>
{
public:
    float W;

    inline Vector4() : X(0), Y(0), Z(0), W(0) {}

    inline Vector4(float X, float Y, float Z, float W)
        : X(X), Y(Y), Z(Z), W(W){}

    inline NumberType & operator[](int index)
    {
        switch(index) {
            case  3: return W;
            case  1: return Y;
            case  2: return Z;
            default: return super[index];
        }
    }

    inline bool const operator == (Vector4 const & other) const
    {
        return (super->==(other) && W == other.W);
    }

    inline Vector4 operator + (Vector4 &rhs)
    {
        return Vector4(X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W);
    }

};
} } // end namespace

#endif
