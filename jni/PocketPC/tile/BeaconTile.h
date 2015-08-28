#pragma once

#include "mcpe/tile/Tile.h"
#include "mcpe/item/Item.h"
#include "mcpe/util/Random.h"

class BeaconTile: public Tile {
public:	
	BeaconTile(int);

	virtual const TextureUVCoordinateSet& getTexture(signed char, int);
	Tile* isCubeShaped()
	
private:
	TextureUVCoordinateSet secondary_tex;
	TextureUVCoordinateSet terciary_tex;
	TextureUVCoordinateSet fourty_tex;
	TextureUVCoordinateSet fifty_tex;
};
