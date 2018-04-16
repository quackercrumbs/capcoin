make -C .. all
if [ ! -d "googletest" ]; then
    git clone git@github.com:google/googletest googletest
fi
