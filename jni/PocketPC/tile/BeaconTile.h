#pragma once

#include "mcpe/tile/EntityTile.h"
#include "mcpe/item/Item.h"
#include "mcpe/util/Random.h"
#include "mcpe/world/level/tileentity/BeaconTileEntity.h"

class BeaconTile: public EntityTile {
public:	
	BeaconTile(int);

	virtual const TextureUVCoordinateSet& getTexture(signed char, int);
	virtual TileEntity* newTileEntity(const TilePos &);
	
private:
	TextureUVCoordinateSet secondary_tex;
};
