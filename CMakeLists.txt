cmake_minimum_required(VERSION 4.5)

project(
  Flat
  VERSION 0.0.1
)


############
# Settings #
############
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#############
# Variables #
#############
set(PROJECT_PREFIX F)
set(PROJECT_LOG_NAME Flat)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR})

set(FLAT_BINARY_DIR ${PROJECT_SOURCE_DIR}/Binary )
set(FLAT_OUTPUT_FOLDER_SIGNATURE
  ${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}-${CMAKE_CXX_COMPILER_ID}
)


##############################
# Setting Build/Config Types #
##############################
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build Type")
  message(STATUS
    "[${PROJECT_LOG_NAME}]
    No Build Type Was Selected. Defaulting To ${CMAKE_BUILD_TYPE}"
  )
endif()


##################################################################
# Setting Up A Folder Structure                                  #
# For All The Available Variations Of Compilers, And Build Types #
##################################################################
if(CMAKE_CONFIGURATION_TYPES)
  foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG_UPPER)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER}
      "${FLAT_BINARY_DIR}/Bin/${FLAT_OUTPUT_FOLDER_SIGNATURE}"
    )
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG_UPPER}
      "${FLAT_BINARY_DIR}/Libs/${FLAT_OUTPUT_FOLDER_SIGNATURE}"
    )
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_UPPER}
      "${FLAT_BINARY_DIR}/Libs/${FLAT_OUTPUT_FOLDER_SIGNATURE}"
    )
  endforeach()
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${FLAT_BINARY_DIR}/Bin/${FLAT_OUTPUT_FOLDER_SIGNATURE}"
  )
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    "${FLAT_BINARY_DIR}/Libs/${FLAT_OUTPUT_FOLDER_SIGNATURE}"
  )
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    "${FLAT_BINARY_DIR}/Libs/${FLAT_OUTPUT_FOLDER_SIGNATURE}"
  )
endif()


#########################
# Adding The Executable #
#########################
include(./Files.cmake)
add_executable(${PROJECT_NAME} ${FLAT_SOURCES})


########################
# ADDING INCLUDE PATHS #
########################
target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/Source
)


################################
# FINDING AND ADDING LIBRARIES #
################################
include(Dependencies.cmake)

# Finding Libraries (System)
find_package(Vulkan REQUIRED COMPONENTS volk shaderc_combined)

# Adding ImGui
add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)

target_include_directories(imgui PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
)

# Adding Libraries (Imported)
target_link_libraries(${PROJECT_NAME} PRIVATE
  SDL3::SDL3
  glm::glm
  imgui
)
# Adding Libraries (System)
target_link_libraries(${PROJECT_NAME} PRIVATE
  # Vulkan Related Packages
  Vulkan::Vulkan
  Vulkan::volk
  Vulkan::shaderc_combined
)


##############
# ADDING PCH #
##############
set(PCH_HEADER "${PROJECT_SOURCE_DIR}/Source/FlatPCH.h")
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH_HEADER})


#######################################################
# SETTING COMPILE DEFINITIONS FOR BUILD/CONFIG TYPES #
#######################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:${PROJECT_PREFIX}_DEBUG>
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Release>:${PROJECT_PREFIX}_RELEASE>
)

if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE
    ${PROJECT_PREFIX}_PLATFORM_WINDOWS
  )
elseif(APPLE)
  target_compile_definitions(${PROJECT_NAME} PRIVATE
    ${PROJECT_PREFIX}_PLATFORM_MACOS
  )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(${PROJECT_NAME} PRIVATE
    ${PROJECT_PREFIX}_PLATFORM_LINUX
  )
endif()

# Some Other Definitions and Settings
target_compile_definitions(${PROJECT_NAME} PUBLIC
  GLM_ENABLE_EXPERIMENTAL
)

# Managing Visual Studio Bullshit
# This is so that visual studio can generate project/file structure correctly
# I... think...
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
  )
endif()
