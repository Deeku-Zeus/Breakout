#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

static int slices = 50;
static int stacks = 50;
static double radius =0.05;
static float z_ord=-0.10;
static float x_ord=0;
static float y_ord=0;
static float pos=0;
static float speedball =10;
static float speedbrick =16;
static double movx =0;
static double movy=0;
static float adderx=1;
static float addery =1.5;
static int start;
static int stop;
static int score;
static int time;
static int i;
static int timer;
int t;
static int win;
static int begining=1;
static int countbrick=0;

static int brickstatus [27]
{
 0,0,0,0,0,
 0,0,0,0,0,0,
 0,0,0,0,0,
 0,0,0,0,0,0,
 0,0,0,0,0
};

static double bricklocation [][2]={
{-0.625,0.65},{-0.325,0.65},{0.025,0.65},{0.275,0.65},{0.575,0.65},
{-0.775,0.65},{-0.475,0.65},{-0.175,0.65},{0.125,0.65},{0.425,0.65},{0.725,0.65},
{-0.625,0.6},{-0.325,0.6},{0.025,0.6},{0.275,0.6},{0.575,0.6},
{-0.775,0.55},{-0.475,0.55},{-0.175,0.55},{0.125,0.55},{0.425,0.55},{0.725,0.55},
{-0.625,0.5},{-0.325,0.5},{0.025,0.5},{0.275,0.5},{0.575,0.5}
};


//method prototypes
static void brickarray(int,int,double,double);
static void brick(double,double,double);
static void balllogic();
static void basebricklogic();
static void borderline(double,double,double,double);
void numdisplay (double , double , double, double , int);
void stringdisplay(char* ,double, double, double);
static int check(double ,double);
void initvals();
void begintime();


