#include "file_reader.h"

#include <stdio.h>
#include <stdlib.h>

#include "executable_options.h"

int file_read(int argc, char *argv[], int file_names, struct flags flags) {
  for (int i = file_names; i < argc; i++) {
    FILE *filep;
    filep = fopen(argv[i], "r");
    if (filep == NULL) {
      fprintf(stderr, "\n%s: No such file or directory\n", argv[i]);
      exit(1);
    }
    int ch;
    int line_number = 1;
    int newlines = 0;
    int file_begun = 1;

    if (flags.flag_n == FLAG_FOUND) {  // OPTION n b
      if (flags.flag_b == FLAG_NOT_FOUND) printf("     %d\t", line_number);
      // if (flags.flag_b == FLAG_FOUND) line_number++;
    }
    while ((ch = fgetc(filep)) != EOF) {
      if (flags.flag_b == FLAG_FOUND && file_begun == 1 && ch != '\n') {
        printf("%6d\t", line_number);
        line_number++;
      }

      if (flags.flag_n == FLAG_FOUND && flags.flag_b == FLAG_NOT_FOUND &&
          newlines > 0) {  //  n
        if (!(flags.flag_b == FLAG_FOUND && file_begun == 1 && ch == '\n') &&
            !(flags.flag_s == FLAG_FOUND && newlines > 2) &&
            !(flags.flag_s == FLAG_FOUND && file_begun == 1 && newlines > 1)) {
          printf("%6d\t", line_number);
          if (flags.flag_b == FLAG_FOUND) line_number++;
        }
      } else if (!(flags.flag_b == FLAG_FOUND && file_begun == 1 &&
                   ch == '\n') &&
                 flags.flag_b == FLAG_FOUND && (newlines > 0 && ch != '\n') &&
                 file_begun != 1) {  // b
        printf("%6d\t", line_number);
        line_number++;
      }

      if (ch != '\n') {
        file_begun = 0;
      }

      if (ch == '\n') {
        newlines++;
        if (flags.flag_b == FLAG_NOT_FOUND) line_number++;
      } else {
        newlines = 0;
      }

      if ((flags.flag_s == FLAG_FOUND && newlines > 2 && ch == '\n') ||
          (flags.flag_s == FLAG_FOUND && file_begun == 1 && newlines > 1 &&
           ch == '\n')) {  //  s
        if (flags.flag_n == FLAG_FOUND && flags.flag_b == FLAG_NOT_FOUND)
          line_number--;
        continue;
      }

      if (flags.flag_v == FLAG_FOUND && ch > 0 && ch < 32 && ch != '\n' &&
          ch != '\t') {
        char nonprinting = ch + 64;
        printf("^%c", nonprinting);
        continue;
      } else if (flags.flag_v == FLAG_FOUND && ch == 127) {
        printf("^?");
        continue;
      } else if (flags.flag_v == FLAG_FOUND && ch > 127 && ch < 160) {
        printf("M-%c", ch - 64);
        continue;
      } else if (flags.flag_v == FLAG_FOUND && ch >= 160 && ch < 255) {
        printf("M-%c", ch - 128);
        continue;
      } else if (flags.flag_v == FLAG_FOUND && ch >= 255) {
        printf("M-^?");
        continue;
      } else if (flags.flag_v == FLAG_FOUND && ch == 0) {
        printf("^@");
        continue;
      }

      if (flags.flag_E == FLAG_FOUND && ch == '\n') {
        printf("$");
      }

      if (flags.flag_T == FLAG_FOUND && ch == '\t') {
        printf("^I");
        continue;
      }
      printf("%c", ch);
    }
  }
  return 0;
}
