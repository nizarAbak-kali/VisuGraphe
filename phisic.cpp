/**FICHIER CONTENANT LES FONCTIONS DE GESTION 
  DE LA PHISIQUE*/

struct droite_t{
  double coeff;
  double inter;
  };
typedef struct droite_t drt;

int distancepointcentre(int xa,int ya){
  return (int)sqrt(square(xa-400)+square(ya-300));//largeur/2 et longeur/2
}

int distance2points(int xa,int ya ,int xb ,int yb){
  return (int)sqrt(square(xa-xb)+square(ya-yb));

}

drt initdroite(ListDigraph::Node noeud1, ListDigraph::Node noeud2, ListDigraph::NodeMap<int>& xe ,ListDigraph::NodeMap<int>& ye){
  drt f;
  //initialisation du coefficient directeur
  f.coeff = (ye[noeud1]-ye[noeud2])/(xe[noeud1]-xe[noeud2]);
  
//cacul intersection avec l'axe des ordonnees
   f.inter=-(f.coeff*xe[noeud1])+ye[noeud1];
  return f;
}

/** fonction qui attirer deux noeuds l'un vers l'autre*/
void rapproche2noeud(ListDigraph::Node noeud1, ListDigraph::Node noeud2, ListDigraph::NodeMap<int>& xe  ,ListDigraph::NodeMap<int>& ye){
  drt f;
  //init de la droite entre noeud1 et noeud2
  f = initdroite(noeud1,noeud2,xe,ye);
 
  //distance entre deux noeuds 
  int dist = distance2points(xe[noeud1],ye[noeud],xe[noeud2],ye[noeud2]);

  //on rapproche le noeud 2 selon le coeff directeur 
  if(f.coeff>0){
    ///on choisit le noeud le plus proche du centre pour le deplacer
    //si le noeud2 est plus proche du centre cest lui qui bouge 
    if(distancepointcentre(xe[noeud2],ye[noeud2]) < distancepointcentre( xe[noeud1],ye[noeud1])){
       //QUELLE NOEUD EST AU DESSUS DE L'AUTRE ?
      
    xe[noeud2] += (int)(dist/2) ; 
    ye[noeud2] = f.coeff * xe[noeud2] + f.inter;
  }//...ou sinon le 1
    else if (distancepointcentre(xe[noeud1],ye[noeud1]) < distancepointcentre( xe[noeud2],ye[noeud2])){
 //QUELLE NOEUD EST AU DESSUS DE L'AUTRE ?
      
      xe[noeud1] += (int)(dist/2) ; 
      ye[noeud1] = f.coeff * xe[noeud1] + f.inter;
    }
  }
  
  else if(f.coeff<0){
    ///on choisit le noeud le plus proche du centre pour le deplacer
    //si le noeud2 est plus proche du centre cest lui qui bouge 
    if(distancepointcentre(xe[noeud2],ye[noeud2]) < distancepointcentre( xe[noeud1],ye[noeud1])){
 //QUELLE NOEUD EST AU DESSUS DE L'AUTRE ?
      
      xe[noeud2] -= (int)(dist/2) ; 
      ye[noeud2] = f.coeff * xe[noeud2] + f.inter;
    }//...ou sinon le 1
     else if (distancepointcentre(xe[noeud1],ye[noeud1]) < distancepointcentre( xe[noeud2],ye[noeud2])){
 //QUELLE NOEUD EST AU DESSUS DE L'AUTRE ?
      
      xe[noeud1] -= (int)(dist/2) ; 
      ye[noeud1] = f.coeff * xe[noeud1] + f.inter;
    }
    
  }
  
  
}

