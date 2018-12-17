/*************************************************************************
                           TrajetCompose  -  description
                             -------------------
    début                : 19/11/2018
    copyright            : (C) 2018 par Corentin LAHAROTTE, Louis UNG, Jan-Markus GELFGREN
    e-mail               : colapala@gmail.com, ung.louis@hotmail.fr
*************************************************************************/

//---------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "TrajetCompose.h"
#include "Trajet.h"
#include "TrajetSimple.h"
#include <cstring>

//#define MAP

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC


//----------------------------------------------------- Méthodes publiques

void TrajetCompose::Afficher()
// Algorithme : RAS
//
{
	cout << "Trajet compose : " <<endl;
  for (int i=0; i<rempli;i++){
	cout << "Sous-trajet " << i+1 <<" : " << endl;
	list[i]->Afficher();
  }
}

const char* TrajetCompose::GetDepart() const
// Algorithme : RAS
//
{
	const char* a = list[0]->GetDepart();
	return a;
}

const char* TrajetCompose::GetArrivee() const
// Algorithme : RAS
//
{
	const char* b=list[rempli-1]->GetArrivee();
	return b;
}

const char* TrajetCompose::GetTransport() const
// Algorithme : Renvoie un message d'erreur.
//
{
	return "pas de transport pour un trajet compose";
}

bool TrajetCompose::VerifContrainte(const TrajetSimple& nouvTrajet)
// Algorithme :
//  Renvoie vrai lorsque la ville de départ du TrajetSimple à ajouter correspond à la 
//	ville d'arrivée du TrajetSimple précédemment rentré dans TrajetCompose
// Renvoie faux sinon
{
	if (!strcmp(nouvTrajet.GetDepart(), list[rempli-1]->GetArrivee())){
		return true;
	}
	else {
		return false;
	}
}

void TrajetCompose::Ajouter(const TrajetSimple &t)
// Algorithme :
// Ajoute le TrajetSimple à la liste s'il remplit les contraintes du TrajetCompose et
// si la liste n'est pas totalement remplie, réallloue de la mémoire en doublant sa taille
{
	if (VerifContrainte(t) ==true){
	  if (rempli < nb_SousTraj){
		list[rempli]= new TrajetSimple(t);
		rempli++;
	  }
	  else {
			nb_SousTraj *=2;
			Trajet ** tmp = new Trajet*[nb_SousTraj];
			for (int i =0; i<rempli;i++){
				tmp[i]= list[i];
			}
			tmp[rempli] = new TrajetSimple(t);
			rempli++;
			delete [] list;
			list = tmp;
	  }
	}
	else {
		cout << "Opération échouée : il faut que la ville de départ corresponde à la ville d'arrivée du sous-trajet précédent" <<endl;
	}

}

void TrajetCompose::Sauvegarder(ofstream& f){
    f << "TrajetCompose" << endl;
    f << GetDepart() << " " << GetArrivee() << endl;
    for (int j =0; j<rempli; j++){
        f << list[j]->GetDepart() <<" " <<list[j]->GetArrivee() << " " << list[j]->GetTransport() << endl;
    }
}

//------------------------------------------------- Surcharge d'opérateurs
TrajetCompose & TrajetCompose::operator = ( const TrajetCompose & unTrajetCompose )
// Algorithme : RAS
//
{
#ifdef MAP
    cout << "Appel de l'operateur = du <TrajetCompose>" << endl;
#endif

	this->~TrajetCompose();
	nb_SousTraj=unTrajetCompose.nb_SousTraj;
	rempli = unTrajetCompose.rempli;
	list = new Trajet*[nb_SousTraj];
	for (int i =0; i<rempli;i++){
		list[i] = new TrajetSimple(unTrajetCompose.list[i]->GetDepart(), unTrajetCompose.list[i]->GetArrivee(), unTrajetCompose.list[i]->GetTransport());
	}
	return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur

TrajetCompose::TrajetCompose ( const TrajetCompose & unTrajetCompose )
// Algorithme :
// Copie les paramètres de unTrajetCompose dans les paramètres du TrajetCompose appelant la méthode
// Copie en profondeur en allouant un nouvel espace mémoire à chaque fois.
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <TrajetCompose>" << endl;
#endif
	nb_SousTraj=unTrajetCompose.nb_SousTraj;
	rempli = unTrajetCompose.rempli;
	list = new Trajet*[nb_SousTraj];
	for (int i =0; i<rempli;i++){
		list[i] = new TrajetSimple(unTrajetCompose.list[i]->GetDepart(), unTrajetCompose.list[i]->GetArrivee(), unTrajetCompose.list[i]->GetTransport());
	}
	
} //----- Fin de TrajetCompose (constructeur de copie)


TrajetCompose::TrajetCompose (const TrajetSimple &t1,const TrajetSimple &t2, int nbelements )
// Algorithme : Affiche un message d'erreur si la contrainte entre les 2 sous-trajets n'est pas vérifiée.
// Dans ce cas-là, il faudra relancer le programme d'exécution à nouveau.
// Cependant cela ne devrait pas arriver avec la classe Menu qui empêche ce genre de situation.
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
    nb_SousTraj = nbelements;
    list = new Trajet*[nb_SousTraj];
    rempli = 2;
 	
	if(!strcmp(t1.GetArrivee(),t2.GetDepart())){
		list[0]= new TrajetSimple(t1.GetDepart(), t1.GetArrivee(), t1.GetTransport());
		list[1]= new TrajetSimple (t2.GetDepart(), t2.GetArrivee(), t2.GetTransport());
	}else{
		cerr<<"erreur"<<endl;
	}
    
} //----- Fin de TrajetCompose


TrajetCompose::~TrajetCompose ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif

	for (int i =0; i<rempli;i++){
		delete list[i];
	}
    delete [] list;
} //----- Fin de ~TrajetCompose


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

