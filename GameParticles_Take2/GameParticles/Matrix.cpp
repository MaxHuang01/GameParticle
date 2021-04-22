//---------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#include <Math.h>
#include "Vect4d.h"
#include "Matrix.h"

Matrix::Matrix()
{	/*
	this->m0 = 0.0;
	this->m1 = 0.0;
	this->m2 = 0.0;
	this->m3 = 0.0;

	this->m4 = 0.0;
	this->m5 = 0.0;
	this->m6 = 0.0;
	this->m7 = 0.0;

	this->m8 = 0.0;
	this->m9 = 0.0;
	this->m10 = 0.0;
	this->m11 = 0.0;
	
	this->m12 = 0.0;
	this->m13 = 0.0;
	this->m14 = 0.0;
	this->m15 = 0.0;*/
	v0.set(0.0f);
	v2.set(0.0f);
	v1.set(0.0f);
	v3.set(0.0f);
}



Matrix::Matrix(Matrix& t)
{
	this->m0 = t.m0;
	this->m1 = t.m1;
	this->m2 = t.m2;
	this->m3 = t.m3;

	this->m4 = t.m4;
	this->m5 = t.m5;
	this->m6 = t.m6;
	this->m7 = t.m7;

	this->m8 = t.m8;
	this->m9 = t.m9;
	this->m10 = t.m10;
	this->m11 = t.m11;
	
	this->m12 = t.m12;
	this->m13 = t.m13;
	this->m14 = t.m14;
	this->m15 = t.m15;
}

Matrix::~Matrix()
{
	
}

void Matrix::operator =(const Matrix& m)
{
	this->v0 = m.v0;
	this->v1 = m.v1;
	this->v2 = m.v2;
	this->v3 = m.v3;
}

void Matrix::setIdentMatrix()
{ 
	//this->m0 = 1.0;
	//this->m1 = 0.0;
	//this->m2 = 0.0;
	//this->m3 = 0.0;

	//this->m4 = 0.0;
	//this->m5 = 1.0;
	//this->m6 = 0.0;
	//this->m7 = 0.0;

	//this->m8 = 0.0;
	//this->m9 = 0.0;
	//this->m10 = 1.0;
	//this->m11 = 0.0;
	
	//this->m12 = 0.0;
	//this->m13 = 0.0;
	//this->m14 = 0.0;
	//this->m15 = 1.0;
	this->m0 = this->m5 = this->m10 = this->m15 = 1.0f;
}

void Matrix::setTransMatrix(Vect4D &t)
{ 
	this->m0 = 1.0f;
	//this->m1 = 0.0;
	//this->m2 = 0.0;
	//this->m3 = 0.0;

	//this->m4 = 0.0;
	this->m5 = 1.0f;
	//this->m6 = 0.0;
	//this->m7 = 0.0;

	//this->m8 = 0.0;
	//this->m9 = 0.0;
	this->m10 = 1.0f;
	//this->m11 = 0.0;
	
	this->m12 = t.x;
	this->m13 = t.y;
	this->m14 = t.z;
	this->m15 = 1.0f;
}

void Matrix::set( MatrixRow row, Vect4D &t )
{
	switch( row )
	{
	case MatrixRow::MATRIX_ROW_0:
		this->m0 = t.x;
		this->m1 = t.y;
		this->m2 = t.z;
		this->m3 = t.w;
		break;

	case MatrixRow::MATRIX_ROW_1:
		this->m4 = t.x;
		this->m5 = t.y;
		this->m6 = t.z;
		this->m7 = t.w;
		break;

	case MatrixRow::MATRIX_ROW_2:
		this->m8 = t.x;
		this->m9 = t.y;
		this->m10 = t.z;
		this->m11 = t.w;
		break;

	case MatrixRow::MATRIX_ROW_3:
		this->m12 = t.x;
		this->m13 = t.y;
		this->m14 = t.z;
		this->m15 = t.w;
		break;

	default:
		// should never get here, if we are here something bad has happened
		assert(0);
	}
}

