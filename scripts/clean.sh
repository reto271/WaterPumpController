#!/bin/bash

CLEAN_ALL=0
CLEAN_ALL_TEXT=""
if [ 1 -eq $# ] ; then
    if [ "--all" == "$1" ] ; then
        CLEAN_ALL=1
        CLEAN_ALL_TEXT="--all"
    fi
fi

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null
cd ..

./scripts/showSW_Version.sh

feedback=0

echo "Clean Tests"
if [ 0 -eq ${feedback} ] ; then
    ./Test/scripts/clean.sh "${CLEAN_ALL_TEXT}"
    feedback=$?
fi

cd ..
if [ 1 -eq ${CLEAN_ALL} ] ; then
    rm -rf GPATH GTAGS GRTAGS
fi

# Back to the original location
popd > /dev/null

exit ${feedback}
