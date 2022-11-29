# LightGameEngine
> Originally a coursework project of CPT205 Computer Graphics, Xi'an Jiaotong-Liverpool University

A simple and lightweight *cross-platform*[^1] C++ 3D game engine based on legacy OpenGL.

[^1]: Currently, most of the engine is cross-platform ready except for PNG texture loading in `Texture.cpp`. If you want to use this engine in Linux or macOS, you will need to modify `Texture.cpp` first. 

## Features
- Hierarchical Modelling
- Texture Mapping
- Simple physics engine
- AABB collision detection
- Heightmap Terrain

## Demo
The Demo project implemented a 3D First-person Shooter (FPS) game. To play this game, build the Demo project and run. 

### Screenshots
![image](https://user-images.githubusercontent.com/8947026/204501900-192fe914-eb63-4d68-8f8a-7c8921e51ebf.png)
![image](https://user-images.githubusercontent.com/8947026/204501922-0670d1f5-1fae-49d3-8aa2-fbc284f1ad30.png)

### Player Instructions
| Control | Action | 
| --- | --- |
| WASD | move around |
| Mouse | look around |
| Left mouse button | shoot |
| Right mouse button | use telescopic sight to aim |
| R | reload the magazine |
| Sapce | jump |


## Getting Started
### Install Dependencies
- freeglut 3.2.2
- glew 2.2.0

You can use [vcpkg](https://vcpkg.io/en/index.html) to install these dependencies. For example:
```shell
vcpkg install freeglut:x64-windows-static
vcpkg install glew:x64-windows-static
```

### Build
#### For Windows
Use Visual Studio to open `LightGameEngine.sln` solution.
#### For other OS
A `CMakeLists.txt` will be provided in the future.

## Limitations and Known Bugs
1. The current implementation of collision detection use brute-force algorithms.
2. Legacy OpenGL is used per the coursework requirement. Maybe I will rewrite this project using modern OpenGL in the future.
3. In release mode, the screen may flicker when the player moves.
