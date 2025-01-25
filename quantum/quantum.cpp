#include "register_types.hpp"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

extern "C" {
	GDExtensionBool GDE_EXPORT quantum_gdextension_init(
		GDExtensionInterfaceGetProcAddress p_get_proc_address,
		const GDExtensionClassLibraryPtr p_library,
		GDExtensionInitialization *r_initialization
	) {
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(quantum_module_init);
		init_obj.register_terminator(quantum_module_deinit);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
