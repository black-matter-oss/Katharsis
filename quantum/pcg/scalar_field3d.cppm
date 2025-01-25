module;
#include <godot_cpp/classes/node3d.hpp>
#include <types.h>

export module quantum.pcg.scalar_field3d;

using namespace godot;

export namespace quantum::pcg {

	class ScalarField3D : public Node3D {
		GDCLASS(ScalarField3D, Node3D)
	private:
		Vector3i size;
		float* data;
	protected:
		static auto _bind_methods() -> void {
			ClassDB::bind_static_method("ScalarField3D", D_METHOD("create", "size"), &ScalarField3D::create);
			ClassDB::bind_method(D_METHOD("get_value", "position"), &ScalarField3D::get_value);
			ClassDB::bind_method(D_METHOD("set_value", "position", "value"), &ScalarField3D::set_value);
			ClassDB::bind_method(D_METHOD("get_data", "index"), &ScalarField3D::get_data);
			ClassDB::bind_method(D_METHOD("set_data", "index", "value"), &ScalarField3D::set_data);
			ClassDB::bind_method(D_METHOD("get_size"), &ScalarField3D::get_size);
		}
	public:
		ScalarField3D() {
			this->size = Vector3i(0, 0, 0);
			this->data = nullptr;
		}

		~ScalarField3D() override {
			delete[] this->data;
		}

		static auto create(Vector3i size) -> ScalarField3D* {
			auto* inst = memnew(ScalarField3D);
			inst->size = size;
			inst->data = new float[size.x * size.y * size.z]();

			return inst;
		}

		auto get_value(const Vector3i position) const -> float {
			const usize index = position.x + position.y * size.x + position.z * size.x * size.y;
			return data[index];
		}

		auto set_value(const Vector3i position, const float value) -> void {
			const usize index = position.x + position.y * size.x + position.z * size.x * size.y;
			data[index] = value;
		}

		auto get_data(const usize index) const -> float { return data[index]; }
		auto set_data(const usize index, const float value) -> void { data[index] = value; }
		auto get_size() -> Vector3i { return size; }

		auto clear() -> void {
			std::fill_n(this->data, this->size.x * this->size.y * this->size.z, 0);
		}
	};
}
