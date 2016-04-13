#include "c3ds.h"

c3ds::c3ds()
{

}

c3ds::~c3ds()
{
	for (int i = 0; i < model.numOfObjects; i++)
	{
		delete [] model.pObject[i].pFaces;
		delete [] model.pObject[i].pVerts;
		delete [] model.pObject[i].pNormals;
		delete [] model.pObject[i].pTexVerts;
	}
}


void c3ds::loadModel(char *fileName)
{
	loader.Import3DS(&model, fileName);
	char temp[255];

	for (int i = 0; i < model.numOfMaterials; i++)
	{
		if (model.pMaterials[i].strFile[0] > 0)
		{
			printf("%s\n", model.pMaterials[i].strFile);
			sprintf(temp, "Data/Textures/%s", model.pMaterials[i].strFile);
			textures.LoadGLTextures(temp, i+1);
		}
	}
}

void c3ds::drawModel(GLuint viewMode, GLfloat size)
{
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	for (int i = 0; i < model.numOfObjects; i++)
	{
		// Ensure that there is at least one object available
		if (model.pObject.size() <= 0)
			break;

		// Get a reference to the current object
		t3DObject *pObject = &model.pObject[i];

		// Check to see if this object has a texture map, if so bind the texture to it.
		if(pObject->bHasTexture) 
		{
			// Turn on texture mapping and turn off color
			glEnable(GL_TEXTURE_2D);

			// Reset the color to normal again
			glColor3ub(255, 255, 255);

			// Bind the texture map to the object by it's materialID
			textures.setTexture(pObject->materialID+1);
		} 
		
		else 
		{
			// Turn off texture mapping and turn on color
			glDisable(GL_TEXTURE_2D);

			// Reset the color to normal again
			glColor3ub(255, 255, 255);
		}

		// This determines if we are in wireframe or normal mode
		if (viewMode)
			glBegin(GL_TRIANGLES);

		else
			glBegin(GL_LINES);

			// Go through all of the faces (polygons) of the object and draw them
			for(int j = 0; j < pObject->numOfFaces; j++)
			{
				// Go through each corner of the triangle and draw it.
				for(int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					// Get the index for each point of the face
					int index = pObject->pFaces[j].vertIndex[whichVertex];
			
					// Give OpenGL the normal for this vertex.
					glNormal3f(pObject->pNormals[ index ].x, pObject->pNormals[ index ].y, pObject->pNormals[ index ].z);
				
					// If the object has a texture associated with it, give it a texture coordinate.
					if(pObject->bHasTexture) 
					{
						// Make sure there was a UVW map applied to the object or else it won't have tex coords.
						if(pObject->pTexVerts) 
						{
							glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
						}
					} 
					
					else 
					{

						// Make sure there is a valid material/color assigned to this object.
						// You should always at least assign a material color to an object, 
						// but just in case we want to check the size of the material list.
						// if the size is at least one, and the material ID != -1,
						// then we have a valid material.
						if(model.pMaterials.size() && pObject->materialID >= 0) 
						{
							// Get and set the color that the object is, since it must not have a texture
							char *pColor = model.pMaterials[pObject->materialID].color;

							// Assign the current color to this model
							glColor3ub(pColor[0], pColor[1], pColor[2]);
						}
					}

					// Pass in the current vertex of the object (Corner of current face)
					glVertex3f(pObject->pVerts[ index ].x * size, pObject->pVerts[ index ].y * size, pObject->pVerts[ index ].z * size);
				}
			}

		glEnd();								// End the drawing
	}
}
