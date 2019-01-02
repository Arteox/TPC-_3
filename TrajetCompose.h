/*************************************************************************
                           TrajetCompose  -  description
                             -------------------
    début                : 19/11/2018
    copyright            : (C) 2018 par Corentin LAHAROTTE, Louis UNG, Jan-Markus GELFGREN
    e-mail               : colapala@gmail.com, ung.louis@hotmail.fr
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H
#include "Trajet.h"
#include "TrajetSimple.h"
#include <fstream>

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
//Classe qui hérite de la classe Trajet.
//Permet de contruire un trajet entre deux villes avec des escales.
//Pour accomplir cela, on appelle la classe TrajetSimple pour chaque sous-trajet.
//Pour différencier un TrajetCompose d'un TrajetSimple, un TrajetCompose est
//obligatoire construite à partir d'au moins de deux sous-trajets.
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
  
  virtual void Afficher();
    // Mode d'emploi :
    // Affiche "Trajet Compose :", puis "Sous-trajet "
	//et son numéro, puis affiche les villes de départ, d'arrivée et le moyen de transport
	//de chaque sous trajet contenu dans le TrajetCompose
    // Contrat :
    // aucun

  void Ajouter(const TrajetSimple &t);
    // Mode d'emploi :
    // Ajoute un TrajetSimple supplémentaire au TrajetCompose
    // Contrat :
    // aucun

  const char* GetDepart() const ;
    // Mode d'emploi :
    //  Renvoie la ville de départ du TrajetCompose
    // Contrat :
    // aucun

  const char* GetArrivee() const;
    // Mode d'emploi :
    // Renvoie la ville d'arrivée du TrajetCompose
    // Contrat :
    // aucun

  const char* GetTransport() const;
    // Mode d'emploi :
    // Renvoie un message d'erreur car il cette méthode ne devrait jamais être appelée.
	// On la déclare et définit uniquement pour éviter un problème de "membre virtuel pur"
    // Contrat :
    // aucun

  bool VerifContrainte(const TrajetSimple& nouvTrajet);
    // Mode d'emploi :
    // Teste si le TrajetSimple respecte les contraintes imposées par le TrajetCompose
	// C'est-à-dire si la ville d'arrivée du sous trajet précédent correspond
	// à la ville de départ du sous-trajet suivant.
    // Contrat :
    // aucun

  void Sauvegarder(ofstream& f);
  
  void SauvegardeType(ofstream& f, int typeTrajet);
  
//------------------------------------------------- Surcharge d'opérateurs
    TrajetCompose & operator = ( const TrajetCompose & unTrajetCompose );
    // Mode d'emploi : RAS
    // Contrat :
    // aucun


//-------------------------------------------- Constructeurs - destructeur
    TrajetCompose ( const TrajetCompose & unTrajetCompose );
    // Mode d'emploi (constructeur de copie) :
    // Construit un TrajetCompose à partir d'un TrajetCompose. Copie en profondeur.
    // Contrat :
    // aucun

    TrajetCompose (const TrajetSimple &t1, const TrajetSimple &t2, int nbelements );
    // Mode d'emploi :
    // Construit un TrajetCompose à partir de 2 TrajetSimples et d'un nombre d'éléments (taille du TrajetCompose) à rentrer
	// Choix de design : un TrajetCompose doit être composé au minimum de deux sous-trajets.
	// S'il est plus long, il faudra passer par la méthode Ajouter ensuite.
    // Contrat :
    // aucun

    virtual ~TrajetCompose ( );
    // Mode d'emploi :
    // Destructeur de TrajetCompose
    // Contrat :
    // aucun

    //int GetRempli();
  
    //Declaration d'amitie entre les 2 classes Catalogue et TrajeCompose
	//Permet à Catalogue d'accèder à tous les attributs et méthodes de TrajetCompose
    friend class Catalogue;

//------------------------------------------------------------------ PRIVE

 protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    int nb_SousTraj;
    int rempli;
    Trajet ** list;

};

//-------------------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TRAJETCOMPOSE_H
