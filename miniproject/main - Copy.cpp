
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define LIGHT_ON 0
#define LIGHT_OFF 1
int pos[16] = {10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85};
int peg[3] = {50,150,250};
int moves[10000][3];
int max_moves;
int POLES[3][10];
int top[3] = {-1,-1,-1};
int NUM_DISKS = 1;
int cnt,counter,speed = 10;
int line1 = 90,line2 = 85;
float ycoordinate;
int lightflag = 1,animationFlag = 1;

void push(int p,int disk)
{
	POLES[p][++top[p]] = disk;
}

void pop(int p)
{
	top[p]--;
}

void tower(int n,int src,int temp,int dst)
{
	if(n > 0)
	{
		tower(n - 1,src,dst,temp);
		moves[cnt][0] = n;
		moves[cnt][1] = src;
		moves[cnt][2] = dst;
		cnt++;
		tower(n - 1,temp,src,dst);
	}
}

void drawPegs()
{
	int i;
	glColor3f(0.5,0.0,0.1);
	for(i = 0;i < 3;i++)
	{
		glPushMatrix();
		glTranslatef(peg[i],5,0);
		glRotatef(-90,1,0,0);
		glutSolidCone(2,70,20,20);
		glutSolidTorus(2,45, 20, 20);
		glPopMatrix();
	}

}

void printString(char *text)
{
	int len = strlen(text),i;
	for(i = 0;i < len;i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[i]);
}

void drawText()
{
	glColor3f(1,1,1);
	glRasterPos3f(-70,line1,0);
	printString("Move :");
	char str[5];
	sprintf(str, "%d", counter);
	glRasterPos3f(-40,line1,0);
	printString(str);
	glRasterPos3f(-70,line2,0);
	printString("Disk");
	char str1[10];
	sprintf(str1, "%d", moves[counter][0]);
	glRasterPos3f(-50,line2,0);
	printString(str1);
	glRasterPos3f(-40,line2,0);
	printString("from");
	char src[2];
	if(moves[counter][1] == 0)
        strcpy(src,"A");
	else if(moves[counter][1] == 1)
        strcpy(src,"B");
	else
        strcpy(src,"C");
	glRasterPos3f(-20,line2,0);
	printString(src);
	glRasterPos3f(-10,line2,0);
	printString("to");
	char dst[2];
	if(moves[counter][2] == 0)
        strcpy(dst,"A");
	else if(moves[counter][2] == 1)
        strcpy(dst,"B");
	else
        strcpy(dst,"C");
	glRasterPos3f(0,line2,0);
	printString(dst);
	glColor3f(0,0,0.5);
	glBegin(GL_POLYGON);
		glVertex3f(-75,93,-5);
		glVertex3f(-75,83,-5);
		glVertex3f(10,83,-5);
		glVertex3f(10,93,-5);
	glEnd();
	glColor3f(1,0,0);
	glRasterPos3f(peg[0],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'A');
	glRasterPos3f(peg[1],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'B');
	glRasterPos3f(peg[2],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'C');
}

void drawSolved()
{
	glColor3f(1,1,0);
	glRasterPos3f(-45,line1,0);
	printString("Solved!\n");
	glRasterPos3f(-60,85,0);
	printString("Total Moves: ");
	char fstr[5];
	sprintf(fstr,"%d",max_moves);
	glRasterPos3f(-10,85,0);
	printString(fstr);
	glColor3f(0,0,0.5);
	glBegin(GL_POLYGON);
		glVertex3f(-75,93,-5);
		glVertex3f(-75,83,-5);
		glVertex3f(10,83,-5);
		glVertex3f(10,93,-5);
	glEnd();
	glColor3f(1,0,0);
	glRasterPos3f(peg[0],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'A');
	glRasterPos3f(peg[1],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'B');
	glRasterPos3f(peg[2],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'C');
}

void display()
{
	int i,j,k;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(lightflag)
        glEnable(GL_LIGHTING);
	glPushMatrix();
	gluLookAt(0,ycoordinate,0,0,0,-1,0,1,0);
	drawPegs();
	for(i = 0;i < 3;i++)
	{
		k = 0;
		for(j = 0;j <= top[i];j++)
		{
			glPushMatrix();
			glTranslatef(peg[i],pos[k++],0);
			glRotatef(90,1,0,0);
			glColor3f(0.1 * POLES[i][j],0.2 * POLES[i][j],0);
			glutSolidTorus(2.0, 4 * POLES[i][j], 20, 20);
			glPopMatrix();
		}
	}
	glPopMatrix();
	glDisable(GL_LIGHTING);
	if(counter == max_moves)
		drawSolved();
	else
		drawText();
	if(lightflag)
        glEnable(GL_LIGHTING);
	glutSwapBuffers();
}


