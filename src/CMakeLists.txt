cmake_minimum_required(VERSION 3.24)

# ===== VARIABLES =====
set(Target
	"main.cpp"
	"Model/Node.cpp"
	"Model/Tree.cpp"
	"Model/Trunk.cpp"
	#"lca/lca.cpp"
	#"fitch/fitch.cpp"
	#"reconciliation/reconciliation.cpp"
)

# ===== VARIABLES =====
set(CMAKE_CXX_STANDARD 11)

# ===== Project definition
project(phylo
	VERSION 0.1
	LANGUAGES CXX)

# ===== Files to clean ======
set_property(
	DIRECTORY ${CMAKE_BINARY_DIR}
	APPEND
	PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_BINARY_DIR}
)

# ===== Project files =====
add_executable(${PROJECT_NAME} ${Target})
