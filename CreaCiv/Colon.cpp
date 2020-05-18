//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : class colon
//*******************



#include "Colon.hpp"


Ccolon::Ccolon(unsigned int _x, unsigned int _y)
{

	m_posTabX = _x ; 
	m_posTabY = _y;
	m_posVilleaConstruire_x = -1 ; 
	m_posVilleaConstruire_y = -1;

	m_TypeUnite = T_Unite::U_Colon;


	sf::Texture* Temp = DATA->getTextureByName("UNIT_COLON");

	if ( Temp)
		m_SpiteUnite.setTexture(*Temp);
}


bool Ccolon::States( StateMachineEvent event, int state )
{
	BeginStateMachine

		//*********** Begin state ************
		State(Colon_INIT)
	OnEnter
		LOG("Ccolon  : Colon_INIT");

		m_end = false;
		SetState( Colon_deplacement ) ;

	OnUpdate
	OnExit
		//*********** End state ************


		//*********** Begin state ************
		State(Colon_deplacement)
	OnEnter
		LOG("Ccolon  : Colon_deplacement");
		
		SetState( Colon_creer_ville ) ;

	OnUpdate
	OnExit
		//*********** End state ************



		//*********** Begin state ************
		State(Colon_creer_ville)
	OnEnter
		LOG("Ccolon  : Colon_creer_ville");
		SetState( Colon_MORT ) ;
	OnUpdate
	OnExit
		//*********** End state ************

		//*********** Begin state ************
		State(Colon_MORT)
	OnEnter
		LOG("Ccolon  : Colon_MORT");
		m_end = true;
	OnUpdate
	OnExit
		//*********** End state ************


	EndStateMachine
}