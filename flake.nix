{
	description = "nix development environment";
	
	inputs = {
		nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
	};

	outputs = { self, nixpkgs }:
		let
			universal = function:
				nixpkgs.lib.genAttrs [
					"x86_64-linux"
					"aarch64-linux"
				] (system: function nixpkgs.legacyPackages.${system});
		in {
			devShell = universal (pkgs: 
				(pkgs.mkShell.override { stdenv = pkgs.llvmPackages_18.libcxxStdenv; } rec {
					name = "godot";

					hardeningDisable = [ "all" ];

					llvm = "llvmPackages_18";
					clang-tools = pkgs."${llvm}".clang-tools;

					libs = with pkgs; [
						pkg-config
						
						mesa
						alsa-lib
						pulseaudio
						libGL
						wayland-scanner
						libxkbcommon
						udev
						fontconfig
						dbus
					] ++ (with pkgs.xorg; [
						libX11
						libXrandr
						libXcursor
						libXi
						libXinerama
						libXfixes.dev
						libXext
					]) ++ [
						pkgs."${llvm}".libcxx
					];

					LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath libs;
					buildInputs = libs;

					nativeBuildInputs = with pkgs; [
						pkg-config
						
						git
						
						scons
						cmake
						ninja
						
						lldb
						yasm
						zip

						emscripten
						valgrind

						godot_4
					] ++ [
						pkgs."${llvm}".clang
						pkgs."${llvm}".bintools
						clang-tools
					];

					shellHook = ''
						export EM_CACHE=$HOME/.emscripten_cache
						export EM_ROOT=${pkgs.emscripten}/share/emscripten
						export EM_SCAN_DEPS_EXE=${clang-tools}/bin/clang-scan-deps
						
						export PATH="${clang-tools}/bin:$PATH"

						ln -s ${godot_4}/bin/godot4 .clang/support/godot
					'';
				}));
		};
}
