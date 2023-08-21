#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#define PI 3.1415927

#define WINDOW_TITLE "Practical Exercise 5B"

/* ASSIGNMENT ONLY NEED TO DO tx, ty and ry only */

float tx = 0, tz = 0, tSpeed = 1;	//translate for model along the z-axis
bool isOrtho = true;		//is orthographic view?
float ONear = -20.0, OFar = 20.0;	//Ortho near and far
float PNear = 4.0, PFar = 21.0;	//Perspective near and far
float ptx = 0, pty = 0, ptSpeed = 1.0;	//translate for projection
float pry = 0, prSpeed = 1;	//rotate y for projection

//Optimus Prime colour 
double optOrangeColor[3] = { 0.847 ,0.129 ,0.129 }; //D92121
double optRedColor[3] = { 0.691 , 0.0705 , 0.149 }; //B1126
double optlightGrey[3] = { 0.82,0.82,0.82 }; //D3D3D3
double optGrey[3] = { 0.656,0.662,0.675 }; //A8A9AD
double optBlue[3] = { 0,0.06,0.66 }; //4682BF
double optlightBColor[3] = { 0.274, 0.509, 0.749 }; //4682BF
double optLightRed[3] = { 0.847, 0.13, 0.13 };
double optDarkGrey[3] = { 0.41, 0.41, 0.41 };

float leftHandAngle = 0;
float headAngle = 0;
float rightHandAngle = 0;
float leftRobotLeg = 0;
float rightRobotLeg = 0;
float rightHandSideway = 0;
float leftHandSideway = 0;

boolean walk = false;
boolean returnMovement = false;
boolean shoot = false;
double shootAngle = -9;
double shootScale = 1;
boolean gun = false;

float x = 0;
float y = 0;
float z = 0;


//Finger Rotation (All together rotate)
float longFingerAngle = 0;
float shortFingerAngle = 0;

//Right Finger (Rotate Individually)
float longRightFinger1Angle = 0;
float longRightFinger2Angle = 0;
float longRightFinger3Angle = 0;
float longRightFinger4Angle = 0;

float shortRightFinger1Angle = 0;
float shortRightFinger2Angle = 0;
float shortRightFinger3Angle = 0;
float shortRightFinger4Angle = 0;

//Left Finger (Rotate Individually)
float longLeftFinger1Angle = 0;
float longLeftFinger2Angle = 0;
float longLeftFinger3Angle = 0;
float longLeftFinger4Angle = 0;

float shortLeftFinger1Angle = 0;
float shortLeftFinger2Angle = 0;
float shortLeftFinger3Angle = 0;
float shortLeftFinger4Angle = 0;


float rightArmAngle = 0;
float rightArmIndi = 0;

float leftArmAngle = 0;
float leftArmIndiAngle = 0;

float rArmX = 0;
float lArmX = 0;

boolean fingerClosed = false;

//move the robot
float moveZRobot = 0;

//use to spin the robot
float moveYRobot = 0;


//Texture Code ============================
int changeTexture = 1;

BITMAP BMP; //The BITMAP structure defines the properties of a bitmap texture.
HBITMAP hBMP = NULL;  // A handle to a bitmap. 


//Lightning 
float amb[3] = { 0 , 0 , 0 }; //red color ambient light 
float posA[3] = { 0 ,6 , 0.0 }; //amb light position (0,6,0) 
float posD[3] = { 0 ,6 , 0.0 }; //amb light position (0,6,0) 
float diff[3] = { 0,0,0 }; //difuse light 
float ambM[3] = { 0 ,0.0,1.0 }; //red color amb material 
float difM[3] = { 0,0,1 }; //red color diff
bool isLightOn = false; //is light on? 


