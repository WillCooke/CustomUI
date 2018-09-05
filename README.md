# CustomUI
- Simple C++ libnx library for creating switch-like UI homebrew apps!
- Support for Buttons Using IO::Button!
- Support for Reading and Writing to files on the SD Card using IO::readFile() and IO::writeFile

# How can I use them?

- The libs are only one header file, so it's easy to embed.
- For using default themeing (HorizonDark and HorizonLight) you'll have to add some files and folders to romfs to your project ("Graphics" and "Fonts")
- You'll need SDL2 libs, check sample's Makefile for more info about required libs, as the UI is rendered using SDL2.
- For those who used NXplay, this libs are based on it's code
