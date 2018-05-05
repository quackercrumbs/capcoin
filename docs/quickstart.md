
# Quickstart
So you've decided to try out capcoin. The instructions listed below are to help guide you in installing the project dependencies. Then we go onto have to run capcoin.

## Requirements
Standard C++ Tools
```
 make
 gcc					#Make sure you're not using clang
 g++
 ```
 
 Additonal Libraries
[boost](https://www.boost.org/users/download/)
[Breep](https://github.com/Organic-Code/Breep)


**Notes:**

 - I recommend using your package manager to install the standard c++ tools and  the C++ boost Library. Also make sure you have the latest versions of each c++ tools.
 - Also make sure you have the correct version of boost installed for Breep to work. Check the [Breep CmakeList](https://github.com/Organic-Code/Breep/blob/master/CMakeLists.txt) to see which version to use.

For example to install boost...
- Mac OS

	```brew install boost ```
	
- Ubuntu

	```apt-get install libboost-all-dev ```
	
- Arch

	```pacman -S boost ```
	
	```pacman -S boost-libs ```

Then run ```./setup.sh``` to clone Breep and build it onto your local machine.

## Compiling and Running Code
```
make all							#This will compile capcoin
./bin/capcoin <port> [initial]		#This will start the full node client on your machine.
                                    #Use the initial flag if you're the first node in the network.
```

