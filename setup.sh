# Check if Boost folder exist in /usr/local/include
if [ -d  "/usr/local/include/boost" ]; then
    echo "Boost found."
fi

# If boost is not found in usr/local/include (headers not found), then we clone boost and install it there
if [ ! -d "/usr/local/include/boost" ]; then
    echo "Enter any key to install boost ...."
    read user_input
    git clone --recursive https://github.com/boostorg/boost modules/boost
    cd modules/boost
    #Header files are saved in /usr/local/include
    #Libs will be saved in /usr/local/lib/
    sudo ./bootstrap.sh --prefix=/usr/local 
    sudo ./b2 install                       
    cd ../../ #return to project root dir
fi

# If Breep isn't modules, then clone the repo a build
# Note, if the repo is already there, it will assume that the project was built
if [ ! -d "modules/Breep" ]; then
    echo "Enter any key to install Breep...."
    read user_input
    git clone https://github.com/Organic-Code/Breep modules/Breep
    cd modules/Breep
    cmake .
    cd ../../ #return to project root dir
fi