int keyboardState = 1;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == VK_F1) {
			keyboardState = 1;
		}
		else if (wParam == VK_F2) {
			keyboardState = 2;
		}
		else if (wParam == VK_F3) {
			keyboardState = 3;
		}
		else if (wParam == VK_F4) {
			keyboardState = 4;
		}
		else if (wParam == 0x31 && keyboardState == 1) {	//long left finger 1 rotate up
			longLeftFinger1Angle += 3;
			x = 0.1;

			if (longLeftFinger1Angle > 50) {
				longLeftFinger1Angle = 50;
			}
		}
		else if (wParam == 0x32 && keyboardState == 1) {	//long left finger 2 rotate up
			longLeftFinger2Angle += 3;
			x = 0.1;

			if (longLeftFinger2Angle > 50) {
				longLeftFinger2Angle = 50;
			}
		}
		else if (wParam == 0x33 && keyboardState == 1) {	//long left finger 3 rotate up
			longLeftFinger3Angle += 3;
			x = 0.1;

			if (longLeftFinger3Angle > 50) {
				longLeftFinger3Angle = 50;
			}
		}
		else if (wParam == 0x34 && keyboardState == 1) {	//long left finger 4 rotate up
			longLeftFinger4Angle += 3;
			x = 0.1;

			if (longLeftFinger4Angle > 50) {
				longLeftFinger4Angle = 50;
			}
		}
		else if (wParam == 0x35 && keyboardState == 1) {	//long right finger 1 rotate up
			longRightFinger1Angle += 3;
			x = 0.1;

			if (longRightFinger1Angle > 50) {
				longRightFinger1Angle = 50;
			}
		}
		else if (wParam == 0x36 && keyboardState == 1) {	//long right finger 2 rotate up
			longRightFinger2Angle += 3;
			x = 0.1;

			if (longRightFinger2Angle > 50) {
				longRightFinger2Angle = 50;
			}
		}
		else if (wParam == 0x37 && keyboardState == 1) {	//long right finger 3 rotate up
			longRightFinger3Angle += 3;
			x = 0.1;

			if (longRightFinger3Angle > 50) {
				longRightFinger3Angle = 50;
			}
		}
		else if (wParam == 0x38 && keyboardState == 1) {	//long right finger 4 rotate up
			longRightFinger4Angle += 3;
			x = 0.1;

			if (longRightFinger4Angle > 50) {
				longRightFinger4Angle = 50;
			}
		}



		else if (wParam == 'Q' && keyboardState == 1) {	//long left finger 1 rotate down
			longLeftFinger1Angle -= 3;
			x = 0.1;

			if (longLeftFinger1Angle <= 0) {
				longLeftFinger1Angle = 0;
			}
		}
		else if (wParam == 'W' && keyboardState == 1) {	//long left finger 2 rotate down
			longLeftFinger2Angle -= 3;
			x = 0.1;

			if (longLeftFinger2Angle <= 0) {
				longLeftFinger2Angle = 0;
			}
		}
		else if (wParam == 'E' && keyboardState == 1) {	//long left finger 3 rotate down
			longLeftFinger3Angle -= 3;
			x = 0.1;

			if (longLeftFinger3Angle <= 0) {
				longLeftFinger3Angle = 0;
			}
		}
		else if (wParam == 'R' && keyboardState == 1) {	//long left finger 4 rotate down
			longLeftFinger4Angle -= 3;
			x = 0.1;

			if (longLeftFinger4Angle <= 0) {
				longLeftFinger4Angle = 0;
			}
		}
		else if (wParam == 'T' && keyboardState == 1) {	//long right finger 1 rotate down
			longRightFinger1Angle -= 3;
			x = 0.1;

			if (longRightFinger1Angle <= 0) {
				longRightFinger1Angle = 0;
			}
		}
		else if (wParam == 'Y' && keyboardState == 1) {	//long right finger 2 rotate down
			longRightFinger2Angle -= 3;
			x = 0.1;

			if (longRightFinger2Angle <= 0) {
				longRightFinger2Angle = 0;
			}
		}
		else if (wParam == 'U' && keyboardState == 1) {	//long right finger 3 rotate down
			longRightFinger3Angle -= 3;
			x = 0.1;

			if (longRightFinger3Angle <= 0) {
				longRightFinger3Angle = 0;
			}
		}
		else if (wParam == 'I' && keyboardState == 1) {	//long right finger 4 rotate down
			longRightFinger4Angle -= 3;
			x = 0.1;

			if (longRightFinger4Angle <= 0) {
				longRightFinger4Angle = 0;
			}
		}
		else if (wParam == 'A' && keyboardState == 1) {	//short left finger 1 rotate up
			shortLeftFinger1Angle += 3;
			x = 0.1;

			if (shortLeftFinger1Angle > 30) {
				shortLeftFinger1Angle = 30;
			}
		}
		else if (wParam == 'S' && keyboardState == 1) {	//short left finger 2 rotate up
			shortLeftFinger2Angle += 3;
			x = 0.1;

			if (shortLeftFinger2Angle > 30) {
				shortLeftFinger2Angle = 30;
			}
		}
		else if (wParam == 'D' && keyboardState == 1) {	//short left finger 3 rotate up
			shortLeftFinger3Angle += 3;
			x = 0.1;

			if (shortLeftFinger3Angle > 30) {
				shortLeftFinger3Angle = 30;
			}
		}
		else if (wParam == 'F' && keyboardState == 1) {	//short left finger 4 rotate up
			shortLeftFinger4Angle += 3;
			x = 0.1;

			if (shortLeftFinger4Angle > 30) {
				shortLeftFinger4Angle = 30;
			}
		}
		else if (wParam == 'G' && keyboardState == 1) {	//short right finger 1 rotate up
			shortRightFinger1Angle += 3;
			x = 0.1;

			if (shortRightFinger1Angle > 30) {
				shortRightFinger1Angle = 30;
			}
		}
		else if (wParam == 'H' && keyboardState == 1) {	//short right finger 2 rotate up
			shortRightFinger2Angle += 3;
			x = 0.1;

			if (shortRightFinger2Angle > 30) {
				shortRightFinger2Angle = 30;
			}
		}
		else if (wParam == 'J' && keyboardState == 1) {	//short right finger 3 rotate up
			shortRightFinger3Angle += 3;
			x = 0.1;

			if (shortRightFinger3Angle > 30) {
				shortRightFinger3Angle = 30;
			}
		}
		else if (wParam == 'K' && keyboardState == 1) {	//short right finger 4 rotate up
			shortRightFinger4Angle += 3;
			x = 0.1;

			if (shortRightFinger4Angle > 30) {
				shortRightFinger4Angle = 30;
			}
		}
		else if (wParam == 'Z' && keyboardState == 1) {	//short left finger 1 rotate down
			shortLeftFinger1Angle -= 3;
			x = 0.1;

			if (shortLeftFinger1Angle <= 0) {
				shortLeftFinger1Angle = 0;
			}
		}
		else if (wParam == 'X' && keyboardState == 1) {	//short left finger 2 rotate down
			shortLeftFinger2Angle -= 3;
			x = 0.1;

			if (shortLeftFinger2Angle <= 0) {
				shortLeftFinger2Angle = 0;
			}
		}
		else if (wParam == 'C' && keyboardState == 1) {	//short left finger 3 rotate down
			shortLeftFinger3Angle -= 3;
			x = 0.1;

			if (shortLeftFinger3Angle <= 0) {
				shortLeftFinger3Angle = 0;
			}
		}
		else if (wParam == 'V' && keyboardState == 1) {	//short left finger 4 rotate down
			shortLeftFinger4Angle -= 3;
			x = 0.1;

			if (shortLeftFinger4Angle <= 0) {
				shortLeftFinger4Angle = 0;
			}
		}
		else if (wParam == 'B' && keyboardState == 1) {	//short right finger 1 rotate down
			shortRightFinger1Angle -= 3;
			x = 0.1;

			if (shortRightFinger1Angle <= 0) {
				shortRightFinger1Angle = 0;
			}
		}
		else if (wParam == 'N' && keyboardState == 1) {	//short right finger 2 rotate down
			shortRightFinger2Angle -= 3;
			x = 0.1;

			if (shortRightFinger2Angle <= 0) {
				shortRightFinger2Angle = 0;
			}
		}
		else if (wParam == 'M' && keyboardState == 1) {	//short right finger 3 rotate down
			shortRightFinger3Angle -= 3;
			x = 0.1;

			if (shortRightFinger3Angle <= 0) {
				shortRightFinger3Angle = 0;
			}
		}
		else if (wParam == 'L' && keyboardState == 1) {	//short right finger 4 rotate down
			shortRightFinger4Angle -= 3;
			x = 0.1;

			if (shortRightFinger4Angle <= 0) {
				shortRightFinger4Angle = 0;
			}
		}
		else if (wParam == VK_LEFT && keyboardState == 1) {	//turn camera left
			pry += prSpeed;
		}
		else if (wParam == VK_RIGHT && keyboardState == 1) {	//turn camera right
			pry -= prSpeed;
		}
		else if (wParam == VK_UP && keyboardState == 1) {
			if (isOrtho) {
				if (tz < OFar) {
					tz += tSpeed;
				}
			}
			else {
				if (tz < PFar) {
					tz += tSpeed;
				}
			}
		}
		else if (wParam == VK_DOWN && keyboardState == 1) {
			if (isOrtho) {
				if (tz > ONear) {
					tz -= tSpeed;
				}
			}
			else {
				if (tz > PNear) {
					tz -= tSpeed;
				}
			}
		}
		else if (wParam == VK_SPACE && keyboardState == 1) {
			leftHandAngle = 0;
			rightHandAngle = 0;
			leftArmAngle = 0;
			rightArmAngle = 0;
			leftHandSideway = 0;
			rightHandSideway = 0;
			headAngle = 0;
			leftRobotLeg = 0;
			rightRobotLeg = 0;

			longFingerAngle = 0;
			shortFingerAngle = 0;

			longRightFinger1Angle = 0;
			longRightFinger2Angle = 0;
			longRightFinger3Angle = 0;
			longRightFinger4Angle = 0;

			shortRightFinger1Angle = 0;
			shortRightFinger2Angle = 0;
			shortRightFinger3Angle = 0;
			shortRightFinger4Angle = 0;

			longLeftFinger1Angle = 0;
			longLeftFinger2Angle = 0;
			longLeftFinger3Angle = 0;
			longLeftFinger4Angle = 0;

			shortLeftFinger1Angle = 0;
			shortLeftFinger2Angle = 0;
			shortLeftFinger3Angle = 0;
			shortLeftFinger4Angle = 0;

		}
		else if (wParam == VK_LEFT && keyboardState == 4) {
			tx -= tSpeed;
		}
		else if (wParam == VK_RIGHT && keyboardState == 4) {
			tx += tSpeed;
		}
		else if (wParam == 'A' && keyboardState == 4) {
			ptx -= ptSpeed;
		}
		else if (wParam == 'D' && keyboardState == 4) {
			ptx += ptSpeed;
		}

		else if (wParam == 'O' && keyboardState == 1) {
			isOrtho = true;
			tz = 0;
		}
		else if (wParam == 'P' && keyboardState == 1) {
			isOrtho = false;
			tz = 4.0;
		}
		else if (wParam == 'C' && keyboardState == 2) { //Rotate both hands up (Sideways)
			leftHandSideway -= 3;
			rightHandSideway -= 3;
			x = 0.1;

			if (leftHandSideway < -90 && rightHandSideway < -90) {
				leftHandSideway = -90;
				rightHandSideway = -90;
			}
		}
		else if (wParam == 'V' && keyboardState == 2) {  //Rotate both hands down (Sideways)
			leftHandSideway += 3;
			rightHandSideway += 3;
			x = 0.1;

			if (leftHandSideway >= 0 && rightHandSideway > 0) {
				leftHandSideway = 0;
				rightHandSideway = 0;
			}
		}
		else if (wParam == 'B' && keyboardState == 2) { //Rotate both hands up (Front)
			leftHandAngle += 3;
			rightHandAngle -= 3;
			z = 0.1;

			if (leftHandAngle > 90 && rightHandAngle < -90) {
				leftHandAngle = 90;
				rightHandAngle = -90;
			}
		}
		else if (wParam == 'N' && keyboardState == 2) {  //Rotate both hands down (Back)
			leftHandAngle -= 3;
			rightHandAngle += 3;
			z = 0.1;

			if (leftHandAngle <= 0 && rightHandAngle >= 0) {
				leftHandAngle = 0;
				rightHandAngle = 0;
			}
		}
		else if (wParam == 'Z' && keyboardState == 2) {
			//move left head 
			headAngle -= 3;
			y = 0.1;
		}
		else if (wParam == 'X' && keyboardState == 2) {
			//move right head 
			headAngle += 3;
			y = 0.1;
		}
		else if (wParam == 'E' && keyboardState == 2) {	//Right hand rotate up (Front)
			//rightHandAngle
			rightHandAngle -= 3;
			z = 0.1;

			if (rightHandAngle <= -90) {
				rightHandAngle = -90;
			}
		}

		else if (wParam == 'M' && keyboardState == 2) {	//Right hand rotate down
			//rightHandAngle 
			rightHandAngle += 3;
			z = 0.1;

			if (rightHandAngle >= 0) {
				rightHandAngle = 0;
			}
		}


		else if (wParam == 'R' && keyboardState == 2) {	//Left hand rotate up (Front)
			//leftHandAngle
			leftHandAngle -= 3;
			z = 0.1;

			if (leftHandAngle <= 0) {
				leftHandAngle = 0;
			}
		}

		else if (wParam == 'T' && keyboardState == 2) {	//Left hand rotate down
			//leftHandAngle 
			leftHandAngle += 3;
			z = 0.1;

			if (leftHandAngle >= 90) {
				leftHandAngle = 90;
			}
		}


		else if (wParam == 'Y' && keyboardState == 2) { //Rotate left hands up (Sideways)
			leftHandSideway -= 3;
			x = 0.1;

			if (leftHandSideway < -90) {
				leftHandSideway = -90;
			}
		}
		else if (wParam == 'U' && keyboardState == 2) {  //Rotate left hands down (Sideways)
			leftHandSideway += 3;
			x = 0.1;

			if (leftHandSideway > 0) {
				leftHandSideway = 0;
			}
		}

		else if (wParam == 'I' && keyboardState == 2) { //Rotate right hands up (Sideways)
			rightHandSideway -= 3;
			x = 0.1;

			if (rightHandSideway < -90) {
				rightHandSideway = -90;
			}
		}
		else if (wParam == 'O' && keyboardState == 2) {  //Rotate right hands down (Sideways)
			rightHandSideway += 3;
			x = 0.1;

			if (rightHandSideway > 0) {
				rightHandSideway = 0;
			}
		}
		else if (wParam == 'J' && keyboardState == 2) {	//Left leg lift up
			//left leg angle
			leftRobotLeg -= 3;
			x = 0.1;

			if (leftRobotLeg <= -90) {
				leftRobotLeg = -90;
			}
		}
		else if (wParam == 'K' && keyboardState == 2) {	//Left leg lift down
			//left leg angle
			leftRobotLeg += 3;
			x = 0.1;

			if (leftRobotLeg >= 90) {
				leftRobotLeg = 90;
			}
		}
		else if (wParam == 'G' && keyboardState == 2) {	//Both leg lift up
			//left leg angle
			leftRobotLeg -= 3;
			rightRobotLeg -= 3;
			x = 0.1;

			if (leftRobotLeg <= -90 && rightRobotLeg <= -90) {
				leftRobotLeg = -90;
				rightRobotLeg = -90;
			}
		}
		else if (wParam == 'H' && keyboardState == 2) {	//Both leg lift down
			//left leg angle
			leftRobotLeg += 3;
			rightRobotLeg += 3;
			x = 0.1;

			if (leftRobotLeg >= 90 && rightRobotLeg >= 90) {
				leftRobotLeg = 90;
				rightRobotLeg = 90;
			}
		}
		else if (wParam == 'S' && keyboardState == 2) {
			//right leg angle down
			rightRobotLeg -= 3;
			x = 0.1;

			if (rightRobotLeg <= -90) {
				rightRobotLeg = -90;
			}
		}
		else if (wParam == 'D' && keyboardState == 2) {

			//right leg angle up
			rightRobotLeg += 3;
			x = 0.1;

			if (rightRobotLeg >= 90) {
				rightRobotLeg = 90;
			}
		}
		else if (wParam == 'B' && keyboardState == 4) {
			if (walk == false) {
				//control walk
				walk = true;
				z = 0.1;
				x = 0.1;
				//set all leg to 0 first (Reset to normal position)
				leftHandAngle = 0;
				rightHandAngle = 0;
				leftRobotLeg = 0;
				rightRobotLeg = 0;
			}
			else if (walk) {
				walk = false;
				leftHandAngle = 0;
				rightHandAngle = 0;
				leftRobotLeg = 0;
				rightRobotLeg = 0;
			}
		}
		else if (wParam == 'P' && keyboardState == 2) {
			//shoot cone
			shoot = true;

		}
		else if (wParam == 'L' && keyboardState == 2) {

			if (gun == false) {
				gun = true;
			}
			else {
				gun = false;
			}
		}
		else if (wParam == 'S' && keyboardState == 3) {
			shortFingerAngle += 3;
			x = 0.1;

			if (shortFingerAngle > 30) {
				shortFingerAngle = 30;
			}
		}

		else if (wParam == 'V' && keyboardState == 3) {
			longFingerAngle += 3;
			x = 0.1;

			if (longFingerAngle > 50) {
				longFingerAngle = 50;
			}
		}
		else if (wParam == 'H' && keyboardState == 3) {
			//move behind the whole robot
			moveZRobot -= 1;
		}
		else if (wParam == 'X' && keyboardState == 3) {

			moveZRobot += 1;
		}
		else if (wParam == 'L' && keyboardState == 3) {
			moveYRobot += 1;
		}
		else if (wParam == 'R' && keyboardState == 3) {
			moveYRobot -= 1;
		}
		else if (wParam == 'F' && keyboardState == 3) {	//Both lower arm rotate up (Front)
			rightArmAngle -= 3;
			leftArmAngle += 3;
			x = 0.1;

			if (rightArmAngle <= -90 && leftArmAngle >= 90) {
				rightArmAngle = -90;
				leftArmAngle = 90;
			}
		}
		else if (wParam == 'M' && keyboardState == 3) {	//Both lower arm rotate down
			rightArmAngle += 3;
			leftArmAngle -= 3;
			x = 0.1;

			if (rightArmAngle >= 0 && leftArmAngle <= 0) {
				rightArmAngle = 0;
				leftArmAngle = 0;
			}
		}

		else if (wParam == 'E' && keyboardState == 3) {	//Lower left arm rotate up (Front)
			leftArmAngle += 3;
			x = 0.1;

			if (leftArmAngle >= 90) {
				leftArmAngle = 90;
			}
		}
		else if (wParam == 'A' && keyboardState == 3) {	//Lower left arm rotate down
			leftArmAngle -= 3;
			x = 0.1;

			if (leftArmAngle <= 0) {
				leftArmAngle = 0;
			}
		}

		else if (wParam == 'Q' && keyboardState == 3) {	//Lower right arm rotate up (Front)
			rightArmAngle -= 3;
			x = 0.1;
			if (rightArmAngle <= -90) {
				rightArmAngle = -90;
			}
		}
		else if (wParam == 'W' && keyboardState == 3) {	//Lower right arm rotate down
			rightArmAngle += 3;
			x = 0.1;

			if (rightArmAngle >= 0) {
				rightArmAngle = 0;
			}
		}
		else if (wParam == 'B' && keyboardState == 3) {
			//finger closed 
			if (fingerClosed == false) {
				//Reset first to 0 
				longFingerAngle = 0;
				shortFingerAngle = 0;
				fingerClosed = true;

				x = 0.1;
				longFingerAngle += 45;
				shortFingerAngle += 60;
			}
			else if (fingerClosed) {
				fingerClosed = false;

				longFingerAngle = 0;
				shortFingerAngle = 0;
			}

		}
		else if (wParam == 'T' && keyboardState == 4) { // change texture
			if (changeTexture == 8) {
				changeTexture = 1;
			}
			else {
				changeTexture++;
			}
		}
		else if (wParam == VK_SPACE && keyboardState == 4) {
			isLightOn = !isLightOn;
		}
		else if (wParam == 'C' && keyboardState == 4) {
			//move right side light
			if (posD[0] < 20) {
				if (isLightOn) {
					posD[0] += 1;
				}
			}
		}
		else if (wParam == 'Z' && keyboardState == 4) {
			//move left side light
			if (posD[0] > -20) {
				if (isLightOn) {
					posD[0] -= 1;
				}
			}
		}
		else if (wParam == 'S' && keyboardState == 4) {
			//Move down the light 
			if (posD[1] > -20) {
				if (isLightOn) {
					posD[1] -= 1;
				}
			}
		}
		else if (wParam == 'W' && keyboardState == 4) {
			//Move up the light 
			if (posD[1] < 20) {
				if (isLightOn) {
					posD[1] += 1;
				}
			}
		}
		else if (wParam == 'E' && keyboardState == 4) {
			//move near lgiht
			if (posD[2] < 20) {
				if (isLightOn) {
					posD[2] += 1;
				}
			}
		}
		else if (wParam == 'Q' && keyboardState == 4) {
			//move far light
			if (posD[2] > -20) {
				if (isLightOn) {
					posD[2] -= 1;
				}
			}
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void drawSphere(double r) {
	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluSphere(sphere, r, 30, 30);
	gluDeleteQuadric(sphere); //must use deleteQuadric to prevent slowing down or crash
}

void drawSphereWithoutGLU()
{

	GLfloat x, y, z, sliceA, stackA;
	GLfloat radius = 0.5;
	int sliceNo = 30, stackNo = 30;
	for (sliceA = 0.0; sliceA < PI;/* <-- change this from 2 * PI to PI will make it half sphere*/ sliceA += PI / sliceNo)
	{
		glBegin(GL_LINE_STRIP);
		for (stackA = 0.0; stackA < PI;/* <-- change this from 2 * PI to PI will make it half sphere*/ stackA += PI / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}

void projection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();							//to reset projection matrix

	glTranslatef(ptx, pty, 0.0);		//translate for projection matrix
	glRotatef(pry, 0, 1, 0.0);
	if (isOrtho) {
		glOrtho(-20.0, 20.0, -20.0, 20.0, ONear, OFar);  //left right bottom top near far (ORTHOVIEW)
	}
	else {
		gluPerspective(20, -1.0, -1, 4);		//(fovy, aspect, near, far);
		glFrustum(-20.0, 20.0, -20.0, 20.0, 4, PFar);  //(xmin, xmax, ymin, ymax, -zmin, -zmax); ** The -zmin is 4.0 because the drawSphere(3.0), the sphere is 3.0. **
	}			//Pnear must be same with the Far 
	//glOrtho(-8.0, 8.0, -6.0, 6.0, -8.0, 8.0);  //This resolution make the sphere nicer not stretch
}

void drawCircle(float cx, float cy, float r, int num_segments) {
	glBegin(GL_TRIANGLE_FAN);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

void drawCylinder(double baseRadius, double topRadius, double height) {
	GLUquadricObj* cylinder = NULL;

	//glRotatef(0.01, 1.0, 1.0, 1.0);
	cylinder = gluNewQuadric();
	//drawstyle by default is glu fill 
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, baseRadius, topRadius, height, 20, 20);
	gluDeleteQuadric(cylinder);

	double x = 0, y = 0, x2 = 0, y2 = 0, noOfTriangle = 0;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);

	for (float angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTriangle) {
		x2 = x + 0.2 * cos(angle);
		y2 = y + 0.2 * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();

	glPushMatrix();
	//Top Circle
	drawCircle(0, 0, baseRadius, 360);

	//btm circle
	glTranslatef(0, 0, height);
	drawCircle(0, 0, topRadius, 360);
	glPopMatrix();
}



void drawCustomQuads(double length, double width, double height) {
	glBegin(GL_QUADS);
	//GL_QUADS

	//Bottom
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);// A
	glTexCoord2f(1, 1);
	glVertex3f(0, length, 0);// B
	glTexCoord2f(1, 0);
	glVertex3f(width, length, 0);// C
	glTexCoord2f(0, 0);
	glVertex3f(width, 0, 0);// D

	//RIGHT
	glTexCoord2f(0, 1);
	glVertex3f(width, 0, 0);// D
	glTexCoord2f(1, 1);
	glVertex3f(width, 0, height);// L
	glTexCoord2f(1, 0);
	glVertex3f(width, length, height);// K
	glTexCoord2f(0, 0);
	glVertex3f(width, length, 0);// C

	//BEHIND 
	glTexCoord2f(0, 1);
	glVertex3f(width, length, 0);// C
	glTexCoord2f(1, 1);
	glVertex3f(width, length, height);// K
	glTexCoord2f(1, 0);
	glVertex3f(0, length, height);// J
	glTexCoord2f(0, 0);
	glVertex3f(0, length, 0);// B

	//LEFT
	glTexCoord2f(0, 1);
	glVertex3f(0, length, 0);// B
	glTexCoord2f(1, 1);
	glVertex3f(0, length, height);// J
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, height);// I
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);// A

	//FRONT 
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);// A
	glTexCoord2f(1, 1);
	glVertex3f(width, 0, 0);// D
	glTexCoord2f(1, 0);
	glVertex3f(width, 0, height);// L
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, height);// I

	//TOP
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, height);// I
	glTexCoord2f(1, 1);
	glVertex3f(width, 0, height);// L
	glTexCoord2f(1, 0);
	glVertex3f(width, length, height);// K
	glTexCoord2f(0, 0);
	glVertex3f(0, length, height);// J

	glEnd();

}
//--------------------------------------------------------------------


