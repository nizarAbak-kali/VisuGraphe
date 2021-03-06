/*
  ABAK-KALI Nizar 
 
  Visualisation de graphe
  
  ALGO COMBI MR VITTAUT 

*/
/*
visu.cpp est le fichier principale 
contenant le main 
*/
#include"myheader.h"




tabnoeud initTabNoeud(SDL_Surface* s,const ListDigraph& g, ListDigraph::NodeMap<int>& xe, ListDigraph::NodeMap<int>& ye){
  //on parcours le graph et rempli la struct noeud
  srand(time(NULL));
  tabnoeud tab;
  struct noeud_visu n;
  //decoupage de l'image selon le nb de noeud
  int part = (int) (s->w)/countNodes(g);
  int indice=0;
  int k = 0;
  
  for(ListDigraph::NodeIt it(g);it!=INVALID ;++it){
    n.noeud = it;
    n.taille=part/countNodes(g);
    /* n.x = k*part;
       n.y = (s->h)/2;*/
    xe[it]=(rand()+n.taille)%s->w ;
    ye[it]=(rand()+n.taille)%s->h;
    
    n.id = g.id(it);
    cout<<"noeud: "<<n.id<<" ";
    cout<<"coordonnes x: "<<xe[it]<<" ";
    cout<<"coordonnes y: "<<ye[it]<<" ";
    cout<<endl;
    k++;
    for(ListDigraph::OutArcIt outa(g,outa);outa!=INVALID;++outa){
      n.listnoeudsucc.push_back(g.target(outa));
    }
    tab.push_back(n);
  }
  return tab;
}


//fonction de gestion des evenement 
static int sdlManageEvents(SDL_Surface * s) {
  static int active = 1;
  SDL_Event event;
  while(SDL_PollEvent(&event)) 
    switch (event.type) {
    case SDL_QUIT:
	exit(1);
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym) {
      case SDLK_ESCAPE:
	exit(1);
      default:
	fprintf(stderr, "La touche %s a ete pressee\n",
		SDL_GetKeyName(event.key.keysym.sym));
	break;
      }
    }
}

//fonction quii sert a l'initialisation de SDL
static SDL_Surface* initSDL(int w,int h){
  SDL_Surface * s;
  const SDL_VideoInfo * vi = NULL;

  if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
    fprintf(stderr, "Impossible d'initialiser SDL: %s\n", SDL_GetError());
    exit(1);
  }
  
  if ( (s = SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE|SDL_DOUBLEBUF  )) == NULL ) {
    fprintf(stderr, "Impossible d'ouvrir le mode video : %s\n", SDL_GetError());
    exit(1);
  }
  return s;
}
//fonctions qui dessine les noeud selon la structure 
void DrawNode(SDL_Surface* s,tabnoeud tab,Uint32* color, ListDigraph::NodeMap<int>& xe , ListDigraph::NodeMap<int>& ye){
  //penser a rajouter les indices en ttf dans le cercle pour plus de lisibilité
   for(tabnoeud::iterator it = tab.begin(); it != tab.end() ; ++it){
     cercle(s,xe[(*it).noeud],ye[(*it).noeud], (*it).taille , color[NOIR]);

   }
}
//dessin des arcs 
void DrawArcs(const ListDigraph& g,SDL_Surface* s, tabnoeud tab,Uint32* color, ListDigraph::NodeMap<int>& xe , ListDigraph::NodeMap<int>& ye){
  ListDigraph::Node cible;
  for(tabnoeud::iterator itnode = tab.begin(); itnode != tab.end() ; ++itnode){
    for(ListDigraph::OutArcIt it(g,((*itnode).noeud));it != INVALID;++it){
      cible = g.target(it);
      arrow(s, xe[(*itnode).noeud], ye[(*itnode).noeud], xe[cible], ye[cible],color[ROUGE]);
    }
  }
}

void sdlDraw(const ListDigraph& g,SDL_Surface * s,Uint32* color,tabnoeud tab, ListDigraph::NodeMap<int>& xe , ListDigraph::NodeMap<int>& ye){
 

 DrawNode(s,tab,color,xe,ye);
  DrawArcs(g,s,tab,color,xe,ye);
}

//fonction contenant la boucle principale 
void sdlLoop(const ListDigraph& g,SDL_Surface * s,Uint32* color) {
  tabnoeud tab;
  ListDigraph::NodeMap<int> coordonnee_x(g);
  ListDigraph::NodeMap<int> coordonnee_y(g);
  tab = initTabNoeud(s,g,coordonnee_x,coordonnee_y);
  for(;;) {
    //si aucune touche n'a été appuyer
    while(sdlManageEvents(s)) SDL_Delay(1);
    sdlDraw(g,s,color,tab,coordonnee_x,coordonnee_y);
    SDL_Flip(s);
  }
}



//penser a parcourrir d'edges en edges 

// static void DrawEdge(const ListDigraph& g,SDL_Surface* s, tabnoeud tab,Uint32* color){
//   for(tabnoeud::iterator itnode = tab.begin(); itnode != tab.end() ; ++itnode){
//     for(Listgraph::EdgeIt it(g);it != INVALID;++it){
      
//     }
//   }
// }

//dessin des arcs sortants

int main(int _ac,char** _av){
  SDL_Surface* ecran;
  ecran=initSDL(800,600);
  
  ListDigraph g;
  
  Uint32 color[10];
  color[0] = SDL_MapRGB(ecran->format,255,255,255); //Blanc
  color[1] = SDL_MapRGB(ecran->format,0,0,0);//Noir
  color[2] = SDL_MapRGB(ecran->format,255,0,0); //Rouge

  SDL_FillRect(ecran, NULL, color[0]);
  SDL_Flip(ecran);
  SDL_WM_SetCaption("Visu graphe", NULL);
  //si pas bon nb de parametre 
  if(_ac != 2){
    cout<<"Erreur : Manque le .lgf a afficher "<<endl;
    cout<<"Usage : ./visugraphe mongraphe_a_afficher.lgf"<<endl;
    SDL_Quit();
    return EXIT_FAILURE;
  }
  else{
    //charge le graph 
    try{
      digraphReader(g,_av[1]).
	run();
    }
    catch(Exception& error){
      std::cerr << "Error: " << error.what() << std::endl;
      return -1;
    }
    //boucle principale
    sdlLoop(g,ecran,color); 
  }
  
  SDL_Quit();
  return EXIT_SUCCESS;
}
