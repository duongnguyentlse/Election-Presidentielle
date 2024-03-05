/// \file global.c
/// \author Duong Nguyen
/// \date Dec 2021
#include "global.h"

/**
 * Print help to user
 * 
 * \return void
 */
void help() {
  
  printf(
      "%s\n",
      "Le programme doit récupérer les options de la ligne de commande.\nCes "
      "options sont normalisées sousla forme d’une balise : un tiret "
      " suivit d’une lettre, et d’un paramètre de la balise qui est une chaîne "
      "decaractères");
}

/**
 * afficher les infos sur l'écran
 * 
 * \param outfp luồng xuất thông tin
 * \param scrutin methode de scrutin
 * \param nbCandidats nombre de candidats
 * \param nbVotants nombre de votants
 * \param vainqueur vainqueur
 * \return void
 */
void affiche_resultat(FILE *outfp, char *scrutin, int nbCandidats,
                      int nbVotants, float score, char *vainqueur) {
  if (score == ERR) {
    fprintf(outfp,
            "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s\n",
            scrutin, nbCandidats, nbVotants, vainqueur);
  } else {
    fprintf(outfp,
            "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s, "
            "score = %0.2f%%\n",
            scrutin, nbCandidats, nbVotants, vainqueur, score);
  }
}

/**
 * afficher message sur l'ecran
 * 
 * \return void
 */
void erreur(char *message) { printf("%s\n", message); }

/**
 * creer un tableau entier dynamique
 * 
 * \param dim dimension
 * \return mảng một chiều
 */
int *creer_tab_int(int dim) {
  int *arr = (int *)calloc(dim, sizeof(int));

  return arr;
}

/**
 * tạo mảng xâu kí tự 1 chiều 
 * 
 * \param dim - dimension
 * \return mảng một chiều
 */
char **creer_tab_char(int dim) {
  char **arr = (char **)calloc(dim, sizeof(char *));
  int i = 0;
  for (; i < dim; ++i) {
    arr[i] = (char *)calloc(MAX, sizeof(char));
    memset(arr[i], '\0', MAX);
  }
  return arr;
}

/**
 * tạo ma trận 2 chiều
 * creer un tab dynamique a 2 dimension
 * 
 * \param nbRows số lượng dòng - nbr de lignes
 * \param nbCol số lượng cột - nbr de colonnes
 * \return ma trận 2 chiều - matrice 2 dimension
 */
int **creer_mat_int(int nbRows, int nbCol) {
  int **mat = (int **)calloc(nbRows, sizeof(int *));
  int i = 0;
  for (; i < nbRows; ++i) {
    mat[i] = (int *)calloc(nbCol, sizeof(int));
  }

  return mat;
}


/**
 * hàm count_nbVotants dùng để đếm số lượng vote, tức là đếm số lượng dòng trong
 * file chúng ta sẽ đọc cả file, đếm số lượng \n sẽ biết số lượng dòng sau đó
 * trừ 1 dòng tiêu đề sẽ ra được số lượng vote
 *
 *La fonction count_nbVotants est utilisée pour compter le nombre de votes,
 *c'est à dire en comptant le nombre de lignes dans le fichier nous lirons tout le fichier,
 *compter le nombre de \n saura le nombre de lignes puis soustraire
 *1 ligne d'entête obtiendra le nombre de votes
 * 
 * \param filename file cần đọc nội dung
 * \return số lượng bầu cử
 */
int count_nbVotants(char *filename) {
  int count = 0; // Line counter (result)
  char c;        // To store a character read from file
  FILE *fp;
  fp = fopen(filename, "r");
  for (c = getc(fp); c != EOF; c = getc(fp))
    if (c == '\n') // Increment count if this character is newline
      count = count + 1;

  // Close the file
  fclose(fp);

  // remove one header line
  return count - 1;
}


/**
 * hàm count_nbCandidats dùng để đếm số lượng ứng cử viên phụ thuộc vào option
 * option này là -d hoặc -i khi chạy chương trình
 * nếu là -d thì cần phải trừ 4 thông tin không liên quan
 * nếu là -i thì không cần phải trừ
 * thực chất là đếm số lượng delimiteur rồi công thêm 1 sẽ ra được số giá trị
 * 
 * \param filename file cần đọc nội dung
 * \param delimiteur delimiteur
 * \param option xét OPT_D hay OPT_I - vérifier si OPT_D ou OPT_I
 * \return số lượng người ứng cử - nbr de candidats
 */
