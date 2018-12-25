/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : 19/11/2018
    copyright            : (C) 2018 par Corentin LAHAROTTE, Louis UNG, Jan-Markus GELFGREN
    e-mail               : colapala@gmail.com, ung.louis@hotmail.fr
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
//#define MAP

//------------------------------------------------------------- Constantes
	
//----------------------------------------------------------------- PUBLIC


//----------------------------------------------------- Méthodes publiques

void Catalogue::Afficher()
// Algorithme : Affiche en détail chaque trajet du Catalogue.
// Si le catalogue est vide, on affiche juste une phrase.
{
	if (nb_trajets==0){
		cout << "Catalogue vide" <<endl <<endl;
	}
	else {
		cout << "Affichage du catalogue : " <<endl;
		for (int i=0; i<nb_trajets; i++){
			cout << "Trajet " << i+1 << endl;
			collection[i]->Afficher();
		}
	}
}

void Catalogue::Ajouter( TrajetSimple* t)
// Algorithme :
// 2 cas : Si la collection n'est pas totalement nb_trajetse, on ajoute le TrajetSimple à la collection,
// sinon on crée une nouvelle collection avec 2 fois plus de mémoire que précédemment,
// on copie en profondeur puis on supprime l'ancienne
// Copie en surface du nouveau trajet à ajouter
{
	if (nb_trajets < taille){
		collection[nb_trajets]=t;
		nb_trajets++;
    }
    else {
		taille *=2;
		Trajet ** tmp = new Trajet*[taille];
		for (int i =0; i<nb_trajets;i++){
			tmp[i]= collection[i];
		}
		tmp[nb_trajets] =t;
		nb_trajets++;
		delete [] collection;
		collection = tmp;	
	}
}

void Catalogue::Ajouter(TrajetCompose *tc)
// Algorithme :
// idem
{

	if (nb_trajets <taille){
		collection[nb_trajets] = tc;
		nb_trajets++;
	}
	else{
		taille *=2;
		Trajet ** tmp = new Trajet*[taille];
		for (int i =0; i<nb_trajets;i++){
			tmp[i]= collection[i];
		}
		tmp[nb_trajets] = tc;
		nb_trajets++;
		delete [] collection;
		collection = tmp;
	}

}

void Catalogue::Recherche(const char * depart, const char * arrivee)
// Algorithme :
// La recherche s'arrête dès qu'on trouve un trajet qui correspond aux paramètres.
// On affiche ensuite le résultat de la recherche.
{
	cout<<"Recherche en cours...pour aller de "<<depart<<" a "<<arrivee<<endl;
	bool trouve=false;
	for (int i=0;i<nb_trajets;i++){
		if(!strcmp(collection[i]->GetDepart(),depart) && !strcmp(collection[i]->GetArrivee(),arrivee) ){
		cout<<"Trajet n°"<<i+1<<endl;
		collection[i]->Afficher();
		trouve=true;
		}
	}
	if(trouve==false){
	cout<<"aucun Résultat pour votre recherche"<<endl;
	}
}

/*int Catalogue::GetNbTraj()
{
    return nb_trajets;
}*/

void Catalogue::Sauvegarde(int numFichier)
{
    ofstream fic;
    string s = "sauvegarde/sauv" + to_string(numFichier);
    fic.open(s);
    if (fic)
    {
        for (int i =0; i<nb_trajets;i++){
            collection[i]->Sauvegarder(fic);
            fic<<'@';
            fic <<endl;
        }
    }
    fic.close();
	
	//on sauvegarde dans un fichier le nb de fichier de sauvegarde
	fic.open("sauvegarde/nb_sauv");
	if (fic)
	{
		fic << numFichier;
	}
	fic.close();
}

void Catalogue::Charger(int numFichier)
{
	cout << "en train de charger" << endl;
	
    ifstream fic;
    string s = "sauvegarde/sauv" + to_string(numFichier);
    string lect;
    string typeTrajet;
    int numLigne =0;
	
	//nécessaire pour le constructeur du trajet compose
	TrajetSimple* t1;
	TrajetSimple* t2;
	TrajetCompose* tc;
	
    fic.open(s);
    if (fic)
    {
    	for (lect; getline(fic, lect); )
    	{
    		if (numLigne ==0)
    		{
    			typeTrajet= lect;
    		}
			
			istringstream iss(lect);
    		vector <string> motsIndiv {istream_iterator<string>{iss}, istream_iterator<string>{}};
    		if (typeTrajet == "TrajetSimple" && numLigne ==2)
    		{
    			Ajouter(new TrajetSimple(motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str()));
    		}
			
			else if (typeTrajet == "TrajetCompose")
			{
				if (numLigne == 2)
				{
					cout << "debut ligne 2" << endl;
					t1 = new TrajetSimple(motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str());;
					cout << "fin ligne 2" << endl;
				}
				else if (numLigne ==3)
				{
					t2 = new TrajetSimple(motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str());
					tc = new TrajetCompose(*t1,*t2,2);
				}
				else if (numLigne > 3 && lect != "@")
				{
					TrajetSimple t3 (motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str());
					tc->Ajouter(t3);
				}
				if (lect == "@"){
					Ajouter(tc);
				}
			}

    		if (lect == "@")
    		{
				delete t1;
				delete t2;
				//delete tc;
    			numLigne=0;
    		}
    		else
    		{
    			numLigne++;
    		}
    	}
    }
}
/*
void Catalogue::ChargerParType(int typeSelecTrajet, int numFichier)
{
	if (typeSelecTrajet ==1)
	{
		ifstream fic;
		string s = "sauvegarde/sauv" + to_string(numFichier);
		string lect;
		string typeTrajet;
		int numLigne =0;
		fic.open(s);
		if (fic)
		{
			for (lect; getline(fic, lect); )
			{
				if (numLigne ==0)
				{
					typeTrajet= lect;
				}

				if (typeTrajet == "TrajetSimple" && numLigne ==2)
				{
					istringstream iss(lect);
					vector <string> motsIndiv {istream_iterator<string>{iss}, istream_iterator<string>{}};
					Ajouter(new TrajetSimple(motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str()));
				}

				if (lect == "@")
				{
					numLigne=0;
				}
				else
				{
					numLigne++;
				}

			}

		}
	}
}*/

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue ( const Catalogue & unCatalogue )
// Algorithme : RAS
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Catalogue>" << endl;
#endif
	
} //----- Fin de Catalogue (constructeur de copie)


Catalogue::Catalogue ()
// Algorithme : RAS
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
	nb_trajets =0;
	taille =2;
	collection = new Trajet*[taille];
	
} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
// Algorithme : RAS
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif

	for (int i =0; i<nb_trajets; i++){
		delete collection[i];
	}
	delete [] collection;
	
} //----- Fin de ~Catalogue


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

