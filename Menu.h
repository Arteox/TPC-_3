/*************************************************************************
                           Menu  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-ma ) il               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Menu> (fichier Menu.h) ----------------
#if ! defined ( Menu_H )
#define Menu_H
//#include "MenuSimple.h"

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Menu>
// Cette classe joue le rôle d'intermédiaire entre le programme et l'utilisateur
// Elle propose 3 fonctionnalités :
// L'affichage du catalogue, l'ajout d'un trajet ou la recherche d'un trajet
// Cette classe correspond à notre "main", c'est elle qui fait appel à toutes les autres classes.
//------------------------------------------------------------------------

class Menu 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
	


//-------------------------------------------- Constructeurs - destructeur
    Menu ( const Menu & unMenu );
    Menu();
    virtual ~Menu ( );


//------------------------------------------------------------------ PRIVE

    protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

        
};

//-------------------------------- Autres définitions dépendantes de <Menu>

#endif // Menu_H

