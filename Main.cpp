#include <windows.h>   // Standard Header For Most Programs
#include <gl/gl.h>     // The GL Header File
#include <gl/glut.h>   // The GL Utility Toolkit (Glut) Header
#include "maze.c"
#include "minion.c"
using namespace std;
GLfloat red_diffuse[] = {1.0f,0.0f,0.0f};
GLfloat green_diffuse[] = {0.0f,1.0f,0.0f};
GLfloat blue_diffuse[] = {0.0f,0.0f,1.0f};
GLfloat lightPos1[] ={5,0,10,1};
GLfloat lightPos2[] ={-5,0,10,1};
GLfloat lightPos3[] ={0,5,10,1};
GLfloat lightPos4[] ={0,-5,10,1};
GLfloat specular[] = {0.500000, 0.500000, 0.500000};
GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightPos[] ={0,15,0,1};
int y_pos = 0;
int x_pos = 0;
int z_const = 5;
int player_x = 0, player_y = 1, player_face = 0;
int y_max[] = {10,22}, y_min = 0;
int x_max[] = {20,19}, x_min = 0;
int level = 0;

void drawFloor(int x, int y)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mtl_kdfloor);
	//glColor3f(0,0.5,0.5);
	glBegin(GL_POLYGON);
		glVertex3f(x,y,z_const);
		glVertex3f(x+1,y,z_const);
		glVertex3f(x+1,y+1,z_const);
		glVertex3f(x,y+1,z_const);
	glEnd();
}

void drawPlayer()
{
	//glDisable(GL_COLOR_MATERIAL);
	glTranslatef(player_x + 0.5f,player_y + 0.3f,z_const);
	if(player_face==0)
	{
		glRotatef(90,0,1,0);
	}
	else if(player_face==1)
	{
		glRotatef(180,0,1,0);
	}
	else if(player_face==2)
	{
		glRotatef(-90,0,1,0);
	}
	else
	{
		glRotatef(0,0,1,0);
	}
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos4);
	//glMaterialfv(GL_FRONT, GL_SPECULAR,specular);
	for(int j = 0; j<15; j++)
	{
		
		glBegin(GL_TRIANGLES);
		int i = 0;
		while(mtls[j][i]!=NULL)
		{
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,mtl_kds[j]);
			glVertex3f(mtls[j][i]/-10.0f,mtls[j][i+1]/10.0f,mtls[j][i+2]/10.0f);
			glVertex3f(mtls[j][i+3]/-10.0f,mtls[j][i+4]/10.0f,mtls[j][i+5]/10.0f);
			glVertex3f(mtls[j][i+6]/-10.0f,mtls[j][i+7]/10.0f,mtls[j][i+8]/10.0f);
			glVertex3f(mtls[j][i]/10.0f,mtls[j][i+1]/10.0f,mtls[j][i+2]/10.0f);
			glVertex3f(mtls[j][i+3]/10.0f,mtls[j][i+4]/10.0f,mtls[j][i+5]/10.0f);
			glVertex3f(mtls[j][i+6]/10.0f,mtls[j][i+7]/10.0f,mtls[j][i+8]/10.0f);
			i = i+9;
		}
			

	    glEnd();
	    
	}
	//glEnable(GL_COLOR_MATERIAL);

}

void drawBox(int x, int y)
{
	//Top
	//glColor3f(0,1,1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl_kdtop);
	glBegin(GL_POLYGON);
		glVertex3f(x,y,z_const+1);
		glVertex3f(x+1,y,z_const+1);
		glVertex3f(x+1,y+1,z_const+1);
		glVertex3f(x,y+1,z_const+1);
	glEnd();
	//Left
	///glColor3f(0.0f,0.8f,0.8f)
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl_kdwall);
	glBegin(GL_POLYGON);
		glVertex3f(x,y,z_const+1);
		glVertex3f(x,y+1,z_const+1);
		glVertex3f(x,y+1,z_const);
		glVertex3f(x,y,z_const);
	glEnd();
	//Right
	glBegin(GL_POLYGON);
		glVertex3f(x+1,y,z_const+1);
		glVertex3f(x+1,y+1,z_const+1);
		glVertex3f(x+1,y+1,z_const);
		glVertex3f(x+1,y,z_const);
	glEnd();
	//Front
	glBegin(GL_POLYGON);
		glVertex3f(x,y,z_const+1);
		glVertex3f(x+1,y,z_const+1);
		glVertex3f(x+1,y,z_const);
		glVertex3f(x,y,z_const);
	glEnd();
	//Back
	glBegin(GL_POLYGON);
		glVertex3f(x,y+1,z_const+1);
		glVertex3f(x+1,y+1,z_const+1);
		glVertex3f(x+1,y+1,z_const);
		glVertex3f(x,y+1,z_const);
	glEnd();
}



