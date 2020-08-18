#!/bin/bash

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null
cd ..

./scripts/build.sh
feedback=$?

if [ 0 -eq ${feedback} ] ; then
    echo "::: Run the Tests"
    ./Test/bin/Test_WaterPumpController --gtest_output=xml:./Test/tmp/gtestresults.xml
    feedback=$?
fi


# Back to the original location
popd > /dev/null

exit ${feedback}