static void resize(int width, int height)
{
    //this calculation is to make the view point at the center.

    glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
     glViewport((width-height)/2, 0, height, height);

    glOrtho(-1, 1, -1, 1, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
void initvals()
{
slices = 50;
stacks = 50;
radius =0.05;
z_ord=-0.10;
x_ord=0;
y_ord=0;
pos=0;
speedball =1;
speedbrick =1.2;
movx =0;
movy=0;
adderx=0.001;
addery =0.0015;
for(int i=0;i<27;i++){
         brickstatus [i]=0;
        }
countbrick=0;
}

void begintime()
{
    t = (glutGet(GLUT_ELAPSED_TIME) / 1000.0);
    time=t-timer;
}

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

if(begining==1)
{
     glColor3f(1.0, 0.0, 0.0);
       // stringdisplay("hello... this is a sample text",-0.3,0.81,-0.3);
        stringdisplay("ATRIA INSTITUTE OF TECHNOLOGY       ",-0.2,0.7,-0.3);
        glColor3f(10,0.4,0);
        stringdisplay("Graphical Implementation of      ",-0.2,0.6,-0.3);
        stringdisplay("    Breakout Game     ",-0.2,0.4,-0.3);
        glColor3f(0,0.5,0);
        stringdisplay("     Submitted By:                 ",-0.2,0.3,-0.3);
        glColor3f(0,0,1);
        stringdisplay("  Deekshit L N Swamy",-0.2,0.2,-0.3);
        glColor3f(0,0,1);
        stringdisplay("    (1AT15CS019)",-0.2,0.1,-0.3);
        glColor3f(0,0.5,0);
        stringdisplay("  Under The Guidance Of:      ",-0.2,0,-0.3);
        glColor3f(0,0,10);
        stringdisplay("    Mr. SATHISHA         ",-0.15,-0.2,-0.3);
        glColor3f(1,0,0.7);
        stringdisplay("  Lecturer,Dept. of CS&E        ",-0.2,-0.3,-0.3);
        stringdisplay("     ATRIA          ",-0.1,-0.4,-0.3);
        stringdisplay("   ANANDNAGAR            ",-0.15,-0.5,-0.3);
        stringdisplay(" Bangalore-560024        ",-0.15,-0.6,-0.3);
        glColor3d(0.5,10,0);
        stringdisplay("   press c to continue     ",-0.2,-0.8,-0.3);

    }



if(start==1 && begining==0)
    {

 //  int a = ((int(t)%60)*100) + (int(t))%60;

        begintime();
        basebricklogic();

    glColor3d(1,0,0);
    glPushMatrix();
        balllogic();
        glTranslated(movx,movy,z_ord);
        glutSolidSphere(radius,slices,stacks);
    glPopMatrix();


    glPushMatrix();
    glColor3f(1,0,0);
        glTranslated(x_ord,y_ord-0.9,z_ord);
        glRotated(15,1,1,-0.1);
        glScaled(1,0.125,0.25);
        glutSolidCube(0.4);
        //brick(0.2,0.0125,0.05);
    glPopMatrix();


    glPushMatrix();
        glColor3f(10,10,10);
        glTranslated(0,0.99,-0.2);
        brick(1,0.15,0.2);
        borderline(1,0.15,-0.1,10);
    glPopMatrix();

    glPushMatrix();
        glColor3f(100,0,0);
        glTranslated(0,-1,0);
        brick(1,0.025,-0.2);
    glPopMatrix();

            //background color
            glPushMatrix();
            glColor3f(0,0,0.2);
            glTranslated(0,0,-0.9);
            brick(1,1,-0.2);
            glPopMatrix();

    glColor3f(0,0,0);
    stringdisplay("BREAKOUT GAME",-0.3,0.9,-0.1);
    glColor3f(128, 0, 0);
    stringdisplay("TIME",-0.8,0.9,-0.1);
    stringdisplay("SCORE: ",0.4,0.9,-0.1);
    glColor3f(0,0,0);
    //time
    numdisplay(-0.6,0.9,-0.1,1.7,time);
    //score
    numdisplay(0.7,0.9,-0.1,1.7,score);
    // border for the top window
    borderline(0.99,0.99,-0.1,10);

    brickarray(5,5,0.2,0.1);


}

if(countbrick>=27)
{
    win=1;
    start=0;
    countbrick=0;

}

if(win==1)
{
    glColor3f(10,0,0);
        stringdisplay("Congragulations",-0.25,0.3,-0.1);
       stringdisplay("YOU WIN !!!",-0.2,0.2,-0.1);
       stringdisplay("--------------------------------",-0.5,0.1,-0.1);
       stringdisplay("Time Lasted : ",-0.2,0,-0.1);
       stringdisplay("Score       : ",-0.2,-0.1,-0.1);
        glColor3f(10,0,0);
        numdisplay(0.2,0,-0.1,1.7,time);
        numdisplay(0.15,-0.1,-0.1,1.7,score);
        stringdisplay("--------------------------------",-0.5,-0.2,-0.1);
        stringdisplay("Press 'r' to restart ",-0.3,-0.5,-0.1);
        stringdisplay("Press 'Esc' or 'q' to Exit ",-0.3,-0.6,-0.1);
        timer=t;
}


    if(start==0&&stop==0 && win==0 && begining==0)
    {
        glColor3f(30,0,0);
        stringdisplay("BREAKOUT GAME",-0.15,0.6,-0.1);
        stringdisplay("Rules :",0,0.4,-0.1);
        stringdisplay("Try To Hit The Bricks Above.",-0.2,0.3,-0.1);
        stringdisplay("Use 'a' or 4 to move left, and 'd' or 6 to move right.",-0.5,0.2,-0.1);
        stringdisplay("to start game press 's' .",-0.2,-0.3,-0.1);

    }

    if(stop==1)
    {
        glColor3f(10,0,0);
        stringdisplay("Oops....",-0.1,0.3,-0.1);
       stringdisplay("GAME-OVER",-0.2,0.2,-0.1);
       stringdisplay("--------------------------------",-0.5,0.1,-0.1);
       stringdisplay("Time Lasted : ",-0.2,0,-0.1);
       stringdisplay("Score       : ",-0.2,-0.1,-0.1);
        glColor3f(10,0,0);
        numdisplay(0.2,0,-0.1,1.7,time);
        numdisplay(0.15,-0.1,-0.1,1.7,score);
        stringdisplay("--------------------------------",-0.5,-0.2,-0.1);
        stringdisplay("Press 'r' to restart ",-0.3,-0.5,-0.1);
        stringdisplay("Press 'Esc' or 'q' to Exit ",-0.3,-0.6,-0.1);
        start=0;
        timer=t;

    }

    glFlush ();
    glutSwapBuffers();
}

static void brickarray(int row,int col,double xshift, double yshift)
{
    double x,y;
    int i=1,j=1;
    static int k=0;
    x=-0.35;
    y=1.4;
    for(i=1;i<=col;i++)
        {
            if(i%2!=0){
                j=1;

            }
            else{
                j=0;
            }
            for(;j<=row;j++)
            {
                if(brickstatus[k++]==0){
                glColor3f(0.9, 0, 0);
                glPushMatrix();
                glRotated(10,3,2,0);
                glScaled(1.5,0.5,1);
                glTranslated(x,y,-0.1);
                glutSolidCube(0.1);
                glPopMatrix();
                }
             x+=xshift;
            }
            y-=yshift;
            if(i%2!=0)
            x=-0.45;
            else
            x=-0.35;
        }
        k=0;

}

void stringdisplay(char* text,double x, double y, double z)
{

glDisable(GL_LIGHTING);

glRasterPos3f(x,y,z);
for(int i = 0; text[i] != '\0'; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

glEnable(GL_LIGHTING);
}

void numdisplay (double posx, double posy, double posz, double space_char, int numb)
{
    glDisable(GL_LIGHTING);
        int j=0,p,k;
        GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;

        p = numb;
        j = 0;
        k = 0;
        while(p > 9)
        {
            k = p % 10;
            glRasterPos3f ((posx-(j*space_char*0.02)),posy, posz);
            glutBitmapCharacter(font_style1,48+k);
            j++;
            p /= 10;
        }
            glRasterPos3f ((posx-(j*space_char*0.02)), posy, posz);
            glutBitmapCharacter(font_style1,48+p);

        glEnable(GL_LIGHTING);
}

static void borderline(double x, double y, double z, double s)
{

        glColor3d(0,0,0);
        glLineWidth(s);
        glBegin(GL_LINE_LOOP);
            glVertex3f(-x,y,z);
            glVertex3f(x,y,z);
            glVertex3f(x,-y,z);
            glVertex3f(-x,-y,z);
        glEnd();
        glFlush();
}

static void basebricklogic()
{

    x_ord+=pos;
    if(x_ord>=1)
    {
        x_ord-=pos;
    }
    if(x_ord<=-1)
    {
        x_ord-=pos;
    }
}

static void balllogic()
{
        //moving the ball.
//logic for rebounding over the slide brick
if((movx<(x_ord+0.15)&& movx>(x_ord-0.15)) && movy<-0.8)
{
    addery=-addery;
    movy+=addery;
    score++;
}
if(check(movx,movy))
{

    addery=-addery;
    movy+=addery;
}

//if it hits on the left and right side
if(movx>=1||movx<=-1)
{
    adderx=-adderx;
    movx+=adderx;
}

// if it hits top and bottom.
if(movy>=0.8||movy<=-1)
{
    if(movy<=-1)
    {
       speedball=0;
       stop=1;
    }
    addery=-addery;
    movy+=addery;
}

movx+=(adderx*speedball);
movy+=(addery*speedball);
}

static int check(double x,double y)
{

    for(int i=0;i<27;i++)
    {
            if((movy>=0.45 && movy<=0.7)&&(movx>=-0.775 && movx<=0.875))// logic to break bricks
                {

                    if(movy>=bricklocation[i][1] && (movx>=bricklocation[i][0]&&movx<=bricklocation[i][0]+0.15) && brickstatus[i]==0)
                    {
                        brickstatus[i]=1;
                        score+=10;
                        countbrick++;
                        return 1;
                    }

                }
    }

    return 0;
}

static void brick(double x, double y, double z)
{
    //front
    glBegin(GL_POLYGON);

	glVertex3f(-x,y,z);
	glVertex3f(x,y,z);
	glVertex3f(x,-y,z);
	glVertex3f(-x,-y,z);
	glEnd();

	//top
	glBegin(GL_POLYGON);

	glVertex3f(x,y,z);
	glVertex3f(x,y,-z);
	glVertex3f(-x,y,-z);
	glVertex3f(-x,y,z);
	glEnd();

	//bottom
	glBegin(GL_POLYGON);
	glVertex3f(x,-y,z);
	glVertex3f(x,-y,-z);
	glVertex3f(-x,-y,-z);
	glVertex3f(-x,-y,z);
	glEnd();

	// back
	glBegin(GL_POLYGON);

	glVertex3f(x,y,-z);
	glVertex3f(-x,y,-z);
	glVertex3f(-x,-y,-z);
	glVertex3f(x,-y,-z);
	glEnd();

	//left
	glBegin(GL_POLYGON);

	glVertex3f(-x,y,z);
	glVertex3f(-x,y,-z);
	glVertex3f(-x,-y,-z);
	glVertex3f(-x,-y,z);
	glEnd();

	//right
	glBegin(GL_POLYGON);

	glVertex3f(x,y,z);
	glVertex3f(x,y,-z);
	glVertex3f(x,-y,-z);
	glVertex3f(x,-y,z);
	glEnd();

}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
    case 'A':
    case '4':
        pos=-0.0015;
        //x_ord-=0.03;
        //basebricklogic();
    break;

    case 'd' :
    case 'D':
    case '6':
       pos=0.0015;
       //x_ord+=0.03;
       //basebricklogic();
        break;

    case '+':
        speedball+=1;
        break;

    case '-':
        speedball-=1;
        break;

    case 's':
    case 'S':
        score=0;
        start=1;
        stop=0;
        win=0;
        timer=t;
        initvals();
        break;

        case 'c':
    case 'C':
        begining=0;
        break;

    case 'r':
    case 'R':
        score=0;
        start=1;
        stop=0;
        win=0;
        timer=t;
        initvals();



        break;

    case 'p':
    case 'P':
        speedball=0;
        break;

    case 'o':
    case 'O':
        speedball=1;
        break;

    case 'q':
    case 27 :
        exit(0);
    break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("BreakOut");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutFullScreen();
    glClearColor(0.1,0.1,0.1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    glutMainLoop();

    return EXIT_SUCCESS;
}
