#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1FileSystem.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map
	// Remove all tilesets
	p2List_item<tileset*>* item;
	item = mapa->tileset.Trim.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}

	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	char* buf;
	int size = App->fs->Load(tmp.GetString(), &buf);
	pugi::xml_parse_result result = map_file.load_buffer(buf, size);

	RELEASE(buf);

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if (ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data

		mapa->mapversion = map_file.child("mapversion").attribute("value").as_float();

		p2SString orientation = map_file.child("orientation").attribute("value").as_string();
		if (orientation == "ortogonal")
		{
			mapa->oritype = orthogonal;
		}
		else if (orientation == "isometric")
		{
			mapa->oritype = isometric;
		}
		else if (orientation == "staggered")
		{
			mapa->oritype = isometricStaggered;
		}
		else
		{
			mapa->oritype = unknown;
		}

		p2SString renderorder = map_file.child("renderorder").attribute("value").as_string();
		if (renderorder == "right-down")
		{
			mapa->renderord = rightDown;
		}
		else if (renderorder == "right-up")
		{
			mapa->renderord = rightUp;
		}
		else if (renderorder == "left-down")
		{
			mapa->renderord = leftDown;
		}
		else if (renderorder == "left-up")
		{
			mapa->renderord = leftUp;
		}
		else
		{
			mapa->oritype = unknown;
		}

		mapa->width = map_file.child("width").attribute("value").as_uint();
		mapa->height = map_file.child("height").attribute("value").as_uint();
		mapa->tilewidth = map_file.child("tilewidth").attribute("value").as_uint();
		mapa->tileheight = map_file.child("tileheight").attribute("value").as_uint();
		mapa->nextojectid = map_file.child("nextobjectid").attribute("value").as_uint();

	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!


	// TODO 5: LOG all the data loaded
	// iterate all tilesets and LOG everything

	if (ret == true)
	{
		LOG("Successfully parsed map XML file: %s", map_file);
		LOG("width: %d height: %d", mapa->width, mapa->height);
		LOG("tile_width: %d tile_height: %d", mapa->tilewidth, mapa->tileheight);

		p2List_item<tileset*>* item = mapa->tileset.Trim.start;
		while (item != NULL)
		{
			tileset* s = item->data;
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.GetString(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tilewidth, s->tileheight);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item = item->next;
		}

		return ret;
	}
}
