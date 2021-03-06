/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : 24/12/2018
    copyright            : (C) 2018 par Alexandra LAFAILLE, Louis UNG
    e-mail               : louis.ung@insa-lyon.fr, alexandra.lafaille@insa-lyon.fr
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

void Catalogue::Sauvegarde(int numFichier)
// Algorithme :
// Le dossier sauvegarde est indiqué par son chemin relatif.
{
    ofstream fic;
    string s = "sauvegarde/sauv" + to_string(numFichier);
    fic.open(s);
    if (fic)
    {
        for (int i =0; i<nb_trajets;i++){
            collection[i]->Sauvegarder(fic);
        }
    }
    fic.close();
	
	fic.open("sauvegarde/nb_sauv");
	if (fic)
	{
		fic << numFichier;
	}
	fic.close();
}

void Catalogue::SauvegarderParVille(int numFichier, string Dep, string Arr)
// Algorithme : RAS
{
	ofstream fic;
	string s = "sauvegarde/sauv" + to_string(numFichier);
	fic.open(s);
	if (fic)
	{
		for (int i = 0; i < nb_trajets; i++) {
			if ((collection[i]->GetDepart() == Dep || Dep == "0") && (collection[i]->GetArrivee() == Arr || Arr == "0"))
			{
				collection[i]->Sauvegarder(fic);
			}
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

void Catalogue::SauvegarderParType(int numFichier, int typeSelecTrajet)
// Algorithme : RAS
{
    ofstream fic;
    string s = "sauvegarde/sauv" + to_string(numFichier);
    fic.open(s);
    if (fic)
    {
        for (int i =0; i<nb_trajets;i++){
            collection[i]->SauvegardeType(fic, typeSelecTrajet);
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

void Catalogue::SauvegarderParIntervalle(int numFichier, int n, int m)
// Algorithme : RAS
{
	ofstream fic;
    string s = "sauvegarde/sauv" + to_string(numFichier);
    fic.open(s);
    if (fic)
    {
        for (int i =0; i<nb_trajets;i++){
			if (i+1 >=n && i+1 <=m){
				collection[i]->Sauvegarder(fic);
			}
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
// Algorithme : 
// Connaissant le format du fichier, on récupère les informations ligne par ligne
// @ indique la fin de la lecture des informations d'un trajet
// Il y a deux pointeurs de trajets simples qui sont nécessaires pour appeler le constructeur de la classe TrajetCompose
// On ne fait que des copies en surface pour les trajets, à part lorsqu'on appelle le constructeur de la classe TrajetCompose

{
    ifstream fic;
    string s = "sauvegarde/sauv" + to_string(numFichier);
    string lect;
    string typeTrajet;
    int numLigne =0;
	
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
					t1 = new TrajetSimple(motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str());;
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
				if (typeTrajet == "TrajetCompose"){
					delete t1;
					delete t2;
				}
    			numLigne=0;
    		}
    		else
    		{
    			numLigne++;
    		}
    	}
    }
	fic.close();
}

void Catalogue::ChargerParType(int typeSelecTrajet, int numFichier)
// Algorithme : RAS
{
	ifstream fic;
    string s = "sauvegarde/sauv" + to_string(numFichier);
    string lect;
    string typeTrajet;
    int numLigne =0;
	
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
    		if (typeSelecTrajet == 1 && typeTrajet == "TrajetSimple" && numLigne ==2)
    		{
    			Ajouter(new TrajetSimple(motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str()));
    		}
			
			else if (typeSelecTrajet ==2 && typeTrajet == "TrajetCompose")
			{
				if (numLigne == 2)
				{
					t1 = new TrajetSimple(motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str());;
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
				if (typeTrajet == "TrajetCompose" && typeSelecTrajet==2){
					delete t1;
					delete t2;
				}
    			numLigne=0;
    		}
    		else
    		{
    			numLigne++;
    		}
    	}
    }
	fic.close();
}

void Catalogue::ChargerParVille(int numFichier, string Dep, string Arr)
// Algorithme : RAS
{
    ifstream fic;
    string s = "sauvegarde/sauv" + to_string(numFichier);
    string lect;
    string typeTrajet;
    int numLigne =0;
	
	TrajetSimple* t1;
	TrajetSimple* t2;
	TrajetCompose* tc;
	
	bool ajoutTrajetSimple;
	bool ajoutTrajetCompose;
	
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
			
			if (typeTrajet == "TrajetSimple"){
				
				if (numLigne ==1){
					if ((motsIndiv.at(0) == Dep || Dep == "0") && (motsIndiv.at(1) == Arr || Arr == "0")){
						ajoutTrajetSimple = true;
					}
				}
				else if (numLigne ==2 && ajoutTrajetSimple == true)
				{
					Ajouter(new TrajetSimple(motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str()));
				}
			}
			
			else if (typeTrajet == "TrajetCompose")
			{
				if (numLigne ==1){
					if ((motsIndiv.at(0) == Dep || Dep == "0") && (motsIndiv.at(1) == Arr || Arr == "0")){
						ajoutTrajetCompose = true;
					}
				}
				if (ajoutTrajetCompose)
				{
					if (numLigne == 2)
					{
						t1 = new TrajetSimple(motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str());;
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
			}

    		if (lect == "@")
    		{
				if (typeTrajet == "TrajetCompose" && ajoutTrajetCompose ==true){
					delete t1;
					delete t2;
				}
    			numLigne=0;
				ajoutTrajetSimple = false;
				ajoutTrajetCompose = false;
    		}
    		else
    		{
    			numLigne++;
    		}
    	}
    }
	fic.close();
}

void Catalogue::ChargerParIntervalle(int numFichier, int n, int m)
// Algorithme : RAS
{
	ifstream fic;
    string s = "sauvegarde/sauv" + to_string(numFichier);
    string lect;
    string typeTrajet;
    int numLigne =0;
	int compteurTrajet =1;
	
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
			
			if (compteurTrajet >=n && compteurTrajet <=m){
				
				if (typeTrajet == "TrajetSimple" && numLigne ==2)
				{
					Ajouter(new TrajetSimple(motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str()));
				}
				
				else if (typeTrajet == "TrajetCompose")
				{
					if (numLigne == 2)
					{
						t1 = new TrajetSimple(motsIndiv.at(0).c_str(),motsIndiv.at(1).c_str(),motsIndiv.at(2).c_str());;
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
			}

    		if (lect == "@")
    		{
				if (typeTrajet == "TrajetCompose" && compteurTrajet >=n && compteurTrajet <=m){
					delete t1;
					delete t2;
				}
    			numLigne=0;
				compteurTrajet++;
    		}
    		else
    		{
    			numLigne++;
    		}
    	}
    }
	fic.close();
}

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