const float&Matrix::operator[](Index e)
{
	// get the individual elements
	switch(e)
	{
	case Index::m0:
		return m0;
		break;
	case Index::m1:
		return m1;
		break;
	case Index::m2:
		return m2;
		break;
	case Index::m3:
		return m3;
		break;
	case Index::m4:
		return m4;
		break;
	case Index::m5:
		return m5;
		break;
	case Index::m6:
		return m6;
		break;
	case Index::m7:
		return m7;
		break;
	case Index::m8:
		return m8;
		break;
	case Index::m9:
		return m9;
		break;	
	case Index::m10:
		return m10;
		break;
	case Index::m11:
		return m11;
		break;	
	case Index::m12:
		return m12;
		break;	
	case Index::m13:
		return m13;
		break;	
	case Index::m14:
		return m14;
		break;
	case Index::m15:
		return m15;
		break;
	default:
		assert(0);
		return m0;
		break;
	}
}

void Matrix::get( MatrixRow row, Vect4D &t )const
{ // get a row of the matrix
	switch( row )
	{
	case MatrixRow::MATRIX_ROW_0:
		t.x = this->m0;
		t.y = this->m1;
		t.z = this->m2;
		t.w = this->m3;
		break;

	case MatrixRow::MATRIX_ROW_1:
		t.x = this->m4;
		t.y = this->m5;
		t.z = this->m6;
		t.w = this->m7;
		break;

	case MatrixRow::MATRIX_ROW_2:
		t.x = this->m8;
		t.y = this->m9;
		t.z = this->m10;
		t.w = this->m11;
		break;

	case MatrixRow::MATRIX_ROW_3:
		t.x = this->m12;
		t.y = this->m13;
		t.z = this->m14;
		t.w = this->m15;
		break;

	default:
		assert(0);
	}
}

Matrix Matrix::operator*( Matrix& rhs) 
{ 
	/*Matrix tmp;
	
	tmp.m0 = (m0*rhs.m0) + (m1*rhs.m4) + (m2*rhs.m8) + (m3*rhs.m12);
	tmp.m1 = (m0*rhs.m1) + (m1*rhs.m5) + (m2*rhs.m9) + (m3*rhs.m13);
	tmp.m2 = (m0*rhs.m2) + (m1*rhs.m6) + (m2*rhs.m10) + (m3*rhs.m14);
	tmp.m3 = (m0*rhs.m3) + (m1*rhs.m7) + (m2*rhs.m11) + (m3*rhs.m15);
	
	tmp.m4 = (m4*rhs.m0) + (m5*rhs.m4) + (m6*rhs.m8) + (m7*rhs.m12);
	tmp.m5 = (m4*rhs.m1) + (m5*rhs.m5) + (m6*rhs.m9) + (m7*rhs.m13);
	tmp.m6 = (m4*rhs.m2) + (m5*rhs.m6) + (m6*rhs.m10) + (m7*rhs.m14);
	tmp.m7 = (m4*rhs.m3) + (m5*rhs.m7) + (m6*rhs.m11) + (m7*rhs.m15);
	
	tmp.m8 = (m8*rhs.m0) + (m9*rhs.m4) + (m10*rhs.m8) + (m11*rhs.m12);
	tmp.m9 = (m8*rhs.m1) + (m9*rhs.m5) + (m10*rhs.m9) + (m11*rhs.m13);
	tmp.m10 = (m8*rhs.m2) + (m9*rhs.m6) + (m10*rhs.m10) + (m11*rhs.m14);
	tmp.m11 = (m8*rhs.m3) + (m9*rhs.m7) + (m10*rhs.m11) + (m11*rhs.m15);
	
	tmp.m12 = (m12*rhs.m0) + (m13*rhs.m4) + (m14*rhs.m8) + (m15*rhs.m12);
	tmp.m13 = (m12*rhs.m1) + (m13*rhs.m5) + (m14*rhs.m9) + (m15*rhs.m13);
	tmp.m14 = (m12*rhs.m2) + (m13*rhs.m6) + (m14*rhs.m10) + (m15*rhs.m14);
	tmp.m15 = (m12*rhs.m3) + (m13*rhs.m7) + (m14 *rhs.m11) + (m15*rhs.m15);

	return tmp;*/

	Matrix A;
	__m128 tmp;
	tmp = _mm_set1_ps(this->v0.x);
	A.v0.m = _mm_mul_ps(tmp, rhs.v0.m);
	tmp = _mm_set1_ps(this->v0.y);
	A.v0.m = _mm_add_ps(A.v0.m, _mm_mul_ps(tmp, rhs.v1.m));
	tmp = _mm_set1_ps(this->v0.z);
	A.v0.m = _mm_add_ps(A.v0.m, _mm_mul_ps(tmp, rhs.v2.m));
	tmp = _mm_set1_ps(this->v0.w);
	A.v0.m = _mm_add_ps(A.v0.m, _mm_mul_ps(tmp, rhs.v3.m));
	tmp = _mm_set1_ps(this->v1.x);
	A.v1.m = _mm_mul_ps(tmp, rhs.v0.m);
	tmp = _mm_set1_ps(this->v1.y);
	A.v1.m = _mm_add_ps(A.v1.m, _mm_mul_ps(tmp, rhs.v1.m));
	tmp = _mm_set1_ps(this->v1.z);
	A.v1.m = _mm_add_ps(A.v1.m, _mm_mul_ps(tmp, rhs.v2.m));
	tmp = _mm_set1_ps(this->v1.w);
	A.v1.m = _mm_add_ps(A.v1.m, _mm_mul_ps(tmp, rhs.v3.m));
	tmp = _mm_set1_ps(this->v2.x);
	A.v2.m = _mm_mul_ps(tmp, rhs.v0.m);
	tmp = _mm_set1_ps(this->v2.y);
	A.v2.m = _mm_add_ps(A.v2.m, _mm_mul_ps(tmp, rhs.v1.m));
	tmp = _mm_set1_ps(this->v2.z);
	A.v2.m = _mm_add_ps(A.v2.m, _mm_mul_ps(tmp, rhs.v2.m));
	tmp = _mm_set1_ps(this->v2.w);
	A.v2.m = _mm_add_ps(A.v2.m, _mm_mul_ps(tmp, rhs.v3.m));
	tmp = _mm_set1_ps(this->v3.x);
	A.v3.m = _mm_mul_ps(tmp, rhs.v0.m);
	tmp = _mm_set1_ps(this->v3.y);
	A.v3.m = _mm_add_ps(A.v3.m, _mm_mul_ps(tmp, rhs.v1.m));
	tmp = _mm_set1_ps(this->v3.z);
	A.v3.m = _mm_add_ps(A.v3.m, _mm_mul_ps(tmp, rhs.v2.m));
	tmp = _mm_set1_ps(this->v3.w);
	A.v3.m = _mm_add_ps(A.v3.m, _mm_mul_ps(tmp, rhs.v3.m));
	return A;
}

