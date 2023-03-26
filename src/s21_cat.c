#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "executable_options.h"
#include "file_reader.h"
#include "parser.h"

int main(int argc, char *argv[]) {
  struct flags cat_flags = {// structure with found flags
                            FLAG_NOT_FOUND, FLAG_NOT_FOUND, FLAG_NOT_FOUND,
                            FLAG_NOT_FOUND, FLAG_NOT_FOUND, FLAG_NOT_FOUND,
                            FLAG_NOT_FOUND, FLAG_NOT_FOUND, FLAG_NOT_FOUND};
  int file_names =
      -1;  // file_names - from this element in argv file names begin

  parse(argc, argv, &file_names, &cat_flags);
  if (file_names > 0) file_read(argc, argv, file_names, cat_flags);
  return 0;
}