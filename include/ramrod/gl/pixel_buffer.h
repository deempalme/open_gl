#ifndef RAMROD_GL_PIXEL_BUFFER_H
#define RAMROD_GL_PIXEL_BUFFER_H

// OpenGL loader and core library
#include "glad/glad.h"

namespace ramrod {
  namespace gl {
    class pixel_buffer
    {
    public:
      pixel_buffer(const bool generate = false);
      ~pixel_buffer();
      /**
       * @brief Creates and initializes a buffer object's data store
       *
       * @param data Specifies a pointer to data that will be copied into the data store
       *        for initialization, or `nullptr` if no data is to be copied.
       * @param size_in_bytes Specifies the size in bytes of the buffer object's new data store.
       * @param usage Specifies the expected usage pattern of the data store:
       *                GL_STREAM_DRAW is for streaming texture upload and
       *                GL_STREAM_READ is for asynchronous framebuffer read-back.
       *
       * @return false if the pixel buffer has not been generated
       */
      bool allocate_data(const GLvoid *data, const GLsizei size_in_bytes,
                         const GLenum usage = GL_STREAM_READ);
      /**
       * @brief Binds this pixel buffer object
       * @return false if the pixel buffer has not been generated
       */
      bool bind();
      /**
       * @brief Generates a new pixel buffer object
       * @return false if the pixel buffer object was already created
       */
      bool generate();
      /**
       * @brief Deletes this pixel buffer object
       * @return true in success or false if the object was not yet generated
       */
      bool delete_buffer();
      /**
       * @brief Pixel buffer's id
       * @return The id or 0 if there was an error or not yet generated
       */
      GLuint id();
      /**
       * @brief Checks if the pixel buffer was generated
       * @return false if the pixel buffer has not been generated
       */
      bool is_created();
      /**
       * @brief Map all of a buffer object's data store into the client's address space
       *
       * @param access Specifies the access policy, indicating whether it will be possible
       *        to read from, write to, or both read from and write to the buffer object's
       *        mapped data store. The symbolic constant must be GL_READ_ONLY,
       *        GL_WRITE_ONLY, or GL_READ_WRITE.
       *
       * @return Pointer to the mapped data or nullptr if error happends or object was not generated
       */
      void *map(const GLenum access = GL_READ_ONLY);
      /**
       * @brief Map all or part of a buffer object's data store into the client's address space
       *
       * @param offset Specifies the starting offset within the buffer of the range to be mapped.
       * @param length Specifies the length of the range to be mapped.
       * @param access Specifies a combination of access flags indicating the desired access
       *        to the mapped range. See the following link for more info:
       *          https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glMapBufferRange.xhtml
       *
       * @return Pointer to the mapped data or nullptr if error happends or object was not generated
       */
      void *map_range(const GLintptr offset, const GLsizeiptr length,
                      const GLenum access = GL_MAP_READ_BIT);
      /**
       * @brief Select a color buffer source for pixels
       *
       * @param mode Specifies a color buffer. Accepted values are GL_FRONT_LEFT, GL_FRONT_RIGHT,
       *             GL_BACK_LEFT, GL_BACK_RIGHT, GL_FRONT, GL_BACK, GL_LEFT, GL_RIGHT, and the
       *             constants GL_COLOR_ATTACHMENTi.
       */
      void read_buffer(const GLenum mode = GL_FRONT);
      /**
       * @brief read_pixels
       *
       * @param x Specify the window horizontal coordinates of the first pixel that is
       *        read from the frame buffer.
       * @param y Specify the window vertical coordinates of the first pixel that is
       *        read from the frame buffer.
       * @param width Specify the horizontal dimensions of the pixel rectangle in pixels.
       * @param height Specify the vertical dimensions of the pixel rectangle in pixels.
       * @param format Specifies the format of the pixel data
       * @param type Specifies the data type of the pixel data.
       * @param data Returns the pixel data.
       *
       * @return false if the pixel buffer has not been generated
       */
      bool read_pixels(const GLint x, const GLint y,
                       const GLsizei width, const GLsizei height,
                       const GLenum format =  GL_BGRA,
                       const GLenum type =  GL_UNSIGNED_BYTE,
                       void *data = nullptr);
      /**
       * @brief Releases the current pixel buffer object
       */
      void release();
      /**
       * @brief Release the mapping of a buffer object's data store into the client's address space
       * @return true unless the data store contents have become corrupt during the time the
       *         data store was mapped
       */
      bool unmap();

    private:
      GLuint buffer_id_;
    };
  }
}
#endif // RAMROD_GL_PIXEL_BUFFER_H
