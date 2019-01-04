#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Catalogue.h"
#include "Menu.h"
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
	
	//variable pour quitter ou rester dans le menu
	bool arret=false; 
	
	TrajetSimple* S1;
	TrajetSimple* S2;
	TrajetCompose* CC;

	while(!arret){
		
		cout<<"Bonjour, et bienvenue dans notre catalogue de trajets"<<endl;
		cout<<"Tapez 1 pour ajouter un trajet simple"<<endl;
		cout<<"Tapez 2 pour ajouter un trajet compose"<<endl;
		cout<<"Tapez 3 pour faire une recherche"<<endl;
		cout<<"Tapez 4 pour afficher le catalogue"<<endl;
        cout<<"Tapez 5 pour sauvegarder le catalogue actuel"<<endl;
        cout<<"Tapez 6 pour charger un catalogue depuis un fichier"<<endl;
        cout<<"Tapez 7 pour quitter le catalogue"<<endl;


		cin>>choix;
		endl(cout);
		switch(choix){
			//Ajout d'un trajet simple
			case 1: 
			{
				
				cout<<"Vous avez choisi l'ajout de trajet simple"<<endl;
				cout<<"Veuillez renseigner la ville de depart, la ville d'arrivee et le moyen de transport"<<endl;

				cin>>villeA>>villeB>>transport;
				S1 = new TrajetSimple(villeA, villeB, transport);
				C.Ajouter(S1);
				break;
			}
				
			//Ajout d'un trajet composé
			case 2:
			{
				
				cout<<"Vous avez choisi l'ajout de trajet compose"<<endl;

				cout<<"Veuillez renseigner le nombre de trajets à ajouter"<<endl;
			
				cin>>nbElements;

				bool ErrRemplissage;
				for (int i=0;i<nbElements;i++)	{
					ErrRemplissage = true;
					
					//boucle infinie tant que l'utilisateur ne renseigne pas les infos correctement
					while (ErrRemplissage){
						cout<<"Veuillez renseigner la ville de depart, la ville d'arrivee et le moyen de transport du "<<i+1<<"e trajet"<<endl;
						cin>>villeA>>villeB>>transport;
						if (i==0 || !strcmp(villeA,S1->GetArrivee())){
							ErrRemplissage=false;
						}
						else {
							cout << "Il faut que la ville de départ corresponde à la ville d'arrivée du sous-trajet précédent. Veuillez à nouveau ressaisir un trajet valide."<<endl;
							endl(cout);
							cout <<"La ville d'arrivée du sous-trajet précédent est : " <<S1->GetArrivee() <<endl;
							endl(cout);
						}
					}
					if (i !=1){
						S1=new TrajetSimple(villeA,villeB,transport);
					}
					if(i==1){
						S2 = new TrajetSimple(villeA, villeB, transport);
						CC = new TrajetCompose(*S1, *S2, nbElements);
					}else if(i>1){
						CC->Ajouter(*S1);
					}
					cout << endl;
				}
				C.Ajouter(CC);
				delete S1;
				delete S2;
				break;
			}
				
			//recherche d'un trajet
			case 3:
				cout<<"Vous avez choisi la recherche de trajets"<<endl;	
				cout<<"Veuillez renseigner la ville de depart, la ville d'arrivee "<<endl;
				cin>>villeA>>villeB;
				endl(cout);
				C.Recherche(villeA,villeB);
				break;

			//affichage du catalogue
			case 4:
				cout<<"Vous avez choisi l'affichage des trajets: "<<endl;
				endl(cout);
				C.Afficher();
				break;

			//sauvegarde du catalogue
            case 5:
			{
                cout << "Vous avez choisi la sauvegarde du catalogue actuel"<<endl;
				cout << "Sélectionnez un critère de sélection de la sauvegarde : " << endl;
				cout << "1 : aucun critère " << endl;
				cout << "2 : par type de trajet " << endl;
				cout << "3 : par ville de départ et/ou d'arrivée" << endl;
				cout << "4 : par intervalle de trajets" << endl;
				int choix_Selec_sauvegarde;
				cin >> choix_Selec_sauvegarde;

				switch (choix_Selec_sauvegarde) 
				{
					case 1:
					{
						cout << "Vous avez choisi la sauvegarde du catalogue actuel sans critère spécifique." << endl;
						C.Sauvegarde(nb_sauv);
						break;
					}
					case 2:
					{
						cout << "Tapez 1 pour sauvegarder les trajets simples ou 2 pour sauvegarder les trajets composés" << endl;
						int typeTrajet_s;
						cin >> typeTrajet_s;
						
						ofstream fic;
						string t = "sauvegarde/sauv" + to_string(nb_sauv);
						fic.open(t);
						if (fic) {
							C.SauvegarderParType(nb_sauv, typeTrajet_s);
						}
						fic.close();
						break;
					}

					case 3:
					{
						cout << "Veuillez saisir le nom de la ville de départ ou 0 si le lieu de départ vous importe peu." << endl;
						string Dep;
						cin >> Dep;

						cout << "Veuillez saisir le nom de la ville d'arrivée ou 0 si le lieu d'arrivée vous importe peu." << endl;
						string Arr;
						cin >> Arr;

						if (Arr == "0" && Dep == "0")
						{
							C.Sauvegarde(nb_sauv);
						}
						else
						{
							C.SauvegarderParVille(nb_sauv, Dep, Arr);
						}
						break;
					}
				}
                nb_sauv++;
                break;
			}
			
			//chargement d'un catalogue
            case 6:
			{
                cout << "Vous avez choisi de charger un catalogue depuis un fichier"<<endl;
				
				//on vérifie le nombre de fichiers de sauvegarde disponibles
				ifstream fic;
				char nb_fichier;
				fic.open("sauvegarde/nb_sauv");
				if (fic) {
					fic.get(nb_fichier);
				}
				fic.close();
				
				//si aucun fichier disponible on affiche un message
				if (nb_fichier == '\0')
				{
					cout << "Aucun fichier disponible" << endl;
				}
				//si des sauvegardes sont disponibles
				else
				{
					cout << "Veuillez choisir un fichier entre 1 et " << nb_fichier << endl;
					int fichier_choisi;
					cin >> fichier_choisi;
					
					cout << "Sélectionnez un critère de sélection de chargement : " << endl;
					cout << "1 : aucun critère " << endl;
					cout << "2 : par type de trajet " << endl;
					cout << "3 : par ville de départ et/ou d'arrivée" << endl;
					cout << "4 : par intervalle de trajets" << endl;
					int choix_Selec;
					cin >> choix_Selec;
					
					switch(choix_Selec){
						case 1:
							C.Charger(fichier_choisi);
							break;
						case 2:
						{
							cout << "Tapez 1 pour ne charger que des trajets simples ou 2 pour ne charger que des trajets composés" << endl;
							int typeTrajet;
							cin >>typeTrajet;
							C.ChargerParType(typeTrajet, fichier_choisi);
							break;
						}
						case 3:
						{
							cout << "Veuillez saisir le nom de la ville de départ ou 0 si le lieu de départ vous importe peu." <<endl;
							string Dep;
							cin >> Dep;
							
							cout <<"Veuillez saisir le nom de la ville d'arrivée ou 0 si le lieu d'arrivée vous importe peu." <<endl;
							string Arr;
							cin >> Arr;
							
							if (Arr == "0" && Dep =="0")
							{
								C.Charger(fichier_choisi);
							}
							else
							{
								C.ChargerParVille(fichier_choisi, Dep, Arr);
							}
						}
					}
				}
				break;
			}
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
		//delete TS[i];
	}
    //delete [] TS;

	for (int i =0; i<MAX_LENGTH;i++){
		//delete TC[i];
	}
	//delete [] TC;
	//delete S1;
	//delete S2;
	//delete CC;
	delete [] villeA;
	delete [] villeB;
	delete [] transport;
	return 0;
}
