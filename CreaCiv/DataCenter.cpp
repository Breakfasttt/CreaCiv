//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 30/01/2013 - 14h35
// Fichier : définition du singleton dataCenter  .hpp
// Dernière modification : 30/01/2013
//@@@@@@@@@@@@@@@@@@@


#include "DataCenter.hpp"


DataManager* DataManager::getSmanager()
{
	static DataManager Instance = DataManager();
	return &Instance;
}

DataManager::DataManager() : 
m_MapImage(),
	m_MapMusique(),
	m_MapSound(),
	m_MapText(),
	m_FloatDesigner(),
	m_IntDesigner(),
	m_BoolDesigner(),
	m_CharDesigner()
{
	
	loadGlobalConfig();
	loadDesignerVariables();
	loadImage();
	loadMusique();
	loadStreamSound();
	loadText();
	loadFont();
}

DataManager::~DataManager()
{
	unloadImage();
	unloadMusique();
	unloadStreamSound();
	unloadText();
	unloadDesignerVariables();
	unloadFont();
}


//@@@@@@@@
//Fonction de chargement
//@@@@@@@@

//chargement du fichier config
void DataManager::loadGlobalConfig()
{
	//ouverture du fichier
	m_Deltatime = 0.0f;
	m_debug = false;
	m_ActiveDebug = false;
	m_MainRender = NULL;
	std::ifstream DataCenter;
	DataCenter.open("Assets/Config.txt",std::ifstream::in);

	if(DataCenter == NULL)
	{
		std::cout << "Erreur lors de l'ouverture du Config.txt" << std::endl;
	}
	else
	{
		std::string LectureFichier;			
		int LectureLangue = 0;


		do
		{			
			DataCenter>>LectureFichier;		
		}while( LectureFichier != "#beginconfig"  );

		do
		{			
			DataCenter>>LectureFichier;

			if( strcmp(LectureFichier.c_str(),"nom" ) == 0 )
			{
				DataCenter >> m_NameRender ;
			}

			if( strcmp(LectureFichier.c_str(),"volume" ) == 0 )
			{
				DataCenter >> m_GlobalVolume ;
			}

			if( strcmp(LectureFichier.c_str(),"langue" ) == 0 )
			{
				DataCenter >> LectureLangue ;
				m_Langue = (T_Langue)LectureLangue;
			}

			if( strcmp(LectureFichier.c_str(),"fenetreX" ) == 0 )
			{
				DataCenter >> m_SizeFenetreX ;;
			}

			if( strcmp(LectureFichier.c_str(),"fenetreY" ) == 0 )
			{
				DataCenter >> m_SizeFenetreY ;

			}

			if( strcmp(LectureFichier.c_str(),"type" ) == 0 )
			{
				DataCenter >> m_TypeFenetre ;
			}

			if( strcmp(LectureFichier.c_str(),"debug" ) == 0 )
			{
				int TempLecture = 0 ;
				DataCenter >> TempLecture ;

				if(TempLecture > 0)
					m_ActiveDebug = true;
				else
					m_ActiveDebug = false; 

				m_debug = m_ActiveDebug;
			}

		}while( strcmp(LectureFichier.c_str(),"#endconfig" ) !=0 || 
			!DataCenter.eof() );


		DataCenter.close();

		if(m_TypeFenetre == 0)
		m_MainRender = new sf::RenderWindow( sf::VideoMode( (unsigned int)m_SizeFenetreX, 
																	(unsigned int)m_SizeFenetreY), 
																	m_NameRender, 
																	WINDOW_WITHOUT_RESIZE ) ;
		else
		m_MainRender = new sf::RenderWindow( sf::VideoMode( (unsigned int)m_SizeFenetreX, 
																	(unsigned int)m_SizeFenetreY), 
																	m_NameRender,
																	WINDOW_FULLSCREEN ) ;


	}
}

