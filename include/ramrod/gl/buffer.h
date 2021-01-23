#ifndef RAMROD_GL_BUFFER_H
#define RAMROD_GL_BUFFER_H

#include "glad/glad.h"

namespace ramrod {
  namespace gl {
    class buffer
    {
    public:
      /**
       * @brief Constructs this buffer object
       *
       * @param create Indicates if the `GL_VERTEX_ARRAY_OBJECT` should be generated inmediately
       */
      buffer(const bool create = false);
      /**
       * @brief Frees the memory of its `GL_VERTEX_ARRAY_OBJECT`, `GL_ARRAY_BUFFER`,
       *        and `GL_ELEMENT_BUFFER`
       */
      ~buffer();
      /**
       * @brief Allocating a `GL_ARRAY_BUFFER`
       *
       * Creates and initializes a buffer object's data store.
       *
       * @param data Specifies a pointer to data that will be copied into the data store
       *             for initialization, or `nullptr` if no data is to be copied.
       * @param size_in_bytes Specifies the size in bytes of the buffer object's new data store.
       * @param ussage Specifies the expected usage pattern of the data store. The symbolic
       *               constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY,
       *               GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW,
       *               GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
       *
       * @returns `false` if `generate_array()` has not been called
       */
      bool allocate_array(const GLvoid *data, const GLsizei size_in_bytes,
                          const GLenum ussage = GL_STATIC_DRAW);
      /**
       * @brief Allocating an `GL_ELEMENT_ARRAY_BUFFER`
       *
       * Creates and initializes a buffer object's data store.
       *
       * @param data Specifies a pointer to data that will be copied into the data store
       *             for initialization, or `nullptr` if no data is to be copied.
       * @param size_in_bytes Specifies the size in bytes of the buffer object's new data store.
       * @param ussage Specifies the expected usage pattern of the data store. The symbolic
       *               constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY,
       *               GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW,
       *               GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
       *
       * @returns `false` if `generate_element()` has not been called
       */
      bool allocate_element(const GLvoid *data, const GLsizei size_in_bytes,
                            const GLenum ussage = GL_STATIC_DRAW);
      /**
       * @brief Allocating a section of a GL_ARRAY_BUFFER
       *
       * Updates a subset of a buffer object's data store
       *
       * @param data Specifies a pointer to the new data that will be copied into the data store.
       * @param size_in_bytes Specifies the size in bytes of the data store region being replaced.
       * @param offset Specifies the offset into the buffer object's data store where data
       *               replacement will begin, measured in bytes.
       *
       * @returns `false` if `generate_array()` has not been called
       */
      bool allocate_section_array(const GLvoid *data, const GLsizei size_in_bytes,
                                  const GLintptr offset = 0);
      /**
       * @brief Allocating a section of a GL_ELEMENT_ARRAY_BUFFER
       *
       * Updates a subset of a buffer object's data store
       *
       * @param data Specifies a pointer to the new data that will be copied into the data store.
       * @param offset Specifies the offset into the buffer object's data store where data
       *               replacement will begin, measured in bytes.
       * @param size_in_bytes Specifies the size in bytes of the data store region being replaced.
       *
       * @returns `false` if `generate_element()` has not been called
       */
      bool allocate_section_element(const GLvoid *data, const GLsizei size_in_bytes,
                                    const GLintptr offset = 0);
      /**
       * @brief Define an array of generic vertex attribute data
       *
       * @param index Specifies the index of the generic vertex attribute to be modified.
       * @param size Specifies the number of components per generic vertex attribute.
       *             Must be 1, 2, 3, 4. Additionally, the symbolic constant `GL_BGRA` is
       *             accepted by **attributte_buffer**. The initial value is 4.
       * @param offset Specifies a offset of the first component of the first generic vertex
       *               attribute in the array in the data store of the buffer currently bound
       *               to the `GL_ARRAY_BUFFER` target. The initial value is 0.
       * @param stride Specifies the byte offset between consecutive generic vertex attributes.
       *               If `stride` is 0, the generic vertex attributes are understood to be
       *               tightly packed in the array. The initial value is 0.
       * @param type Specifies the data type of each component in the array. The symbolic
       *             constants `GL_BYTE`, `GL_UNSIGNED_BYTE`, `GL_SHORT`, `GL_UNSIGNED_SHORT`,
       *             `GL_INT`, and `GL_UNSIGNED_INT` are accepted by **attributte_buffer**.
       *             Additionally `GL_HALF_FLOAT`, `GL_FLOAT`, `GL_DOUBLE`, `GL_FIXED`,
       *             `GL_INT_2_10_10_10_REV`, `GL_UNSIGNED_INT_2_10_10_10_REV` and
       *             `GL_UNSIGNED_INT_10F_11F_11F_REV` are accepted by **attributte_buffer**.
       *             `GL_DOUBLE` is also accepted by **glVertexAttribLPointer** and is the
       *             only token accepted by the type parameter for that function. The initial
       *             value is `GL_FLOAT`.
       * @param normalized For **attributte_buffer**, specifies whether fixed-point data
       *                   values should be normalized (`GL_TRUE`) or converted directly as
       *                   fixed-point values (`GL_FALSE`) when they are accessed.
       */
      void attributte_buffer(const GLuint index, const GLint size, const GLintptr offset,
                             const GLsizei stride, const GLenum type = GL_FLOAT,
                             const GLboolean normalized = GL_FALSE);
      /**
       * @brief Binds this buffer's `GL_ARRAY_BUFFER` and `GL_ELEMENT_ARRAY_BUFFER` if there is one
       */
      void buffer_bind();
      /**
       * @brief Releases this buffer's `GL_ARRAY_BUFFER` and `GL_ELEMENT_ARRAY_BUFFER` if there is one
       */
      void buffer_release();
      /**
       * @brief Executes a `glDrawArrays
       *
       * If the `count` value is left as 0 then, it will be calculated using the `size_in_bytes`
       * introduced in the last call to `allocate_array()` and it will be divides by the
       * `stride` of the last call to `attibute_buffer()` minus the `first` value.
       *
       * @param mode  Specifies what kind of primitives to render. Symbolic constants
       *              `GL_POINTS`, `GL_LINE_STRIP`, `GL_LINE_LOOP`, `GL_LINES`,
       *              `GL_LINE_STRIP_ADJACENCY`, `GL_LINES_ADJACENCY`, `GL_TRIANGLE_STRIP`,
       *              `GL_TRIANGLE_FAN`, `GL_TRIANGLES`, `GL_TRIANGLE_STRIP_ADJACENCY`,
       *              `GL_TRIANGLES_ADJACENCY` and `GL_PATCHES` are accepted.
       * @param first Specifies the starting index in the enabled arrays.
       * @param count Specifies the number of indices to be rendered. Leave it 0 to draw all
       */
      void draw(const GLenum mode, const GLint first = 0, const GLsizei count = 0);
      /**
       * @brief Executes a `glDrawElements`
       *
       * If the `count` value is left as 0 then, it will be calculated using the `size_in_bytes`
       * introduced in the last call to `allocate_element()` and it will be divides by the
       * size in bytes of the selected `type` minus the `offset` value.
       *
       * @param mode  Specifies what kind of primitives to render. Symbolic constants
       *              `GL_POINTS`, `GL_LINE_STRIP`, `GL_LINE_LOOP`, `GL_LINES`,
       *              `GL_LINE_STRIP_ADJACENCY`, `GL_LINES_ADJACENCY`, `GL_TRIANGLE_STRIP`,
       *              `GL_TRIANGLE_FAN`, `GL_TRIANGLES`, `GL_TRIANGLE_STRIP_ADJACENCY`,
       *              `GL_TRIANGLES_ADJACENCY` and `GL_PATCHES` are accepted.
       * @param count Specifies the number of indices to be rendered. Leave it 0 to draw all
       * @param type Specifies the type of the values in indices. Must be one of
       *             `GL_UNSIGNED_BYTE`, `GL_UNSIGNED_SHORT`, or `GL_UNSIGNED_INT`.
       * @param offset Specifies the index's location where it should start
       */
      void draw_elements(const GLenum mode, GLsizei count = 0,
                         const GLenum type = GL_UNSIGNED_BYTE, const GLintptr offset = 0);
      /**
       * @brief Executes a `glDrawArraysInstanced`
       *
       * @param mode  Specifies what kind of primitives to render. Symbolic constants
       *              `GL_POINTS`, `GL_LINE_STRIP`, `GL_LINE_LOOP`, `GL_LINES`,
       *              `GL_LINE_STRIP_ADJACENCY`, `GL_LINES_ADJACENCY`, `GL_TRIANGLE_STRIP`,
       *              `GL_TRIANGLE_FAN`, `GL_TRIANGLES`, `GL_TRIANGLE_STRIP_ADJACENCY`,
       *              `GL_TRIANGLES_ADJACENCY` and `GL_PATCHES` are accepted.
       * @param first Specifies the starting index in the enabled arrays.
       * @param count Specifies the number of indices to be rendered.
       * @param instance_count Specifies the number of instances of the specified range of
       *                       indices to be rendered.
       */
      void draw_instanced(const GLenum mode, const GLint first, const GLsizei count,
                          const GLsizei instance_count);
      /**
       * @brief Executes a `glDrawElementsInstanced`
       *
       * @param mode  Specifies what kind of primitives to render. Symbolic constants
       *              `GL_POINTS`, `GL_LINE_STRIP`, `GL_LINE_LOOP`, `GL_LINES`,
       *              `GL_LINE_STRIP_ADJACENCY`, `GL_LINES_ADJACENCY`, `GL_TRIANGLE_STRIP`,
       *              `GL_TRIANGLE_FAN`, `GL_TRIANGLES`, `GL_TRIANGLE_STRIP_ADJACENCY`,
       *              `GL_TRIANGLES_ADJACENCY` and `GL_PATCHES` are accepted.
       * @param count Specifies the number of indices to be rendered. Leave it 0 to draw all
       * @param type Specifies the type of the values in indices. Must be one of
       *             `GL_UNSIGNED_BYTE`, `GL_UNSIGNED_SHORT`, or `GL_UNSIGNED_INT`.
       * @param offset Specifies the index's location where it should start
       * @param instance_count Specifies the number of instances of the specified range
       *                       of indices to be rendered.
       */
      void draw_instanced_elements(const GLenum mode, GLsizei count,
                                   const GLenum type, const GLintptr offset,
                                   const GLsizei instance_count);
      /**
       * @brief Deletes this buffer's `GL_ARRAY_BUFFER`, `GL_ELEMENT_ARRAY_BUFFER` and
       *        `GL_VERTEX_BUFFER`
       *
       * @return `false` if array and buffers were not generated
       */
      bool delete_buffer();
      /**
       * @brief Disables a generic vertex attribute array
       *
       * @param attribute_id Specifies the index of the generic vertex attribute to
       *                     be enabled or disabled.
       */
      void disable(const GLuint attribute_id);
      /**
       * @brief Modify the rate at which generic vertex attributes advance during
       *        instanced rendering
       *
       * @param attribute_id Specify the index of the generic vertex attribute.
       * @param divisor Specify the number of instances that will pass between updates of
       *        the generic attribute at slot _index_.
       */
      void divisor(const GLuint attribute_id, const GLuint divisor);
      /**
       * @brief Enables a generic vertex attribute array
       * @param attribute_id Specifies the index of the generic vertex attribute to
       *                     be enabled or disabled.
       */
      void enable(const GLuint attribute_id);
      /**
       * @brief Generates a `GL_ARRAY_BUFFER` buffer
       *
       * @return `false` if it was not possible to generate the array buffer
       */
      bool generate_array();
      /**
       * @brief Generates a `GL_ELEMENT_ARRAY_BUFFER` buffer
       *
       * @return `false` if it was not possible to generate the element array
       */
      bool generate_element();
      /**
       * @brief Generates a `GL_VERTEX_ARRAY_OBJECT` buffer
       *
       * @return `false` if it was not possible to generate the vertex array
       */
      bool generate_vertex();
      /**
       * @brief Getting the ID of the `GL_ARRAY_BUFFER`
       *
       * @returns `GL_ARRAY_BUFFER`'s ID
       */
      GLuint id_array();
      /**
       * @brief Getting the ID of the `GL_ELEMENT_ARRAY_BUFFER`
       *
       * @returns `GL_ELEMENT_ARRAY_BUFFER`'s ID
       */
      GLuint id_element();
      /**
       * @brief Getting the ID of the `GL_VERTEX_ARRAY_OBJECT`
       *
       * @returns `GL_VERTEX_ARRAY_OBJECT`'s ID
       */
      GLuint id_vertex();
      /**
       * @brief Getting the size in bytes of the `GL_ARRAY_BUFFER`
       *
       * This function additionally binds the  `GL_ARRAY_BUFFER`
       *
       * @returns Size in bytes of `GL_ARRAY_BUFFER`
       */
      GLint size_array();
      /**
       * @brief Getting the size in bytes of the `GL_ELEMENT_ARRAY_BUFFER`
       *
       * This function additionally binds the  `GL_ELEMENT_ARRAY_BUFFER`
       *
       * @returns Size in bytes of `GL_ELEMENT_ARRAY_BUFFER`
       */
      GLint size_element();
      /**
       * @brief Binds this `GL_VERTEX_ARRAY_OBJECT`
       *
       * @return `false` if `generate_vertex()` has not been yet called
       */
      void vertex_bind();
      /**
       * Releases this `GL_VERTEX_ARRAY_OBJECT`
       */
      void vertex_release();

    private:
      GLuint array_buffer_, element_buffer_, vertex_array_;
      GLsizei array_stride_, array_size_, element_size_;
    };
  }
}

#endif // RAMROD_GL_BUFFER_H
