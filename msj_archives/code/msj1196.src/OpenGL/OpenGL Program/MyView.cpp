// OpenGLView.cpp : implementation of the COpenGLView class
//

#include "stdafx.h"
#include "OpenGL.h"

#include "OpenGLDoc.h"
#include "MyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
////////////////////////////////////////////////////////////

// This is where we override the COpenGLView class members
// to get different functionality

IMPLEMENT_DYNCREATE(CMyView, COpenGLView)

// No stock scene
void CMyView::RenderStockScene()
{
	return; // NOP
}

// set up properties for nice shiny materials, create four lights
// and then render some text. This is pretty complicated, so take a
// look at the texts listed in the bibliography of my article to find
// out more about how to do it.
void CMyView::RenderScene()
{
	// define the lighting properties of the text material
	GLfloat materialSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat materialShininess[1] = { 128.0f };
	GLfloat materialAmbient[4] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat materialDiffuse[4] = { 0.4f, 0.4f, 0.4f, 1.0f };

    GLfloat local_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    
    ::glLightModelfv(GL_LIGHT_MODEL_AMBIENT, local_ambient);

	// red
    GLfloat ambient0[] =  { 0.1f, 0.0f, 0.0f, 1.0f };
    GLfloat diffuse0[] =  { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat specular0[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat position0[] = { 1.7f, 0.8f, 1.5f, 1.0f };

	// green
    GLfloat ambient1[] =  { 0.0f, 0.1f, 0.0f, 1.0f };
    GLfloat diffuse1[] =  { 0.0f, 1.0f, 0.0f, 1.0f };
    GLfloat specular1[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    GLfloat position1[] = { -2.0f, -0.7f, -2.0f, 0.0f };

	// blue
    GLfloat ambient2[] =  { 0.0f, 0.0f, 0.4f, 1.0f };
    GLfloat diffuse2[] =  { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat specular2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat position2[] = { -2.8f, 0.8f, 0.0f, 1.0f };

	// white
    GLfloat ambient3[] =  { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat diffuse3[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat specular3[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat position3[] = { 1.0f, 0.0f, 2.0f, 1.0f };

#if 0
	// If you'd like to see where the lights are placed
	// then you can uncomment this code

	::glDisable( GL_LIGHTING );

	::glPushMatrix();
	::glColor3fv( diffuse0 );
	::glTranslatef( position0[0], position0[1], position0[2] );
  	::auxWireSphere(.15f);
	::glPopMatrix();

	::glPushMatrix();
	::glColor3fv( diffuse1 );
	::glTranslatef( position1[0], position1[1], position1[2] );
  	::auxWireSphere(.15f);
	::glPopMatrix();

	::glPushMatrix();
	::glColor3fv( diffuse2 );
	::glTranslatef( position2[0], position2[1], position2[2] );
  	::auxWireSphere(.15f);
	::glPopMatrix();

	::glPushMatrix();
	::glColor3fv( diffuse3 );
	::glTranslatef( position3[0], position3[1], position3[2] );
  	::auxWireSphere(.15f);
	::glPopMatrix();

#endif
	
	::glEnable( GL_LIGHTING );

    ::glEnable(GL_LIGHT0);  
    ::glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    ::glLightfv(GL_LIGHT0, GL_POSITION, position0);
    ::glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    ::glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

    ::glEnable(GL_LIGHT1);
    ::glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
    ::glLightfv(GL_LIGHT1, GL_POSITION, position1);
    ::glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    ::glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
	
    ::glEnable(GL_LIGHT2);  
    ::glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
    ::glLightfv(GL_LIGHT2, GL_POSITION, position2);
    ::glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
    ::glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);

    ::glEnable(GL_LIGHT3);  
    ::glLightfv(GL_LIGHT3, GL_AMBIENT, ambient3);
    ::glLightfv(GL_LIGHT3, GL_POSITION, position3);
    ::glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);
    ::glLightfv(GL_LIGHT3, GL_SPECULAR, specular3);
 
	::glMaterialfv( GL_FRONT, GL_SPECULAR, materialSpecular );
	::glMaterialfv( GL_FRONT, GL_SHININESS, materialShininess );
	::glMaterialfv( GL_FRONT, GL_DIFFUSE, materialDiffuse );
	::glMaterialfv( GL_FRONT, GL_AMBIENT, materialAmbient );

	::glPushMatrix();
	::glRotatef( 25.0f, 0.0f, 1.0f, 0.0f );
	::glTranslatef( -1.5f, 0.7f, 0.0f );
	GLTextOut( "Look Ma!" );
	::glPopMatrix();

	::glPushMatrix();
	::glRotatef( -25.0f, 0.0f, 1.0f, 0.0f );
	::glTranslatef( -2.5f, -0.7f, 0.0f );
	GLTextOut( "MFC in 3D!!" );
	::glPopMatrix();

}

