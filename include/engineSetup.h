#ifndef ENGINE_SETUP_H
# define ENGINE_SETUP_H
	#include <raylib.h>
	#include <iostream>
	#include <map>
	#include <vector>

	struct SpriteFrame
	{
		Image		image;
		Texture2D	texture;
	};

	typedef std::map<std::string, std::vector<std::string>> 	TexturePath;
	typedef std::vector<SpriteFrame> 							Sprite;
	typedef std::map<std::string, Sprite> 						SpriteMap;

#endif
