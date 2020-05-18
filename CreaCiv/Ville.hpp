//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : class ville
//*******************

#pragma once
#include "Unite.hpp"
#include "Guerrier.hpp"


enum
{
	Ville_INIT,
	ville_creer,
	ville_MORT,
};


class Cville : public Cunit
{
	

protected :

	virtual bool States( StateMachineEvent event, int state ) ;
	virtual FSM* Clone(){return NULL;} ;
	virtual std::string GetName(){ return "Cguerrier";};


	bool m_bGuerrier_creer;

public :

	Cville(unsigned int _x, unsigned int _y) ;
	virtual ~Cville(){};


	bool getGuerrierCreer(){return m_bGuerrier_creer;};
	void setGuerrierCreer(bool _b){m_bGuerrier_creer = _b;}

	Cguerrier* CreerGuerrier(){return new Cguerrier(m_posTabX,m_posTabY);};

};