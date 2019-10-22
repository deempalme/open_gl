#ifndef RAMROD_GL_RENDER_PROCESSOR_H
#define RAMROD_GL_RENDER_PROCESSOR_H

// OpenGL loader and SDL2 library
#include "glad/glad.h"

namespace ramrod {
  namespace gl {
    class render_processor
    {
    public:
      render_processor();
      ~render_processor();

    protected:
      void initialize_render();
      void render();

    private:
      GLuint frame_albedo_, frame_emission_, frame_metalnes_, frame_normal_, frame_roghness_;
    };
  }
}
#endif // RAMROD_GL_RENDER_PROCESSOR_H
