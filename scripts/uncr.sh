#!/bin/bash

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null
cd ..

#../Common/scripts/showSW_Version.sh

# Uncrustify the applicaiton files
uncrustify -c Common/uncr.cfg Application/*.cpp Application/*.hpp --replace

# Do only format the main.c (actually it is genererated and manually edited)
uncrustify -c Common/uncr.cfg Core/Src/main.c --replace

# Move backup files to temporary folder
mkdir -p tmp
mv Application/*.unc-backup~ tmp
mv Application/*.unc-backup.md5~ tmp
mv Core/Src/*.unc-backup~ tmp
mv Core/Src/*.unc-backup.md5~ tmp

./Test/scripts/uncr.sh

# Back to the original location
popd > /dev/null

exit ${feedback}
