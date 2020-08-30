#!/bin/bash

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null

Version=$(cat ../Application/Application.cpp | \
              grep "V[0-9]\{2\}\.[0-9]\{2\}" | \
              grep -v "^[ ]\{0,\}//" | \
              awk -F'"' '{ print $2 }' )


#echo ""
echo "SW Version: ${Version}"
#echo "---"

#export DATA_LOGGER_LUXTRONIK_SW_VERSION="${MajorMinorVersion} ${BetaVersion}"

# Back to the original location
popd > /dev/null
