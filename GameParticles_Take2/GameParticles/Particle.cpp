//---------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#include "Particle.h"
#include "Matrix.h"

Particle::Particle()
{
	// construtor
	this->life = 0.0f;
	this->position.set( 0.0f);
	this->velocity.set( 0.0f );
	this->scale.set( 1.0f );
	this->rotation = 0.0f;
	this->rotation_velocity = 0.5f;
	this->next = nullptr;
	this->prev = nullptr;
}

Particle::~Particle()
{
	// nothing to do
}

void Particle::CopyDataOnly( const Particle &p )
{
	// copy the data only
	// this way of copying data is more efficient that element by element
	this->position = p.position;
	this->velocity = p.velocity;
	this->scale    = p.scale;
	this->rotation = p.rotation;
	this->rotation_velocity = p.rotation_velocity;
	this->life     = p.life;
}

void Particle::Update(const float& time_elapsed)
{
	// Rotate the matrices
	/*Vect4D tmp_Row0;
	tmp_Row0 = curr_Row0;
	prev_Row0 = tmp_Row0;

	Vect4D tmp_Row1;
	tmp_Row1 = curr_Row1;
	prev_Row1 = tmp_Row1;

	Vect4D tmp_Row2;
	tmp_Row2 = curr_Row2;
	prev_Row2 = tmp_Row2;

	Vect4D tmp_Row3;
	tmp_Row3 = curr_Row3;
	prev_Row3 = tmp_Row3;*/

	
	
	prev_Row0 = curr_Row0;

	prev_Row1 = curr_Row1;

	prev_Row2 = curr_Row2;

	prev_Row3 = curr_Row3;

	Matrix tmp;

	tmp.set(Matrix::MatrixRow::MATRIX_ROW_0, this->diff_Row0);
	tmp.set(Matrix::MatrixRow::MATRIX_ROW_1, this->diff_Row1);
	tmp.set(Matrix::MatrixRow::MATRIX_ROW_2, this->diff_Row2);
	tmp.set(Matrix::MatrixRow::MATRIX_ROW_3, this->diff_Row3);

	float MatrixScale = tmp.Determinant();

	// serious math below - magic secret sauce
	life += time_elapsed;
	position = position + (velocity * time_elapsed);
	Vect4D z_axis(0.0f, -0.25f, 1.0f);
	Vect4D v(3,4,0);
	position.Cross( z_axis, v);
	v.norm(v);
	position = position + v * 0.05f * life;

	if( MatrixScale > 1.0f )
	{
		MatrixScale = 1.0f/MatrixScale;
	};

	rotation = rotation + MatrixScale + rotation_velocity * time_elapsed *2.01f;
}

void Particle::operator=(const Particle& p) 
{
	this->next = p.next;
	this->prev = p.prev;

	this->prev_Row0 = p.prev_Row0;
	this->prev_Row1 = p.prev_Row1;
	this->prev_Row2 = p.prev_Row2;
	this->prev_Row3 = p.prev_Row3;

	this->position = p.position;
	this->life = p.life;
	this->rotation = p.rotation;
	this->velocity = p.velocity;
	this->scale = p.scale;

	this->diff_Row0 = p.diff_Row0;
	this->diff_Row1 = p.diff_Row1;
	this->diff_Row2 = p.diff_Row2;
	this->diff_Row3 = p.diff_Row3;
	this->rotation_velocity = p.rotation_velocity;
	this->pad1 = this->pad2 = this->pad3 = this->pad4 = p.pad1;
	


	this->curr_Row0 = p.curr_Row0;
	this->curr_Row1 = p.curr_Row1;
	this->curr_Row2 = p.curr_Row2;
	this->curr_Row3 = p.curr_Row3;

}

// --- End of File ---
