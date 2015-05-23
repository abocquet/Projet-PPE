double[] position = {
  .0, -100.0
}
, target = {
  100.0, 150.0
}
, 

d = {
  .0, .0
}
;

float theta = 0 ;

void setup() {
  size(800, 800);
  frameRate(30);
}

void draw() {

  double[][] matrice_passage = {
    { 
      Math.cos(radians(theta)), Math.sin(radians(theta))
      }
      , 
    { 
      -Math.sin(radians(theta)), Math.cos(radians(theta))
      }
    };

    d = product_matrix(d, matrice_passage); //on calcul les coordonées de d dans (i, j)
  position = sum_col_matrix(d, position); // on ajoute le déplacement à la position du dirigeable

  //On calcul ensuite les coordonées de la cible dans le repère Dirigeable
  matrice_passage[0][1] *= -1;
  matrice_passage[1][0] *= -1;

  double[] tr = product_matrix(diff_col_matrix(target, position), matrice_passage);

  // puis on adapte la propulsion en fonction
  boolean avancer = false, tourner_gauche = false, tourner_droite = false ;
  float angle = degrees((float)Math.atan(tr[0]/tr[1]));
  double distance_to_target = Math.sqrt(Math.pow(tr[0], 2) + Math.pow(tr[1], 2));

  if(distance_to_target > 10){
    if (close(angle, 0, 2) && tr[1] > 0) {
      avancer = true ;
    } else if (tr[0] > 0) {
      tourner_gauche = true ;
    } else if (tr[0] < 0) {
      tourner_droite = true ;
    }
  }
  
  adapter_propulsion(avancer, tourner_gauche, tourner_droite);
  dessiner();
}

boolean close(double val, double ref, double marge) {
  return Math.abs(val - ref) <= marge ;
}

// pont entre le pilote et la simulation de position
void adapter_propulsion(boolean avancer, boolean tourner_gauche, boolean tourner_droite) {

  d[0]=.0;
  d[1]=.0;

  if (avancer) {
    d[1] = 1 ;
  }

  if (tourner_gauche) { 
    theta -= 1 ;
  }
  if (tourner_droite) { 
    theta += 1 ;
  }
}

/*******************************************
 *    GESTION DE L'AFFICHAGE (HORS PILOTE)
 *******************************************/

void dessiner() {
  background(255);

  translate(width/2, height/2);
  repere(50, color(255, 0, 0));

  pushMatrix();
  translate((int)position[0], (int)position[1]);
  rotate(radians(theta));
  repere(50, color(0, 255, 0));
  popMatrix();

  pushMatrix();
  translate((int)target[0], (int)target[1]);
  repere(50, color(0, 0, 255));
  popMatrix();

  arrow(0, 0, (int)position[0], (int)position[1]);
}

void repere(int size, color c) {

  stroke(c);
  arrow(0, 0, size, 0); 
  arrow(0, 0, 0, size);
}

void arrow(int x1, int y1, int x2, int y2) {
  line(x1, y1, x2, y2);
  pushMatrix();
  translate(x2, y2);
  float a = atan2(x1-x2, y2-y1);
  rotate(a);
  line(0, 0, -10, -10);
  line(0, 0, 10, -10);
  popMatrix();
} 

