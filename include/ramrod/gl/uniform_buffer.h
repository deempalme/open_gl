#ifndef RAMROD_GL_UNIFORM_BUFFER_H
#define RAMROD_GL_UNIFORM_BUFFER_H

#include "glad/glad.h"

namespace ramrod {
  namespace gl {
    class uniform_buffer
    {
    public:
      // construct this Buffer object and creates a new GL_VERTEX_ARRAY if create is true
      uniform_buffer(const bool create = false);
      // frees the memory of its GL_UNIFORM_BUFFER
      ~uniform_buffer();
      // Allocates the buffer data
      bool allocate(const GLvoid *data, const GLsizei size_in_bytes,
                    const GLenum ussage = GL_STATIC_DRAW);
      // Allocates a section into the buffer data
      bool allocate_section(const GLvoid *data, const GLsizeiptr size_in_bytes,
                            const GLintptr offset_in_bytes = 0);
      // binds this GL_UNIFORM_BUFFER
      void bind();
      void bind_base(const GLuint index);
      void bind_range(const GLuint index, const GLintptr offset_in_bytes,
                      const GLsizeiptr size_in_bytes);
      bool delete_buffer();
      // creates a new buffer
      bool generate();
      // Releases this GL_UNIFORM_BUFFER
      void release();
      // Links a specific region of a buffer to a binding point
      bool range(const GLsizeiptr size_in_bytes, const GLuint index = 0,
                 const GLintptr offset_in_bytes = 0);
      // Returns the size in bytes of the array buffer
      GLint size();

    private:
      GLuint buffer_;
    };
  }
}
#endif // RAMROD_GL_UNIFORM_BUFFER_H
