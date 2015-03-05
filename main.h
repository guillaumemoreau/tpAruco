//
//  main.h
//  UserPerspectiveAR
//
//  Created by Jean-Marie Normand on 01/03/13.
//  Copyright (c) 2013 Centrale Innovation. All rights reserved.
//

#ifndef UserPerspectiveAR_main_h
#define UserPerspectiveAR_main_h

#include <iostream>

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>

// OpenGL/GLUT
#ifdef __APPLE__
   #include <OPENGL/gl.h>
   #include <GLUT/glut.h>
#else
   #include <stdlib.h>
   #include <GL/glut.h>
#endif

// OpenCV
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// ArUco
#include "ArUco-OpenGL.h"

// Default wdth and height of the video
#define DEFAULT_VIDEO_WIDTH   800
#define DEFAULT_VIDEO_HEIGHT  600

// Defining escape key
#define KEY_ESCAPE 27
#define DEFAULT_RESIZE_RATIO 0.7

// Namespaces
using namespace std;
using namespace cv;

// OpenCV stuff: cameras, etc.
int            cameraID;
VideoCapture   cap;

// Names of the OpenCV windows
string         windowNameCapture;


// Width/Height of the image
int            widthFrame;
int            heightFrame;

// GLUT attributes
GLint          g_hWindow;

// ArUco object
ArUco          *arucoManager;

// Ratio of view resizing
double         resizeRatio;

// Keeping current capture image
cv::Mat        curImg;

// Test again
cv::Mat        debugImg;

// Forward declarations

// GLUT functions

// Initializing OpenGL
void initGL(int argc, char * argv[]);

// Loop function
void doWork();

// Idle function
void idle();

// Resize function
void resize(GLsizei iWidth, GLsizei iHeight);

// Mouse function
void mouse(int b,int s,int x,int y);

// Keyboard function
void keyboard(unsigned char key, int x, int y);

// Exit function
void exitFunction();

#endif
