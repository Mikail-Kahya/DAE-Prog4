cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# list source files here
add_executable(${PROJECT_NAME}
  "Main.cpp"

  "Source/Input/PlayerCommand.cpp"

  "Source/Widgets/PlotWidget.cpp"
  "Source/Widgets/MeasureWidget.cpp"

  "Source/Components/HealthComponent.cpp"

  "Source/Components/FPSComponent.cpp"
  "Source/Components/MovementComponent.cpp"
  "Source/Components/OrbitComponent.cpp"
  
  "Source/Components/ScoreComponent.cpp"
  "Source/Components/FireComponent.cpp"
  "Source/Components/RespawnComponent.cpp"
  "Source/Components/ExplosionComponent.cpp"
  "Source/Components/HealthBarComponent.cpp"
)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)


target_link_libraries(${PROJECT_NAME} PUBLIC ${ENGINE_NAME})
target_include_directories(${ENGINE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#ASK ALEX HOW TO SPLIT UP EMSCRIPTEN

if(WIN32)
     # add post build commands

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/Data" "${CMAKE_BINARY_DIR}/Data"
  )
endif()