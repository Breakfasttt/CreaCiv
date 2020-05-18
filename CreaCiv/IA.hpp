//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : IA de Creaciv
//*******************



#pragma once
#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"
#include "FSM.hpp"
#include "Map.hpp"

#include "InfosIa.hpp"
#include "ATH.hpp"
#include "General_Ia.hpp"


class ATH;
class CGeneral_IA;

enum
{
	INIT_STATE,
	ETAT_ATTENTE,	
	INFOS_ATTITUDE,
	INFOS_RESSOURCES,
	INFOS_PLAN,
	GESTION_GENERAUX,
	
};


class Cia : public FSM
{

public :

	Cia();
	virtual ~Cia();

	// fonction général

	void AfficheMap();

	// << accesseurs >>

	inline int getOr(){return m_StockOr;};
	inline int getOrParTour(){return m_OrParTour;};
	inline int getPoidsComportement(unsigned int _i){return m_Poids_Comportement[_i];};

	inline void setOr(int _or){m_StockOr = _or;};
	inline void setOrParTour(int _orPT){m_OrParTour = _orPT;};
	inline void setPoidsComportement(unsigned int _id, int _poids){m_Poids_Comportement[_id] = _poids;};

	inline void addOr(int _or){m_StockOr += _or;};
	inline void addOrParTour(int _orPT){m_OrParTour += _orPT;};
	void addPoidsComportement(unsigned int _id, int _poids);

	void setATH(ATH* _ath){m_ATH = _ath;};

protected :

	// << attributs >>

	// attributs généraux
		ATH* m_ATH;
		Cmap* Map;
		bool m_Debug_afficheMap;
		bool m_CaseDecouverte[SIZEX][SIZEY];

	// attributs personnels
		int m_StockOr;
		int m_OrParTour;
		int m_Poids_Comportement[4];
		

	// généraux de l'ia
		CGeneral_IA*  m_LeGeneral;


	// Fonction FSM
	virtual bool States( StateMachineEvent event, int state ) ;
	virtual FSM* Clone(){return NULL;} ;
	virtual std::string GetName(){ return "IA_FSM";};


	//fonction général

	void actualiseCaseDecouverte();

	void DefinirStrategie();
	T_strategie VerifierBrancheMilitaire();
	T_strategie VerifierBrancheExpension();
	T_strategie VerifierBrancheNegociant();
	T_strategie VerifierBrancheCroissance();

	


};