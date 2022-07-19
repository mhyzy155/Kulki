file(GLOB SOURCES *.cpp)
add_library(src STATIC ${SOURCES})
target_include_directories(src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)