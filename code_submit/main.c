/// \file main.c
/// \author your name
/// \date Dec 2021

#include <stdio.h>
#include <stdlib.h>

#include "global.h"

int main(int argc, char **argv) {
  int i = 0;

  char **tab_balises = creer_tab_char(argc - 1);
  FILE *outfp = stdout;
  char *filename = (char *)calloc(MAX, sizeof(char));
  char *action = (char *)calloc(MAX, sizeof(char));
  char *delimiteur = ",";
  int option;
  list_candidats *l = (list_candidats *)calloc(1, sizeof(list_candidats));
  t_mat_int_dyn *t = (t_mat_int_dyn *)calloc(1, sizeof(t_mat_int_dyn));
  t_mat_int_dyn
      *duel_mat = (t_mat_int_dyn *)calloc(1, sizeof(t_mat_int_dyn));

  if (argc != NB_BALISES + 2 && argc != NB_BALISES + 3) {
    erreur("Error1: wrong format scrutin -d/-i <file> -o [file] -m <methods>, "
           "methods = {cs, cm, uni1, uni2, all}!");
    return EXIT_FAILURE;
  }

  int idx = 0;
  for (i = 1; i < argc - 1;) {
    if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-i") == 0 ||
        strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "-o") == 0) {
      if (strcmp(argv[i], "-o") == 0 && i + 1 <= argc &&
          argv[i + 1][0] == '-') {
        sprintf(tab_balises[idx], "%s", argv[i]);
        idx++;
        ++i;
      } else {
        if (strcmp(argv[i], "-m") == 0) {
          if (!(strcmp(argv[i + 1], "uni1") == 0 ||
                strcmp(argv[i + 1], "uni2") == 0 ||
                strcmp(argv[i + 1], "cm") == 0 ||
                strcmp(argv[i + 1], "cs") == 0 ||
                strcmp(argv[i + 1], "all") == 0)) {
            erreur("Error1: wrong format scrutin -d/-i <file> -o [file] -m "
                   "<methods>, methods = {cs, cm, uni1, uni2, all}!");
            return EXIT_FAILURE;
          }
        }
        sprintf(tab_balises[idx], "%s", argv[i]);
        idx++;
        sprintf(tab_balises[idx], "%s", argv[i + 1]);
        idx++;
        i += 2;
      }

    } else {
      erreur("Error1: wrong format scrutin -d/-i <file> -o [file] -m "
             "<methods>, methods = {cs, cm, uni1, uni2, all}!");
      return EXIT_FAILURE;
    }
  }

  for (i = 0; i < idx; ++i) {
    if (strcmp(tab_balises[i], "-d") == 0) {
      option = OPT_D;
      strcpy(filename, tab_balises[i + 1]);
    } else if (strcmp(tab_balises[i], "-i") == 0) {
      option = OPT_I;
      strcpy(filename, tab_balises[i + 1]);
    } else if (strcmp(tab_balises[i], "-o") == 0) {
      if (i + 1 < idx && !(strcmp(tab_balises[i + 1], "-d") == 0 ||
                           strcmp(tab_balises[i + 1], "-i") == 0 ||
                           strcmp(tab_balises[i + 1], "-m") == 0)) {
        outfp = fopen(tab_balises[i + 1], "w");
        ++i;
      }
    } else if (strcmp(tab_balises[i], "-m") == 0) {
      strcpy(action, tab_balises[i + 1]);
    }
  }

  read_voting_data(filename, delimiteur, t, option);
  read_cadidats(filename, delimiteur, l, option);

  // lựa chọn chức năng
  if (strcmp(action, "uni1") == 0) {
    if (option == OPT_D) {
      erreur("option -d is present, it disables the use of arguments uni1 and "
             "uni2 of the option -m");
      return EXIT_FAILURE;
    }
    uninominal_un_tour(*t, *l, outfp);
  } else if (strcmp(action, "uni2") == 0) {
    if (option == OPT_D) {
      erreur("option -d is present, it disables the use of arguments uni1 and "
             "uni2 of the option -m");
      return EXIT_FAILURE;
    }
    uninominal_deux_tours(*t, *l, outfp);
  } else if (strcmp(action, "cs") == 0) {
    if (option == OPT_I) {
      duel_mat = convert_to_duel_matrix(*t);
      schulze(*duel_mat, *l, outfp);
    } else {
      schulze(*t, *l, outfp);
    }
  } else if (strcmp(action, "cm") == 0) {
    if (option == OPT_I) {
      duel_mat = convert_to_duel_matrix(*t);
      minimax(*duel_mat, *l, outfp);
    } else {
      minimax(*t, *l, outfp);
    }
  }
  // action = all
  else {
    if (option == OPT_D) {
      erreur("option -d is present, it disables the use of arguments uni1 and "
             "uni2 of the option -m");
      schulze(*t, *l, outfp);
      minimax(*t, *l, outfp);
    } else {
      uninominal_un_tour(*t, *l, outfp);
      uninominal_deux_tours(*t, *l, outfp);
      duel_mat = convert_to_duel_matrix(*t);
      schulze(*duel_mat, *l, outfp);
      minimax(*duel_mat, *l, outfp);
    }
  }

  fclose(outfp);
  return EXIT_SUCCESS;
}
