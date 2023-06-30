project(main)

find_package(OpenCV REQUIRED)

find_package(Doxygen)
if (DOXYGEN_FOUND)
	add_custom_target(docs ${DOXYGEN_EXECUTABLE} docs.doxyfile
	COMMENT "Generating API documentation with Doxygen"
	VERBATIM
	SOURCES ${PRJ_DOXY}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

include_directories(metrics/include)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(metrics)

target_link_libraries(${PROJECT_NAME}
	PRIVATE opencv_core opencv_imgcodecs
	PUBLIC metrics
)

install(TARGETS ${PROJECT_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}")

install(DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/"
	DESTINATION "${CMAKE_INSTALL_PREFIX}"
	FILES_MATCHING 
	PATTERN "*.dll"
)

install(DIRECTORY "data"
	DESTINATION "${CMAKE_INSTALL_PREFIX}"
)