#include "ramrod/gl/shader.h"

#include <fstream>
#include <sstream>
#include <filesystem>

namespace ramrod {
  namespace gl {
    shader::shader() :
      id_(0),
      error_(false),
      error_log_("Shader program not created yet...\n----------\n")
    {}

    shader::shader(const std::string &vertex_path,
                   const std::string &fragment_path,
                   const std::string &geometry_path) :
      id_(0),
      error_(false),
      error_log_()
    {
      create(vertex_path, fragment_path, geometry_path);
    }

    shader::~shader(){
      if(id_ > 0)
        glDeleteProgram(id_);
    }

    GLint shader::attribute_location(const std::string &name) const{
      return glGetAttribLocation(id_, name.c_str());
    }

    bool shader::create(const std::string &vertex_path,
                        const std::string &fragment_path,
                        const std::string &geometry_path){
      if(id_ == 0){
        error_log_.clear();
        error_ = false;

        std::ifstream vertex_file;
        std::string vertex_absolute_path(vertex_path);
        error_ = error_ || !std::filesystem::exists(vertex_absolute_path);

        std::ifstream fragment_file;
        std::string fragment_absolute_path(fragment_path);
        error_ = error_ || !std::filesystem::exists(fragment_absolute_path);

        std::ifstream geometry_file;
        std::string geometry_absolute_path(geometry_path);
        bool geometry{geometry_path != ""};

        if(geometry)
          error_ = error_ || !std::filesystem::exists(geometry_absolute_path);

        // open files
        vertex_file.open(vertex_absolute_path);
        fragment_file.open(fragment_absolute_path);
        if(geometry){
          geometry_file.open(geometry_absolute_path);
          geometry = geometry && geometry_file.is_open();
          if(!geometry){
            error_ = true;
            error_log_ += "The geometry shader: " + std::string(geometry_absolute_path) +
                          " was not opened.\n----------\n";
          }
        }

        if(vertex_file.is_open() && fragment_file.is_open()){
          std::stringstream vertex_stream, fragment_stream, geometry_stream;

          // read file's buffer contents into streams
          vertex_stream << vertex_file.rdbuf();
          fragment_stream << fragment_file.rdbuf();
          if(geometry) geometry_stream << geometry_file.rdbuf();

          // close file handlers
          vertex_file.close();
          fragment_file.close();
          if(geometry) geometry_file.close();

          std::string vertex_text(vertex_stream.str());
          std::string fragment_text(fragment_stream.str());
          std::string geometry_text;
          if(geometry) geometry_text = geometry_stream.str();

          // convert stream into const char*
          const char *vertex_code{vertex_text.c_str()};
          const char *fragment_code{fragment_text.c_str()};
          const char *geometry_code{geometry_text.c_str()};

          // compile shaders
          GLint has_succed;
          char info_log[512];
          GLsizei info_size;

          // vertex shader
          GLuint vertex_shader{glCreateShader(GL_VERTEX_SHADER)};
          glShaderSource(vertex_shader, 1, &vertex_code, NULL);
          glCompileShader(vertex_shader);
          // check for shader compile errors
          glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &has_succed);
          if(has_succed == GL_FALSE){
            glGetShaderInfoLog(vertex_shader, 512, &info_size, info_log);
            error_log_ += "\n### Vertex shader compilation failed...\n\n" +
                          std::string(info_log, static_cast<std::size_t>(info_size))
                          + "\n----------\n";
            error_ = true;
          }

          // fragment Shader
          GLuint fragment_shader{glCreateShader(GL_FRAGMENT_SHADER)};
          glShaderSource(fragment_shader, 1, &fragment_code, NULL);
          glCompileShader(fragment_shader);
          // check for shader compile errors
          glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &has_succed);
          if(has_succed == GL_FALSE){
            glGetShaderInfoLog(fragment_shader, 512, &info_size, info_log);
            error_log_ += "\n### Fragment shader compilation failed...\n\n" +
                          std::string(info_log, static_cast<std::size_t>(info_size))
                          + "\n----------\n";
            error_ = true;
          }

          // Geometry Shader
          GLuint geometry_shader{0u};
          if(geometry){
            geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry_shader, 1, &geometry_code, NULL);
            glCompileShader(geometry_shader);
            // check for shader compile errors
            glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &has_succed);
            if(has_succed == GL_FALSE){
              glGetShaderInfoLog(geometry_shader, 512, &info_size, info_log);
              error_log_ += "\n### Geometry shader compilation failed...\n\n" +
                            std::string(info_log, static_cast<std::size_t>(info_size))
                            + "\n----------\n";
              error_ = true;
            }
          }

