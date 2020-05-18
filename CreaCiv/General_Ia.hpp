//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : le général des armées de l'IA de creaciv
//*******************


#pragma once

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"
#include "FSM.hpp"
#include "ATH.hpp"

#include "InfosIa.hpp"


#include "Unite.hpp"
#include "Colon.hpp"
#include "Ville.hpp"
#include "Guerrier.hpp"



enum
{
	GENERAL_INIT,
	GENERAL_DEFINIR_ORDRE,
	GENERAL_DONNE_ORDRE,
	GENERAL_GESTION_UNITE,
	GENERAL_FIN,
};


class ATH;

class CGeneral_IA : public FSM
{

public :


	CGeneral_IA();
	virtual ~CGeneral_IA();


	unsigned int getNombreUnite(){return m_StockUnite.size();};
	unsigned int getNombreEnnemie(){return m_uniteEnemi.size();};
	unsigned int getNombreVille(){return m_stockVille.size();};
	
	void setATH(ATH* _ath){ if (m_ATH != NULL) { m_ATH = _ath; }};

	T_strategie getStrategieActuel(){return m_StrategieActuel;};
	void setStrategie(T_strategie _s){m_StrategieActuel = _s;};

	void AffichageUnite(bool Tab[][SIZEY] , int _sizeX, int _sizeY);


	Cunit* getVille(int _i){return m_stockVille[_i];};
	Cunit* getUnite(int _i){return m_StockUnite[_i];};
	Cunit* getEnnemi(int _i){return m_uniteEnemi[_i];};


protected :

	//ATH 

	ATH* m_ATH ;

	// unite

	std::vector<Cunit*> m_stockVille;
	std::vector<Cunit*> m_StockUnite;
	std::vector<Cunit*> m_uniteEnemi;

	Ccolon* getColon();
	bool SoldatDisponible();

	void gestionRetourVille();
	void gestionRetourUnite();

	//statégie

	T_strategie m_StrategieActuel;

	T_ordre m_ordreAdonner;

	void ChoixOrdre();
	void DonnerOrdre();

	T_ordre OrdreParStrategieEtendre();
	T_ordre OrdreParStrategieExplorer();
	T_ordre OrdreParStrategieAttaquer();
	T_ordre OrdreParStrategieDevelopper();



	// Fonction FSM
	virtual bool States( StateMachineEvent event, int state ) ;
	virtual FSM* Clone(){return NULL;} ;
	virtual std::string GetName(){ return "GENERAL_IA";};

};