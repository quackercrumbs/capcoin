# Check if Boost folder exist in /usr/local/include
if [ -d  "/usr/local/include/boost" ]; then
    echo "Boost found."
else
    echo "Boost not found."
fi

# If Breep isn't modules, then clone the repo a build
# Note, if the repo is already there, it will assume that the project was built
if [ ! -d "modules/Breep" ]; then
    echo "Breep not found."
    echo "Press Enter to install Breep...."
    read user_input
    git clone https://github.com/Organic-Code/Breep modules/Breep
    echo "Breep clone process complete."
    echo "Press Enter proceed to build process...."
    read user_input
    cd modules/Breep
    #cmake .
    cd ../../ #return to project root dir
else
    echo "Breep found."
fi
