#cmake version
cmake_minimum_required(VERSION 3.12...3.15)

if(NOT TARGET ${RamRodGL_LIBRARIES})
  project(RamRodGL
    VERSION 0.8.0
    DESCRIPTION "Ram-Rod's OpenGL helper library"
    LANGUAGES CXX C
  )

  #header files
  set(HPP_FILES
    include/ramrod/gl/buffer.h
    include/ramrod/gl/frame_buffer.h
    include/ramrod/gl/render_buffer.h
    include/ramrod/gl/render_processor.h
    include/ramrod/gl/shader.h
    include/ramrod/gl/texture.h
    include/ramrod/gl/uniform_buffer.h
  )

  #source files
  set(CPP_FILES
    src/ramrod/gl/buffer.cpp
    src/ramrod/gl/frame_buffer.cpp
    src/ramrod/gl/render_buffer.cpp
    src/ramrod/gl/render_processor.cpp
    src/ramrod/gl/shader.cpp
    src/ramrod/gl/texture.cpp
    src/ramrod/gl/uniform_buffer.cpp
  )

  # ++++++++++++++++++++++++++++++++++++++ GLAD ++++++++++++++++++++++++++++++++++++++
  # adding the root directory of the GLAD source tree to your project
  set(GLAD_FILES lib/GLAD/src/glad.c)
  # ++++++++++++++++++++++++++++++++++++ END GLAD ++++++++++++++++++++++++++++++++++++

  set(${PROJECT_NAME}_DIRS_LOCAL
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib/GLAD/include
  )

  set(${PROJECT_NAME}_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}
    ${${PROJECT_NAME}_DIRS_LOCAL}

    CACHE INTERNAL ""
  )

  set(${PROJECT_NAME}_LIBRARIES ${PROJECT_NAME} CACHE INTERNAL "")

  #add every file to the executable
  add_library(${PROJECT_NAME})

  set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD          17
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS        FALSE
  )

  target_sources(${PROJECT_NAME}
    PRIVATE
      ${HPP_FILES}
      ${CPP_FILES}
    PUBLIC
      ${GLAD_FILES}
  )

  target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${${PROJECT_NAME}_DIRS_LOCAL}
  )

  target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_NAME}_RESOURCE_DIR="${PROJECT_BINARY_DIR}"
  )

  target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_17
  )

  target_compile_options(${PROJECT_NAME}
    PRIVATE
      -Wall
      -Wextra
      -Wundef
      -pedantic
      -Wconversion
      -Wcast-align
      -Wfloat-equal
      -Wpointer-arith
      -Wsign-conversion
      -Wunreachable-code
      -Wunused-function
      -Wignored-qualifiers
  )

  set_source_files_properties(${GLAD_FILES}
    PROPERTIES COMPILE_FLAGS
      " -Wno-all -Wno-extra -Wno-undef -Wno-pedantic -Wno-conversion -Wno-cast-align"
      " -Wno-float-equal -Wno-pointer-arith -Wno-sign-conversion -Wno-unreachable-code"
      " -Wno-unused-function -Wno-ignored-qualifiers"
  )

endif(NOT TARGET ${RamRodGL_LIBRARIES})
