#include "utils.h"
#include "windows.h"
#include <stdio.h>
#include <GL/glut.h>
#include "menu.h"

using namespace GraphUtils;

int button;
int tick = 0;
int tick2 = 0;
int fig = 0;
float z = 0.1;
float zb = 0.1;
bool move, b;
int color = 1;
float distZ = -10;
float distX = -3.5;
float distY = -3;
float angleX = 0;
float angleY = -40;
float mouseX, mouseY;
float width, height;
int mx, my;
int time = 0;
int time2 = 0;
bool finish = false;
int xFrom, yFrom;
int  xTo, yTo;

int arrBoard[8][8] = { { 1,0,1,0,1,0,1,0 },
{ 0,1,0,1,0,1,0,1 },
{ 1,0,1,0,1,0,1,0 },
{ 0,1,0,1,0,1,0,1 },
{ 1,0,1,0,1,0,1,0 },
{ 0,1,0,1,0,1,0,1 },
{ 1,0,1,0,1,0,1,0 },
{ 0,1,0,1,0,1,0,1 } };

/*Figures :
White=1 & Black=2;
pawn=1;
knight=2;
bishop=3;
castle=4
queen=5;
king=6;
*/

int arrFig[8][8] = { { 14,11,0,0,0,0,21,24 },
{ 12,11,0,0,0,0,21,22 },
{ 13,11,0,0,0,0,21,23 },
{ 15,11,0,0,0,0,21,25 },
{ 16,11,0,0,0,0,21,26 },
{ 13,11,0,0,0,0,21,23 },
{ 12,11,0,0,0,0,21,22 },
{ 14,11,0,0,0,0,21,24 } };

// Drawing parallesquares to construct chess board
class board
{
public:
	board() {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (arrBoard[i][j] == 1)
				{
					glMaterialfv(GL_FRONT, GL_AMBIENT, ambiGreen);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffGreen);
					glMaterialfv(GL_FRONT, GL_SPECULAR, specGreen);
					glMaterialf(GL_FRONT, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					GraphUtils::parallesquare(1, 1, 0.1);
					// Recovery the current matrix from stack:
					glPopMatrix();
				}
				if (arrBoard[i][j] == 0)
				{
					glMaterialfv(GL_FRONT, GL_AMBIENT, ambiWhite);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, diffWhite);
					glMaterialfv(GL_FRONT, GL_SPECULAR, specWhite);
					glMaterialf(GL_FRONT, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					GraphUtils::parallesquare(1, 1, 0.1);
					// Recovery the current matrix from stack:
					glPopMatrix();
				}
			}
		}
	}
};

