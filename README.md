# FunnyOpenGL
### Contributions
- Use Discord VC to talk about details of engine development goals
- Update BUILD NOTES when libraries are added/removed
- Update GOALS & DESIGN REF when appropriate
### Engine Goals
- Physics (Rigidbodies)
- Entity Component System
	- Voxels (Blocks but not Microsoft)
	- Entities
- GUI
- Chunks
- Worlds/Dimensions (Need a better name, but multiple "worlds" should be able to exist on one save)
- Game Saves
- World Gen (should be an entirely interchangable system, for ease of prototyping and having different biomes etc)
	- randomness seeded with time https://www.bogotobogo.com/cplusplus/RandomNumbers.php
	- Cave generation https://www.youtube.com/watch?v=v7yyZZjF1z4&list=PLFt_AvWsXl0eZgMK_DT5_biRkWXftAOf9
- Player Settings
	- Keybinds
	- Video
	- List incomplete
- Networking
	- https://github.com/ValveSoftware/GameNetworkingSockets
		- this might be the lib but I have to look into it more in regard to the "no portforwarding" requirement
		- especially since I would like that requirement to be met even while not in the steam eco-system(in dev & releases outside of steam)
	- PnP for players (no port forwarding shananigans)
	- Dedicated Headless

Reimplement everything using custom built types/libraries where feasable/realistic
- Vector/Matrix/Quaternion Math
- Physics

Include appropriate NOTICE/LICENSE information in source & build respectively

Engine Development Complete*<br>
- new features will have to be added to the engine
- due to the scope of any game developed on top of it

### Engine Design Ref
- [Texture Atlas vs OpenGLArrayTexture](https://gamedev.stackexchange.com/questions/121567/texture-atlas-vs-array-texture-how-differently-are-they-handled-by-cpu-and-gpu)

### Build Notes
c++20
Libs
- glad v0.1.36
- glfw3 v3.3.8#2
- glm v0.9.9.8#2
- [stb_image v2.28](https://github.com/nothings/stb)
- unimplemented
	- bullet3 v3.25#1
	- assimp v5.2.5

### Design Notes
- for things that need to be differentiated quickly
	- treat red/orange/yellow/green as the same color when color coding



### VS Notes(lol)
- Extentions
	- GLSL language integration
	- Markdown Editor v2
- Keybinds
	- Edit.IncreaseLineIndent
		- -Window.NextDocumentWindowNav
		- -Diff.SwitchBetweenLeftAndRight
	- Edit.DecreaseLineIndent
		- -Edit.TabLeft