void drawChestWindows() {


	//draw chest window
	glPushMatrix();
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	glTranslatef(3, 2, 5);
	drawCustomQuads(8, 6, 1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(optRedColor[0], optRedColor[1], optRedColor[2]);
	//draw window frame left 
	glPushMatrix();
	glTranslatef(2, 2, 5);
	drawCustomQuads(8, 1, 2);
	glPopMatrix();

	//draw window frame right 
	glPushMatrix();
	glTranslatef(9, 2, 5);
	drawCustomQuads(8, 1, 2);
	glPopMatrix();

	//draw window frame Top
	glPushMatrix();
	glTranslatef(2, 1, 5);
	drawCustomQuads(1, 8, 2);
	glPopMatrix();

	//draw window frame btm
	glPushMatrix();
	glTranslatef(2, 10, 5);
	drawCustomQuads(1, 8, 2);
	glPopMatrix();
	glPopMatrix();
}

void drawRibs() {
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glPushMatrix();

	glTranslatef(-8, -3, 0);
	drawCustomQuads(3, 4, 5);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(-4, -1, 0);
	drawCustomQuads(1, 3, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-2, 0, -5);
	glPushMatrix();

	glTranslatef(-8, -3, 0);
	drawCustomQuads(3, 4, 5);
	glPopMatrix();

	glPushMatrix();

	glTranslatef(-4, -1, 0);
	drawCustomQuads(1, 3, 5);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}

void drawAbs() {

	// abs behind
	glPushMatrix();
	glColor3f(optRedColor[0], optRedColor[1], optRedColor[2]);
	glTranslatef(-6, -8, 0);
	drawCustomQuads(8, 14, 3);
	glPopMatrix();

	//abs
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(-2, -7, 3);
	drawCustomQuads(8, 6, 1.8);
	glPopMatrix();

	//most btm horizontal abs
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(-2, -6, 4.8);
	drawCustomQuads(0.5, 6, 0.5);
	glPopMatrix();

	//most btm left horizontal abs
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(-2.5, -6, 4.8);
	glRotatef(90, 0, 1, 0);
	drawCustomQuads(0.5, 4, 0.5);
	glPopMatrix();

	//most btm right horizontal abs
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(4, -6, 4.8);
	glRotatef(90, 0, 1, 0);
	drawCustomQuads(0.5, 4, 0.5);
	glPopMatrix();

	//2nd horizontal abs
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(-2, -4, 4.8);
	drawCustomQuads(0.5, 6, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 2, 0);
	//2nd btm left horizontal abs
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(-2.5, -6, 4.8);
	glRotatef(90, 0, 1, 0);
	drawCustomQuads(0.5, 4, 0.5);
	glPopMatrix();

	//2nd btm right horizontal abs
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(4, -6, 4.8);
	glRotatef(90, 0, 1, 0);
	drawCustomQuads(0.5, 4, 0.5);
	glPopMatrix();
	glPopMatrix();

	//1st btm horizontal abs
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(-2, -2, 4.8);
	drawCustomQuads(0.5, 6, 0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, 0);
	//1s5 btm left horizontal abs
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(-2.5, -6, 4.8);
	glRotatef(90, 0, 1, 0);
	drawCustomQuads(0.5, 4, 0.5);
	glPopMatrix();

	//1st btm right horizontal abs
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(4, -6, 4.8);
	glRotatef(90, 0, 1, 0);
	drawCustomQuads(0.5, 4, 0.5);
	glPopMatrix();
	glPopMatrix();

	//vertical abs line
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(0.6, -8, 4.8);
	drawCustomQuads(8, 0.6, 0.5);
	glPopMatrix();
}

void drawScrewUnderWindow() {
	for (int i = -3; i < 15; i += 3) {
		glPushMatrix();
		glTranslatef(i, 0, 0);
		glPushMatrix();
		glColor3f(optOrangeColor[0], optOrangeColor[1], optOrangeColor[2]);
		glTranslatef(-4, 0.6, 1.5);
		drawCylinder(0.4, 0.4, 4);
		glPopMatrix();

		glPushMatrix();
		glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
		glTranslatef(-4, 0.6, 3.7);
		drawCylinder(0.2, 0.2, 2);
		glPopMatrix();
		glPopMatrix();
	}
}

void drawEarPadsHead() {
	//earPads
	glPushMatrix();
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	glTranslatef(0, 2, 0);
	drawCustomQuads(8, 1, 0.5);
	glPopMatrix();

	//square
	glPushMatrix();
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	glRotatef(-20, 0, 0, 1);
	glTranslatef(-2, 0, 0);
	drawCustomQuads(4, 6, 0.5);
	glPopMatrix();

	//cylinder
	glPushMatrix();
	glTranslatef(1, 2, -0.8);
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	drawCylinder(1, 1, 0.8);
	glPopMatrix();

}

void drawEarPadsHeadLeft() {
	//earPads
	glPushMatrix();
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	glTranslatef(0, 2, 0);
	drawCustomQuads(8, 1, 0.5);
	glPopMatrix();

	//square
	glPushMatrix();
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	glRotatef(-20, 0, 0, 1);
	glTranslatef(-2, 0, 0);
	drawCustomQuads(4, 6, 0.5);
	glPopMatrix();

	//cylinder
	glPushMatrix();
	glTranslatef(1, 2, 0.5);
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	drawCylinder(1, 1, 0.8);
	glPopMatrix();

}

void drawTriangleSquare() {
	/*
	glVertex3f(-1, 0, 0); // A
	glVertex3f(1, 0, 0); //B
	glVertex3f(0, 1, 0); //C
	glVertex3f(-1, 0, 1);//D
	glVertex3f(0, 1, 1);//F
	glVertex3f(1, 0, 1);//E
	*/

	glBegin(GL_QUADS);
	//BTM ABED
	glVertex3f(-1, 0, 0); // A
	glVertex3f(1, 0, 0); //B
	glVertex3f(1, 0, 1);//E
	glVertex3f(-1, 0, 1);//D
	glEnd();

	glBegin(GL_TRIANGLES);
	//FRONT DFE
	glVertex3f(-1, 0, 1);//D
	glVertex3f(0, 1, 1);//F
	glVertex3f(1, 0, 1);//E
	glEnd();

	glBegin(GL_QUADS);
	//right EBCF
	glVertex3f(1, 0, 1);//E
	glVertex3f(1, 0, 0); //B
	glVertex3f(0, 1, 0); //C
	glVertex3f(0, 1, 1);//F
	glEnd();

	glBegin(GL_QUADS);
	//FDAC
	glVertex3f(0, 1, 1);//F
	glVertex3f(-1, 0, 1);//D
	glVertex3f(-1, 0, 0); // A
	glVertex3f(0, 1, 0); //C
	glEnd();

	glBegin(GL_TRIANGLES);
	//CBA
	glVertex3f(0, 1, 0); //C
	glVertex3f(1, 0, 0); //B
	glVertex3f(-1, 0, 0); // A
	glEnd();
}

void drawHead() {
	//draw head box
	glPushMatrix();
	glTranslatef(-1, -1, 2);
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	drawCustomQuads(8, 5, 5);
	glPopMatrix();



	//draw mouth
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(1.5, 6, -4);
	glScalef(3, 4, 4);
	glRotatef(30, 1, 0, 0);
	glColor3f(optLightRed[0], optLightRed[1], optLightRed[2]);
	drawTriangleSquare();
	glPopMatrix();


	//lefT earpads
	glPushMatrix();
	glTranslatef(5, 0, 5);
	glRotatef(-90, 0, 1, 0);
	drawEarPadsHead();
	glPopMatrix();

	//rightt earpads
	glPushMatrix();
	glTranslatef(-1.5, 0, 5);
	glRotatef(-270, 0, 1, 0);
	glRotatef(180, 0, 1, 0);
	drawEarPadsHeadLeft();
	glPopMatrix();

	//middle thorn
	glPushMatrix();
	glRotatef(30, 1, 0, 0);
	glTranslatef(1.28, 3, 7);
	drawCustomQuads(5, 0.4, 0.5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(30, 1, 0, 0);
	glTranslatef(-0.2, 3, 5);
	drawCustomQuads(5, 0.4, 0.5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(30, 1, 0, 0);
	glTranslatef(2.8, 3, 5);
	drawCustomQuads(5, 0.4, 0.5);
	glPopMatrix();

	//left eye
	glPushMatrix();
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	glTranslatef(0, 5, 7);
	drawSphere(0.5);
	glPopMatrix();

	//right eye 
	glPushMatrix();
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	glTranslatef(3, 5, 7);
	drawSphere(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.2, 0, 6.5);
	drawCustomQuads(9, 0.5, 1);
	glPopMatrix();

	//right horn
	glPushMatrix();
	glTranslatef(1.4, 8.5, 7);
	glRotatef(90, 0, 1, 0);
	glRotatef(60, 1, 0, 0);
	glRotatef(-60, 0, 0, 1);
	drawCustomQuads(5, 0.5, 0.5);
	glPopMatrix();


	//left horn
	glPushMatrix();
	glTranslatef(1.2, 8, 7);
	glRotatef(90, 0, 1, 0);
	glRotatef(-60, 1, 0, 0);
	glRotatef(-60, 0, 0, 1);
	drawCustomQuads(5, 0.5, 0.5);
	glPopMatrix();

	//middle thorn
	glPushMatrix();
	glTranslatef(0.95, -1, 1.5);
	drawCustomQuads(8, 1, 0.5);
	glPopMatrix();

	//draw bhd head 
	glPushMatrix();
	glTranslatef(1.5, 0, 0.5);
	drawCylinder(0, 0.5, 1);
	glPopMatrix();

	//draw bhd head 
	glPushMatrix();
	glTranslatef(1.5, 2, 0.5);
	drawCylinder(0, 0.5, 1);
	glPopMatrix();

	//draw bhd head 
	glPushMatrix();
	glTranslatef(1.5, 4, 0.5);
	drawCylinder(0, 0.5, 1);
	glPopMatrix();

	//draw bhd head 
	glPushMatrix();
	glTranslatef(1.5, 6, 0.5);
	drawCylinder(0, 0.5, 1);
	glPopMatrix();

}

void drawChest() {
	//Left Grey Cylinder
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(2.5, 8.4, 8);
	drawCylinder(1.6, 1.6, 3);
	glPopMatrix();

	//draw chest
	glPushMatrix();
	glColor3f(optRedColor[0], optRedColor[1], optRedColor[2]);
	glTranslatef(-9, 0, 0);
	drawCustomQuads(12, 20, 5);
	glPopMatrix();

	//Right Grey Cylinder
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-2.5, 8.4, 10);
	drawCylinder(1.6, 1.6, 3);
	glPopMatrix();


	//right
	drawChestWindows();

	glPushMatrix();
	glTranslatef(-10, 0, 0);
	drawChestWindows();
	glPopMatrix();



	drawRibs();
	drawAbs();
	drawScrewUnderWindow();
}

/********************* JIAH MING ********************/

void drawShoe() {	//JM
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 1);
	glVertex3f(0, 1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(1, 1, 0);

	glTexCoord2f(0, 1);
	glVertex3f(1, 1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, -1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0, -1);
	glTexCoord2f(0, 0);
	glVertex3f(1, 0, 1);

	glTexCoord2f(0, 1);
	glVertex3f(1, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, -1);
	glTexCoord2f(0, 0);
	glVertex3f(1, 0, -1);

	glTexCoord2f(0, 1);
	glVertex3f(1, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, -1);
	glTexCoord2f(1, 0);
	glVertex3f(0, 1, -1);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, -1);

	glTexCoord2f(0, 1);
	glVertex3f(0, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 1, -1);

	glTexCoord2f(0, 1);
	glVertex3f(0, 1, -1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(1, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(1, 1, -1);

	glEnd();
}

void drawCone(double br, double tr, double h) {
	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, br, tr, h, 10, 10);
	gluDeleteQuadric(cylinder); //must use deleteQuadric to prevent slowing down or crash
}

void drawUnderwear() {	//JM
	glBegin(GL_POLYGON);

	//glColor3f(1, 0, 0);
	//FRONT
	glVertex3f(2, 2, 0); //P
	glVertex3f(2, 1, 0); //H
	glVertex3f(1, 1, 0); //I
	glVertex3f(0, 0, 0); //B
	glVertex3f(-1, 0, 0); //A
	glVertex3f(-2, 1, 0); //J
	glVertex3f(-3, 1, 0); //F 
	glVertex3f(-3, 2, 0); //O

	//glColor3f(0, 1, 0);
	//RIGHT
	glVertex3f(-3, 2, 0); //O
	glVertex3f(-3, 1, 0); //F
	glVertex3f(-2, 1, 0); //J
	glVertex3f(-1, 0, 0); //A
	glVertex3f(-1, 0, 6); //D
	glVertex3f(-2, 1, 6); //K
	glVertex3f(-3, 1, 6); //E
	glVertex3f(-3, 2, 6); //M

	//glColor3f(0, 0, 1);
	//BEHIND
	glVertex3f(-3, 2, 6); //M
	glVertex3f(-3, 1, 6); //E
	glVertex3f(-2, 1, 6); //K
	glVertex3f(-1, 0, 6); //D
	glVertex3f(0, 0, 6); //C
	glVertex3f(1, 1, 6); //L
	glVertex3f(2, 1, 6); //G
	glVertex3f(2, 2, 6); //N

	//glColor3f(1, 1, 0);
	//TOP
	glVertex3f(2, 2, 6); //N
	glVertex3f(-3, 2, 6); //M
	glVertex3f(-3, 2, 0); //O
	glVertex3f(2, 2, 0); //P

	//glColor3f(1, 0, 1);
	//LEFT
	glVertex3f(2, 2, 0); //N
	glVertex3f(2, 1, 0); //P
	glVertex3f(1, 1, 0); //H
	glVertex3f(0, 0, 0); //I
	glVertex3f(0, 0, 6); //B
	glVertex3f(1, 1, 6); //C
	glVertex3f(2, 1, 6); //L
	glVertex3f(2, 2, 6); //G

	glEnd();
}
//change
void drawQuads(double length, double width, double height) {
	glBegin(GL_QUADS);

	//Bottom
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);// A
	glTexCoord2f(1, 1);
	glVertex3f(0, length, 0);// B
	glTexCoord2f(1, 0);
	glVertex3f(width, length, 0);// C
	glTexCoord2f(0, 0);
	glVertex3f(width, 0, 0);// D

	//RIGHT
	glTexCoord2f(0, 1);
	glVertex3f(width, 0, 0);// D
	glTexCoord2f(1, 1);
	glVertex3f(width, 0, height);// L
	glTexCoord2f(1, 0);
	glVertex3f(width, length, height);// K
	glTexCoord2f(0, 0);
	glVertex3f(width, length, 0);// C

	//BEHIND 
	glTexCoord2f(0, 1);
	glVertex3f(width, length, 0);// C
	glTexCoord2f(1, 1);
	glVertex3f(width, length, height);// K
	glTexCoord2f(1, 0);
	glVertex3f(0, length, height);// J
	glTexCoord2f(0, 0);
	glVertex3f(0, length, 0);// B

	//LEFT
	glTexCoord2f(0, 1);
	glVertex3f(0, length, 0);// B
	glTexCoord2f(1, 1);
	glVertex3f(0, length, height);// J
	glTexCoord2f(1, 0);
	glVertex3f(0, 0, height);// I
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);// A

	//FRONT 
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);// A
	glTexCoord2f(1, 1);
	glVertex3f(width, 0, 0);// D
	glTexCoord2f(1, 0);
	glVertex3f(width, 0, height);// L
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, height);// I

	//TOP
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, height);// I
	glTexCoord2f(1, 1);
	glVertex3f(width, 0, height);// L
	glTexCoord2f(1, 0);
	glVertex3f(width, length, height);// K
	glTexCoord2f(0, 0);
	glVertex3f(0, length, height);// J

	glEnd();

}

