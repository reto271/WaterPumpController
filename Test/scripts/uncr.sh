#!/bin/bash

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null
cd ..

#../Common/scripts/showSW_Version.sh

uncrustify -c ../Common/uncr.cfg src/*.cpp src/*.hpp --replace

mkdir -p tmp
mv src/*.unc-backup~ tmp
mv src/*.unc-backup.md5~ tmp


# Back to the original location
popd > /dev/null

exit ${feedback}
