#include<windows.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string>
#include <bits/stdc++.h>

#define PI 3.1416

///Global Variable
int score = 0;
bool gameover = false;
char a[100] = "Game over, score:";
float boundary = 50; /// Scene boundary
float border = 40;   /// Game boundary

///Agent 1 Parameters
float RAgent = 6.0;
float CAgentX = -20, CAgentY = 0;
bool isAgentDestroyed = false;
float agentSpeed = 0.5;

///Agent 1 Parameters
float CAgentBX = 20, CAgentBY = 0;
bool isAgentBDestroyed = false;
float agentBSpeed = 0.5;

///Enemy 1 Parameters
float REnemy = 4.0;
float CEnemyX = -border, CEnemyY = 0.0;
int state = 1;
float enemySpeed = 0.001;

///Enemy 2 Parameters
float CEnemyBX = border, CEnemyBY = -border;
int stateB = 1;
float enemyBSpeed = 0.001;

void circle(float radius_x, float radius_y)
{
	int i=0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex2f (cos(angle) * radius_x, sin(angle) * radius_y);
			//glVertex2f (cos(angle) * radius_x+5, sin(angle) * radius_y);
		}

	glEnd();
}

void Sprint( int x, int y, char *st)
{
	int l,i;

	l=strlen( st );
	glRasterPos3i( x, y, -1);
	for( i=0; i < l; i++)
		{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
	}
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-border, border);
        glVertex2f(border, border);
        glVertex2f(border, -border);
        glVertex2f(-border, -border);
        glVertex2f(-border, border);
    glEnd();

    if(!isAgentDestroyed)
    {
        glPushMatrix();             //Green Circle
        glTranslatef(CAgentX, CAgentY,0);
        glColor3f(0.0, 1.0, 0.0);
        circle(RAgent,RAgent);
        glPopMatrix();
    }

    if(!isAgentBDestroyed)
    {
        glPushMatrix();             //Green Circle
        glTranslatef(CAgentBX, CAgentBY,0);
        glColor3f(0.0, 1.0, 0.0);
        circle(RAgent,RAgent);
        glPopMatrix();
    }

    //Enemy A
    glPushMatrix();             //Red circle (Static)
    glTranslatef(CEnemyX, CEnemyY,0);
    glColor3f(1.0, 0.0, 0.0);
    circle(REnemy,REnemy);
    glPopMatrix();

    //Enemy B
    glPushMatrix();             //Red circle (Static)
    glTranslatef(CEnemyBX, CEnemyBY,0);
    glColor3f(1.0, 0.0, 0.0);
    circle(REnemy,REnemy);
    glPopMatrix();
    if(gameover)
    {
        Sprint(-20,0, a);
        char num_str[10];
        sprintf(num_str, "%d", score); // convert the number to a string
        for (int i = 0; i < strlen(num_str); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, num_str[i]);
        }
    }

    glFlush();
}