void drawRobotLeftHand() {	//JM
	/*************  LEFT ARM  *************/

	glPushMatrix();
	glTranslatef(10, 0, 0);

	//Cone On Shoulders 1 (Left cone)
	glPushMatrix();
	glColor3f(optRedColor[0], optRedColor[1], optRedColor[2]);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(7.9, -3.5, 11);
	drawCone(1, 0, 2);
	glPopMatrix();

	//Cone On Shoulders 2 (Right cone)
	glPushMatrix();
	glColor3f(optRedColor[0], optRedColor[1], optRedColor[2]);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(11.1, -3.5, 11);
	drawCone(1, 0, 2);
	glPopMatrix();

	//Left shoulder
	glPushMatrix();
	glColor3f(optLightRed[0], optLightRed[1], optLightRed[2]);
	glTranslatef(7, 6, 1);
	drawQuads(5, 5, 5);
	glPopMatrix();

	//Left Shoulder Design 1 (Grey Cylinder)
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(9.5, 8.5, 4);
	drawCylinder(1.3, 1.3, 3);
	glPopMatrix();

	//Left Shoulder Design 2 (Yellow Cylinder)
	glPushMatrix();
	glColor3f(1, 0.84, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-3.5, 8.5, 12);
	drawCylinder(1.3, 1.3, 1);
	glPopMatrix();

	//Elbow
	glPushMatrix();
	glColor3f(optRedColor[0], optRedColor[1], optRedColor[2]);
	glTranslatef(8, 2, 1.5);
	drawQuads(4, 3, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9.5, 3, 3.3);
	//drawSphere(7);
	glRotatef(leftArmAngle, 0, 0, x);
	glPushMatrix();
	glTranslatef(-9.5, -3, -3.3);
	//Arm
	glPushMatrix();
	glColor3f(optLightRed[0], optLightRed[1], optLightRed[2]);
	glTranslatef(7, -6, 1);
	drawQuads(9, 5, 5);
	glPopMatrix();

	//Left Arm design 1
	glPushMatrix();
	glColor3f(1, 0.84, 0);
	glTranslatef(8, -1, 5);
	drawQuads(1, 3, 2);
	glPopMatrix();

	//Left Arm design 2
	glPushMatrix();
	glColor3f(1, 0.84, 0);
	glTranslatef(8, -4, 5);
	drawQuads(1, 3, 2);
	glPopMatrix();

	//Hands
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(7.5, -9, 1.5);
	drawQuads(3, 4, 4);
	glPopMatrix();

	/************** FINGER 1 **************/
	//Finger Joint 1
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(8, -9.25, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -9.5, 4.5);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(longFingerAngle, x, 0, 0);
	glRotatef(longLeftFinger4Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 9.5, -4.6);
	//Top Finger 1
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(7.76, -10.5, 4.5);
	drawQuads(1, 0.5, 0.5);
	glPopMatrix();

	//Middle Finger Joint 1
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(8, -10.75, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -10.5, 4.55);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(shortFingerAngle, x, 0, 0);
	glRotatef(shortLeftFinger4Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 11.5, -4.5);
	//Middle Part Finger 1
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(7.76, -14, 4.5);
	drawQuads(2, 0.5, 0.5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	/************** FINGER 2 **************/
	//Finger Joint 2
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(9, -9.25, 4.7);
	drawSphere(0.3);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-5, -9.5, 4.5);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(longFingerAngle, x, 0, 0);
	glRotatef(longLeftFinger3Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 9.5, -4.6);
	//Top Finger 2
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(8.76, -10.5, 4.5);
	drawQuads(1, 0.5, 0.5);
	glPopMatrix();

	//Middle Finger Joint 2
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(9, -10.75, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -10.5, 4.55);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(shortFingerAngle, x, 0, 0);
	glRotatef(shortLeftFinger3Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 11.5, -4.5);
	//Middle Part Finger 2
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(8.76, -14, 4.5);
	drawQuads(2, 0.5, 0.5);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	/************** FINGER 3 **************/
	//Finger Joint 3
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(10, -9.25, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -9.5, 4.5);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(longFingerAngle, x, 0, 0);
	glRotatef(longLeftFinger2Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 9.5, -4.6);
	//Top Finger 3
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(9.76, -10.5, 4.5);
	drawQuads(1, 0.5, 0.5);
	glPopMatrix();

	//Middle Finger Joint 3
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(10, -10.75, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -10.5, 4.55);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(shortFingerAngle, x, 0, 0);
	glRotatef(shortLeftFinger2Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 11.5, -4.5);
	//Middle Part Finger 3
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(9.76, -14, 4.5);
	drawQuads(2, 0.5, 0.5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	/************** FINGER 4 **************/
	//Finger Joint 4
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(11, -9.25, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -9.5, 4.5);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(longFingerAngle, x, 0, 0);
	glRotatef(longLeftFinger1Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 9.5, -4.6);
	//Top Finger 4
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(10.76, -10.5, 4.5);
	drawQuads(1, 0.5, 0.5);
	glPopMatrix();


	//Middle Finger Joint 4
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(11, -10.75, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -10.5, 4.55);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(shortFingerAngle, x, 0, 0);
	glRotatef(shortLeftFinger1Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 11.5, -4.5);
	//Middle Part Finger 4
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(10.76, -14, 4.5);
	drawQuads(2, 0.5, 0.5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

//changed right hand
void drawRobotRightHand() {		//JM
	/*************  RIGHT ARM  *************/

	glPushMatrix();
	glTranslatef(10, 0, 0);

	//Cone On Shoulders 1 (Left cone)
	glPushMatrix();
	glColor3f(optRedColor[0], optRedColor[1], optRedColor[2]);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(7.9, -3.5, 11);
	drawCone(1, 0, 2);
	glPopMatrix();

	//Cone On Shoulders 2 (Right cone)
	glPushMatrix();
	glColor3f(optRedColor[0], optRedColor[1], optRedColor[2]);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(11.1, -3.5, 11);
	drawCone(1, 0, 2);
	glPopMatrix();

	//Right shoulder
	glPushMatrix();
	glColor3f(optLightRed[0], optLightRed[1], optLightRed[2]);
	glTranslatef(7, 6, 1);
	drawQuads(5, 5, 5);
	glPopMatrix();

	//Right Shoulder Design (Grey Cylinder)
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(9.5, 8.5, 4);
	drawCylinder(1.3, 1.3, 3);
	glPopMatrix();


	//Right Shoulder Design 2 (Yellow Cylinder)
	glPushMatrix();
	glColor3f(1, 0.84, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-3.5, 8.5, 6);
	drawCylinder(1.3, 1.3, 1);
	glPopMatrix();

	//Elbow
	glPushMatrix();
	glColor3f(optRedColor[0], optRedColor[1], optRedColor[2]);
	glTranslatef(8, 2, 1.5);
	drawQuads(4, 3, 4);
	glPopMatrix();

	//Lower arm movement
	glPushMatrix();
	glTranslatef(9.5, 3, 3.3);
	//drawSphere(7);
	glRotatef(rightArmAngle, 0, 0, x);
	glPushMatrix();
	glTranslatef(-9.5, -3, -3.3);
	//Arm
	glPushMatrix();
	glColor3f(optLightRed[0], optLightRed[1], optLightRed[2]);
	glTranslatef(7, -6, 1);
	drawQuads(9, 5, 5);
	glPopMatrix();

	//Right Arm design 1
	glPushMatrix();
	glColor3f(1, 0.84, 0);
	glTranslatef(8, -1, 5);
	drawQuads(1, 3, 2);
	glPopMatrix();

	//Right Arm design 2
	glPushMatrix();
	glColor3f(1, 0.84, 0);
	glTranslatef(8, -4, 5);
	drawQuads(1, 3, 2);
	glPopMatrix();


	//Hands
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(7.5, -9, 1.5);
	drawQuads(3, 4, 4);
	glPopMatrix();

	/************** FINGER 1 **************/
	//Finger Joint 1
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(8, -9.25, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -9.5, 4.5);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(longFingerAngle, x, 0, 0);
	glRotatef(longRightFinger1Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 9.5, -4.6);
	//Top Finger 1
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(7.76, -10.5, 4.5);
	drawQuads(1, 0.5, 0.5);
	glPopMatrix();

	//Middle Finger Joint 1
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(8, -10.75, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -10.5, 4.55);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(shortFingerAngle, x, 0, 0);
	glRotatef(shortRightFinger1Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 11.5, -4.5);
	//Middle Part Finger 1
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(7.76, -14, 4.5);
	drawQuads(2, 0.5, 0.5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	/************** FINGER 2 **************/
	//Finger Joint 2
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(9, -9.25, 4.7);
	drawSphere(0.3);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-5, -9.5, 4.5);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(longFingerAngle, x, 0, 0);
	glRotatef(longRightFinger2Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 9.5, -4.6);
	//Top Finger 2
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(8.76, -10.5, 4.5);
	drawQuads(1, 0.5, 0.5);
	glPopMatrix();

	//Middle Finger Joint 2
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(9, -10.75, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -10.5, 4.55);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(shortFingerAngle, x, 0, 0);
	glRotatef(shortRightFinger2Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 11.5, -4.5);
	//Middle Part Finger 2
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(8.76, -14, 4.5);
	drawQuads(2, 0.5, 0.5);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	/************** FINGER 3 **************/
	//Finger Joint 3
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(10, -9.25, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -9.5, 4.5);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(longFingerAngle, x, 0, 0);
	glRotatef(longRightFinger3Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 9.5, -4.6);
	//Top Finger 3
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(9.76, -10.5, 4.5);
	drawQuads(1, 0.5, 0.5);
	glPopMatrix();

	//Middle Finger Joint 3
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(10, -10.75, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -10.5, 4.55);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(shortFingerAngle, x, 0, 0);
	glRotatef(shortRightFinger3Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 11.5, -4.5);
	//Middle Part Finger 3
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(9.76, -14, 4.5);
	drawQuads(2, 0.5, 0.5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	/************** FINGER 4 **************/
	//Finger Joint 4
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(11, -9.25, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -9.5, 4.5);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(longFingerAngle, x, 0, 0);
	glRotatef(longRightFinger4Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 9.5, -4.6);
	//Top Finger 4
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(10.76, -10.5, 4.5);
	drawQuads(1, 0.5, 0.5);
	glPopMatrix();


	//Middle Finger Joint 4
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(11, -10.75, 4.7);
	drawSphere(0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -10.5, 4.55);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(shortFingerAngle, x, 0, 0);
	glRotatef(shortRightFinger4Angle, x, 0, 0);
	glPushMatrix();
	glTranslatef(5, 11.5, -4.5);
	//Middle Part Finger 4
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(10.76, -14, 4.5);
	drawQuads(2, 0.5, 0.5);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

} // changed

void drawRobotWaist() {		//JM
	/************** WAIST **************/

	//Waist
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glPushMatrix();
	glTranslatef(3, 0, 0.5);
	glScalef(4, 3, 1);
	drawUnderwear();
	glPopMatrix();

	//Left Sphere
	glPushMatrix();
	glColor3f(optDarkGrey[0], optDarkGrey[1], optDarkGrey[2]);
	glTranslatef(-6.5, 2, 3.5);
	drawSphere(1);
	glPopMatrix();

	//Right Sphere
	glPushMatrix();
	glColor3f(optDarkGrey[0], optDarkGrey[1], optDarkGrey[2]);
	glTranslatef(8.5, 2, 3.5);
	drawSphere(1);
	glPopMatrix();
}

//changedleg
void drawRobotLeftLeg() {	//JM
	/************** LEFT LEG **************/

	//Quadriceps
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(-9, -16, 1);
	drawQuads(11, 5, 5);
	glPopMatrix();

	//Quadriceps design 1
	glPushMatrix();
	glColor3f(optDarkGrey[0], optDarkGrey[1], optDarkGrey[2]);
	glTranslatef(-8, -7, 5);
	drawQuads(1, 3, 2);
	glPopMatrix();

	//Quadriceps design 2
	glPushMatrix();
	glColor3f(optDarkGrey[0], optDarkGrey[1], optDarkGrey[2]);
	glTranslatef(-8, -9, 5);
	drawQuads(1, 3, 2);
	glPopMatrix();

	//Knee
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(-8, -18, 1.5);
	drawQuads(3, 3, 4);
	glPopMatrix();

	//Leg
	glPushMatrix();
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	glTranslatef(-10, -29, 0);
	drawQuads(12, 7, 7);
	glPopMatrix();

	//Left leg design 1
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-3, -23, -11);
	drawCylinder(1.3, 1.3, 1);
	glPopMatrix();

	//Left leg design 2
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-3, -26.5, -11);
	drawCylinder(1.3, 1.3, 1);
	glPopMatrix();

	//Left Shoe
	glPushMatrix();
	glTranslatef(-10, -34, 7);
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glScalef(7, 5, 7);
	drawShoe();
	glPopMatrix();
}

//changedleg
void drawRobotRightLeg() {	//JM
	/************** RIGHT LEG **************/

	//Quadriceps
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(9, -16, 1);
	drawQuads(11, 5, 5);
	glPopMatrix();

	//Quadriceps design 1
	glPushMatrix();
	glColor3f(optDarkGrey[0], optDarkGrey[1], optDarkGrey[2]);
	glTranslatef(10, -7, 5);
	drawQuads(1, 3, 2);
	glPopMatrix();

	//Quadriceps design 2
	glPushMatrix();
	glColor3f(optDarkGrey[0], optDarkGrey[1], optDarkGrey[2]);
	glTranslatef(10, -9, 5);
	drawQuads(1, 3, 2);
	glPopMatrix();

	//Knee
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glTranslatef(10, -18, 1.5);
	drawQuads(3, 3, 4);
	glPopMatrix();

	//Leg
	glPushMatrix();
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	glTranslatef(8, -29, 0);
	drawQuads(12, 7, 7);
	glPopMatrix();

	//Right leg design 1
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-3, -23, 15);
	drawCylinder(1.3, 1.3, 1);
	glPopMatrix();

	//Right leg design 2
	glPushMatrix();
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-3, -26.5, 15);
	drawCylinder(1.3, 1.3, 1);
	glPopMatrix();

	//Right Shoe
	glPushMatrix();
	glTranslatef(8, -34, 7);
	glColor3f(optGrey[0], optGrey[1], optGrey[2]);
	glScalef(7, 5, 7);
	drawShoe();
	glPopMatrix();
}


