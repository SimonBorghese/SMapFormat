CC=gcc

FLAGS=-O3 -Wall

.PHONY: shared

LIBNAME=libsmap.so

FILES=smf.c smf-writer.c

shared:
	$(CC) -shared $(FLAGS) -o $(LIBNAME) $(FILES)

