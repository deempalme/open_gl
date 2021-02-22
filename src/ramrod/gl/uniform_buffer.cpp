#include "ramrod/gl/uniform_buffer.h"

namespace ramrod {
  namespace gl {
    uniform_buffer::uniform_buffer(const bool create):
      id_(0)
    {
      if(create)
        generate();
    }

    uniform_buffer::~uniform_buffer(){
      if(id_ > 0)
        glDeleteBuffers(1, &id_);
    }

    bool uniform_buffer::allocate(const GLvoid *data, const GLsizei size_in_bytes,
                                  const GLenum ussage){
      if(id_ == 0) return false;
      glBufferData(GL_UNIFORM_BUFFER, size_in_bytes, data, ussage);
      return true;
    }

    bool uniform_buffer::allocate_section(const GLvoid *data, const GLsizeiptr size_in_bytes,
                                          const GLintptr offset){
      if(id_ == 0) return false;
      glBufferSubData(GL_UNIFORM_BUFFER, offset, size_in_bytes, data);
      return true;
    }

    void uniform_buffer::bind(){
      glBindBuffer(GL_UNIFORM_BUFFER, id_);
    }

    void uniform_buffer::bind_base(const GLuint index){
      glBindBufferBase(GL_UNIFORM_BUFFER, index, id_);
    }

    void uniform_buffer::bind_range(const GLuint index, const GLintptr offset,
                                    const GLsizeiptr size_in_bytes){
      glBindBufferRange(GL_UNIFORM_BUFFER, index, id_, offset, size_in_bytes);
    }

    GLint uniform_buffer::block_binding(const GLuint shader_id, const GLuint uniform_index) const {
      GLint binding = -1;
      glGetActiveUniformBlockiv(shader_id, uniform_index, GL_UNIFORM_BLOCK_BINDING, &binding);
      return binding;
    }

    GLint uniform_buffer::block_size(const GLuint shader_id, const GLuint uniform_index) const {
      GLint size = -1;
      glGetActiveUniformBlockiv(shader_id, uniform_index, GL_UNIFORM_BLOCK_DATA_SIZE, &size);
      return size;
    }

    bool uniform_buffer::delete_buffer(){
      if(id_ == 0) return false;
      glDeleteBuffers(1, &id_);
      id_ = 0;
      return true;
    }

    bool uniform_buffer::generate(){
      if(id_ > 0) return false;
      glGenBuffers(1, &id_);
      return true;
    }

    GLuint uniform_buffer::id() const {
      return id_;
    }

    void uniform_buffer::release(){
      glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    GLint uniform_buffer::size() const{
      GLint size{0};
      if(id_ > 0){
        glBindBuffer(GL_UNIFORM_BUFFER, id_);
        glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_SIZE, &size);
      }
      return size;
    }
  }
}
