#include <BrewingStandTile.h>

BeaconTile::BeaconTile(int id) : EntityTile(id, &Material::metal) {
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

const TextureUVCoordinateSet& BrewingStandTile::getTexture(signed char side, int data) {
	return side == 0 ? tex : (side == 1 ? secondary_tex : terciary_tex);
}

TileEntity* BeaconTile::newTileEntity(const TilePos& tp) {
	return new BeaconTileEntity();
}
