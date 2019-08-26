#---Automatically Generated from template 'CMakeList.txt' wrote by @aliben---
#
# @Copyright (C) 2019 All rights reserved.
# @filename: Socket
# @author: aliben.develop@gmail.com
# @create_date: 2019-08-26 18:27:43
# @last_modified_date: NO_LAST_MODIFIED_DATE
# @description: TODO
#---****************************************************************---

# Cmake version required
cmake_minimum_required(VERSION 3.10)

#project name
project(Socket)

# Option
  IF( EXISTS ${PROJECT_SOURCE_DIR}/cmake_config/option.cmake )
    INCLUDE(${PROJECT_SOURCE_DIR}/cmake_config/option.cmake)
  ENDIF()

# Compiler flag
  IF( EXISTS ${PROJECT_SOURCE_DIR}/cmake_config/compiler_option.cmake )
    INCLUDE(${PROJECT_SOURCE_DIR}/cmake_config/compiler_option.cmake)
  ENDIF()

  MESSAGE( STATUS "Project:  ${PROJECT_NAME}" )
  MESSAGE( STATUS "Build Type: " ${CMAKE_BUILD_TYPE})
  MESSAGE( STATUS "DEBUG POSTFIX: " ${CMAKE_DEBUG_POSTFIX})

  IF( EXISTS ${PROJECT_SOURCE_DIR}/cmake_config/other_options.cmake )
    INCLUDE(${PROJECT_SOURCE_DIR}/cmake_config/other_options.cmake)
  ENDIF()

  IF( EXISTS ${PROJECT_SOURCE_DIR}/cmake_config/find_package.cmake )
    INCLUDE(${PROJECT_SOURCE_DIR}/cmake_config/find_package.cmake)
  ENDIF()

# Set Subdir(src)
  ADD_SUBDIRECTORY(src)
  ADD_SUBDIRECTORY(examples)
  IF(BUILD_GTESTS)
    ADD_SUBDIRECTORY(testing)
  ENDIF()

# EXECUTABLE
  # Example: ADD_EXECUTABLE( EXEC_NAME SRC_FILE_NAME_LIST )

# TARGET LINK
  # Example: TARGET_LINK_LIBRARIES( EXEC_NAME LIBPATH ) ...LIB_PATH e.g. ${OPENCV_LIBS}
