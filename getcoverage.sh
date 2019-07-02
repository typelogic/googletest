#!/bin/sh
#

if [ -r testapp ];then
    ./testapp
else
    echo "-- NOTHING TO DO --"
    exit 1
fi

if [ -r testapp.gcno ];then
    gcov testapp.gcno
    lcov --capture --directory . --output-file gcov_result.info
    mkdir -p CODE_COVERAGE
    genhtml gcov_result.info --output-directory CODE_COVERAGE
else
    echo "*** NOTHING TO DO ***"
fi
