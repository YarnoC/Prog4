cmake_minimum_required(VERSION 3.16)

project(project)

if (WIN32)
  set(CMAKE_OBJECT_PATH_MAX 260)
endif ()


set(SRC_FILES
  Minigin/Component.cpp
  Minigin/Font.cpp
  Minigin/GameObject.cpp
  Minigin/GameTime.cpp
  Minigin/InputManager.cpp
  Minigin/Main.cpp
  Minigin/Minigin.cpp
  Minigin/Renderer.cpp
  Minigin/ResourceManager.cpp
  Minigin/Scene.cpp
  Minigin/SceneManager.cpp
  Minigin/TextComponent.cpp
  Minigin/TextObject.cpp
  Minigin/Texture2D.cpp
  Minigin/Transform.cpp
  Minigin/Gamepad.cpp
  Minigin/TextureComponent.cpp
  Minigin/FpsComponent.cpp
  Minigin/Command.cpp
  Minigin/Component.h
  Minigin/Font.h
  Minigin/GameObject.h
  Minigin/GameTime.h
  Minigin/InputManager.h
  Minigin/Minigin.h
  Minigin/Renderer.h
  Minigin/ResourceManager.h
  Minigin/Scene.h
  Minigin/SceneManager.h
  Minigin/Singleton.h
  Minigin/TextComponent.h
  Minigin/TextObject.h
  Minigin/Texture2D.h
  Minigin/Transform.h
  Minigin/Gamepad.h
  Minigin/TextureComponent.h
  Minigin/FpsComponent.h
  Minigin/Command.h
)

include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.1 # NOTE: latest as of writing, feel free to change
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
    SDL2_ttf
    URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.22.0-VC.zip
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_GetProperties(SDL2_ttf)
  if(NOT sdl2_ttf_POPULATED)
    FetchContent_Populate(SDL2_ttf)
    set(SDL2_TTF_INCLUDE_DIR ${sdl2_ttf_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.dll")
  else()
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.dll")
  endif()
  endif()

  FetchContent_Declare(
      SDL2_image
      URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.8-VC.zip
      DOWNLOAD_NO_PROGRESS ON
      DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
    )
    FetchContent_GetProperties(SDL2_image)
    if(NOT SDL2_image_POPULATED)
      FetchContent_Populate(SDL2_image)
      set(SDL2_IMAGE_INCLUDE_DIR ${sdl2_image_SOURCE_DIR}/include)
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
      set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.lib")
      set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.dll")
    else()
      set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.lib")
      set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.dll")
    endif()
    endif()

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)


add_executable(Minigin WIN32 ${SRC_FILES})
target_link_libraries(Minigin PRIVATE glm::glm SDL2::SDL2main SDL2::SDL2 ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

target_include_directories(Minigin PRIVATE ${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

set_property(TARGET Minigin PROPERTY
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS FALSE)
