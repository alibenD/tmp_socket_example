#---Automatically Generated from template 'option.cmake' wrote by @aliben---
#
# @Copyright (C) 2019 All rights reserved.
# @filename: option.cmake
# @author: aliben.develop@gmail.com
# @create_date: 2019-08-26 18:27:44
# @last_modified_date: NO_LAST_MODIFIED_DATE
# @description: TODO
#---****************************************************************---

#project name

# Option
  OPTION(ENABLE_ALL_WARNING ON)
  OPTION(ENABLE_WARNING_AS_ERROR OFF)
  OPTION(ENABLE_WARNING_EXTRA ON)
  OPTION(ENABLE_VERBOSE ON)
  OPTION(ENABLE_PROFILER OFF)

  OPTION(BUILD_GTESTS "Build test example cases with google test" ON)
  OPTION(WITH_GLOG "Enable google log in this case" OFF)

  OPTION(BUILD_SHARED_LIBS "Build shared libraries" ON)

# CMake Build System Default Setup
  SET(CMAKE_BUILD_TYPE "Release" CACHE STRING "Default Build Type")
  SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Release Debug RelWithDebInfo MinSizeRel)

