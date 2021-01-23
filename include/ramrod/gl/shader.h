#ifndef RAMROD_GL_SHADER_H
#define RAMROD_GL_SHADER_H

#include "glad/glad.h"

#ifdef USING_ALGEBRAICA
#include "algebraica/algebraica.h"
#endif

#include <string>

namespace ramrod {
  namespace gl {
    class shader
    {
    public:
      /*
     * Object constructor, the shader will not yet be created
     */
      shader();
      /*
     * Construct this object and creates this shader program
     */
      shader(const std::string &vertex_path,
             const std::string &fragment_path,
             const std::string &geometry_path = "");
      /*
     * Deleting the shader program to free memory (CPU and OpenGL)
     */
      ~shader();
      /*
     * Getting the attribute location
     *
     * @returns GLint : attribute location
     */
      GLint attribute_location(const std::string &name) const;
      /*
     * Creates the shader program
     *
     * @returns bool : false if shader program was not properly created or previously created
     */
      bool create(const std::string &vertex_path,
                  const std::string &fragment_path,
                  const std::string &geometry_path = "");
      /*
     * Deleting the shader program
     *
     * @returns bool : false if shader program was not created
     */
      bool delete_shader();
      /*
     * Returning if the program had an error
     *
     * @returns bool : false if shader program was not properly created
     */
      bool error() const;
      /*
     * Returns the error description if error() is true
     *
     * @returns const std::string& : Detailed description of the failure
     */
      const std::string &error_log() const;
      /*
     * Returns the shader program ID
     *
     * @returns const GLint& : Shader program id
     */
      GLuint id() const;
      /*
     * Creates the shader program if is not yet created
     *
     * @returns bool : false if shader program was not properly created or previously created
     */
      bool operator()(const std::string &vertex_path,
                      const std::string &fragment_path,
                      const std::string &geometry_path = "");
      /**
       * @brief Releasing all the shaders
       */
      void release() const;
      /**
       * @brief Getting the binding index of the uniform block
       *
       * @param uniform_name Specifies the address an array of characters to containing the
       *                     name of the uniform block whose index to retrieve.
       *
       * @return The index of the uniform buffer binding point last selected by the uniform
       *         block specified by `uniform_index` for program is returned. If no uniform
       *         block has been previously specified, zero is returned or -1 if there was
       *         and error.
       */
      GLint uniform_block_binding(const std::string &uniform_name) const;
      /**
       * @brief Getting the binding index of the uniform block
       *
       * @param uniform_index Specifies the index of the uniform block within program.
       *
       * @return The index of the uniform buffer binding point last selected by the uniform
       *         block specified by `uniform_index` for program is returned. If no uniform
       *         block has been previously specified, zero is returned or -1 if there was
       *         and error.
       */
      GLint uniform_block_binding(const GLuint uniform_index) const;
      /**
       * @brief Retrieve the index of a named uniform block
       *
       * @param uniform_name Specifies the address an array of characters to containing the
       *                     nameof the uniform block whose index to retrieve.
       *
       * @return Uniform block's index or `GL_INVALID_INDEX` if does not exist
       */
      GLuint uniform_block_index(const std::string &uniform_name) const;
      /**
       * @brief Getting the size of the uniform block's data in bytes
       *
       * @param uniform_name Specifies the address an array of characters to containing
       *                     the name of the uniform block whose index to retrieve.
       *
       * @return Size in bytes of the uniform block's data or -1 if error happened
       */
      GLint uniform_block_data_size(const std::string &uniform_name) const;
      /**
       * @brief Getting the size of the uniform block's data in bytes
       *
       * @param uniform_index Specifies the index of the uniform block within program.
       *
       * @return Size in bytes of the uniform block's data or -1 if error happened
       */
      GLint uniform_block_data_size(const GLuint uniform_index) const;
      /*
     * Getting the uniform location
     *
     * @returns GLint : uniform location
     */
      GLint uniform_location(const std::string &name) const;
      /*
     * Activates/bind the shader program
     *
     * @returns bool : false if shader program was not created
     */
      void use() const;

      // :::::::::::::::::::::::::::::::: Utility uniform functions :::::::::::::::::::::::::::::::

      // bool -----------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const bool value) const;
      // integer --------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const int value) const;
      // GLuint ---------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const GLuint value) const;
      // float ----------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const float value) const;
      void set_value(const GLint uniform_location, const float *value, const int size = 4) const;
      // vector 2D ------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const float x, const float y) const;
      // vector 3D ------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const float x, const float y, const float z) const;
      // vector 4D ------------------------------------------------------------------------
      void set_value(const GLint uniform_location,
                     const float x, const float y, const float z, const float w) const;

      // :::::::::::::::::::::: Utility uniform functions using uniform names :::::::::::::::::::::

      // bool -----------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const bool value) const;
      // integer --------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const int value) const;
      // GLuint ---------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const GLuint value) const;
      // float ----------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const float value) const;
      void set_value(const std::string &uniform_name, const float *value, const int size = 4) const;
      // vector 2D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const float x, const float y) const;
      // vector 3D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const float x, const float y, const float z) const;
      // vector 4D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name,
                     const float x, const float y, const float z, const float w) const;

      // ::::::::::::::::::::: Utility uniform functions using algebraica lib :::::::::::::::::::::
#ifdef USING_ALGEBRAICA
      // vector 2D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::vec2f &vector) const;
      // vector 3D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::vec3f &vector) const;
      void set_values(const std::string &uniform_name,
                      const algebraica::vec3f *pointer_to_vector_array,
                      const GLsizei vector_array_size) const;
      // vector 4D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::vec4f &vector) const;
      // Quaternion ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::quaternionF &quaternion) const;
      // matrix 3D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::mat3f &matrix) const;
      // matrix 4D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::mat4f &matrix) const;
#endif

    private:
      GLuint id_;
      bool error_;
      std::string error_log_;
    };
  }
}
#endif // RAMROD_GL_SHADER_H
