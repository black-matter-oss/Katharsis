module;
#include <godot_cpp/variant/vector3i.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/surface_tool.hpp>
#include <utility>
#include <vector>
#include <cmath>
#include <thread>
#include <memory>
#include <types.h>

#define ISO_LEVEL 0.0
#define THREAD_TARGET 8

export module quantum.pcg.algorithm.marching_cubes;
import :lut;
import quantum.pcg.scalar_field3d;

export namespace quantum::pcg {

	class MarchingCubes : public Object {
		GDCLASS(MarchingCubes, Object)
	private:
		ScalarField3D* scalar_field;
		std::vector<Vector3> vertices;
	protected:
		static void _bind_methods() {
			ClassDB::bind_static_method("MarchingCubes", D_METHOD("create", "scalar_field"), &MarchingCubes::create);
			ClassDB::bind_method(D_METHOD("march_single", "position"), &MarchingCubes::march_single);
			ClassDB::bind_method(D_METHOD("march"), &MarchingCubes::march);
			ClassDB::bind_method(D_METHOD("generate_mesh"), &MarchingCubes::generate_mesh);
		}
	public:
		MarchingCubes() : scalar_field(nullptr) {}

		static auto create(ScalarField3D* scalar_field) -> MarchingCubes* {
			auto* inst = memnew(MarchingCubes);
			inst->scalar_field = scalar_field;

			return inst;
		}

		auto march_single(const Vector3i position) -> void {
			const int* triangle = lut_lookup(position.x, position.y, position.z);

			for(int i = 0; i < marching_cubes_lut::TRIANGLES_HEIGHT; i++) {
				int edge_index = triangle[i];
				if(edge_index < 0) break;

				Vector2i edge = marching_cubes_lut::EDGES[edge_index];
				Vector3i a = marching_cubes_lut::POINTS[edge.x];
				Vector3i b = marching_cubes_lut::POINTS[edge.y];

				const Vector3 marched_position = vector_interpolate(
					Vector3(position.x + a.x, position.y + a.y, position.z + a.z),
					Vector3(position.x + b.x, position.y + b.y, position.z + b.z)
				);

				vertices.push_back(marched_position);
			}
		}

		auto march() -> void {
			/*int thread_count = THREAD_TARGET;
			int levels_per_thread = std::floor((this->scalar_field.get_size().y - 1) / THREAD_TARGET);

			if(levels_per_thread <= 0) thread_count = 0;

			int remaining_levels = (this->scalar_field.get_size().y - 1) % THREAD_TARGET;

			for(int i = 0; i < thread_count + 1; i++) {
				int max_level = i == thread_count ? levels_per_thread : remaining_levels;

				std::thread thread([&] {
					for(int y = 0; y < max_level; y++) {
						for(int x = 0; x < this->scalar_field.get_size().x - 1; x++) {
							for(int z = 0; z < this->scalar_field.get_size().z - 1; z++) {
								march_single(Vector3i(x, y + (i * levels_per_thread), z));
							}
						}
					}
				});

				thread.detach();
			}*/

			for(int y = 0; y < scalar_field->get_size().y - 1; y++) {
				for(int x = 0; x < scalar_field->get_size().x - 1; x++) {
					for(int z = 0; z < scalar_field->get_size().z - 1; z++) {
						march_single(Vector3i(x, y, z));
					}
				}
			}
		}

		auto generate_mesh() -> Ref<ArrayMesh> {
			const auto surface_tool = memnew(SurfaceTool);
			surface_tool->begin(Mesh::PRIMITIVE_TRIANGLES);
			surface_tool->set_smooth_group(-1); // flat shading

			for(Vector3 vertex : vertices) {
				surface_tool->add_vertex(vertex);
			}

			surface_tool->generate_normals();
			//surface_tool->generate_lod() TODO
			//surface_tool->index();

			//auto* mesh = memnew(ArrayMesh);
			//surface_tool->commit(mesh);
			auto mesh = surface_tool->commit();

			memdelete(surface_tool);
			return mesh;
		}
	protected:
		[[nodiscard]]
		auto lut_lookup(const int x, const int y, const int z) const -> const int* {
			int i = 0;

			auto size = scalar_field->get_size();

			int sf_i = x + y * size.x + z * size.x * size.y;
			i |= (scalar_field->get_data(sf_i) < ISO_LEVEL) << 0;

			sf_i += size.x * size.y;
			i |= (scalar_field->get_data(sf_i) < ISO_LEVEL) << 1;

			sf_i += 1;
			i |= (scalar_field->get_data(sf_i) < ISO_LEVEL) << 2;

			sf_i -= size.x * size.y;
			i |= (scalar_field->get_data(sf_i) < ISO_LEVEL) << 3;

			sf_i += -1 + size.x;
			i |= (scalar_field->get_data(sf_i) < ISO_LEVEL) << 4;

			sf_i += size.x * size.y;
			i |= (scalar_field->get_data(sf_i) < ISO_LEVEL) << 5;

			sf_i += 1;
			i |= (scalar_field->get_data(sf_i) < ISO_LEVEL) << 6;

			sf_i -= size.x * size.y;
			i |= (scalar_field->get_data(sf_i) < ISO_LEVEL) << 7;

			return marching_cubes_lut::TRIANGLES[i];
		}

		[[nodiscard]]
		auto vector_interpolate(const Vector3 a, const Vector3 b) const -> const Vector3 {
			const float value_a = scalar_field->get_value(a);
			const float value_b = scalar_field->get_value(b);

			return a + (ISO_LEVEL - value_a) / (value_b - value_a) * (b - a);
		}
	};
}
