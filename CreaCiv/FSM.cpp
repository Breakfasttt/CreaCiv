//@@@@@@@@@@@@@@@@@@@
// Auteur : Portions Copyright (C) Steve Rabin, 2001. adapté par Y.Colaisseau
// Date : 06/02/2013 - 14h38
// Fichier : définition du singleton dataCenter  .hpp
// Dernière modification : 06/02/2013
//@@@@@@@@@@@@@@@@@@@

#include "FSM.hpp"
#include <iostream>



FSM::FSM( void ) : m_ListState()
{
	m_end = false;
	m_MaxRegistedState = 50 ;
	m_currentState = 0;
	m_stateChange = false;
	m_nextState = false;
	m_ListState.push_back(m_currentState);
}


void FSM::Initialize( void )
{
	Process( EVENT_Enter );
}


void FSM::Update( void )
{
	Process( EVENT_Update );
}


void FSM::Process( StateMachineEvent event )
{
	States( event, m_currentState );

	// Check for a state change
	int safetyCount = 10;
	while( m_stateChange && (--safetyCount >= 0) )
	{
		//assert( safetyCount > 0 && "StateMachine::Process - States are flip-flopping in an infinite loop." );

		m_stateChange = false;

		// Let the last state clean-up
		States( EVENT_Exit, m_currentState );

		// Set the new state
		m_currentState = m_nextState;	
		m_ListState.push_back(m_currentState);

		// Let the new state initialize
		States( EVENT_Enter, m_currentState );
	}

}


void FSM::SetState( unsigned int newState )
{
	m_stateChange = true;
	m_nextState = newState;
}


void FSM::AfficheHistorique()
{
	std::list<unsigned int>::iterator it;
	int i =0;

	std::cout << std::endl << "#############" << std::endl << std::endl ;

	for(it = m_ListState.begin() ; it != m_ListState.end();  ++it)
	{
		std::cout << "etat n°:"<< i << " : " << (*it) << std::endl;
		i++;
	}

	std::cout << std::endl << "#############" << std::endl << std::endl ;
}

void FSM::RetourEtatPrecedent()
{
	m_stateChange = true;
	unsigned int  Temp = m_ListState.back();
	m_ListState.pop_back();
	m_nextState = m_ListState.back();
	m_ListState.pop_back();
	m_ListState.push_back(Temp);

	while( m_ListState.size() > m_MaxRegistedState)
	{
		m_ListState.pop_front();	
	}	
}

unsigned int FSM::getStateBefore()
{  
	std::list<unsigned int>::iterator it;

	if( m_ListState.size() >= 2 ) 
	{ 

		
		it = m_ListState.end();
		--it;
		--it;

		return (*it); 	
	} 
	else if( m_ListState.size() >0 )
	{
		it = m_ListState.end();
		return (*it);
	}


	return 0 ; 

};

