#ifndef _RENDERER_METHODS
#define _RENDERER_METHODS

#include "RENDERER.h"

/*
//Texture Related Vars
GLubyte *textureImage;
GLuint *textures;
int numberOfTextures = 3;

//prototyping
bool loadPngImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);
void drawTiles(void);

void drawTiles(void)
{
			glBindTexture(GL_TEXTURE_2D,textures[1]);
			glBindTexture(GL_TEXTURE_2D,textures[2]);
}

void loadTexture(GLuint texture, char* filename)
{
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
 /*   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                     NULL, NULL, NULL);
 
    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }
 
    /* Allocate/initialize the memory
     * for image information.  REQUIRED. */
 /*   info_ptr = png_create_info_struct(png_ptr);
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
    /*if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated
         * with the png_ptr and info_ptr */
    /*    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        /* If we get here, we had a
         * problem reading the file */
        //return false;
    /*}
 
    /* Set up the output control if
     * you are using standard C streams */
    /*png_init_io(png_ptr, fp);
 
    /* If we have already
     * read some of the signature */
    /*png_set_sig_bytes(png_ptr, sig_read);
 
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
    /*png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
 
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
    //png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
 
    /* Close the file */
    //fclose(fp);
 
    /* That's it */
    /*return true;
}

void FreeImage(GLuint texture)
{
	glDeleteTextures(1,&texture);
}
*/


renderer::~renderer(void)
{
	delete[] vertices;
	delete[] colors;
	tempColors.clear();
	tempVertices.clear();
}

void renderer::clearArrays(void)
{
	delete[] vertices;
	delete[] colors;
	buildOk = true;
}

renderer::renderer(void)
{
	vertices = new int[0];
	colors = new double[0];
	tempVertices.clear();
	tempColors.clear();
	buildOk = true;
	textureData.changeName("rough_tiles.png");
}

void renderer::buildArrays(void)
{
	if(!tempVertices.empty())
	{
		clearArrays();
		vertices = new int[tempVertices.size()*2];
		colors = new double[tempColors.size()*3];
		for(int i = 0; i < tempVertices.size(); i++)
		{
			vertices[i*2] = tempVertices.at(i)[0];
			vertices[i*2 + 1] = tempVertices.at(i)[1];
			colors[i*3] = tempColors.at(i)[0];
			colors[i*3 + 1] = tempColors.at(i)[1];
			colors[i*3 + 2] = tempColors.at(i)[2];
		}
		buildOk = false;
	}
	else;
}

void renderer::addPoint(int point[2]) 
{
	buildOk = true;
	int* newPoint;
	newPoint = new int[2];
	newPoint[0] = point[0], newPoint[1] = point[1];
	tempVertices.push_back(newPoint);
}

void renderer::addColor(int color[3]) 
{
	buildOk = true;
	double* newColor;
	newColor = new double[2];
	newColor[0] = color[0], newColor[1] = color[1], newColor[2] = color[2];
	tempColors.push_back(newColor);
}

void renderer::addTile(int center[2], int color[3], int size)
{
	for(int i = 0; i < 6; i++) addColor(color);
	int * point;
	point = new int[2];
	point[0] = center[0] - size/2;
	point[1] = center[1] - size/2;
	addPoint(point);
	point[0] = center[0] + size/2;
	point[1] = center[1] - size/2;
	addPoint(point);
	point[0] = center[0] - size/2;
	point[1] = center[1] + size/2;
	addPoint(point);
	point[0] = center[0] - size/2;
	point[1] = center[1] + size/2;
	addPoint(point);
	point[0] = center[0] + size/2;
	point[1] = center[1] + size/2;
	addPoint(point);
	point[0] = center[0] + size/2;
	point[1] = center[1] - size/2;
	addPoint(point);

}

void renderer::render(void)
{
	if(buildOk)
	{
		buildArrays();
		buildOk = false;
		cout << "built " << tempVertices.size() << endl;
	}
	if(!buildOk)
	{
		textureData.setupTexture();
		glBindTexture(GL_TEXTURE_2D, textureData.getTexture());
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(2, GL_INT, 0, vertices);
		glColorPointer(3, GL_DOUBLE, 0, colors);
		
		glTexCoordPointer(2, GL_DOUBLE, 0, textureData.textureArray);
		glDrawArrays(GL_TRIANGLES, 0, tempVertices.size());
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

void renderer::printPoint(int pos)
{
	if(pos < tempVertices.size()) cout << tempVertices.at(pos)[0] << " x pos" 
		<< endl << tempVertices.at(pos)[1] << " y pos" << endl;
	else cout << "no point found" << endl;
}

void renderer::worldToArray(world gameSpace, int resolution)
{
	unsigned int pos[2];
	double color[3];
	int location[2];
	double textCoords[2];
	for(int i = 0; i < gameSpace.getY(); i++)
	{
		pos[1] = i;
		for(int j = 0; j < gameSpace.getX(); j++)
		{
			pos[0] = j;
			int * color = new int[3];
			if(gameSpace.getTileCollision(gameSpace.checkTileMap(pos))) 
			{
				color[0] = 1, color[1] = 1, color[2] = 1;
				textCoords[0] = 0, textCoords[1] = 1;
				textureData.addTile(textCoords);
			}
			else 
			{
				color[0] = 1, color[1] = 0, color[2] = 0;
				textCoords[0] = 0, textCoords[1] = 1;
				textureData.addTile(textCoords);
			}
			location[0] = j*resolution, location[1] = i*resolution;
			addTile(location, color, resolution);
		}
	}
}

#endif