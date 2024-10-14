# chip8

This repository is a C++ implementation of a CHIP8 emulator to run on a Linux environment using the SDL library.

To test this code you need g++, make and SDL2. If you are on Ubuntu you can install these packages with the following command:

```
sudo apt install g++ build-essential libsdl2-dev
```

To build simply type make

```
make
```

To run you need to pass a ROM file:

```
./chip8.elf -r roms/demos/Maze1.ch8
```

