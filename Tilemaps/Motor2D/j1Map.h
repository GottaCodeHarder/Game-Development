#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "p2DynArray.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!

struct tileset
{
	int firstgid;
	char* name;
	unsigned int tilewidth;
	unsigned int tileheight;
	unsigned int spacing;
	unsigned int margin;

	~tileset(){};
};

// TODO 1: Create a struct needed to hold the information to Map node
struct tilemap
{
	float mapversion = App->config.child("ORGANIZATION").attribute("value").name();
	enum orientation;
	enum renderorder;
	int width;
	int height;
	int tilewidth;
	int tileheight;
	int nextojectid;
	p2DynArray tileset;

	~tilemap(){};

};

enum orientation
{
	orthogonal = 1,
	isometric,
	isometricStaggered,
	hexagonalStaggered
};

enum renderorder
{
	rightDown = 1,
	rightUp,
	leftDown,
	leftUp
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:

public:

	// TODO 1: Add your struct for map info as public for now
	tilemap* mapa;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__