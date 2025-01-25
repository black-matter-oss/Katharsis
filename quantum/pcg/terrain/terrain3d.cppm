module;
#include <assert.h>
#include <functional>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/time.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <map>
#include <types.h>

export module quantum.pcg.terrain.terrain3d;
import quantum.pcg.terrain.chunk;
import quantum.pcg.terrain.generator;
import quantum.pcg.algorithm.marching_cubes;

using namespace godot;

export namespace quantum::pcg {

	class Terrain3D : public Node3D {
		GDCLASS(Terrain3D, Node3D)
	private:
		Vector3i chunk_size;
		std::map<Vector3i, Chunk*> chunks;

		TerrainGenerator* generator;
	protected:
		static void _bind_methods() {
			ClassDB::bind_method(D_METHOD("genereate_chunk", "coords"), &Terrain3D::generate_chunk);
			ClassDB::bind_method(D_METHOD("regenerate_chunk", "coords"), &Terrain3D::regenerate_chunk);
			ClassDB::bind_method(D_METHOD("build_chunk", "coords"), &Terrain3D::build_chunk);
			ClassDB::bind_method(D_METHOD("get_chunk_size"), &Terrain3D::get_chunk_size);
			ClassDB::bind_method(D_METHOD("set_chunk_size", "size"), &Terrain3D::set_chunk_size);
			ClassDB::bind_method(D_METHOD("get_chunk", "coords"), &Terrain3D::get_chunk);
			ClassDB::bind_method(D_METHOD("set_generator", "generator"), &Terrain3D::set_generator);
		}
	public:
		auto generate_chunk(const Vector3i coords) -> bool {
			assert(generator);
			if(chunks.contains(coords)) return false;

			auto* chunk = Chunk::create(coords, chunk_size);
			chunks[coords] = chunk;
			generator->generate_chunk(chunk);

			return true;
		}

		auto regenerate_chunk(const Vector3i coords) -> void {
			assert(generator);

			if(!chunks.contains(coords)) {
				generate_chunk(coords);
				return;
			}

			auto* chunk = chunks[coords];
			generator->generate_chunk(chunk);
		}

		auto build_chunk(const Vector3i coords) -> void {
			assert(chunks.contains(coords));
			auto* chunk = chunks[coords];
			auto* mc = MarchingCubes::create(chunk->get_terrain_data());

			//std::thread thread([&] {
#if DEBUG_ENABLED
			uint64_t time_start = Time::get_singleton()->get_ticks_usec();
#endif

			mc->march();

#if DEBUG_ENABLED
			UtilityFunctions::print(std::format(
				"<Terrain3D::build_chunk> MarchingCubes::march took {}ms",
				(Time::get_singleton()->get_ticks_usec() - time_start) / 1000.0
			).c_str());
#endif

#if DEBUG_ENABLED
			time_start = Time::get_singleton()->get_ticks_usec();
#endif

			auto mesh = mc->generate_mesh();

#if DEBUG_ENABLED
			UtilityFunctions::print(std::format(
			"<Terrain3D::build_chunk> MarchingCubes::generate_mesh took {}ms",
			(Time::get_singleton()->get_ticks_usec() - time_start) / 1000.0
			).c_str());
#endif

			auto mesh_instance = memnew(MeshInstance3D);
			mesh_instance->set_name(coords);
			mesh_instance->set_mesh(mesh);
			mesh_instance->set_position(chunk->get_world_offset());

			add_child(mesh_instance);
			//});
			//thread.detach();
		}

		auto get_chunk_size() const -> Vector3i { return chunk_size; }
		auto set_chunk_size(const Vector3i size) -> void { chunk_size = size; }
		auto get_chunk(const Vector3i coords) -> Chunk* { return chunks[coords]; }
		auto set_generator(TerrainGenerator* generator) -> void { this->generator = generator; }
	};
}
