# SplineEditor

## Project

This project is a C++ application utilizing the [Libigl](https://libigl.github.io/) library to develop a fundamental spline editor.

### Hierarchy

The project structure is organized as follows:

```
SplineEditor/
├── README.md
├── CMakeLists.txt
├── src/
│   ├── b_spline.cpp
│   ├── controls.cpp
│   ├── helper.cpp
│   ├── main.cpp
│   ├── rendering.cpp
│   └── sources.hpp
├── cmake/
│   └── libigl/
├── build/
└── assets/
    ├── split_2.png
    ├── split_10.png
    └── split_50.png
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

This should find and build the dependencies and create a `SplineEditor` binary.

## Run

From within the `build` directory execute the command:

    ./SplineEditor [split] [step]

Both `[split]` and `[step]` are optional parameters that can be used to customize the behavior of the spline editor:

- **[step]** The distance to move a point
- **[split]** The number of points between two control

## Controls

Use the following controls to interact with the spline editor:

- **`Tab+click`** Selecte a point
- **`W`** Move selected point up
- **`A`** Move selected point left
- **`S`** Move selected point down
- **`D`** Move selected point right
- **`Q`** Move selected point forward
- **`E`** Move selected point
- **`H`** Display the help message
- **`C`** Display / Hide control points
- **`B`** Display / Hide surface

## Galery

### Example with split = 2

![Example with split = 2](/assets/split_2.png)

### Example with split = 10

![Example with split = 10](/assets/split_10.png)

### Example with split = 50

![Example with split = 50](/assets/split_50.png)

## Author

This project was created by [Marie Giacomel](https://www.linkedin.com/in/marie-giacomel/).

Thank you for reading! Enjoy using the SplineEditor!
