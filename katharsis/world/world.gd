extends Node3D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var noise: FastNoiseLite = FastNoiseLite.new()
	
	print(TerrainGenerator)
	print(SimpleNoiseGenerator)
	
	var generator: SimpleNoiseGenerator = TerrainGenerator.new()
	generator.noise = noise
	
	var terrain: Terrain3D = Terrain3D.new()
	terrain.set_chunk_size(Vector3i(64, 32, 64))
	terrain.set_generator(generator)
	
	add_child(terrain)
	
	for x in range(4):
		for z in range(4):
			if terrain.genereate_chunk(Vector3i(x, 0, z)):
				terrain.build_chunk(Vector3i(x, 0, z))
	
	#var sf = ScalarField3D.create(Vector3i(64, 64, 64))
	#var mc = MarchingCubes.create(sf)
	#
	#var start = Time.get_ticks_usec()
	#for x in range(64):
		#for z in range(64):
			#var height = (noise.get_noise_2d(x, z) + 1) * 16
			#
			#for y in range(64):
				#sf.set_value(Vector3i(x, y, z), y - height)
	#var end = Time.get_ticks_usec()
	#
	#print("terrain generation (gd) took ", ((end - start) / 1000.0), "ms")
	#
	#start = Time.get_ticks_usec()
	#mc.march()
	#end = Time.get_ticks_usec()
	#
	#print("marching (cpp) took ", ((end - start) / 1000.0), "ms")
	#
	#start = Time.get_ticks_usec()
	#var mesh = mc.generate_mesh()
	#end = Time.get_ticks_usec()
	#
	#print("mesh generation (cpp) took ", ((end - start) / 1000.0), "ms")
	#
	#var mesh_instance = MeshInstance3D.new()
	#mesh_instance.mesh = mesh
	#add_child(mesh_instance)
	
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
