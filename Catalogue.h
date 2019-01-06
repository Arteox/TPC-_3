/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : 24/12/2018
    copyright            : (C) 2018 par Alexandra LAFAILLE, Louis UNG
    e-mail               : louis.ung@insa-lyon.fr, alexandra.lafaille@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Trajet.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
// Classe amie de classe TrajetCompose.
// Cette classe permet de recenser tous les trajets (simple et composé) qui ont été créés.
// Elle permet de les afficher, et également d'en ajouter.
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	void Afficher();
    // Mode d'emploi :
    // Affiche le catalogue
	// Chaque trajet est affiché en détail un par un.
    // Contrat :
    // aucun

	void Ajouter( TrajetSimple* t);
    // Mode d'emploi :
    // Ajoute un TrajetSimple au catalogue
    // Contrat :
    // aucun
    
	void Ajouter(TrajetCompose *tc);
    // Mode d'emploi :
	// Surcharge de la méthode Ajouter
    // Ajoute un TrajetCompose au lieu d'un TrajetSimple au catalogue
    // Contrat :
    // aucun
    
	void Recherche(const char* depart,const char* arrivee);
    // Mode d'emploi :
    // Recherche un Trajet ayant les villes de départ et d'arrivée correspondantes aux villes placées en paramètres
	// Affiche le premier Trajet qui répond aux critères (recherche simple).
    // Contrat :
    // aucun

    void Sauvegarde(int numFichier);
	// Mode d'emploi :
    // Sauvegarde le catalogue courant dans le fichier txt dans le dossier sauvegarde/
	// Le numéro de ce fichier est indiqué en paramètre (sauv1, sauv2, etc)
	// met à jour le numéro du fichier le plus récent dans sauvegarde/nb_sauv
    // Contrat :
    // aucun

	void SauvegarderParVille(int numFichier, string Dep, string Arr);
	// Mode d'emploi :
    // Sauvegarde uniquement les trajets du catalogue dont la ville de départ et/ou la ville d'arrivée correspondent
	// aux paramètres indiqués.
	// Si Dep = 0 alors on regarde uniquement la ville d'arrivée du trajet.
	// De même si Arr =0 on regarde uniquement la ville de départ.
	// Si Dep et Arr valent 0, tous les trajets sont sauvegardés.
    // Contrat :
    // aucun

    void SauvegarderParType(int numFichier, int typeSelecTrajet);
	// Mode d'emploi :
    // Sauvegarde uniquement des trajets simples (typeSelecTrajet =1) ou des trajets composés (typeSelecTrajet = 2)
    // Contrat :
    // aucun
	
	void SauvegarderParIntervalle(int numFichier, int n, int m);
	// Mode d'emploi :
    // Sauvegarde tous les trajets se situant dans l'intervalle [n ,m] inclus entre 0 et nb_trajets
    // Contrat :
    // n <= m

    void Charger(int numFichier);
	// Mode d'emploi :
    // Ajoute au catalogue tous les trajets enregistrés dans le numFichier-ième fichier dans le repertoire sauvegarde/
    // Contrat :
    // aucun
	
	void ChargerParType(int typeSelecTrajet, int numFichier);
	// Mode d'emploi :
    // Même chose que la méthode Charger avec une spécification en plus
	// Si typeSelecTrajet = 1 on n'ajoute que les trajets simples
	// et si typeSelecTrajet =2 que les trajets composés.
    // Contrat :
    // aucun
	
	void ChargerParVille(int numFichier, string Dep, string Arr);
	// Mode d'emploi :
    // Ajoute uniquement les trajets au catalogue 
	// dont la ville de départ et/ou la ville d'arrivée correspondent
	// aux paramètres indiqués.
	// Si Dep = 0 alors on regarde uniquement la ville d'arrivée du trajet.
	// De même si Arr =0 on regarde uniquement la ville de départ.
	// Si Dep et Arr valent 0, tous les trajets sont ajoutés.
    // Contrat :
    // aucun
	
	void ChargerParIntervalle(int numFichier, int n, int m);
	// Mode d'emploi :
    // Ajoute tous les trajets du fichier indiqué qui sont dans l'intervalle [n, m] inclus entre 0 et nb_trajets
    // Contrat :
    // n <=m


//-------------------------------------------- Constructeurs - destructeur
    Catalogue ( const Catalogue & unCatalogue );
    // Mode d'emploi (constructeur de copie) :
    // Construit un catalogue à partir d'un autre catalogue
	// Constructeur de copie par défaut.
    // Contrat :
    // aucun

    Catalogue ();
    // Mode d'emploi :
    // Construit un catalogue vide
    // Contrat :
    // aucun

    virtual ~Catalogue ( );
    // Mode d'emploi :
    // Destructeur de catalogue
    // Contrat :
    // aucun

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	Trajet ** collection;
	int taille;
	int nb_trajets;
	
};

//-------------------------------- Autres définitions dépendantes de <Catalogue>

#endif // CATALOGUE_H

