//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : class colon
//*******************

#pragma once
#include "Unite.hpp"
#include "Ville.hpp"


enum
{
	Colon_INIT,
	Colon_deplacement,
	Colon_creer_ville,
	Colon_MORT,
};


class Ccolon : public Cunit
{


protected :

	virtual bool States( StateMachineEvent event, int state ) ;
	virtual FSM* Clone(){return NULL;} ;
	virtual std::string GetName(){ return "Cguerrier";};

	int m_posVilleaConstruire_x ;
	int m_posVilleaConstruire_y ;


public :

	Ccolon(unsigned int _x, unsigned int _y) ;
	virtual ~Ccolon(){};

	bool AunePositionPourConstruire(){  if(m_posVilleaConstruire_x >=0 ){return true;} return false;    } ;

	void setPositionAconstruire(int _x, int _y){m_posVilleaConstruire_x = _x ; m_posVilleaConstruire_y = _y ;};

	bool ColonEnPosition(){  if( m_posVilleaConstruire_x== m_posTabX && m_posVilleaConstruire_y == m_posTabY ){ return true;  }  return false;  };


	Cville* construire(){return new Cville(m_posTabX,m_posTabY);};

};