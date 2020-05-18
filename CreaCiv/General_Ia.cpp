//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : le général des armées de l'IA de creaciv
//*******************


#include "General_Ia.hpp"



CGeneral_IA::CGeneral_IA() : FSM()
{
	m_stockVille.push_back( new Cville(3,3) );
}


CGeneral_IA::~CGeneral_IA()
{
	if ( m_ATH ) 
		m_ATH = NULL;
}


bool CGeneral_IA::States( StateMachineEvent event, int state )
{
	BeginStateMachine


		//*********** Begin state ************
		State(GENERAL_INIT)
			OnEnter

				LOG("IA CGeneral_IA  : GENERAL_INIT");
				m_end = false;
				SetState(GENERAL_DEFINIR_ORDRE);

			OnUpdate
			OnExit
		//*********** End state ************

		//*********** Begin state ************
		State(GENERAL_DEFINIR_ORDRE)
			OnEnter

				LOG("IA CGeneral_IA  : GENERAL_DEFINIR_ORDRE");
				m_ATH->Lancer_Message("Le general choisie ses ordres");
				ChoixOrdre();
				SetState(GENERAL_DONNE_ORDRE);

			OnUpdate
			OnExit
		//*********** End state ************

		//*********** Begin state ************
		State(GENERAL_DONNE_ORDRE)
			OnEnter

				LOG("IA CGeneral_IA  : GENERAL_DONNE_ORDRE");
				SetState(GENERAL_GESTION_UNITE);
				m_ATH->Lancer_Message("Le general donne ses ordres");
				DonnerOrdre();


			OnUpdate
			OnExit
		//*********** End state ************


		//*********** Begin state ************
		State(GENERAL_GESTION_UNITE)
			OnEnter

				LOG("IA CGeneral_IA  : GENERAL_GESTION_UNITE");
				m_ATH->Lancer_Message("Gestion des unités");
				

				for(unsigned int i = 0 ; i < m_stockVille.size() ;++i)
				{
					m_stockVille[i]->ForceCurrentState(0);
					m_stockVille[i]->Initialize();
				}

				for(unsigned int i = 0 ; i < m_StockUnite.size() ;++i)
				{
					m_StockUnite[i]->ForceCurrentState(0);
					m_StockUnite[i]->Initialize();
				}

			OnUpdate

				int nombreVille = m_stockVille.size() ;
				int testVilleFini = 0 ;

				int nombreUnite = m_StockUnite.size() ;
				int testUniteFini = 0 ;

				for(unsigned int i = 0 ; i < m_stockVille.size() ;++i)
				{
					m_stockVille[i]->Update();

					if ( m_stockVille[i]->IsEnd() )
						testVilleFini++;
				}

				for(unsigned int i = 0 ; i < m_StockUnite.size() ;++i)
				{
					m_StockUnite[i]->Update();

					if ( m_StockUnite[i]->IsEnd() )
						testUniteFini++;
				}


				if( nombreVille == testVilleFini && testUniteFini == nombreUnite)
				{
					SetState(GENERAL_FIN);
					LOG("toutes les unité on fini leur action")
					LOG("gestion des retour unité")
				}


			OnExit
				gestionRetourVille();
				gestionRetourUnite();

		//*********** End state ************

		//*********** Begin state ************
		State(GENERAL_FIN)
			OnEnter
				LOG("IA CGeneral_IA  : GENERAL_FIN");
				m_end = true;
			OnUpdate
			OnExit
		//*********** End state ************

	EndStateMachine
}