void drawStar() {


	glBegin(GL_TRIANGLES);

	glVertex3f(-0.60, 0.77, 0);
	glVertex3f(-0.42, 0.77, 0);
	glVertex3f(-0.58, 0.68, 0);

	//second triangle top triangle
	glVertex3f(-0.64, 1, 0);
	glVertex3f(-0.68, 0.77, 0);
	glVertex3f(-0.60, 0.77, 0);

	//3rd Triangle
	glVertex3f(-0.68, 0.77, 0);
	glVertex3f(-0.7, 0.68, 0);
	glVertex3f(-0.86, 0.77, 0);

	//4th Triangle
	glVertex3f(-0.64, 0.63, 0);
	glVertex3f(-0.7, 0.68, 0);
	glVertex3f(-0.82, 0.43, 0);

	//5th Triangle
	glVertex3f(-0.64, 0.63, 0);
	glVertex3f(-0.58, 0.68, 0);
	glVertex3f(-0.51, 0.43, 0);

	glEnd();

	glBegin(GL_POLYGON);//code for the Polygon within the stars

	glVertex3f(-0.60, 0.77, 0); // <--- -0.60 instead of -0.68
	glVertex3f(-0.68, 0.77, 0);
	glVertex3f(-0.7, 0.68, 0);
	glVertex3f(-0.64, 0.63, 0);
	glVertex3f(-0.58, 0.68, 0);

	glEnd();
}