void animate()
{
    if(!gameover)
    {
        score++;

        ///Enemy A Movement
        if(state == 1)
        {
            CEnemyX += enemySpeed;
            CEnemyY += enemySpeed;

            if(CEnemyX>0 && CEnemyY>border)
            {
                state = 2;
            }
        }
        else if(state == 2)
        {
            CEnemyY -= enemySpeed;

            if(CEnemyY<-border)
            {
                state = 3;
            }
        }
        else if(state == 3)
        {
            CEnemyX += enemySpeed;
            CEnemyY += enemySpeed;

            if(CEnemyX>border && CEnemyY>0)
            {
                state = 4;
            }

        }
        else if(state == 4){

            CEnemyX -= enemySpeed;
            if(CEnemyX<-border)
            {
                state = 1;
            }
        }

        ///Enemy B Movement
        if(stateB == 1)
        {
            CEnemyBX -= enemySpeed;
            CEnemyBY += enemySpeed;

            if(CEnemyBX<-border && CEnemyBY>border)
            {
                stateB = 2;
            }
        }
        else if(stateB == 2)
        {
            CEnemyBX += enemySpeed;
            CEnemyBY -= (enemySpeed/2);

            if(CEnemyBX>border &&CEnemyBY<0)
            {
                stateB = 3;
            }
        }
        else if(stateB == 3)
        {
            CEnemyBX -= (enemySpeed/2);
            CEnemyBY += (enemySpeed/2);

            if(CEnemyBX<0 && CEnemyBY>border)
            {
                stateB = 4;
            }

        }
        else if(stateB == 4){

            CEnemyBX += (enemySpeed/2);
            CEnemyBY -= enemySpeed;

            if(CEnemyBX>border && CEnemyBY<-border)
            {
                stateB = 1;
            }
        }

        ///Attack Logic of agent A
        float distanceAWithA = sqrt((CAgentX-CEnemyX)*(CAgentX-CEnemyX) + (CAgentY-CEnemyY)*(CAgentY-CEnemyY));
        float distanceAWithB = sqrt((CAgentX-CEnemyBX)*(CAgentX-CEnemyBX) + (CAgentY-CEnemyBY)*(CAgentY-CEnemyBY));

        ///Attack Logic of agent B
        float distanceBWithA = sqrt((CAgentBX-CEnemyX)*(CAgentBX-CEnemyX) + (CAgentBY-CEnemyY)*(CAgentBY-CEnemyY));
        float distanceBWithB = sqrt((CAgentBX-CEnemyBX)*(CAgentBX-CEnemyBX) + (CAgentBY-CEnemyBY)*(CAgentBY-CEnemyBY));

        if(distanceAWithA <= RAgent+REnemy || distanceAWithB <= RAgent+REnemy)
        {
            isAgentDestroyed = true;
            isAgentBDestroyed = true;
            gameover = true;
        }
        if(distanceBWithA <= RAgent+REnemy || distanceBWithB <= RAgent+REnemy)
        {
            isAgentDestroyed = true;
            isAgentBDestroyed = true;
            gameover = true;
        }
        }else{
                //glutPostRedisplay();
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1.0,1.0,1.0);
            Sprint(0,0, "Hello");
            glutPostRedisplay();
    }
    glutPostRedisplay();
}
void getStringRepxn()
{
    glRasterPos2d(50,180);
    for(int i=0;i<15;i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, a[i]);
    }
    glFlush();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-boundary, boundary, -boundary, boundary, -boundary, boundary);
}


void spe_key(int key, int x, int y)
{

	switch (key) {

		case GLUT_KEY_LEFT:
                CAgentX -= agentSpeed;

                if(CAgentX<0 && -CAgentX>border-RAgent)
                {
                    isAgentDestroyed = true;
                    gameover = true;
                }
				glutPostRedisplay();
				break;

		case GLUT_KEY_RIGHT:
                CAgentX += agentSpeed;

                if(CAgentX>0 && CAgentX>border-RAgent)
                {
                    isAgentDestroyed = true;
                    gameover = true;
                }
				glutPostRedisplay();
				break;

        case GLUT_KEY_DOWN:
                CAgentY -= agentSpeed;
                if(CAgentY<0 && -CAgentY>border - RAgent)
                {
                    isAgentDestroyed = true;
                    gameover = true;
                }
				glutPostRedisplay();
				break;

		case GLUT_KEY_UP:
                CAgentY += agentSpeed;
                if(CAgentY>0 && CAgentY>border-RAgent)
                {
                    isAgentDestroyed = true;
                    gameover = true;
                }
				glutPostRedisplay();
				break;
	  default:
			break;
	}
}

void keyboard_action(unsigned char key, int x, int y)
{
    if(key == 'u')
    {
        CAgentBY += agentSpeed;
        if(CAgentBY>0 && CAgentBY>border-RAgent)
        {
            isAgentBDestroyed = true;
            gameover = true;
        }
        glutPostRedisplay();

    }
    else if(key == 'd')
    {
        CAgentBY -= agentSpeed;
        if(CAgentBY<0 && -CAgentBY>border - RAgent)
        {
            isAgentBDestroyed = true;
            gameover = true;
        }
        glutPostRedisplay();
    }
    else if(key == 'l')
    {
        CAgentBX -= agentSpeed;

        if(CAgentBX<0 && -CAgentBX>border-RAgent)
        {
            isAgentBDestroyed = true;
            gameover = true;
        }
        glutPostRedisplay();
    }
    else if(key == 'r')
    {
        CAgentBX += agentSpeed;
        if(CAgentBX>0 && CAgentBX>border-RAgent)
        {
            isAgentBDestroyed = true;
            gameover = true;
        }
        glutPostRedisplay();
    }
}

void mouse_action(int button,int state,int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        glutPostRedisplay();
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        glutPostRedisplay();
    }
    else if(button == GLUT_MIDDLE_BUTTON)
    {
        glutPostRedisplay();
    }
}


int main()
{
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Circle");
	init();
	glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(keyboard_action);
    glutMouseFunc(mouse_action);
	glutMainLoop();
	return 0;
}
