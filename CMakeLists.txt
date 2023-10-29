cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 11)


# ===== VARIABLES =====
set(CMAKE_CXX_STANDARD 11)


# ===== Project Definition =====
project(Tree-C
	VERSION 0.1
	LANGUAGES CXX)


# ===== Project files =====

# ===== Additional CmakeLists.txt =====
add_subdirectory(src)
add_subdirectory(Tests)
#add_subdirectory(Tests)
