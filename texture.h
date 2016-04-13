#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <GL/glut.h>
#include <vector>

using namespace std;


/* Image type - contains height, width, and data */
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

typedef struct Image Image;

class Texture
{
public:

	Texture();
	int LoadGLTextures(char *filename, int index);
	int setTexture(int texID);

private :
	int ImageLoad(char *filename, Image *image);
	vector<GLuint> texture;
	vector<int> lookUp;
};