void drawGun() {
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 2);
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	drawCylinder(1, 1, 8);
	glPopMatrix();

	//magazine small clylinder left 1 
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 3);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	//magazine small clylinder left 2nd 
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 5);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	//magazine small clylinder left 3rd
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 7);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	//===============================================================
	glPushMatrix();
	glTranslatef(0, 0, 2);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 2);
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	drawCylinder(1, 1, 8);
	glPopMatrix();

	//magazine small clylinder left 1 
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 3);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	//magazine small clylinder left 2nd 
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 5);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	//magazine small clylinder left 3rd
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 7);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	glPopMatrix();

	//===================================TOP
	glPushMatrix();
	glTranslatef(0, 2, 0);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 2);
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	drawCylinder(1, 1, 8);
	glPopMatrix();

	//magazine small clylinder left 1 
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 3);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	//magazine small clylinder left 2nd 
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 5);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	//magazine small clylinder left 3rd
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 7);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	//===============================================================
	glPushMatrix();
	glTranslatef(0, 0, 2);
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 2);
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	drawCylinder(1, 1, 8);
	glPopMatrix();

	//magazine small clylinder left 1 
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 3);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	//magazine small clylinder left 2nd 
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 5);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	//magazine small clylinder left 3rd
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, -1, 7);
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	drawCylinder(1.2, 1.2, 0.5);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();

	//=======================================
	//Gun body
	glPushMatrix();
	glTranslatef(5, -1, 0.8);
	glColor3f(optOrangeColor[0], optOrangeColor[1], optOrangeColor[2]);
	drawCustomQuads(2, 8, 4);
	glPopMatrix();

	//cylinder
	glPushMatrix();
	glColor3f(optLightRed[0], optLightRed[1], optLightRed[2]);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-3, 0, 10);
	drawCylinder(1, 2, 6);
	glPopMatrix();

	//extension not straight long
	glPushMatrix();
	glTranslatef(5, -5, 2.7);
	glRotatef(45, 0, 0, 1);
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	drawCustomQuads(0.5, 5, 0.5);
	glPopMatrix();

	//extension not straight short
	glPushMatrix();
	glTranslatef(5, -3, 2.7);
	glRotatef(45, 0, 0, 1);
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	drawCustomQuads(0.5, 5, 0.5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glTranslatef(-5, -5, 0);
	//extension not straight long
	glPushMatrix();
	glTranslatef(5, -5, 2.7);
	glRotatef(45, 0, 0, 1);
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	drawCustomQuads(0.5, 5, 0.5);
	glPopMatrix();

	//extension not straight short
	glPushMatrix();
	glTranslatef(5, -3, 2.7);
	glRotatef(45, 0, 0, 1);
	glColor3f(optlightBColor[0], optlightBColor[1], optlightBColor[2]);
	drawCustomQuads(0.5, 5, 0.5);
	glPopMatrix();
	glPopMatrix();

	//2nd most infront
	glPushMatrix();
	glTranslatef(-4, 0, 1.5);
	glRotatef(45, 1, 0, 0);
	glColor3f(optLightRed[0], optLightRed[1], optLightRed[2]);
	drawCustomQuads(2, 7, 2);
	glPopMatrix();


	//most infront sharp edgest
	glPushMatrix();
	glColor3f(optlightGrey[0], optlightGrey[1], optlightGrey[2]);
	glTranslatef(-8, 0, 3);
	glRotatef(90, 0, 1, 0);
	drawCylinder(0.1, 0.7, 4);
	glPopMatrix();

	//holder for holding 
	glPushMatrix();
	glColor3f(optBlue[0], optBlue[1], optBlue[2]);
	glTranslatef(15, -8, 2.5);
	glRotatef(50, 0, 0, 1);

	drawCustomQuads(9, 1, 1);
	glPopMatrix();



	//also want to check where the gun is active or not 
	if (shoot) {

		shootAngle -= 0.2;

		//Bullet
		glPushMatrix();
		glScalef(shootScale, shootScale, shootScale);
		glColor3f(0, 1, 0);
		glRotatef(90, 0, 1, 0);
		//the z-axis = x 
		glTranslatef(-3, 0, shootAngle);
		drawCylinder(0.1, 0.5, 3);
		glPopMatrix();

		if (shootAngle < -70) {
			//reset 
			shootScale = 0;
			shootAngle = -9;
			shoot = false;
		}
		else {
			shootScale = 1;
		}
	}
}