int count_nbCandidats(char *filename, char *delimiteur, int option) {
  int count = 0; // Line counter (result)
  char *line = (char *)malloc(MAXINT * sizeof(char));
  memset(line, '\0', MAXINT);
  FILE *fp;
  fp = fopen(filename, "r");

  rewind(fp); // đưa con trỏ đến đâu file
  fgets(line, MAXINT, fp);

  // bây giờ sẽ đếm só lượng delimiteur
  const char *tok;
  tok = strtoke(line, delimiteur);
  while (tok != NULL) {
    count++;
    tok = strtoke(NULL, delimiteur);
  }

  // free pointer
  free(line);

  // Close the file
  fclose(fp);
  // trả về số candidats
  if (option == OPT_D) {
    return count;
  } else {
    return count - NB_UNUSED;
  }
}

/**
 * hàm này dùng để cắt chuỗi dựa vào delimiteur
 * 
 * \param str chuỗi đầu vào - entrer str
 * \param delim delimiteur
 * \return chuỗi cắt được - string
 */
char *strtoke(char *str, char *delim) {
  static char *start = NULL; /* stores string str for consecutive calls */
  char *token = NULL;        /* found token */
  /* assign new start in case */
  if (str)
    start = str;
  /* check whether text to parse left */
  if (!start)
    return NULL;
  /* remember current start as found token */
  token = start;
  /* find next occurrence of delim */
  start = strpbrk(start, delim);
  /* replace delim with terminator and move start to follower */
  if (start)
    *start++ = '\0';
  /* done */
  return token;
}

/**
 * hàm getfield dùng để lấy dữ liệu thứ num
 * ví dụ value1, value2, value 3, num = 2 thì sẽ nhận được giá trị là value2
 *
 *la fonction getfield est utilisée pour obtenir num .th data
 *par exemple valeur1, valeur2, valeur 3, num = 2 obtiendra valeur2
 *
 * \param line chuỗi đầu vào
 * \param num vị trí cần cắt
 * \param delimiteur delimiteur
 * \return chuỗi cần cắt
 */
const char *getfield(char *line, int num, char *delimiteur) {
  const char *tok;
  tok = strtoke(line, delimiteur);
  --num;
  while (num--) {
    tok = strtoke(NULL, delimiteur);
  }
  return tok;
}


/**
 * hàm read_cadidats dùng để đọc danh sách cadidats
 * option cũng tương tự với hàm phía trên, nếu là -d thì cần bỏ 4 giá trị đầu
 * còn nếu là -i thì không cần loại bỏ giá trị không cần thiết
 *
 * la fonction read_cadidats est utilisée pour lire la liste des cadidats
 * l'option est similaire à la fonction ci-dessus, si c'est -d, vous devez supprimer les 4 premières valeurs
 * et si c'est -i alors pas besoin de supprimer la valeur inutile
 *
 * \param filename file cần đọc
 * \param list danh sách ứng cử viên
 * \param delimiteur delimiteur
 * \param option xét OPT_D hay OPT_I
 * \return void
 */
void read_cadidats(char *filename, char *delimiteur, list_candidats *list,
                   int option) {
  // khởi tạo list candidats
  list->count = count_nbCandidats(filename, delimiteur, option);
  list->name = creer_tab_char(list->count);

  char *line = (char *)calloc(MAXINT, sizeof(char));
  memset(line, '\0', MAXINT);
  FILE *fp;
  fp = fopen(filename, "r");
  rewind(fp); // đưa con trỏ đến đâu file

  fgets(line, MAXINT, fp);

  // kiểu tra option
  option = option == OPT_I ? 4 : 0;

  // lấy dữ liệu
  int i = 0;
  for (; i < list->count; ++i) {
    char *temp = strdup(line);
    strcpy(list->name[i], getfield(temp, i + option + 1, delimiteur));
    free(temp);
  }

  fclose(fp);
}


