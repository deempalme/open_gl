#include "ramrod/gl/frame_buffer.h"

#include "ramrod/gl/constants.h"

namespace ramrod {
  namespace gl {
    frame_buffer::frame_buffer(const bool generate, const bool add_render_buffer) :
      frame_id_(0),
      render_id_(0),
      frame_attachment_(GL_NONE),
      render_attachment_(GL_NONE),
      render_format_(GL_NONE)
    {
      if(generate)
        generate_frame(add_render_buffer);
    }

    frame_buffer::~frame_buffer(){
      if(frame_id_ > 0)
        glDeleteFramebuffers(1, &frame_id_);
      if(render_id_ > 0)
        glDeleteRenderbuffers(1, &render_id_);
    }

    bool frame_buffer::attach_2D(const GLuint texture, const GLenum attachment,
                                 const GLenum texture_target_type, const GLint level){
      if(frame_id_ == 0) return false;

      glFramebufferTexture2D(GL_FRAMEBUFFER, frame_attachment_ = attachment,
                             texture_target_type, texture, level);
      return true;
    }

    bool frame_buffer::attach_render(const GLenum render_attachment){
      if(frame_id_ == 0 || render_id_ == 0) return false;

      glFramebufferRenderbuffer(GL_FRAMEBUFFER, render_attachment_ = render_attachment,
                                GL_RENDERBUFFER, render_id_);
      return true;
    }

    void frame_buffer::bind(){
      glBindFramebuffer(GL_FRAMEBUFFER, frame_id_);
    }

    void frame_buffer::bind_render(){
      glBindRenderbuffer(GL_RENDERBUFFER, render_id_);
    }

    void frame_buffer::clear(GLbitfield mask){
      glClear(mask);
    }

    bool frame_buffer::delete_frame(){
      if(frame_id_ == 0) return false;

      glDeleteFramebuffers(1, &frame_id_);
      frame_id_ = 0;

      delete_render();
      return true;
    }

    bool frame_buffer::delete_render(){
      if(render_id_ == 0) return false;

      glDeleteRenderbuffers(1, &render_id_);
      render_id_ = 0;
      return true;
    }

    bool frame_buffer::draw_buffer(){
      if(frame_id_ == 0) return false;
      glDrawBuffers(1, &frame_attachment_);
      return true;
    }

    void frame_buffer::draw_buffer(const GLenum buffer){
      glDrawBuffer(buffer);
    }

    void frame_buffer::draw_buffers(const GLsizei number_of_buffers, const GLenum *buffers){
      glDrawBuffers(number_of_buffers, buffers);
    }

    GLenum frame_buffer::frame_attachment(){
      return frame_attachment_;
    }

    GLuint frame_buffer::frame_id(){
      return frame_id_;
    }

    bool frame_buffer::generate_frame(const bool generate_render_buffer){
      if(frame_id_ == 0){
        glGenFramebuffers(1, &frame_id_);

        if(generate_render_buffer && render_id_ == 0)
          return generate_render();

        return true;
      }
      return false;
    }

    bool frame_buffer::generate_render(){
      if(render_id_ > 0) return false;
      glGenRenderbuffers(1, &render_id_);
      return render_id_ > 0;
    }

    bool frame_buffer::is_created(){
      return frame_id_ > 0;
    }

    bool frame_buffer::read_buffer(){
      if(frame_attachment_ != GL_NONE) return false;
      glReadBuffer(frame_attachment_);
      return true;
    }

    bool frame_buffer::read_pixel(GLvoid *data, const GLint x, const GLint y,
                                  const GLsizei width, const GLsizei height,
                                  const GLenum type, const GLenum components){
      if(frame_id_ == 0) return false;
      glReadPixels(x, y, width, height, components, type, data);
      return true;
    }

    void frame_buffer::release(){
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void frame_buffer::release_render(){
      glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    GLenum frame_buffer::render_attachment(){
      return render_attachment_;
    }

    GLenum frame_buffer::render_format(){
      return render_format_;
    }

    GLuint frame_buffer::render_id(){
      return render_id_;
    }

    bool frame_buffer::render_storage(const GLsizei width, const GLsizei height,
                                      const GLenum internal_format){
      if(render_id_ == 0) return false;
      glRenderbufferStorage(GL_RENDERBUFFER, render_format_ = internal_format, width, height);
      return true;
    }

    GLenum frame_buffer::status(){
      return glCheckFramebufferStatus(GL_FRAMEBUFFER);
    }

    const char *frame_buffer::status_msg(){
      const GLenum frame_status{glCheckFramebufferStatus(GL_FRAMEBUFFER)};

      if(frame_status != GL_FRAMEBUFFER_COMPLETE){
        switch(frame_status){
          case GL_FRAMEBUFFER_UNDEFINED:
          return GL_FRAMEBUFFER_UNDEFINED_error;
          break;
          case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
          return GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_error;
          break;
          case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
          return GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_error;
          break;
          case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
          return GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_error;
          break;
          case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
          return GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_error;
          break;
          case GL_FRAMEBUFFER_UNSUPPORTED:
          return GL_FRAMEBUFFER_UNSUPPORTED_error;
          break;
          case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
          return GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_error;
          break;
          case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
          return GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_error;
          break;
          default:
          return GL_UNKNOWN_error;
          break;
        }
      }
      return GL_FRAMEBUFFER_COMPLETE_ok;
    }
  }
}
