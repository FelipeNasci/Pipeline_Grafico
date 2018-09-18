#ifndef CONTROLLER_H
#define CONTROLLER_H

void keyboard(unsigned char key, int x, int y){

GLfloat rX = 0, rY = 0, rZ = 0;
GLfloat tX = 0, tY = 0, tZ = 0;

    switch(key){

        //Rotacoes eixo x
        case 'x':   rX += 0.1;
            break;
        case 'X':   rX -= 0.1;
            break;

        //Rotacoes eixo y
        case 'y':   rY += 0.1;
            break;
        case 'Y':   rY -= 0.1;
            break;

        //Rotacoes eixo z
        case 'z':   rZ += 0.1;
            break;
        case 'Z':   rZ -= 0.1;
            break;

        //Translacao do obj
        case 'j':   tX += 0.1;
            break;
        case 'J':   tX -= 0.1;
            break;

        case 'l' :  tY += 0.1;
            break;
        case 'L' :  tY -= 0.1;
            break;

        case 'k' :  tZ += 0.1;
            break;
        case 'K' :  tZ -= 0.1;
            break;


    }

}

void mouse(){}

#endif // CONTROLLER_H