Matrix& Matrix::operator/=(const float rhs)
{ 
	// divide each element by a value
	// using inverse multiply trick, faster that individual divides
	float inv_rhs = 1.0f/rhs;

	/*m0 *= inv_rhs;
	m1 *= inv_rhs;
	m2 *= inv_rhs;
	m3 *= inv_rhs;
	m4 *= inv_rhs;
	m5 *= inv_rhs;
	m6 *= inv_rhs;
	m7 *= inv_rhs;
	m8 *= inv_rhs;
	m9 *= inv_rhs;
	m10 *= inv_rhs;
	m11 *= inv_rhs;
	m12 *= inv_rhs;
	m13 *= inv_rhs;
	m14 *= inv_rhs;
	m15 *= inv_rhs;*/

	Matrix A;
	__m128 tmp;

	tmp = _mm_set1_ps(inv_rhs);
	this->v0.m = _mm_mul_ps(tmp, this->v0.m);
	this->v1.m = _mm_mul_ps(tmp, this->v1.m);
	this->v2.m = _mm_mul_ps(tmp, this->v2.m);
	this->v3.m = _mm_mul_ps(tmp, this->v3.m);
	



	return *this;
}

const float Matrix::Determinant()
{
	float ta = (m10 * m15) - (m11 * m14);
	// tb = (kq - mo)
	float tb = (m9 * m15) - (m11 * m13);
	// tc = (kp - lo)
	float tc = (m9 * m14) - (m10 * m13);
	// td = (jq - mn)
	float td = (m8 * m15) - (m11 * m12);
	// te = (jo - kn)
	float te = (m8 * m13) - (m9 *  m12);
	// tf = (jp - ln)
	float tf = (m8 * m14) - (m10 * m12);
	
	return ((m0 * ((m5 * ta) - (m6 * tb) + (m7 * tc)))
			- (m1 * ((m4 * ta) - (m6 * td) + (m7 * tf)))
			+ (m2 * ((m4 * tb) - (m5 * td) + (m7 * te)))
			- (m3 * ((m4 * tc) - (m5 * tf) + (m6 * te))));
	
}