GLuint loadTexture(LPCSTR filename) {
	//take from step 1
	GLuint texture = 0;  // Define a texture name we are going to use for texture mapping. In OpenGL, any non-zero unsigned integer may be used as a texture name.

	//Step 3: Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	// Step 4: Assign texture to polygon.
	glEnable(GL_TEXTURE_2D);  // This function will enable 2D texture mapping for OpenGL. 
	glGenTextures(1, &texture);// This function will return 1 currently unused names for the given texture object. 
	glBindTexture(GL_TEXTURE_2D, texture);
	//When the texture name is used for the first time, this function will create a new texture objectand assigned with the given name
	// This function is also called when we want to bind a previously created texture to an object. 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//This function is used to specify the magnification and minification filtering methods
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits); // - This function is used to define a two dimensional texture.

	//take from step 5
	DeleteObject(hBMP);// - Delete the bitmap handle once you create the texture object. 

	return texture;
}

void handleg() {

	//Left Robot Hand
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(1.8, 4.5, 5);
	glPushMatrix();
	glRotatef(leftHandAngle, 0, 0, z);
	glRotatef(leftHandSideway, x, 0, 0);

	if (gun) {
		glPushMatrix();
		glScalef(0.6, 0.6, 0.6);
		glTranslatef(5, -27, 3.5);
		glRotatef(180, 0, 1, 0);
		glRotatef(90, 0, 0, 1);
		drawGun();
		glPopMatrix();
	}
	//drawSphere(4);
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-19.5, -8.5, -3);
	drawRobotLeftHand();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//Right Robot Hand
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-1.8, 4.5, 6);
	glPushMatrix();
	//drawSphere(4);
	glRotatef(rightHandAngle, 0, 0, z);
	glRotatef(rightHandSideway, x, 0, 0);
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-19.5, -8.5, -3);
	drawRobotRightHand();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	//Left Robot Leg
	glPushMatrix();
	glTranslatef(-2.6, -4.3, 1.7);
	glPushMatrix();
	glRotatef(leftRobotLeg, x, 0, 0);
	//drawSphere(6);
	glPushMatrix();
	glTranslatef(3.3, 3, -1.5);
	glScalef(0.5, 0.5, 0.5);
	drawRobotLeftLeg();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	//Right Robot Leg
	glPushMatrix();
	glTranslatef(3.3, -4.3, 1.7);
	glPushMatrix();
	glRotatef(rightRobotLeg, x, 0, 0);
	/*drawSphere(6);*/
	glPushMatrix();
	glTranslatef(-5.7, 3, -1.5);
	glScalef(0.5, 0.5, 0.5);
	drawRobotRightLeg();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void body() {
	//draw head
	glPushMatrix();
	glTranslatef(0.5, 7.6, 2.5);
	glPushMatrix();
	glRotatef(headAngle, 0, y, 0);
	//drawSphere(5);
	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-1.5, -2.5, -5);
	drawHead();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//draw body 
	glPushMatrix();
	glScalef(0.4, 0.4, 0.4);
	glTranslatef(0.2, 3, 2);
	drawChest();
	glPopMatrix();
	//Robot Waist
	glPushMatrix();
	glScalef(0.35, 0.35, 0.35);
	glTranslatef(0, -11.9, 2);
	drawRobotWaist();
	glPopMatrix();

}

