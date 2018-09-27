#!/bin/bash

rm -f bla.db
g++ test.cpp Protocol.cpp BabelStruct.cpp ../../Db/Db.cpp ../../Db/DbData.cpp -I../../Db/ -g