#include "ramrod/gl/error.h"

namespace ramrod {
  namespace gl {
    GLenum error::code(){
      return glGetError();
    }

    std::string error::message(){
      std::string error_message;
      GLenum error_code;

      while((error_code = glGetError()) != GL_NO_ERROR){
        switch(error_code){
          case GL_INVALID_ENUM:
            error_message += "GL_INVALID_ENUM: An unacceptable value is specified for an "
                             "enumerated argument. The offending command is ignored and has "
                             "no other side effect than to set the error flag.\n";
          break;
          case GL_INVALID_VALUE:
            error_message += "GL_INVALID_VALUE: A numeric argument is out of range. The "
                             "offending command is ignored and has no other side effect than "
                             "to set the error flag.\n";
          break;
          case GL_INVALID_OPERATION:
            error_message += "GL_INVALID_OPERATION: The specified operation is not allowed in "
                             "the current state. The offending command is ignored and has no "
                             "other side effect than to set the error flag.\n";
          break;
          case GL_INVALID_FRAMEBUFFER_OPERATION:
            error_message += "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is "
                             "not complete. The offending command is ignored and has no other "
                             "side effect than to set the error flag.\n";
          break;
          case GL_OUT_OF_MEMORY:
            error_message += "GL_OUT_OF_MEMORY: There is not enough memory left to execute "
                             "the command. The state of the GL is undefined, except for the "
                             "state of the error flags, after this error is recorded.\n";
          break;
#ifdef GL_STACK_UNDERFLOW
          case GL_STACK_UNDERFLOW:
            error_message += "GL_STACK_UNDERFLOW: An attempt has been made to perform an "
                             "operation that would cause an internal stack to underflow.\n";
          break;
          case GL_STACK_OVERFLOW:
            error_message += "GL_STACK_OVERFLOW: An attempt has been made to perform an "
                             "operation that would cause an internal stack to overflow.\n";
          break;
#endif
          default: break;
        }
      }
      return error_message;
    }

    std::string error::message(const GLenum error_code){
      std::string error_message;

      switch(error_code){
        case GL_INVALID_ENUM:
          error_message += "GL_INVALID_ENUM: An unacceptable value is specified for an "
                           "enumerated argument. The offending command is ignored and has "
                           "no other side effect than to set the error flag.\n";
        break;
        case GL_INVALID_VALUE:
          error_message += "GL_INVALID_VALUE: A numeric argument is out of range. The "
                           "offending command is ignored and has no other side effect than "
                           "to set the error flag.\n";
        break;
        case GL_INVALID_OPERATION:
          error_message += "GL_INVALID_OPERATION: The specified operation is not allowed in "
                           "the current state. The offending command is ignored and has no "
                           "other side effect than to set the error flag.\n";
        break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
          error_message += "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is "
                           "not complete. The offending command is ignored and has no other "
                           "side effect than to set the error flag.\n";
        break;
        case GL_OUT_OF_MEMORY:
          error_message += "GL_OUT_OF_MEMORY: There is not enough memory left to execute "
                           "the command. The state of the GL is undefined, except for the "
                           "state of the error flags, after this error is recorded.\n";
        break;
#ifdef GL_STACK_UNDERFLOW
        case GL_STACK_UNDERFLOW:
          error_message += "GL_STACK_UNDERFLOW: An attempt has been made to perform an "
                           "operation that would cause an internal stack to underflow.\n";
        break;
        case GL_STACK_OVERFLOW:
          error_message += "GL_STACK_OVERFLOW: An attempt has been made to perform an "
                           "operation that would cause an internal stack to overflow.\n";
        break;
#endif
        default: break;
      }
      return error_message;
    }
  } // namespace: gl
} // namespace: ramrod
