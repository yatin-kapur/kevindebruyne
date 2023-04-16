#!/bin/bash

wget https://boostorg.jfrog.io/artifactory/main/release/1.82.0/source/boost_1_82_0.tar.gz

tar -xzf boost_1_82_0.tar.gz
cd boost_1_82_0
./bootstrap.sh --prefix=../lib/boost_stage
./b2 install

# get rid of zipped and downloaded files
cd ..
rm -rf boost_1_82_0.tar.gz
rm -rf boost_1_82_0

# extract boost library out with headers
mv lib/boost_stage/include/boost lib/boost
rm -rf lib/boost_stage

cd lib/boost
# create build file for boost lib
echo "load('@rules_cc//cc:defs.bzl', 'cc_library')

cc_library(
    name = 'boost',
    hdrs = glob(['**']),
    visibility = ['//visibility:public'],
    includes = ['./'],
)" > BUILD