#!/bin/bash

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null
cd ..

./scripts/showSW_Version.sh

mkdir -p tmp
if [ ! -f tmp/plantuml.jar ] ; then
    wget http://sourceforge.net/projects/plantuml/files/plantuml.jar/download -O tmp/plantuml.jar
fi

# Remove the old docu
rm -rf docu
mkdir -p docu

doxygen Common/doxyfile

#cd docu/latex
#make 2>&1 >> ../../tmp/latex.log

# Back to the original location
popd > /dev/null
