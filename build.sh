#!/bin/bash

#---Automatically Generated from template 'bash' wrote by @aliben---
# @Copyright (C) 2019 All rights reserved.
# @file: build.sh
# @author: aliben.develop@gmail.com
# @created_date: 2019-08-26 18:27:45
# @last_modified_date: NO_LAST_MODIFIED_DATE
# @brief: TODO
# @details: TODO
#---***********************************************---


#---Variables
CREATED_TIME=`date '+%Y-%m-%d %H:%M:%S'`
CREATED_YEAR=`date '+%Y'`
CLEAN=$1
#---Shell Command
if [[ ! -d "build" ]]; then
  mkdir -p build
fi
if [[ "${CLEAN}" == "clean" ]]; then
  rm -rf bin/*
  rm -rf build/*
  rm -rf lib/*
fi

if [[ "${CLEAN}" == "debug" ]]; then
  BUILD_TYPE=DEBUG
else
  BUILD_TYPE=RELEASE
fi

if [ ! -L ./bin/log ]; then
  ln -s `pwd`/log ./bin/log
fi

set -x
cd build
cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
make -j7
set +x

if [[ "${CLEAN}" == "debug" ]]; then
  cd ..
  ./run_test.sh

  COVERAGE_FILE=coverage.info
  REPORT_FOLDER=coverage_report
  lcov --rc lcov_branch_coverage=1 -c -d build -o ${COVERAGE_FILE}_tmp
  lcov --rc lcov_branch_coverage=1  -e ${COVERAGE_FILE}_tmp "*src*" -o ${COVERAGE_FILE}
  genhtml --rc genhtml_branch_coverage=1 ${COVERAGE_FILE} -o ${REPORT_FOLDER}
  rm -rf ${COVERAGE_FILE}_tmp
  rm -rf ${COVERAGE_FILE}

  if [[ "$OSTYPE" == "darwin"* ]]; then
    open ./${REPORT_FOLDER}/index.html
  fi
fi
