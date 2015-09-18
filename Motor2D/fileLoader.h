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

	bool LoadFile();
};

#endif