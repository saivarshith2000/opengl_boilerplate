#include <Shader.h>

/* Constructor for Shader Class. It reads the shader source files, compiles
 * the shaders, creates and links the shader program. It any error occurs,
 * program exits abruptly with an error message
 */
Shader::Shader(const char *vertexSourceName, const char *fragmentSourceName)
{
    /* read sources */
    std::string vertexSourceStr = readFile(vertexSourceName);
    assert(vertexSourceStr != "");
    const char *vertexSource = vertexSourceStr.c_str();
    std::string fragmentSourceStr = readFile(fragmentSourceName);
    assert(fragmentSourceStr != "");
    const char *fragmentSource = fragmentSourceStr.c_str();

    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    assert(checkCompileError(vertexShader) != 0);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    assert(checkCompileError(fragmentShader) != 0);

    /* create and link shader program */
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    assert(checkLinkError() != 0);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return ;
}

void Shader::useShader()
{
    glUseProgram(shaderProgram);
    return ;
}

/* Set the uniform value in shader for type glm::mat4 */
void Shader::setUniformMat4f(const char *uniform, glm::mat4 val)
{
    int uniformLocation = glGetUniformLocation(shaderProgram, uniform);
    useShader();
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &val[0][0]);
}

/* Reads entire file and returns a string containing the file contents */
std::string Shader::readFile(const char *filename)
{
    std::string str = "";
    std::ifstream f(filename);
    if(f) {
        std::ostringstream ss;
        ss << f.rdbuf();
        str = ss.str();
    }
    return str;
}

/* Checks the compilation status of a shader */
int Shader::checkCompileError(unsigned int shader)
{
    int status = 0;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "SHADER COMPILATION ERROR\n" << infoLog << std::endl;
        return 0;
    }
    return 1;
}

/* Checks the linking status of a shader program */
int Shader::checkLinkError()
{
    int status = 0;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "SHADER PROGRAM LINK ERROR\n" << infoLog << std::endl;
        return 0;
    }
    return 1;
}

