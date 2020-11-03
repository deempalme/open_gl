#include "ramrod/gl/pixel_buffer.h"

namespace ramrod {
  namespace gl {
    pixel_buffer::pixel_buffer(const bool generate) :
      buffer_id_{0}
    {
      if(generate)
        this->generate();
    }

    pixel_buffer::~pixel_buffer(){
      if(buffer_id_ > 0)
        glDeleteBuffers(1, &buffer_id_);
    }

    bool pixel_buffer::allocate_data(const GLvoid *data, const GLsizei size_in_bytes,
                                     const GLenum usage){
      if(buffer_id_ == 0) return false;
      glBufferData(GL_PIXEL_PACK_BUFFER, size_in_bytes, data, usage);
      return true;
    }

    bool pixel_buffer::bind(){
      if(buffer_id_ == 0) return false;
      glBindBuffer(GL_PIXEL_PACK_BUFFER, buffer_id_);
      return true;
    }

    bool pixel_buffer::generate(){
      if(buffer_id_ > 0) return false;
      glGenBuffers(1, &buffer_id_);
      return buffer_id_ > 0;
    }

    bool pixel_buffer::delete_buffer(){
      if(buffer_id_ == 0) return false;
      glDeleteBuffers(1, &buffer_id_);
      return true;
    }

    GLuint pixel_buffer::id(){
      return buffer_id_;
    }

    bool pixel_buffer::is_created(){
      return buffer_id_ > 0;
    }

    void *pixel_buffer::map(const GLenum access){
      if(buffer_id_ == 0) return nullptr;
      return glMapBuffer(GL_PIXEL_PACK_BUFFER, access);
    }

    void *pixel_buffer::map_range(const GLintptr offset, const GLsizeiptr length,
                                  const GLenum access){
      if(buffer_id_ == 0) return nullptr;
      return glMapBufferRange(GL_PIXEL_PACK_BUFFER, offset, length, access);
    }

    void pixel_buffer::read_buffer(const GLenum mode){
      glReadBuffer(mode);
    }

    bool pixel_buffer::read_pixels(const GLint x, const GLint y,
                                   const GLsizei width, const GLsizei height,
                                   const GLenum format, const GLenum type, void *data){
      if(buffer_id_ == 0) return false;
      glReadPixels(x, y, width, height, format, type, data);
      return true;
    }

    void pixel_buffer::release(){
      glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    }

    bool pixel_buffer::unmap(){
      return glUnmapBuffer(GL_PIXEL_PACK_BUFFER) == GL_TRUE;
    }
  } // namespace: gl
} // namespace: ramrod
