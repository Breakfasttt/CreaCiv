//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : class guerrier
//*******************



#include "Guerrier.hpp"

Cguerrier::Cguerrier(unsigned int _x, unsigned int _y)
{
	m_posTabX = _x ; 
	m_posTabY = _y;

	m_TypeUnite = T_Unite::U_Soldat;

	sf::Texture* Temp = DATA->getTextureByName("UNIT_GUERRIER");

	if ( Temp)
		m_SpiteUnite.setTexture(*Temp);

}

bool Cguerrier::States( StateMachineEvent event, int state )
{
	BeginStateMachine

		//*********** Begin state ************
		State(GUERRIER_INIT)
	OnEnter
		LOG("Cguerrier  : GUERRIER_INIT");
		SetState( GUERRIER_DEPLACEMENT ) ;
		m_end = false;

	OnUpdate
	OnExit
		//*********** End state ************


		//*********** Begin state ************
		State(GUERRIER_DEPLACEMENT)
	OnEnter
		LOG("Cguerrier  : GUERRIER_DEPLACEMENT");
		
		

	OnUpdate


		if ( T_ordre::M_Exploration == m_monOrdre )
		{
			int x = ( rand()%3 ) - 1 ;
			int y = ( rand()%3 ) - 1 ;

			if ( !(m_posTabX == 0 && x <0) )
				m_posTabX += x;

			if(  !(m_posTabY == 0 && y < 0) )
				m_posTabY += y;

			if(  m_posTabX > SIZEX-1 )
				m_posTabX = SIZEX-1 ;


			if(  m_posTabY > SIZEY-1 )
				m_posTabY = SIZEY-1 ;
		}


		SetState( GUERRIER_MORT ) ;

	OnExit
		//*********** End state ************


		//*********** Begin state ************
		State(GUERRIER_MORT)
	OnEnter
		LOG("Cguerrier  : GUERRIER_MORT");
		m_end = true;
	OnUpdate
	OnExit
		//*********** End state ************


	EndStateMachine
}
