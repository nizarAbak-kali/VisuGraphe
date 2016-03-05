/*HEADER PRINCIPALE */

#ifndef BIBI
#define BIBI

#include <iostream>
#include <lemon/list_graph.h>
#include <list>
#include <vector>
#include <lemon/lgf_reader.h>
#include <SDL/SDL.h>
#include <math.h>
#include <time.h>
#include"auxi.cpp" 
#include "phisic.cpp" 

#define BLANC 0
#define NOIR 1
#define ROUGE 2
using namespace std;
using namespace lemon;

/*voici la structure qui va representer les noeuds   */
struct noeud_visu{
  //noeud present 
  ListDigraph::Node noeud;
   //coordonnes de ce noeud sur le dessin 
  int x,y;
  //Identifiant sur le graphe lemon /label 
  int id ;
  //taille sur l'image 
  int taille ;
  //liste des successeurs du noeud
  list<ListDigraph::Node> listnoeudsucc;
} ;
typedef vector<struct noeud_visu> tabnoeud;


tabnoeud initTabNoeud(SDL_Surface* ,const ListDigraph&,ListDigraph::NodeMap<int>&, ListDigraph::NodeMap<int>&);

//phisic


#endif
