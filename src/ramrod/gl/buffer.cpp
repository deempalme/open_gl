#include "ramrod/gl/buffer.h"

namespace ramrod {
  namespace gl {
    buffer::buffer(const bool create):
      array_buffer_(0),
      element_buffer_(0),
      vertex_array_(0)
    {
      if(create)
        generate_vertex();
    }

    buffer::~buffer(){
      if(array_buffer_ > 0)
        glDeleteBuffers(1, &array_buffer_);

      if(element_buffer_ > 0)
        glDeleteBuffers(1, &element_buffer_);

      if(vertex_array_ > 0)
        glDeleteVertexArrays(1, &vertex_array_);
    }

    bool buffer::allocate_array(const GLvoid *data, const GLsizei size_in_bytes,
                                const GLenum ussage){
      if(array_buffer_ == 0) return false;
      glBufferData(GL_ARRAY_BUFFER, size_in_bytes, data, ussage);
      return true;
    }

    bool buffer::allocate_element(const GLvoid *data, const GLsizei size_in_bytes,
                                  const GLenum ussage){
      if(element_buffer_ == 0) return false;
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_in_bytes, data, ussage);
      return true;
    }

    bool buffer::allocate_section_array(const GLvoid *data, const GLint offset,
                                        const GLsizei size_in_bytes){
      if(array_buffer_ == 0) return false;
      glBufferSubData(GL_ARRAY_BUFFER, offset, size_in_bytes, data);
      return true;
    }

    bool buffer::allocate_section_element(const GLvoid *data, const GLint offset,
                                          const GLsizei size_in_bytes){
      if(element_buffer_ == 0) return false;
      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size_in_bytes, data);
      return true;
    }

    void buffer::attributte_buffer(const GLuint index, const GLint size, const GLint offset,
                                   const GLsizei stride, const GLenum type,
                                   const GLboolean normalized){
      glVertexAttribPointer(index, size, type, normalized, stride,
                            reinterpret_cast<const GLvoid*>(offset));
    }

    void buffer::buffer_bind(){
      if(array_buffer_ > 0)
        glBindBuffer(GL_ARRAY_BUFFER, array_buffer_);
      if(element_buffer_ > 0)
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
    }

    void buffer::buffer_release(){
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    bool buffer::delete_buffer(){
      if(vertex_array_ == 0 && array_buffer_ == 0 && element_buffer_ == 0) return false;

      if(array_buffer_ > 0){
        glDeleteBuffers(1, &array_buffer_);
        array_buffer_ = 0;
      }
      if(element_buffer_ > 0){
        glDeleteBuffers(1, &element_buffer_);
        element_buffer_ = 0;
      }
      if(vertex_array_ > 0){
        glDeleteVertexArrays(1, &vertex_array_);
        vertex_array_ = 0;
      }
      return true;
    }

    void buffer::disable(const GLuint attribute_id){
      glDisableVertexAttribArray(attribute_id);
    }

    void buffer::divisor(const GLuint attribute_id, const GLuint divisor){
      glVertexAttribDivisor(attribute_id, divisor);
    }

    void buffer::enable(const GLuint attribute_id){
      glEnableVertexAttribArray(attribute_id);
    }

    bool buffer::generate_array(){
      if(array_buffer_ > 0) return false;
      glGenBuffers(1, &array_buffer_);
      return array_buffer_ > 0;
    }

    bool buffer::generate_element(){
      if(element_buffer_ > 0) return false;
      glGenBuffers(1, &element_buffer_);
      return element_buffer_ > 0;
    }

    bool buffer::generate_vertex(){
      if(vertex_array_ > 0) return false;
      glGenVertexArrays(1, &vertex_array_);
      return vertex_array_ > 0;
    }

    GLuint buffer::id_array(){
      return array_buffer_;
    }

    GLuint buffer::id_element(){
      return element_buffer_;
    }

    GLuint buffer::id_vertex(){
      return vertex_array_;
    }

    GLint buffer::size_array(){
      GLint size{0};
      if(array_buffer_ > 0){
        glBindBuffer(GL_ARRAY_BUFFER, array_buffer_);
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
      }
      return size;
    }

    GLint buffer::size_element(){
      GLint size{0};
      if(element_buffer_ > 0){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
        glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
      }
      return size;
    }

    void buffer::vertex_bind(){
      glBindVertexArray(vertex_array_);
    }

    void buffer::vertex_release(){
      glBindVertexArray(0);
    }
  }
}
