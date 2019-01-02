/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : 19/11/2018
    copyright            : (C) 2018 par Corentin LAHAROTTE, Louis UNG, Jan-Markus GELFGREN
    e-mail               : colapala@gmail.com, ung.louis@hotmail.fr
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
    
    //int GetNbTraj();

    void Sauvegarde(int numFichier);

	void SauvegarderParVille(int numFichier, string Dep, string Arr)

    void Charger(int numFichier);
	
	void ChargerParType(int typeSelecTrajet, int numFichier);
	
	void ChargerParVille(int numFichier, string Dep, string Arr);


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


    //friend class Menu;
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

