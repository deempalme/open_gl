#ifndef RAMROD_GL_UNIFORM_BUFFER_H
#define RAMROD_GL_UNIFORM_BUFFER_H

#include "glad/glad.h"

namespace ramrod {
  namespace gl {
    class uniform_buffer
    {
    public:
      /**
       * @brief Constructs this buffer object
       *
       * @param create Indicates if the `GL_UNIFORM_BUFFER` should be generated inmediately
       */
      uniform_buffer(const bool create = false);
      /**
       * @brief Frees the memory of its `GL_UNIFORM_BUFFER`
       */
      ~uniform_buffer();
      /**
       * @brief Allocating a `GL_UNIFORM_BUFFER`
       *
       * Creates and initializes a buffer object's data store.
       *
       * @param data Specifies a pointer to data that will be copied into the data store
       *             for initialization, or `nullptr` if no data is to be copied.
       * @param size_in_bytes Specifies the size in bytes of the buffer object's new data store.
       * @param ussage Specifies the expected usage pattern of the data store. The symbolic
       *               constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY,
       *               GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW,
       *               GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
       *
       * @returns `false` if `generate()` has not been called
       */
      bool allocate(const GLvoid *data, const GLsizei size_in_bytes,
                    const GLenum ussage = GL_STATIC_DRAW);
      /**
       * @brief Allocating a section of a `GL_UNIFORM_BUFFER`
       *
       * Updates a subset of a buffer object's data store
       *
       * @param data Specifies a pointer to the new data that will be copied into the data store.
       * @param size_in_bytes Specifies the size in bytes of the data store region being replaced.
       * @param offset Specifies the offset into the buffer object's data store where data
       *               replacement will begin, measured in bytes.
       *
       * @returns `false` if `generate()` has not been called
       */
      bool allocate_section(const GLvoid *data, const GLsizeiptr size_in_bytes,
                            const GLintptr offset = 0);
      /**
       * @brief Binds this buffer's `GL_UNIFORM_BUFFER`
       */
      void bind();
      /**
       * @brief Bind this uniform buffer object to an indexed buffer target
       *
       * @param index Specify the index of the binding point within the array specified by target.
       */
      void bind_base(const GLuint index);
      /**
       * @brief Bind a range within a uniform buffer object to an indexed buffer target
       *
       * @param index Specify the index of the binding point within the array
       *              specified by _target_.
       * @param offset The starting offset in basic machine units into the
       *               buffer object _buffer_.
       * @param size_in_bytes The amount of data in machine units that can be read from
       *                      the buffer object while used as an indexed target.
       */
      void bind_range(const GLuint index, const GLintptr offset,
                      const GLsizeiptr size_in_bytes);
      /**
       * @brief Deletes this `GL_UNIFORM_BUFFER`
       */
      bool delete_buffer();
      /**
       * @brief Generates a `GL_UNIFORM_BUFFER` buffer
       *
       * @return `false` if it was not possible to generate the uniform buffer
       */
      bool generate();
      /**
       * @brief Releases this buffer's `GL_UNIFORM_BUFFER`
       */
      void release();
      /**
       * @brief Getting the size in bytes of the `GL_UNIFORM_BUFFER`
       *
       * This function additionally binds the  `GL_UNIFORM_BUFFER`
       *
       * @returns Size in bytes of `GL_UNIFORM_BUFFER`
       */
      GLint size();

    private:
      GLuint buffer_;
    };
  }
}
#endif // RAMROD_GL_UNIFORM_BUFFER_H
