//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : Charge une map dans un tableau de donné et permet son affichage
//*******************

#include "Map.hpp"


Cmap::Cmap()
{

}

Cmap::Cmap(std::string _FileName)
{

	//init de l'ancre

	m_Ancre.x = DATA->getFloatByName("MAP_ancre_x");
	m_Ancre.y = DATA->getFloatByName("MAP_ancre_y");

	// << init du tableau >>
	for(int i = 0 ; i < SIZEX ; ++i)
	{
		for(int j = 0 ; j < SIZEY ; ++j)
		{
			m_TableauMap[i][j] = 0;
		}	
	}

	LectureFichier(_FileName);
	RemplissageSpriteTableau();

}

Cmap::~Cmap()
{

}

void Cmap::LectureFichier(std::string _FileName)
{
	// << chargement du fichier map >>
	std::ifstream FileMap;

	FileMap.open("Assets/Decors/" + _FileName,std::ifstream::in);

	if(FileMap == NULL)
	{
		std::cout << "Erreur lors de l'ouverture de la map : " << _FileName << std::endl;
	}
	else
	{
		int X = 0 ;
		int Y = 0 ;

		int infosCaseLu  = 0 ;

		LOG("Lecture de la carte")
		LOG("-------------------")

		while( !FileMap.eof() && Y < SIZEY )
		{

			char infosCaseLuChar = FileMap.get();

			if( infosCaseLuChar != '\n')
			{
				infosCaseLu = atoi(&infosCaseLuChar);

				if( DDEBUG )
					std::cout << infosCaseLu;

				if (X < SIZEX && Y < SIZEY )
					m_TableauMap[X][Y] = infosCaseLu;

				X++;

				if( X >= SIZEX )
				{

					Y++;
					X=0;

					if( DDEBUG )
						std::cout << std::endl;
				}	

			}
		}

		LOG("-------------------")
		LOG("fin de lecture")		
	}	
}

void Cmap::RemplissageSpriteTableau()
{
	for(int i = 0 ; i < SIZEX ; ++i)
	{
		for(int j = 0 ; j < SIZEY ; ++j)
		{

			// << position de la case >>

			m_TableauAffichage[i][j].setPosition( m_Ancre.x + PIXELSIZE * i ,
												  m_Ancre.y + PIXELSIZE * j );

			// << texture de la case >>
			sf::Texture* TempTexture = NULL;

			switch( m_TableauMap[i][j] ) 
			{
			
				case 0 : TempTexture = DATA->getTextureByName("CASE_EAU"); break;
				case 1 : TempTexture = DATA->getTextureByName("CASE_PLAINE");break;
				case 2 : TempTexture = DATA->getTextureByName("CASE_FORET");break;
				default : TempTexture = DATA->getTextureByName("CASE_EAU");	break;		
			}

			if( TempTexture )
				m_TableauAffichage[i][j].setTexture(*TempTexture);

		}	
	}
}

void Cmap::AfficheMap()
{
	for(int i = 0 ; i < SIZEX ; ++i)
	{
		for(int j = 0 ; j < SIZEY ; ++j)
		{
			RENDER->draw( m_TableauAffichage[i][j] ) ;
		}
	}
}

void Cmap::AfficheMap(bool Tab[][SIZEY] , int _sizeX, int _sizeY)
{
	for(int i = 0 ; i < _sizeX ; ++i)
	{
		for(int j = 0 ; j < _sizeY ; ++j)
		{
			if( Tab[i][j] == true )
			{
				RENDER->draw( m_TableauAffichage[i][j] ) ;
			}
		}
	}	

}


int Cmap::getInfosCase(int, int)
{
	return 0;
}

void Cmap::setInfosCase(int, int)
{

}

int* Cmap::getTableau()
{
	return NULL;
}
