#!/bin/bash

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null
cd ..

./scripts/showSW_Version.sh

feedback=0

if [ 0 -eq ${feedback} ] ; then
    echo "::: Build Test"
    if [ ! -d "./Test/googletest" ] ; then
        echo "Get google test framework"
        ./Test/scripts/getGoogleTest.sh
    fi
    ./Test/scripts/build.sh "$0"
    feedback=$?
fi


# Back to the original location
popd > /dev/null

echo "Feedback './script/build.sh' ${feedback}"
exit ${feedback}
