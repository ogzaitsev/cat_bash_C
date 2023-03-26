all: 
	make clean
	make s21_cat

s21_cat: s21_cat.c file_reader.c parser.c file_reader.h parser.h executable_options.h
	gcc -Wall -Werror -Wextra -std=c11 s21_cat.c file_reader.c parser.c -o s21_cat


rebuild:
	make clean
	make all

clean:
	rm -rf *.o
	rm -rf s21_cat
