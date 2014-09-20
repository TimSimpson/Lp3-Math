#ifndef MATH_TRIG_H
#define MATH_TRIG_H

#include <Config_Lp3Math.h>
#include <Lp3/LE.h>

namespace Lp3 { namespace Math {

//const float COT_INFINITY = 3.40282346638528860e+38;

MACARONI_LIB_DECL_Lp3___Lp3_46_Math___DEV___lib
extern const float SIN[360];

MACARONI_LIB_DECL_Lp3___Lp3_46_Math___DEV___lib
extern const float COS[360];

MACARONI_LIB_DECL_Lp3___Lp3_46_Math___DEV___lib
extern const float TAN[360];

MACARONI_LIB_DECL_Lp3___Lp3_46_Math___DEV___lib
extern const float COT[360];


inline float Cos(int degrees)
{
	return COS[degrees];
}

inline float Cot(int degrees)
{
	return COT[degrees];
}

MACARONI_LIB_DECL_Lp3___Lp3_46_Math___DEV___lib
float GetArc(float sinAnswer);

//void InitTrig();

inline float Sin(int degrees)
{
	return SIN[degrees];
}

inline float Tan(int degrees)
{
	return TAN[degrees];
}



} } // end namespace

#endif