Matrix Matrix::GetAdjugate() 
{
	Matrix tmp;
	
	// load		ABC		(3)		ABC--
	float t1 = (m10*m15) - (m11*m14);
	float t2 = (m9*m15) - (m11*m13);
	float t3 = (m9*m14) - (m10*m13);
	
	// a = f(ta) - g(tb) + h(tc)
	tmp.m0 = (m5*t1) - (m6*t2) + (m7*t3);
	// b = -( b(ta) - c(tb) + d(tc))
	tmp.m1 = -((m1*t1) - (m2*t2) + (m3*t3));
	
	// load		JK		(5)		ABCJK
	float t4 = (m8*m15) - (m11*m12);
	float t5 = (m8*m14) - (m10*m12);
	// e = - ( e(ta) - g(tj) + h(tk))
	tmp.m4 = -( (m4*t1) - (m6*t4) + (m7*t5));
	// f = a(ta) - c(tj) + d(tk)
	tmp.m5 = (m0*t1) - (m2*t4) + (m3*t5);
	
	// unload	AJ		(3)		-BC-K
	// load		P		(4)		PBC-K
	t1 = (m8*m13) - (m9*m12);
	// n = -( e(tc) - f(tk) + g(tp))
	tmp.m12 = -((m4*t3) - (m5*t5) + (m6*t1));
	// o = a(tc) - b(tk) + c(tp)
	tmp.m13 = (m0*t3) - (m1*t5) + (m2*t1);
	
	// unload	KC		(2)		PB---
	// load		J		(3)		PBJ--
	t3 = (m8*m15) - (m11*m12);
	
	// j = e(tb) - f(tj) + h(tp)
	tmp.m8 = (m4*t2) - (m5*t3) + (m7*t1);
	// k = - ( a(tb) - b(tj) + d(tp))
	tmp.m9 = -((m0*t2) - (m1*t3) + (m3*t1));
	
	// unload	BPJ		(0)		-----
	// load		DLM		(3)		DLM--
	t1 = (m6*m15) - (m7*m14);
	t2 = (m4*m15) - (m7*m12);
	t3 = (m4*m14) - (m6*m12);
	
	// g = - ( a(td) - c(tl) + d(tm))
	tmp.m6 = -((m0*t1) - (m2*t2) + (m3*t3));
	
	// load		FR		(5)		DLMFR
	t4 = (m5*m14) - (m6*m13);
	t5 = (m4*m13) - (m5*m12);
	
	// p = - ( a(tf) - b(tm) + c(tr))
	tmp.m14 = -( (m0*t4) - (m1*t3) + (m3*t5));
	
	// unload	M		(4)		DL-FR
	// load		E		(5)		DLEFR
	t3 = (m5*m15) - (m7*m13);
	
	// l = a(te) - b(tl) + d(tr)
	tmp.m10 = (m0*t3) - (m1*t2) + (m3*t5);
	
	// unload	LR		(3)		D-EF-
	// c = b(td) - c(te) + d(tf)
	tmp.m2 = (m1*t1) - (m2*t3) + (m3*t4);
	
	// unload	DEF		(0)		-----
	// load		GHI		(3)		GHI--
	t1 = (m6*m11) - (m7*m10);
	t2 = (m5*m11) - (m7*m9);
	t3 = (m5*m10) - (m6*m9);
	
	// d = -( b(tg) - c(th) + d(ti) )
	tmp.m3 = -( (m1*t1) - (m2*t2) + (m3*t3));
	
	// load		NO		(5)		GHINO
	t4 = (m4*m11) - (m7*m8);
	t5 = (m4*m10) - (m6*m8);
	
	// h = a(tg) - c(tn) + d(to)
	tmp.m7 = (m0*t1) - (m2*t4) + (m3*t5);
	
	// unload	G		(4)		-HINO
	// load		Q		(5)		QHINO
	t1 = (m4*m9) - (m5*m8);
	
	// m = -( a(th) - b(tn) + d(tq))
	tmp.m11 = -((m0*t2) - (m1*t4) + (m3*t1));
	
	// unload	HN		(3)		Q-I-O
	// q = a(ti) - b(to) + c(tq)
	tmp.m15 = (m0*t3) - (m1*t5) + (m2*t1);
	
	return tmp;
}

void Matrix::Inverse( Matrix &out ) 
{
	//Matrix tmp;
	float det = Determinant();
	if(fabs(det) >= 0.0001f)
	{
		// do nothing, Matrix is not invertable
		out = GetAdjugate();
		out /= det;
	}
	

	//out = tmp;
}

