#include "include/smf/smf.h"

SMF* SMF_initalizeMapfile(const char *file){
	SMF *map = (SMF*) malloc(sizeof(SMF));

	map->file = fopen(file, "rb");
	if (map->file == NULL){
		return (void*)0;
	}

	// Verify the signature
	char *sig = (char*) malloc(sizeof(char)*5);
	fread(sig, 4, 1, map->file);
	if (strcmp("smap", sig) != 0){
		return (void*)1;
	}


	// Getting the file length
	uint16_t *objCount = (uint16_t*) malloc(sizeof(uint16_t));
	fread(objCount, 2, 1, map->file);
	if (objCount <= 0){
		// Uh oh, something went wrong
		return (void*)2;
	}
	// Assign obj count to our value
	map->object_count = (*objCount);
	free(objCount);
	
	// Allocated our needed space
	map->objects = (SMF_MAP*) malloc(sizeof(SMF_MAP) * map->object_count);
	
	// Get objects
	for (uint16_t x = 0; x < map->object_count; x++){
		int res = readObject(&(map->objects[x]), map->file);
		if (res != 0){
			printf("Got Error: %d\n", res);
			return (void*)3;
		}
	}

	// Verify the ending signature
	fread(sig, 4, 1, map->file);
	if (strcmp("maps", sig) != 0){
		printf("Warning: Failed to get formal ending for file: %s\n", file);
	}
	// We've verified that both sigures exists, we don't need sig anymore
	free(sig);



	return map;
}

static int readObject(SMF_MAP *map, FILE *file){
	// Usage: Read the next object
	
	// Read the length of the 3d model file name
	uint16_t *nameLen = (uint16_t*) malloc(sizeof(uint16_t));
	fread(nameLen, 2, 1, file);
	if (nameLen <= 0){
		// Uh oh, something went wrong
		return -1;
	}

	// Read the 3d model file
	char *fileName = (char*) malloc(sizeof(char) * (*nameLen) + 1);
	fread(fileName, (*nameLen), 1, file);
	if ((strcmp("", fileName) == 0) || fileName == NULL){
		// Name broken
		return -2;
	}
	map->mapFile = fileName;

	fread(&map->x, 2, 1, file);
	if (map->x < 0){
		// Uh oh, something went wrong
		return -3;
	}
	fread(&map->y, 2, 1, file);
	if (map->y < 0){
		// Uh oh, something went wrong
		return -4;
	}
	fread(&map->z, 2, 1, file);
	if (map->z < 0){
		// Uh oh, something went wrong
		return -5;
	}

	fread(&map->rotation, 2, 1, file);
	if (map->rotation < 0){
		// Uh oh, something went wrong
		return -6;
	}
	fread(&map->x_rot, 1, 1, file);
	if (map->x_rot < 0){
		// Uh oh, something went wrong
		return -7;
	}
	fread(&map->y_rot, 1, 1, file);
	if (map->y_rot < 0){
		// Uh oh, something went wrong
		return -8;
	}
	fread(&map->z_rot, 1, 1, file);
	if (map->z_rot < 0){
		// Uh oh, something went wrong
		return -9;
	}

	fread(&map->x_scl, 2, 1, file);
	if (map->x_scl <= 0){
		// Uh oh, something went wrong
		return -10;
	}
	fread(&map->y_scl, 2, 1, file);
	if (map->y_scl <= 0){
		// Uh oh, something went wrong
		return -11;
	}
	fread(&map->z_scl, 2, 1, file);
	if (map->z_scl <= 0){
		// Uh oh, something went wrong
		return -12;
	}
	
	return 0;
}