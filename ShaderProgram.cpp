#include "ShaderProgram.h"

std::vector<ShaderProgram*> ShaderProgram::shaders;

void ShaderProgram::loadShaders(const char* vertexFile, const char* fragmentFile) {
    programID = shaderLoader.loadShader(vertexFile, fragmentFile);
}

ShaderProgram::ShaderProgram() : programID(0), currentShader(nullptr) {}

void ShaderProgram::init() {
    programID = glCreateProgram();
}

void ShaderProgram::attachShader(const Shader& shader) {
    glAttachShader(programID, shader.getShaderID());
}

void ShaderProgram::link() {
    glLinkProgram(programID);
    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(programID, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void ShaderProgram::use() const {
    glUseProgram(programID);
}

GLuint ShaderProgram::getProgramID() const {
    return programID;
}

void ShaderProgram::setViewMatrix(const glm::mat4& viewMatrix) {
    use();
    setMatrix("viewMatrix", viewMatrix);
}

void ShaderProgram::setProjectionMatrix(const glm::mat4& projectionMatrix) {
    use();
    setMatrix("projectionMatrix", projectionMatrix);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programID);
}

void ShaderProgram::cleanup() {
    for (ShaderProgram* shaderProgram : shaders) {
        delete shaderProgram;
    }
    shaders.clear();
}

void ShaderProgram::addShader(ShaderProgram* shaderProgram) {
    shaders.push_back(shaderProgram);
}

int ShaderProgram::getShadersCount() {
    return static_cast<int>(shaders.size());
}

ShaderProgram* ShaderProgram::getShaderByIndex(int index) {
    if (index >= 0 && static_cast<size_t>(index) < shaders.size()) {
        return shaders[index];
    }
    return nullptr;
}

void ShaderProgram::checkCompilation(GLuint shaderID) {
    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> infoLog(length);
        glGetShaderInfoLog(shaderID, length, nullptr, infoLog.data());
        std::cerr << "ERROR: Shader compilation failed: " << infoLog.data() << std::endl;
    }
}

GLuint ShaderProgram::getShaderID() const {
    return programID;
}

void ShaderProgram::setMatrix(const std::string& name, const glm::mat4& matrix) {
    GLint loc = glGetUniformLocation(programID, name.c_str());
    if (loc != -1) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
    }
}

void ShaderProgram::updateLights(const std::vector<Light*>& lights, const glm::vec3& viewPos) {
    use();
    int numLights = static_cast<int>(lights.size());
    setInt("numLights", numLights);

    for (int i = 0; i < numLights; ++i) {
        std::string base = "lights[" + std::to_string(i) + "]";

        setInt(base + ".type", lights[i]->type);
        setVec3(base + ".position", lights[i]->position);
        setVec3(base + ".color", lights[i]->color);
        setFloat(base + ".intensity", lights[i]->intensity);

        setVec3(base + ".direction", lights[i]->direction);
        setFloat(base + ".constant", lights[i]->constant);
        setFloat(base + ".linear", lights[i]->linear);
        setFloat(base + ".quadratic", lights[i]->quadratic);

        setFloat(base + ".innerCutoff", lights[i]->innerCutoff);
        setFloat(base + ".outerCutoff", lights[i]->outerCutoff);
    }

    setVec3("viewPos", viewPos);
}