void Matrix::setScaleMatrix(Vect4D &scale)
{
	//	{	sx		0		0		0	}
	//	{	0		sy		0		0	}
	//	{	0		0		sz		0	}
	//	{	0		0		0		1	}
	
	//Matrix tmp;
	this->m0 = scale.x;
	//this->m1 = 0;
	//this->m2 = 0;
	//this->m3 = 0;
	
	//this->m4 = 0;
	this->m5 = scale.y;
	//this->m6 = 0;
	//his->m7 = 0;
	
	//this->m8 = 0;
	//this->m9 = 0;
	this->m10 = scale.z;
	//this->m11 = 0;
	
	//this->m12 = 0;
	//this->m13 = 0;
	//this->m14 = 0;
	this->m15 = 1.0f;
}

void Matrix::setRotZMatrix(float& az)
{
	//	{	cos		-sin	0		0	}
	//	{	sin		cos		0		0	}
	//	{	0		0		1		0	}
	//	{	0		0		0		1	}
	
	Matrix tmp;
	tmp.m0 = cos(az);
	tmp.m1 = -sin(az);
	//tmp.m2 = 0;
	//tmp.m3 = 0;
	
	tmp.m4 = sin(az);
	tmp.m5 = cos(az);
	//tmp.m6 = 0;
	//tmp.m7 = 0;
	
	//tmp.m8 = 0;
	//tmp.m9 = 0;
	tmp.m10 = 1.0f;
	//tmp.m11 = 0;
	
	//tmp.m12 = 0;
	//tmp.m13 = 0;
	//tmp.m14 = 0;
	tmp.m15 = 1.0f;
	
	*this = tmp;
}

// --- End of File ---

void Matrix::setTmpInMain() 
{
	this->m0 = 1.0f;
	this->m5 = 1.0f;
	this->m10 = 1.0f;
	this->m13 = 3.0f;
	this->m14 = 10.0f;
	this->m15 = 1.0f;
}

void Matrix::setInverseCameraMatrixInDraw()
{
	this->m0 = 1.0f;
	this->m1 = -0.0f;
	this->m3 = -0.0f;
	this->m4 = -0.0f;
	this->m5 = 1.0f;
	this->m6 = -0.0f;
	this->m9 = -0.0f;
	this->m10 = 1.0f;
	this->m11 = -0.0f;
	this->m12 = -0.0f;
	this->m13 = -3.0f;
	this->m14 = -10.0f;
	this->m15 = 1.0f;
}
void Matrix::setTransCameraInDraw()
{
	this->m0 = 1.0f;
	this->m5 = 1.0f;
	this->m10 = 1.0f;
	this->m12 = -0.0f;
	this->m13 = -3.0f;
	this->m14 = -10.0f;
	this->m15 = 1.0f;
}

