//int changeTexture = 1;
//
//
//
//
//
//		else if (wParam == 'F') {
//		if (changeTexture == 8) {
//			changeTexture = 1;
//		}
//		else {
//			changeTexture++;
//		}
//		}
//
//
//
//
//
//
//
//		void body() {
//			//draw head
//			glPushMatrix();
//			glTranslatef(0.5, 7.6, 2.5);
//			glPushMatrix();
//			glRotatef(headAngle, 0, y, 0);
//			//drawSphere(5);
//			glPushMatrix();
//			glScalef(0.5, 0.5, 0.5);
//			glTranslatef(-1.5, -2.5, -5);
//			drawHead();
//			glPopMatrix();
//			glPopMatrix();
//			glPopMatrix();
//
//			//draw body 
//			glPushMatrix();
//			glScalef(0.4, 0.4, 0.4);
//			glTranslatef(0.2, 3, 2);
//			drawChest();
//			glPopMatrix();
//			//Robot Waist
//			glPushMatrix();
//			glScalef(0.35, 0.35, 0.35);
//			glTranslatef(0, -11.9, 2);
//			drawRobotWaist();
//			glPopMatrix();
//
//		}
//
//		void handleg() {
//
//			//Left Robot Hand
//			glPushMatrix();
//			glRotatef(-90, 0, 1, 0);
//			glTranslatef(1.8, 4.5, 5);
//			glPushMatrix();
//			glRotatef(leftHandAngle, 0, 0, x);
//
//			if (gun) {
//				glPushMatrix();
//				glScalef(0.6, 0.6, 0.6);
//				glTranslatef(5, -27, 3.5);
//				glRotatef(180, 0, 1, 0);
//				glRotatef(90, 0, 0, 1);
//				drawGun();
//				glPopMatrix();
//			}
//			//drawSphere(4);
//			glPushMatrix();
//			glScalef(0.5, 0.5, 0.5);
//			glTranslatef(-19.5, -8.5, -3);
//			drawRobotLeftHand();
//			glPopMatrix();
//			glPopMatrix();
//			glPopMatrix();
//
//			//Right Robot Hand
//			glPushMatrix();
//			glRotatef(90, 0, 1, 0);
//			glTranslatef(-1.8, 4.5, 6);
//			glPushMatrix();
//			//drawSphere(4);
//			glRotatef(rightHandAngle, 0, 0, x);
//			glPushMatrix();
//			glScalef(0.5, 0.5, 0.5);
//			glTranslatef(-19.5, -8.5, -3);
//			drawRobotRightHand();
//			glPopMatrix();
//			glPopMatrix();
//			glPopMatrix();
//
//
//			//Left Robot Leg
//			glPushMatrix();
//			glTranslatef(-2.6, -4.3, 1.7);
//			glPushMatrix();
//			glRotatef(leftRobotLeg, x, 0, 0);
//			//drawSphere(6);
//			glPushMatrix();
//			glTranslatef(3.3, 3, -1.5);
//			glScalef(0.5, 0.5, 0.5);
//			drawRobotLeftLeg();
//			glPopMatrix();
//			glPopMatrix();
//			glPopMatrix();
//
//
//			//Right Robot Leg
//			glPushMatrix();
//			glTranslatef(3.3, -4.3, 1.7);
//			glPushMatrix();
//			glRotatef(rightRobotLeg, x, 0, 0);
//			/*drawSphere(6);*/
//			glPushMatrix();
//			glTranslatef(-5.7, 3, -1.5);
//			glScalef(0.5, 0.5, 0.5);
//			drawRobotRightLeg();
//			glPopMatrix();
//			glPopMatrix();
//			glPopMatrix();
//		}
//
//
//		void bodyTexture() {
//			glPushMatrix();
//			GLuint textureArray[7];
//			switch (changeTexture) {
//			case 1:
//				body();
//				break;
//			case 2:
//				textureArray[0] = loadTexture("water.bmp");
//				body();
//				glDeleteTextures(1, &textureArray[0]);// This function is called to free the texture name.
//				break;
//
//			case 3:
//				textureArray[1] = loadTexture("green.bmp");
//				body();
//				glDeleteTextures(1, &textureArray[1]);// This function is called to free the texture name.
//				break;
//
//			case 4:
//				textureArray[2] = loadTexture("ice.bmp");
//				body();
//				glDeleteTextures(1, &textureArray[2]);// This function is called to free the texture name.
//				break;
//
//			case 5:
//				textureArray[3] = loadTexture("rust.bmp");
//				body();
//				glDeleteTextures(1, &textureArray[3]);// This function is called to free the texture name.
//				break;
//
//			case 6:
//				textureArray[4] = loadTexture("fire.bmp");
//				body();
//				glDeleteTextures(1, &textureArray[4]);// This function is called to free the texture name.
//				break;
//
//			case 7:
//				textureArray[5] = loadTexture("purple.bmp");
//				body();
//				glDeleteTextures(1, &textureArray[5]);// This function is called to free the texture name.
//				break;
//			case 8:
//				textureArray[6] = loadTexture("dirt.bmp");
//				body();
//				glDeleteTextures(1, &textureArray[6]);// This function is called to free the texture name.
//				break;
//			default:
//				break;
//			}
//			glDisable(GL_TEXTURE_2D);  //This function will disable 2D texture mapping for OpenGL. 
//
//			glPopMatrix();
//		}
//
//		void handlegTexture() {
//			glPushMatrix();
//			GLuint textureArray[7];
//			switch (changeTexture) {
//			case 1:
//				handleg();
//				break;
//			case 2:
//				textureArray[0] = loadTexture("rust.bmp");
//				handleg();
//				glDeleteTextures(1, &textureArray[0]);// This function is called to free the texture name.
//				break;
//
//			case 3:
//				textureArray[1] = loadTexture("dirt.bmp");
//				handleg();
//				glDeleteTextures(1, &textureArray[1]);// This function is called to free the texture name.
//				break;
//
//			case 4:
//				textureArray[2] = loadTexture("fire.bmp");
//				handleg();
//				glDeleteTextures(1, &textureArray[2]);// This function is called to free the texture name.
//				break;
//
//			case 5:
//				textureArray[3] = loadTexture("ice.bmp");
//				handleg();
//				glDeleteTextures(1, &textureArray[3]);// This function is called to free the texture name.
//				break;
//
//			case 6:
//				textureArray[4] = loadTexture("purple.bmp");
//				handleg();
//				glDeleteTextures(1, &textureArray[4]);// This function is called to free the texture name.
//				break;
//			case 7:
//				textureArray[5] = loadTexture("green.bmp");
//				handleg();
//				glDeleteTextures(1, &textureArray[5]);// This function is called to free the texture name.
//				break;
//			case 8:
//				textureArray[6] = loadTexture("water.bmp");
//				handleg();
//				glDeleteTextures(1, &textureArray[6]);// This function is called to free the texture name.
//				break;
//			default:
//				break;
//			}
//			glDisable(GL_TEXTURE_2D);  //This function will disable 2D texture mapping for OpenGL. 
//
//			glPopMatrix();
//		}
//
//		void display()
//		{
//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//			glEnable(GL_DEPTH_TEST);
//
//			projection();
//			glMatrixMode(GL_MODELVIEW);		//refer to modelview matrix
//			glLoadIdentity();
//
//			glPushMatrix();
//			glTranslatef(0, 0, objectZ);
//			bodyTexture();
//			handlegTexture();
//
//			if (walk == true) {
//
//				if (leftHandAngle > 70 && rightHandAngle < -70 && leftRobotLeg < -70 && rightRobotLeg > 70) {
//					//stop
//					returnMovement = true;
//					leftHandAngle -= 0.1;
//					rightHandAngle += 0.1;
//					leftRobotLeg += 0.1;
//					rightRobotLeg -= 0.1;
//				}
//				else {
//					if (leftHandAngle < -70) {
//						returnMovement = false;
//					}
//
//					if (returnMovement) {
//						leftHandAngle -= 0.1;
//						rightHandAngle += 0.1;
//						leftRobotLeg += 0.1;
//						rightRobotLeg -= 0.1;
//					}
//					else {
//						leftHandAngle += 0.1;
//						rightHandAngle -= 0.1;
//						leftRobotLeg -= 0.1;
//						rightRobotLeg += 0.1;
//					}
//
//
//				}
//			}
//
//			glDisable(GL_TEXTURE_2D);  //This function will disable 2D texture mapping for OpenGL.
//
//
//			glPopMatrix();
//		}