// chargement des sf::texture
void DataManager::loadImage()
{
	std::ifstream DataCenter  ;

	DataCenter.open("Assets/DataImage.txt",std::ifstream::in);


	if( DataCenter == NULL)
	{
		std::cout << "Erreur lors de l'ouverture du DataImage" << std::endl;
	}
	else
	{

		while( !DataCenter.eof() )
		{
			std::string TextureKey;
			std::string TextureLink;

			DataCenter >> TextureKey >> TextureLink ;			

			if(TextureKey != "" && TextureLink != "")
			{
				sf::Texture* tempTexture = new sf::Texture();

				tempTexture->loadFromFile(TextureLink);

				m_MapImage[TextureKey] = tempTexture;

				tempTexture = NULL;	
			}
		}

		DataCenter.close();
	}
}

//chargement des musiques
void DataManager::loadMusique()
{
	std::ifstream DataCenter;
	DataCenter.open("Assets/DataMusique.txt",std::ifstream::in);

	if( DataCenter == NULL)
	{
		std::cout << "Erreur lors de l'ouverture du DataMusic" << std::endl;
	}
	else
	{

		while( !DataCenter.eof() )
		{
			std::string MusicName;
			std::string MusicLink;

			DataCenter >> MusicName >> MusicLink ;
			if(MusicName != "" && MusicLink != "")
			{			
				m_MapMusique[MusicName] = MusicLink;
			}		
		}

		DataCenter.close();
	}
}

//chargement des Sons
void DataManager::loadStreamSound()
{
	std::ifstream DataCenter;

	DataCenter.open("Assets/DataSound.txt",std::ifstream::in);


	if( DataCenter == NULL)
	{
		std::cout << "Erreur lors de l'ouverture du Datasound" << std::endl;
	}
	else
	{

		while( !DataCenter.eof() )
		{
			std::string SoundKey;
			std::string SoundLink;

			DataCenter >> SoundKey >> SoundLink ;

			if(SoundKey != "" && SoundLink !="")
			{
				sf::SoundBuffer* tempSound = new sf::SoundBuffer();
				tempSound->loadFromFile(SoundLink);
				m_MapSound[SoundKey] = tempSound;
				tempSound = NULL;
			}
		}

		DataCenter.close();
	}
}

//chargement des textes
void DataManager::loadText()
{
	std::ifstream DataCenter;
	std::string Link("Assets/Localization");


	switch(m_Langue)
	{
	case FRENCH : Link = Link + "/Fr.txt"   ;	break ;
	case ENGLISH : Link = Link + "/En.txt"  ;	break ;
	case DEUTCH : Link = Link + "/De.txt"   ;	break ;
	case SPANISH : Link = Link + "/Sp.txt"  ;	break ;
	default : Link = Link + "/Fr.txt"		;	break ;	
	}



	DataCenter.open(Link,std::ifstream::in);

	if( DataCenter == NULL)
	{
		std::cout << "Erreur lors de l'ouverture du DataText" << std::endl;
	}
	else
	{

		while( !DataCenter.eof() )
		{
			std::string TextKey;
			std::string Text;

			DataCenter >> TextKey >> Text ;



			for(unsigned int i = 0 ; i < Text.size() ; ++i)
			{
				if( Text[i] == '_')
				{
					Text[i] = ' ';
				}
				if( Text[i] == '@')
				{
					Text[i] = '\n';
				}
			}

			if(TextKey != "" && Text !="")
				m_MapText[TextKey] = Text;

		}

		DataCenter.close();
	}
}

//chargement des fonts
void DataManager::loadFont()
{
	std::ifstream DataCenter;
	DataCenter.open("Assets/DataFont.txt",std::ifstream::in);

	if( DataCenter == NULL)
	{
		std::cout << "Erreur lors de l'ouverture du DataFont" << std::endl;
	}
	else
	{

		while( !DataCenter.eof() )
		{
			std::string FontName;
			std::string FontLink;

			DataCenter >> FontName >> FontLink ;
			if(FontName != "" && FontLink != "")
			{	
				sf::Font* temp = new sf::Font();
				temp->loadFromFile(FontLink);

				m_MapFont[FontName] = temp;
				temp = NULL;
			}		
		}

		DataCenter.close();
	}	
}

