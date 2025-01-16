cmake_minimum_required(VERSION 3.5)
project(FracLib VERSION 1.2)

# C++ requirements
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Variables
set(LIBRARY_NAME "Frac")
set(EXPORT_NAME "FracTargets")

# Optimization level setting for Release only
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g")
endif()

# Define the library
add_library(${LIBRARY_NAME} STATIC src/frac.cpp)

# Include directory to the library
target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Set the output directory for the library inside bin directory
set_target_properties(${LIBRARY_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Define GNU standard installation directories
include(GNUInstallDirs)

# Install the library
install(
    TARGETS ${LIBRARY_NAME}
    EXPORT ${EXPORT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}    # static (.a)
)

# Install header files
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h" # ensure its just headers
)

# Export the targets to a script
install(
    EXPORT ${EXPORT_NAME}
    FILE ${EXPORT_NAME}.cmake
    NAMESPACE FracLib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Generate the ConfigVersion file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/FracLibConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Generate the Config file
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/FracLibConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/FracLibConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Install the Config files
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/FracLibConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/FracLibConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
