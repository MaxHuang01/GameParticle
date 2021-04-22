//---------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#include "OpenGLDevice.h"
#include "ParticleEmitter.h"
#include "Settings.h"

PerformanceTimer globalTimer;

ParticleEmitter::ParticleEmitter()
:	start_position( 0.0f, 0.0f, 0.0f ),
	start_velocity( 0.0f, 1.0f, 0.0f), 
	max_life( MAX_LIFE ),
	max_particles( NUM_PARTICLES ),
	last_active_particle( -1 ),
	spawn_frequency(0.0000001f),
	last_spawn(globalTimer.GetGlobalTime()),
	last_loop(globalTimer.GetGlobalTime()),
	headParticle(0),
	vel_variance(1.0f, 4.0f, 0.4f),
	pos_variance(1.0f, 1.0f, 1.0f),
	scale_variance(2.5f)
	//particle_list(NUM_PARTICLES)
{
	// nothing to do
	//bufferCount = 0;
}

ParticleEmitter::~ParticleEmitter()
{
	Particle *pTmp = this->headParticle;
	
	while (pTmp != nullptr)
	{
		Particle *pDeleteMe = pTmp;
		pTmp = pTmp->next;
		delete pDeleteMe;
	}
}

void ParticleEmitter::SpawnParticle()
{
	// create another particle if there are ones free
	if( last_active_particle < max_particles-1 )
	{
	
		// create new particle
		Particle* buffer = (Particle*)_aligned_malloc(sizeof(Particle) * 1, 16);
		AZUL_PLACEMENT_NEW_BEGIN
		#undef new
		Particle *newParticle = new(spawn) Particle();
		AZUL_PLACEMENT_NEW_END
		// initialize the particle
		newParticle->life     = 0.0f;
		newParticle->position = start_position;
		newParticle->velocity = start_velocity;
		newParticle->scale    = Vect4D(1.0f, 1.0f, 1.0f, 1.0f);

		// apply the variance
		this->Execute(newParticle->position, newParticle->velocity, newParticle->scale);

		// increment count
		last_active_particle++;

		// add to list
		this->addParticleToList( *newParticle );
		spawn++;

	}
}

void ParticleEmitter::update()
{
	// get current time
	float current_time = globalTimer.GetGlobalTime();

	// spawn particles
	float time_elapsed = current_time - last_spawn;
	
	// update
	while( spawn_frequency < time_elapsed )
	{
		// spawn a particle
		this->SpawnParticle();
		// adjust time
		time_elapsed -= spawn_frequency;
		
		
	}
	last_spawn = current_time;
	// total elapsed
	// last time
	time_elapsed = current_time - last_loop;

	Particle *p = this->headParticle;
	int index = 0;
	// walk the particles

	while( p!= 0 )
	{
		//// call every particle and update its position 
		//p->Update(time_elapsed);

		//// if it's live is greater that the max_life 
		//// and there is some on the list
		//// remove node
		//if((p->life > max_life) && (last_active_particle > 0))
		//{
		//	// particle to remove
		//	Particle *s = p;

		//	// need to squirrel it away.
		//	p=p->next;

		//	// remove last node
		//	this->removeParticleFromList( s );

		//	// update the number of particles
		//	last_active_particle--;
		//}
		//else
		//{
		//	// increment to next point
		//	p = p->next;
		//}

		if (p->life < max_life)
		{
			p->Update(time_elapsed);
		}
		else
		{
			p->life = 0.0f;
			p->position = start_position;
			p->velocity = start_velocity;
			p->scale.set(1.0f);
			this->Execute(p->position, p->velocity, p->scale);
		}
		*(drawBuffer + index) = *p;
		p = p->next;
		index++;
	}

	//move a copy to vector for faster iterations in draw
	p = this->headParticle;
	//bufferCount = 0;

	// clear the buffer
	//drawBuffer.clear();

	// walk the pointers, add to list
	//int index = 0;
	//while(p != 0)
	//{
	//	// add to buffer
	//	//drawBuffer[index] = *p;
	//	
	//	//drawBuffer.push_back(*p);

	//	// advance ptr
	//	*(drawBuffer + index) = *p;
	//	p = p->next;
	//	index++;
	//	// track the current count
	//	//bufferCount++;
	//	
	//}

	// make sure the counts track (asserts go away in release - relax Christos)
	//assert(bufferCount == (last_active_particle+1));
	last_loop = current_time;
}
	   
