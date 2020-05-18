//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau - adaptation du namespace d'O. Gagon d'Elemental TD 2
// Date : 06/02/2013 - 14h44
// Fichier : déclaraction de la classe inputManager.hpp 
// Dernière modification : 07/02/2013
//@@@@@@@@@@@@@@@@@@@



#pragma once

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"



#define EVENT EventManager::getEventManager()
#define SOURISX EventManager::getEventManager()->getSourisX()
#define SOURISY EventManager::getEventManager()->getSourisY()

class EventManager
{
public :

	static EventManager* getEventManager();
	~EventManager();

	void update(sf::RenderWindow* _ecran);


	inline int getSourisX() const {return m_sourisX;};
	inline int getSourisY() const {return m_sourisY;};
	inline int isClosed() const {return m_close;}

	bool isKeyPressed(sf::Keyboard::Key _key) ;
	bool isMButtonPressed(sf::Mouse::Button _but) ;
	void AnnuleMouseButton(sf::Mouse::Button _but);
	void AnnuleKeyPressed(sf::Keyboard::Key _key) ;

	std::string GetTextEntered(){return m_TextEntered;};
	void SetTextEntered(std::string _s){m_TextEntered.clear(); m_TextEntered = _s;};
	void ReinitTextEntered();
	void SupprimeLettreTextEntered();
	


private :

	EventManager();

	sf::Event m_event;

	bool m_KeyInput[sf::Keyboard::KeyCount] ;
	bool m_MouseInput[sf::Mouse::ButtonCount];

	int m_sourisX;
	int m_sourisY;

	bool m_close;

	std::string m_TextEntered;

};