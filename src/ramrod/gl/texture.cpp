#include "ramrod/gl/texture.h"

namespace ramrod{
  namespace gl {
    texture::texture(const bool create, const GLuint active_texture, const GLenum texture_target) :
      id_(0),
      active_texture_(active_texture),
      data_type_(GL_UNSIGNED_BYTE),
      texture_target_(texture_target),
      internal_format_(GL_RGBA8),
      max_filtering_(8.0f),
      has_mipmap_(true),
      custom_filtering_(false)
    {
      if(create)
        generate();
    }

    texture::~texture(){
      if(id_ > 0)
        glDeleteTextures(1, &id_);
    }

    void texture::activate(){
      glActiveTexture(GL_TEXTURE0 + active_texture_);
    }

    void texture::active_texture(){
      glActiveTexture(GL_TEXTURE0 + active_texture_);
    }

    void texture::active_texture(const GLuint new_active_texture){
      glActiveTexture(GL_TEXTURE0 + (active_texture_ = new_active_texture));
    }

    GLuint texture::active_texture_id(){
      return active_texture_;
    }

    bool texture::allocate(const GLsizei width, const GLsizei height, const void *texture_data,
                           const GLenum data_format, const GLenum data_type,
                           const GLint internal_format, const GLenum target,
                           const GLint level){
      if(id_ == 0) return false;
      glTexImage2D(target, level, internal_format_ = internal_format, width, height,
                   0, data_format, data_type_ = data_type, texture_data);
      return true;
    }

    bool texture::allocate(const GLsizei width, const GLsizei height,
                           const void *texture_data, const int component_size){
      if(id_ == 0) return false;

      GLenum data_format{GL_RGBA};
      GLint internal_format{GL_RGBA8};

      switch(component_size){
        case 1:
          data_format = GL_RED;
          internal_format = GL_R8;
        break;
        case 2:
          data_format = GL_RG;
          internal_format = GL_RG8;
        break;
        case 3:
          data_format = GL_RGB;
          internal_format = GL_RGB8;
        break;
        default:
        break;
      }
      glTexImage2D(GL_TEXTURE_2D, 0, internal_format_ = internal_format, width, height,
                   0, data_format, data_type_ = GL_UNSIGNED_BYTE, texture_data);
      return true;
    }

    void texture::bind(){
      glBindTexture(texture_target_, id_);
    }

    bool texture::delete_texture(){
      if(id_ == 0) return false;
      glDeleteTextures(1, &id_);
      id_ = 0;
      return true;
    }

    bool texture::generate(){
      if(id_ == 0){
        glGenTextures(1, &id_);
        return id_ > 0;
      }
      return false;
    }

    bool texture::generate_mipmap(){
      if(id_ == 0) return false;
      glGenerateMipmap(texture_target_);
      return true;
    }

    bool texture::parameter(const GLint wrap_s, const GLint wrap_t,
                            const GLint min_filter, const GLint mag_filter){
      if(id_ == 0) return false;

      if(has_mipmap_){
        // set the texture wrapping parameters
        glTexParameteri(texture_target_, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(texture_target_, GL_TEXTURE_WRAP_T, wrap_t);
        // set texture filtering parameters
        glTexParameteri(texture_target_, GL_TEXTURE_MIN_FILTER, min_filter);
        glTexParameteri(texture_target_, GL_TEXTURE_MAG_FILTER, mag_filter);
        // Set anisotropic filter
        if(custom_filtering_)
          glTexParameterf(texture_target_, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_filtering_);
        else
          glTexParameterf(texture_target_, GL_TEXTURE_MAX_ANISOTROPY_EXT, global_max_filtering_);
        // Generates mipmap
        glGenerateMipmap(texture_target_);
      }else{
        glTexParameteri(texture_target_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(texture_target_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      }
      return true;
    }

    bool texture::parameter(const GLenum parameter_name, const GLint value){
      if(id_ == 0) return false;
      glTexParameteri(texture_target_, parameter_name, value);
      return true;
    }
    bool texture::parameter(const GLenum parameter_name, const GLfloat value){
      if(id_ == 0) return false;
      glTexParameterf(texture_target_, parameter_name, value);
      return true;
    }

    GLuint texture::id(){
      return id_;
    }

    void texture::internal_format(const GLint new_internal_format){
      internal_format_ = new_internal_format;
    }

    GLfloat texture::max_anisotropic_filtering(){
      if(custom_filtering_) return max_filtering_;
      return global_max_filtering_;
    }

    void texture::max_anisotropic_filtering(const GLfloat new_max_filtering){
      max_filtering_ = new_max_filtering;
      custom_filtering_ = true;
    }

    bool texture::mipmap(){
      return has_mipmap_;
    }

    void texture::mipmap(const bool generate_mipmap){
      has_mipmap_ = generate_mipmap;
    }

    GLenum texture::texture_target(){
      return texture_target_;
    }

    void texture::texture_target(const GLenum new_texture_target){
      texture_target_ = new_texture_target;
    }

    bool texture::set_max_filtering(const GLfloat max_filtering){
      if(filtering_initialized_) return false;

      global_max_filtering_ = max_filtering;
      return true;
    }

    // ::::::::::::::::::::::::::::::: INITIALIZING STATIC VARIABLES ::::::::::::::::::::::::::::::::

    bool texture::filtering_initialized_ = false;
    GLfloat texture::global_max_filtering_{0.0f};
  }
}
