# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/sauterelle/Documents/Concordia/COMP438/DiceSimulator/build/_deps/libigl_imgui_fonts-src"
  "/home/sauterelle/Documents/Concordia/COMP438/DiceSimulator/build/_deps/libigl_imgui_fonts-build"
  "/home/sauterelle/Documents/Concordia/COMP438/DiceSimulator/build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix"
  "/home/sauterelle/Documents/Concordia/COMP438/DiceSimulator/build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/tmp"
  "/home/sauterelle/Documents/Concordia/COMP438/DiceSimulator/build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp"
  "/home/sauterelle/Documents/Concordia/COMP438/DiceSimulator/build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src"
  "/home/sauterelle/Documents/Concordia/COMP438/DiceSimulator/build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/sauterelle/Documents/Concordia/COMP438/DiceSimulator/build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/sauterelle/Documents/Concordia/COMP438/DiceSimulator/build/_deps/libigl_imgui_fonts-subbuild/libigl_imgui_fonts-populate-prefix/src/libigl_imgui_fonts-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
