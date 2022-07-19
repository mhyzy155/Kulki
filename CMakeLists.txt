cmake_minimum_required(VERSION 3.21.1)
set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


project(Kulki LANGUAGES CXX)

add_library(project_warnings INTERFACE)
target_compile_options(project_warnings
                      INTERFACE -Wall
                                -Werror # treat all warnings as errors
                                -Wextra # reasonable and standard
                                -Wshadow # warn the user if a variable
                                        # declaration shadows one from a
                                        # parent context
                                -Wnon-virtual-dtor # warn the user if a class
                                                  # with virtual functions
                                                  # has a non-virtual
                                                  # destructor. This helps
                                                  # catch hard to track down
                                                  # memory errors
                                -Wold-style-cast # warn for c-style casts
                                -Wcast-align # warn for potential performance
                                            # problem casts
                                -Wunused # warn on anything being unused
                                -Woverloaded-virtual # warn if you overload
                                                    # (not override) a
                                                    # virtual function
                                -Wpedantic # warn if non-standard C++ is used
                                -Wconversion # warn on type conversions that
                                            # may lose data
                                -Wsign-conversion # warn on sign conversions
                                -Wnull-dereference # warn if a null
                                                  # dereference is detected
                                -Wdouble-promotion # warn if float is
                                                  # implicit promoted to
                                                  # double
                                -Wformat=2 # warn on security issues around
                                          # functions that format output (ie
                                          # printf)
                         )

add_subdirectory(src)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
set(SDL_LIBS SDL2::Main SDL2::Image SDL2::TTF)

enable_testing()
add_subdirectory(tests)

add_executable(Kulki main.cpp)
target_compile_features(Kulki PRIVATE cxx_std_20)
target_link_libraries(Kulki project_warnings src ${SDL_LIBS})


