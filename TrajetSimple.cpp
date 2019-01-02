/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : 19/11/2018
    copyright            : (C) 2018 par Corentin LAHAROTTE, Louis UNG, Jan-Markus GELFGREN
    e-mail               : colapala@gmail.com, ung.louis@hotmail.fr
*************************************************************************/

//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Trajet.h"
#include "TrajetSimple.h"
#include <cstring>
//#define MAP


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void TrajetSimple::Afficher()
// Algorithme : RAS
//
{
  cout << Depart << endl;
  cout << Arrivee <<endl;
  cout<<Transport<<endl <<endl;
}

const char* TrajetSimple::GetDepart() const
// Algorithme : RAS
//
{
	return Depart;
}

const char* TrajetSimple::GetArrivee() const
// Algorithme : RAS
//
{
	return Arrivee;
}

const char* TrajetSimple::GetTransport() const
// Algorithme : RAS
//
{
	return Transport;
}

void TrajetSimple::Sauvegarder(ofstream& f)
{
    f << "TrajetSimple" <<endl;
    f << Depart << " " << Arrivee << endl;
    f << Depart << " " << Arrivee << " " << Transport <<endl;
    f << '@' <<endl;
}

void TrajetSimple::SauvegardeType(ofstream& f, int typeTrajet){
    if (typeTrajet ==1)
    {
        this->Sauvegarder(f);
    }
}

//------------------------------------------------- Surcharge d'opérateurs
TrajetSimple & TrajetSimple::operator = ( const TrajetSimple & unTrajetSimple )
// Algorithme : Effectue une copie en profondeur en allouant un nouvel espace mémoire avant de copier.
//
{
	
	this->~TrajetSimple();
    Depart = new char[strlen(unTrajetSimple.Depart)+1];
    strcpy(Depart,unTrajetSimple.Depart);
    Arrivee = new char[strlen(unTrajetSimple.Arrivee)+1];
    strcpy(Arrivee,unTrajetSimple.Arrivee);
    Transport = new char[strlen(unTrajetSimple.Transport)+1];
    strcpy(Transport,unTrajetSimple.Transport);
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur

TrajetSimple::TrajetSimple ( const TrajetSimple & unTrajetSimple )
// Algorithme : RAS
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <TrajetSimple>" << endl;
    
#endif
	Depart = new char[strlen(unTrajetSimple.Depart)+1];
    strcpy(Depart,unTrajetSimple.Depart);
    Arrivee = new char[strlen(unTrajetSimple.Arrivee)+1];
    strcpy(Arrivee,unTrajetSimple.Arrivee);
    Transport = new char[strlen(unTrajetSimple.Transport)+1];
    strcpy(Transport,unTrajetSimple.Transport);
    
	
} //----- Fin de TrajetSimple (constructeur de copie)

//constructeur sans aucun parametres
TrajetSimple::TrajetSimple (){
#ifdef MAP
    cout << "Appel au constructeur sans param de <TrajetSimple>" << endl;
#endif
}

TrajetSimple::TrajetSimple ( const char* depart, const char * arrivee,const char * t )
										
// Algorithme : On effectue une copie en profondeur dans le constructeur.
//
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
    Depart = new char[strlen(depart)+1];
    strcpy(Depart,depart);
    Arrivee = new char[strlen(arrivee)+1];
    strcpy(Arrivee,arrivee);
    Transport = new char[strlen(t)+1];
    strcpy(Transport,t);
} //----- Fin de TrajetSimple


TrajetSimple::~TrajetSimple ( )
// Algorithme : RAS
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
	//cout <<"this pointer points to " <<this <<endl;
    delete [] Depart;
    delete [] Arrivee;
    delete [] Transport;
} //----- Fin de ~TrajetSimple


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

