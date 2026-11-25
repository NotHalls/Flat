# Settings Dirs
set(FETCHCONTENT_BASE_DIR
  "${CMAKE_SOURCE_DIR}/.deps"
  CACHE PATH "FetchContent Dependency Storage"
)

include(FetchContent)

# Reuse existing dependencies
if(EXISTS "${FETCHCONTENT_BASE_DIR}/sdl3-src/CMakeLists.txt")
  set(FETCHCONTENT_SOURCE_DIR_SDL3
    "${FETCHCONTENT_BASE_DIR}/sdl3-src")
endif()

if(EXISTS "${FETCHCONTENT_BASE_DIR}/imgui-src/imgui.cpp")
  set(FETCHCONTENT_SOURCE_DIR_IMGUI
    "${FETCHCONTENT_BASE_DIR}/imgui-src")
endif()

if(EXISTS "${FETCHCONTENT_BASE_DIR}/glm-src/CMakeLists.txt")
  set(FETCHCONTENT_SOURCE_DIR_GLM
    "${FETCHCONTENT_BASE_DIR}/glm-src")
endif()

# Fetching
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
  GIT_TAG         release-3.4.20
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY  https://github.com/ocornut/imgui.git
  GIT_TAG         v1.93.0
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
  glm
  GIT_REPOSITORY  https://github.com/g-truc/glm.git
  GIT_TAG         1.0.3
)
FetchContent_MakeAvailable(glm)