void InitGL ( void )     // Create Some Everyday Functions
{

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable ( GL_COLOR_MATERIAL );
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void display ( void )   // Create The Display Function
{
	
	
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glPushMatrix();
	glTranslatef(-1.0f + x_pos,-3.0f + y_pos,-10.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(-15.0f,1.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	//Diffuse (non-shiny) light component
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	//Specular (shiny) light component
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos3);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos4);
	for(int i = 0; i < x_max[level]+1; i++)
	{
		for(int j = 0; j < y_max[level]+1; j++)
		{
			if(maze[level][i][j] == 1)
			{
				drawBox(i,j);
			}
			else
			{
				drawFloor(i,j);
			}
		}
	}
	
	
	drawPlayer();
	glPopMatrix();
	glutSwapBuffers();
}

void reshape ( int width , int height )   // Create The Reshape Function (the viewport)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
  switch ( key ) {
    case 27:        // When Escape Is Pressed...
      exit ( 0 );   // Exit The Program
      break;        // Ready For Next Case
    default:        // Now Wrap It Up
      break;
  }
}

void arrow_keys ( int a_keys, int x, int y )  // Create Special Function (required for arrow keys)
{
  switch ( a_keys ) {
    case GLUT_KEY_UP:     // When Up Arrow Is Pressed...
		//y_pos--;
		if(player_face==1&&player_y+1<=y_max[level]&&maze[level][player_x][player_y+1]!=1)
		{
			y_pos--;
			player_y++;
		}
		if(player_face!=1)
		{
			player_face = 1;
		}
      	break;
    case GLUT_KEY_DOWN:               // When Down Arrow Is Pressed...
    	//y_pos++;
    	if(player_face==3&&player_y-1>=y_min&&maze[level][player_x][player_y-1]!=1)
		{
			y_pos++;
			player_y--;
		}
		if(player_face!=3)
		{
			player_face = 3;
		}
      	break;
    case GLUT_KEY_LEFT:               // When Left Arrow Is Pressed...
    	
    	if(player_face==2&&player_x-1>=x_min&&maze[level][player_x-1][player_y]!=1)
		{
			x_pos++;
			player_x--;
		}
		if(player_face!=2)
		{
			player_face = 2;
		}
      	break;
    case GLUT_KEY_RIGHT:               // When Right Arrow Is Pressed...
    	
    	if(player_face==0&&player_x+1<=x_max[level]&&maze[level][player_x+1][player_y]!=1)
		{
			x_pos--;
			player_x++;
		}
		if(player_face!=0)
		{
			player_face = 0;
		}
      	break;
    default:
      	break;
    
	
	
  }
  if(player_x == x_max[level]&&player_y == y_max[level])  
  {
  	//sleep(2000);
  	exit(0);
  }
  //cout<<player_x<<" "<< player_y<<endl;
}


int main ( int argc, char** argv )   // Create Main Function For Bringing It All Together
{
  glutInit            ( &argc, argv ); // Erm Just Write It =)
  glutInitDisplayMode ( GLUT_RGBA | GLUT_DOUBLE ); // Display Mode
  glutInitWindowSize  ( 500, 500 ); // If glutFullScreen wasn't called this is the window size
  glutCreateWindow    ( "NeHe's OpenGL Framework" ); // Window Title (argv[0] for current directory as title)
  glutFullScreen      ( );          // Put Into Full Screen
  InitGL ();
  glutDisplayFunc     ( display );  // Matching Earlier Functions To Their Counterparts
  glutReshapeFunc     ( reshape );
  glutKeyboardFunc    ( keyboard );
  glutSpecialFunc     ( arrow_keys );
  glutIdleFunc		  ( display );
  glutMainLoop        ( );          // Initialize The Main Loop
  
}


