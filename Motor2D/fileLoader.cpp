#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "fileLoader.h"

#include "PhysFS/include/physfs.h"
#pragma comment (lib, "PhysFS/libx86/physfs.lib")

fileLoader::fileLoader() : j1Module()
{
	
}

fileLoader:: ~fileLoader()
{

}

bool fileLoader:: Init()
{
	PHYSFS_init(NULL);
	return true;
}

bool fileLoader:: CleanUp()
{
	PHYSFS_deinit();
	return true;
}