cmake_minimum_required(VERSION 3.22)

if(UNIX AND NOT APPLE)
  set(CMAKE_CXX_COMPILER "g++-11")
endif()

project(ttransform LANGUAGES CXX)

# ========== Project Setup ==========
set(CMAKE_CXX_STANDARD 20)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Assume development build by default
set(RELEASE_TAG "development" CACHE STRING "Release tag for the build")

# Default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

# ========== Dependencies Setup ==========

# ========== Source Files ==========
file(GLOB_RECURSE TTRANSFORM_SOURCES "src/*.cpp")
add_executable(ttransform ${TTRANSFORM_SOURCES})

target_compile_definitions(ttransform PRIVATE RELEASE_TAG="${RELEASE_TAG}")

# ========== Include Directories ==========
target_include_directories(ttransform
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# ========== Compile Options ==========
target_compile_options(ttransform PRIVATE -ffp-contract=off)

# Compiler warnings
target_compile_options(ttransform PRIVATE
  -Wall  # Enable all warnings
  -Wextra  # Enable extra warnings
  -Wpedantic  # Enable pedantic warnings
)

# ========== Installation ==========
install(TARGETS ttransform  DESTINATION /usr/local/bin)

# Uninstall target
add_custom_target("uninstall")
add_custom_command(
  TARGET "uninstall"
  POST_BUILD
  COMMENT "Uninstalling ttransform..."
  COMMAND xargs rm -vf < install_manifest.txt || echo "Nothing in install_manifest.txt to be uninstalled!"
)