          // shader Program
          id_ = glCreateProgram();
          glAttachShader(id_, vertex_shader);
          glAttachShader(id_, fragment_shader);
          if(geometry) glAttachShader(id_, geometry_shader);
          glLinkProgram(id_);
          // check for linking errors
          glGetProgramiv(id_, GL_LINK_STATUS, &has_succed);
          if(has_succed == GL_FALSE){
            glGetProgramInfoLog(id_, 512, &info_size, info_log);
            error_log_ += "\n### Shader program linking failed...\n\n" +
                          std::string(info_log, static_cast<std::size_t>(info_size)) +
                          "\n----------\n";
            error_ = true;
          }
          glDetachShader(id_, vertex_shader);
          glDetachShader(id_, fragment_shader);

          glDeleteShader(vertex_shader);
          glDeleteShader(fragment_shader);

          if(geometry){
            glDetachShader(id_, geometry_shader);
            glDeleteShader(geometry_shader);
          }

          use();
        }else{
          if(!vertex_file.is_open())
            error_log_ += "The vertex shader: " + std::string(vertex_absolute_path) +
                          " was not opened.\n----------\n";
          if(!fragment_file.is_open())
            error_log_ += "The fragment shader: " + std::string(fragment_absolute_path) +
                          " was not opened.\n----------\n";
          error_ = true;
        }
        return id_ != 0;
      }else{
        error_log_ += "The shader was previously created.\n----------\n";

        return !(error_ = true);
      }
    }

    bool shader::delete_shader(){
      if(id_ == 0) return false;
      glDeleteProgram(id_);
      id_ = 0;
      return true;
    }

    bool shader::error() const{
      return error_;
    }

    const std::string &shader::error_log() const{
      return error_log_;
    }

    GLuint shader::id() const{
      return id_;
    }

    bool shader::operator()(const std::string &vertex_path,
                            const std::string &fragment_path,
                            const std::string &geometry_path){
      return create(vertex_path, fragment_path, geometry_path);
    }

    GLint shader::uniform_location(const std::string &name) const{
      return glGetUniformLocation(id_, name.c_str());
    }

    void shader::use() const{
      glUseProgram(id_);
    }

    // :::::::::::::::::::::::::::::::: Utility uniform functions :::::::::::::::::::::::::::::::

    void shader::set_value(const GLint uniform_location, const bool value) const {
      glUniform1i(uniform_location, static_cast<int>(value));
    }

    void shader::set_value(const GLint uniform_location, const int value) const {
      glUniform1i(uniform_location, value);
    }

    void shader::set_value(const GLint uniform_location, const GLuint value) const {
      glUniform1ui(uniform_location, value);
    }

    void shader::set_value(const GLint uniform_location, const float value) const {
      glUniform1f(uniform_location, value);
    }

    void shader::set_value(const GLint uniform_location, const float *value, const int size) const {
      switch(size){
        case 1:
          glUniform1fv(uniform_location, 1, value);
        break;
        case 2:
          glUniform2fv(uniform_location, 1, value);
        break;
        case 3:
          glUniform3fv(uniform_location, 1, value);
        break;
        case 4:
          glUniform4fv(uniform_location, 1, value);
        break;
      }
    }

    void shader::set_value(const GLint uniform_location, const float x, const float y) const {
      glUniform2f(uniform_location, x, y);
    }

    void shader::set_value(const GLint uniform_location,
                           const float x, const float y, const float z) const {
      glUniform3f(uniform_location, x, y, z);
    }

    void shader::set_value(const GLint uniform_location,
                           const float x, const float y, const float z, const float w) const {
      glUniform4f(uniform_location, x, y, z, w);
    }

    // :::::::::::::::::::::: Utility uniform functions using uniform names :::::::::::::::::::::

    void shader::set_value(const std::string &uniform_name, const bool value) const {
      glUniform1i(glGetUniformLocation(id_, uniform_name.c_str()), static_cast<int>(value));
    }

    void shader::set_value(const std::string &uniform_name, const int value) const {
      glUniform1i(glGetUniformLocation(id_, uniform_name.c_str()), value);
    }

    void shader::set_value(const std::string &uniform_name, const GLuint value) const {
      glUniform1ui(glGetUniformLocation(id_, uniform_name.c_str()), value);
    }

    void shader::set_value(const std::string &uniform_name, const float value) const {
      glUniform1f(glGetUniformLocation(id_, uniform_name.c_str()), value);
    }

    void shader::set_value(const std::string &uniform_name, const float *value, const int size) const {
      switch(size){
        case 1:
          glUniform1fv(glGetUniformLocation(id_, uniform_name.c_str()), 1, value);
        break;
        case 2:
          glUniform2fv(glGetUniformLocation(id_, uniform_name.c_str()), 1, value);
        break;
        case 3:
          glUniform3fv(glGetUniformLocation(id_, uniform_name.c_str()), 1, value);
        break;
        case 4:
          glUniform4fv(glGetUniformLocation(id_, uniform_name.c_str()), 1, value);
        break;
      }
    }

    void shader::set_value(const std::string &uniform_name,
                           const float x, const float y) const {
      glUniform2f(glGetUniformLocation(id_, uniform_name.c_str()), x, y);
    }

    void shader::set_value(const std::string &uniform_name,
                           const float x, const float y, const float z) const {
      glUniform3f(glGetUniformLocation(id_, uniform_name.c_str()), x, y, z);
    }

    void shader::set_value(const std::string &uniform_name,
                           const float x, const float y, const float z, const float w) const {
      glUniform4f(glGetUniformLocation(id_, uniform_name.c_str()), x, y, z, w);
    }

    // ::::::::::::::::::::: Utility uniform functions using algebraica lib :::::::::::::::::::::