/**
 * hàm read_voting_data dùng để đọc dữ liệu vote từ danh sách
 * nó cũng tương tự đối với tham số option, nếu là -d thì cần bỏ 4 cột đầu k có
 * ý nghĩa, còn -i thì không cần bỏ cột nào hết
 *
 * la fonction read_voting_data est utilisée pour lire les données de vote de la liste
 * il en est de même pour le paramètre option, si c'est -d, il faut supprimer les 4 premières colonnes
 * et avec -i, aucune colonne ne doit être supprimée
 *
 * \param filename file cần đọc
 * \param list danh sách phiếu cần đọc
 * \param delimiteur delimiteur
 * \param option xét OPT_D hay OPT_I - OPT_D or OPT_I
 * \return void
 */
void read_voting_data(char *filename, char *delimiteur, t_mat_int_dyn *list,
                      int option) {
  // khởi tạo ma trận lưu giá trị
  list->nbCol = count_nbCandidats(filename, delimiteur, option);
  list->nbRows = count_nbVotants(filename);
  list->tab = creer_mat_int(list->nbRows, list->nbCol);

  char *line = (char *)calloc(MAXINT, sizeof(char));
  memset(line, '\0', MAXINT);
  FILE *fp;
  fp = fopen(filename, "r");
  rewind(fp); // đưa con trỏ đến đâu file

  // chúng ta bỏ dòng đầu tiên, đọc nó sẽ chuyển con trỏ chuột xuống phía dưới
  fgets(line, MAXINT, fp);

  // kiểu tra option
  option = option == OPT_I ? 4 : 0;

  // lấy dữ liệu
  int i = 0, j = 0;
  for (i = 0; i < list->nbRows; ++i) {
    memset(line, '\0', MAXINT);
    // đọc dữ liệu 1 dòng
    fgets(line, MAXINT, fp);
    for (j = 0; j < list->nbCol; ++j) {
      // lấy các giá trị tương ứng
      char *temp = strdup(line);
      list->tab[i][j] = atoi(getfield(temp, j + option + 1, delimiteur));
      free(temp);
    }
  }

  fclose(fp);
}


/**
 * hàm này dùng để lấy index của người chiến thắng dựa vào phương pháp Condorcet
 * schulze với thuật toán Floyd warshall
 * 
 * \param duels_mat ma trận bầu cử
 * \return index của người chiến thắng - indice du vainqueur
 */
int get_schulze(t_mat_int_dyn duels_mat) {
  int **dist = creer_mat_int(duels_mat.nbRows, duels_mat.nbCol);
  int i, j, k, isTrue;
  // init matrix
  for (i = 0; i < duels_mat.nbRows; i++)
    for (j = 0; j < duels_mat.nbCol; j++)
      if (i != j)
        if (duels_mat.tab[i][j] > duels_mat.tab[j][i])
          dist[i][j] = duels_mat.tab[i][j];
        else
          dist[i][j] = 0;
      else
        dist[i][j] = 0;

  // Floyd Warshall
  // thật sự đây là ma trận vuông nên nbRows = nbCol
  for (i = 0; i < duels_mat.nbRows; ++i) {
    for (j = 0; j < duels_mat.nbRows; ++j) {
      if (i != j) {
        for (k = 0; k < duels_mat.nbRows; ++k) {
          if (i != k && j != k) {
            dist[j][k] = MAXI(dist[j][k], MIN(dist[j][i], dist[i][k]));
          }
        }
      }
    }
  }

  // find the candidats  E wins since p[E,X] >= p[X,E]
  // for every other candidate X
  for (i = 0; i < duels_mat.nbRows; ++i) {
    isTrue = 1;
    for (j = 0; j < duels_mat.nbRows; ++j) {
      if (i != j) {
        if (dist[i][j] >= dist[j][i]) {
          isTrue &= 1;
        } else {
          isTrue &= 0;
        }
      }
    }

    if (isTrue == 1) {
      return i;
    }
  }

  return ERR;
}


/**
 * hàm này dùng để tìm chiến thằng bằng Schulze
 * 
 * \param duels_mat ma trận bầu cử
 * \param list danh sách ứng cử viên
 * \param outfp luồng xuất thông tin
 * \return void
 */
void schulze(t_mat_int_dyn duels_mat, list_candidats list, FILE *outfp) {
  int index = get_schulze(duels_mat);

  if (index == ERR) {
    erreur("Can not find won candidats");
  } else {
    affiche_resultat(outfp, "Condorcet Schulze", duels_mat.nbCol,
                     duels_mat.tab[0][1] + duels_mat.tab[1][0], ERR,
                     list.name[index]);
  }
}


