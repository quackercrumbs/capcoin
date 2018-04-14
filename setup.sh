if [ ! -d "test/googletest" ]; then
    git clone git@github.com:google/googletest test/googletest
fi
if [ -d "test/googletest" ]; then
    make -C test/ all
fi
