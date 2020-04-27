
#include "opengl.h"


extern shaders shaderCode;


void loadShader(string vPath, string fPath){

    ifstream vIn(vPath);
    ifstream fIn(fPath);    

    string line;
    while(getline(vIn,line)){        
        shaderCode.vertex += line + '\n'; 
    }

    while(getline(fIn,line)){        
        shaderCode.fragment += line + '\n'; 
    }

    cout<<shaderCode.vertex<<endl;
    cout<<shaderCode.fragment<<endl;

    return;
}


unsigned int createShader(string vShader,string fShader){

    unsigned int program = glCreateProgram();

    unsigned int vShaderObject = compileShader(GL_VERTEX_SHADER, vShader);
    unsigned int fShaderObject = compileShader(GL_FRAGMENT_SHADER, fShader);

    glAttachShader(program,vShaderObject);    
    glAttachShader(program,fShaderObject);    
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vShaderObject);
    glDeleteShader(fShaderObject);

    return program;
}  


static unsigned int compileShader(unsigned int type, string& source){
    
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);    
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if(result == GL_FALSE){

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);

        cout<<"Failed to compile"
        <<(type == GL_VERTEX_SHADER? "vertex": "fragment")<<endl;
        cout<<message<<endl;

        glDeleteShader(id);

        return 0;
    }

    return id;
}
