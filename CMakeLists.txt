cmake_minimum_required(VERSION 3.15)
project(wet1DS)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -Wall -pedantic-errors -g -Werror -DNDEBUG")
set(CMAKE_CXX_STANDARD 11)
add_executable(wet1DS  main.cpp StreamData.h SongData.h MainArtistData.h ArtistData.h LinkedList.h FinalAVLTree.h Diesel.h)