void CGeneral_IA::AffichageUnite(bool Tab[][SIZEY] , int _sizeX, int _sizeY)
{

	sf::Vector2f Ancre( DATA->getFloatByName("MAP_ancre_x") , 
						DATA->getFloatByName("MAP_ancre_y") );

	// affichage des ville

	for (unsigned int i = 0; i < m_stockVille.size() ; i++)
	{	
		unsigned int X = m_stockVille[i]->getposTabX();
		unsigned int Y = m_stockVille[i]->getposTabY();


		m_stockVille[i]->ActualisePosition(Ancre);
		m_stockVille[i]->RenderUnit();

	}

	// affichage des unité

	for (unsigned int i = 0; i < m_StockUnite.size() ; i++)
	{	
		unsigned int X = m_StockUnite[i]->getposTabX();
		unsigned int Y = m_StockUnite[i]->getposTabY();

		m_StockUnite[i]->ActualisePosition(Ancre);
		m_StockUnite[i]->RenderUnit();

	}

	//Affichage des Ennemi

	for (unsigned int i = 0; i < m_uniteEnemi.size() ; i++)
	{	
		unsigned int X = m_uniteEnemi[i]->getposTabX();
		unsigned int Y = m_uniteEnemi[i]->getposTabY();

		if ( (int)X < _sizeX && (int)Y < _sizeY && (int)X >=0 && (int)Y >= 0 )
		{
			if( Tab[X][Y] )
			{
				m_stockVille[i]->ActualisePosition(Ancre);
				m_uniteEnemi[i]->RenderUnit();
			}
		}
	}



}


// fonction d'unite


Ccolon* CGeneral_IA::getColon()
{
	void* PointeurAretourner= NULL;

	for(int i = 0 ; i< m_StockUnite.size() ; ++i)
	{
		if ( m_StockUnite[i]->getType() == T_Unite::U_Colon )
		{
			PointeurAretourner = (void*)m_StockUnite[i];
		}
	}

	if ( PointeurAretourner )
	{
		return (Ccolon*)PointeurAretourner;
	}


	return NULL;

}


bool CGeneral_IA::SoldatDisponible()
{
	for(unsigned int i = 0 ; i < m_StockUnite.size() ; ++i)
	{
		if ( m_StockUnite[i]->getType() == U_Soldat  )
		{
			return true;
		}
	}


	return false;
}

// << fonction de hiérarchie >>

void CGeneral_IA::ChoixOrdre()
{

	switch(m_StrategieActuel)
	{
		case S_Etendre : m_ordreAdonner = OrdreParStrategieEtendre(); break;
		case S_Explorer : m_ordreAdonner = OrdreParStrategieExplorer(); break;
		case S_Attaquer : m_ordreAdonner = OrdreParStrategieAttaquer(); break;
		case S_developper : m_ordreAdonner = OrdreParStrategieDevelopper(); break;
		default : break;
	}

}


void CGeneral_IA::DonnerOrdre()
{

	switch(m_ordreAdonner)
	{
		case C_Economique : m_ATH->Lancer_Message("GENERAL : ordre de construction économique") ; break;
		case C_Expension : m_ATH->Lancer_Message("GENERAL : ordre de formation d'un colon") ;  break;
		case C_Militaire : m_ATH->Lancer_Message("GENERAL : ordre de formation d'un soldat") ;  break;
		case C_Ville : m_ATH->Lancer_Message("GENERAL : ordre de construction d'une ville") ;  break;
		case M_Attaque : m_ATH->Lancer_Message("GENERAL : ordre de deplacement d'attaque") ;  break;
		case M_Deplacement : m_ATH->Lancer_Message("GENERAL : ordre de déplacement") ;  break;
		case M_Exploration : m_ATH->Lancer_Message("GENERAL : ordre d'exploration") ;  break;
		case D_Def_Ville : m_ATH->Lancer_Message("GENERAL : ordre de défense de ville") ;  break;
		case D_Def_Position : m_ATH->Lancer_Message("GENERAL : ordre de défense de position") ;  break;

		default : m_ATH->Lancer_Message("GENERAL : aucun ordre n'est pertinant pour le moment"); break;
	}

}


T_ordre CGeneral_IA::OrdreParStrategieEtendre()
{
	Ccolon* TempColon = getColon();

	//si un colon est disponible
	if ( TempColon )
	{
		//si le colon a une position de construction
		if ( TempColon->AunePositionPourConstruire() )
		{
			// si le colon est en position
			if ( TempColon->ColonEnPosition() )
			{
				TempColon->setOrdre( C_Ville ) ;	
				return C_Ville;
			}
			else
			{
				TempColon->setOrdre( M_Deplacement ) ;
				return M_Deplacement;
			}			
		}
		else
		{
			int x = rand()% SIZEX;
			int y = rand() % SIZEY;

			TempColon->setPositionAconstruire(x,y);
			TempColon->setOrdre( M_Deplacement ) ;
			return M_Deplacement;

		}
	
	}
	else //sinon
	{
		if ( m_stockVille.size()> 0) //si une ville est dispo, on lance l'ordre de construction d'un colon
		{
			m_stockVille[0]->setOrdre( C_Expension ) ;
			return C_Expension;
		
		}
		else
		{
			m_ATH->Lancer_Message("Vous avez perdu :'(") ;
		}
		
	
	
	}

	return Fin_Ordre;
}