/** fonction qui va eloigner deux noeuds */
void eloigne2noeud(ListDigraph::Node noeud1, ListDigraph::Node noeud2, ListDigraph::NodeMap<int>& xe  ,ListDigraph::NodeMap<int>& ye){
  drt f;
  //init de la droite entre noeud1 et noeud2
  f = initdroite(noeud1,noeud2,xe,ye);
 
  //distance entre deux noeuds 
  int dist = distance2points(xe[noeud1],ye[noeud],xe[noeud2],ye[noeud2]);
  //on eloigne le noeud 2 selon le coeff directeur 
   if(f.coeff>0){
    ///on choisit le noeud le plus proche du centre pour le deplacer
    //si le noeud2 est plus eloigne du centre est lui qui bouge 
  if(distancepointcentre(xe[noeud2],ye[noeud2]) > distancepointcentre( xe[noeud1],ye[noeud1])){
    if(ye[noeud2] < ye[noeud1]){
      xe[noeud2] -= (int)(dist/2) ;// 
      ye[noeud2] = f.coeff * xe[noeud2] + f.inter;
    }
    else if (ye[noeud2] > ye[noeud1]){
      xe[noeud2] += (int)(dist/2) ; 
      ye[noeud2] = f.coeff * xe[noeud2] + f.inter;
    }
  }//...ou sinon le 1
    else if (distancepointcentre(xe[noeud1],ye[noeud1]) > distancepointcentre( xe[noeud2],ye[noeud2])){
      if(ye[noeud1]<ye[noeud2]){
	xe[noeud1] -= (int)(dist/2) ; 
	ye[noeud1] = f.coeff * xe[noeud1] + f.inter;
      }
      else if (ye[noeud1] > ye[noeud2]){
	xe[noeud1] += (int)(dist/2) ; 
	ye[noeud1] = f.coeff * xe[noeud1] + f.inter;
      }
     
    }
  }
  
  else if(f.coeff<0){
    ///on choisit le noeud le plus proche du centre pour le deplacer
    //si le noeud2 est plus eloigne du centre cest lui qui bouge 
    if(distancepointcentre(xe[noeud2],ye[noeud2]) > distancepointcentre( xe[noeud1],ye[noeud1])){
      if(ye[noeud2]<ye[noeud1]){
      xe[noeud2] += (int)(dist/2) ; 
      ye[noeud2] = f.coeff * xe[noeud2] + f.inter;
    }
    else if (ye[noeud2] > ye[noeud1]){
      xe[noeud2] -= (int)(dist/2) ; 
      ye[noeud2] = f.coeff * xe[noeud2] + f.inter;
    }
    }//...ou sinon le 1
    else if (distancepointcentre(xe[noeud1],ye[noeud1]) > distancepointcentre( xe[noeud2],ye[noeud2])){
      if(ye[noeud1]<ye[noeud2]){
	xe[noeud1] += (int)(dist/2) ; 
	ye[noeud1] = f.coeff * xe[noeud1] + f.inter;
      }
      else if (ye[noeud1] > ye[noeud2]){
	xe[noeud1] -= (int)(dist/2) ; 
	ye[noeud1] = f.coeff * xe[noeud1] + f.inter;
      }
    }
    
  }

}

//
void inverse2noeud(ListDigraph::Node noeud1, ListDigraph::Node noeud2, ListDigraph::NodeMap<int>& xe  ,ListDigraph::NodeMap<int>& ye){
  //petite fonction toutes gentille ou l'on va tranquillement inverser les coordonnes de deux point 

  int xtmp,ytmp;
  
  xtmp = xe[noeud2];
  ytmp = ye[noeud2];

  ye[noeud2] = ye[noeud1];
  xe[noeud2] = xe[noeud1];
  ye[noeud1] = ytmp;
  xe[noeud1] = xtmp;
}


bool sontcroiser(ListDigraph::Node noeud1, ListDigraph::Node noeud2,ListDigraph::Node noeud3,ListDigraph::Node noeud4, ListDigraph::NodeMap<int>& xe  ,ListDigraph::NodeMap<int>& ye){
  //detecter si deux segment sont croiser 
  //on creer d'abord les droites a partir des deux couples de noeuds 

  
  return true ;
}

//donne le nb de croisement 
int croisement(ListDigraph& g ,ListDigraph::NodeMap<int>& xe  ,ListDigraph::NodeMap<int>& ye ){
  int nbcroisement = 0;
  while(){
  //on parcours par couple de noeud
    ListDigraph::iterator noeud1(g);
    ListDigraph::iterator noeud2(g);
    ListDigraph::iterator noeud3(g);
    ListDigraph::iterator noeud4(g);
    
    
  return nbcroisement;
}
 