class figures {
public:
	figures()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (arrFig[i][j] == 11)
				{
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specWhite);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					// The cylinder should be located in the vertical direction:

					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glutSolidCone(0.3, 0.9f, 20, 20);
					glTranslatef(0, 0, 0.9f);
					glutSolidSphere(0.12f, 20, 20);
					glTranslatef(0, 0, -0.82);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.09);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					glTranslatef(0, 0, 0.6);
					glutSolidTorus(0.05f, 0.05f, 20, 20);
					gluDeleteQuadric(quadricObj);
					glPopMatrix();
				}
				if (arrFig[i][j] == 21)
				{
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specBlack);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					//Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					//The cylinder should be located in the vertical direction:

					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glutSolidCone(0.3, 0.9f, 20, 20);
					glTranslatef(0, 0, 0.9f);
					glutSolidSphere(0.12f, 20, 20);
					glTranslatef(0, 0, -0.82);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.09);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					glTranslatef(0, 0, 0.6);
					glutSolidTorus(0.05f, 0.05f, 20, 20);
					gluDeleteQuadric(quadricObj);
					glPopMatrix();
				}
				if (arrFig[i][j] == 14)
				{
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specWhite);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					// The cylinder should be located in the vertical direction:
					//GLUquadricObj* quadricObj = gluNewQuadric();
					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.073);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.1);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					gluCylinder(quadricObj, 0.26, 0.26, 0.4, 20, 2);
					// The disk must be drawn up outer facet:
					glTranslatef(0, 0, 0.4);
					glRotatef(180, 1, 0, 0);
					gluDisk(quadricObj, 0, 0.26, 20, 20);
					glTranslatef(0, 0, 0);
					gluCylinder(quadricObj, 0.26, 0.26, 0.05, 20, 20);
					glTranslatef(0, 0, 0);
					gluDisk(quadricObj, 0, 0.36, 20, 20);
					glTranslatef(0, 0, -0.0);
					glRotatef(180, 1, 0, 0);
					gluCylinder(quadricObj, 0.26, 0.26, 0.07, 20, 20);
					glTranslatef(0, 0, 0.07);
					gluDisk(quadricObj, 0.26, 0.36, 20, 20);
					glTranslatef(0, 0, -0.07);
					gluCylinder(quadricObj, 0.36, 0.36, 0.07, 20, 20);
					gluDeleteQuadric(quadricObj);
					glPopMatrix();
				}
				if (arrFig[i][j] == 24)
				{
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specBlack);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					// The cylinder should be located in the vertical direction:
					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.073);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.1);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					gluCylinder(quadricObj, 0.26, 0.26, 0.4, 20, 2);
					// The disk must be drawn up outer facet:
					glTranslatef(0, 0, 0.4);
					glRotatef(180, 1, 0, 0);
					gluDisk(quadricObj, 0, 0.26, 20, 20);
					glTranslatef(0, 0, 0);
					gluCylinder(quadricObj, 0.26, 0.26, 0.05, 20, 20);
					glTranslatef(0, 0, 0);
					gluDisk(quadricObj, 0, 0.36, 20, 20);
					glTranslatef(0, 0, -0.0);
					glRotatef(180, 1, 0, 0);
					gluCylinder(quadricObj, 0.26, 0.26, 0.07, 20, 20);
					glTranslatef(0, 0, 0.07);
					gluDisk(quadricObj, 0.26, 0.36, 20, 20);
					glTranslatef(0, 0, -0.07);
					gluCylinder(quadricObj, 0.36, 0.36, 0.07, 20, 20);
					gluDeleteQuadric(quadricObj);
					glPopMatrix();
				}
				if (arrFig[i][j] == 13)
				{
					// Definition of material properties:
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specWhite);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.073);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.1);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					glutSolidCone(0.26, 0.8f, 20, 20);
					glTranslatef(0, 0, 0.5f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.1f);
					glutSolidCube(0.2f);
					glTranslatef(0, 0, 0.1f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.16f);
					glutSolidSphere(0.15f, 20, 20);
					gluDeleteQuadric(quadricObj);
					glPopMatrix();
				}
				if (arrFig[i][j] == 23)
				{
					// Definition of material properties:
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specBlack);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.073);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.1);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					glutSolidCone(0.26, 0.8f, 20, 20);
					glTranslatef(0, 0, 0.5f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.1f);
					glutSolidCube(0.2f);
					glTranslatef(0, 0, 0.1f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.16f);
					glutSolidSphere(0.15f, 20, 20);
					gluDeleteQuadric(quadricObj);
					glPopMatrix();
				}

				if (arrFig[i][j] == 16)
				{
					// Definition of material properties:
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specWhite);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.073);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.1);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					glutSolidCone(0.26, 0.8f, 20, 20);
					glTranslatef(0, 0, 0.5f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.15f);
					glutSolidSphere(0.15f, 20, 20);
					glTranslatef(0, 0, 0.15f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.14f);
					glutSolidCube(0.2f);
					glutSolidSphere(0.12f, 20, 20);
					glTranslatef(0, 0, 0.14f);
					glutSolidCube(0.07f);
					glTranslatef(0, 0, 0.07f);
					glutSolidCube(0.07f);
					glTranslatef(0, 0, 0.07f);
					glutSolidCube(0.07f);
					glTranslatef(0, 0, 0.07f);
					glutSolidCube(0.07f);
					glTranslatef(0.07, 0, -0.07f);
					glutSolidCube(0.07f);
					glTranslatef(-0.14, 0, 0);
					glutSolidCube(0.07f);
					gluDeleteQuadric(quadricObj);
					glPopMatrix();
				}
				if (arrFig[i][j] == 26)
				{
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specBlack);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);

					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.073);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.1);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					glutSolidCone(0.26, 0.8f, 20, 20);
					glTranslatef(0, 0, 0.5f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.15f);
					glutSolidSphere(0.15f, 20, 20);
					glTranslatef(0, 0, 0.15f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.14f);
					glutSolidCube(0.2f);
					glutSolidSphere(0.12f, 20, 20);
					glTranslatef(0, 0, 0.14f);
					glutSolidCube(0.07f);
					glTranslatef(0, 0, 0.07f);
					glutSolidCube(0.07f);
					glTranslatef(0, 0, 0.07f);
					glutSolidCube(0.07f);
					glTranslatef(0, 0, 0.07f);
					glutSolidCube(0.07f);
					glTranslatef(0.07, 0, -0.07f);
					glutSolidCube(0.07f);
					glTranslatef(-0.14, 0, 0);
					glutSolidCube(0.07f);
					gluDeleteQuadric(quadricObj);
					glPopMatrix();
				}

				if (arrFig[i][j] == 15)
				{
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specWhite);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);

					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.073);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.1);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					glutSolidCone(0.26, 0.8f, 20, 20);
					glTranslatef(0, 0, 0.5f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.15f);
					glutSolidSphere(0.15f, 20, 20);
					glTranslatef(0, 0, 0.15f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.19f);
					glutSolidSphere(0.15f, 20, 20);
					glRotatef(90, 0, 1, 1);
					glutSolidCube(0.25f);

					gluDeleteQuadric(quadricObj);
					glPopMatrix();

				}
				if (arrFig[i][j] == 25)
				{
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specBlack);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.073);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.1);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					glutSolidCone(0.26, 0.8f, 20, 20);
					glTranslatef(0, 0, 0.5f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.15f);
					glutSolidSphere(0.15f, 20, 20);
					glTranslatef(0, 0, 0.15f);
					glutSolidTorus(0.05f, 0.13f, 20, 20);
					glTranslatef(0, 0, 0.19f);
					glutSolidSphere(0.15f, 20, 20);
					glRotatef(90, 0, 1, 1);
					glutSolidCube(0.25f);
					gluDeleteQuadric(quadricObj);
					glPopMatrix();
				}
				if (arrFig[i][j] == 12)
				{
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffWhite);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specWhite);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					glRotatef(90, 0, 0, 1);
					// The cylinder should be located in the vertical direction:
					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.073);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.1);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					glTranslatef(0, -0.03, 0);
					gluCylinder(quadricObj, 0.24, 0.2, 0.6, 20, 20);
					glTranslatef(0, 0.08, 0.2);
					glutSolidSphere(0.25f, 20, 20);
					glTranslatef(0, -0.08, 0.4);
					glutSolidSphere(0.21f, 20, 20);
					glRotatef(110, -1, 0, 0);
					gluCylinder(quadricObj, 0.21, 0.09, 0.42, 20, 20);
					glTranslatef(0, 0, 0.42);
					gluDisk(quadricObj, 0, 0.09, 20, 20);
					gluDeleteQuadric(quadricObj);
					glPopMatrix();
				}
				if (arrFig[i][j] == 22)
				{
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffBlack);
					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specBlack);
					glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, GraphUtils::shininess);
					// Writing the current matrix into stack:
					glPushMatrix();
					glTranslatef(i, j, z);
					glRotatef(180, 0, 0, 1);
					glRotatef(90, 0, 0, 1);
					// The cylinder should be located in the vertical direction:
					GLUquadricObj* quadricObj = gluNewQuadric();
					gluDisk(quadricObj, 0, 0.3, 20, 20);
					glTranslatef(0, 0, 0.05);
					glutSolidTorus(0.05f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.073);
					glutSolidTorus(0.07f, 0.3f, 20, 20);
					glTranslatef(0, 0, 0.1);
					glutSolidTorus(0.04f, 0.26f, 20, 20);
					glTranslatef(0, -0.03, 0);
					gluCylinder(quadricObj, 0.24, 0.2, 0.6, 20, 20);
					glTranslatef(0, 0.08, 0.2);
					glutSolidSphere(0.25f, 20, 20);
					glTranslatef(0, -0.08, 0.4);
					glutSolidSphere(0.21f, 20, 20);
					glRotatef(110, -1, 0, 0);
					gluCylinder(quadricObj, 0.21, 0.09, 0.42, 20, 20);
					glTranslatef(0, 0, 0.42);
					gluDisk(quadricObj, 0, 0.09, 20, 20);

					gluDeleteQuadric(quadricObj);
					glPopMatrix();
				}
			}
		}

	}
};
void on_paint()
{
	char text[128];
	if (finish)
		sprintf_s(text, "Game over.White Won. White: %d Black: %d    Esc - Exit", time, time2);
	else
		sprintf_s(text, "Esc - Exit   ZoomIn-Up ZoomOut-Down   --Time->  White: %d  Black: %d", time, time2);

	glViewport(0, 0, width, height);

	float lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	if (finish)
		glClearColor(0.7, 0.71, 0.7, 1);
	else
		glClearColor(0.6, 0.62, 0.6, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 1, 0, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(0, 0.9, 0.7); // yellow text
	drawString(GLUT_BITMAP_HELVETICA_18, text, 0.01, 0.95);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40, width / height, 1, 100);

	glTranslatef(distX, distY, distZ);
	glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	glRotatef(angleY, 1.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	board br;
	figures fg;
	//board

	//figures

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glFlush();
	glutSwapBuffers();
}
void on_timer(int value)
{
	if (color == 1) {
		tick++;
		if (tick >= 19)
		{
			if (!finish)
				time++;
			tick = 0;
		}
	}
	if (color == 2) {
		tick2++;
		if (tick2 >= 19)
		{
			if (!finish)
				time2++;
			tick2 = 0;
		}
	}
	on_paint();
	glutTimerFunc(25, on_timer, 0);
}
bool findNearest(int x, int y, int& x1, int& y1)
{
	int viewport[4];
	int iMin = 0, jMin = 0;
	double mvMatrix[16], projMatrix[16];
	double minDist = 2000;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			double wx = i;
			double wy = j;
			double wz = 0.1;
			glGetIntegerv(GL_VIEWPORT, viewport);
			glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
			glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

			double dx, dy, dz;
			gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
			dy = viewport[3] - dy - 1; double d = (x - dx) * (x - dx) + (y - dy) * (y - dy); // квадрат відстані
			if (d < minDist)
			{
				minDist = d;
				iMin = i;
				jMin = j;
			}
		}
	}
	if (minDist < 1000)
	{
		x1 = iMin;
		y1 = jMin;
		return true;
	}
	else
		return false;
}
void on_motion(int x, int y)
{
	switch (button)
	{
	case 2: // right button: scene rotation 
			/*    angleX += x - mouseX;
			angleY += y - mouseY;
			mouseX = x;
			mouseY = y;*/
		break;
	}
}
void on_size(int _width, int _height)
{
	width = _width;
	if (height == 0)
		height = 1;
	height = _height;
}
void on_special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (z > 2)
			break;
		z += 0.1;
		zb += 0.1;
		break;
	case GLUT_KEY_DOWN:
		z -= 0.1;
		zb -= 0.1;
		break;


	}

}
void on_mouse(int _button, int state, int x, int y)
{
	if (state == 1) {
		button = -1;
		return;
	}
	switch (button = _button) {
	case 0:
	{
		switch (fig)
		{
		case 0:
		{
			if (findNearest(x, y, xFrom, yFrom))
			{
				if (arrFig[xFrom][yFrom] != 0)
				{
					if (findNearest(x, y, xFrom, yFrom))
					{
						fig = arrFig[xFrom][yFrom];
						mx = xFrom;
						my = yFrom;
					}
				}

			}
			break;
		}
		case 11:
		{
			if (findNearest(x, y, xTo, yTo) && color == 1)
			{
				if (arrFig[xTo][yTo] == 0)
				{
					if (my == 1) {
						if (yTo == yFrom + 1 && xFrom == xTo || yTo == yFrom + 2 && xFrom == xTo) {
							if (findNearest(x, y, xTo, yTo))
							{
								arrFig[xTo][yTo] = fig;
								arrFig[xFrom][yFrom] = 0;
								fig = 0;
								color = 2;
							}
						}
						else
						{
							fig = 0;
						}

					}
					else if (my > 1) {
						if (yTo == yFrom + 1 && xFrom == xTo) {
							if (findNearest(x, y, xTo, yTo))
							{
								arrFig[xTo][yTo] = fig;
								arrFig[xFrom][yFrom] = 0;
								fig = 0;
								color = 2;
							}
						}
						else
						{
							fig = 0;
						}
					}
				}
				else if (arrFig[xTo][yTo] == 21 || arrFig[xTo][yTo] == 22 || arrFig[xTo][yTo] == 23 || arrFig[xTo][yTo] == 24 || arrFig[xTo][yTo] == 25)
				{
					if (xTo == xFrom + 1 && yTo == yFrom + 1 || xTo == xFrom - 1 && yTo == yFrom + 1)
					{
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 2;
					}
				}
				else if (arrFig[xTo][yTo] == 26)
				{

					fig = 0;
				}

			}
			else fig = 0; break; }
		case 21:
		{
			if (findNearest(x, y, xTo, yTo) && color == 2)
			{
				if (arrFig[xTo][yTo] == 0)
				{
					if (yFrom == 6) {
						if (yTo == yFrom - 1 && xFrom == xTo || yTo == yFrom - 2 && xFrom == xTo) {
							if (findNearest(x, y, xTo, yTo))
							{
								arrFig[xTo][yTo] = fig;
								arrFig[xFrom][yFrom] = 0;
								fig = 0;
								color = 1;
							}
						}
						else
						{
							fig = 0;
						}
					}
					else if (yFrom < 6) {
						if (yTo == yFrom - 1 && xFrom == xTo) {
							if (findNearest(x, y, xTo, yTo))
							{
								arrFig[xTo][yTo] = fig;
								arrFig[xFrom][yFrom] = 0;
								fig = 0;
								color = 1;
							}
						}
						else
						{
							fig = 0;
						}
					}
				}
				else if (arrFig[xTo][yTo] == 11 || arrFig[xTo][yTo] == 12 || arrFig[xTo][yTo] == 13 || arrFig[xTo][yTo] == 14 || arrFig[xTo][yTo] == 15)
				{
					if (xTo == xFrom - 1 && yTo == yFrom - 1 || xTo == xFrom + 1 && yTo == yFrom - 1)
					{
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 1;
					}
				}
				else if (arrFig[xTo][yTo] == 16)
				{

					fig = 0;
				}
			}
			else fig = 0;
			break; }
		case 12:
		{
			if (findNearest(x, y, xTo, yTo) && color == 1)
			{
				if (arrFig[xTo][yTo] == 0)
				{

					if (yTo == yFrom + 1 && xTo == xFrom + 2 || yTo == yFrom + 1 && xTo == xFrom - 2 || yTo == yFrom + 2 && xTo == xFrom - 1 || yTo == yFrom + 2 && xTo == xFrom + 1 || yTo == yFrom - 1 && xTo == xFrom + 2 || yTo == yFrom - 1 && xTo == xFrom - 2 || yTo == yFrom - 2 && xTo == xFrom - 1 || yTo == yFrom - 2 && xTo == xFrom + 1) {
						if (findNearest(x, y, xTo, yTo))
						{
							arrFig[xTo][yTo] = fig;
							arrFig[xFrom][yFrom] = 0;
							fig = 0;
							color = 2;
						}
					}
					else
					{
						fig = 0;
					}

				}
				else if (arrFig[xTo][yTo] == 21 || arrFig[xTo][yTo] == 22 || arrFig[xTo][yTo] == 23 || arrFig[xTo][yTo] == 24 || arrFig[xTo][yTo] == 25)
				{
					if (yTo == yFrom + 1 && xTo == xFrom + 2 || yTo == yFrom + 1 && xTo == xFrom - 2 || yTo == yFrom + 2 && xTo == xFrom - 1 || yTo == yFrom + 2 && xTo == xFrom + 1 || yTo == yFrom - 1 && xTo == xFrom + 2 || yTo == yFrom - 1 && xTo == xFrom - 2 || yTo == yFrom - 2 && xTo == xFrom - 1 || yTo == yFrom - 2 && xTo == xFrom + 1)
					{
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 2;
					}
				}
				else if (arrFig[xTo][yTo] == 26)
				{

					fig = 0;
				}
				else fig = 0;
			}
			else fig = 0; break; }
		case 22:
		{
			if (findNearest(x, y, xTo, yTo) && color == 2)
			{
				if (arrFig[xTo][yTo] == 0)
				{

					if (yTo == yFrom + 1 && xTo == xFrom + 2 || yTo == yFrom + 1 && xTo == xFrom - 2 || yTo == yFrom + 2 && xTo == xFrom - 1 || yTo == yFrom + 2 && xTo == xFrom + 1 || yTo == yFrom - 1 && xTo == xFrom + 2 || yTo == yFrom - 1 && xTo == xFrom - 2 || yTo == yFrom - 2 && xTo == xFrom - 1 || yTo == yFrom - 2 && xTo == xFrom + 1) {
						if (findNearest(x, y, xTo, yTo))
						{
							arrFig[xTo][yTo] = fig;
							arrFig[xFrom][yFrom] = 0;
							fig = 0;
							color = 1;
						}
					}
					else
					{
						fig = 0;
					}

				}
				else if (arrFig[xTo][yTo] == 11 || arrFig[xTo][yTo] == 12 || arrFig[xTo][yTo] == 13 || arrFig[xTo][yTo] == 14 || arrFig[xTo][yTo] == 15)
				{
					if (yTo == yFrom + 1 && xTo == xFrom + 2 || yTo == yFrom + 1 && xTo == xFrom - 2 || yTo == yFrom + 2 && xTo == xFrom - 1 || yTo == yFrom + 2 && xTo == xFrom + 1 || yTo == yFrom - 1 && xTo == xFrom + 2 || yTo == yFrom - 1 && xTo == xFrom - 2 || yTo == yFrom - 2 && xTo == xFrom - 1 || yTo == yFrom - 2 && xTo == xFrom + 1)
					{
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 1;
					}
				}
				else if (arrFig[xTo][yTo] == 16)
				{

					fig = 0;
				}
				else fig = 0;
			}
			else fig = 0; break; }
		case 13:
		{
			if (findNearest(x, y, xTo, yTo) && color == 1)
			{

				if (arrFig[xTo][yTo] == 0)
				{
					if (xTo - xFrom == yTo - yFrom || xFrom - xTo == yFrom - yTo || xTo - xFrom == yFrom - xTo || xTo - xFrom == yFrom - yTo) {
						if (arrFig[xTo][yTo] == 0)
						{
							color = 2;
							arrFig[xTo][yTo] = fig;
							arrFig[xFrom][yFrom] = 0;
							fig = 0;
						}
					}
					else {
						fig = 0;
					}
				}
				else if (arrFig[xTo][yTo] == 21 || arrFig[xTo][yTo] == 22 || arrFig[xTo][yTo] == 23 || arrFig[xTo][yTo] == 24 || arrFig[xTo][yTo] == 25)
				{
					if (xTo - xFrom == yTo - yFrom || xFrom - xTo == yFrom - yTo || xTo - xFrom == yFrom - xTo || xTo - xFrom == yFrom - yTo) {
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 2;
					}
				}
				else if (arrFig[xTo][yTo] == 26)
				{

					fig = 0;
				}
				else fig = 0;
			}
			else fig = 0; break; }
		case 23:
		{
			if (findNearest(x, y, xTo, yTo) && color == 2)
			{

				if (arrFig[xTo][yTo] == 0)
				{
					if (xTo - xFrom == yTo - yFrom || xFrom - xTo == yFrom - yTo || xTo - xFrom == yFrom - xTo || xTo - xFrom == yFrom - yTo) {
						if (arrFig[xTo][yTo] == 0)
						{
							color = 1;
							arrFig[xTo][yTo] = fig;
							arrFig[xFrom][yFrom] = 0;
							fig = 0;
						}
					}
					else {
						fig = 0;
					}
				}
				else if (arrFig[xTo][yTo] == 11 || arrFig[xTo][yTo] == 12 || arrFig[xTo][yTo] == 13 || arrFig[xTo][yTo] == 14 || arrFig[xTo][yTo] == 15)
				{
					if (xTo - xFrom == yTo - yFrom || xFrom - xTo == yFrom - yTo || xTo - xFrom == yFrom - xTo || xTo - xFrom == yFrom - yTo) {
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 1;
					}
				}
				else if (arrFig[xTo][yTo] == 16)
				{

					fig = 0;
				}
				else fig = 0;
			}
			else fig = 0; break; }

		case 14:
		{
			if (findNearest(x, y, xTo, yTo) && color == 1)
			{
				if (arrFig[xTo][yTo] == 0)
				{
					if (xTo == xFrom || yFrom == yTo) {
						if (arrFig[xTo][yTo] == 0)
						{
							arrFig[xTo][yTo] = fig;
							arrFig[xFrom][yFrom] = 0;
							fig = 0;
							color = 2;
						}
					}
					else {
						fig = 0;
					}
				}
				else if (arrFig[xTo][yTo] == 21 || arrFig[xTo][yTo] == 22 || arrFig[xTo][yTo] == 23 || arrFig[xTo][yTo] == 24 || arrFig[xTo][yTo] == 25)
				{
					if (xTo == xFrom || yFrom == yTo) {
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 2;
					}
				}
				else if (arrFig[xTo][yTo] == 26)
				{

					fig = 0;
				}
				else fig = 0;
			}
			else fig = 0; break; }
		case 24:
		{
			if (findNearest(x, y, xTo, yTo) && color == 2)
			{
				if (arrFig[xTo][yTo] == 0)
				{
					if (xTo == xFrom || yFrom == yTo) {
						if (arrFig[xTo][yTo] == 0)
						{
							arrFig[xTo][yTo] = fig;
							arrFig[xFrom][yFrom] = 0;
							fig = 0;
							color = 1;
						}
					}
					else {
						fig = 0;
					}
				}
				else if (arrFig[xTo][yTo] == 11 || arrFig[xTo][yTo] == 12 || arrFig[xTo][yTo] == 13 || arrFig[xTo][yTo] == 14 || arrFig[xTo][yTo] == 15)
				{
					if (xTo == xFrom || yFrom == yTo) {
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 1;
					}
				}
				else if (arrFig[xTo][yTo] == 16)
				{

					fig = 0;
				}
				else fig = 0;
			}
			else fig = 0; break; }
		case 15:
		{
			if (findNearest(x, y, xTo, yTo) && color == 1)
			{
				if (arrFig[xTo][yTo] == 0)
				{
					if (xTo == xFrom || yFrom == yTo || xTo - xFrom == yTo - yFrom || xFrom - xTo == yFrom - yTo || xTo - xFrom == yFrom - xTo || xTo - xFrom == yFrom - yTo) {
						if (arrFig[xTo][yTo] == 0)
						{
							arrFig[xTo][yTo] = fig;
							arrFig[xFrom][yFrom] = 0;
							fig = 0;
							color = 2;
						}
					}
					else {
						fig = 0;
					}
				}
				else if (arrFig[xTo][yTo] == 21 || arrFig[xTo][yTo] == 22 || arrFig[xTo][yTo] == 23 || arrFig[xTo][yTo] == 24 || arrFig[xTo][yTo] == 25)
				{
					if (xTo == xFrom || yFrom == yTo || xTo - xFrom == yTo - yFrom || xFrom - xTo == yFrom - yTo || xTo - xFrom == yFrom - xTo || xTo - xFrom == yFrom - yTo) {
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 2;
					}
				}
				else if (arrFig[xTo][yTo] == 26)
				{

					fig = 0;
				}
				else fig = 0;
			}
			else fig = 0; break; }
		case 25:
		{
			if (findNearest(x, y, xTo, yTo) && color == 2)
			{
				if (arrFig[xTo][yTo] == 0)
				{
					if (xTo == xFrom || yFrom == yTo || xTo - xFrom == yTo - yFrom || xFrom - xTo == yFrom - yTo || xTo - xFrom == yFrom - xTo || xTo - xFrom == yFrom - yTo) {
						if (arrFig[xTo][yTo] == 0)
						{
							arrFig[xTo][yTo] = fig;
							arrFig[xFrom][yFrom] = 0;
							fig = 0;
							color = 1;
						}
					}
					else {
						fig = 0;
					}
				}
				else if (arrFig[xTo][yTo] == 11 || arrFig[xTo][yTo] == 12 || arrFig[xTo][yTo] == 13 || arrFig[xTo][yTo] == 14 || arrFig[xTo][yTo] == 15)
				{
					if (xTo == xFrom || yFrom == yTo || xTo - xFrom == yTo - yFrom || xFrom - xTo == yFrom - yTo || xTo - xFrom == yFrom - xTo || xTo - xFrom == yFrom - yTo) {
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 1;
					}
				}
				else if (arrFig[xTo][yTo] == 16)
				{

					fig = 0;
				}
				else fig = 0;
			}
			else fig = 0; break; }
		case 16:
		{
			if (findNearest(x, y, xTo, yTo) && color == 1)
			{
				if (arrFig[xTo][yTo] == 0)
				{
					if (xTo == xFrom&&yFrom + 1 || xTo == xFrom&&yFrom - 1 || yFrom == yTo&&xFrom + 1 || yFrom == yTo&&xFrom - 1 || xFrom + 1 && yFrom + 1 || xFrom + 1 && yFrom - 1 || xFrom - 1 && yFrom + 1 || xFrom - 1 && yFrom - 1) {
						if (arrFig[xTo][yTo] == 0)
						{
							arrFig[xTo][yTo] = fig;
							arrFig[xFrom][yFrom] = 0;
							fig = 0;
							color = 2;
						}
					}
					else {
						fig = 0;
					}
				}
				else if (arrFig[xTo][yTo] == 21 || arrFig[xTo][yTo] == 22 || arrFig[xTo][yTo] == 23 || arrFig[xTo][yTo] == 24 || arrFig[xTo][yTo] == 25)
				{
					if (xTo == xFrom&&yFrom + 1 || xTo == xFrom&&yFrom - 1 || yFrom == yTo&&xFrom + 1 || yFrom == yTo&&xFrom - 1 || xFrom + 1 && yFrom + 1 || xFrom + 1 && yFrom - 1 || xFrom - 1 && yFrom + 1 || xFrom - 1 && yFrom - 1) {
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 2;
					}
				}
				else if (arrFig[xTo][yTo] == 26)
				{

					fig = 0;
				}
				else fig = 0;
			}
			else fig = 0; break; }

		case 26:
		{
			if (findNearest(x, y, xTo, yTo) && color == 2)
			{
				if (arrFig[xTo][yTo] == 0)
				{
					if (xTo == xFrom&&yFrom + 1 || xTo == xFrom&&yFrom - 1 || yFrom == yTo&&xFrom + 1 || yFrom == yTo&&xFrom - 1 || xFrom + 1 && yFrom + 1 || xFrom + 1 && yFrom - 1 || xFrom - 1 && yFrom + 1 || xFrom - 1 && yFrom - 1) {
						if (arrFig[xTo][yTo] == 0)
						{
							arrFig[xTo][yTo] = fig;
							arrFig[xFrom][yFrom] = 0;
							fig = 0;
							color = 1;
						}
					}
					else {
						fig = 0;
					}
				}
				else if (arrFig[xTo][yTo] == 11 || arrFig[xTo][yTo] == 12 || arrFig[xTo][yTo] == 13 || arrFig[xTo][yTo] == 14 || arrFig[xTo][yTo] == 15)
				{
					if (xTo == xFrom&&yFrom + 1 || xTo == xFrom&&yFrom - 1 || yFrom == yTo&&xFrom + 1 || yFrom == yTo&&xFrom - 1 || xFrom + 1 && yFrom + 1 || xFrom + 1 && yFrom - 1 || xFrom - 1 && yFrom + 1 || xFrom - 1 && yFrom - 1) {
						arrFig[xTo][yTo] = fig;
						arrFig[xFrom][yFrom] = 0;
						fig = 0;
						color = 1;
					}
				}
				else if (arrFig[xTo][yTo] == 16)
				{

					fig = 0;
				}
				else fig = 0;
			}
			else fig = 0; break; }
		}}
	}
}
void on_keyboard(unsigned char key, int x, int y)
{
	// Handling events from the keyboard:
	if (key == 27) {
		exit(EXIT_SUCCESS);
	}
	if (key == 'x' || key == 'X')
	{
		if (color == 1)
		{
			distZ = -10;
			distX = -3.5;
			distY = -3;
			angleX = 0;
			angleY = -40;
		}
		else if (color == 2)
		{
			distZ = -15;
			distX = 3.5;
			distY = 2.5;
			angleX = 180;
			angleY = 220;
		}
	}
}
int main(int argc, char* argv[])
{
	for (;;) {
		menu ch;
		int choice = ch.c;
		switch (choice) {
		case 1: {
			glutInit(&argc, argv);
			glutInitWindowSize(1024, 768);
			glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
			glutCreateWindow("Chess Game © Berk Arslan");
			glutDisplayFunc(on_paint);
			glutReshapeFunc(on_size);
			glutMotionFunc(on_motion);
			glutMouseFunc(on_mouse);
			glutKeyboardFunc(on_keyboard);
			glutSpecialFunc(on_special);
			glutIdleFunc(on_paint);
			glutTimerFunc(25, on_timer, 0);
			glutMainLoop();
			break; }
		case 2:
		{
			ch.play();
			cin.get();
			system("CLS");
			menu::menu();
			break;
		}
		case 3:
			exit(0);
		}
	}
}