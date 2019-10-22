#include "ramrod/gl/render_buffer.h"

namespace ramrod {
  namespace gl {
    render_buffer::render_buffer(const bool create) :
      id_(0)
    {
      if(create)
        generate();
    }

    render_buffer::~render_buffer(){
      if(id_ > 0)
        glDeleteRenderbuffers(1, &id_);
    }

    void render_buffer::attach_render_to_framebuffer(const GLenum internal_format){
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, internal_format, GL_RENDERBUFFER, id_);
    }

    void render_buffer::bind(){
      glBindRenderbuffer(GL_RENDERBUFFER, id_);
    }

    bool render_buffer::delete_buffer(){
      if(id_ == 0) return false;
      glDeleteRenderbuffers(1, &id_);
      id_ = 0;
      return true;
    }

    bool render_buffer::generate(){
      if(id_ == 0){
        glGenRenderbuffers(1, &id_);
        return id_ > 0;
      }else{
        return false;
      }
    }

    GLuint render_buffer::id(){
      return id_;
    }

    bool render_buffer::is_created(){
      return id_ > 0;
    }

    void render_buffer::release(){
      glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    bool render_buffer::storage(const GLsizei width, const GLsizei height, const GLenum format){
      if(id_ == 0) return false;
      glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
      return true;
    }
  }
}
