//*******************
// Projet : CreaCiv
// Auteur : Yann C.
// description : enum de tout les ordres/comportement de l'ia
//*******************


#pragma once


// << Attitudes >>
typedef enum
{
	A_Militaire,
	A_Expensionniste,
	A_Negociant,
	A_Croissance,
	A_Fin_Attitude

}T_attitudes;


// << Stratégie >>
typedef enum
{
	S_Etendre,
	S_Explorer,
	S_Attaquer,
	S_developper,
	S_Rien,
	S_Fin_strategie

}T_strategie;


// << types d'ordre >>
typedef enum
{
	//ordre de construction (ville)
	C_Economique,
	C_Expension,
	C_Militaire,

	//ordre colon
	C_Ville,

	//ordre militaire
	M_Attaque,
	M_Deplacement,
	M_Exploration,

	//ordre de défense
	D_Def_Ville,
	D_Def_Position,

	Fin_Ordre

}T_ordre;




// << types d'unité >>
typedef enum
{
	U_Colon,
	U_Ville,
	U_Soldat,
	U_fin_unite

}T_Unite;