/**
 * hàm này dùng để lấy index người chiến thắng dựa vào phương pháp Condorcet
 * minimax
 *
 * cette fonction permet d'obtenir l'indice gagnant basé sur la méthode Condorcet
 * minimax
 *
 * \param duels_mat ma trận bầu cử
 * \return index của người chiến thắng
 */
int get_minimax(t_mat_int_dyn duels_mat) {
  int **dist = creer_mat_int(duels_mat.nbRows, duels_mat.nbCol);
  int i, j, index;
  // init matrix
  for (i = 0; i < duels_mat.nbRows; i++)
    for (j = 0; j < duels_mat.nbRows; j++)
      dist[i][j] = duels_mat.tab[i][j] - duels_mat.tab[j][i];

  int *score = creer_tab_int(duels_mat.nbRows);
  int _max; // dùng để lưu giá trị max score
  for (i = 0; i < duels_mat.nbRows; ++i) {
    _max = MININT;
    for (j = 0; j < duels_mat.nbRows; ++j) {
      _max = MAXI(_max, dist[j][i]);
    }
    score[i] = _max;
  }

  index = 0;
  for (i = 1; i < duels_mat.nbRows; ++i) {
    if (score[index] > score[i]) {
      index = i;
    }
  }

  return index;
}

/**
 * hàm này dùng để tìm người chiến thắng bằng minimax
 *
 * Cette fonction est utilisée pour trouver le gagnant par minimax
 *
 * \param duels_mat ma trận bầu cử
 * \param list danh sách ứng cử viên
 * \param outfp luồng xuất thông tin
 * \return void
 */
void minimax(t_mat_int_dyn duels_mat, list_candidats list, FILE *outfp) {
  int index = get_minimax(duels_mat);

  affiche_resultat(outfp, "Condorcet minimax", duels_mat.nbCol,
                   duels_mat.tab[0][1] + duels_mat.tab[1][0], ERR,
                   list.name[index]);
}

/**
 * hàm này dùng để chuyển từ danh sách phiếu bầu sang ma trận
 *
 * Cette fonction permet de convertir une liste de votes en matrice
 *
 * \param t danh sách bầu cử
 * \return ma trận được chuyển từ danh sách bầu cử
 */
t_mat_int_dyn *convert_to_duel_matrix(t_mat_int_dyn t) {
  t_mat_int_dyn *t1 = (t_mat_int_dyn *)calloc(1, sizeof(t_mat_int_dyn));

  t1->nbRows = t.nbCol;
  t1->nbCol = t.nbCol;
  t1->tab = creer_mat_int(t1->nbRows, t1->nbCol);

  int i, j, k;
  for (i = 0; i < t.nbCol; ++i) {
    for (j = 0; j < t.nbCol; ++j) {
      t1->tab[i][j] = 0;
    }
  }

  for (i = 0; i < t.nbRows; ++i) {
    for (j = 0; j < t.nbCol; ++j) {
      for (k = j + 1; k < t.nbCol; ++k) {
        if (t.tab[i][j] >= t.tab[i][k]) {
          t1->tab[k][j]++;
        } else { // if(t.tab[i][j] < t.tab[i][k]){
          t1->tab[j][k]++;
        }
      }
    }
  }

  return t1;
}


/**
 * hàm này dùng để sao chép dữ liệu từ mảng 1 chiều sang kiểu dữ liệu
 * t_tab_int_dyn
 *
 * cette fonction est utilisée pour copier les données d'un tableau à 1 dimension vers le type de données t_tab_int_dyn
 *
 * \param arr mảng đầu vào
 * \param size kích thước mảng
 * \param t biến cần được copy dữ liệu
 * \return void
 */
void copy_data(int *arr, int size, t_tab_int_dyn *t) {
  int i;
  for (i = 0; i < size; ++i) {
    t->tab[i] = arr[i];
  }
}


/**
 * hàm này dùng để tìm giá trị nhỏ nhất của 1 votant dành cho cadidats
 *
 * cette fonction permet de trouver la valeur minimale de 1 votant pour les cadidats
 * 
 * \param t dữ liệu đầu vào
 * \return giá trị nhỏ nhất
 */
int find_min_one_row(t_tab_int_dyn t) {
  int _min = t.tab[0];
  int i;
  for (i = 1; i < t.dim; ++i) {
    _min = MIN(_min, t.tab[i]);
  }

  return _min;
}

