class_name SimpleNoiseGenerator
extends TerrainGenerator

@export var noise: FastNoiseLite

func _generate_chunk(chunk: Chunk) -> void:
	noise.seed = get_seed()
	
	for x in range(chunk.get_size().x):
		for z in range(chunk.get_size().z):
			var height: float = (noise.get_noise_2d(x, z) + 1) * 16
			
			for y in range(chunk.get_size().y):
				chunk.get_terrain_data().set_value(Vector3i(x, y, z), y - height)
