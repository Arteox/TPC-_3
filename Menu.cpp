#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include <iostream>
#include "Catalogue.h"
#include "Menu.h"
#include <cstring>
#include <fstream>
#include <string>
using namespace std;
//!! Ce programme peut faire des erreurs dûes à l'allocation de TS** de taille MAX_LENGTH.
// Cependant elles ne nuisent pas à l'exécution du programme, elles veulent juste dire que tout l'espace n'est pas utilisé
int main(){
	const int MAX_LENGTH=50;
	int choix;
	int nbElements;
	char* villeA=new char[MAX_LENGTH];
	char* villeB=new char[MAX_LENGTH];
	char* transport=new char[MAX_LENGTH];
	Catalogue C;
        int nb_sauv =1;
	
	
	//Stocke tous les trajets simples ajoutés avec un index
	TrajetSimple** TS=new TrajetSimple*[MAX_LENGTH];
	int indexSimple=0;
	
	//stocke tous les trajets composés ajoutés
	TrajetCompose** TC=new TrajetCompose*[MAX_LENGTH];		
	int indexComp=0;
	
	//variable pour quitter ou rester dans le menu
	bool arret=false; 


	while(!arret){
		
		cout<<"Bonjour, et bienvenue dans notre catalogue de trajets"<<endl;
		cout<<"Tapez 1 pour ajouter un TrajetSimple"<<endl;
		cout<<"Tapez 2 pour ajouter un TrajetCompose"<<endl;
		cout<<"Tapez 3 pour faire une recherche"<<endl;
		cout<<"Tapez 4 pour Afficher le catalogue"<<endl;
                cout<<"Tapez 5 pour sauvegarder le catalogue actuel"<<endl;
                cout<<"Tapez 6 pour charger un catalogue depuis un fichier"<<endl;
                cout<<"Tapez 7 pour quitter le catalogue"<<endl;


		cin>>choix;
		endl(cout);
		switch(choix){
			//Ajout d'un trajet simple
			case 1: 
				
				cout<<"vous avez choisi l'ajout de TrajetSimple"<<endl;
				cout<<"veuillez renseigner la ville de depart, la ville d'arrivee et le moyen de transport"<<endl;

				cin>>villeA>>villeB>>transport;
				TS[indexSimple]=new TrajetSimple(villeA,villeB,transport);
				C.Ajouter(TS[indexSimple]);			
				indexSimple++;
				break;
				
			//Ajout d'un trajet composé
			case 2:
				
				cout<<"vous avez choisi l'ajout de Trajetcompose"<<endl;

				cout<<"veuillez renseigner le nombre de trajets a ajouter"<<endl;
			
				cin>>nbElements;

				bool ErrRemplissage;
				for (int i=0;i<nbElements;i++)	{
					ErrRemplissage = true;
					
					//boucle infinie tant que l'utilisateur ne renseigne pas les infos correctement
					while (ErrRemplissage){
						cout<<"veuillez renseigner la ville de depart, la ville d'arrivee et le moyen de transport du "<<i+1<<"e trajet"<<endl;
						cin>>villeA>>villeB>>transport;
						if (i==0 || !strcmp(villeA,TS[indexSimple-1]->GetArrivee())){
							ErrRemplissage=false;
						}
						else {
							cout << "Il faut que la ville de départ corresponde à la ville d'arrivée du sous trajet-précédent. Veuillez à nouveau ressaisir un trajet valide."<<endl;
							endl(cout);
							cout <<"la ville d'arrivée du sous trajet précédent est : " <<TS[indexSimple-1]->GetArrivee() <<endl;
							endl(cout);
						}
					}
					TS[indexSimple]=new TrajetSimple(villeA,villeB,transport);
					if(i==1){
						TC[indexComp]=new TrajetCompose(*TS[indexSimple-1],*TS[indexSimple],nbElements);
					}else if(i>1){
						TC[indexComp]->Ajouter(*TS[indexSimple]);
					}
					indexSimple++;
					cout << endl;
				}
				C.Ajouter(TC[indexComp]);
				indexComp++;
				break;
				
			//recherche d'un trajet
			case 3:
				cout<<"vous avez choisi la recherche de trajets"<<endl;	
				cout<<"veuillez renseigner la ville de depart, la ville d'arrivee "<<endl;
				cin>>villeA>>villeB;
				endl(cout);
				C.Recherche(villeA,villeB);
				break;

			//affichage du catalogue
			case 4:
				cout<<"vous avez choisi l'affichage des trajets: "<<endl;
				endl(cout);
				C.Afficher();
				break;

                        case 5:
                                cout << "Vous avez choisi la sauvegarde du catalogue actuel"<<endl;
                                C.Sauvegarde(nb_sauv);
                                nb_sauv++;
                                break;


                        case 6:
                                cout << "Vous avez choisi de charger un catalogue depuis un fichier"<<endl;
                                C.Charger(1);
                                break;
			//fin du menu
                        case 7:
				cout<<"Au revoir"<<endl;
				arret=true;
				break;
		}
		endl(cout);
	}

	//on libère toute la mémoire allouée
	for (int i =0; i<MAX_LENGTH;i++){
		delete TS[i];
	}
    	delete [] TS;

	for (int i =0; i<MAX_LENGTH;i++){
		delete TC[i];
	}
    	delete [] TC;

	delete [] villeA;
	delete [] villeB;
	delete [] transport;
	return 0;
}
