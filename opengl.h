
#include <iostream>
#include <fstream>
#include <cstring>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

#define NUM_BUFFERS 1
#define NUM_VERTICES 6


typedef struct{
    string vertex; 
    string fragment;
}shaders;


void init(void);
void loadShader(string vpath, string fpath);
unsigned int createShader(string vshader,string fshader);
static unsigned int compileShader(unsigned int type, string& source);
