#  For more information, please see: http://software.sci.utah.edu
# 
#  The MIT License
# 
#  Copyright (c) 2015 Scientific Computing and Imaging Institute,
#  University of Utah.
# 
#  
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software. 
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.

SET_PROPERTY(DIRECTORY PROPERTY "EP_BASE" ${ep_base})

IF(UNIX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
  IF(APPLE)
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -ftemplate-depth=256")
    SET(CMAKE_CXX_FLAGS_DEBUG "-Wshorten-64-to-32 ${CMAKE_CXX_FLAGS_DEBUG}")
  ELSE()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
  ENDIF()
ENDIF()

SET(vtk_ARGS
  "-DBUILD_EXAMPLES:BOOL=OFF"
  "-DBUILD_TESTING:BOOL=OFF"
  # from http://www.vtk.org/Wiki/VTK/Tutorials/QtSetup:
  "-DBUILD_SHARED_LIBS:BOOL=ON"
  "-DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}"
  "-DVTK_Group_Qt:BOOL=OFF"
  "-DModule_vtkGUISupportQt:BOOL=ON"
  "-DModule_vtkGUISupportQtOpenGL:BOOL=ON"
  "-DVTK_USE_SYSTEM_FREETYPE:BOOL=ON"
  "-DFREETYPE_INCLUDE_DIR_freetype2:PATH=${Freetype_DIR}/include/freetype2"
  "-DFREETYPE_INCLUDE_DIR_ft2build:PATH=${Freetype_SOURCE_DIR}/include"
  "-DFREETYPE_LIBRARY:FILEPATH=${Freetype_LIB_PATH}"
)

SET(vtk_GIT_URL "https://gitlab.kitware.com/vtk/vtk.git")
SET(vtk_GIT_TAG "v6.2.0")

# If CMake ever allows overriding the checkout command or adding flags,
# git checkout -q will silence message about detached head (harmless).
ExternalProject_Add(VTK_external
  GIT_REPOSITORY ${vtk_GIT_URL}
  GIT_TAG ${vtk_GIT_TAG}
  PATCH_COMMAND ""
  INSTALL_DIR ""
  INSTALL_COMMAND ""
  CMAKE_ARGS ${vtk_ARGS}
)

ExternalProject_Get_Property(VTK_external BINARY_DIR)
SET(VTK_DIR ${BINARY_DIR} CACHE PATH "")

MESSAGE(STATUS "VTK_DIR=${VTK_DIR}")
