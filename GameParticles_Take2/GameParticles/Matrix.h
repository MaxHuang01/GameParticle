//---------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"
#include "Vect4D.h"

// forward declare
class Vect4D;

// class
class Matrix
{
public:

	// local enumerations
	enum class MatrixRow
	{
		MATRIX_ROW_0,
		MATRIX_ROW_1,
		MATRIX_ROW_2,
		MATRIX_ROW_3
	};

	Matrix();//default	
	Matrix(Matrix& t);//copy
	~Matrix();//destructor
	void operator =(const Matrix& m);//assugnment
	//big 4

	void set( MatrixRow row, Vect4D &t );
	void get( MatrixRow row, Vect4D &vOut )const;

	void setIdentMatrix();
	void setTransMatrix(Vect4D &t );
	void setScaleMatrix(Vect4D &s );
	void setRotZMatrix(float& Z_Radians );

	const float &operator[]( Index e);
	
	Matrix operator*( Matrix &t );
	Matrix operator*( float s );

	const float Determinant();
	
	Matrix GetAdjugate();
	Matrix& operator/=(const float t);
	
	void Inverse( Matrix &out );
	void setTmpInMain();
	void setInverseCameraMatrixInDraw();
	void setTransCameraInDraw();

	Matrix fiveMatrixMul(Matrix& a,Matrix& b, Matrix& c, Matrix& d, Matrix& e);

	union
	{
		struct
		{
			Vect4D v0;
			Vect4D v1;
			Vect4D v2;
			Vect4D v3;
		};

		struct
		{
			// ROW 0
			float m0;
			float m1;
			float m2;
			float m3;

			// ROW 1
			float m4;
			float m5;
			float m6;
			float m7;

			// ROW 2
			float m8;
			float m9;
			float m10;
			float m11;

			// ROW 3
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};
	
private:
	//// ROW 0
	//float m0;
	//float m1;
	//float m2;
	//float m3;

	//// ROW 1
	//float m4;
	//float m5;
	//float m6;
	//float m7;

	//// ROW 2
	//float m8;
	//float m9;
	//float m10;
	//float m11;

	//// ROW 3
	//float m12;
	//float m13;
	//float m14;
	//float m15;
};

#endif  

// --- End of File ---
