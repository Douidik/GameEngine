#include "EnginePCH.h"
#include "Shader.h"
#include "Util/Util.h"

void Shader::setUniform(const std::string &name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string &name, unsigned int value) {
    glUniform1ui(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string &name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string &name, double value) {
    glUniform1f(getUniformLocation(name), value);
}


void Shader::setUniform(const std::string &name, glm::vec2 value) {
    glUniform2f(getUniformLocation(name), value.x, value.y);
}

void Shader::setUniform(const std::string &name, glm::vec3 value) {
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string &name, glm::vec4 value) {
    glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const std::string &name, glm::mat4 value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const std::string &name, glm::mat3 value) {
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}


Shader::Shader(const std::string &fpVertex, const std::string &fpFragment) {
    mId = parseProgram(readShader({RESOURCE_PATH(fpVertex), RESOURCE_PATH(fpFragment)}));
}

std::tuple<std::string, std::string> Shader::readShader(std::tuple<std::string, std::string> filepaths) {
    std::ifstream streamVertex(std::get<0>(filepaths), std::ios::in),
            streamFragment(std::get<1>(filepaths), std::ios::in);

    if (streamVertex && streamFragment) {
        std::stringstream sstrVertex, sstrFragment;
        sstrVertex << streamVertex.rdbuf();
        sstrFragment << streamFragment.rdbuf();
        return {sstrVertex.str(), sstrFragment.str()};
    } else {
        std::string error =
                std::string("Failed to read ") +
                std::string(!streamVertex && !streamFragment ? "vertex and fragment " : !streamVertex ? "vertex "
                                                                                                      : "fragment ") +
                std::string("shader(s) files: ") +
                std::string(
                        !streamVertex && !streamFragment ? std::get<0>(filepaths) + "and " + std::get<0>(filepaths) :
                        !streamVertex ? std::get<0>(filepaths) :
                        std::get<1>(filepaths));

        std::cerr << error << std::endl;
        assert(0);

        return {"Cannot read Vertex shader file.", "Cannot read Fragment shader file."};
    }
}

GLuint Shader::parseProgram(std::tuple<std::string, std::string> sources) {
    GLuint idVertex = parseShader(std::get<0>(sources), ShaderType::Vertex);
    GLuint idFragment = parseShader(std::get<1>(sources), ShaderType::Fragment);

    GLuint idProgram = glCreateProgram();

    glAttachShader(idProgram, idVertex);
    glAttachShader(idProgram, idFragment);

    glLinkProgram(idProgram);

    int isLinked;
    glGetProgramiv(idProgram, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        char linkError[1024];
        int linkErrorLen;
        glGetProgramiv(idProgram, GL_INFO_LOG_LENGTH, &linkErrorLen);
        glGetProgramInfoLog(idProgram, linkErrorLen, nullptr, &linkError[0]);

        std::string errorMessage = "Failed to link program:\n";

        for (int i = 0; i < linkErrorLen; i++) {
            errorMessage += linkError[i];
        }

        std::cerr << errorMessage << std::endl;
        assert(0); // Program error
    }

    glDetachShader(idProgram, idVertex);
    glDetachShader(idProgram, idFragment);

    glDeleteShader(idVertex);
    glDeleteShader(idFragment);

    return idProgram;
}

GLuint Shader::parseShader(const std::string &source, ShaderType type) {
    GLuint id = glCreateShader(type);
    const char *source_cstr = source.c_str();
    glShaderSource(id, 1, &source_cstr, nullptr);
    glCompileShader(id);

    int isCompiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE) {
        char compileError[1024];
        int compileErrorLen;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &compileErrorLen);
        glGetShaderInfoLog(id, compileErrorLen, nullptr, &compileError[0]);

        std::string errorMessage =
                "Failed to compile " + std::string(type == ShaderType::Vertex ? "vertex " : "fragment ") +
                std::string("shader:\n");

        for (int i = 0; i < compileErrorLen; i++) {
            errorMessage += compileError[i];
        }

        std::cerr << errorMessage << std::endl;
        assert(0); // Shader error
    }

    return id;

}

int Shader::getLayoutLocation(const std::string &name) {
    if (mLayoutLocationCache.find(name) != mLayoutLocationCache.end()) {
        return mLayoutLocationCache[name];
    }

    GLuint location = glGetAttribLocation(mId, name.c_str());

    if (location == -1) {
        std::string errorMessage = "Failed to find attrib location: " + name;
        std::cerr << errorMessage << std::endl;
    }

    mLayoutLocationCache[name] = location;

    //assert(location != -1);
    return location;
}


