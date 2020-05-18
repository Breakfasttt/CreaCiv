//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : class guerrier
//*******************


#pragma once
#include "Unite.hpp"


enum
{
	GUERRIER_INIT,
	GUERRIER_DEPLACEMENT,
	GUERRIER_MORT,
};


class Cguerrier : public Cunit
{


protected :

	virtual bool States( StateMachineEvent event, int state ) ;
	virtual FSM* Clone(){return NULL;} ;
	virtual std::string GetName(){ return "Cguerrier";};


public :

	Cguerrier(unsigned int _x, unsigned int _y) ;
	virtual ~Cguerrier(){};


};