//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 02/02/2013 - 10h40
// Fichier : définition de la classe game.hpp
// Dernière modification : 02/02/2013
//@@@@@@@@@@@@@@@@@@@

#pragma once

#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"

#include "IA.hpp"
#include "ATH.hpp"


class Game
{
protected :
	
	sf::Clock MainClock;
	float DeltaTime;
	bool m_ActualiseTitre;


	void debugMode();

	Cia Mon_Ia;
	ATH Mon_Ath;


public :

	Game();
	~Game();

	void init();
	void update();
	void deinit();
	
};