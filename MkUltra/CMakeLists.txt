cmake_minimum_required(VERSION 3.26)
project(Minigin)

if(EMSCRIPTEN)
  message("Using Emscripten!")
endif()

if(EMSCRIPTEN)
  set(ENGINE_NAME MkUltra_web PARENT_SCOPE)
  set(ENGINE_NAME MkUltra_web)
  set(ENGINE_PARAM )
else()
  set(ENGINE_NAME MkUltra PARENT_SCOPE)
  set(ENGINE_NAME MkUltra)
  set(ENGINE_PARAM WIN32)
endif()

add_library(${ENGINE_NAME} STATIC
  "Source/Core/GameObject.cpp"
  "Source/Core/Transform.cpp"

  "Source/Input/InputManager.cpp"
  "Source/Core/MkUltra.cpp"
  
  "Source/Core/ServiceLocator.cpp"
  "Source/Core/Renderer.cpp"
  "Source/Core/ResourceManager.cpp"
  "Source/Core/Texture2D.cpp"
  "Source/Core/Font.cpp"

  "Source/Core/Scene.cpp"
  "Source/Core/SceneManager.cpp"
  "Source/Core/TimeManager.cpp"
  "Source/Core/PhysicsSystem.cpp"

  "Source/Components/IComponent.cpp"
  "Source/Components/TextComponent.cpp"
  "Source/Components/RenderComponent.cpp"
  
  "Source/Components/BoxColliderComponent.cpp"
  "Source/Components/StateComponent.cpp"

  "Source/Widgets/GUI.cpp"
  "Source/Core/DebugUtils.cpp"
  "GUIWidget.h"

  "Source/Input/ControllerInput.cpp" 
  "Source/Input/Controller.cpp"
  "Source/Input/KeyboardInput.cpp"
  "Source/Input/Action.cpp"
  
  "Source/Core/IObserver.cpp"
  "Source/Core/Geometry.cpp"
  
  "IState.h"
  "GameObjectState.h"
  
  "ISoundSystem.h"
  "NullSoundSystem.h"
  "Source/Sound/DefaultSoundSystem.cpp"
   )

# enable c++20 features
target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_20)

include(FetchContent)
# add glm
FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip
  DOWNLOAD_NO_PROGRESS ON
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
endif()

# add SDL2
if (WIN32)
  FetchContent_Declare(
    SDL2
    URL https://www.libsdl.org/release/SDL2-devel-2.28.5-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads 
  )
  FetchContent_GetProperties(SDL2)
  if(NOT SDL2_POPULATED)
    FetchContent_Populate(SDL2)
    set(SDL2_INCLUDE_DIR ${sdl2_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x64/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x64/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll")
  else()
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x86/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x86/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x86/SDL2.dll")
  endif()
  endif()

  # add SDL2_image
  FetchContent_Declare(
    SDL2_image
    URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.2-VC.zip 
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

  # add SDL2_ttf
  FetchContent_Declare(
    SDL2_ttf
    URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.20.2-VC.zip
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

  set(VLD_DIR "$ENV{ProgramFiles\(x86\)}/Visual Leak Detector")
  IF(EXISTS ${VLD_DIR})
    set(VLD_INCLUDE_DIR "${VLD_DIR}/include")
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(VLD_LIBRARY "${VLD_DIR}/lib/Win64/vld.lib")
    else()
        set(VLD_LIBRARY "${VLD_DIR}/lib/Win32/vld.lib")
    endif()
  endif()

  SET(XINPUT_LIB XInput)

  # set all include directories
  target_include_directories(${ENGINE_NAME} PUBLIC
    ${VLD_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIR} 
    ${SDL2_IMAGE_INCLUDE_DIR} 
    ${SDL2_TTF_INCLUDE_DIR})
  
  # set libraries to link with
  target_link_libraries(${ENGINE_NAME} PUBLIC
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES} 
    ${VLD_LIBRARY}
    ${XINPUT_LIB} 
  )

elseif(NOT EMSCRIPTEN)

  FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.5
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  FetchContent_MakeAvailable(SDL2)
  
  FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2IMAGE_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_image)

  FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.20.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2TTF_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_ttf)

  target_include_directories("${ENGINE_NAME}" PUBLIC 
    ${sdl2_SOURCE_DIR}/include
    ${sdl2_image_SOURCE_DIR}/include
    ${sdl2_ttf_SOURCE_DIR}
  )
  target_link_libraries("${ENGINE_NAME}" PUBLIC 
    SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf
  )
endif()

#imgui

target_link_libraries(${ENGINE_NAME} PUBLIC imguiLib)
target_include_directories(imguiLib PUBLIC
  ${SDL2_INCLUDE_DIR}
)
target_include_directories(${ENGINE_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${glm_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/includes/imgui
)

#soloud
target_link_libraries(${ENGINE_NAME} PUBLIC soloud)

if(EMSCRIPTEN)
    target_compile_definitions(soloud PUBLIC WITH_SDL2_STATIC)
else()
    target_compile_definitions(soloud PUBLIC WITH_MINIAUDIO)
    target_link_libraries(soloud PUBLIC ${sdl2_SOURCE_DIR})
endif()


# compile at max warning level + treat warnings as errors
target_compile_options(${ENGINE_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

 if(EMSCRIPTEN)
        set(EMSCRIPTEN_COMPILE_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -g")
        set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_TTF=2 -g -sALLOW_MEMORY_GROWTH --preload-file \"${CMAKE_SOURCE_DIR}/Data@/\" -sSDL2_IMAGE_FORMATS=['tga','png']")

        # work around https://github.com/emscripten-core/emscripten/issues/11513
        set(EMSCRIPTEN_LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS} -fno-stack-protector")

        # Use the Emscripten toolchain
        set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/EmscriptenToolchain.cmake)

        # Additional settings for Emscripten build
        set_target_properties(${ENGINE_NAME} PROPERTIES
            COMPILE_FLAGS "${EMSCRIPTEN_COMPILE_FLAGS}"
            LINK_FLAGS "${EMSCRIPTEN_LINK_FLAGS}"
        )

        # Have emscripten generate a html page too.
        set(CMAKE_EXECUTABLE_SUFFIX ".html")
elseif(WIN32)
        # add post build commands
        add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_LIBRARY_DLL}" "${CMAKE_BINARY_DIR}/${PROJECT_FOLDER}"
        )
        add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_IMAGE_LIBRARY_DLL}" "${CMAKE_BINARY_DIR}/${PROJECT_FOLDER}"
        )
        add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_TTF_LIBRARY_DLL}" "${CMAKE_BINARY_DIR}/${PROJECT_FOLDER}"
        )

        add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
          COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/Data" "${CMAKE_BINARY_DIR}/${PROJECT_FOLDER}/Data"
        )
endif()