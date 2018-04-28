# Quickstart
So you've decided to try out capcoin. The instructions listed below are to help guide you in installing the project dependencies. Then we go onto have to run capcoin.

## Requirements
Standard C++ Tools
 - cmake
 - make
 - gcc
 - g++
 
 Additonal Libraries
 - boost
 - Breep

Use your package manager to install the standard c++ tools and  the C++ boost Library.

For example to install boost...
 - Mac OS
	```brew install libboost-all-dev ```
- Ubuntu
	```apt-get install libboost-all-dev ```
- Arch
	```pacman -S boost ```
	```pacman -S boost-libs ```

Then run ```./setup.sh``` to clone Breep and build it onto your local machine.

## Compiling and Running Code
```
make all			#This will compile capcoin
./bin/capcoin		#This will start the full node client on your machine.
```