#ifdef USING_ALGEBRAICA
    void shader::set_value(const std::string &uniform_name, const algebraica::vec2f &vector) const {
      glUniform2fv(glGetUniformLocation(id_, uniform_name.c_str()), 1, vector.data());
    }

    void shader::set_value(const std::string &uniform_name, const algebraica::vec3f &vector) const {
      glUniform3fv(glGetUniformLocation(id_, uniform_name.c_str()), 1, vector.data());
    }

    void shader::set_values(const std::string &uniform_name,
                            const algebraica::vec3f *pointer_to_vector_array,
                            const GLsizei vector_array_size) const {
      glUniform3fv(glGetUniformLocation(id_, uniform_name.c_str()),
                   vector_array_size, pointer_to_vector_array->data());
    }

    void shader::set_value(const std::string &uniform_name, const algebraica::vec4f &vector) const {
      glUniform4fv(glGetUniformLocation(id_, uniform_name.c_str()), 1, vector.data());
    }

    void shader::set_value(const std::string &uniform_name,
                           const algebraica::quaternionF &quaternion) const {
      glUniform4fv(glGetUniformLocation(id_, uniform_name.c_str()), 1, quaternion.data());
    }

    void shader::set_value(const std::string &uniform_name, const algebraica::mat3f &matrix) const {
      glUniformMatrix3fv(glGetUniformLocation(id_, uniform_name.c_str()),
                         1, GL_FALSE, matrix.data());
    }

    void shader::set_value(const std::string &uniform_name, const algebraica::mat4f &matrix) const {
      glUniformMatrix4fv(glGetUniformLocation(id_, uniform_name.c_str()), 1,
                         GL_FALSE, matrix.data());
    }
#endif
  } // namespace gl
} // namespace ramrod
