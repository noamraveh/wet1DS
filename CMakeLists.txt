cmake_minimum_required(VERSION 3.15)
project(wet1DS)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -Wall -pedantic-errors -g -Werror -DNDEBUG")
set(CMAKE_CXX_STANDARD 11)
add_executable(wet1DS  newtestsAVL.cpp Diesel.h LinkedList.h Library1.h MainArtistData.h SongData.h ArtistData.h StreamData.h)
