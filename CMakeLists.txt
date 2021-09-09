#cmake version
cmake_minimum_required(VERSION 3.5...3.15)

if(NOT TARGET ${RamRodGL_LIBRARIES})
  project(RamRodGL
    VERSION 0.8.0
    DESCRIPTION "Ram-Rod's OpenGL helper library"
    LANGUAGES CXX C
  )

  # finding dependencies
  find_package(OpenGL REQUIRED)

  # ++++++++++++++++++++++++++++++++++++++ GLAD ++++++++++++++++++++++++++++++++++++++
  # adding the root directory of the GLAD source tree to your project
  set(GLAD_FILES lib/GLAD/src/glad.c)
  # ++++++++++++++++++++++++++++++++++++ END GLAD ++++++++++++++++++++++++++++++++++++

  set(${PROJECT_NAME}_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib/GLAD/include
    CACHE INTERNAL ""
  )

  set(${PROJECT_NAME}_LIBRARIES
    ${PROJECT_NAME}
    CACHE INTERNAL ""
  )

  #add every file to the executable
  add_library(${PROJECT_NAME})

  set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD          17
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS        FALSE
  )

  target_sources(${PROJECT_NAME}
    PRIVATE
      src/ramrod/gl/buffer.cpp
      src/ramrod/gl/error.cpp
      src/ramrod/gl/frame_buffer.cpp
      src/ramrod/gl/pixel_buffer.cpp
      src/ramrod/gl/render_buffer.cpp
      src/ramrod/gl/shader.cpp
      src/ramrod/gl/texture.cpp
      src/ramrod/gl/uniform_buffer.cpp
    PUBLIC
      ${GLAD_FILES}
  )

  target_include_directories(${PROJECT_NAME}
    BEFORE PRIVATE
    include
    lib/GLAD/include
  )

  #indicates which libraries to use in the executable
  target_link_libraries(${PROJECT_NAME}
    # OpenGL libraries
    ${OPENGL_LIBRARIES}
  )

  target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

endif(NOT TARGET ${RamRodGL_LIBRARIES})
