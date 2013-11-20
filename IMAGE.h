#pragma once
#ifndef _IMAGE_HANDLER
#define _IMAGE_HANDLER

#include "COLLECTIONS.h"
#ifndef TEXTURE_LOAD_ERROR
	#define TEXTURE_LOAD_ERROR 0
#endif

class image
{
	private: 
		bool imageAvailable;
		const char* imageName;
		int imageSize[2];
		//This is the image that we are using
		GLubyte *textureBinary;
		GLuint texture;
		//This is the texture being binded
		vector<double*> textureVector;
		//This also loads the images
		void checkIfAvailable(void);
		void buildTextureArray(void);
		void addTexture(double* textCoords);
		bool buildOkay;
		bool hasAlpha;

	public:
		
		image(void);
		image(const char* startImage);
		double* getTextureArray(void);
		void setupTexture(void);
		void changeName(const char* name);
		void addTile(double* textCoords);
		void writeReport(void);
		GLubyte* getTextureBinary(void);
		GLuint getTexture(void);
		double *textureArray;
};
#endif