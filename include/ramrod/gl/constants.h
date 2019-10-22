#ifndef RAMROD_GL_CONSTANTS_H
#define RAMROD_GL_CONSTANTS_H

namespace ramrod {
  constexpr char GL_FRAMEBUFFER_UNDEFINED_error[] =
      "The specified framebuffer is the default read or draw framebuffer, "
      "but the default framebuffer does not exist.\0";
  constexpr char GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_error[] =
      "The framebuffer attachment points are framebuffer incomplete.\0";
  constexpr char GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_error[] =
      "The framebuffer does not have at least one image attached to it.\0";
  constexpr char GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_error[] =
      "The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for "
      "any color attachment point(s) named by GL_DRAW_BUFFERi.\0";
  constexpr char GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_error[] =
      "GL_READ_BUFFER is not GL_NONE and the value of "
      "GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color "
      "attachment point named by GL_READ_BUFFER.\0";
  constexpr char GL_FRAMEBUFFER_UNSUPPORTED_error[] =
      "The combination of internal formats of the attached images "
      "violates an implementation-dependent set of restrictions.\0";
  constexpr char GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_error[] =
      "The value of GL_RENDERBUFFER_SAMPLES is not the same for all "
      "attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the "
      "not same for all attached textures; or, if the attached images are "
      "a mix of renderbuffers and textures, the value of "
      "GL_RENDERBUFFER_SAMPLES does not match the value of "
      "GL_TEXTURE_SAMPLES.\n\n"
      "The value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for "
      "all attached textures; or, if the attached images are a mix of "
      "renderbuffers and textures, the value of "
      "GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all "
      "attached textures.\0";
  constexpr char GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_error[] =
      "A framebuffer attachment is layered, and any populated attachment "
      "is not layered, or if all populated color attachments are not from "
      "textures of the same target.\0";
  constexpr char GL_UNKNOWN_error[] = "Unknown error.\0";
  constexpr char GL_FRAMEBUFFER_COMPLETE_ok[] = "Framebuffer is complete\0";
}

#endif // RAMROD_GL_CONSTANTS_H
