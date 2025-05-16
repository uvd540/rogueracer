# Rogueracer
A turn based racing roguelike based on the classic pen and paper game [racetrack](https://en.wikipedia.org/wiki/Racetrack_(game))

Made using [raylib](http://raylib.com)

# Build instructions
The easiest way to build is to use the included cmake configuration file.
`
  # Clone the repository
  git clone https://github.com/uvd540/rogueracer.git
  # Enter the cloned directory
  cd rogueracer
  # Setup the cmake build configuration
  cmake -B . -S build
  # Build the project
  cmake --build build
  # Run the game
  .\build\Debug\rogueracer.exe
`
