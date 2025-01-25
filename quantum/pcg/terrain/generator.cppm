module;
#include <assert.h>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>
#include <random>

export module quantum.pcg.terrain.generator;
import quantum.pcg.terrain.chunk;

using namespace godot;

namespace quantum::pcg {

	export class TerrainGenerator : public Node {
		GDCLASS(TerrainGenerator, Node)
	private:
		int seed;
	protected:
		static void _bind_methods() {
			ClassDB::bind_static_method("TerrainGenerator", D_METHOD("create", "seed"), &TerrainGenerator::create);

			GDVIRTUAL_BIND(_generate_chunk, "chunk")
			ClassDB::bind_method(D_METHOD("generate_chunk", "chunk"), &TerrainGenerator::generate_chunk);
			ClassDB::bind_method(D_METHOD("get_seed"), &TerrainGenerator::get_seed);
			ClassDB::bind_method(D_METHOD("set_seed", "seed"), &TerrainGenerator::set_seed);
		}
	public:
		static auto create(const int seed = 0) -> TerrainGenerator* {
			auto* inst = memnew(TerrainGenerator);

			if(seed == 0) inst->seed = std::rand();
			else inst->seed = seed;

			return inst;
		}

		GDVIRTUAL1(_generate_chunk, Chunk*)

		virtual auto generate_chunk(Chunk* chunk) -> void {
			assert(GDVIRTUAL_CALL(_generate_chunk, chunk) && "generate_chunk not implemented in target class");
		}

		auto get_seed() const -> int { return seed; }
		auto set_seed(const int seed) -> void { this->seed = seed; }
	};
}