void lighting()
{
	GLfloat shininess[] = {50};
	GLfloat white[] = {0.6,0.6,0.6,1};
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[] = {100,60, 10, 0.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);
}

void init()
{
	glClearColor(0.0,0.0,0.0,0);
	glColor3f(1,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-80,350,-10,100,-100,100);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	lighting();
}

void animate(int n,int src,int dest)
{
	int i;
	if(speed <= 0)
        speed = 1;
	for(i = pos[top[src] + 1];i < 90;i += speed)
	{
		glPushMatrix();
		glTranslatef(peg[src],i,0);
		glRotatef(85,1,0,0);
		glColor3f(0.1 * n,0.2 * n,0);
		glutSolidTorus(2.0, 4 * n, 20, 20);
		glPopMatrix();
		glutSwapBuffers();
		display();
	}
	if(peg[src] < peg[dest])
		for(i = peg[src];i <= peg[dest];i += speed)
		{
			glPushMatrix();
			glTranslatef(i,90,0);
			glRotatef(85,1,0,0);
			glColor3f(0.1 * n,0.2 * n,0);
			glutSolidTorus(2.0, 4 * n, 20, 20);
			glPopMatrix();
			glutSwapBuffers();
			display();
		}
	else
		for(i = peg[src];i >= peg[dest];i -= speed)
		{
			glPushMatrix();
			glTranslatef(i,90,0);
			glRotatef(85,1,0,0);
			glColor3f(0.1 * n,0.2 * n,0);
			glutSolidTorus(2.0, 4 * n, 20, 20);
			glPopMatrix();
			glutSwapBuffers();
			display();
		}
	for(i = 70;i > pos[top[dest] + 1];i -= speed)
	{
		glPushMatrix();
		glTranslatef(peg[dest],i,0);
		glRotatef(85,1,0,0);
		glColor3f(0.1*n,0.2*n,0);
		glutSolidTorus(2.0, 4*n, 20, 20);
		glPopMatrix();
		glutSwapBuffers();
		display();
	}
}

void mouse(int btn,int mode,int x,int y)
{
	if(btn == 4 && mode == GLUT_DOWN)
	{
		if(counter < max_moves)
		{
			pop(moves[counter][1]);
			if(animationFlag)
				animate(moves[counter][0],moves[counter][1],moves[counter][2]);
			push(moves[counter][2],moves[counter][0]);
			counter++;
		}
	}
	if(btn == 3 && mode == GLUT_DOWN)
	{
		if(counter > 0)
		{
			counter--;
			pop(moves[counter][2]);
			if(animationFlag)
				animate(moves[counter][0],moves[counter][2],moves[counter][1]);
			push(moves[counter][1],moves[counter][0]);
		}
	}
	glutPostRedisplay();
}

void restart()
{
	int i;
	memset(POLES,0,sizeof(POLES));
	memset(moves,0,sizeof(POLES));
	memset(top,-1,sizeof(top));
	cnt = 0, counter = 0;
	ycoordinate = 0.1;
	max_moves = pow(2,NUM_DISKS) - 1;
	for(i = NUM_DISKS;i > 0;i--)
	{
		push(0,i);
	}
	tower(NUM_DISKS,0,1,2);
}

void processMenuLighting(int option)
{
	switch(option)
	{
		case LIGHT_OFF:
			glDisable(GL_LIGHTING);
			lightflag = 0;
            break;
		case LIGHT_ON:
			glEnable(GL_LIGHTING);
			lightflag = 1;
            break;
	}
	glutPostRedisplay();
}
void processMenuMain2(int option)
{

}
void processMenuCamera(int option)
{
	switch(option)
	{
		case 0: ycoordinate += 0.2; break;
		case 1: ycoordinate += 0.1; break;
		case 2: ycoordinate -= 0.1; break;
		case 3: ycoordinate -= 0.2; break;
	}
	glutPostRedisplay();
}

void processMenuRestart(int option)
{
	if(option == 0)
	{
		restart();
		glutPostRedisplay();
	}
}

void processMenuExit(int option)
{
	if(option == 0)
        exit(0);
}

void processMenuAnimate(int option)
{
	switch(option)
	{
		case 0:
			animationFlag = 1;
            break;
		case 1:
			animationFlag = 0;
	}
}