/**
 * hàm này dùng để tìm người chiến thắng uninominal_un_tour
 *
 * cette fonction est utilisée pour trouver le gagnant uninominal_un_tour
 * 
 * \param t danh sách bầu cử
 * \param list danh sách ứng cử viên
 * \param outfp luồng xuất thông tin
 * \return void
 */
void uninominal_un_tour(t_mat_int_dyn t, list_candidats l, FILE *outfp) {
  t_tab_int_dyn *temp = (t_tab_int_dyn *)calloc(1, sizeof(t_tab_int_dyn));
  temp->dim = t.nbCol;

  t_tab_int_dyn *score = (t_tab_int_dyn *)calloc(1, sizeof(t_tab_int_dyn));
  score->dim = t.nbCol;
  score->tab = creer_tab_int(score->dim);

  int i, j, _min;
  for (i = 0; i < t.nbRows; ++i) {
    temp->tab = creer_tab_int(temp->dim);
    copy_data(t.tab[i], t.nbCol, temp);
    _min = find_min_one_row(*temp);
    for (j = 0; j < t.nbCol; ++j) {
      if (t.tab[i][j] == _min) {
        score->tab[j]++;
      }
    }
  }

  _min = find_max_index(*score, ERR);

  affiche_resultat(outfp, "uninominal à un tour", score->dim, t.nbRows, ERR,
                   l.name[_min]);
}

/**
 * hàm này dùng để tìm index của giá trị lớn nhất
 *
 * cette fonction permet de trouver l'indice de la plus grande valeur
 *
 * \param t dữ liệu đầu vào
 * \param idx bỏ qua index này
 * \return index của giá trị lớn nhất
 */
int find_max_index(t_tab_int_dyn t, int idx) {
  int index = 0;
  if (idx == 0) {
    ++index;
  }
  int i;
  for (i = 0; i < t.dim; ++i) {
    if (i != idx && t.tab[index] < t.tab[i]) {
      index = i;
    }
  }

  return index;
}
/**
 * hàm này dùng để tìm người chiến thắng uninominal_deux_tours
 *
 * cette fonction permet de trouver des gagnants uninominal_deux_tours
 * 
 * \param t danh sách bầu cử
 * \param list danh sách ứng cử viên
 * \param outfp luồng xuất thông tin
 * \return void
 */
void uninominal_deux_tours(t_mat_int_dyn t, list_candidats l, FILE *outfp) {
  t_tab_int_dyn *temp = (t_tab_int_dyn *)calloc(1, sizeof(t_tab_int_dyn));
  temp->dim = t.nbCol;

  t_tab_int_dyn *score = (t_tab_int_dyn *)calloc(1, sizeof(t_tab_int_dyn));
  score->dim = t.nbCol;
  score->tab = creer_tab_int(score->dim);

  int i, j, _min, firstIndex, secondIndex, lastIndex;
  for (i = 0; i < t.nbRows; ++i) {
    temp->tab = creer_tab_int(temp->dim);
    copy_data(t.tab[i], t.nbCol, temp);
    _min = find_min_one_row(*temp);
    for (j = 0; j < t.nbCol; ++j) {
      if (t.tab[i][j] == _min) {
        score->tab[j]++;
      }
    }
  }

  firstIndex = find_max_index(*score, ERR);
  secondIndex = find_max_index(*score, firstIndex);

  score->tab[firstIndex] = score->tab[secondIndex] = 0;
  for (i = 0; i < t.nbRows; ++i) {
    if (t.tab[i][firstIndex] < t.tab[i][secondIndex]) {
      score->tab[firstIndex]++;
    } else if (t.tab[i][firstIndex] > t.tab[i][secondIndex]) {
      score->tab[secondIndex]++;
    }
  }

  lastIndex = score->tab[firstIndex] > score->tab[secondIndex] ? firstIndex
                                                               : secondIndex;

  affiche_resultat(outfp,
                   "uninominal à deux tours, tour 1 vainqueur 1 : ", score->dim,
                   t.nbRows, ERR, l.name[firstIndex]);
  affiche_resultat(outfp,
                   "uninominal à deux tours, tour 1 vainqueur 2 : ", score->dim,
                   t.nbRows, ERR, l.name[secondIndex]);
  affiche_resultat(outfp, "uninominal à deux tours, tour 2", 2, t.nbRows, ERR,
                   l.name[lastIndex]);
}
