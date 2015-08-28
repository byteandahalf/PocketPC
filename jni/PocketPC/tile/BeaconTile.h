#pragma once

#include "mcpe/tile/Tile.h"

class BeaconTile: public Tile {
public:	

	static Tile* beacon;
	
	BeaconTile(int);

	virtual const TextureUVCoordinateSet& getTexture(signed char, int);
	bool isCubeShaped();
	bool isSolidRender();
	
private:
	TextureUVCoordinateSet secondary_tex;
	TextureUVCoordinateSet terciary_tex;
	//TextureUVCoordinateSet fourth_tex;
	//TextureUVCoordinateSet fifth_tex;
};
