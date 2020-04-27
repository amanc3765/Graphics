
#include "opengl.h"


shaders shaderCode;


int main(void){

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err){
        cout<<"Error: "<<glewGetErrorString(err)<<endl;
    }

    //Set up vertex data and shaders
    init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //Render data
        glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void init(void){

     float vertices[2*NUM_VERTICES] = {
        -0.90, -0.90, // Triangle 1
         0.85, -0.90,
        -0.90,  0.85,
         0.90, -0.85, // Triangle 2
         0.90,  0.90,
        -0.85,  0.90
    };    


    unsigned int buffer;
    glGenBuffers(NUM_BUFFERS, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glEnableVertexAttribArray(0);
    
    loadShader("Shaders/vertex.glsl","Shaders/fragment.glsl");
    unsigned int program = createShader(shaderCode.vertex, shaderCode.fragment);
    glUseProgram(program);

}