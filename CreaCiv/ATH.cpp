//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : affichage tête haute de Creaciv
//*******************

#include "ATH.hpp"


ATH::ATH() : m_Liste_de_Message() , m_Message_en_Attente()
{
	m_IaInfos = NULL;
}

ATH::~ATH()
{
	m_IaInfos = NULL;
}


void ATH::init_ATH(Cia* _ia)  
{
	// << pointeur sur une IA pour récupéré ses infos >>
	m_IaInfos = _ia;
	m_IaInfos->setATH(this) ;

	// << Chargement de la font >>

	m_FontHud = DATA->getFontByName("Civ_Font");

	if( m_FontHud)
	{
		m_Txt_or.setFont(*m_FontHud);
		m_Txt_orParTour.setFont(*m_FontHud);
		m_Tour_Suivant.setFont(*m_FontHud);

		for(unsigned int i  = 0 ; i < 4 ; ++i)
		{
			m_Txt_Attitude[i].setFont(*m_FontHud);
		}
	}

	// << Chargement des textes >>


	m_infosOr = DATA->getTextByName("HUD_OR") ;
	m_infosOrParTour = DATA->getTextByName("HUD_ORPT") ;
	m_infosPoidsAttitude[A_Militaire] = DATA->getTextByName("HUD_ATTI1");
	m_infosPoidsAttitude[A_Expensionniste] = DATA->getTextByName("HUD_ATTI2");
	m_infosPoidsAttitude[A_Negociant] = DATA->getTextByName("HUD_ATTI3");
	m_infosPoidsAttitude[A_Croissance] = DATA->getTextByName("HUD_ATTI4");

	RecupereInfosIa();

	m_Tour_Suivant.setString( DATA->getTextByName("HUD_PASSERTOUR")  ) ;


	for(unsigned int i = 0 ; i < 4 ; ++i)
	{
		m_Bouton_plus[i].setString( DATA->getTextByName("HUD_PLUS")  ) ;
		m_Bouton_Moins[i].setString( DATA->getTextByName("HUD_MOINS")  ) ;
	
	}


	// << chargement des positions

	float Ancre_Atti_x = DATA->getFloatByName("HUD_Ancre_attitudes_x");
	float Ancre_Atti_y = DATA->getFloatByName("HUD_Ancre_attitudes_y");
	float decal_bouton = DATA->getFloatByName("HUD_Decal_bouton");
	float decal_text = DATA->getFloatByName("HUD_Decal_Text");
	float Ancre_Infos_x = DATA->getFloatByName("HUD_Ancre_infos_ia_x");
	float Ancre_Infos_y = DATA->getFloatByName("HUD_Ancre_infos_ia_y");
	float Ancre_Passer_x = DATA->getFloatByName("HUD_Ancre_Passer_x");
	float Ancre_Passer_y = DATA->getFloatByName("HUD_Ancre_Passer_y");


	for(unsigned int i = 0 ; i < 4 ; i++ )
	{
		m_Bouton_Moins[i].setPosition( Ancre_Atti_x ,
									   Ancre_Atti_y + i*decal_bouton );

		m_Bouton_plus[i].setPosition( Ancre_Atti_x +  decal_text,
									   Ancre_Atti_y + i*decal_bouton );

		m_Txt_Attitude[i].setPosition( Ancre_Atti_x +  decal_text*2,
									   Ancre_Atti_y + i*decal_bouton );
	
	}


	m_Tour_Suivant.setPosition( Ancre_Passer_x,
								Ancre_Passer_y );

	m_Txt_or.setPosition( Ancre_Infos_x,
						  Ancre_Infos_y );

	m_Txt_orParTour.setPosition( Ancre_Infos_x,
								 Ancre_Infos_y  + decal_bouton);


	// chargement pompe a message


	m_MaxTimer = DATA->getFloatByName("HUD_Temps_prochain_message");
	m_Vitesse = DATA->getFloatByName("HUD_Vitesse_defilement_message");
	m_Taille = DATA->getFloatByName("HUD_MessageBox_Taille");
	m_Ancre_Message.x = DATA->getFloatByName("HUD_Ancre_Message_x");
	m_Ancre_Message.y = DATA->getFloatByName("HUD_Ancre_Message_y");

	m_TaillePolice_message = (unsigned int)DATA->getIntByName("HUD_Taille_Police");
	m_max_message_character = DATA->getIntByName("HUD_max_caractere_mess");

	m_Timer = 0.0f;
	m_accepte_message = true;

}

void ATH::update_ATH()
{
	AddTestText();
	ChangeAttitude();
	ActualiseListeMessage();
}

void ATH::display_ATH()
{

	RENDER->draw( m_Txt_or );
	RENDER->draw( m_Txt_orParTour );
	RENDER->draw( m_Tour_Suivant );


	for(unsigned int i = 0 ; i < 4 ; i++ )
	{
		RENDER->draw( m_Bouton_Moins[i] ) ;

		RENDER->draw( m_Bouton_plus[i] );

		RENDER->draw( m_Txt_Attitude[i] );	
	}


	for( unsigned int i = 0 ; i < m_Liste_de_Message.size() ; ++i)
	{
		RENDER->draw( m_Liste_de_Message[i] ) ;
	}

}

