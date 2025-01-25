#include "register_types.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

import quantum;

using namespace godot;
using namespace quantum;

void quantum_module_init(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(pcg::ScalarField3D);
	GDREGISTER_CLASS(pcg::Chunk);
	GDREGISTER_CLASS(pcg::Terrain3D);
	GDREGISTER_ABSTRACT_CLASS(pcg::TerrainGenerator);
	GDREGISTER_CLASS(pcg::MarchingCubes);
}

void quantum_module_deinit(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
