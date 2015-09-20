#ifndef __FILELOADER_H__
#define __FILELOADER_H__

#include "j1Module.h"

class fileLoader : public j1Module
{
public:
	fileLoader();
	~fileLoader();
	bool Init();
	bool CleanUp();
	bool FirstRead(const char* filename);
	bool GetSize(int size, PHYSFS_File *file);
	bool Read(int size, PHYSFS_File *file);
	bool Close(int size, PHYSFS_File *file);

	bool LoadFile();
};

#endif