void ATH::deinit_ATH()
{

}

// << fonction utilitaire >>

void ATH::RecupereInfosIa()
{
	if ( m_IaInfos )
	{
		std::ostringstream oss1, oss2 ;
		oss1 << m_IaInfos->getOr();
		oss2 << m_IaInfos->getOrParTour();

		m_Txt_or.setString( m_infosOr + oss1.str() );
		m_Txt_orParTour.setString( m_infosOrParTour + oss2.str() );


		for(unsigned int i = 0 ; i < 4 ; ++i)
		{
			std::ostringstream oss ;
			oss << m_IaInfos->getPoidsComportement(i);
			m_Txt_Attitude[i].setString( m_infosPoidsAttitude[i] + oss.str() ) ;	
		}
	}
}

void ATH::ChangeAttitude()
{
	
	// << Ajoute Points >>

	sf::Vector2f InfosSouris;
	InfosSouris.x = (float)EVENT->getSourisX();
	InfosSouris.y = (float)EVENT->getSourisY();

	bool Click = EVENT->isMButtonPressed( sf::Mouse::Button::Left );
	bool firstBreak = false;


	for(unsigned int i = 0 ; i < A_Fin_Attitude ; ++i)
	{
		if( Click && m_Bouton_plus[i].getGlobalBounds().contains(InfosSouris) )
		{
			m_IaInfos->addPoidsComportement(i,1);
			RecupereInfosIa();
			firstBreak= true;
			break;
		}
	}

	// << enléve points Points >>

	if( !firstBreak)
	{
		for(unsigned int i = 0 ; i < A_Fin_Attitude ; ++i)
		{
			if( Click && m_Bouton_Moins[i].getGlobalBounds().contains(InfosSouris) )
			{
				m_IaInfos->addPoidsComportement(i,-1);
				RecupereInfosIa();
				firstBreak = true;
				break;
			}
		}
	}

}

bool ATH::Clic_tour_suivant()
{
	sf::Vector2f PosSouris  = sf::Vector2f( EVENT->getSourisX() ,
											EVENT->getSourisY() );


	if( m_Tour_Suivant.getGlobalBounds().contains( PosSouris ) /*&& m_Liste_de_Message.size() == 0 */)
	{
		if( EVENT->isMButtonPressed(sf::Mouse::Button::Left) )
		{
			return true;
		}
	}
	
	return false;
}

// << Capture de message >>


void ATH::ActualiseListeMessage()
{
	
	//actualisation des positions des messages

	std::vector<sf::Text>::iterator it;

	std::vector< std::vector<sf::Text>::iterator > m_ItToErase;

	for(it = m_Liste_de_Message.begin();  it != m_Liste_de_Message.end() ; ++it)
	{
		sf::Vector2f temp = (*it).getPosition() ;
		temp.y += DATA->getDT() * m_Vitesse;
		(*it).setPosition(temp);

		if( temp.y > m_Ancre_Message.y + m_Taille )
		{
			m_ItToErase.push_back( it) ;
			//m_Liste_de_Message.erase( it ) ; crash pour le moment
			
		}
	}

	for( unsigned int i = 0 ; i < m_ItToErase.size() ; ++ i)
	{
		m_Liste_de_Message.erase( m_ItToErase[i] ) ;
	
	}

	m_ItToErase.clear();


	// actualisation du timer 

	if( !m_accepte_message) // si on accepte pas de message un timer est lancé
	{
		m_Timer += DATA->getDT();

		if( m_Timer > m_MaxTimer ) //quadn le timer termine
		{
			m_Timer = 0.0f; 
			m_accepte_message = true;

			if( m_Message_en_Attente.size() > 0 ) // on regarde s'il existe d'autre message a envoyé
			{
				std::string Temp = m_Message_en_Attente.front() ;
				m_Message_en_Attente.pop_front();
				Lancer_Message(Temp); //et on envoie le premier message en attente
			}
		}
	}

}


void ATH::Lancer_Message(std::string _mess)
{
	if( m_accepte_message ) 
	{
		m_accepte_message = false;
		sf::Text TempText;
		TempText.setFont(*m_FontHud);
		TempText.setCharacterSize(m_TaillePolice_message);
		TempText.setPosition(m_Ancre_Message);

		bool resize = false;

		while( _mess.size() > (m_max_message_character-3) )
		{
			_mess.pop_back();
			resize = true;
			
		}

		if ( resize )
			_mess += "...";

		TempText.setString(_mess);

		m_Liste_de_Message.push_back( TempText );

	}
	else
	{
		m_Message_en_Attente.push_back(_mess);
	
	}
}


void ATH::AddTestText()
{
	if(  DDEBUG   )
	{
		if( EVENT->isMButtonPressed( sf::Mouse::Button::Right ) )
		{
			Lancer_Message("Ceci est un message de test !!! Et ceci est pour tester la longueur max du texte ici present");
		
		}
	
	}
}


