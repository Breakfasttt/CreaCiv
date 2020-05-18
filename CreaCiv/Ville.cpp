//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : class guerrier
//*******************



#include "Ville.hpp"


Cville::Cville(unsigned int _x, unsigned int _y)
{
	m_posTabX = _x ; 
	m_posTabY = _y;

	m_TypeUnite = T_Unite::U_Ville;

	sf::Texture* Temp = DATA->getTextureByName("UNIT_VILLE");

	if ( Temp)
		m_SpiteUnite.setTexture(*Temp);

}

bool Cville::States( StateMachineEvent event, int state )
{
	BeginStateMachine

		//*********** Begin state ************
		State(Ville_INIT)
	OnEnter
		LOG("Cville  : Ville_INIT");
		SetState(ville_creer);
		m_end = false;
	OnUpdate
	OnExit
		//*********** End state ************


		//*********** Begin state ************
		State(ville_creer)
	OnEnter
		LOG("Cville  : ville_creer");
		
	OnUpdate


		if( C_Militaire == m_monOrdre )
			m_bGuerrier_creer = true;


		SetState(ville_MORT);
	OnExit
		//*********** End state ************


		//*********** Begin state ************
		State(ville_MORT)
	OnEnter
		LOG("Cville  : ville_MORT");
		m_end = true;
	OnUpdate
	OnExit
		//*********** End state ************


	EndStateMachine
}