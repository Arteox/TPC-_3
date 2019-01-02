/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : 19/11/2018
    copyright            : (C) 2018 par Corentin LAHAROTTE, Louis UNG, Jan-Markus GELFGREN
    e-mail               : colapala@gmail.com, ung.louis@hotmail.fr
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
//Classe qui hérite de la classe Trajet.
//Cette classe permet de créer un trajet simple 
//entre 2 villes en précisant le moyen de transport utilisé.
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

  virtual void Afficher();
    // Mode d'emploi :
    //  Affiche les villes de départ, d'arrivée et le moyen de transport
    // Contrat :
    // aucun

  const char* GetDepart() const;
    // Mode d'emploi :
    //  Renvoie la ville de départ
    // Contrat :
    // aucun

  const char* GetArrivee() const ;
    // Mode d'emploi :
    //  Renvoie la ville d'Arrivée
    // Contrat : 
    // aucun

  const char* GetTransport() const;
    // Mode d'emploi :
    //  Renvoie le moyen de Transport
    // Contrat : 
    // aucun

  void Sauvegarder(ofstream& f);

  void SauvegardeType(ofstream& f, int typeTrajet);

//------------------------------------------------- Surcharge d'opérateurs
    TrajetSimple & operator = ( const TrajetSimple & unTrajetSimple );
    // Mode d'emploi :
    //  Fait une copie des paramètres de unTrajetSimple dans les paramètres du TrajetSimple appelé
    // Contrat : 
    // aucun

//-------------------------------------------- Constructeurs - destructeur
    TrajetSimple ( const TrajetSimple & unTrajetSimple );
    // Mode d'emploi (constructeur de copie) :
    //  Construit un trajetSimple à partir d'un trajetSimple (en surface)
    // Contrat : 
    // aucun

    TrajetSimple(const char* depart,const char * arrivee,const char * t );
    // Mode d'emploi :
    //  Construit un trajetSimple à partir d'une ville de départ, d'une ville d'arrivée et d'un moyen de Transport
    // Contrat :
    // aucun
    
    TrajetSimple ();
    // Mode d'emploi :
    //  Constructeur par défaut.
	// Sert uniquement pour le traçage des appels de constructeurs.
    // Contrat :
    // aucun

    virtual ~TrajetSimple ( );
    // Mode d'emploi :
    // Destructeur de TrajetSimple
    // Contrat :
    // aucun

    friend class Menu;
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    char* Transport;
    char* Depart;
    char* Arrivee;
};

//-------------------------------- Autres définitions dépendantes de <TrajetSimple>

#endif // TRAJETSIMPLE_H

