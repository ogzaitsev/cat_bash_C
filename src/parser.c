#include "parser.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "executable_options.h"

int parse(int argc, char* argv[], int* file_names, struct flags* flags) {
  const char* short_options = "benstvETh";
  const struct option long_options[] = {
      {"help", no_argument, NULL, 'h'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {"number", no_argument, NULL, 'n'},
      {"number-nonblank", no_argument, NULL, 'b'},
      {NULL, 0, NULL, 0}};
  int rez = 0;
  int option_index = -1;
  while ((rez = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {
    switch (rez) {
      case 'h': {
        printf(
            "This is help.\n"
            "for using cat type:\n"
            "cat [OPTION] [FILE]...\n"
            "Available options: b,e,n,s,t,v,E,T,h\n"
            "Or use long commands: \"help\", \"number\","
            " \"number-nonblank\", \"squeeze-blank\"\n");
        //                if (option_index < 0)
        //                    printf("short help option\n");
        //                else
        //                    printf("option_index = %d (\"%s\",%d,%c)\n",
        //                           option_index,
        //                           long_options[option_index].name,
        //                           long_options[option_index].has_arg,
        //                           long_options[option_index].val
        //                    );
        flags->flag_h = FLAG_FOUND;
        break;
      };
      case 's': {
        // printf("COMMAND squeeze-blank\n");
        flags->flag_s = FLAG_FOUND;
        break;
      };
      case 'n': {
        // printf("COMMAND number \n");
        flags->flag_n = FLAG_FOUND;
        break;
      };
      case 'b': {
        // printf("COMMAND number-nonblank \n");
        flags->flag_b = FLAG_FOUND;
        break;
      }
      case 'e': {
        // printf("COMMAND e \n");
        flags->flag_E = FLAG_FOUND;
        flags->flag_v = FLAG_FOUND;
        break;
      }
      case 't': {
        // printf("COMMAND t \n");
        flags->flag_T = FLAG_FOUND;
        flags->flag_v = FLAG_FOUND;
        break;
      }
      case 'v': {
        // printf("COMMAND v \n");
        flags->flag_v = FLAG_FOUND;
        break;
      }
      case 'E': {
        // printf("COMMAND E \n");
        flags->flag_E = FLAG_FOUND;
        break;
      }
      case 'T': {
        // printf("COMMAND T %d\n", flags->flag_T);
        flags->flag_T = FLAG_FOUND;
        break;
      }
      case '?':
      default: {
        // printf("found unknown option\n");
        break;
      }
    }
    option_index = -1;
  }
  for (int j = 1; j < argc; j++) {  // detect files after flags
    if (argv[j][0] != '-') {
      *file_names = j;
      break;
    }
  }
  return 0;
}