void processMenuSolveCompletely(int option)
{
	int temp = animationFlag;
	animationFlag = 0;
	float i, j;
	while(counter < max_moves)
	{
		mouse(4,GLUT_DOWN,0,0);
		display();
		for(i = 0;i < 100000;i = i + 0.1)
			for(j = 0;j < 100;j = j + 0.1);
	}
	animationFlag = temp;
}

void processMenuBgColor(int option)
{
	switch(option)
	{
		case 0: glClearColor(0,0,0,0); break;
		case 1: glClearColor(1,1,1,0); break;
		case 2: glClearColor(1,0,0,0); break;
		case 3: glClearColor(0,1,0,0); break;
		case 4: glClearColor(0,0,1,0); break;
		case 5: glClearColor(0,1,1,0); break;
		case 6: glClearColor(1,0,1,0); break;
		case 7: glClearColor(1,1,0,0); break;
		case 8: glClearColor(1,0.65,0,0); break;
		case 9: glClearColor(0.63,0.13,0.94,0); break;
	}
	glutPostRedisplay();
}

void processMenuNumDisks(int option)
{
	NUM_DISKS = option;
	restart();
	glutPostRedisplay();
}

void processMenuMain1(int option)
{
}

void createGLUTMenus2()
{
	int menu = glutCreateMenu(processMenuLighting);
	glutAddMenuEntry("On",LIGHT_ON);
	glutAddMenuEntry("Off",LIGHT_OFF);
	int menuExit = glutCreateMenu(processMenuExit);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);
    int menuDisks = glutCreateMenu(processMenuNumDisks);
	glutAddMenuEntry("1",1);
	glutAddMenuEntry("2",2);
	glutAddMenuEntry("3",3);
	glutAddMenuEntry("4",4);
	glutAddMenuEntry("5",5);
	glutAddMenuEntry("6",6);
	glutAddMenuEntry("7",7);
	glutAddMenuEntry("8",8);
	glutAddMenuEntry("9",9);
	glutAddMenuEntry("10",10);
	glutCreateMenu(processMenuMain1);
	int menuCamera = glutCreateMenu(processMenuCamera);
	glutAddMenuEntry("+0.2",0);
	glutAddMenuEntry("+0.1",1);
	glutAddMenuEntry("-0.1",2);
	glutAddMenuEntry("-0.2",3);
	int menuRestart = glutCreateMenu(processMenuRestart);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);
	int menuAnimate = glutCreateMenu(processMenuAnimate);
	glutAddMenuEntry("On",0);
	glutAddMenuEntry("Off",1);
	int menuBgColor = glutCreateMenu(processMenuBgColor);
	glutAddMenuEntry("Black",0);
	glutAddMenuEntry("White",1);
	glutAddMenuEntry("Red",2);
	glutAddMenuEntry("Green",3);
	glutAddMenuEntry("Blue",4);
	glutAddMenuEntry("Cyan",5);
	glutAddMenuEntry("Magenta",6);
	glutAddMenuEntry("Yellow",7);
	glutAddMenuEntry("Orange",8);
    glutAddMenuEntry("Purple",9);
	int menuSolveCompletely = glutCreateMenu(processMenuSolveCompletely);
	glutAddMenuEntry("Start",0);
	glutCreateMenu(processMenuMain2);
	glutAddSubMenu("Lighting",menu);
	glutAddSubMenu("Number of disks",menuDisks);
	glutAddSubMenu("Move View Point",menuCamera);
	glutAddSubMenu("Animation",menuAnimate);
	glutAddSubMenu("Change Background Color",menuBgColor);
	glutAddSubMenu("Solve It!",menuSolveCompletely);
	glutAddSubMenu("Start Over Again?",menuRestart);
	glutAddSubMenu("Exit",menuExit);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void strokeString(float x,float y,float sx,float sy,char *string,int width)
{
	char *c;
	glLineWidth(width);
	glPushMatrix();
	glTranslatef(x,y,0);
	glScalef(sx,sy,0);
	for(c = string; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *c);
	}
	glPopMatrix();
}

void initfirst()
{
	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,1000,0,1000,-1,1);
	glMatrixMode(GL_MODELVIEW);
}

