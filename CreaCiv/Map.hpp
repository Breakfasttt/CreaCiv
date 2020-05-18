//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : Charge une map dans un tableau de donné et permet son affichage
//*******************


#pragma once
#include "GeneralConfig.hpp"
#include "DataCenter.hpp"


#define SIZEX 40
#define SIZEY 10
#define PIXELSIZE 20.0f

class Cmap
{
protected :

	// attributs
	int m_TableauMap[SIZEX][SIZEY];
	sf::Sprite m_TableauAffichage[SIZEX][SIZEY];

	sf::Vector2f m_Ancre;

	//fonction outils

	void LectureFichier(std::string _FileName);
	void RemplissageSpriteTableau();


public :

	Cmap();
	Cmap(std::string _FileName);
	~Cmap();

	// fonction général
	void AfficheMap();
	void AfficheMap(bool Tab[][SIZEY] , int _sizeX, int _sizeY);


	//Accesseur
	int getInfosCase(int, int);
	void setInfosCase(int, int); 


	int* getTableau();

};
