/*************************************************************************
                           Trajet  -  description
                             -------------------
    début                : 19/11/2018
    copyright            : (C) 2018 par Corentin LAHAROTTE, Louis UNG, Jan-Markus GELFGREN
    e-mail               : colapala@gmail.com, ung.louis@hotmail.fr
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H )
#define TRAJET_H
#include <fstream>
using namespace std;

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
//Classe abstraite qui sert d'ancêtre commun aux classes TrajetSimple et TrajetCompose
//Ainsi, on pourra créer des tableaux contenant des instances de ces deux classes.
//La classe en elle-même ne dispose d'aucune fonctionnalité.
//------------------------------------------------------------------------

class Trajet 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	virtual void Afficher();
    // Mode d'emploi : 
    //  
    // Contrat :
    // aucun

	virtual const char* GetDepart() const =0;
    // Mode d'emploi :
    //
    // Contrat :
    // aucun

	virtual const char* GetArrivee() const =0;
    // Mode d'emploi :
    //
    // Contrat :
    // aucun

	virtual const char* GetTransport() const=0;
    // Mode d'emploi :
    //
    // Contrat :
    // aucun


    virtual void Sauvegarder(ofstream& f);

    virtual void SauvegardeType(ofstream& f, int typeTrajet);

//------------------------------------------------- Surcharge d'opérateurs
    Trajet & operator = ( const Trajet & unTrajet );
    // Mode d'emploi :
    //
    // Contrat :
    // aucun

//-------------------------------------------- Constructeurs - destructeur
    Trajet ( const Trajet & unTrajet );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    // aucun

    
    Trajet();
    // Mode d'emploi :
    //
    // Contrat :
    // aucun

    virtual ~Trajet ( );
    // Mode d'emploi :
    //  Destructeur de Trajets
    // Contrat :
    // aucun



//------------------------------------------------------------------ PRIVE

    protected:

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés


};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif // TRAJET_H

