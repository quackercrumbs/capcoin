#Install and build Breep if it is not found in modules
if [ ! -d "modules/Breep" ]; then
    echo "Enter any key to install Breep...."
    read user_input
    git clone git@github.com:Organic-Code/Breep.git modules/Breep
    cd modules/Breep
    cmake .
    cd ../../ #return to project root dir
fi


if [ -d  "/usr/local/include/boost" ]; then
    echo "Boost found."
fi

#Install and build boost if it is not found in user/local/include (headers not found)
if [ ! -d "/usr/local/include/boost" ]; then
    echo "Enter any key to install boost ...."
    read user_input
    git clone --recursive git@github.com:boostorg/boost.git modules/boost
    cd modules/boost
    #Header files are saved in /usr/local/include
    #Libs will be saved in /usr/local/lib/
    sudo ./bootstrap.sh --prefix=/usr/local 
    sudo ./b2 install                       
    cd ../../ #return to project root dir
fi
