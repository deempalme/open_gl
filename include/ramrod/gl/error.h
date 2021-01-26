#ifndef RAMROD_GL_ERROR_H
#define RAMROD_GL_ERROR_H

// OpenGL loader and core library
#include "glad/glad.h"
#include <string>

namespace ramrod {
  namespace gl {
    class error
    {
    public:
      error() = default;
      /**
       * @brief return error code
       *
       * Each detectable error is assigned a numeric code and symbolic name. When an error
       * occurs, the error flag is set to the appropriate error code value. No other errors
       * are recorded until code() is called, the error code is returned, and the flag
       * is reset to GL_NO_ERROR. If a call to code() returns GL_NO_ERROR, there has
       * been no detectable error since the last call to code(), or since the GL was
       * initialized.
       *
       * @return The value of the error flag
       */
      static GLenum code();
      /**
       * @brief Getting errors' descriptions
       *
       * Obtains the full description and name of all the currents errors since the last
       * call to code(), message() or the beginning of the program.
       *
       * @return String containing the full error's information or empty if there is no error
       */
      static std::string message();
      /**
       * @brief Getting error's description
       *
       * Obtains the full description and name of the `error_code` value.
       *
       * @param error_code The error code obtained from `code()` or `glGetError()`
       *
       * @return String containing the full error's information or empty if there is no error
       */
      static std::string message(const GLenum error_code);

    private:
    };
  }
}
#endif // RAMROD_GL_ERROR_H
