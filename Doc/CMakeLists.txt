option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)
if (DOXYGEN_FOUND)
	# Set input and output folder
	set(DOXYGEN_IN ${CMAKE_CURRENT_LIST_DIR}/Doxyfile.in)
	set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

	# Request to configure the file (DOXYGEN_IN is the input template that will be copied in DOXYGEN_OUT
	# 	and the @variable@ will be replaced by the env variables)
	configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
	message("Doxygen build started")

	# Files to clean
	set_property(
		DIRECTORY ${CMAKE_BINARY_DIR}
		APPEND
		PROPERTY ADDITIONAL_CLEAN_FILES Doxyfile CMakeDoxyfile.in ../Doc/doc_doxygen
	)

	add_custom_target(doc_doxygen ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating code documentation with doxygen"
		VERBATIM
	)
else(DOXYGEN_FOUND)
	message("Doxygen needs to be installed to generate doxygen documentation")
endif(DOXYGEN_FOUND)
