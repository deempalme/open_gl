#include "ramrod/gl/uniform_buffer.h"

namespace ramrod {
  namespace gl {
    uniform_buffer::uniform_buffer(const bool create):
      buffer_(0)
    {
      if(create)
        generate();
    }

    uniform_buffer::~uniform_buffer(){
      if(buffer_ > 0)
        glDeleteBuffers(1, &buffer_);
    }

    bool uniform_buffer::allocate(const GLvoid *data, const GLsizei size_in_bytes,
                                  const GLenum ussage){
      if(buffer_ > 0) return false;
      glBufferData(GL_UNIFORM_BUFFER, size_in_bytes, data, ussage);
      return true;
    }

    bool uniform_buffer::allocate_section(const GLvoid *data, const GLsizeiptr size_in_bytes,
                                          const GLintptr offset){
      if(buffer_ > 0) return false;
      glBufferSubData(GL_UNIFORM_BUFFER, offset, size_in_bytes, data);
      return true;
    }

    void uniform_buffer::bind(){
      glBindBuffer(GL_UNIFORM_BUFFER, buffer_);
    }

    void uniform_buffer::bind_base(const GLuint index){
      glBindBufferBase(GL_UNIFORM_BUFFER, index, buffer_);
    }

    void uniform_buffer::bind_range(const GLuint index, const GLintptr offset,
                                    const GLsizeiptr size_in_bytes){
      glBindBufferRange(GL_UNIFORM_BUFFER, index, buffer_, offset, size_in_bytes);
    }

    bool uniform_buffer::delete_buffer(){
      if(buffer_ == 0) return false;
      glDeleteBuffers(1, &buffer_);
      return true;
    }

    bool uniform_buffer::generate(){
      if(buffer_ > 0) return false;
      glGenBuffers(1, &buffer_);
      return true;
    }

    void uniform_buffer::release(){
      glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    GLint uniform_buffer::size(){
      GLint size{0};
      if(buffer_ > 0){
        glBindBuffer(GL_UNIFORM_BUFFER, buffer_);
        glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_SIZE, &size);
      }
      return size;
    }
  }
}
