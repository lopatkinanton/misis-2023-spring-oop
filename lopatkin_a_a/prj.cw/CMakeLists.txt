find_package(OpenCV REQUIRED)
add_executable(main main.cpp)
target_link_libraries(main
	PRIVATE opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui
)