#ifndef _KEYBOARD_MACHINE
#define _KEYBOARD_MACHINE

#include <GL\freeglut.h>
#include <GL\GL.h>
#include "WORLD.h"
#include <iostream>
#include <png.h>

#include <fstream>
#include <string>

/****

0 - W
1 - S
2 - A
3 - D
4 - Action/E
5 - Inventory/Q
6 - Run/Walk/Shift
7 - MainMenu/ESC

***/
bool keys[8];

//character speed
int speed = 16;

/*
This will be the clear keys function
*/
void resetKeys(void) 
{
	for(int i = 0; i < 8; i++) keys[i] = false;
}

void keyRelease(unsigned char keyStroke, int x, int y)
{
	switch(keyStroke)
	{
	case 'w': keys[0] = false;
		break;

	case 's': keys[1] = false;
		break;

	case 'a': keys[2] = false;
		break;

	case 'd': keys[3] = false;
		break;

	case 'e': 
	case 'q': 
	default: resetKeys();
		break;
	}	
}

/*

Basic input for the keyboard

*/
void keyboardInput(unsigned char keyStroke, int x, int y)
{
	switch(keyStroke)
	{
	case 'w': keys[0] = true;
		keys[1] = false;
		break;

	case 's': keys[0] = false;
		keys[1] = true;
		break;

	case 'a': keys[2] = true;
		keys[3] = false;
		break;

	case 'd': keys[2] = false;
		keys[3] = true;
		break;

	case 'e': resetKeys();
		keys[4] = true;
		break;

	case 'q': resetKeys();
		keys[5] = true;
		break;

	default: break;
	}
}

/*
This is the state machine to run the keyboard in the idleFunc
*/
player menuStates(player character, world map)
{
	//W and A
	if(keys[0] && keys[2])
	{
		if(keys[6]);
		else 
		{
			character.checkMovement(map, 0, speed);
			character.checkMovement(map, -speed, 0);
		}
	}
	//W and D
	else if(keys[0] && keys[3])
	{
		if(keys[6]);
		else
		{
			character.checkMovement(map, 0, speed);
			character.checkMovement(map, speed, 0);
		}
	}
	//S and A
	else if(keys[1] && keys[2])
	{
		if(keys[6]);
		else 
		{
			character.checkMovement(map, -speed, 0);
			character.checkMovement(map, 0, -speed);
		}

	}
	//S and D
	else if(keys[1] && keys[3])
	{
		if(keys[6]);
		else
		{ 
			character.checkMovement(map, 0, -speed);
			character.checkMovement(map, speed,0);
		}
	}
	//W
	else if(keys[0])
	{
		if(keys[6]);
		else character.checkMovement(map, 0, speed);
	}
	//S
	else if(keys[1])
	{
		if(keys[6]);
		else character.checkMovement(map, 0, -speed);
	}
	//A
	else if(keys[2])
	{
		if(keys[6]);
		else character.checkMovement(map, -speed, 0);
	}
	//D
	else if(keys[3])
	{
		if(keys[6]);
		else character.checkMovement(map, speed, 0);
	}
	//Action or E key
	else if(keys[4]);
	//Menu or Q key
	else if(keys[7]);
	return character;

}

#endif

#ifndef _PURE_KLEPTOMANIA
#define _PURE_KLEPTOMANIA

#define TEXTURE_LOAD_ERROR 0

using namespace std;

double WIDTH = 600;
double HEIGHT = 600;

int viewPortCenter[2] = {0,0};
unsigned int initSize[2] = {1,1};
world DAN(initSize);
player nathan(DAN);

vector<string> stringWorld;

//Texture Related Vars
GLubyte *textureImage;
GLuint *textures;
int numberOfTextures = 3;


//prototyping
bool loadPngImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);
void drawTiles(void);

void calculateViewPort(player character)
{
	viewPortCenter[0] = character.getPositionX() - WIDTH/2;
	viewPortCenter[1] = character.getPositionY() - HEIGHT/2;
}

void updateViewPort(player character)
{
	if((character.getPositionX() - viewPortCenter[0]) > 0.75*WIDTH)
		viewPortCenter[0] += speed; 
	else if((character.getPositionX() - viewPortCenter[0]) < 0.25*WIDTH)
		viewPortCenter[0]-=speed; 
	if((character.getPositionY() - viewPortCenter[1]) > 0.75*HEIGHT)
		viewPortCenter[1]+=speed; 
	else if((character.getPositionY() - viewPortCenter[1]) < 0.25*HEIGHT)
		viewPortCenter[1]-=speed; 

}

