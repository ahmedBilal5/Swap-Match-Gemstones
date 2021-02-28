//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================
/*NOTE: EXCEPT FOR THE THIRD AND FOURTH ROW, SWAPPING IN THE GAME OCCURS PERFECTLY*/ 
#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include "Gemboard.cpp"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt

using namespace std;
Gemboard Gboard(8,8);
// seed the the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void setSpaceForGems(){
        const int screenWidth = 1020, screenLength = 840;
        int spaceWidth, spaceLength,Xremainder,Yremainder;
        Xremainder = screenWidth%(Gboard.getYlines());
        spaceWidth = screenWidth/(Gboard.getYlines());
        Yremainder = (screenLength-100)%(Gboard.getXlines());
        spaceLength = (screenLength-100)/(Gboard.getXlines());
        Gboard.setY_Arr(Xremainder/2+50, spaceWidth);
        Gboard.setX_Arr(Yremainder/2+20, spaceLength);
        Gboard.setGemCoord();
        for(int i = 0; i < Gboard.getXlines(); i++)
                DrawLine( (Gboard.getY_Arr())[0],(Gboard.getX_Arr())[i],(Gboard.getY_Arr())[Gboard.getYlines()-1],(Gboard.getX_Arr())[i]  , 10 , colors[MISTY_ROSE] );
        for(int i = 0; i < Gboard.getYlines(); i++)
                DrawLine( (Gboard.getY_Arr())[i],(Gboard.getX_Arr())[0],(Gboard.getY_Arr())[i],(Gboard.getX_Arr())[Gboard.getXlines()-1]  , 10 , colors[MISTY_ROSE] );
}

void fillingBoardWithGems(){
       for(int i = 0; i < Gboard.getRows(); i++){
                for(int j = 0; j < Gboard.getCols(); j++){
                        switch((Gboard.getBoard()[i][j]).getType()){
                                
                                case 0:
                                         //0 is type triangle
                                        DrawTriangle(Gboard.getGemCoord()[i][j].getX()-28 , Gboard.getGemCoord()[i][j].getY()-22, Gboard.getGemCoord()[i][j].getX()+28 , Gboard.getGemCoord()[i][j].getY()-22 , Gboard.getGemCoord()[i][j].getX() ,Gboard.getGemCoord()[i][j].getY()+24 , colors[CRIMSON]);
                                        break;
                                case 1:
                                        //1 is type circle
                                        DrawCircle(Gboard.getGemCoord()[i][j].getX(),Gboard.getGemCoord()[i][j].getY(),25,colors[ORANGE]);
                                        break;
                                case 2:
                                        //2 is type square
                                        DrawSquare(Gboard.getGemCoord()[i][j].getX()-23,Gboard.getGemCoord()[i][j].getY()-25, 50, colors[SALMON]);
                                        break;
                                case 3:
                                        //3 is type Rounded rectangle No.1
                                        DrawRoundRect(Gboard.getGemCoord()[i][j].getX()-22,Gboard.getGemCoord()[i][j].getY()-30,45,65,colors[TURQUOISE],20);
                                        break;
                                case 4:
                                        //4 is rounded rectangle No.2
                                        DrawRoundRect(Gboard.getGemCoord()[i][j].getX()-30,Gboard.getGemCoord()[i][j].getY()-24,60,50,colors[GREEN],20);
                                        break;
                                case 5:
                                        //5 is rounded rectangle No.3
                                         DrawRoundRect(Gboard.getGemCoord()[i][j].getX()-36,Gboard.getGemCoord()[i][j].getY()-25,70,55,colors[ORCHID],40);
                                         break;
                        }
             }
        }
        for(int i = 0; i < Gboard.getRows(); i++){
                for(int j = 0; j < Gboard.getCols(); j++)
                         DrawCircle(Gboard.getGemCoord()[i][j].getX(),Gboard.getGemCoord()[i][j].getY(),1,colors[YELLOW]);
        }
}
                                     
void InitialChainRemover(){
         Gboard.chainChecker();
         Gboard.chainRemover();            
}              
        
/*
 * Main Canvas drawing function.
 * */
 
Center& SpecifyingCentre(int x, int y){
        int specXpos = 0, specYpos = 0;
       
       for(int i = 0; i < Gboard.getCols(); i++){
                 if(x > Gboard.getY_Arr()[i] && x < Gboard.getY_Arr()[i+1])
                                specXpos = i;
       }
       for(int i = 0; i < Gboard.getRows(); i++){
                 if(x > Gboard.getX_Arr()[i] && x < Gboard.getX_Arr()[i+1])
                                specYpos = i;
       }
       return Gboard.getGemCoord()[specXpos][specYpos];
}

