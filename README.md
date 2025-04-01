# Jelly Simulation

## Project

Jelly Simulation is a simulation project that models the behavior of diff
erent jelly objects. The project uses numerical methods to simulate the deformation and movement of the jelly.

The simulation is implemented in C++ and uses libraries such as [libigl](https://libigl.github.io/) for geometry processing. Users can interact with the simulation through controls to manipulate the jelly and observe its dynamic responses in real-time thanks to the [ImGui library](https://github.com/ocornut/imgui).

### Hierarchy

The project structure is organized as follows:

```
JellySimulation/
├── README.md
├── CMakeLists.txt
├── src/
│   ├── generation.cpp
│   ├── main.cpp
│   ├── menu.cpp
│   ├── simulation.cpp
│   └── sources.hpp
├── cmake/
│   └── libigl/
├── models/
│   ├── cone.obj
│   ├── format_obj.py
│   └── pyramid.obj
├── build/
└── assets/
    ├── cube.png
    ├── icosahedron.png
    ├── cone.png
    ├── cylinder.png
    ├── pyramid.png
    └── pentagon.png
```

- `README.md`: This file, containing the project documentation.
- `CMakeLists.txt`: The CMake configuration file for building the project.
- `src/`: Directory containing the source code files.
- `cmake/`: Directory containing the library headers.
- `models/`: Directory containing examples .obj and a python script to formate a .obj file into a clean .obj readable by libigl.
- `build/`: Directory where the project is built.
- `assets/`: Directory containing image assets used in the gallery section.

## Compile

Compile this project using the standard cmake routine:

    mkdir build
    cd build
    cmake ..
    make

This should find and build the dependencies and create a `JellySimulation` binary.

## Run

From within the `build` directory execute the command:

    ./JellySimulation

## Controls
The simulation can be controlled using the following keyboard and mouse controls:

- `Left Mouse Button`: Rotate the camera.
- `Right Mouse Button`: Move the scene.
- `A`: Play/Pause the simulation.
- `R`: Reset the simulation.

You can also control the simulation using the GUI:
- `Play/Pause`: Toggle the simulation state.
- `Reset`: Reset the simulation to its initial state.
- `Cube`: Set the jelly shape to a cube.
- `Icosahedron`: Set the jelly shape to an icosahedron.
- `Cone`: Set the jelly shape to a cone.
- `Cylinder`: Set the jelly shape to a cylinder.
- `Pentagon`: Set the jelly shape to a pentagon.
- `Pyramid`: Set the jelly shape to a pyramid.

## Galery

### With a cube
![Cube](assets/cube.gif)

### With a icosahedron
![icosahedron](assets/icosahedron.gif)

### With a pyramid
![pyramid](assets/pyramid.gif)

### With a cone
![cone](assets/cone.gif)

### With a pentagon
![pentagon](assets/pentagon.gif)

### With a cylinder
![cylinder](assets/cylinder.gif)

## Author

This project was created by [Marie Giacomel](https://www.linkedin.com/in/marie-giacomel/).

Thank you for reading! Enjoy your Jelly simulations!
