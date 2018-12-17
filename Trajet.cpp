/*************************************************************************
                           Trajet  -  description
                             -------------------
    début                : 19/11/2018
    copyright            : (C) 2018 par Corentin LAHAROTTE, Louis UNG, Jan-Markus GELFGREN
    e-mail               : colapala@gmail.com, ung.louis@hotmail.fr
*************************************************************************/

//---------- Réalisation de la classe <Trajet> (fichier Trajet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;
#include <cstring> 
#include <fstream>

//------------------------------------------------------ Include personnel
#include "Trajet.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
 
 void Trajet::Afficher()
// Algorithme : RAS
//
{
}

const char* Trajet::GetDepart() const
// Algorithme : RAS
//
{
 return "no";
}

const char* Trajet::GetArrivee() const
// Algorithme : RAS
//
{
return "no";
}

const char* Trajet::GetTransport() const
// Algorithme : RAS
//
{
return "no";
}
void Trajet::Sauvegarder(std::ofstream& f){

}

//------------------------------------------------- Surcharge d'opérateurs
Trajet & Trajet::operator = ( const Trajet & unTrajet )
// Algorithme : RAS
//
{
  return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Trajet::Trajet ( const Trajet & unTrajet )
// Algorithme : RAS
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Trajet>" << endl;
#endif
} //----- Fin de Trajet (constructeur de copie)


Trajet::Trajet ()
// Algorithme : RAS
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Trajet>" << endl;
#endif
} //----- Fin de Trajet


Trajet::~Trajet ( )
// Algorithme : RAS
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Trajet>" << endl;
#endif
} //----- Fin de ~Trajet


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
