#ifndef SMF_WRITER_H
#define SMF_WRITER_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct{
	uint32_t fileNameLen;
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
} SMF_WMAP;

typedef struct{
	// Object Count
	uint32_t obj_count;
	// All the objects in the map
	SMF_WMAP *objs;

} SMF_WRITE;

SMF_WRITE *SMF_makeWriteMap();

// appends an object to our map
// Use a vulkan-like parameter system, I guess 
void SMF_appendObject(SMF_WRITE *map, SMF_WMAP *params);

void SMF_writeToFile(SMF_WRITE *map, const char *file);

static void safeWrite(uint16_t num, FILE *file);

#endif