#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "fileLoader.h"

#include "PhysFS/include/physfs.h"
#pragma comment (lib, "PhysFS/libx86/physfs.lib")

fileLoader::fileLoader() : j1Module()
{
	PHYSFS_File file;
	int size;
}

fileLoader:: ~fileLoader()
{

}

bool fileLoader:: Init()
{
	PHYSFS_init(NULL);
	return true;
}

bool fileLoader::FirstRead(const char* filename)
{
	PHYSFS_File *file = PHYSFS_openRead(filename);
	if (file == NULL)
	{
		return false;
	}
	return true;
}

bool fileLoader::GetSize(int size, PHYSFS_File *file)
{
	size = PHYSFS_fileLength(file);
	if (size == NULL)
	{
		return false;
	}
	return true;
}

bool fileLoader::Read(int size, PHYSFS_File *file)
{
	char *buffer;
	buffer = new char[PHYSFS_fileLength(file)];
	int lenghtRead = PHYSFS_read(file, buffer, 1, size); // revisar render y emmagatzemar
	return true;
}

SDL_RWops* fileLoader::Load(const char* file)
{

}

bool fileLoader::Close(int size, PHYSFS_File *file)
{
	PHYSFS_close(file);
	if (PHYSFS_close(file) == 0)
	{
		return false;
	}
	return true;
}

bool fileLoader:: CleanUp()
{
	PHYSFS_deinit();
	return true;
}