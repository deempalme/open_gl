#ifndef RAMROD_GL_TEXTURE_H
#define RAMROD_GL_TEXTURE_H

// OpenGL loader and core library
#include "glad/glad.h"

namespace ramrod{
  namespace gl {
    class texture
    {
    public:
      /**
       * @brief Creates a texture object
       *
       * @param create         Indicates if the texture's name should be generated right away
       * @param active_texture Specifies which texture unit to make active, integer starting from 0
       * @param has_mipmap     Indicates if this texture will be generating mipmaps
       * @param texture_target Specifies the target to which the texture is bound
       */
      texture(const bool create = false,
              const GLuint active_texture = 0,
              const bool has_mipmap = true,
              const GLenum texture_target = GL_TEXTURE_2D);
      /**
        * @brief Deletes this named texture
        */
      ~texture();
      /**
       * @brief Select this texture's active unit
       */
      void activate();
      /**
       * @brief Select this texture's active unit
       */
      void active_texture();
      /**
       * @brief Choses a new texture's active unit and activates it
       *
       * @param new_active_texture Specifies the new texture unit to make active
       */
      void active_texture(const GLuint new_active_texture);
      /**
       * @brief Getting this texture's active unit
       *
       * @return texture's active unit
       */
      GLuint active_texture_id();
      /**
       * @brief Specify a two-dimensional texture image
       *
       * @param width        Specifies the width of the texture image.
       * @param height       Specifies the height of the texture image
       * @param texture_data Specifies a pointer to the image data in memory.
       * @param data_format  Specifies the format of the pixel data. The following symbolic
       *                     values are accepted: GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA,
       *                     GL_BGRA, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER,
       *                     GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER,
       *                     GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL.
       * @param data_type    Specifies the data type of the pixel data. The following
       *                     symbolic values are accepted: GL_UNSIGNED_BYTE, GL_BYTE,
       *                     GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT,
       *                     GL_HALF_FLOAT, GL_FLOAT, GL_UNSIGNED_BYTE_3_3_2,
       *                     GL_UNSIGNED_BYTE_2_3_3_REV, GL_UNSIGNED_SHORT_5_6_5,
       *                     GL_UNSIGNED_SHORT_5_6_5_REV, GL_UNSIGNED_SHORT_4_4_4_4,
       *                     GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_UNSIGNED_SHORT_5_5_5_1,
       *                     GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_INT_8_8_8_8,
       *                     GL_UNSIGNED_INT_8_8_8_8_REV, GL_UNSIGNED_INT_10_10_10_2,
       *                     and GL_UNSIGNED_INT_2_10_10_10_REV.
       * @param internal_format Specifies the number of color components in the texture.
       * @param level        Specifies the level-of-detail number. Level 0 is the base image level.
       *                     Level n is the nth mipmap reduction image.
       * @return `false` if the texture has not been generated yet
       */
      bool allocate(const GLsizei width, const GLsizei height, const void *texture_data = nullptr,
                    const GLenum data_format = GL_RGBA, const GLenum data_type = GL_UNSIGNED_BYTE,
                    const GLint internal_format = GL_RGBA8, const GLint level = 0);
      /**
       * @brief Specify a two-dimensional texture image
       *
       * It does automatically selects the data and internal format
       *
       * @param width          Specifies the width of the texture image.
       * @param height         Specifies the height of the texture image
       * @param texture_data   Specifies a pointer to the image data in memory.
       * @param component_size Specifies the number of color components in the texture.
       *
       * @return `false` if the texture has not been generated yet
       */
      bool allocate(const GLsizei width, const GLsizei height, const void *texture_data,
                    const int component_size);
      /**
       * @brief Specify a two-dimensional texture subimage
       *
       * @param width        Specifies the width of the texture subimage.
       * @param height       Specifies the height of the texture subimage.
       * @param texture_data Specifies a pointer to the image data in memory.
       * @param x_offset     Specifies a texel offset in the x direction within the texture array.
       * @param y_offset     Specifies a texel offset in the y direction within the texture array.
       * @param format       Specifies the format of the pixel data. The following symbolic
       *                     values are accepted: GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA,
       *                     GL_BGRA, GL_DEPTH_COMPONENT, and GL_STENCIL_INDEX.
       * @param type         Specifies the data type of the pixel data. The following
       *                     symbolic values are accepted: GL_UNSIGNED_BYTE, GL_BYTE,
       *                     GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_FLOAT,
       *                     GL_UNSIGNED_BYTE_3_3_2, GL_UNSIGNED_BYTE_2_3_3_REV,
       *                     GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_5_6_5_REV,
       *                     GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV,
       *                     GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV,
       *                     GL_UNSIGNED_INT_8_8_8_8, GL_UNSIGNED_INT_8_8_8_8_REV,
       *                     GL_UNSIGNED_INT_10_10_10_2, and GL_UNSIGNED_INT_2_10_10_10_REV.
       * @param level        Specifies the level-of-detail number. Level 0 is the base image
       *                     level. Level n is the nth mipmap reduction image.
       *
       * @return `false` if the texture has not been generated yet
       */
      bool allocate_sub_2d(const GLsizei width, const GLsizei height,
                           const void *texture_data = nullptr,
                           const GLint x_offset = 0, const GLint y_offset = 0,
                           const GLenum format = GL_RGBA,
                           const GLenum type = GL_UNSIGNED_BYTE, const GLint level = 0);
      /**
       * @brief Binds this named texture to a texturing target
       */
      void bind();
      /**
       * @brief Deletes this named texture
       *
       * @return `false` if the texture has not been generated yet
       */
      bool delete_texture();
      /**
       * @brief generate
       *
       * @return `false` if the texture was already generated
       */
      bool generate();
      /**
       * @brief Generate mipmaps for this specific texture object
       *
       * @return `false` if the texture has not been generated yet
       */
      bool generate_mipmap();
      /**
       * @brief Obtaining the texture name
       *
       * @return The texture's name
       */
      GLuint id();
      /**
       * @brief Changing this texture's internal format
       *
       * @param new_internal_format Specifies the number of color components in the texture.
       */
      void internal_format(const GLint new_internal_format);
      /**
       * @brief Obtaining this texture's maximum anisotropy filter
       *
       * @return maximum anisotropy filter value
       */
      GLfloat max_anisotropic_filtering();
      /**
       * @brief Setting this texture's maximum anisotropy filter
       *
       * @param new_max_filtering new maximum anisotropy filter value
       */
      void max_anisotropic_filtering(const GLfloat new_max_filtering);
      /**
       * @brief Indicates if this texture is generating mipmaps
       *
       * @return `true` if it is generating
       */
      bool mipmap();
      /**
       * @brief Setting if the texture should generate mipmaps
       *
       * @param generate_mipmap `true` to generate mipmaps when texture data is allocated
       */
      void mipmap(const bool generate_mipmap);
      /**
       * @brief Set texture parameters
       *
       * @param wrap_s     Sets the wrap parameter for texture coordinate s to either
       *                   GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT,
       *                   GL_REPEAT, or GL_MIRROR_CLAMP_TO_EDGE.
       * @param wrap_t     Sets the wrap parameter for texture coordinate t to either
       *                   GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT,
       *                   GL_REPEAT, or GL_MIRROR_CLAMP_TO_EDGE.
       * @param min_filter The texture minifying function is used whenever the
       *                   level-of-detail function used when sampling from the
       *                   texture determines that the texture should be minified.
       *                   GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST,
       *                   GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR,
       *                   or GL_LINEAR_MIPMAP_LINEAR
       * @param mag_filter The texture magnification function is used whenever the
       *                   level-of-detail function used when sampling from the texture
       *                   determines that the texture should be magified:
       *                   GL_NEAREST, or GL_LINEAR
       *
       * @return `false` if the texture has not been generated yet
       */
      bool parameter(const GLint wrap_s = GL_REPEAT, const GLint wrap_t = GL_REPEAT,
                     const GLint min_filter = GL_LINEAR_MIPMAP_LINEAR,
                     const GLint mag_filter = GL_LINEAR);
      /**
       * @brief Setting integer texture parameters
       *
       * @param parameter_name Specifies the symbolic name of a single-valued texture parameter.
       * @param value          specifies the integer value of parameter_name.
       *
       * @return `false` if the texture has not been generated yet
       */
      bool parameter(const GLenum parameter_name, const GLint value);
      /**
       * @brief Setting floating texture parameters
       *
       * @param parameter_name Specifies the symbolic name of a single-valued texture parameter.
       * @param value          specifies the floating value of parameter_name.
       *
       * @return `false` if the texture has not been generated yet
       */
      bool parameter(const GLenum parameter_name, const GLfloat value);
      /**
       * @brief Setting floating pixel storage modes
       *
       * @param name  Specifies the symbolic name of the parameter to be set.
       * @param param Specifies the floating value that name is set to.
       *
       * @return `false` if the texture has not been generated yet
       */
      bool pixel_store_f(GLenum name, GLfloat param);
      /**
       * @brief Setting integer pixel storage modes
       *
       * @param name  Specifies the symbolic name of the parameter to be set.
       * @param param Specifies the integer value that name is set to.
       *
       * @return `false` if the texture has not been generated yet
       */
      bool pixel_store_i(GLenum name, GLint param);
      /**
       * @brief Releases this named texture to a texturing target
       */
      void release();
      /**
       * @brief Obatining the target to which the texture is bound
       *
       * @return texture's boundary target
       */
      GLenum texture_target();
      /**
       * @brief texture_target
       *
       * @param new_texture_target Specifies the target to which the texture is bound
       */
      void texture_target(const GLenum new_texture_target);
      /**
       * @brief Setting a global texture's maximum anisotropy filter
       *
       * If max anisotropy filter values has not been set for individual textures then
       * they will take the global value
       *
       * @param max_filtering new global maximum anisotropy filter value
       */
      static bool set_max_filtering(const GLfloat max_filtering);

    private:
      GLuint id_;
      GLuint active_texture_;
      GLenum data_type_, texture_target_;
      GLint internal_format_;
      GLfloat max_filtering_;
      bool has_mipmap_, error_, custom_filtering_;

      static bool filtering_initialized_;
      static GLfloat global_max_filtering_;
    };
  }
}
#endif // RAMROD_GL_TEXTURE_H
