//@@@@@@@@@@@@@@@@@@@
// Auteur : Y.Colaisseau
// Date : 30/01/2013 - 13h52
// Fichier : définition du singleton dataCenter  .hpp
// Dernière modification : 30/01/2013
//@@@@@@@@@@@@@@@@@@@


#pragma once

#include "GeneralConfig.hpp"

typedef enum
{
	FRENCH = 0,
	ENGLISH,
	DEUTCH,
	SPANISH

}T_Langue;

#define WINDOW_TITRE sf::Style::Titlebar //active la barre de titre 
#define WINDOW_CLOSE sf::Style::Close //active la crois rouge
#define WINDOW_NONE  sf::Style::None // sans barre sans titre
#define WINDOW_RESIZE sf::Style::Resize // autorise le resize
#define WINDOW_DEFAULT sf::Style::Default //fenetre par défault ( title,close,resize)
#define WINDOW_FULLSCREEN sf::Style::Fullscreen //active le fullscreen
#define WINDOW_WITHOUT_RESIZE sf::Style::Titlebar | sf::Style::Close // fenétre par default sans resize
#define DATA DataManager::getSmanager()
#define RENDER DataManager::getSmanager()->getRenderWindow()
#define DDEBUG DataManager::getSmanager()->getDebug()
#define SDDEBUG(a) DataManager::getSmanager()->setDebug(a)
#define ADDEBUG DataManager::getSmanager()->getActiveDebug()
#define ASDDEBUG(a) DataManager::getSmanager()->setActiveDebug(a)
#define LOG(x)  if( DDEBUG) {  std::cout << (x) ;  std::cout << std::endl; } 

class DataManager
{

private :

	
	DataManager();

	//map de stockage des data
	std::map<std::string,sf::Texture*> m_MapImage;
	std::map<std::string,std::string> m_MapMusique;
	std::map<std::string,sf::SoundBuffer*> m_MapSound;
	std::map<std::string, std::string> m_MapText;
	std::map<std::string,sf::Font*> m_MapFont;


	//map stockage des variables designers

	std::map<std::string,float> m_FloatDesigner;
	std::map<std::string,int> m_IntDesigner;
	std::map<std::string,bool> m_BoolDesigner;
	std::map<std::string,char> m_CharDesigner;


	// comportement global de la fenêtre de jeu
	float m_GlobalVolume;
	T_Langue m_Langue;
	float m_SizeFenetreX , m_SizeFenetreY;
	int m_TypeFenetre;
	sf::RenderWindow* m_MainRender;
	sf::Event m_LastEvent;
	std::string m_NameRender;
	bool m_debug;
	bool m_ActiveDebug;
	float m_Deltatime;

	//fonction de chargement

	void loadGlobalConfig();
	void loadImage();
	void loadMusique();
	void loadStreamSound();
	void loadText();
	void loadFont();
	void loadDesignerVariables();


	//fonction de déchargement
	void unloadImage();
	void unloadMusique();
	void unloadStreamSound();
	void unloadText();
	void unloadFont();
	void unloadDesignerVariables();
		

public :

	static DataManager* getSmanager();
	~DataManager();

	//fonction accesseurs de comportement global
	float getGlobalVolume() const {return m_GlobalVolume;};
	float getSizeFenetreX() const {return m_SizeFenetreX;};
	float getSizeFenetreY() const {return m_SizeFenetreY;};
	int getTypeFenetre() const {return m_TypeFenetre;};
	T_Langue getLangue() const {return m_Langue;};

	bool getDebug() const {return m_debug;};
	void setDebug(bool _b) {m_debug = _b;};

	bool getActiveDebug() const {return m_ActiveDebug;};
	void setActiveDebug(bool _b) {m_ActiveDebug = _b;};

	float getDT() const {return m_Deltatime;};
	void setDT(float _f) {m_Deltatime = _f;};

	void setGlobalVolume(float _f){m_GlobalVolume = _f;};
	void setLangue(T_Langue _l){m_Langue = _l; ReloadLanguage(); };
	void ReloadLanguage();
	std::string getMainTitleName(){return m_NameRender;};
	void setTitleName(std::string _st){m_MainRender->setTitle(_st); };

	//spécifique a la sfml
	sf::RenderWindow* getRenderWindow(){return m_MainRender;};

	//accesseurs d'assets
	sf::Texture* getTextureByName(std::string _name);
	sf::SoundBuffer* getSoundBufferByName(std::string _name);
	std::string getMusicByName(std::string _name);
	std::string getTextByName(std::string);
	sf::Font* getFontByName(std::string _name);

	//accesseur de variable designe
	float getFloatByName(std::string _name);
	int getIntByName(std::string _name);
	char getCharByName(std::string _name);
	bool getBoolByName(std::string _name);

};


