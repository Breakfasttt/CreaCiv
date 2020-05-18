//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : class d'unite
//*******************


#pragma once

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"
#include "FSM.hpp"
#include "Map.hpp"

#include "InfosIa.hpp"


class Cunit : public FSM
{

public :


	Cunit(){};
	virtual ~Cunit(){};


	T_Unite getType(){return m_TypeUnite;};

	unsigned int getposTabX(){return m_posTabX;};
	unsigned int getposTabY(){return m_posTabY;};

	void RenderUnit(){RENDER->draw(m_SpiteUnite);};
	void ActualisePosition(sf::Vector2f _ancre){

												float X = m_posTabX * PIXELSIZE + _ancre.x ;
												float Y = m_posTabY * PIXELSIZE + _ancre.y ;

												m_SpiteUnite.setPosition(X,Y);
												};

	T_ordre getOrdre(){return m_monOrdre;};
	void setOrdre(T_ordre _ordre) { m_monOrdre = _ordre ;  } ;


protected :

	sf::Sprite m_SpiteUnite;
	T_Unite m_TypeUnite;
	T_ordre m_monOrdre;

	unsigned int m_posTabX;
	unsigned int m_posTabY;

	// Fonction FSM
	virtual bool States( StateMachineEvent event, int state ){return false;} ;
	virtual FSM* Clone(){return NULL;} ;
	virtual std::string GetName(){ return "Cunit";};

};


