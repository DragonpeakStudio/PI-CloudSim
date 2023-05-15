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