//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : IA de Creaciv
//*******************



#include "IA.hpp"


Cia::Cia() : FSM()
{
	// création de la map

	Map = new Cmap("MapIA.txt") ;
	for(int i = 0 ; i < SIZEX ;++i)
		for(int j = 0 ; j < SIZEX ;++j)
			m_CaseDecouverte[i][j] = false;

	m_StockOr = 0;
	m_OrParTour = 0;

	m_Debug_afficheMap = false;


	m_Poids_Comportement[A_Militaire] = 0;
	m_Poids_Comportement[A_Expensionniste] = 0;
	m_Poids_Comportement[A_Negociant] = 0;
	m_Poids_Comportement[A_Fin_Attitude] = 0;


	m_ATH = NULL;
	m_LeGeneral = new CGeneral_IA();
}


Cia::~Cia()
{
	if ( Map ) 
		delete Map;

	if ( m_ATH )
		m_ATH = NULL;

	if (  m_LeGeneral ) 
	{
		delete m_LeGeneral;
	}
}


bool Cia::States( StateMachineEvent event, int state )
{
	BeginStateMachine


		//*********** Begin state ************
		State(INIT_STATE)
		OnEnter
		LOG("IA Script  : INIT_STATE");

	m_StockOr = DATA->getIntByName("IA_INIT_OR");
	m_OrParTour = DATA->getIntByName("IA_INIT_OR_PAR_TOUR");
	actualiseCaseDecouverte();

	OnUpdate

		if( m_ATH )
			SetState(ETAT_ATTENTE);

	OnExit
		//*********** End state ************


		//*********** Begin state ************
		State(ETAT_ATTENTE)

	OnEnter
		LOG("IA Script  : ETAT_ATTENTE");
		m_ATH->Lancer_Message("En attente du Tour suivant");

	OnUpdate

		if( m_ATH->Clic_tour_suivant() )
		{
			SetState(INFOS_ATTITUDE);
		}

	OnExit
			//*********** End state ************


			//*********** Begin state ************
			State(INFOS_ATTITUDE)
			OnEnter
			LOG("IA Script  : INFOS_ATTITUDE");

		SetState(INFOS_RESSOURCES);
		OnUpdate
			OnExit
			//*********** End state ************


			//*********** Begin state ************
			State(INFOS_RESSOURCES)
		OnEnter
			LOG("IA Script  : INFOS_RESSOURCES");

			actualiseCaseDecouverte();
			SetState(INFOS_PLAN);

		OnUpdate
		OnExit

			//*********** End state ************

			//*********** Begin state ************
			State(INFOS_PLAN)
		OnEnter
			LOG("IA Script  : INFOS_PLAN");
			DefinirStrategie();
			SetState(GESTION_GENERAUX);

		OnUpdate
			OnExit
			//*********** End state ************



			//*********** Begin state ************
			State(GESTION_GENERAUX)
			OnEnter
			LOG("IA Script  : GESTION_GENERAUX");

		m_LeGeneral->setATH(m_ATH);
		m_LeGeneral->ForceCurrentState(0);
		m_LeGeneral->Initialize();


		OnUpdate


			m_LeGeneral->Update();

		if ( m_LeGeneral->IsEnd() )
		{
			SetState(ETAT_ATTENTE);
		}

		OnExit
			actualiseCaseDecouverte();
			//*********** End state ************




			EndStateMachine
}


void Cia::AfficheMap()
{

	if ( EVENT->isKeyPressed(sf::Keyboard::F2) )
	{
		m_Debug_afficheMap = !m_Debug_afficheMap;
	}


	if( Map && DDEBUG && m_Debug_afficheMap )
	{
		Map->AfficheMap();
		m_LeGeneral->AffichageUnite(m_CaseDecouverte, (int)SIZEX , (int)SIZEY );
	}
	else
	{
		Map->AfficheMap(m_CaseDecouverte, (int)SIZEX , (int)SIZEY );
		m_LeGeneral->AffichageUnite(m_CaseDecouverte, (int)SIZEX , (int)SIZEY );
	}

}


//fonction general

void Cia::actualiseCaseDecouverte()
{
	int nombreVille = m_LeGeneral->getNombreVille();
	int nombreUnite = m_LeGeneral->getNombreUnite();

	// afichage des cases que les villes voient
	for (int i =0; i < nombreVille ; ++i)
	{
		
		int X = m_LeGeneral->getVille(i)->getposTabX() ;
		int Y = m_LeGeneral->getVille(i)->getposTabY() ;
		
		X -= 1;
		Y -= 1 ;

		for(int j = 0 ; j < 3 ; ++ j)
		{
			for(int k = 0 ; k < 3 ; ++ k)
			{

				if( (X+j) >= 0 && (X+j) <SIZEX 
					&& (Y+k) >=0 && (Y+k) < SIZEY )
				{
					m_CaseDecouverte[X+j][Y+k] = true;	
				}
			}				
		}	
	}	



	// afichage des cases que les unité voient
	for (int i =0; i < nombreUnite ; ++i)
	{
		
		int X = m_LeGeneral->getUnite(i)->getposTabX() ;
		int Y = m_LeGeneral->getUnite(i)->getposTabY() ;
		
		X -= 1;
		Y -= 1 ;

		for(int j = 0 ; j < 3 ; ++ j)
		{
			for(int k = 0 ; k < 3 ; ++ k)
			{

				if( (X+j) >= 0 && (X+j) <SIZEX 
					&& (Y+k) >=0 && (Y+k) < SIZEY )
				{
					m_CaseDecouverte[X+j][Y+k] = true;	
				}
			}				
		}	
	}	

}

