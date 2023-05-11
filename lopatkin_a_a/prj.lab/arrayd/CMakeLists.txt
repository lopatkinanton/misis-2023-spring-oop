add_library(arrayd arrayd.cpp include/arrayd/arrayd.hpp)
set_property(TARGET rational PROPERTY CXX_STANDARD 20)
target_include_directories(arrayd PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS arrayd)