Matrix Matrix::fiveMatrixMul(Matrix& a, Matrix& b, Matrix& c, Matrix& d, Matrix& e)
{
	Matrix A;
	Matrix B;
	Matrix C;
	Matrix D;
	__m128 tmp;
	A.m0 = a.m0 * b.m0 + a.m1 * b.m4 + a.m2 * b.m8 + a.m3 * b.m12;
	A.m1 = a.m0 * b.m1 + a.m1 * b.m5 + a.m2 * b.m9 + a.m3 * b.m13;
	A.m4 = a.m0 * b.m4 + a.m5 * b.m4 + a.m6 * b.m8 + a.m7 * b.m12;
	A.m5 = a.m4 * b.m1 + a.m5 * b.m5 + a.m6 * b.m9 + a.m7 * b.m13;
	A.m10 = a.m8 * b.m2 +a.m9 * b.m6 + a.m10 * b.m10 + a.m11 * b.m14;
	//A.m12 = a.m0 * b.m4 +a.m5 * b.m4 + a.m6 * b.m8 + a.m7 * b.m12;

	tmp = _mm_set1_ps(a.v3.x);
	A.v3.m = _mm_mul_ps(tmp, b.v0.m);
	tmp = _mm_set1_ps(a.v3.y);
	A.v3.m = _mm_add_ps(A.v3.m, _mm_mul_ps(tmp, b.v1.m));
	tmp = _mm_set1_ps(a.v3.z);
	A.v3.m = _mm_add_ps(A.v3.m, _mm_mul_ps(tmp, b.v2.m));
	tmp = _mm_set1_ps(a.v3.w);
	A.v3.m = _mm_add_ps(A.v3.m, _mm_mul_ps(tmp, b.v3.m));

	
	//====a*b


	B.m0 = c.m0 * d.m0 + c.m1 * d.m4 + c.m2 * d.m8 + c.m3 * d.m12;
	B.m1 = c.m0 * d.m1 + c.m1 * d.m5 + c.m2 * d.m9 + c.m3 * d.m13;
	B.m4 = c.m0 * d.m4 + c.m5 * d.m4 + c.m6 * d.m8 + c.m7 * d.m12;
	B.m5 = c.m4 * d.m1 + c.m5 * d.m5 + c.m6 * d.m9 + c.m7 * d.m13;
	B.m10 = c.m8 * d.m2 +c.m9 * d.m6 + c.m10 * d.m10 + c.m11 * d.m14;
	//B.m12 = c.m0 * d.m4 +c.m5 * d.m4 + c.m6 * d.m8 + c.m7 * d.m12;

	tmp = _mm_set1_ps(c.v3.x);
	B.v3.m = _mm_mul_ps(tmp, d.v0.m);
	tmp = _mm_set1_ps(c.v3.y);
	B.v3.m = _mm_add_ps(B.v3.m, _mm_mul_ps(tmp, d.v1.m));
	tmp = _mm_set1_ps(c.v3.z);
	B.v3.m = _mm_add_ps(B.v3.m, _mm_mul_ps(tmp, d.v2.m));
	tmp = _mm_set1_ps(c.v3.w);
	B.v3.m = _mm_add_ps(B.v3.m, _mm_mul_ps(tmp, d.v3.m));
	//===c*d

	C.m0 = A.m0 * B.m0 + A.m1 * B.m4 + A.m2 * B.m8 + A.m3 * B.m12;
	C.m1 = A.m0 * B.m1 + A.m1 * B.m5 + A.m2 * B.m9 + A.m3 * B.m13;
	C.m4 = A.m0 * B.m4 + A.m5 * B.m4 + A.m6 * B.m8 + A.m7 * B.m12;
	C.m5 = A.m4 * B.m1 + A.m5 * B.m5 + A.m6 * B.m9 + A.m7 * B.m13;
	C.m10 = A.m8 * B.m2 + A.m9 * B.m6 + A.m10 * B.m10 + A.m11 * B.m14;
	//C.m12 = A.m0 * B.m4 + A.m5 * B.m4 + A.m6 * B.m8 + A.m7 * B.m12;

	tmp = _mm_set1_ps(A.v3.x);
	C.v3.m = _mm_mul_ps(tmp, B.v0.m);
	tmp = _mm_set1_ps(A.v3.y);
	C.v3.m = _mm_add_ps(C.v3.m, _mm_mul_ps(tmp, B.v1.m));
	tmp = _mm_set1_ps(A.v3.z);
	C.v3.m = _mm_add_ps(C.v3.m, _mm_mul_ps(tmp, B.v2.m));
	tmp = _mm_set1_ps(A.v3.w);
	C.v3.m = _mm_add_ps(C.v3.m, _mm_mul_ps(tmp, B.v3.m));
	//===  C = (a*b)*(c*d) 

	D.m0 = C.m0 * e.m0 + C.m1 * e.m4 + C.m2 * e.m8 + C.m3 * e.m12;
	D.m1 = C.m0 * e.m1 + C.m1 * e.m5 + C.m2 * e.m9 + C.m3 * e.m13;
	D.m4 = C.m0 * e.m4 + C.m5 * e.m4 + C.m6 * e.m8 + C.m7 * e.m12;
	D.m5 = C.m4 * e.m1 + C.m5 * e.m5 + C.m6 * e.m9 + C.m7 * e.m13;
	D.m10 = C.m8 * e.m2 + C.m9 * e.m6 + C.m10 * e.m10 + C.m11 * e.m14;
	//D.m12 = C.m0 * e.m4 + C.m5 * e.m4 + C.m6 * e.m8 + C.m7 * e.m12;

	tmp = _mm_set1_ps(C.v3.x);
	D.v3.m = _mm_mul_ps(tmp, e.v0.m);
	tmp = _mm_set1_ps(C.v3.y);
	D.v3.m = _mm_add_ps(D.v3.m, _mm_mul_ps(tmp, e.v1.m));
	tmp = _mm_set1_ps(C.v3.z);
	D.v3.m = _mm_add_ps(D.v3.m, _mm_mul_ps(tmp, e.v2.m));
	tmp = _mm_set1_ps(C.v3.w);
	D.v3.m = _mm_add_ps(D.v3.m, _mm_mul_ps(tmp, e.v3.m));
	//=== (a*b)*(c*d) * e

	return D;
}