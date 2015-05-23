double[] sum_col_matrix(double A[], double B[])
{
  double[] res = new double[A.length];

  for (int i = 0; i < 2; i++) {
    res[i] = A[i] + B[i];
  }

  return res ;
}

double[] diff_col_matrix(double A[], double B[])
{
  double[] res = new double[A.length];

  for (int i = 0; i < 2; i++) {
    res[i] = A[i] - B[i];
  }

  return res ;
}

double[] product_matrix(double a[], double B[][])
{
  double[] res = new double[a.length];
  double A[] = new double[a.length];

  /*
   * on copie les données de la matrice colonne donnée en argument
   * ainsi s'il s'agit de la même matrice que res
   * on évite les erreurs dues à la lecture de cette matrice
   * alors qu'elle est modifiée
   *
   */

  for (int i = 0; i < 2; i++) {
    A[i] = a[i] ;
  }

  for (int y = 0; y < 2; y++) {
    res[y] = 0 ;

    for (int i = 0; i < 2; i++) {
      res[y] += B[i][y] * A[i] ;
    }
  }

  return res ;
}

void print_col_matrix(double m[])
{
  for (int i = 0; i < 2; i++) {
    println(m[i]);
  }
  println();
}

void print_rect_matrix(double m[][]) {
  for (int x = 0; x < 2; x++) {
    for (int y = 0; y < 2; y++) {
      print(m[x][y]);
    }
    println("");
  }
  println("");
}