void  Cia::addPoidsComportement(unsigned int _id, int _poids)
{
	m_Poids_Comportement[_id] += _poids;

	if( m_Poids_Comportement[_id] > 10 )
		m_Poids_Comportement[_id] = 10 ;

	if( m_Poids_Comportement[_id] < 0)
		m_Poids_Comportement[_id] = 0 ;

}


void Cia::DefinirStrategie()
{

	//on récupére l'attitude la plus élever. si elles ont le même poid. on prendras la première .
	T_attitudes TempAttitudes;
	int valeur = m_Poids_Comportement[0];
	TempAttitudes = A_Militaire;

	for(unsigned int i = 1 ; i < A_Fin_Attitude ; ++i)
	{
		if ( m_Poids_Comportement[i] > valeur )
		{
			TempAttitudes = (T_attitudes)i ;
			valeur = m_Poids_Comportement[i];
		}
	}


	// on parcoure les braches pour définir la stratégie a établir.
	T_strategie StrategieAdopter = S_Rien;

	switch (TempAttitudes)
	{
		case A_Militaire : StrategieAdopter = VerifierBrancheMilitaire(); 
						m_ATH->Lancer_Message("l'IA est un grand militaire"); break;
		case A_Expensionniste : StrategieAdopter = VerifierBrancheExpension(); 
							m_ATH->Lancer_Message("l'IA est Expensionniste"); break;
		case A_Negociant : StrategieAdopter = VerifierBrancheNegociant(); 
							m_ATH->Lancer_Message("l'IA est un Negociant née"); break;
		case A_Croissance : StrategieAdopter = VerifierBrancheCroissance(); 
							m_ATH->Lancer_Message("l'IA espère voir sa nation grandir");  break;
		default : StrategieAdopter = S_Rien ; m_ATH->Lancer_Message("Une attitude par default a ete adopter"); break;	
	}


	switch (StrategieAdopter)
	{
		case S_Etendre : m_ATH->Lancer_Message("Strategie d'expension choisie");  break;
		case S_Explorer : m_ATH->Lancer_Message("Strategie d'exploration choisie");  break;
		case S_Attaquer : m_ATH->Lancer_Message("Strategie militaire choisie");  break;
		case S_developper : m_ATH->Lancer_Message("Strategie de developpement choisie");  break;
		default : m_ATH->Lancer_Message("Aucune strategie choisie"); break;	
	}

	if ( StrategieAdopter != S_Rien )
		m_LeGeneral->setStrategie(StrategieAdopter );

}


T_strategie Cia::VerifierBrancheMilitaire()
{
	// si le general n'a pas de strategie d'attaque ou d'exploration
	if ( m_LeGeneral->getStrategieActuel()  !=  (S_Attaquer || S_Explorer)  )
	{
		//si des ennemies ont ete detecter , ont lance une strategie d'attaque
		if( m_LeGeneral->getNombreEnnemie() >0 )
		{
			return S_Attaquer ;
		}
		else
		{
			return S_Explorer;
		}
	
	}

	return S_Rien;

}

T_strategie Cia::VerifierBrancheExpension()
{
	// si le general n'a pas de strategie d'expension (s'étendre)
	if ( m_LeGeneral->getStrategieActuel()  !=  S_Etendre  )
	{
		//si la civ est assez développée
		if( m_StockOr > 1 )
		{
			//on vérifie le nombre de case découverte 

			int NombreVille = m_LeGeneral->getNombreVille() ;

			if( NombreVille > 0 )
			{
				int NombreCase = 0 ;
				for (int i = 0 ; i < SIZEX ; ++i)
				{
					for (int j = 0 ; j < SIZEY ; ++j)
					{
						if( m_CaseDecouverte[i][j] == true )
							NombreCase++;
					}			
				}

				// s'il y a assez de case découverte par la civilization
				NombreCase /= NombreVille ;
				if ( NombreCase > 8 )
					return S_Etendre;
				else
					return S_Explorer; //sinon on explore

			}
			else
			{
				return S_Etendre ;
			}			
		}
		else
		{	//si elle n'a pas assez d'or elle se développe
			return S_developper;
		}
	}


	return S_Rien;

}

T_strategie Cia::VerifierBrancheNegociant()
{
	// si le general n'a pas de stategie de développement
	if ( m_LeGeneral->getStrategieActuel()  !=  S_developper  )
	{
		return S_developper;	
	}

	return S_Rien;
}

T_strategie Cia::VerifierBrancheCroissance()
{
	// si le general n'a pas de stategie de développement
	if ( m_LeGeneral->getStrategieActuel()  !=  S_developper  )
	{
		if( m_OrParTour < 25 )
			return S_developper;
		else
			return S_Explorer;
	}

	return S_Rien;
}