void display(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glutInitDisplayMode(GL_DEPTH | GL_FLOAT | GL_RGB | GL_RGBA | GL_DOUBLEBUFFER);
	
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluOrtho2D(viewPortCenter[0], WIDTH + viewPortCenter[0], viewPortCenter[1], HEIGHT + viewPortCenter[1]);
	glViewport(0,0,WIDTH, HEIGHT);

	updateViewPort(nathan);

	//this draws the tiles
	drawTiles();

	//this is for the character
	glClear(GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D,textures[0]);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(nathan.getPositionX()-32,nathan.getPositionY()-32);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(nathan.getPositionX()+32,nathan.getPositionY()-32);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(nathan.getPositionX()+32,nathan.getPositionY()+32);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(nathan.getPositionX()-32,nathan.getPositionY()+32);

	glEnd();

	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void drawTiles(void)
{
	unsigned int pos[2];
	int xPos = 0,yPos = 0;
	for(int y = 0; y < DAN.getY(); y++)
	{
		
		for(int x = 0; x < DAN.getX(); x++)
		{
			pos[0]=x;
			pos[1]=y;

			switch(DAN.checkTileMap(pos))
			{
			case 0://wall
				glBindTexture(GL_TEXTURE_2D,textures[1]);
				break;
			case 1: //floor
				glBindTexture(GL_TEXTURE_2D,textures[2]);
				break;
			}

			glClearColor(0,0,0,0);
			glClear(GL_DEPTH_BUFFER_BIT);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex2i(xPos-32,yPos-32);
			glTexCoord2f(1.0f, 0.0f); glVertex2i(xPos+32, yPos-32);
			glTexCoord2f(1.0f, 1.0f); glVertex2i(xPos+32, yPos+32);
			glTexCoord2f(0.0f, 1.0f); glVertex2i(xPos-32, yPos+32);
			glEnd();

			xPos +=64;
		}
		yPos += 64;
		xPos = 0;
	}
}

void reshape(int x, int y)
{
	WIDTH = x, HEIGHT = y;
	calculateViewPort(nathan);
}

void idle(void)
{
	nathan = menuStates(nathan, DAN);
}

void getWorldFromTextFile(string fname)
{
	string line;
	ifstream infile;

	unsigned int lineNum = 0;

	infile.open(fname);

	while(!infile.eof())
	{
		getline(infile,line);
		stringWorld.push_back(line);
	}
	infile.close();
}

void populateWorld(vector<string> map)
{
	unsigned int size[] = {0,map.size()};

	for (int i =0; i<map.size();i++)
	{
		for(int j = 0; j<(map.at(i)).length(); j++)
		{
			switch((map.at(i))[j])
			{
			case '0':
				DAN.setTileLocation(size, 0);
				size[0]++;
				break;
			case '1':
				DAN.setTileLocation(size, 1);	
				size[0]++;
				break;	
			}
		}
		size[0] = 0;
		size[1]--;
	}
}

unsigned int getTxtWorldX(void)
{
	return stringWorld.at(0).length();
}

unsigned int getTxtWorldY(void)
{
	return stringWorld.size();
}

void loadTexture(GLuint texture, char* filename)
{
	//i dont think these two things are needed
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	int width, height;
    bool hasAlpha;
    bool success = loadPngImage(filename, width, height, hasAlpha, &textureImage);
    if (!success) {
        std::cout << "Unable to load png file" << std::endl;
        return;
    }
    std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;
    
	glBindTexture(GL_TEXTURE_2D,texture);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width,
                 height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
                 textureImage);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void init()
{
	textures = new GLuint[numberOfTextures];

	glGenTextures(numberOfTextures,textures);

	loadTexture(textures[0],"sprite_1.png");
	loadTexture(textures[1],"wall_1.png");
	loadTexture(textures[2],"floor_1.png");



	glEnable(GL_DEPTH_TEST);
}

bool loadPngImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;
 
    if ((fp = fopen(name, "rb")) == NULL)
        return false;
 
    /* Create and initialize the png_struct
     * with the desired error handler
     * functions.  If you want to use the
     * default stderr and longjump method,
     * you can supply NULL for the last
     * three parameters.  We also supply the
     * the compiler header file version, so
     * that we know if the application
     * was compiled with a compatible version
     * of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                     NULL, NULL, NULL);
 
    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }
 
    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return false;
    }
 
    /* Set error handling if you are
     * using the setjmp/longjmp method
     * (this is the normal method of
     * doing things with libpng).
     * REQUIRED unless you  set up
     * your own error handlers in
     * the png_create_read_struct()
     * earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        return false;
    }
 
    /* Set up the output control if
     * you are using standard C streams */
    png_init_io(png_ptr, fp);
 
    /* If we have already
     * read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);
 
    /*
     * If you have enough memory to read
     * in the entire image at once, and
     * you need to specify only
     * transforms that can be controlled
     * with one of the PNG_TRANSFORM_*
     * bits (this presently excludes
     * dithering, filling, setting
     * background, and doing gamma
     * adjustment), then you can read the
     * entire image (including pixels)
     * into the info structure with this
     * call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
 
    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);
    outWidth = width;
    outHeight = height;
 
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    *outData = (unsigned char*) malloc(row_bytes * outHeight);
 
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
 
    for (int i = 0; i < outHeight; i++) {
        // note that png is ordered top to
        // bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
    }
 
    /* Clean up after the read,
     * and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
 
    /* Close the file */
    fclose(fp);
 
    /* That's it */
    return true;
}

void FreeImage(GLuint texture)
{
	glDeleteTextures(1,&texture);
}


void main(int argv, char* argc[])
{
	resetKeys();

	getWorldFromTextFile("world.txt");
	unsigned int mapFileSize[] = {getTxtWorldX(),getTxtWorldY()};

	tile block;
	object newBlock;

	unsigned int startTile[] = {16,11};

	DAN.changePlayerStart(startTile);
	player greg(DAN);
	nathan = greg;

	block.changeDescription("HOORAY");
	block.changePassThrough(true);

	DAN.changeDimension(mapFileSize); //sets map size
	

	DAN.addTile(block);
	DAN.printLog();

	populateWorld(stringWorld);

	glutInit(&argv, argc);
	glutInitWindowSize(600,600);
	glutCreateWindow("Pure Kleptomania");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardInput);
	glutKeyboardUpFunc(keyRelease);

	init();
	//drawTiles();

	glutMainLoop();

	FreeImage(textures[0]);
	FreeImage(textures[1]);
	FreeImage(textures[2]);
}

#endif