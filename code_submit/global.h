/// \file global.h
/// \author Duong Nguyen
/// \date Dec 2021

#ifndef GLOBAL_H
#define GLOBAL_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NB_BALISES 4
#define NB_METHODES 5
#define OPT_I 0
#define OPT_D 1
#define OPT_O 2
#define OPT_M 3
#define OPT_H -1
#define SUCCESS 1
#define ERR -2
#define NB_UNUSED 4 // \def< sỐ lượng dữ liệu không dùng như id, ngày,../

#define MAX 300      /// \def< longueur maximale de la ligne dans le fichier
#define MAXINT 1000  /// \def< entier max utile dans le programme
#define MININT -1000 /// \def< entier min utile dans le programme
#define LONGMOTS 30  /// \def< longueur max d'une chaîne de caractères
#define NBCOLADM                                                               \
  3 /// \def< nb de colonnes administratives avant la colonne du premier choix
#define KO -1          /// \def< pas bon ou vide
#define OK 0           /// \def< bon
#define NBMAXOPTIONS 4 /// \def < ça parle en soi.
//
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAXI(a, b) (((a) > (b)) ? (a) : (b))

/// \struct pour encapsuler des tableaux dynamiques d'entiers avec la dimension.
typedef struct s_tab_dyn {
  int *tab;
  int dim;
} t_tab_int_dyn;

typedef struct s_mat_dyn {
  int **tab;
  int nbRows;
  int nbCol;
} t_mat_int_dyn;

/// \struct khai báo cấu trúc dữ liệu dùng để lưu danh sách cadidats
typedef struct List_Candidats {
  char **name;
  int count;
} list_candidats;


/**
 * Print help to user
 * 
 * \return void
 */
void help();

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
                      int nbVotants, float score, char *vainqueur);

/**
 * afficher message sur l'ecran
 * 
 * \return void
 */                      
void erreur(char *message);

/**
 * creer un tableau entier dynamique
 *
 * \param dim dimension
 * \return mảng một chiều
 */
int *creer_tab_int(int dim);

/**
 * tạo mảng xâu kí tự 1 chiều
 *
 * \param dim - dimension
 * \return mảng một chiều
 */
char **creer_tab_char(int dim);

/**
 * tạo ma trận 2 chiều
 * creer un tab dynamique a 2 dimension
 *
 * \param nbRows số lượng dòng - nbr de lignes
 * \param nbCol số lượng cột - nbr de colonnes
 * \return ma trận 2 chiều - matrice 2 dimension
 */
int **creer_mat_int(int nbRows, int nbCol);

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
int count_nbVotants(char *filename);

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
int count_nbCandidats(char *filename, char *delimiteur, int option);

/**
 * hàm này dùng để cắt chuỗi dựa vào delimiteur
 *
 * \param str chuỗi đầu vào - entrer str
 * \param delim delimiteur
 * \return chuỗi cắt được - string
 */
char *strtoke(char *str, char *delim);

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
 */const char *getfield(char *line, int num, char *delimiteur);

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
                   int option);

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
                      int option);


/**
 * hàm này dùng để lấy index của người chiến thắng dựa vào phương pháp Condorcet
 * schulze với thuật toán Floyd warshall
 *
 * \param duels_mat ma trận bầu cử
 * \return index của người chiến thắng - indice du vainqueur
 */

int get_schulze(t_mat_int_dyn duels_mat);


/**
 * hàm này dùng để tìm chiến thằng bằng Schulze
 * 
 * \param duels_mat ma trận bầu cử
 * \param list danh sách ứng cử viên
 * \param outfp luồng xuất thông tin
 * \return void
 */
void schulze(t_mat_int_dyn duels_mat, list_candidats list, FILE *outfp);

/**
 * hàm này dùng để lấy index người chiến thắng dựa vào phương pháp Condorcet
 * minimax https://en.wikipedia.org/wiki/Minimax_Condorcet_method#Example_with_Condorcet_winner
 *
 * cette fonction permet d'obtenir l'indice gagnant basé sur la méthode Condorcet
 * minimax
 *
 * \param duels_mat ma trận bầu cử
 * \return index của người chiến thắng
 */
int get_minimax(t_mat_int_dyn duels_mat);


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
void minimax(t_mat_int_dyn duels_mat, list_candidats list, FILE *outfp);


/**
 * hàm này dùng để chuyển từ danh sách phiếu bầu sang ma trận
 *
 * Cette fonction permet de convertir une liste de votes en matrice
 *
 * \param t danh sách bầu cử
 * \return ma trận được chuyển từ danh sách bầu cử
 */
t_mat_int_dyn* convert_to_duel_matrix(t_mat_int_dyn t);


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
void copy_data(int *arr, int size, t_tab_int_dyn *t);

/**
 * hàm này dùng để tìm giá trị nhỏ nhất của 1 votant dành cho cadidats
 *
 * cette fonction permet de trouver la valeur minimale de 1 votant pour les cadidats
 *
 * \param t dữ liệu đầu vào
 * \return giá trị nhỏ nhất
 */
int find_min_one_row(t_tab_int_dyn t);

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
void uninominal_un_tour(t_mat_int_dyn t, list_candidats l, FILE *outfp);

/**
 * hàm này dùng để tìm người chiến thắng uninominal_deux_tours
 * 
 * \param t danh sách bầu cử
 * \param list danh sách ứng cử viên
 * \param outfp luồng xuất thông tin
 * \return void
 */
void uninominal_deux_tours(t_mat_int_dyn t, list_candidats l, FILE *outfp);

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
int find_max_index(t_tab_int_dyn t, int index);
#endif