void first()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	strokeString(250,900,0.3,0.3,"MINI PROJECT ON",2);
	glColor3f(0,1,1);
	strokeString(50,820,0.3,0.3,"ILLUSTRATION OF TOWER OF HANOI",4);
	strokeString(320,750,0.3,0.3,"USING OPENGL",4);
	glColor3f(1,0.65,0);
	strokeString(50,650,0.2,0.2,"COURSE TITLE: COMPUTER GRAPHICS LABORATORY",2);
	strokeString(50,600,0.2,0.2,"COURSE CODE: 18CSL67",2);
	strokeString(50,550,0.2,0.2,"STUDENT NAME: PRANAY NAMBIAR",2);
	strokeString(50,500,0.2,0.2,"STUDENT USN: 1BY19CS107",2);
	glColor3f(1,0,1);
	strokeString(320,400,0.2,0.2,"Under the guidance of:",3);
	glColor3f(0,1,0);
    strokeString(20,350,0.2,0.15,"Prof. Muneshwara M S",2);
    strokeString(20,300,0.2,0.15,"Assistant Professor",2);
    strokeString(20,250,0.2,0.15,"Dept. of CSE, BMSIT&M",2);
    strokeString(550,350,0.2,0.15,"Prof. Chethana C",2);
    strokeString(550,300,0.2,0.15,"Assistant Professor",2);
    strokeString(550,250,0.2,0.15,"Dept. of CSE, BMSIT&M",2);
	glColor3f(1,0,0);
	strokeString(250,60,0.2,0.2,"Press N to get going!",3);
	glutSwapBuffers();
}

void displayPage()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	strokeString(450,900,0.3,0.3,"MENU",2);
	glColor3f(0,1,1);
	strokeString(50,820,0.3,0.3,"1. ABOUT (Press A)",4);
	strokeString(50,750,0.3,0.3,"2. INSTRUCTIONS (Press I)",4);
	strokeString(50,680,0.3,0.3,"3. DEMO (Press Enter!)",4);
	glutSwapBuffers();
}

void about()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	strokeString(450,900,0.3,0.3,"ABOUT",2);
	glColor3f(0,1,1);
	strokeString(20,820,0.17,0.17,"The Tower of Hanoi is a mathematical game or puzzle.",2);
	strokeString(20,780,0.17,0.17,"It consists of three rods, and a number of disks of",2);
	strokeString(20,740,0.17,0.17,"different sizes which can slide onto any rod.",2);
	glColor3f(1,0,1);
	strokeString(20,700,0.17,0.17,"The puzzle starts with the disks in a neat stack",2);
	strokeString(20,660,0.17,0.17,"in ascending order of size on one rod, the smallest",2);
	strokeString(20,620,0.17,0.17,"at the top, thus making a conical shape.",2);
	glColor3f(1,1,0);
	strokeString(20,580,0.17,0.17,"The objective of the puzzle is to move the entire",2);
	strokeString(20,540,0.17,0.17,"stack to another rod, obeying the following rules:",2);
	strokeString(20,500,0.17,0.17,"1. Only one disk can be moved at a time.",2);
	strokeString(20,460,0.17,0.17,"2. Each move consists of taking the upper",2 );
	strokeString(20,420,0.17,0.17,"   disk from one of the stacks and placing it on",2);
	strokeString(20,380,0.17,0.17,"   top of another stack i.e. a disk can only be moved",2);
	strokeString(20,340,0.17,0.17,"   if it is the uppermost disk on a stack.",2);
	strokeString(20,300,0.17,0.17,"3. No disk may be placed on top of a smaller disk.",2);
	glutSwapBuffers();
}

void instructions()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1,0,0);
   strokeString(350,900,0.3,0.3,"INSTRUCTIONS",2);
   glColor3f(0,1,0);
   strokeString(50,800,0.17,0.17,"1 . Right click on the screen to view the menu.",2);
   strokeString(50,700,0.17,0.17,"2 . Set the number of disks using the menu.",2);
   strokeString(50,600,0.17,0.17,"3. Set the lighting, animation using the menu.",2);
   strokeString(50,500,0.17,0.17,"4 . Start the simulation using the menu.",2);
   strokeString(50,400,0.17,0.17,"5. Press H to return to home page.",2);
   glutSwapBuffers();
}

void keyboard2(unsigned char c, int x, int y){}
void keyboard(unsigned char c, int x, int y)
{
	switch(c)
	{
		case 13:
			restart();
			init();
			glutDisplayFunc(display);
			createGLUTMenus2();
			glutKeyboardFunc(keyboard2);
			glutMouseFunc(mouse);
            break;
        case 78:
            initfirst();
            glutDisplayFunc(displayPage);
            break;
        case 65:
            initfirst();
            glutDisplayFunc(about);
            break;
        case 73:
            initfirst();
            glutDisplayFunc(instructions);
            break;
        case 72:
            initfirst();
            glutDisplayFunc(first);
            break;
	}
	glutPostRedisplay();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1024,720);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Tower of Hanoi");
	initfirst();
	glutDisplayFunc(first);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
