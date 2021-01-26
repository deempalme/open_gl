#ifndef RAMROD_GL_FRAME_BUFFER_H
#define RAMROD_GL_FRAME_BUFFER_H

// OpenGL loader and core library
#include "glad/glad.h"

namespace ramrod {
  namespace gl {
    class frame_buffer
    {
    public:
      frame_buffer(const bool generate = false, const bool add_render_buffer = false);
      ~frame_buffer();
      /**
       * @brief Attaches a texture into the frame buffer
       * @return false if frame buffer was not generated
       */
      bool attach_2D(const GLuint texture, const GLenum attachment = GL_COLOR_ATTACHMENT0,
                     const GLenum texture_target_type = GL_TEXTURE_2D, const GLint level = 0);
      /**
       * @brief Attaches the render buffer to the frame buffer
       * @return false if frame buffer or render buffer have been generated
       */
      bool attach_render(const GLenum render_attachment = GL_DEPTH_ATTACHMENT);
      /**
       * @brief Binds the frame buffer
       * @return false if frame buffer was not generated
       */
      void bind();
      /**
       * @brief Binds the render buffer
       * @return false if render was not generated
       */
      void bind_render();
      /**
       * @brief Clears the frame buffer content
       */
      void clear(GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      /**
       * @brief Deletes the frame buffer and render buffer (if created)
       * @return false if frame buffer does not exist
       */
      bool delete_frame();
      /**
       * @brief Deletes the render buffer
       * @return false if render buffer does not exist
       */
      bool delete_render();
      /**
       * @brief Draws this frame buffer
       * @return false if render buffer does not exist
       */
      bool draw_buffer();
      /**
       * @brief Specify which color buffers are to be drawn into
       *
       * @param buffer For default framebuffer, the argument specifies up to four color buffers
       *        to be drawn into. Symbolic constants GL_NONE, GL_FRONT_LEFT, GL_FRONT_RIGHT,
       *        GL_BACK_LEFT, GL_BACK_RIGHT, GL_FRONT, GL_BACK, GL_LEFT, GL_RIGHT, and
       *        GL_FRONT_AND_BACK are accepted. The initial value is GL_FRONT for
       *        single-buffered contexts, and GL_BACK for double-buffered contexts. For
       *        framebuffer objects, GL_COLOR_ATTACHMENT$m$ and GL_NONE enums are accepted,
       *        where $m$ is a value between 0 and GL_MAX_COLOR_ATTACHMENTS.
       */
      void draw_buffer(const GLenum buffer);
      /**
       * @brief Specifies a list of color buffers to be drawn into
       *
       * @param number_of_buffers Specifies the number of buffers in bufs.
       * @param buffers Points to an array of symbolic constants specifying the buffers
       *        into which fragment colors or data values will be written.
       */
      void draw_buffers(const GLsizei number_of_buffers, const GLenum *buffers);
      /**
       * @brief Returns the frame attachment point
       * @return for more info see
       *    https://khronos.org/registry/OpenGL-Refpages/gl4/html/glFramebufferTexture.xhtml
       */
      GLenum frame_attachment();
      /**
       * @brief Returns the frame buffer id
       * @return Returns the frame buffer ID
       */
      GLuint frame_id();
      /**
       * @brief Generates a frame buffer and optionally a render buffer too
       * @return false if frame buffer was already created
       */
      bool generate_frame(const bool generate_render_buffer = false);
      /**
       * @brief Generates a render buffer
       * @return false if render buffer was already generated
       */
      bool generate_render();
      /**
       * @brief Returns true if the Frame buffer was properly created
       * @return false if frame buffer is not created yet
       */
      bool is_created();
      /**
       * @brief Read this framebuffer
       * @return false if frame buffer is not created yet
       */
      bool read_buffer();
      /**
       * @brief Reads a pixel from the frame buffer
       * @return false if frame buffer is not created yet
       */
      bool read_pixel(GLvoid *data, const GLint x, const GLint y,
                      const GLsizei width = 1, const GLsizei height = 1,
                      const GLenum type = GL_UNSIGNED_BYTE, const GLenum components = GL_RGBA);
      /**
       * @brief Releases the actual frame buffer
       * @return false if frame buffer is not created yet
       */
      void release();
      /**
       * @brief Releases the render buffer
       * @return false if render buffer is not created yet
       */
      void release_render();
      /**
       * @brief Returns the Render attachment type
       * @return For more info see
       *    https://khronos.org/registry/OpenGL-Refpages/gl4/html/glFramebufferRenderbuffer.xhtml
       */
      GLenum render_attachment();
      /**
       * @brief Returns Render Buffer internal format
       * @return For more info see
       *    https://khronos.org/registry/OpenGL-Refpages/gl4/html/glFramebufferRenderbuffer.xhtml
       */
      GLenum render_format();
      /**
       * @brief Returns Render Buffer ID
       * @return render buffer id
       */
      GLuint render_id();
      /**
       * @brief Defines Render Buffer properties
       * @return false if render buffer is not created yet
       */
      bool render_storage(const GLsizei width, const GLsizei height,
                          const GLenum internal_format = GL_DEPTH_COMPONENT24);
      /**
       * @brief Returning the status of this frame buffer
       * @return for more info see
       *    https://khronos.org/registry/OpenGL-Refpages/gl4/html/glCheckFramebufferStatus.xhtml
       */
      GLenum status();
      /**
       * @brief Returning the datailed explanation of the current framebuffer's status
       * @return Detailed information about the current error
       */
      const char *status_msg();

    private:
      GLuint frame_id_, render_id_;
      GLenum frame_attachment_, render_attachment_, render_format_;
    };
  }
}
#endif // RAMROD_GL_FRAME_BUFFER_H
