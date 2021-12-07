#ifndef SMF_H
#define SMF_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// This is the main struct that will hold all of our data
typedef struct{
	const char *mapFile;
	uint16_t x;
	uint16_t y;
	uint16_t z;

	uint16_t rotation;
	uint8_t x_rot;
	uint8_t y_rot;
	uint8_t z_rot;

	uint16_t x_scl;
	uint16_t y_scl;
	uint16_t z_scl;
} SMF_MAP;

typedef struct{
	FILE *file;
	SMF_MAP *objects;
	uint16_t object_count;
} SMF;

SMF* SMF_initalizeMapfile(const char *file);

static int readObject(SMF_MAP *map, FILE *file);


#endif