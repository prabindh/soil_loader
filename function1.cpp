//Code snippet to show using SOIL and context sharing 
// Blocking approach
// Refer to http://gpupowered.org/node/45
// prabindh@yahoo.com

#include "SOIL.h"

#include <thread> 

#define GLFW_INCLUDE_ES2 1

#include <GLFW/glfw3.h>

static int temptextureidhack = 0;

void SOIL_loader()

{
   glfwMakeContextCurrent((GLFWwindow*)PARENT_WINDOWHACK);

    SOIL_load_OGL_texture

        (

        "./img_test.png",

        SOIL_LOAD_AUTO,

        temptextureidhack,

        NULL

        );

}



int setup_texture_data()
{
    //Restore other GL attribs
    restore_attribs();

    glGenTextures(1, &textureID);

    temptextureidhack = textureID;

    std::thread textureloader(SOIL_loader);

    textureloader.join();

    glfwMakeContextCurrent((GLFWwindow*)PARENT_WINDOWHACK);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

    return 0;

}