void ParticleEmitter::addParticleToList(Particle &const p )
{
	//assert(p);
	if( this->headParticle == 0 )
	{ // first on list
		this->headParticle = &p;
		p.next = 0;
		p.prev= 0;
	}
	else 
	{ // add to front of list
		headParticle->prev = &p;
		p.next = headParticle;
		p.prev = 0;
		headParticle = &p;
	}

}

void ParticleEmitter::removeParticleFromList( Particle &p )
{
	// make sure we are not screwed with a null pointer
	//assert(p);

	if( p.prev == 0 && p.next == 0  )
	{ // only one on the list
		this->headParticle = 0;
	}
	else if( p.prev == 0 && p.next != 0  )
	{ // first on the list
		p.next->prev = 0;
		this->headParticle = p.next;
	}
	else if( p.prev!= 0 && p.next == 0 )
	{ // last on the list 
		p.prev->next = 0;
	}
	else//( p->next != 0  && p->prev !=0 )
	{ // middle of the list
		p.prev->next = p.next;
		p.next->prev = p.prev;
	}
	
	// bye bye
	delete &p;
}

void ParticleEmitter::draw()
{
	//// initialize the camera matrix
	//Matrix cameraMatrix;
	//cameraMatrix.setIdentMatrix();

	//// setup the translation matrix
	//Matrix transMatrix;
	//Vect4D trans(0.0f, 3.0f, 10.0f);
	//transMatrix.setTransMatrix(&trans);

	//Matrix tmp;
	//// multiply them together
	//tmp = cameraMatrix * transMatrix;

	//// get the inverse matrix
	//Matrix inverseCameraMatrix;
	//tmp.Inverse(inverseCameraMatrix);
	Matrix tmp;
	/*Matrix inverseCameraMatrix;
	inverseCameraMatrix.setInverseCameraMatrixInDraw();*/
	// iterate throught the list of particles
	//std::list<Particle>::iterator it;
	//for( it = drawBuffer.begin(); it != drawBuffer.end(); ++it)
	//{
	//	// get the position from this matrix
	//	Vect4D camPosVect;
	//	inverseCameraMatrix.get( Matrix::MatrixRow::MATRIX_ROW_3, &camPosVect );

	//	// camera position
	//	Matrix transCamera;
	//	transCamera.setTransMatrix( &camPosVect );

	//	// particle position
	//	Matrix transParticle;
	//	transParticle.setTransMatrix( &it->position );

	//	// rotation matrix
	//	Matrix rotParticle;
	//	rotParticle.setRotZMatrix( it->rotation );

	//	// pivot Point
	//	Matrix pivotParticle;
	//	Vect4D pivotVect;
	//	pivotVect.set(1.0, 0.0, 50.0);
	//	pivotVect = pivotVect * 20.0 * it->life;
	//	pivotParticle.setTransMatrix( &pivotVect );

	//	// scale Matrix
	//	Matrix scaleMatrix;
	//	scaleMatrix.setScaleMatrix( &it->scale );

	//	// total transformation of particle
	//	tmp = scaleMatrix * transCamera * transParticle * rotParticle * scaleMatrix;

	//	// ------------------------------------------------
	//	//  Set the Transform Matrix and Draws Triangle
	//	//  Note: 
	//	//       this method is using doubles... 
	//	//       there is a float version (hint)
	//	// ------------------------------------------------
	//	OpenGLDevice::SetTransformMatrixDouble((const double *)&tmp);

	//	// squirrel away matrix for next update
	//	tmp.get(Matrix::MatrixRow::MATRIX_ROW_0, &it->curr_Row0 );
	//	tmp.get(Matrix::MatrixRow::MATRIX_ROW_1, &it->curr_Row1 );
	//	tmp.get(Matrix::MatrixRow::MATRIX_ROW_2, &it->curr_Row2 );
	//	tmp.get(Matrix::MatrixRow::MATRIX_ROW_3, &it->curr_Row3 );

	//	// difference vector
	//	it->diff_Row0 = it->curr_Row0 - it->prev_Row0;
	//	it->diff_Row1 = it->curr_Row1 - it->prev_Row1;
	//	it->diff_Row2 = it->curr_Row2 - it->prev_Row2;
	//	it->diff_Row3 = it->curr_Row3 - it->prev_Row3;

	//	// clears or flushes some internal setting, used in debug, but is need for performance reasons
	//	// magic...  really it's magic.
	////	GLenum glError = glGetError();
	////	assert(glError == 0);
	//	//AZUL_UNUSED_VAR(glError);
	//}

	

	//Vect4D camPosVect;
	Matrix transCamera;
	Matrix transParticle;
	Matrix rotParticle;
	//Matrix pivotParticle;
	//Vect4D pivotVect;
	Matrix scaleMatrix;
	Particle* pDraw = drawBuffer;
	//inverseCameraMatrix.get(Matrix::MatrixRow::MATRIX_ROW_3, &camPosVect);
	//transCamera.setTransMatrix(&camPosVect);
	transCamera.setTransCameraInDraw();
	for (int index1 = 0; index1 <=99999; ++index1)
	{
		pDraw = (drawBuffer + index1);
		

		// get the position from this matrix
		
		

		// camera position
		
		

		// particle position
		
		transParticle.setTransMatrix(pDraw->position);

		// rotation matrix
		
		rotParticle.setRotZMatrix(pDraw->rotation);

		// pivot Point
		
		/*pivotVect.set(1.0f, 0.0f, 50.0f);
		pivotVect = pivotVect * 20.0f * pDraw->life;
		pivotParticle.setTransMatrix(&pivotVect);*/

		// scale Matrix
		
		scaleMatrix.setScaleMatrix(pDraw->scale);

		// total transformation of particle
		tmp = scaleMatrix * transCamera * transParticle * rotParticle * scaleMatrix;
		//tmp = tmp.fiveMatrixMul(scaleMatrix, transCamera, transParticle, rotParticle, scaleMatrix);
		// ------------------------------------------------
		//  Set the Transform Matrix and Draws Triangle
		//  Note: 
		//       this method is using doubles... 
		//       there is a float version (hint)
		// ------------------------------------------------
		OpenGLDevice::SetTransformMatrixFloat((const float*)&tmp);

		// squirrel away matrix for next update
		tmp.get(Matrix::MatrixRow::MATRIX_ROW_0, pDraw->curr_Row0);
		tmp.get(Matrix::MatrixRow::MATRIX_ROW_1, pDraw->curr_Row1);
		tmp.get(Matrix::MatrixRow::MATRIX_ROW_2, pDraw->curr_Row2);
		tmp.get(Matrix::MatrixRow::MATRIX_ROW_3, pDraw->curr_Row3);


		// difference vector
		pDraw->diff_Row0 = pDraw->curr_Row0 - pDraw->prev_Row0;
		pDraw->diff_Row1 = pDraw->curr_Row1 - pDraw->prev_Row1;
		pDraw->diff_Row2 = pDraw->curr_Row2 - pDraw->prev_Row2;
		pDraw->diff_Row3 = pDraw->curr_Row3 - pDraw->prev_Row3;

		// clears or flushes some internal setting, used in debug, but is need for performance reasons
		// magic...  really it's magic.
	//	GLenum glError = glGetError();
	//	assert(glError == 0);
		//AZUL_UNUSED_VAR(glError);
		
	}

	

	// delete the buffer
	/*for( size_t i = 0; i < drawBuffer.size(); i++ )
	{
		drawBuffer.pop_back();
	}*/

	// done with buffer, clear it.
	//drawBuffer.clear();
}

void ParticleEmitter::Execute(Vect4D& const pos, Vect4D& const vel, Vect4D& const sc)
{
	// Ses it's ugly - I didn't write this so don't bitch at me
	// Sometimes code like this is inside real commerical code ( so now you know how it feels )
	
	// x - variance
	float var = static_cast<float>(rand() % 1000) * 0.001f;
	float sign = static_cast<float > (rand() % 2);
	float*t_pos = reinterpret_cast<float*>(&pos);
	float*t_var = &pos_variance[Vect::x];
	if(sign == 0)
	{
		var *= -1.0;
	}
	*t_pos += *t_var * var;

	// y - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;
	
	// z - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;
	
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	
	// x  - add velocity
	t_pos = &vel[Vect::x];
	t_var = &vel_variance[Vect::x];
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;
	
	// y - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;
	
	// z - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	t_var++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += *t_var * var;
	
	// correct the sign
	var = 2.0f * static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	
	if(sign == 0)
	{
		var *= -1.0f;
	}
	sc = sc * var;

	
}

// --- End of File ---
