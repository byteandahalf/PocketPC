#include "BeaconTile.h"

Tile* BeaconTile::beacon = NULL;

BeaconTile::BeaconTile(int id) : Tile(id, &Material::metal) {
	tex = getTextureUVCoordinateSet("glass", 0);
	secondary_tex = getTextureUVCoordinateSet("obsidian", 0);
	terciary_tex = getTextureUVCoordinateSet("beacon", 0);
	//fourth_tex = getTextureUVCoordinateSet("beacon_beam", 0);
	//fifth_tex = getTextureUVCoordinateSet("beacon_beam", 1);
	beacon->renderPass = Tile::glass->renderPass;
	Tile::solid[id] = false;
	Tile::lightBlock[id] = 0;
	new TileItem(id - 256);
}

bool BeaconTile::isCubeShaped() { 
     return false;
}

bool BeaconTile::isSolidRender() { 
     return false;
}

const TextureUVCoordinateSet& BeaconTile::getTexture(signed char side, int data) {
	return side == 0 ? tex : (side == 1 ? secondary_tex : terciary_tex);
}
