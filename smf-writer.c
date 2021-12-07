#include "include/smf/smf-writer.h"

#include <inttypes.h>

SMF_WRITE *SMF_makeWriteMap(){
	SMF_WRITE *map = (SMF_WRITE*) malloc(sizeof(SMF_WRITE));

	map->obj_count = 0;
	map->objs = NULL;

	return map;
}

// appends an object to our map
// Use a vulkan-like parameter system, I guess 
void SMF_appendObject(SMF_WRITE *map, SMF_WMAP *params){
	void *dummyVar;
	dummyVar = realloc(map->objs, sizeof(SMF_WMAP) * (map->obj_count+1));
	if (dummyVar != NULL){
		map->objs = dummyVar;
	}
	else{
		printf("Fatal error in SMF Writer, failed to realloc at line: %d", __LINE__);
		return;
	}

	map->objs[map->obj_count].fileNameLen = params->fileNameLen;
	map->objs[map->obj_count].mapFile = params->mapFile;

	map->objs[map->obj_count].x = params->x;
	map->objs[map->obj_count].y = params->y;
	map->objs[map->obj_count].z = params->z;

	map->objs[map->obj_count].rotation = params->rotation;
	map->objs[map->obj_count].x_rot = params->x_rot;
	map->objs[map->obj_count].y_rot = params->y_rot;
	map->objs[map->obj_count].z_rot = params->z_rot;

	map->objs[map->obj_count].x_scl = params->x_scl;
	map->objs[map->obj_count].y_scl = params->y_scl;
	map->objs[map->obj_count].z_scl = params->z_scl;

	map->obj_count++;

	

}

void SMF_writeToFile(SMF_WRITE *map, const char *file){
	FILE *_file = fopen(file, "wb");
	fputs("smap", _file);
	printf("Got: %d\n", map->obj_count);
	safeWrite(map->obj_count, _file);

	for (int o = 0; o<map->obj_count; o++){
		safeWrite(map->objs[o].fileNameLen, _file);
		fputs(map->objs[o].mapFile, _file);

		// Use safe write as it is 2 bytes
		safeWrite(map->objs[o].x, _file);
		safeWrite(map->objs[o].y, _file);
		safeWrite(map->objs[o].z, _file);

		safeWrite(map->objs[o].rotation, _file);
		// No need for safe write, 1 byte
		fputc(map->objs[o].x_rot, _file);
		fputc(map->objs[o].y_rot, _file);
		fputc(map->objs[o].z_rot, _file);

		safeWrite(map->objs[o].x_scl, _file);
		safeWrite(map->objs[o].y_scl, _file);
		safeWrite(map->objs[o].z_scl, _file);
	}

	// Put ending signature
	fputs("maps", _file);


	fclose(_file);
}


static void safeWrite(uint16_t num, FILE *file){
	// Safely write both bytes with accounting for big/little edian of OS
	fputc((num>>0), file);
	fputc((num>>8), file);
}