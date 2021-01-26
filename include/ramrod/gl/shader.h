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
      GLint attribute_location(const std::string &name);
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
      bool error();
      /*
     * Returns the error description if error() is true
     *
     * @returns const std::string& : Detailed description of the failure
     */
      const std::string &error_log();
      /*
     * Returns the shader program ID
     *
     * @returns const GLint& : Shader program id
     */
      GLuint id();
      /*
     * Creates the shader program if is not yet created
     *
     * @returns bool : false if shader program was not properly created or previously created
     */
      bool operator()(const std::string &vertex_path,
                      const std::string &fragment_path,
                      const std::string &geometry_path = "");
      /*
     * Getting the uniform location
     *
     * @returns GLint : uniform location
     */
      GLint uniform_location(const std::string &name);
      /*
     * Activates/bind the shader program
     *
     * @returns bool : false if shader program was not created
     */
      void use();

      // :::::::::::::::::::::::::::::::: Utility uniform functions :::::::::::::::::::::::::::::::

      // bool -----------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const bool value);
      // integer --------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const int value);
      // GLuint ---------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const GLuint value);
      // float ----------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const float value);
      // vector 2D ------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const float x, const float y);
      // vector 3D ------------------------------------------------------------------------
      void set_value(const GLint uniform_location, const float x, const float y, const float z);
      // vector 4D ------------------------------------------------------------------------
      void set_value(const GLint uniform_location,
                     const float x, const float y, const float z, const float w);

      // :::::::::::::::::::::: Utility uniform functions using uniform names :::::::::::::::::::::

      // bool -----------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const bool value);
      // integer --------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const int value);
      // GLuint ---------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const GLuint value);
      // float ----------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const float value);
      // vector 2D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const float x, const float y);
      // vector 3D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const float x, const float y, const float z);
      // vector 4D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name,
                     const float x, const float y, const float z, const float w);

      // ::::::::::::::::::::: Utility uniform functions using algebraica lib :::::::::::::::::::::
#ifdef USING_ALGEBRAICA
      // vector 2D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::vec2f &vector);
      // vector 3D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::vec3f &vector);
      void set_values(const std::string &uniform_name,
                      const algebraica::vec3f *pointer_to_vector_array,
                      const GLsizei vector_array_size);
      // vector 4D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::vec4f &vector);
      // Quaternion ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::quaternionF &quaternion);
      // matrix 3D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::mat3f &matrix);
      // matrix 4D ------------------------------------------------------------------------
      void set_value(const std::string &uniform_name, const algebraica::mat4f &matrix);
#endif

    private:
      GLuint id_;
      bool error_;
      std::string error_log_;
    };
  }
}
#endif // RAMROD_GL_SHADER_H