//chargement des variables designers
void DataManager::loadDesignerVariables()
{
	std::ifstream DataCenter;
	std::string Link("Assets/DataVariable.txt");


	DataCenter.open(Link,std::ifstream::in);

	if( DataCenter == NULL)
	{
		std::cout << "Erreur lors de l'ouverture du DataText" << std::endl;
	}
	else
	{
		std::string type;
		std::string Text;		

		while( !DataCenter.eof() )
		{

			DataCenter >> type ;

			if( type == "FLOAT")
			{
				float TempL;

				DataCenter >> Text >> TempL;

				m_FloatDesigner[Text] = TempL;
			}

			if( type == "INT")
			{
				int TempL;

				DataCenter >> Text >> TempL;

				m_IntDesigner[Text] = TempL;			
			}
			if( type == "CHAR")
			{
				char TempL;

				DataCenter >> Text >> TempL;

				m_CharDesigner[Text] = TempL;			
			}
			if( type == "BOOL")
			{
				int TempL;
				bool TempB = false;

				DataCenter >> Text >> TempL;

				if( TempL != 0)
					TempB = true;
				else
					TempB = false;

				m_BoolDesigner[Text] = TempB;			
			}
		}
	}
}

//fonction de rechargement
void  DataManager::ReloadLanguage()
{
	m_MapText.clear();
	loadText();
}


//fonction de déchargement


void DataManager::unloadImage()
{
	std::map<std::string,sf::Texture*>::iterator it;

	for(it = m_MapImage.begin() ; it != m_MapImage.end() ; ++it)
	{
		delete (*it).second;
		(*it).second = NULL;
	}

	m_MapImage.clear();

}

void DataManager::unloadMusique()
{
	m_MapMusique.clear();
}

void DataManager::unloadStreamSound()
{
	std::map<std::string,sf::SoundBuffer*>::iterator it;

	for(it = m_MapSound.begin() ; it != m_MapSound.end() ; ++it)
	{
		delete (*it).second;
		(*it).second = NULL;
	}

	m_MapSound.clear();
}

void DataManager::unloadText()
{
	m_MapText.clear();
}

void DataManager::unloadDesignerVariables()
{
	m_FloatDesigner.clear();
	m_IntDesigner.clear();
	m_BoolDesigner.clear();
	m_CharDesigner.clear();
}

void DataManager::unloadFont()
{
	std::map<std::string,sf::Font*>::iterator it;

	for(it = m_MapFont.begin() ; it != m_MapFont.end() ; ++it)
	{
		delete (*it).second;
		(*it).second = NULL;
	}

	m_MapFont.clear();
}

//accesseur
sf::Texture* DataManager::getTextureByName(std::string _name)
{
	if( m_MapImage[_name] != NULL )
		return m_MapImage[_name] ;

	return NULL;
}

sf::SoundBuffer* DataManager::getSoundBufferByName(std::string _name)
{
	if( m_MapSound[_name] != NULL )
		return m_MapSound[_name] ;

	return NULL;
}

std::string DataManager::getMusicByName(std::string _name)
{
	return m_MapMusique[_name] ;
}

std::string DataManager::getTextByName(std::string _name)
{
	return m_MapText[_name] ;
}

sf::Font* DataManager::getFontByName(std::string _name)
{
	return m_MapFont[_name];
}

float DataManager::getFloatByName(std::string _name)
{
	return m_FloatDesigner[_name] ;
}

int DataManager::getIntByName(std::string _name)
{
	return m_IntDesigner[_name] ;
}

char DataManager::getCharByName(std::string _name)
{
	return m_CharDesigner[_name] ;
}

bool DataManager::getBoolByName(std::string _name)
{
	return m_BoolDesigner[_name] ;
}


