/*
** ULAVAL PROJECT, 2025
** IFT3100H25_TP1_E10 [WSL : Ubuntu]
** File description:
** TessellationShader
*/

#ifndef TESSELATIONSHADER_HPP_
#define TESSELATIONSHADER_HPP_

#include "ofShader.h"

class TessellationShader : public ofShader {
public:
    bool loadTessellation(const of::filesystem::path &tcsName, const of::filesystem::path &tesName)
    {
        return setupShaderFromFile(GL_TESS_CONTROL_SHADER, tcsName) &&
               setupShaderFromFile(GL_TESS_EVALUATION_SHADER, tesName) && linkProgram();
    }
};

#endif /* !TESSELATIONSHADER_HPP_ */
