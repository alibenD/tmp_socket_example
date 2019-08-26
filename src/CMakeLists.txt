#---Automatically Generated from template 'CMakeList.txt' wrote by @aliben---
#
# @Copyright (C) 2019 All rights reserved.
# @filename: Socket
# @author: aliben.develop@gmail.com
# @create_date: 2019-08-26 18:27:43
# @last_modified_date: NO_LAST_MODIFIED_DATE
# @description: TODO
#---****************************************************************---

FILE(GLOB_RECURSE HEADERS
  ../include/Socket/*/*.h*
  ../include/Socket/*.h*
  ../include/*.h*
  )
FILE(GLOB_RECURSE SOURCES *.cc *.cpp *.c *.cxx)

ADD_LIBRARY(Socket SHARED ${HEADERS} ${SOURCES})
TARGET_LINK_LIBRARIES(Socket ${THIRD_PARTY_LIBS})
