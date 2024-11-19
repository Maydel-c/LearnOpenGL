//
//  Shader.hpp
//  GLFWExample
//
//  Created by Abhinav on 19/11/24.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // the program ID
    unsigned int ID;
    
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    
    // use/activate the shader
    void use();
    
    // utility uniform functions
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
};

#endif /* Shader_hpp */
