//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau - adaptation du namespace d'O. Gagon d'Elemental TD 2
// Date : 06/02/2013 - 14h44
// Fichier : définition de la classe inputManager.cpp 
// Dernière modification : 07/02/2013
//@@@@@@@@@@@@@@@@@@@


#include "EventManager.hpp"



EventManager::EventManager() : m_TextEntered()
{

	// << init des variables >>

	for(int i =0 ; i< sf::Keyboard::KeyCount ; ++i)
	{
		m_KeyInput[i]  = 0 ;
	}

	for(int i =0 ; i< sf::Mouse::ButtonCount ; ++i)
	{
		m_MouseInput[i]  = 0 ;
	}

	m_sourisX = 0;
	m_sourisY = 0;

	m_close = false;;
}

EventManager::~EventManager()
{

}


EventManager* EventManager::getEventManager()
{
	static EventManager Instance = EventManager();
	return &Instance;
}


void EventManager::update(sf::RenderWindow* _ecran)
{

	sf::Vector2i PosMouse = sf::Mouse::getPosition(*_ecran);
	m_sourisX = PosMouse.x;
	m_sourisY = PosMouse.y;


	while (_ecran->pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_close = true;
			break;
		case sf::Event::KeyPressed:
			m_KeyInput[m_event.key.code] = true;
			break;
		case sf::Event::KeyReleased:
			m_KeyInput[m_event.key.code] = false;
			break;
		case sf::Event::MouseButtonPressed:
			m_MouseInput[m_event.mouseButton.button] = true;
			break;
		case sf::Event::MouseButtonReleased:
			m_MouseInput[m_event.mouseButton.button] = false;
			break;

		case sf::Event::TextEntered:

			if (m_event.text.unicode > 30 && (m_event.text.unicode < 127
				|| m_event.text.unicode > 159))
			{
				m_TextEntered.push_back( m_event.text.unicode) ;
			}

			break;
		default : break;
		}
	}


	if( this->isKeyPressed( sf::Keyboard::F1 ) && ADDEBUG )
	{
		SDDEBUG( !DDEBUG ) ;
		system("cls");
	}

}


bool EventManager::isKeyPressed(sf::Keyboard::Key _key) 
{
	if( m_KeyInput[_key] == true)
	{
		m_KeyInput[_key] = false;
		return true;	
	}

	return false;	
}

bool EventManager::isMButtonPressed(sf::Mouse::Button _but) 
{
	if( m_MouseInput[_but] == true)
	{
		m_MouseInput[_but] = false;
		return true;	
	}

	return false;	
}

void EventManager::AnnuleMouseButton(sf::Mouse::Button _but)
{
	m_MouseInput[_but] = true;
}

void EventManager::AnnuleKeyPressed(sf::Keyboard::Key _key)
{
	m_KeyInput[_key] = true;
}


void EventManager::ReinitTextEntered()
{
	while( m_TextEntered.size()>0)
		m_TextEntered.pop_back();

	m_TextEntered.clear();
		
} 

void EventManager::SupprimeLettreTextEntered()
{
	if( m_TextEntered.size() > 0)
		m_TextEntered.pop_back();
}