int RowIndex(int x){
        int specXpos = 0;
         for(int i = 0; i < Gboard.getCols(); i++){
                 if(x > Gboard.getY_Arr()[i] && x < Gboard.getY_Arr()[i+1])
                                specXpos = i;
       }
       return specXpos;
}
int ColIndex(int y){
        int specYpos = 0;
         for(int i = 0; i < Gboard.getRows(); i++){
                 if(y > Gboard.getX_Arr()[i] && y < Gboard.getX_Arr()[i+1])
                                specYpos = i;
       }
       return specYpos;
}
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	//cout << Gboard.getGemCoord()[0][0].getX() << endl;
	cout << "The X: " << (SpecifyingCentre(x,y)).getX() << endl;
	cout << "Row Index: " << RowIndex(x) << endl << "Col index: " << ColIndex(x) << endl;
	glutPostRedisplay();
	//timer();
}
string convertedScore(){  
        string scorestring;
        stringstream s1;
        s1 << Gboard.getScore();
        s1>>scorestring;
        return scorestring;
}
string convertedLevel(){
          stringstream s2;
          string levelstring;  
         
          s2 << Gboard.getGameLevel().getLevel(); 
          s2>>levelstring;
          return levelstring;        
}
string convertedPts(){
          stringstream s3;
          string ptsstring;  
         
          s3 << Gboard.getGameLevel().getPts(); 
          s3>>ptsstring;
          return ptsstring;        
}
string convertedMoves(){
        stringstream s4;
        string movesString;
        s4<< Gboard.getGameLevel().getMovesAllowed();
        s4>> movesString;
        return movesString;
}

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
        
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
             
                       InitialChainRemover();
	               setSpaceForGems();
	               fillingBoardWithGems();
	               DrawString( 50, 750, "SCORE: ", colors[MISTY_ROSE]);
	               DrawString( 140, 750, convertedScore(), colors[ORANGE]);
	               DrawString( 200, 750, "LEVEL: ", colors[MISTY_ROSE]);
	               DrawString( 290, 750, convertedLevel(), colors[AQUA]);
	               DrawString( 200, 710, "MOVES LEFT: ", colors[MISTY_ROSE]);
	               DrawString( 375, 710, convertedMoves(), colors[AQUA]);
                       DrawString( 350, 750, "PASSING SCORE: ", colors[MISTY_ROSE]);
	               DrawString( 550, 750, convertedPts(), colors[AQUA]);
	               DrawString( 610, 780, "PRESS 'H' FOR A HINT!", colors[RED]);
	               DrawString( 50, 710, "LIVES: ", colors[MISTY_ROSE]);
	               if(Gboard.getMenu().getHintOption()==true)
	                       DrawString( 610, 750,Gboard.getHint(), colors[RED]);
	               for(int i = 0; i < Gboard.getLives(); i++)
	                       DrawCircle(140+(i*18),720,8,colors[RED]);
	         
          
	 
	//Fire Gun
	/*DrawSquare( 400 , 20 ,40,colors[RED]); 
	DrawSquare( 300, 50, 50, colors[YELLOW]);
	DrawSquare( 300, 100, 50, colors[AQUA]);
	*///DrawSquare( 300, 150, 50, colors[SALMON]);
	/*DrawSquare( 300, 200, 50, colors[YELLOW_GREEN]);
	DrawSquare( 300, 250, 50, colors[ORCHID]);
	DrawSquare( 300, 300, 50, colors[SEA_GREEN]);
	DrawSquare( 300, 350, 50, colors[TURQUOISE]);
	DrawSquare( 300, 400, 50, colors[FIREBRICK]);
	DrawSquare( 300, 450, 50, colors[CRIMSON]);
	Torus2d(150,500,45,50,25,50,3,colors[GREEN]);
	//Mushroom
	DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	
	*///Spider
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[CRIMSON] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
        /*

	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	*///DrawCircle(100,500,50,colors[ORANGE]);/*
	//DrawCircle(50,670,10,colors[RED]);
	//DrawCircle(70,670,10,colors[RED]);
	//DrawCircle(90,670,10,colors[RED]);
	//DrawRoundRect(500,200,45,65,colors[TURQUOISE],20);
	//DrawRoundRect(100,200,60,50,colors[GREEN],20);	
	//DrawRoundRect(200,90,70,55,colors[ORCHID],40);
	//DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);
	
	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	if( key == 'h' || key == 'H'){
	        Gboard.allowHint(true);
	        Gboard.hintUsed();
	        //Gboard.matchFinder();
	}
	if (key == '1')
	        Gboard.getMenu().setMenuControl(1);
	if(key=='2')
	         Gboard.getMenu().setMenuControl(2);
	if(key=='3')
	        Gboard.getMenu().setMenuControl(3);
	if(key=='4')
	        exit(1);
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */


/*This function is called (automatically) whenever your mouse moveges witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */

void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	//glutPostRedisplay();
}
void Timer(int m) {

	// implement your functionality here
        //glutDisplayFunc(GameDisplay);
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(10.0, Timer, 0);
}
/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{ Gboard.matchAllower(x ,y);
			cout << "SCORE IS: " << Gboard.getScore() << endl;
			Gboard.moveToNextLevel();
			Gboard.allowHint(false);
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}

void boardInfo(){
        
        for(int i = 0; i < Gboard.getRows(); i++){
                cout <<"WE ARE IN THE " << i << "ST ROW:\n";
                for(int j = 0; j < Gboard.getCols(); j++)
                       cout << "COLLUMN " << j << ": " << Gboard.getBoard()[i][j].getType() << endl;
         }
}               
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
        //Gemboard G;
        //G.randombunch();
	int width = 1020, height = 840; // i have set my window size to be 800 x 600
        //boardInfo();
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Project"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
        //InitialChainRemover();
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(10.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
