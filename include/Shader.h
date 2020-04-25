#ifndef SHADER_H_
#define SHADER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Class for operations related to Shaders */
class Shader {
public:
    Shader(const char *vertexSourceName, const char *fragmentSourceName);
    void useShader();
    /* void setUniformInt(); */
    /* void setUniformFloat(); */
    void setUniformMat4f(const char *uniform, glm::mat4 val);

private:
    unsigned int shaderProgram;
    std::string readFile(const char *filename);
    int checkCompileError(unsigned int shader);
    int checkLinkError();
};


#endif // SHADER_H_
