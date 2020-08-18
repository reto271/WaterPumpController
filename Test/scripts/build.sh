#!/bin/bash

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null

#../../Common/scripts/showSW_Version.sh

# Offer option -v : verbose
VERBOSE=0
if [ 1 -eq $# ] ; then
    if [ "-v" == "$1" ] ; then
        VERBOSE=1
    fi
fi

# Cmake followed by make...
mkdir -p ../bin
cd ../bin
cmake ..
feedback=$?
echo "cmake feedback: ${feedback}"
if [ 0 -eq ${feedback} ] ; then
    if [ 1 -eq ${VERBOSE} ] ; then
        make VERBOSE=1
    else
        make
    fi
    feedback=$?
fi

# Back to the original location
popd > /dev/null

echo "Feedback './Test/script/build.sh' ${feedback}"

exit ${feedback}
