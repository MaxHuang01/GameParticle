//---------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#ifndef Vect4D_H
#define Vect4D_H

// includes
#include "Enum.h"
#include <immintrin.h>
#include <smmintrin.h>


// Foward Declarations
class Matrix;

// class
class __declspec(align(16)) Vect4D
{
public:
	friend class Matrix;

	Vect4D();//default	
	Vect4D(float tx, float ty, float tz, float tw = 1.0f );//specialized
	~Vect4D();//destructor
	void operator=(const Vect4D& v);//assignment
	Vect4D(const Vect4D& v);//copy

	void norm( Vect4D &out );
	void set(float tx, float ty, float tz, float tw = 1.0f);
	void set(float t);
	
	
	Vect4D operator + ( Vect4D &t );
	Vect4D operator - ( Vect4D &t );
	Vect4D operator * (float scale );

	void Cross(Vect4D &vin, Vect4D &vout);
	float &operator[]( Vect e);

	float SqrtOpt(float k);

	union
	{
		__declspec(align(16)) __m128 m;

		// anonymous struct
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};

private:
	/*float x;
	float y;
	float z;
	float w;*/
};

#endif

// --- End of File ---
