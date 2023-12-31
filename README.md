# Note
This project was created for a university assignment. Due to technical issues and time restrictions the code quality is not up to the level I would have liked.
The program is an implementation of a realtime cloud simulation and rendering system and a partially functional landscape collision system. The simulation is based on https://www.researchgate.net/publication/221249075_Simulation_of_cloud_dynamics_on_graphics_hardware and the rendering uses a basic raymarching based approach.
![Cloud Example](images/Screenshot_20231214_123836.png "Cloud Example")

# Running and Building
## Requirements 
Requires minimum c++ 17.
GLEW, SDL2 and OpenImageIO must be installed and available through find_package.  
## Build on Linux

```bash
mkdir build
cd build
cmake ..
make
./cloudrenderer/cloudRenderer
```

# Notes
Code under the imgui/ folder is from https://github.com/ocornut/imgui with the exception of modifications made for it to work with CMake and is available under the MIT license.  
Code under the engine/ folder is partly derived from code which I created for a personal project prior to the assignment.  
With the exception of the above notes all other code was created for this project.
