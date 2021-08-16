#include "src/Engine.hpp"

// GAME_CONFIGS = GameConfigs::instance();

int main(int argc, char **argv) 
{
    Engine::start(argc, argv);
    return 0;
}

// #include <GL/glut.h>
// #include <math.h>
// #include <iostream>

// #define FPS 60
// #define TO_RADIANS 3.14/180.0

// //width and height of the window ( Aspect ratio 16:9 )
// const int width = 16*50;
// const int height = 9*50;

// float pitch = 0.0, yaw= 0.0;
// float camX=0.0,camZ=0.0;

// void display();
// void reshape(int w,int h);
// void timer(int);
// void passive_motion(int,int);
// void camera();
// void keyboard(unsigned char key,int x,int y);
// void keyboard_up(unsigned char key,int x,int y);

// struct Motion
// {
//     bool Forward,Backward,Left,Right;
// };

// Motion motion = {false,false,false,false};

// void init()
// {
//     glutSetCursor(GLUT_CURSOR_NONE);
//     glEnable(GL_DEPTH_TEST);
//     glDepthFunc(GL_LEQUAL);
//     glutWarpPointer(width/2,height/2);
//     glutFullScreen();
// }

// int main(int argc,char**argv)
// {
//     glutInit(&argc,argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//     glutInitWindowSize(width, height);
//     glutCreateWindow("Projectile Motion - 3D Simulation");

//     init();
//     glutDisplayFunc(display);
//     glutReshapeFunc(reshape);
//     glutPassiveMotionFunc(passive_motion);
//     glutTimerFunc(0,timer,0);    //more info about this is given below at definition of timer()
//     glutKeyboardFunc(keyboard);
//     glutKeyboardUpFunc(keyboard_up);

//     glutMainLoop();
//     return 0;
// }

// /* This function just draws the scene. I used Texture mapping to draw
//    a chessboard like surface. If this is too complicated for you ,
//    you can just use a simple quadrilateral */

// void draw()
// {
//     glEnable(GL_TEXTURE_2D);
//     GLuint texture;
//     glGenTextures(1,&texture);

//     unsigned char texture_data[2][2][4] =
//                     {
//                         0,0,0,255,  255,255,255,255,
//                         255,255,255,255,    0,0,0,255
//                     };

//     glBindTexture(GL_TEXTURE_2D,texture);
//     glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,2,2,0,GL_RGBA,GL_UNSIGNED_BYTE,texture_data);

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
//                     GL_NEAREST);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//                     GL_NEAREST);

//     glBegin(GL_QUADS);

//     glTexCoord2f(0.0,0.0);  glVertex3f(-50.0,-5.0,-50.0);
//     glTexCoord2f(25.0,0.0);  glVertex3f(50.0,-5.0,-50.0);
//     glTexCoord2f(25.0,25.0);  glVertex3f(50.0,-5.0,50.0);
//     glTexCoord2f(0.0,25.0);  glVertex3f(-50.0,-5.0,50.0);

//     glEnd();

//     glDisable(GL_TEXTURE_2D);
// }

// void display()
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glLoadIdentity();
//     camera();
//     glTranslatef(0,0,-10);
//     glColor3f(0.3,1,0.3);
//     glutSolidCube(2);
//     draw();

//     glutSwapBuffers();
// }

// void reshape(int w,int h)
// {
//     glViewport(0,0,w,h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(60,16.0/9.0,1,75);
//     glMatrixMode(GL_MODELVIEW);

// }


// /*this funtion is used to keep calling the display function periodically
//   at a rate of FPS times in one second. The constant FPS is defined above and
//   has the value of 60
// */
// void timer(int)
// {
//     glutPostRedisplay();
//     glutWarpPointer(width/2,height/2);
//     glutTimerFunc(1000/FPS,timer,0);
// }

// void passive_motion(int x,int y)
// {
//     /* two variables to store X and Y coordinates, as observed from the center
//       of the window
//     */
//     int devx,devy;
//     devx = (width/2)-x;
//     devy = (height/2)-y;

//     /* apply the changes to pitch and yaw*/
//     yaw+=(float)devx/10.0;
//     pitch+=(float)devy/10.0;
// }

// void camera()
// {

//     if(motion.Forward)
//     {
//         camX += cos((yaw+90)*TO_RADIANS)/5.0;
//         camZ -= sin((yaw+90)*TO_RADIANS)/5.0;
//     }
//     if(motion.Backward)
//     {
//         camX += cos((yaw+90+180)*TO_RADIANS)/5.0;
//         camZ -= sin((yaw+90+180)*TO_RADIANS)/5.0;
//     }
//     if(motion.Left)
//     {
//         camX += cos((yaw+90+90)*TO_RADIANS)/5.0;
//         camZ -= sin((yaw+90+90)*TO_RADIANS)/5.0;
//     }
//     if(motion.Right)
//     {
//         camX += cos((yaw+90-90)*TO_RADIANS)/5.0;
//         camZ -= sin((yaw+90-90)*TO_RADIANS)/5.0;
//     }

//     /*limit the values of pitch
//       between -60 and 70
//     */
//     if(pitch>=70)
//         pitch = 70;
//     if(pitch<=-60)
//         pitch=-60;

//     glRotatef(-pitch,1.0,0.0,0.0); // Along X axis
//     glRotatef(-yaw,0.0,1.0,0.0);    //Along Y axis
//     glTranslatef(-camX,0.0,-camZ);
// }

// void keyboard(unsigned char key,int x,int y)
// {
//     switch(key)
//     {
//     case 'W':
//     case 'w':
//         motion.Forward = true;
//         break;
//     case 'A':
//     case 'a':
//         motion.Left = true;
//         break;
//     case 'S':
//     case 's':
//         motion.Backward = true;
//         break;
//     case 'D':
//     case 'd':
//         motion.Right = true;
//         break;
//     }
// }
// void keyboard_up(unsigned char key,int x,int y)
// {
//     switch(key)
//     {
//     case 'W':
//     case 'w':
//         motion.Forward = false;
//         break;
//     case 'A':
//     case 'a':
//         motion.Left = false;
//         break;
//     case 'S':
//     case 's':
//         motion.Backward = false;
//         break;
//     case 'D':
//     case 'd':
//         motion.Right = false;
//         break;
//     }
// }