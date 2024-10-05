#ifndef ENGINE_SETUP_H
# define ENGINE_SETUP_H
	#if (__APPLE__ || __MACH__)
		#include "../lib/raylib/src/raylib.h"
	#else
		#include <raylib.h>
	#endif
	#include <iostream>
	#include <map>
	#include <vector>
	#include <algorithm>
	#include <array>
	#include <strings.h>
	#include <string.h>

	#define VECTOR_RESERVE 100

	struct Hitbox
	{
		Rectangle	box;
		Vector2		offset;
	};

	struct SpriteFrame
	{
		Image		image;
		Texture2D	texture;
	};

	typedef std::map<std::string, std::vector<std::string>> 	TexturePath;
	typedef std::vector<SpriteFrame> 							Sprite;
	typedef std::map<std::string, Sprite> 						SpriteMap;

#endif
