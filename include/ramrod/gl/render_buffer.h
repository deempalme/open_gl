#ifndef RAMROD_GL_RENDER_BUFFER_H
#define RAMROD_GL_RENDER_BUFFER_H

// OpenGL loader and core library
#include "glad/glad.h"

namespace ramrod {
  namespace gl {
    class render_buffer
    {
    public:
      render_buffer(const bool create = false);
      ~render_buffer();
      /**
       * @brief Attaching the render_buffer to the bound FrameBuffer.
       * @return  false if render_buffer has not yet been created
       */
      void attach_render_to_framebuffer(const GLenum internal_format = GL_DEPTH_STENCIL_ATTACHMENT);
      /**
       * @brief Activate this render_buffer, returns false if not created yet
       */
      void bind();
      /**
       * @brief Deletes this render buffer
       * @return false if render was not generated
       */
      bool delete_buffer();
      /**
       * @brief Generates a new render buffer
       * @return false if error when creating render buffer or if already existed
       */
      bool generate();
      /**
       * @brief Returns the render buffer id
       * @return The render's buffer id
       */
      GLuint id();
      /**
       * @brief Checking if the render buffer exist
       * @return true if the render buffer was properly created
       */
      bool is_created();
      /**
       * @brief Releases the actual render_buffer
       */
      void release();
      /**
       * @brief Establish data storage, format and dimensions of a render_buffer object's image.
       * @return false if render_buffer has not yet been created
       */
      bool storage(const GLsizei width, const GLsizei height,
                   const GLenum format = GL_DEPTH24_STENCIL8);

    private:
      GLuint id_;
    };
  }
}
#endif // RAMROD_GL_RENDER_BUFFER_H
