#!/bin/bash

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null
cd ..

./scripts/showSW_Version.sh

# Remove the old docu
rm -rf docu
mkdir -p docu

doxygen Common/doxyfile

#cd docu/latex
#make 2>&1 >> ../../tmp/latex.log

# Back to the original location
popd > /dev/null
