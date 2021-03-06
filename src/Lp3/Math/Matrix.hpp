#ifndef LP3_MATH_MATRIX
#define LP3_MATH_MATRIX

#include <Lp3/Math/Vector.hpp>
#include <Lp3/Math/Trig.h>

namespace Lp3 { namespace Math {



template<typename T>
class Matrix4
{
public:
    Vector4<T> Rows[4];

    Matrix4()
    {}

    inline Vector4<T> & operator[](int index)
    {
        return Rows[index];
    }

    Matrix4 operator * (Matrix4 & rhs)
    {
        Matrix4 c; // new matrix is a.rows and b.columns (rhs == b)
        for (int i = 0; i < 4; i ++) // a.rows
        {
            for (int j = 0; j < 4; j ++) // b.columns
            {
                c[i][j] = 0.0f;
                for (int k = 0; k < 4; k ++) // a.columns
                {
                    c[i][j] += ((*this)[i][k]) * (rhs[k][j]);
                }
            }
        }
        return c;
    }

    inline Vector3<T> CreateVector3FromColumn(int column) const
    {
        return Vector3<T>(Rows[0].GetValue(column),
                          Rows[1].GetValue(column),
                          Rows[2].GetValue(column));
    }

    inline Vector4<T> CreateVector4FromColumn(int column) const
    {
        return Vector4<T>(Rows[0].GetValue(column),
                          Rows[1].GetValue(column),
                          Rows[2].GetValue(column),
                          Rows[3].GetValue(column));
    }

    /** Treats the matrix on rhs as if it's a 4 x 1 matrix (that's
     * 4 rows by 1 column, with the last row being set to zero)
     * producing a 4 x 1 matrix, which is
     * represented as a Vector4. */
    Vector3<T> MultiplyByVector3 (const Vector3<T> & rhs)
    {
        // Treats vector4 as a one column, 4 row matrix.
        // Result is 4 x 1
        Vector3<T> c; // new matrix is a.rows and b.columns (rhs == b)
         // forget last row (index = 3) because its cut off.
        /*for (int i = 0; i < 3; i ++) // a.rows
        {
            // We treat the Vector as though it's "columns" = 1, so there
            // is only one j which is constant at zero.
            //for (int j = 0; j < 1; j ++) // b.columns
            //{
                //c[i][j] = 0.0f;
                c[i] = 0.0f;
                for (int k = 0; k < 3; k ++) // a.columns
                {
                    //c[i][j] += ((*this)[i][k]) * (rhs[k][j]);
                    (c[i]) += ((*this)[i][k]) * (rhs[k]);
                }
            //}
        }
        */
        c.X = (((*this)[0].X) * rhs.X) + (((*this)[0].Y) * rhs.Y) +
                (((*this)[0].Z) * rhs.Z); // + blah * 0.0f
        c.Y = (((*this)[1].X) * rhs.X) + (((*this)[1].Y) * rhs.Y) +
                (((*this)[1].Z) * rhs.Z);
        c.Z = (((*this)[2].X) * rhs.X) + (((*this)[2].Y) * rhs.Y) +
                (((*this)[2].Z) * rhs.Z);
        return c;
    }


    /** Treats the matrix on rhs as if it's a 4 x 1 matrix (that's
     * 4 rows by 1 column) producing a 4 x 1 matrix, which is
     * represented as a Vector4. */
    Vector4<T> MultiplyByVector4 (const Vector4<T> & rhs)
    {
        // Treats vector4 as a one column, 4 row matrix.
        // Result is 4 x 1
        Vector4 c; // new matrix is a.rows and b.columns (rhs == b)
        for (int i = 0; i < 4; i ++) // a.rows
        {
            // We treat the Vector as though it's "columns" = 1, so there
            // is only one j which is constant at zero.
            //for (int j = 0; j < 1; j ++) // b.columns
            //{
                //c[i][j] = 0.0f;
                c[i] = 0.0f;
                for (int k = 0; k < 4; k ++) // a.columns
                {
                    //c[i][j] += ((*this)[i][k]) * (rhs[k][j]);
                    c[i] += ((*this)[i][k]) * (rhs[k]);
                }
            //}
        }
        return c;
    }


    void SetColumnToVector(int column, Vector3<T> & vector)
    {
        Rows[0][column] = vector.X;
        Rows[1][column] = vector.Y;
        Rows[2][column] = vector.Z;
        Rows[3][column] = 0.0f;
    }

    void SetColumnToVector(int column, Vector4<T> & vector)
    {
        Rows[0][column] = vector.X;
        Rows[1][column] = vector.Y;
        Rows[2][column] = vector.Z;
        Rows[3][column] = vector.W;
    }

    void SetToIdentity()
    {
        Rows[0] = Vector4(1, 0, 0, 0);
        Rows[1] = Vector4(0, 1, 0, 0);
        Rows[2] = Vector4(0, 0, 1, 0);
        Rows[3] = Vector4(0, 0, 0, 1);
    }

    void SetToRotateMatrixX(int angle)
    {
        while(angle >= 360)
        {
            angle = angle - 360;
        }
        while(angle < 0)
        {
            angle = angle + 360;
        }
        this->Rows[0] = Vector4<T>(1, 0, 0, 0);
        this->Rows[1] = Vector4<T>(0, Cos(angle), Sin(angle) * -1.0f, 0);
        this->Rows[2] = Vector4<T>(0, Sin(angle), Cos(angle), 0);
        this->Rows[3] = Vector4<T>(0, 0, 0, 1);
    }


    void SetToRotateMatrixY(int angle)
    {
        while(angle >= 360)
        {
            angle = angle - 360;
        }
        while (angle < 0)
        {
            angle = angle + 360;
        }
        this->Rows[0] = Vector4<T>(Cos(angle), 0, Sin(angle) * -1.0f, 0);
        this->Rows[1] = Vector4<T>(0, 1, 0, 0);
        this->Rows[2] = Vector4<T>(Sin(angle), 0, Cos(angle), 0);
        this->Rows[3] = Vector4<T>(0, 0, 0, 1);
    }


    /** This exciting function is like SetToRotateMatrixY, but instead
     * of using an angle, it takes a unit vector where X and Z are pointed
     * in some direction, and that angle between them is what would
     * be supplied to the other SetToRotateMatrixY function, but figuring
     * out the angle would take time so you call this INSTEAD!!K#JKJHF
     * EXPECTS CARTISIAN CORDINATES?!!  X++ to right, Z ++ is UP!*/
    void SetToRotateMatrixY(Vector3<T> direction)
    {
        this->Rows[0] = Vector4(direction.Z * -1.0f, 0, direction.X, 0);
        this->Rows[1] = Vector4(0, 1, 0, 0);
        this->Rows[2] = Vector4(direction.X * -1.0f, 0, direction.Z * -1.0f, 0);
        this->Rows[3] = Vector4(0, 0, 0, 1);
    }

    void SetToRotateMatrixZ(int angle)
    {
        while(angle >= 360)
        {
            angle = angle - 360;
        }
        while (angle < 0)
        {
            angle = angle + 360;
        }
        this->Rows[0] = Vector4(Cos(angle), Sin(angle) * -1.0f, 0, 0);
        this->Rows[1] = Vector4(Sin(angle), Cos(angle), 0, 0);
        this->Rows[2] = Vector4(0, 0, 1, 0);
        this->Rows[3] = Vector4(0, 0, 0, 1);
    }
};

}}

#endif
