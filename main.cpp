  //
//  main.cpp
//  UserPerspectiveAR
//
//  Created by Jean-Marie Normand on 12/02/13.
//  Copyright (c) 2013 Centrale Innovation. All rights reserved.
//


// OpenGL/GLUT
#include <OPENGL/gl.h>
#include <GLUT/glut.h>

// Main include
#include "main.h"

// number of the camera used. usually 0 for internal
const int cameraId = 1;

// marker size (in meters)
const float markerSize = 0.105f;

// Initializing OpenGL/GLUt states
void initGL(int argc, char * argv[]) {
   
   // Setting window's initial position
   glutInitWindowPosition(0, 0);
   // Setting initial window's size: initialized with the size of the video
   glutInitWindowSize(widthFrame,heightFrame);
   
   // Setting up display mode
   glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
   // Creating window and setting its name
   g_hWindow = glutCreateWindow( "AruCo" );
   // setting up draw callback
   glutDisplayFunc( doWork );
   // Setting up idle callback
   glutIdleFunc( idle );
   // Setting up resize callback
   glutReshapeFunc( resize );
   // Setting up the mouse callback
   glutMouseFunc( mouse );
   // Setting up keyboard callback
   glutKeyboardFunc( keyboard );
   
   // Setting up clear color
   glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
   // and depth clear value
   glClearDepth( 1.0 );
   
   glShadeModel (GL_SMOOTH);
   glEnable(GL_NORMALIZE);
   
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
}

// Resize function
void resize(GLsizei iWidth, GLsizei iHeight) {
   // Calling ArUco resize
   arucoManager->resize(iWidth, iHeight);
   
   // not all sizes are allowed. OpenCV images have padding
   // at the end of each line in these that are not aligned to 4 bytes
   if (iWidth*3%4!=0) {
      iWidth+=iWidth*3%4;//resize to avoid padding
   }
   glutReshapeWindow(iWidth, iHeight);
   glutPostRedisplay();
}

// Mouse function
void mouse(int b,int s,int x,int y) {
   // nothing for now
}

// Keyboard function
void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case KEY_ESCAPE:
         exitFunction();
         exit(0);
         break;

      default:
         break;
	}
	
}

// Loop function
void doWork() {

   // Showing images
   imshow(windowNameCapture, curImg);
   
   // Calling ArUco draw function
   arucoManager->drawScene();
   
   // Swapping GLUT buffers
   glutSwapBuffers();
}

// Idle function
void idle() {
   
   // Clearing color and depth buffers
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   
   // Getting current frames
   cap >> curImg;
   
   // Calling ArUco idle
   arucoManager->idle(curImg);
    
   // Keyboard manager + waiting for key
   char retKey = cv::waitKey(1);
   if(retKey == KEY_ESCAPE){
      exitFunction();
      exit(EXIT_SUCCESS);
   }
  
   // Redisplay GLUT window
   glutPostRedisplay();
}


// Exit function
void exitFunction() {  
   
   // Destroy OpenCV window
   destroyWindow(windowNameCapture);
   
   // Release capture
   cap.release();
   
   // Deleting ArUco manager
   if(arucoManager) {
      delete(arucoManager);
      arucoManager = NULL;
   }
   
   // Deleting GLUT window
   if(g_hWindow) {
      glutDestroyWindow(g_hWindow);
   }
   
}

// Main 
int main(int argc, char * argv[])
{
   // OpenGL/GLUT Initialization
   glutInit(&argc, argv);
   
   // print a welcome message, and the OpenCV version
   cout << "Welcome to arucoMinimal, using OpenCV version " <<
           CV_VERSION << endl;
   
   cout << "Hot keys: " << endl <<
          "\tESC - quit the program" << endl;
   
   // Creating the ArUco object with camera parameters
   arucoManager = new ArUco("camera.yml", markerSize);
   std::cout<<"ArUco OK"<<std::endl;
   
   // Creating the OpenCV capture
   cap.open(cameraId);
   if(!cap.isOpened()) {
      cerr << "Erreur lors de l'initialisation de la capture de la camera !"<< endl;
      cerr << "Fermeture..." << endl;
      exit(EXIT_FAILURE);
   }
   else{
      // retrieving a first frame so that the display does not crash
      cap >> curImg;
   }
   
   // Getting width/height of the image
   widthFrame  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
   heightFrame = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
   std::cout<<"Frame width = "<<widthFrame<<std::endl;
   std::cout<<"Frame height = "<<heightFrame<<std::endl;
   
   // OpenCV window
   windowNameCapture = "Scene";
   cv::namedWindow(windowNameCapture, CV_WINDOW_AUTOSIZE);  
   
   // Exit function
   atexit(exitFunction);
   
   // OpenGL/GLUT Initialization
   initGL(argc, argv);
   
   // Starting GLUT main loop
   glutMainLoop();
   
   return 0;
}

