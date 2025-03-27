# Jelly Simulation

## Project

Jelly Simulation is a simulation project that models the behavior of a jelly cube object. The project uses numerical methods to simulate the deformation and movement of the jelly.

The simulation is implemented in C++ and uses libraries such as [libigl](https://libigl.github.io/) for geometry processing. Users can interact with the simulation through controls to manipulate the jelly and observe its dynamic responses in real-time thanks to the [ImGui library](https://github.com/ocornut/imgui).

### Hierarchy

The project structure is organized as follows:

```
JellySimulation/
├── README.md
├── CMakeLists.txt
├── src/
│   ├── controls.cpp
│   ├── generation.cpp
│   ├── main.cpp
│   ├── simulation.cpp
│   └── sources.hpp
├── cmake/
│   └── libigl/
├── build/
└── assets/
    ├──
    └──
```

- `README.md`: This file, containing the project documentation.
- `CMakeLists.txt`: The CMake configuration file for building the project.
- `src/`: Directory containing the source code files.
- `cmake/`: Directory containing the library headers.
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

## Galery

###

## Author

This project was created by [Marie Giacomel](https://www.linkedin.com/in/marie-giacomel/).

Thank you for reading! Enjoy using the Jelly Simulation!
