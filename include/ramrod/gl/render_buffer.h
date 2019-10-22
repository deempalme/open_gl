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

      // Attaching the render_buffer to the bound FrameBuffer.
      // Returns false if render_buffer has not yet been created
      void attach_render_to_framebuffer(const GLenum internal_format = GL_DEPTH_STENCIL_ATTACHMENT);

      // Activate this render_buffer, returns false if not created yet
      void bind();

      bool delete_buffer();

      bool generate();

      // returns the render buffer id
      GLuint id();

      // returns true if the Frame buffer was properly created
      bool is_created();

      // Releases the actual render_buffer
      void release();

      // Establish data storage, format and dimensions of a render_buffer object's image.
      // Returns false if render_buffer has not yet been created
      bool storage(const GLsizei width, const GLsizei height,
                   const GLenum format = GL_DEPTH24_STENCIL8);

    private:
      GLuint id_;
    };
  }
}
#endif // RAMROD_GL_RENDER_BUFFER_H