void bodyTexture() {
	glPushMatrix();
	GLuint textureArray[7];
	switch (changeTexture) {
	case 1:
		body();
		break;
	case 2:
		textureArray[0] = loadTexture("water.bmp");
		body();
		glDeleteTextures(1, &textureArray[0]);// This function is called to free the texture name.
		break;

	case 3:
		textureArray[1] = loadTexture("green.bmp");
		body();
		glDeleteTextures(1, &textureArray[1]);// This function is called to free the texture name.
		break;

	case 4:
		textureArray[2] = loadTexture("ice.bmp");
		body();
		glDeleteTextures(1, &textureArray[2]);// This function is called to free the texture name.
		break;

	case 5:
		textureArray[3] = loadTexture("rust.bmp");
		body();
		glDeleteTextures(1, &textureArray[3]);// This function is called to free the texture name.
		break;

	case 6:
		textureArray[4] = loadTexture("fire.bmp");
		body();
		glDeleteTextures(1, &textureArray[4]);// This function is called to free the texture name.
		break;

	case 7:
		textureArray[5] = loadTexture("purple.bmp");
		body();
		glDeleteTextures(1, &textureArray[5]);// This function is called to free the texture name.
		break;
	case 8:
		textureArray[6] = loadTexture("dirt.bmp");
		body();
		glDeleteTextures(1, &textureArray[6]);// This function is called to free the texture name.
		break;
	default:
		break;
	}
	glDisable(GL_TEXTURE_2D);  //This function will disable 2D texture mapping for OpenGL. 

	glPopMatrix();
}

void handlegTexture() {
	glPushMatrix();
	GLuint textureArray[7];
	switch (changeTexture) {
	case 1:
		handleg();
		break;
	case 2:
		textureArray[0] = loadTexture("rust.bmp");
		handleg();
		glDeleteTextures(1, &textureArray[0]);// This function is called to free the texture name.
		break;

	case 3:
		textureArray[1] = loadTexture("dirt.bmp");
		handleg();
		glDeleteTextures(1, &textureArray[1]);// This function is called to free the texture name.
		break;

	case 4:
		textureArray[2] = loadTexture("fire.bmp");
		handleg();
		glDeleteTextures(1, &textureArray[2]);// This function is called to free the texture name.
		break;

	case 5:
		textureArray[3] = loadTexture("ice.bmp");
		handleg();
		glDeleteTextures(1, &textureArray[3]);// This function is called to free the texture name.
		break;

	case 6:
		textureArray[4] = loadTexture("purple.bmp");
		handleg();
		glDeleteTextures(1, &textureArray[4]);// This function is called to free the texture name.
		break;
	case 7:
		textureArray[5] = loadTexture("green.bmp");
		handleg();
		glDeleteTextures(1, &textureArray[5]);// This function is called to free the texture name.
		break;
	case 8:
		textureArray[6] = loadTexture("water.bmp");
		handleg();
		glDeleteTextures(1, &textureArray[6]);// This function is called to free the texture name.
		break;
	default:
		break;
	}
	glDisable(GL_TEXTURE_2D);  //This function will disable 2D texture mapping for OpenGL. 

	glPopMatrix();
}

void lighting() {

	//light 0 : red color amb light at pos (0,6,0) above enable lightning 

	GLfloat specular[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);


	if (isLightOn) {
		glEnable(GL_LIGHTING);
	}
	else {
		glDisable(GL_LIGHTING);
	}


	//light 1 : Green color dif light at pos(6,0,0) above
	glLightfv(GL_LIGHT1, GL_DIFFUSE, specular);
	glLightfv(GL_LIGHT1, GL_POSITION, posD);

	glEnable(GL_LIGHT1);


	glMatrixMode(GL_MODELVIEW);//refer to modelview matrix
	glLoadIdentity(); //to reset the modelview


	//ambient Material
	glMaterialfv(GL_FRONT, GL_AMBIENT, specular);





}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	projection();
	glMatrixMode(GL_MODELVIEW);        //refer to modelview matrix
	glLoadIdentity();

	lighting();

	//Create background ===========================================================
	GLuint textureArray[1];

	glPushMatrix();
	glTranslatef(-50, -50, -68);
	textureArray[0] = loadTexture("background.bmp");
	drawCustomQuads(80, 80, 50);
	glDeleteTextures(1, &textureArray[0]);// This function is called to free the texture name.
	glPopMatrix();
	//Create background ===========================================================


	if (isLightOn) {
		glPushMatrix();
		glTranslatef(posD[0], posD[1], posD[2]);
		glColor3f(1, 1, 0);
		drawSphere(2);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0, 0, moveZRobot);
	glTranslatef(0, moveYRobot, 0);
	bodyTexture();
	handlegTexture();

	glDisable(GL_TEXTURE_2D);  //This function will disable 2D texture mapping for OpenGL.
	glPopMatrix();

	if (walk == true) {

		if (leftHandAngle < -70 && rightHandAngle < -70 && leftRobotLeg < -70 && rightRobotLeg > 70) {
			//stop
			returnMovement = true;
			leftHandAngle += 0.1;
			rightHandAngle += 0.1;
			leftRobotLeg += 0.1;
			rightRobotLeg -= 0.1;
		}
		else {
			if (leftHandAngle > 70) {
				returnMovement = false;
			}

			if (returnMovement) {
				leftHandAngle += 0.1;
				rightHandAngle += 0.1;
				leftRobotLeg += 0.1;
				rightRobotLeg -= 0.1;
			}
			else {
				leftHandAngle -= 0.1;
				rightHandAngle -= 0.1;
				leftRobotLeg -= 0.1;
				rightRobotLeg += 0.1;
			}


		}
	}


}



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));



	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------

