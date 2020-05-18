//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : affichage tête haute de Creaciv
//*******************


#pragma once
#include "GeneralConfig.hpp"
#include "DataCenter.hpp"
#include "EventManager.hpp"

#include "InfosIa.hpp"
#include "IA.hpp"

class Cia;

class ATH
{

public :

	ATH();
	~ATH();

	void init_ATH(Cia* _ia);
	void update_ATH();
	void display_ATH();
	void deinit_ATH();

	void Lancer_Message(std::string _mess);

	bool Clic_tour_suivant();

protected :

	//Ia
	Cia* m_IaInfos;

	//font

	sf::Font* m_FontHud;

	//string

	std::string m_infosOr;
	std::string m_infosOrParTour;
	std::string m_infosPoidsAttitude[4];

	// Texte

	sf::Text m_Txt_or;
	sf::Text m_Txt_orParTour;
	sf::Text m_Txt_Attitude[4];

	// bouton

	sf::Text m_Tour_Suivant;

	sf::Text m_Bouton_plus[4];
	sf::Text m_Bouton_Moins[4];


	// Capture De Message

	float m_MaxTimer;
	float m_Timer;
	float m_Vitesse;
	float m_Taille;
	bool m_accepte_message;
	unsigned int m_TaillePolice_message;
	int m_max_message_character;
	sf::Vector2f m_Ancre_Message;

	std::list<sf::String> m_Message_en_Attente;
	std::vector<sf::Text> m_Liste_de_Message;
	void ActualiseListeMessage();

	void AddTestText();
	

	// fonction utilitaire

	void RecupereInfosIa();
	void ChangeAttitude();


	

};