T_ordre CGeneral_IA::OrdreParStrategieExplorer()
{

	// on vérifie si il y a suffisament d'unité
	if( m_StockUnite.size() > 0 )
	{

		bool testExplo = false;
		
		for(unsigned int i = 0 ; i < m_StockUnite.size() ; ++i)
		{
			if ( m_StockUnite[i]->getType() == U_Soldat && m_StockUnite[i]->getOrdre() != M_Exploration )
			{
				m_StockUnite[i]->setOrdre( M_Exploration ) ;
				testExplo = true;
			}
		}
	

		if ( testExplo ) 
			return M_Exploration;
		else
			return Fin_Ordre;
	
	
	}
	else
	{
		if ( m_stockVille.size()> 0) //si une ville est dispo, on lance l'ordre de construction d'un soldat
		{
			m_stockVille[0]->setOrdre( C_Militaire ) ;
			return C_Militaire;
		
		}
		else
		{
			m_ATH->Lancer_Message("Vous avez perdu :'(") ;
		}		
	
	
	}


	return Fin_Ordre ;
}

T_ordre CGeneral_IA::OrdreParStrategieAttaquer()
{
	// on vérifie s'il y a des unité ennemi
	if ( m_uniteEnemi.size() > 0 )
	{
		
		for(unsigned int i = 0 ; i < m_StockUnite.size() ; ++i)
		{
			if ( m_StockUnite[i]->getType() == U_Soldat  )
			{
				m_StockUnite[i]->setOrdre( M_Attaque ) ;
			}
		}

			return M_Attaque;
	}
	else if ( SoldatDisponible() ) // si des soldat sont disponible
	{
		//on lance a tout les soldat un ordre d'exploration
		for(unsigned int i = 0 ; i < m_StockUnite.size() ; ++i)
		{
			if ( m_StockUnite[i]->getType() == U_Soldat && m_StockUnite[i]->getOrdre() != M_Exploration )
			{
				m_StockUnite[i]->setOrdre( M_Exploration ) ;
			}
		}

		return M_Exploration ;
	
	}
	else //sinon on créer des soldats
	{
		if ( m_stockVille.size()> 0) //si une ville est dispo, on lance l'ordre de construction d'un soldat
		{
			m_stockVille[0]->setOrdre( C_Militaire ) ;
			return C_Militaire;
		
		}
		else
		{
			m_ATH->Lancer_Message("Vous avez perdu :'(") ;
		}		
	}





	return Fin_Ordre ;
}

T_ordre CGeneral_IA::OrdreParStrategieDevelopper()
{
	//si des villes sont disponibles
		if ( m_stockVille.size()> 0) //si une ville est dispo, on lance l'ordre de construction d'un soldat
		{

			for(unsigned int i = 0 ; i < m_stockVille.size() ; ++i)
			{
				//toute les villes lances de l'or
				m_stockVille[i]->setOrdre( C_Economique  ) ;

			}

			return C_Economique;
		
		}
		else
		{
			m_ATH->Lancer_Message("Vous avez perdu :'(") ;
		}




	return Fin_Ordre ;
}



void CGeneral_IA::gestionRetourVille()
{
			for(unsigned int i = 0 ; i < m_stockVille.size() ; ++i)
			{
				void* TempVoidVille = m_stockVille[i];
				Cville* TempVille = (Cville*) TempVoidVille ;

				//vérification des guerrier creer
				if ( TempVille->getGuerrierCreer() ) 
				{
					TempVille->setOrdre(Fin_Ordre);
					TempVille->setGuerrierCreer(false);
					m_StockUnite.push_back(	TempVille->CreerGuerrier() );			
				}

			}
}


void CGeneral_IA::gestionRetourUnite()
{

}

