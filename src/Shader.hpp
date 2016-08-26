#ifndef SHADER_HPP
#define SHADER_HPP


#include "MathTypes.hpp"

#include <string>
#include <GL/glew.h>


class Shader {
public:
    Shader(const std::string& vsFileName, const std::string& fsFileName);
    ~Shader(void);

    Shader(const Shader&) = delete;
    Shader(Shader&&);
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&&);

    operator GLuint() const;

    GLuint getId(void) const;
    void use(void);
    void use(const Matrix4Glf& mvp, const Vector3Glf& color = {0.0f, 0.0f, 0.0f});

private:
    GLuint _programId;
};


#endif // SHADER_HPP
