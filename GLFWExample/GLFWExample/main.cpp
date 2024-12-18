#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_s.h"

/*
// vertex shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"layout (location=1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
    "gl_Position = vec4(aPos, 1);\n"
    "ourColor = aColor;\n" // specify a color output to the fragment shader
"}\0";

// fragment shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
    "FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";
*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{

    // Initializing GLFW version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
    // Initializing GLFW window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Initializing GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    
//===============================================================
    
    Shader ourShader("./3.3.shader.vs", "./3.3.shader.fs"); // set edit scheme > options > current directory to your directory
    
    float vertices[] = {
       // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
   };
    
    
    
//===============================================================
    /*
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // Checking if shader compilation successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }
    
    // 1. Write a fragment shader
    // 2. Compile it
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    // Checking if shader compilation successful
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }
    
    // Linking both vertex and fragment shaders in a shader program. Then Delete the shaders as now we only need the shader program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // Checking if shader programs compiles correctly
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<<std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // defining the vertices - preparing data for vertex shader
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.f, 0.f,
        0.5f, -0.5f, 0.0f, 0.f, 1.f, 0.f,
        0.0f, 0.5f, 0.0f, 0.f, 0.f, 1.f
    };
    */
    
    // VBOs and VAOs manage that memory
    unsigned int VBO, VAO/*, EBO*/;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // fill a VBO, configure vertex attribute pointers and store it all in a VAO.
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // Specify what the input data means by specifying the vertex attributes. input data can contain any form of data and we need to explicitly tell openGL what that data means
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    /*
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    */
    
    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        // read esc keypress and close the window
        processInput(window);
        
        // clear screen with a color on every frame
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Drawing a triangle
        /*
        glUseProgram(shaderProgram);
         */
        ourShader.use();
        
        /*
        float timeValue = glfwGetTime();
        float greenValue = (std::sin(timeValue) / 2.f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        */
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
//      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // get pixel data from back buffer to the front buffer (display)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // Delete VAOs and VBOs once purpose is served
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
//   glDeleteBuffers(1, &EBO);
     /*
     glDeleteProgram(shaderProgram);
     */
    
    
    // clean/delete all of GLFW's resources when loop ends
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


