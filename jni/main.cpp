#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <Substrate.h>
#include <string>

#include <mcpe/client/resources/I18n.h>
#include <mcpe/item/Item.h>
#include <mcpe/tile/Tile.h>
#include <mcpe/client/renderer/TileTessellator.h>
#include <mcpe/util/Matrix.h>
#include <mcpe/client/renderer/ItemInHandRenderer.h>
#include "PocketPC/tile/BeaconTile.h"

bool duelWield = false;

//Change game version.
static std::string (*getGameVersionString_real)();
static std::string getGameVersionString_hook() {
    return "PocketPC Addon v1.0";
}

//Change item names and edit the lang.
static std::string (*I18n_get_real)(std::string const&, std::vector<std::string, std::allocator<std::string>> const&);
static std::string I18n_get_hook(std::string const& key, std::vector<std::string, std::allocator<std::string>> const& a) {
	if(key == "menu.copyright") return "©SmartDEV";
//	if(key == "menu.play") return "Singleplayer";
//We don't need this! I'm gonna redo the start menu
	return I18n_get_real(key, a);
}

//TileTesellation.
bool (*_TileTessellator$tessellateInWorld)(TileTessellator*, Tile*, const TilePos&, bool);
bool TileTessellator$tessellateInWorld(TileTessellator* self, Tile* tile, const TilePos& pos, bool b) {
	switch(tile->id) {
		case 138:
			return self->tessellateBeaconInWorld(tile, pos);
			break;
		default:
			return _TileTessellator$tessellateInWorld(self, tile, pos, b);
			break;
	}
}

//Tile Init.
void (*_Tile$initTiles)();
void Tile$initTiles() {
	_Tile$initTiles();
	BeaconTile::beacon = (Tile*)((new BeaconTile(138))->init()->setDestroyTime(1.0F)->setLightEmission(1.0F)->setNameId("beacon")->setSoundType(Tile::SOUND_GLASS));

}

//Duel wielding.
static void (*_ItemInHandRenderer$render)(ItemInHandRenderer*, float);
static void ItemInHandRenderer$render(ItemInHandRenderer* renderer, float partialTicks) {
	_ItemInHandRenderer$render(renderer, partialTicks);
	if(duelWield){
		MatrixStack::Ref matref = MatrixStack::World.push();
		Vec3 oneleft {-0.995f, -0.01f, 0.01f};
		matref.matrix->translate(oneleft);
		_ItemInHandRenderer$render(renderer, partialTicks);
	}
}

//Hook the functions.
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	void* handle = dlopen("libminecraftpe.so", RTLD_LAZY);
	void* getGameVersionString = dlsym(RTLD_DEFAULT, "_ZN6Common20getGameVersionStringEv");
	MSHookFunction(getGameVersionString, (void*)&getGameVersionString_hook, (void**)&getGameVersionString_real);
	MSHookFunction((void*) &ItemInHandRenderer::render, (void*) &ItemInHandRenderer$render, (void**) &_ItemInHandRenderer$render);
	MSHookFunction((void*) &I18n::get, (void*) &I18n_get_hook, (void**) &I18n_get_real);
	MSHookFunction((void*) &Tile::initTiles, 					(void*) &Tile$initTiles, 						(void**) &_Tile$initTiles);
	MSHookFunction((void*) &TileTessellator::tessellateInWorld, (void*) &TileTessellator$tessellateInWorld, 	(void**) &_TileTessellator$tessellateInWorld);
	
	return JNI_VERSION_1_2;
}
