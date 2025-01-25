module;
#include <godot_cpp/classes/resource.hpp>
#include <types.h>

export module quantum.pcg.terrain.chunk;
import quantum.pcg;

using namespace godot;

export namespace quantum::pcg {

	class Chunk : public Resource {
		GDCLASS(Chunk, Resource)
	private:
		Vector3i coords;
		Vector3i size;

		ScalarField3D* terrain_data;
	protected:
		static void _bind_methods() {
			ClassDB::bind_static_method("Chunk", D_METHOD("create", "coords", "size", "data"), &Chunk::create);
			ClassDB::bind_method(D_METHOD("get_coords"), &Chunk::get_coords);
			ClassDB::bind_method(D_METHOD("get_world_offset"), &Chunk::get_world_offset);
			ClassDB::bind_method(D_METHOD("get_size"), &Chunk::get_size);
			ClassDB::bind_method(D_METHOD("get_terrain_data"), &Chunk::get_terrain_data);
		}
	public:
		Chunk() {
			this->coords = Vector3i(0, 0, 0);
			this->size = Vector3i(0, 0, 0);
		}

		~Chunk() override { }

		static auto create(Vector3i coords, Vector3i size, ScalarField3D* data = nullptr) -> Chunk* {
			auto* inst = memnew(Chunk);
			inst->coords = coords;
			inst->size = size;

			if(data != nullptr) inst->terrain_data = data;
			else inst->terrain_data = ScalarField3D::create(size);

			return inst;
		}

		auto get_coords() const -> Vector3i { return coords; }
		auto get_world_offset() const -> Vector3i { return { coords.x * size.x, coords.y * size.y, coords.z * size.z }; }
		auto get_size() const -> Vector3i { return size; }
		auto get_terrain_data() -> ScalarField3D* { return terrain_data; }
	};
}
