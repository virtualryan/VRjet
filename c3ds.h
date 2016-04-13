#include "texture.h"
#include "3ds.h"


#define MAX_TEXTURES 100								// The maximum amount of textures to load


class c3ds
{
public :
	c3ds();
	~c3ds();

	void drawModel(GLuint viewMode, GLfloat size);
	void loadModel(char *fileName);

private :
	CLoad3DS loader;
	t3DModel model;
	Texture textures;



};
