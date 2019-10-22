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
      /*
     * Attaches a texture into the frame buffer
     *
     * @returns bool : false if frame buffer was not generated
     */
      bool attach_2D(const GLuint texture, const GLenum attachment = GL_COLOR_ATTACHMENT0,
                     const GLenum texture_target_type = GL_TEXTURE_2D, const GLint level = 0);
      /*
     * Attaches the render buffer to the frame buffer
     *
     * @returns bool : false if frame buffer or render buffer have been generated
     */
      bool attach_render(const GLenum render_attachment = GL_DEPTH_ATTACHMENT);
      /*
     * Binds the frame buffer
     *
     * @returns bool : false if frame buffer was not generated
     */
      void bind();
      /*
     * Binds the render buffer
     *
     * @returns bool : false if render was not generated
     */
      void bind_render();
      /*
     * Clears the frame buffer content
     */
      void clear(GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      /*
     * Deletes the frame buffer and render buffer (if created)
     *
     * @returns bool : false if frame buffer does not exist
     */
      bool delete_frame();
      /*
     * Deletes the render buffer
     *
     * @returns bool : false if render buffer does not exist
     */
      bool delete_render();
      bool draw_buffer();
      /*
     * Returns the frame attachment point
     *
     * @returns const GLenum& : for more info see
     *    https://khronos.org/registry/OpenGL-Refpages/gl4/html/glFramebufferTexture.xhtml
     */
      GLenum frame_attachment();
      /*
     * Returns the frame buffer id
     *
     * @returns const GLuint& : Returns the frame buffer ID
     */
      GLuint frame_id();
      /*
     * Generates a render buffer
     *
     * @returns bool : false if render buffer was already generated
     */
      bool generate_render();
      /*
     * Generates a frame buffer and optionally a render buffer too
     *
     * @returns bool : false if frame buffer was already created
     */
      bool generate_frame(const bool generate_render_buffer = false);
      /*
     * Returns true if the Frame buffer was properly created
     *
     * @returns bool : false if frame buffer is not created yet
     */
      bool is_created();
      bool read_buffer();
      /*
     * Reads a pixel from the frame buffer
     *
     * @returns bool : false if frame buffer is not created yet
     */
      bool read_pixel(GLvoid *data, const GLint x, const GLint y,
                      const GLsizei width = 1, const GLsizei height = 1,
                      const GLenum type = GL_UNSIGNED_BYTE, const GLenum components = GL_RGBA);
      /*
     * Releases the actual frame buffer
     *
     * @returns bool : false if frame buffer is not created yet
     */
      void release();
      /*
     * Releases the render buffer
     *
     * @returns bool : false if render buffer is not created yet
     */
      void release_render();
      /*
     * Returns the Render attachment type
     *
     * @returns const GLenum : For more info see
     *    https://khronos.org/registry/OpenGL-Refpages/gl4/html/glFramebufferRenderbuffer.xhtml
     */
      GLenum render_attachment();
      /*
     * Returns Render Buffer internal format
     *
     * @returns const GLenum : For more info see
     *    https://khronos.org/registry/OpenGL-Refpages/gl4/html/glFramebufferRenderbuffer.xhtml
     */
      GLenum render_format();
      /*
     * Returns Render Buffer ID
     *
     * @returns const GLuint : render buffer id
     */
      GLuint render_id();
      /*
     * Defines Render Buffer properties
     *
     * @returns bool : false if render buffer is not created yet
     */
      bool render_storage(const GLsizei width, const GLsizei height,
                          const GLenum internal_format = GL_DEPTH_COMPONENT24);
      /*
     * Returning the status of this frame buffer
     *
     * @returns GLenum : for more info see
     *    https://khronos.org/registry/OpenGL-Refpages/gl4/html/glCheckFramebufferStatus.xhtml
     */
      GLenum status();
      const char *status_msg();

    private:
      GLuint frame_id_, render_id_;
      GLenum frame_attachment_, render_attachment_, render_format_;
    };
  }
}
#endif // RAMROD_GL_FRAME_BUFFER_H
