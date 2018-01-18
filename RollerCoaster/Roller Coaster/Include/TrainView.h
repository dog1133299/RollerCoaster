#ifndef TRAINVIEW_H  
#define TRAINVIEW_H  
#include <QtOpenGL/QGLWidget>  
#include <QtGui/QtGui>  
#include <QtOpenGL/QtOpenGL>  
#include <GL/GLU.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib") 
#include "Utilities/ArcBallCam.H"
#include "Utilities/3DUtils.H"
#include "Track.H"
#include"point3d.h"
#include"Model.h"
#include<vector>

class AppMain;
class CTrack;

//#######################################################################
// TODO
// You might change the TrainView in order to add different objects to
// be drawn, or adjust the lighting, or ...
//#######################################################################


class TrainView : public QGLWidget  
{  
	Q_OBJECT  
public:  
	explicit TrainView(QWidget *parent = 0);  
	~TrainView();  

public:
	// overrides of important window things
	//virtual int handle(int);
	virtual void paintGL();

	// all of the actual drawing happens in this routine
	// it has to be encapsulated, since we draw differently if
	// we're drawing shadows (no colors, for example)
	void drawStuff(bool doingShadows=false);

	// setup the projection - assuming that the projection stack has been
	// cleared for you
	void setProjection();

	// Reset the Arc ball control
	void resetArcball();

	// pick a point (for when the mouse goes down)
	void doPick(int mx, int my);

	void loadTexture2D(QString str, GLuint &textureID);
	void drawOther();
	void drawBuilding(int x,int y,int z,int w,  int h, GLuint sticker, float s, float u,float v);
	void drawCube(int x,int y,int z, int height, int w, int h, GLuint sticker, float s, float u, float v);

	void drawtree1(int x,int z, int height, float angle1,float angle2,bool doingShadows);
	void drawtree2(int x, int z, int height, float angle1, float angle2, bool doingShadows);
	void drawtree3(int x, int z, int height, float angle1, float angle2, bool doingShadows);

public:
	ArcBallCam		arcball;			// keep an ArcBall for the UI
	int				selectedCube;  // simple - just remember which cube is selected

	CTrack*			m_pTrack;		// The track of the entire scene
	
	GLuint ground1;
	GLuint train1_ID;
	GLuint train2_ID;
	GLuint building1;
	GLuint citywall1;
	GLuint citywall2;
	GLuint citywall3;
	GLuint citywall4;
	GLuint water;

	GLuint Mcd;
	GLuint NTUST;


	GLuint ground2;
	GLuint splash;


	GLuint ground3;
	GLuint wall;
	GLuint money;
	GLuint TV;
	GLuint wood;
	GLuint painting;
	GLuint frig;
	GLuint MRT;
	GLuint seven;


	GLuint test2;
	vector<GLuint> Sky;
	Model *m;
	
	int camera;
	int curve;
	int track;
	int box = 1;
	bool cave = false;

	bool YS=false;
	bool GS=false;

	float bugOh=1;

	int onceM = 0; 
	int onceP = 0;
	int third= 0;

	int trainShape = 0;

	bool close = true;

	bool isrun; 
	bool wheel=false;
	int people = 0;

	int t_time=0;
	int test = 0;
	int speed = 30;
	int tempspeed=30;
	vector<Pnt3f> orienttemp;
	vector<Pnt3f> crosstemp;
	vector<Pnt3f> postemp;
	vector<Pnt3f> qtstemp;
	vector<int> DIVIDE_LINE;

	Pnt3f matrix1_look, matrix2_look, matrix4_look;

	typedef enum {
		spline_Linear = 0,
		spline_CardinalCubic = 1,
		spline_CubicB_Spline = 2
	} spline_t; 

};  
#endif // TRAINVIEW_H  