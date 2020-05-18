//@@@@@@@@@@@@@@@@@@@
// Auteur : Portions Copyright (C) Steve Rabin, 2001. adapté par Y.Colaisseau
// Date : 06/02/2013 - 14h38
// Fichier : Classe virtuel d'une machine a état FSM.hpp
// Dernière modification : 06/02/2013
//@@@@@@@@@@@@@@@@@@@



#ifndef __FSM_H__
#define __FSM_H__

#include <list>

enum StateMachineEvent
{
	EVENT_Update,
	EVENT_Enter,
	EVENT_Exit
};


//State Machine Language Macros (put these keywords in the file USERTYPE.DAT in the same directory as MSDEV.EXE)
#define BeginStateMachine		if( state < 0 ) { if(0) {
#define EndStateMachine			return( true ); } } else { return( false ); }  return( false );
#define State(a)				return( true ); } } else if( a == state ) { if(0) {
#define OnEvent(a)				return( true ); } else if( a == event ) {
#define OnEnter					OnEvent( EVENT_Enter )
#define OnUpdate				OnEvent( EVENT_Update )
#define OnExit					OnEvent( EVENT_Exit )


class FSM
{
public:

	FSM( void );
	~FSM( void ) {}

	void Initialize( void );
	void Update( void );
	void SetState( unsigned int newState );
	unsigned int getStateBefore();
	unsigned int getCurrentState(){return m_currentState;};
	void ForceCurrentState(unsigned int state){ m_currentState= state; m_nextState = state; };

	void AfficheHistorique();
	void RetourEtatPrecedent();

	inline unsigned int getMaxRegistedStates() const {return m_MaxRegistedState;};
	inline void setMaxRegistedStates(unsigned int _max ){ m_MaxRegistedState = _max ; };
	virtual FSM* Clone() = 0 ;
	virtual std::string GetName() = 0;
	virtual void UserFonction(void*){};
	virtual bool IsEnd(){return m_end;};

protected:

	bool m_end;
	unsigned int m_currentState;
	unsigned int m_nextState;
	bool m_stateChange;
	std::list<unsigned int> m_ListState;
	unsigned int m_MaxRegistedState;


	void Process( StateMachineEvent event );
	virtual bool States( StateMachineEvent event, int state ) = 0;
	
	

};


#endif	// __STATEMCH_H__