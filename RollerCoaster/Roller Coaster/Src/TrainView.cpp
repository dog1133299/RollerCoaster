#include "TrainView.h"  
#include<iostream>


TrainView::TrainView(QWidget *parent) :  
QGLWidget(parent)  
{
	resetArcball();
	
	
}  
TrainView::~TrainView()  
{}  

void TrainView:: resetArcball()
	//========================================================================
{
	// Set up the camera to look at the world
	// these parameters might seem magical, and they kindof are
	// a little trial and error goes a long way
	arcball.setup(this, 40, 250, .2f, .4f, 0);
}

void TrainView::paintGL()
{	//load貼圖
	if (onceP==0)
	{
		loadTexture2D("ground.png", ground1);
		loadTexture2D("train2.png", train1_ID);
		loadTexture2D("train1.png", train2_ID);
		loadTexture2D("building1.png", building1);
		loadTexture2D("citywall1.png", citywall1);
		loadTexture2D("citywall2.png", citywall2);
		loadTexture2D("citywall3.png", citywall3);
		loadTexture2D("citywall4.png", citywall4);
		loadTexture2D("water.png", water);



		loadTexture2D("space.png", ground2);

		
		loadTexture2D("grass.png", ground3);
		loadTexture2D("money.png", money);
		loadTexture2D("TV.png", TV);
		loadTexture2D("wood.png", wood);
		loadTexture2D("frig.png", frig);
		loadTexture2D("wall.png", wall);
		loadTexture2D("painting.png", painting);
		loadTexture2D("MRT.png", MRT);
		loadTexture2D("seven.png", seven);
		loadTexture2D("splash.png", splash);

		GLuint tmp;
		loadTexture2D("Sunny2_UP.png", tmp); Sky.push_back(tmp);
		loadTexture2D("Sunny2_DN.png", tmp); Sky.push_back(tmp);
		loadTexture2D("Sunny2_BK.png", tmp); Sky.push_back(tmp);
		loadTexture2D("Sunny2_FR.png", tmp); Sky.push_back(tmp);
		loadTexture2D("Sunny2_LF.png", tmp); Sky.push_back(tmp);
		loadTexture2D("Sunny2_RT.png", tmp); Sky.push_back(tmp);

		loadTexture2D("rock.png", test2);
		onceP++;
	
		
	} 
	
	//*********************************************************************
	//
	// * Set up basic opengl informaiton
	//
	//**********************************************************************
	// Set up the view port
	glViewport(0,0,width(),height());

	// clear the window, be sure to clear the Z-Buffer too
	glClearColor(0,0,.3f,0);		// background should be blue

	// we need to clear out the stencil buffer since we'll use
	// it for shadows
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH);

	// Blayne prefers GL_DIFFUSE
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// prepare for projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setProjection();		// put the code to set up matrices here

	//######################################################################
	// TODO: 
	// you might want to set the lighting up differently. if you do, 
	// we need to set up the lights AFTER setting up the projection
	//######################################################################
	// enable the lighting
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// top view only needs one light
	if (this->camera == 1) {
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	} else {
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
	}

	//*********************************************************************
	//
	// * set the light parameters
	//
	//**********************************************************************
	GLfloat lightPosition1[]	= {0,1,1,0}; // {50, 200.0, 50, 1.0};
	GLfloat lightPosition2[]	= {1, 0, 0, 0};
	GLfloat lightPosition3[]	= {0, -1, 0, 0};
	GLfloat yellowLight[]		= {0.5f, 0.5f, .1f, 1.0};
	GLfloat whiteLight[]		= {1.0f, 1.0f, 1.0f, 1.0};
	GLfloat blueLight[]			= {.1f,.1f,.3f,1.0};
	GLfloat grayLight[]			= {.3f, .3f, .3f, 1.0};

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, grayLight);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowLight);

	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, blueLight);

	if (trainShape == 1){
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
	}
	else{
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	//*********************************************************************
	// now draw the ground plane
	//*********************************************************************
	/*setupFloor();
	glDisable(GL_LIGHTING);
	drawFloor(200,10);
	
	*/
	//*********************************************************************
	// now draw the object and we need to do it twice
	// once for real, and then once for shadows
	//*********************************************************************
	glEnable(GL_LIGHTING);
	setupObjects();

	drawStuff();

	// this time drawing is for shadows (except for top view)
	if (this->camera != 1) {
		setupShadows();
		drawStuff(true);
		unsetupShadows();
	}	

	
}

//************************************************************************
//
// * This sets up both the Projection and the ModelView matrices
//   HOWEVER: it doesn't clear the projection first (the caller handles
//   that) - its important for picking
//========================================================================
void TrainView::
setProjection()
//========================================================================
{
	 
	// Compute the aspect ratio (we'll need it)
	float aspect = static_cast<float>(width()) / static_cast<float>(height());

	// Check whether we use the world camp
	if (this->camera == 0){
		arcball.setProjection(false);
		update();
	// Or we use the top cam
	}else if (this->camera == 1) {
		float wi, he;
		if (aspect >= 1) {
			wi = 220;
			he = wi / aspect;
		} 
		else {
			he = 220;
			wi = he * aspect;
		}

		// Set up the top camera drop mode to be orthogonal and set
		// up proper projection matrix
		glMatrixMode(GL_PROJECTION);
		glOrtho(-wi, wi, he, -he, 200, -200);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(-90,1,0,0);
		update();
	} 
	// Or do the train view or other view here
	//####################################################################
	// TODO: 
	// put code for train view projection here!	
	//####################################################################
	else {
		glMatrixMode(GL_PROJECTION);
		gluPerspective(120, 1, 1, 10000); glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		matrix4_look.normalize();
		matrix2_look.normalize();
		gluLookAt(matrix1_look.x, matrix1_look.y + 5,
			matrix1_look.z, matrix1_look.x + matrix2_look.x,
			matrix1_look.y + matrix2_look.y + 5,
			matrix1_look.z + matrix2_look.z, matrix4_look.x, matrix4_look.y, matrix4_look.z);

#ifdef EXAMPLE_SOLUTION
		trainCamView(this,aspect);
#endif
		update();
	}
}

//************************************************************************
//
// * this draws all of the stuff in the world
//
//	NOTE: if you're drawing shadows, DO NOT set colors (otherwise, you get 
//       colored shadows). this gets called twice per draw 
//       -- once for the objects, once for the shadows
//########################################################################
// TODO: 
// if you have other objects in the world, make sure to draw them
//########################################################################
//========================================================================
void TrainView::drawStuff(bool doingShadows)
{ 
	// Draw the control points
	// don't draw the control points if you're driving 
	// (otherwise you get sea-sick as you drive through them)
	if (this->camera != 2) {
		for (size_t i = 0; i < this->m_pTrack->points.size(); ++i) {
			if (!doingShadows) {
				if (((int)i) != selectedCube)
					glColor3ub(240, 60, 60);
				else
					glColor3ub(240, 240, 30);
			}
			this->m_pTrack->points[i].draw();
		}
		update();


	}
	// draw the track
	//####################################################################
	// TODO: 
	// call your own track drawing code
	//####################################################################
	float M[4][4] = { { -0.5  ,  1  ,   -0.5 ,  0 },//矩陣1
					  {1.5  ,  -2.5 ,0  , 1,},
					  { -1.5, 2  , 0.5 ,0,},
					  { 0.5 , -0.5 ,0, 0 } };
	float M2[4][4] = { { -0.1667  , 0.5 , -0.5 , 0.1667 },//矩陣2
						{ 0.5  , -1 ,0  , 0.667,},
						{ -0.5, 0.5  ,0.5 ,0.1667, },
						{ 0.1667 , 0 ,0, 0 } };


	spline_t type_spline = (spline_t)curve;
	DIVIDE_LINE.clear();
	for (size_t i = 0; i < this->m_pTrack->points.size(); ++i)
	{
		Pnt3f  qt, qt0, qt1, orient_t, cross_t;
		// pos
		Pnt3f cp_pos_p1 = m_pTrack->points[i].pos;	//取得一個點
		Pnt3f cp_pos_p2 = m_pTrack->points[(i + 1) % this->m_pTrack->points.size()].pos; //取得下一個點
		Pnt3f cp_pos_p3 = m_pTrack->points[(i + 2) % this->m_pTrack->points.size()].pos; //取得下一個點
		Pnt3f cp_pos_p4 = m_pTrack->points[(i + 3) % this->m_pTrack->points.size()].pos; //取得下一個點

		int d = sqrt((cp_pos_p2.x - cp_pos_p3.x)*(cp_pos_p2.x - cp_pos_p3.x)
			+ (cp_pos_p2.y - cp_pos_p3.y)*(cp_pos_p2.y - cp_pos_p3.y)
			+ (cp_pos_p2.z - cp_pos_p3.z)*(cp_pos_p2.z - cp_pos_p3.z));
		DIVIDE_LINE.push_back(d/3);
		//std::cout << " "<<d<<" " << d / 3 << " ";

		// orient
		Pnt3f cp_orient_p1 = m_pTrack->points[i].orient;//第一個點的方向
		Pnt3f cp_orient_p2 = m_pTrack->points[(i + 1) % this->m_pTrack->points.size()].orient; //第2個點的方向
		Pnt3f cp_orient_p3 = m_pTrack->points[(i + 2) % this->m_pTrack->points.size()].orient; //第3個點的方向
		Pnt3f cp_orient_p4 = m_pTrack->points[(i + 3) % this->m_pTrack->points.size()].orient; //第4個點的方向


		float percent = 1.0f / DIVIDE_LINE[i]; //將兩點之間 分成DIVIDE_LINE段
		float t = 0;// 從t=0開始

		switch (type_spline)	//type_spline類型  
		{
		case spline_Linear://選擇liner的話
			qt = (1 - t) * cp_pos_p2 + t * cp_pos_p3;
			break;
		case spline_CardinalCubic://選擇CardinalCubic 
			qt = (cp_pos_p1*M[0][0] + cp_pos_p2*M[1][0] + cp_pos_p3*M[2][0] + cp_pos_p4*M[3][0])*t*t*t +
				(cp_pos_p1*M[0][1] + cp_pos_p2*M[1][1] + cp_pos_p3*M[2][1] + cp_pos_p4*M[3][1])*t*t +
				(cp_pos_p1*M[0][2] + cp_pos_p2*M[1][2] + cp_pos_p3*M[2][2] + cp_pos_p4*M[3][2])*t +
				(cp_pos_p1*M[0][3] + cp_pos_p2*M[1][3] + cp_pos_p3*M[2][3] + cp_pos_p4*M[3][3]);

			/*菊花
			qt = (-t*t*t + 3*t*t - 3*t + 1) * cp_pos_p1
				+ (3*t*t*t - 6*t*t + 3*t) * cp_pos_p2
				+ (-3*t*t*t + 3*t*t) * cp_pos_p3
				+ (t*t*t)* cp_pos_p4;
			漩渦
				qt = -4.5    *   (t - 1 / 3) *(t - 2 / 3)* (t - 1)*cp_pos_p1
				+ 13.5* (t - 0) *(t - 2 / 3)* (t - 1) *cp_pos_p2
				+ -13.5* (t - 0) *(t - 1 / 3)*(t - 1)*cp_pos_p3
				+ 4.5 *(t - 0) *(t - 1 / 3) *(t - 2 / 3) *cp_pos_p4;*/
			break;
		case spline_CubicB_Spline:

			qt = (cp_pos_p1*M2[0][0] + cp_pos_p2*M2[1][0] + cp_pos_p3*M2[2][0] + cp_pos_p4*M2[3][0])*t*t*t +
				(cp_pos_p1*M2[0][1] + cp_pos_p2*M2[1][1] + cp_pos_p3*M2[2][1] + cp_pos_p4*M2[3][1])*t*t +
				(cp_pos_p1*M2[0][2] + cp_pos_p2*M2[1][2] + cp_pos_p3*M2[2][2] + cp_pos_p4*M2[3][2])*t +
				(cp_pos_p1*M2[0][3] + cp_pos_p2*M2[1][3] + cp_pos_p3*M2[2][3] + cp_pos_p4*M2[3][3]);

			break;
		}
		switch (type_spline) {
		case spline_Linear:
			orient_t = (1 - t) * cp_orient_p2 + t * cp_orient_p3;

			break;
		case spline_CardinalCubic://選擇CardinalCubic 
			orient_t = (cp_orient_p1*M[0][0] + cp_orient_p2*M[1][0] + cp_orient_p3*M[2][0] + cp_orient_p4*M[3][0])*t*t*t +
				(cp_orient_p1*M[0][1] + cp_orient_p2*M[1][1] + cp_orient_p3*M[2][1] + cp_orient_p4*M[3][1])*t*t +
				(cp_orient_p1*M[0][2] + cp_orient_p2*M[1][2] + cp_orient_p3*M[2][2] + cp_orient_p4*M[3][2])*t +
				(cp_orient_p1*M[0][3] + cp_orient_p2*M[1][3] + cp_orient_p3*M[2][3] + cp_orient_p4*M[3][3]);

			break;
		case spline_CubicB_Spline:
			orient_t = (cp_orient_p1*M2[0][0] + cp_orient_p2*M2[1][0] + cp_orient_p3*M2[2][0] + cp_orient_p4*M2[3][0])*t*t*t +
				(cp_orient_p1*M2[0][1] + cp_orient_p2*M2[1][1] + cp_orient_p3*M2[2][1] + cp_orient_p4*M2[3][1])*t*t +
				(cp_orient_p1*M2[0][2] + cp_orient_p2*M2[1][2] + cp_orient_p3*M2[2][2] + cp_orient_p4*M2[3][2])*t +
				(cp_orient_p1*M2[0][3] + cp_orient_p2*M2[1][3] + cp_orient_p3*M2[2][3] + cp_orient_p4*M2[3][3]);


			break;
		}

		int n = 0;
	 
		
		
		for (size_t j = 0; j < DIVIDE_LINE[i]; j++) {//迴圈將每個線段畫出來
			qt0 = qt;



			switch (type_spline) {
			case spline_Linear:
				orient_t = (1 - t) * cp_orient_p2 + t * cp_orient_p3;

				break;
			case spline_CardinalCubic://選擇CardinalCubic 
				orient_t = (cp_orient_p1*M[0][0] + cp_orient_p2*M[1][0] + cp_orient_p3*M[2][0] + cp_orient_p4*M[3][0])*t*t*t +
					(cp_orient_p1*M[0][1] + cp_orient_p2*M[1][1] + cp_orient_p3*M[2][1] + cp_orient_p4*M[3][1])*t*t +
					(cp_orient_p1*M[0][2] + cp_orient_p2*M[1][2] + cp_orient_p3*M[2][2] + cp_orient_p4*M[3][2])*t +
					(cp_orient_p1*M[0][3] + cp_orient_p2*M[1][3] + cp_orient_p3*M[2][3] + cp_orient_p4*M[3][3]);

				break;
			case spline_CubicB_Spline:
				orient_t = (cp_orient_p1*M2[0][0] + cp_orient_p2*M2[1][0] + cp_orient_p3*M2[2][0] + cp_orient_p4*M2[3][0])*t*t*t +
					(cp_orient_p1*M2[0][1] + cp_orient_p2*M2[1][1] + cp_orient_p3*M2[2][1] + cp_orient_p4*M2[3][1])*t*t +
					(cp_orient_p1*M2[0][2] + cp_orient_p2*M2[1][2] + cp_orient_p3*M2[2][2] + cp_orient_p4*M2[3][2])*t +
					(cp_orient_p1*M2[0][3] + cp_orient_p2*M2[1][3] + cp_orient_p3*M2[2][3] + cp_orient_p4*M2[3][3]);


				break;
			}


			t += percent;


			switch (type_spline) {
			case spline_Linear:
				qt = (1 - t) * cp_pos_p2 + t * cp_pos_p3;
				break;
			case spline_CardinalCubic://選擇CardinalCubic 
				qt = (cp_pos_p1*M[0][0] + cp_pos_p2*M[1][0] + cp_pos_p3*M[2][0] + cp_pos_p4*M[3][0])*t*t*t +
					(cp_pos_p1*M[0][1] + cp_pos_p2*M[1][1] + cp_pos_p3*M[2][1] + cp_pos_p4*M[3][1])*t*t +
					(cp_pos_p1*M[0][2] + cp_pos_p2*M[1][2] + cp_pos_p3*M[2][2] + cp_pos_p4*M[3][2])*t +
					(cp_pos_p1*M[0][3] + cp_pos_p2*M[1][3] + cp_pos_p3*M[2][3] + cp_pos_p4*M[3][3]);

				break;
			case spline_CubicB_Spline:
				qt = (cp_pos_p1*M2[0][0] + cp_pos_p2*M2[1][0] + cp_pos_p3*M2[2][0] + cp_pos_p4*M2[3][0])*t*t*t +
					(cp_pos_p1*M2[0][1] + cp_pos_p2*M2[1][1] + cp_pos_p3*M2[2][1] + cp_pos_p4*M2[3][1])*t*t +
					(cp_pos_p1*M2[0][2] + cp_pos_p2*M2[1][2] + cp_pos_p3*M2[2][2] + cp_pos_p4*M2[3][2])*t +
					(cp_pos_p1*M2[0][3] + cp_pos_p2*M2[1][3] + cp_pos_p3*M2[2][3] + cp_pos_p4*M2[3][3]);

				break;
			}


			qt1 = qt;
			glLineWidth(3);
			glBegin(GL_LINES);
			if (!doingShadows) {
				glColor3ub(32, 32, 64);
			}

			postemp.push_back(qt);
			

			orient_t.normalize();//算方向
			cross_t = (qt1 + -1 * qt0) * orient_t;
			cross_t.normalize();
			crosstemp.push_back(cross_t*5.0f);
			cross_t = cross_t * 2.5f;
			

			qtstemp.push_back(qt1 + -1 * qt0);

			Pnt3f test = cross_t* (qt1 + -1 * qt0);
			test.normalize();
			orienttemp.push_back(test);

			switch (track)
			{
			case 0:
				glLineWidth(5);
				glBegin(GL_LINES);//一條line

				glVertex3f(qt0.x, qt0.y, qt0.z);
				glVertex3f(qt1.x, qt1.y, qt1.z);
				glEnd();

				break;
			case 1:
				glLineWidth(3);
				glBegin(GL_LINES);//兩條軌道線

				glVertex3f(qt0.x + cross_t.x, qt0.y + cross_t.y, qt0.z + cross_t.z);
				glVertex3f(qt1.x + cross_t.x, qt1.y + cross_t.y, qt1.z + cross_t.z);

				glVertex3f(qt0.x - cross_t.x, qt0.y - cross_t.y, qt0.z - cross_t.z);
				glVertex3f(qt1.x - cross_t.x, qt1.y - cross_t.y, qt1.z - cross_t.z);
				glEnd();

				if (j == n) {
					cross_t.normalize();
					cross_t = cross_t * 4.5f;
					glBegin(GL_QUADS);//枕木

					glVertex3f(qt0.x + cross_t.x, qt0.y + cross_t.y, qt0.z + cross_t.z);

					glVertex3f(qt1.x + cross_t.x, qt1.y + cross_t.y, qt1.z + cross_t.z);

					glVertex3f(qt1.x - cross_t.x, qt1.y - cross_t.y, qt1.z - cross_t.z);
					glVertex3f(qt0.x - cross_t.x, qt0.y - cross_t.y, qt0.z - cross_t.z);
					glEnd();
					n += 3;
				}
				break;
			case 2: 
					cross_t.normalize();
					cross_t = cross_t * 4.5f;
					glBegin(GL_QUADS);//馬路

					glVertex3f(qt0.x + cross_t.x, qt0.y + cross_t.y, qt0.z + cross_t.z);

					glVertex3f(qt1.x + cross_t.x, qt1.y + cross_t.y, qt1.z + cross_t.z);

					glVertex3f(qt1.x - cross_t.x, qt1.y - cross_t.y, qt1.z - cross_t.z);
					glVertex3f(qt0.x - cross_t.x, qt0.y - cross_t.y, qt0.z - cross_t.z);
					glEnd();
			
				break;
			case 3:
				glLineWidth(0);
				glBegin(GL_LINES);//一條隱形line
				glVertex3f(qt0.x, qt0.y, qt0.z);
				glVertex3f(qt0.x, qt0.y, qt0.z);
				glEnd();
				if (j == n) {
					glBegin(GL_QUADS);//方塊

					glVertex3f(qt0.x + cross_t.x, qt0.y + cross_t.y, qt0.z + cross_t.z);

					glVertex3f(qt1.x + cross_t.x, qt1.y + cross_t.y, qt1.z + cross_t.z);

					glVertex3f(qt1.x - cross_t.x, qt1.y - cross_t.y, qt1.z - cross_t.z);
					glVertex3f(qt0.x - cross_t.x, qt0.y - cross_t.y, qt0.z - cross_t.z);
					glEnd();
					n += 3;
				}
				break;
			default:
				break;
			}
			

		}
		
		/*if (onceM == 0)
		{ 
			onceM++;
			Point3d p(10, 1, 10); //位置
			m = new Model("fence.obj", 80, p); //讀黨
			//m->render(false, false);//
		}
		glColor3f(255, 255, 255);
		m->render(false, false);
		glClearColor(255,255,255,1);
		glDisable(GL_TEXTURE_2D);
		
		
		//Pnt3f cp_pos_p1 = m_pTrack->points[0].pos;	//取得一個點
		/*Point3d p(postemp[t_time].x, postemp[t_time].y,postemp[t_time].z); //位置
		Model *m;
		m = new Model("Arrow.obj", 100, p); //讀黨
		m->render(false, false);//render
*/
	}
	
	if (isrun) {
	
		if (test %speed == 0)
		{
			int sum = 0;
			for (int i = 0; i < this->m_pTrack->points.size(); i++)
				sum = sum + DIVIDE_LINE[i]; 

			if (t_time < sum )
				t_time++;
			else
				t_time = 0;
			
			/*下坡加速*/
			if (postemp[(t_time - 1 + postemp.size()) % postemp.size()].y > postemp[(t_time+1) % postemp.size()].y*1.1)
			{
				third++;
				if (third > 1) {
					speed = tempspeed*0.7; bugOh = 1.5;
					third = 0;
				}
			}
			else if (postemp[(t_time - 1 + postemp.size()) % postemp.size()].y < postemp[(t_time + 1) % postemp.size()].y*0.9)
			{
				third--;
				if (third<-2)
				{
					speed = tempspeed*1.2; bugOh = 0.6;

					third = 0;
				}
				
			}
			else
			{
				third = 0;
				speed = tempspeed; bugOh = 1.0;
			}
		}
		test++;
	
		

			
	}

	
#ifdef EXAMPLE_SOLUTION
	drawTrack(this, doingShadows);
#endif

	// draw the train
	//####################################################################
	// TODO: 
	//	call your own train drawing code
	//####################################################################
	int temp = t_time% postemp.size();
	Pnt3f forehead = crosstemp[temp] * orienttemp[temp];
	//火車視角
	matrix1_look.x = postemp[temp].x - forehead.x * 3 + orienttemp[temp].x * 2;
	matrix1_look.y = postemp[temp].y - forehead.y * 3 + orienttemp[temp].y * 2;
	matrix1_look.z = postemp[temp].z - forehead.z * 3 + orienttemp[temp].z * 2;
	matrix4_look = orienttemp[temp];
	matrix2_look = qtstemp[temp];

	/*圓柱
	glBegin(GL_POLYGON);
	GLUquadricObj *cola = gluNewQuadric();
	gluCylinder(cola, 10, 100, 100, 200, 100);
	glEnd();*/

	drawOther();
	if (cave && postemp.size()>20)
	{
		int tt = 10;
		Pnt3f f = crosstemp[tt] * orienttemp[tt] * 3;
		Pnt3f f1 = crosstemp[tt-2] * orienttemp[tt-2] * 2;
		Pnt3f f2 = crosstemp[tt+2] * orienttemp[tt+2] * 2;
		glBindTexture(GL_TEXTURE_2D, test2);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(1.0f, 1.0f);		glVertex3f(postemp[tt].x, postemp[tt].y + 30, postemp[tt].z);//0
		glTexCoord2f(2.0f, 1.0f);		glVertex3f(postemp[tt+2].x + crosstemp[tt + 2].x * 4, 0, postemp[tt + 2].z + crosstemp[tt + 2].z * 4);//1
		glTexCoord2f(2.0f, 2.0f);		glVertex3f(postemp[tt + 2].x + crosstemp[tt + 2].x*2 + f2.x, 0, postemp[tt + 2].z + crosstemp[tt + 2].z*2 + f2.z);//2
		glTexCoord2f(1.0f, 2.0f);		glVertex3f(postemp[tt].x + crosstemp[tt].x*1.6 + f.x * 3, postemp[tt].y + 10, postemp[tt].z + crosstemp[tt].z*1.6 + f.z);//3
		glTexCoord2f(0.5f, 2.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x*1.6 + f.x, postemp[tt].y + 20, postemp[tt].z - crosstemp[tt].z*1.6 + f.z);//4
		glTexCoord2f(0.0f, 2.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x*2 + f.x, 0, postemp[tt].z - crosstemp[tt].z *2+ f.z);//5
		glTexCoord2f(0.0f, 1.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x * 4, 0, postemp[tt].z - crosstemp[tt].z * 4);//6
		glTexCoord2f(0.0f, 0.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x*2 - f.x, 0, postemp[tt].z - f.z - crosstemp[tt].z*2);//7
		glTexCoord2f(0.5f, 0.0f);		glVertex3f(postemp[tt - 2].x - crosstemp[tt - 2].x*1.6 - f1.x, postemp[tt - 2].y + 10, postemp[tt - 2].z - f1.z - crosstemp[tt - 2].z*1.6);//8
		glTexCoord2f(1.5f, 0.0f);		glVertex3f(postemp[tt - 2].x + crosstemp[tt - 2].x*1.6 - f1.x, postemp[tt - 2].y + 20, postemp[tt - 2].z - f1.z + crosstemp[tt - 2].z*1.6);//9
		glTexCoord2f(2.0f, 0.0f);		glVertex3f(postemp[tt].x + crosstemp[tt].x*2 - f.x, 0, postemp[tt].z - f.z + crosstemp[tt].z*2);//10
		glTexCoord2f(2.0f, 1.0f);		glVertex3f(postemp[tt].x + crosstemp[tt].x *4, 0, postemp[tt].z + crosstemp[tt].z * 4);//1
		glEnd();
		glDisable(GL_TEXTURE_2D);
		 tt = 5;
		 f = crosstemp[tt] * orienttemp[tt] * 2;
		 f1 = crosstemp[tt - 2] * orienttemp[tt - 2] * 3;
		 f2 = crosstemp[tt + 2] * orienttemp[tt + 2] * 2;
		 glBindTexture(GL_TEXTURE_2D, test2);
		 glEnable(GL_TEXTURE_2D);
		 glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(1.0f, 1.0f);		glVertex3f(postemp[tt].x, postemp[tt].y + 30, postemp[tt].z);//0
		glTexCoord2f(2.0f, 1.0f);		glVertex3f(postemp[tt + 2].x + crosstemp[tt + 2].x * 4, 0, postemp[tt + 2].z + crosstemp[tt + 2].z * 4);//1
		glTexCoord2f(2.0f, 2.0f);		glVertex3f(postemp[tt + 2].x + crosstemp[tt + 2].x * 2 + f2.x, 0, postemp[tt + 2].z + crosstemp[tt + 2].z * 2 + f2.z);//2
		glTexCoord2f(1.0f, 2.0f);		glVertex3f(postemp[tt].x + crosstemp[tt].x*1.6 + f.x * 3, postemp[tt].y + 10, postemp[tt].z + crosstemp[tt].z*1.6 + f.z);//3
		glTexCoord2f(0.5f, 2.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x*1.6 + f.x, postemp[tt].y + 20, postemp[tt].z - crosstemp[tt].z*1.6 + f.z);//4
		glTexCoord2f(0.0f, 2.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x * 2 + f.x, 0, postemp[tt].z - crosstemp[tt].z * 2 + f.z);//5
		glTexCoord2f(0.0f, 1.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x * 4, 0, postemp[tt].z - crosstemp[tt].z * 4);//6
		glTexCoord2f(0.0f, 0.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x * 2 - f.x, 0, postemp[tt].z - f.z - crosstemp[tt].z * 2);//7
		glTexCoord2f(0.5f, 0.0f);		glVertex3f(postemp[tt - 2].x - crosstemp[tt - 2].x*1.6 - f1.x, postemp[tt - 2].y + 10, postemp[tt - 2].z - f1.z - crosstemp[tt - 2].z*1.6);//8
		glTexCoord2f(1.5f, 0.0f);		glVertex3f(postemp[tt - 2].x + crosstemp[tt - 2].x*1.6 - f1.x, postemp[tt - 2].y + 20, postemp[tt - 2].z - f1.z + crosstemp[tt - 2].z*1.6);//9
		glTexCoord2f(2.0f, 0.0f);		glVertex3f(postemp[tt].x + crosstemp[tt].x * 2 - f.x, 0, postemp[tt].z - f.z + crosstemp[tt].z * 2);//10
		glTexCoord2f(2.0f, 1.0f);		glVertex3f(postemp[tt].x + crosstemp[tt].x * 4, 0, postemp[tt].z + crosstemp[tt].z * 4);//1
		glEnd();
		glDisable(GL_TEXTURE_2D);
		tt = 20;
		f = crosstemp[tt] * orienttemp[tt] * 4;
		f1 = crosstemp[tt - 2] * orienttemp[tt - 2] * 2;
		f2 = crosstemp[tt + 2] * orienttemp[tt + 2] * 2;
		glBindTexture(GL_TEXTURE_2D, test2);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(1.0f, 1.0f);		glVertex3f(postemp[tt].x, postemp[tt].y + 30, postemp[tt].z);//0
		glTexCoord2f(2.0f, 1.0f);		glVertex3f(postemp[tt + 2].x + crosstemp[tt + 2].x * 4, 0, postemp[tt + 2].z + crosstemp[tt + 2].z * 4);//1
		glTexCoord2f(2.0f, 2.0f);		glVertex3f(postemp[tt + 2].x + crosstemp[tt + 2].x * 2 + f2.x, 0, postemp[tt + 2].z + crosstemp[tt + 2].z * 2 + f2.z);//2
		glTexCoord2f(1.0f, 2.0f);		glVertex3f(postemp[tt].x + crosstemp[tt].x*1.6 + f.x * 3, postemp[tt].y + 10, postemp[tt].z + crosstemp[tt].z*1.6 + f.z);//3
		glTexCoord2f(0.5f, 2.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x*1.6 + f.x, postemp[tt].y + 20, postemp[tt].z - crosstemp[tt].z*1.6 + f.z);//4
		glTexCoord2f(0.0f, 2.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x * 2 + f.x, 0, postemp[tt].z - crosstemp[tt].z * 2 + f.z);//5
		glTexCoord2f(0.0f, 1.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x * 4, 0, postemp[tt].z - crosstemp[tt].z * 4);//6
		glTexCoord2f(0.0f, 0.0f);		glVertex3f(postemp[tt].x - crosstemp[tt].x * 2 - f.x, 0, postemp[tt].z - f.z - crosstemp[tt].z * 2);//7
		glTexCoord2f(0.5f, 0.0f);		glVertex3f(postemp[tt - 2].x - crosstemp[tt - 2].x*1.6 - f1.x, postemp[tt - 2].y + 10, postemp[tt - 2].z - f1.z - crosstemp[tt - 2].z*1.6);//8
		glTexCoord2f(1.5f, 0.0f);		glVertex3f(postemp[tt - 2].x + crosstemp[tt - 2].x*1.6 - f1.x, postemp[tt - 2].y + 20, postemp[tt - 2].z - f1.z + crosstemp[tt - 2].z*1.6);//9
		glTexCoord2f(2.0f, 0.0f);		glVertex3f(postemp[tt].x + crosstemp[tt].x * 2 - f.x, 0, postemp[tt].z - f.z + crosstemp[tt].z * 2);//10
		glTexCoord2f(2.0f, 1.0f);		glVertex3f(postemp[tt].x + crosstemp[tt].x * 4, 0, postemp[tt].z + crosstemp[tt].z * 4);//1

		glEnd();
		glDisable(GL_TEXTURE_2D);

 

	}
	Pnt3f Oh ;
	switch (trainShape)
	{
	case 0:

		glBindTexture(GL_TEXTURE_2D, train2_ID);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		/*10*/	glVertex3f(postemp[temp].x - forehead.x*1.5 + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*1.5 + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z *1.5 + crosstemp[temp].z + orienttemp[temp].z * 3);
		glTexCoord2f(1.0f, 0.0f);
		/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
		glTexCoord2f(1.0f, 1.0f);
		/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);
		glTexCoord2f(0.33f, 1.0f);
		/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, train2_ID);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		/*9*/	glVertex3f(postemp[temp].x - forehead.x*1.5 - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*1.5 - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*1.5 - crosstemp[temp].z + orienttemp[temp].z * 3);
		glTexCoord2f(1.0f, 0.0f);
		/*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
		glTexCoord2f(1.0f, 1.0f);
		/*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);
		glTexCoord2f(0.33f, 1.0f);
		/*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, train2_ID);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		/*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
		glTexCoord2f(1.0f, 0.0f);
		/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
		glTexCoord2f(1.0f, 1.0f);
		/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);
		glTexCoord2f(0.0f, 1.0f);
		/*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);
		glEnd();
		glDisable(GL_TEXTURE_2D);



		glBindTexture(GL_TEXTURE_2D, train1_ID);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glColor3f(200, 200, 20);

		/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);
		/*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);
		/*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);
		/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);

		/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
		/*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
		/*9*/	glVertex3f(postemp[temp].x - forehead.x*1.5 - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*1.5 - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*1.5 - crosstemp[temp].z + orienttemp[temp].z * 3);
		/*10*/	glVertex3f(postemp[temp].x - forehead.x*1.5 + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*1.5 + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*1.5 + crosstemp[temp].z + orienttemp[temp].z * 3);

		glTexCoord2f(0.0f, 0.0f);
		/*10*/	glVertex3f(postemp[temp].x - forehead.x*1.5 + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*1.5 + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*1.5 + crosstemp[temp].z + orienttemp[temp].z * 3);
		glTexCoord2f(1.0f, 0.0f);
		/*9*/	glVertex3f(postemp[temp].x - forehead.x*1.5 - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*1.5 - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*1.5 - crosstemp[temp].z + orienttemp[temp].z * 3);
		glTexCoord2f(1.0f, 1.0f);
		/*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);
		glTexCoord2f(0.0f, 1.0f);
		/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);

		glEnd();
		glDisable(GL_TEXTURE_2D);
	

		for (int b = 1; b < box; b++)//後面車廂
		{
			 temp = (t_time + postemp.size() - b * 3) % postemp.size();
			 forehead = crosstemp[temp] * orienttemp[temp];
			glBindTexture(GL_TEXTURE_2D, train2_ID);
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			

			glTexCoord2f(0.0f, 0.0f);
			/*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
			glTexCoord2f(1.0f, 0.0f);
			/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
			glTexCoord2f(1.0f, 1.0f);
			/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);
			glTexCoord2f(0.0f, 1.0f);
			/*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);

			glTexCoord2f(0.0f, 0.0f);
			/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);
			glTexCoord2f(1.0f, 0.0f);
			/*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
			glTexCoord2f(1.0f, 1.0f);
			/*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);
			glTexCoord2f(0.0f, 1.0f);
			/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);
			 
			/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
			/*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
			/*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
			/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);
 
		//	glTexCoord2f(0.0f, 0.0f);
			/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);
		//	glTexCoord2f(1.0f, 0.0f);
			/*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);
		//	glTexCoord2f(1.0f, 1.0f);
			/*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);
		//	glTexCoord2f(0.0f, 1.0f);
			/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);

			glTexCoord2f(0.0f, 0.0f);
			/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
			glTexCoord2f(1.0f, 0.0f);
			/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);
			glTexCoord2f(1.0f, 1.0f);
			/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);
			glTexCoord2f(0.0f, 1.0f);
			/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);


			glTexCoord2f(0.0f, 0.0f);
			/*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
			glTexCoord2f(1.0f, 0.0f);
			/*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
			glTexCoord2f(1.0f, 1.0f);
			/*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);
			glTexCoord2f(0.0f, 1.0f);
			/*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);

			glEnd();
			glDisable(GL_TEXTURE_2D);

			glClearColor(200, 200, 200, 1);
		}

		//小吉
		temp = 11;
		forehead = (crosstemp[temp] * orienttemp[temp])*0.6f;
		Oh = orienttemp[temp] * 2;

		glBegin(GL_QUADS);//眼睛
		glColor3f(255, 255, 255);

		/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*6 + Oh.x * 6, postemp[temp].y - forehead.y + crosstemp[temp].y*6 + Oh.y * 6, postemp[temp].z - forehead.z + crosstemp[temp].z*6 + Oh.z * 6);
		/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *6 + Oh.x * 9, postemp[temp].y - forehead.y + crosstemp[temp].y*6 + Oh.y * 9, postemp[temp].z - forehead.z + crosstemp[temp].z*6 + Oh.z * 9);
		/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *6.3 + Oh.x * 9, postemp[temp].y - forehead.y + crosstemp[temp].y *6.3 + Oh.y * 9, postemp[temp].z - forehead.z + crosstemp[temp].z *6.3 + Oh.z * 9);
		/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *6.3 + Oh.x * 6, postemp[temp].y - forehead.y + crosstemp[temp].y *6.3+ Oh.y * 6, postemp[temp].z - forehead.z + crosstemp[temp].z  *6.3 + Oh.z * 6);


		/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*5.4 + Oh.x * 6, postemp[temp].y - forehead.y + crosstemp[temp].y*5.4 + Oh.y * 6, postemp[temp].z - forehead.z + crosstemp[temp].z*5.4 + Oh.z * 6);
		/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *5.4 + Oh.x * 9, postemp[temp].y - forehead.y + crosstemp[temp].y*5.4 + Oh.y * 9, postemp[temp].z - forehead.z + crosstemp[temp].z*5.4 + Oh.z * 9);
		/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *5.1 + Oh.x * 9, postemp[temp].y - forehead.y + crosstemp[temp].y *5.1 + Oh.y * 9, postemp[temp].z - forehead.z + crosstemp[temp].z *5.1 + Oh.z * 9);
		/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *5.1 + Oh.x * 6, postemp[temp].y - forehead.y + crosstemp[temp].y *5.1 + Oh.y * 6, postemp[temp].z - forehead.z + crosstemp[temp].z  *5.1 + Oh.z * 6);

		glEnd();

		glBegin(GL_QUADS);//嘴巴
			glColor3f(255, 0, 0);

			/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*5.4 + Oh.x, postemp[temp].y - forehead.y + crosstemp[temp].y*5.4 + Oh.y, postemp[temp].z - forehead.z + crosstemp[temp].z*5.4 + Oh.z);
			/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *5.4 + Oh.x * 4, postemp[temp].y - forehead.y + crosstemp[temp].y*5.4 + Oh.y * 4, postemp[temp].z - forehead.z + crosstemp[temp].z*5.4 + Oh.z * 4);
			/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *6 + Oh.x * 4, postemp[temp].y - forehead.y + crosstemp[temp].y *6 + Oh.y * 4, postemp[temp].z - forehead.z + crosstemp[temp].z *6 + Oh.z * 4);
			/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *6 + Oh.x, postemp[temp].y - forehead.y + crosstemp[temp].y *6 + Oh.y, postemp[temp].z - forehead.z + crosstemp[temp].z  *6 + Oh.z);

			glEnd();
		



		forehead = (crosstemp[temp] * orienttemp[temp])*0.59f;

		glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *6.4+ Oh.x * 5, postemp[temp].y + crosstemp[temp].y*6.4 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*6.4+ Oh.z * 5);
		/*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*6.2 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*6.2 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*6.2 + Oh.z * 5);
		/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *6.2 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*6.2 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*6.2 + Oh.z * 10);
		/*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*6.4 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y *6.4+ Oh.y * 10, postemp[temp].z + crosstemp[temp].z*6.4 + Oh.z * 10);

		/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*6.2 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*6.2 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*6.2 + Oh.z * 5);
		/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *6.2 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*6.2 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*6.2 + Oh.z * 10);
		/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x*6.4 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*6.4 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*6.4 + Oh.z * 10);
		/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x*6.4 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y *6.4 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*6.4 + Oh.z * 5);
	
		/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *6.2 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*6.2 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*6.2 + Oh.z * 10);
		/*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*6.4 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y *6.4 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*6.4 + Oh.z * 10);
		/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x*6.4 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*6.4 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*6.4 + Oh.z * 10);
		/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *6.2 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*6.2 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*6.2 + Oh.z * 10);

		/*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*6.4 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y *6.4 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*6.4 + Oh.z * 10);
		/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x*6.4 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*6.4 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*6.4 + Oh.z * 10);
		/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x*6.4 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y *6.4 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*6.4 + Oh.z * 5);
		/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *6.4 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*6.4 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*6.4 + Oh.z * 5);

		/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *6.4 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*6.4 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*6.4 + Oh.z * 5);
		/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x*6.4 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y *6.4 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*6.4 + Oh.z * 5);
		/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*6.2 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*6.2 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*6.2 + Oh.z * 5);
		/*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*6.2 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*6.2 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*6.2 + Oh.z * 5);

		/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*6.2 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*6.2 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*6.2 + Oh.z * 5);
		/*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*6.2 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*6.2 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*6.2 + Oh.z * 5);
		/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *6.2 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*6.2 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*6.2 + Oh.z * 10);
		/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *6.2 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*6.2 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*6.2 + Oh.z * 10);

		///
		/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *5+ Oh.x * 5, postemp[temp].y + crosstemp[temp].y*5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*5 + Oh.z * 5);
		/*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*5.5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*5.5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*5.5 + Oh.z * 5);
		/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *5.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*5.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*5.5 + Oh.z * 10);
		/*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*5 + Oh.z * 10);

		/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*5.5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*5.5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*5.5 + Oh.z * 5);
		/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *5.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*5.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*5.5 + Oh.z * 10);
		/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x*5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z *5+ Oh.z * 10);
		/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x*5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y *5+ Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*5 + Oh.z * 5);
	
		/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *5.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*5.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*5.5 + Oh.z * 10);
		/*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y * 5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z * 5 + Oh.z * 10);
		/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y * 5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z * 5 + Oh.z * 10);
		/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *5.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*5.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*5.5 + Oh.z * 10);
	
		/*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y * 5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z * 5 + Oh.z * 10);
		/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y * 5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z * 5 + Oh.z * 10);
		/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y * 5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z * 5 + Oh.z * 5);
		/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y * 5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z * 5 + Oh.z * 5);

		/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y * 5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z * 5 + Oh.z * 5);
		/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y * 5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z * 5 + Oh.z * 5);
		/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*5.5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*5.5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*5.5 + Oh.z * 5);
		/*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*5.5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*5.5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*5.5 + Oh.z * 5);

		/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*5.5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*5.5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*5.5 + Oh.z * 5);
		/*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*5.5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*5.5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*5.5 + Oh.z * 5);
		/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *5.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*5.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*5.5 + Oh.z * 10);
		/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *5.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*5.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*5.5 + Oh.z * 10);

		glEnd();
		glClearColor(0, 0, 0, 1);

		for (int b = 0; b < 6; b++)
		{
			temp = (postemp.size() - b +10) % postemp.size();
			forehead = crosstemp[temp] * orienttemp[temp];
			crosstemp[temp] = crosstemp[temp] * 0.8f;

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
			
			glBegin(GL_QUADS);

			/*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *6+ orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y*6 + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z *6+ orienttemp[temp].z * 3);
			/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *8+ orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y*8 + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z*8 + orienttemp[temp].z * 3);
			/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*8 + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y*8 + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z*8 + orienttemp[temp].z * 10);
			/*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*6 + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y*6 + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z *6+ orienttemp[temp].z * 10);

			/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x*8 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y*8 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z*8 + orienttemp[temp].z * 3);
			/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *6+ orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y*6 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z *6+ orienttemp[temp].z * 3);
			/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x*6 + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*6 + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*6 + orienttemp[temp].z * 10);
			/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x*8 + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*8 + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z *8+ orienttemp[temp].z * 10);

			/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 8 + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y * 8 + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z * 8 + orienttemp[temp].z * 3);
			/*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 6 + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y * 6 + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z * 6 + orienttemp[temp].z * 3);
			/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 6 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y * 6 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z * 6 + orienttemp[temp].z * 3);
			/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 8 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y * 8 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z * 8 + orienttemp[temp].z * 3);

			/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 8 + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y * 8 + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z * 8 + orienttemp[temp].z * 10);
			/*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 6 + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y * 6 + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z * 6 + orienttemp[temp].z * 10);
			/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 6 + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y * 6 + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z * 6 + orienttemp[temp].z * 10);
			/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 8 + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y * 8 + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z * 8 + orienttemp[temp].z * 10);

			/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 8 + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y * 8 + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z * 8 + orienttemp[temp].z * 3);
			/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 8 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y * 8 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z * 8 + orienttemp[temp].z * 3);
			/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 8 + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y * 8 + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z * 8 + orienttemp[temp].z * 10);
			/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 8 + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y * 8 + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z * 8 + orienttemp[temp].z * 10);

			/*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 6 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y * 6 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z * 6 + orienttemp[temp].z * 3);
			/*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 6 + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y * 6 + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z * 6 + orienttemp[temp].z * 3);
			/*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x * 6 + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y * 6 + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z * 6 + orienttemp[temp].z * 10);
			/*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x * 6 + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y * 6 + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z * 6 + orienttemp[temp].z * 10);

			glEnd();
			glDisable(GL_BLEND);

		}

		if (GS) {
			temp = (postemp.size() + 6) % postemp.size();
			forehead = crosstemp[temp] * orienttemp[temp];
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glColor4f(0.2f, 0.0f, 0.7f, 0.5f);

			glBegin(GL_QUADS);
			temp = (postemp.size() + 6) % postemp.size();
			glVertex3f(postemp[temp].x + orienttemp[temp].x * 15, postemp[temp].y + orienttemp[temp].y * 15, postemp[temp].z + orienttemp[temp].z * 15);
			glVertex3f(postemp[temp].x + orienttemp[temp].x * 30, postemp[temp].y + orienttemp[temp].y * 30, postemp[temp].z + orienttemp[temp].z * 30);
			temp = (postemp.size() + 9) % postemp.size();

			glVertex3f(postemp[temp].x - forehead.x + orienttemp[temp].x * 30, postemp[temp].y - forehead.y + orienttemp[temp].y * 30, postemp[temp].z - forehead.z + orienttemp[temp].z * 30);
			glVertex3f(postemp[temp].x - forehead.x + orienttemp[temp].x * 15, postemp[temp].y - forehead.y + orienttemp[temp].y * 15, postemp[temp].z - forehead.z + orienttemp[temp].z * 15);

			glEnd();

			glBegin(GL_TRIANGLES);
			temp = (postemp.size() +7) % postemp.size();
			glVertex3f(postemp[temp].x + orienttemp[temp].x * 15, postemp[temp].y + orienttemp[temp].y * 15, postemp[temp].z + orienttemp[temp].z * 15);
			temp = (postemp.size()+8) % postemp.size();
			glVertex3f(postemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + orienttemp[temp].z * 10);
			temp = (postemp.size()+9) % postemp.size();
			glVertex3f(postemp[temp].x + orienttemp[temp].x * 15, postemp[temp].y + orienttemp[temp].y * 15, postemp[temp].z + orienttemp[temp].z * 15);
			glEnd();
			glDisable(GL_BLEND);

		}


	
		break;
		 case 1://cube
			 temp = (t_time + 2) % postemp.size();
			 forehead = (crosstemp[temp] * orienttemp[temp])*0.6f;
			  Oh = orienttemp[temp] * bugOh;

			 glBegin(GL_QUADS);//眼睛
			 glColor3f(255, 255, 255);

			 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.6 + Oh.x * 6, postemp[temp].y - forehead.y + crosstemp[temp].y*0.6 + Oh.y * 6, postemp[temp].z - forehead.z + crosstemp[temp].z*0.6 + Oh.z * 6);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.6 + Oh.x * 9, postemp[temp].y - forehead.y + crosstemp[temp].y*0.6 + Oh.y * 9, postemp[temp].z - forehead.z + crosstemp[temp].z*0.6 + Oh.z * 9);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.9 + Oh.x * 9, postemp[temp].y - forehead.y + crosstemp[temp].y *0.9 + Oh.y * 9, postemp[temp].z - forehead.z + crosstemp[temp].z *0.9 + Oh.z * 9);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.9 + Oh.x * 6, postemp[temp].y - forehead.y + crosstemp[temp].y *0.9 + Oh.y * 6, postemp[temp].z - forehead.z + crosstemp[temp].z  *0.9 + Oh.z * 6);


			 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.6 + Oh.x * 6, postemp[temp].y - forehead.y - crosstemp[temp].y*0.6 + Oh.y * 6, postemp[temp].z - forehead.z - crosstemp[temp].z*0.6 + Oh.z * 6);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.6 + Oh.x * 9, postemp[temp].y - forehead.y - crosstemp[temp].y*0.6 + Oh.y * 9, postemp[temp].z - forehead.z - crosstemp[temp].z*0.6 + Oh.z * 9);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.9 + Oh.x * 9, postemp[temp].y - forehead.y - crosstemp[temp].y *0.9 + Oh.y * 9, postemp[temp].z - forehead.z - crosstemp[temp].z *0.9 + Oh.z * 9);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.9 + Oh.x * 6, postemp[temp].y - forehead.y - crosstemp[temp].y *0.9 + Oh.y * 6, postemp[temp].z - forehead.z - crosstemp[temp].z  *0.9 + Oh.z * 6);

			 glEnd();

			 if (bugOh != 1)
			 {
				 glBegin(GL_QUADS);//嘴巴
				 glColor3f(255, 0, 0);

				 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.6 + Oh.x, postemp[temp].y - forehead.y - crosstemp[temp].y*0.6 + Oh.y, postemp[temp].z - forehead.z - crosstemp[temp].z*0.6 + Oh.z);
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.6 + Oh.x * 4, postemp[temp].y - forehead.y - crosstemp[temp].y*0.6 + Oh.y * 4, postemp[temp].z - forehead.z - crosstemp[temp].z*0.6 + Oh.z * 4);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.6 + Oh.x * 4, postemp[temp].y - forehead.y + crosstemp[temp].y *0.6 + Oh.y * 4, postemp[temp].z - forehead.z + crosstemp[temp].z *0.6 + Oh.z * 4);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.6 + Oh.x, postemp[temp].y - forehead.y + crosstemp[temp].y *0.6 + Oh.y, postemp[temp].z - forehead.z + crosstemp[temp].z  *0.6 + Oh.z);

				 glEnd();
			 }


			 forehead = (crosstemp[temp] * orienttemp[temp])*0.59f;

			 glBegin(GL_QUADS);
			 glColor3f(0, 0, 0);
			 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z + crosstemp[temp].z + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z + crosstemp[temp].z + Oh.z * 10);

			 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 10);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 5);

			 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z + crosstemp[temp].z + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 10);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 10);

			 /*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z + crosstemp[temp].z + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 10);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 5);
			 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z + crosstemp[temp].z + Oh.z * 5);

			 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z + crosstemp[temp].z + Oh.z * 5);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 5);
			 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 5);

			 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 10);

			 ///
			 /*1*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - crosstemp[temp].z + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*3*/	glVertex3f(postemp[temp].x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - crosstemp[temp].z + Oh.z * 10);

			 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 10);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 5);

			 /*3*/	glVertex3f(postemp[temp].x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - crosstemp[temp].z + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 10);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 10);

			 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - crosstemp[temp].z + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 10);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 5);
			 /*1*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - crosstemp[temp].z + Oh.z * 5);

			 /*1*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - crosstemp[temp].z + Oh.z * 5);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 5);
			 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 5);

			 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*3*/	glVertex3f(postemp[temp].x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 10);

			 glEnd();
			 glClearColor(0, 0, 0, 1);

			 for (int b = 0; b < box * 2; b++)
			 {
				 temp = (t_time + postemp.size() - b * 1) % postemp.size();
				 forehead = crosstemp[temp] * orienttemp[temp];
				 crosstemp[temp] = crosstemp[temp] * 0.8f;

				 glEnable(GL_BLEND);
				 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				 glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
				 if (b == box * 2 - 1 && bugOh>1)
				 {
					 glColor4f(1.0f, 0.8f, 0.0f, 0.4f);
				 }
				 glBegin(GL_QUADS);

				 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
				 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
				 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);
				 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);

				 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);

				 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
				 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
				 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);

				 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);
				 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);

				 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
				 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);
				 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);

				 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
				 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
				 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);

				 glEnd();
				 glDisable(GL_BLEND);

				 if (wheel)
				 {
					 if (t_time % 2 == 0)
					 {
						 glBegin(GL_POLYGON);
						 glColor3d(0, 0, 0);
						 /*0*/	glVertex3f(postemp[temp].x - forehead.x*0.5 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.5 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.5 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						 /*1*/	glVertex3f(postemp[temp].x - forehead.x*0.3 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.3 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.3 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						 /*2*/	glVertex3f(postemp[temp].x - forehead.x*0.4 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						 /*3*/	glVertex3f(postemp[temp].x - forehead.x*0.6 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.6 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.6 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						 /*4*/	glVertex3f(postemp[temp].x - forehead.x*0.7 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.7 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.7 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						 /*5*/	glVertex3f(postemp[temp].x - forehead.x*0.6 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.6 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.6 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						 /*6*/	glVertex3f(postemp[temp].x - forehead.x*0.4 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.4 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.4 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						 /*1*/	glVertex3f(postemp[temp].x - forehead.x*0.3 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.3 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.3 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);

						 glEnd();

						 glBegin(GL_POLYGON);
						 glColor3d(0, 0, 0);
						 /*0*/	glVertex3f(postemp[temp].x - forehead.x*0.5 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.5 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.5 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						 /*1*/	glVertex3f(postemp[temp].x - forehead.x*0.3 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.3 + -crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.3 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						 /*2*/	glVertex3f(postemp[temp].x - forehead.x*0.4 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						 /*3*/	glVertex3f(postemp[temp].x - forehead.x*0.6 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.6 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.6 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						 /*4*/	glVertex3f(postemp[temp].x - forehead.x*0.7 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.7 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.7 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						 /*5*/	glVertex3f(postemp[temp].x - forehead.x*0.6 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.6 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.6 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						 /*6*/	glVertex3f(postemp[temp].x - forehead.x*0.4 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.4 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.4 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						 /*1*/	glVertex3f(postemp[temp].x - forehead.x*0.3 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.3 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.3 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);

						 glEnd();
					 }
					 else
					 {
						 glBegin(GL_POLYGON);
						 glColor3d(0, 0, 0);
						 /*0*/	glVertex3f(postemp[temp].x - forehead.x*0.5 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.5 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.5 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						 /*1*/	glVertex3f(postemp[temp].x - forehead.x*0.4 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						 /*2*/	glVertex3f(postemp[temp].x - forehead.x*0.5 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 5, postemp[temp].y - forehead.y*0.5 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 5, postemp[temp].z - forehead.z*0.5 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 5);
						 /*3*/	glVertex3f(postemp[temp].x - forehead.x*0.6 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.6 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.6 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						 /*4*/	glVertex3f(postemp[temp].x - forehead.x*0.6 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.6 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.6 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						 /*5*/	glVertex3f(postemp[temp].x - forehead.x*0.5 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 1, postemp[temp].y - forehead.y*0.5 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 1, postemp[temp].z - forehead.z*0.5 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 1);
						 /*6*/	glVertex3f(postemp[temp].x - forehead.x*0.4 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.4 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.4 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						 /*1*/	glVertex3f(postemp[temp].x - forehead.x*0.4 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);

						 glEnd();


						 glBegin(GL_POLYGON);
						 glColor3d(0, 0, 0);
						 /*0*/	glVertex3f(postemp[temp].x - forehead.x*0.5 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.5 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.5 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						 /*1*/	glVertex3f(postemp[temp].x - forehead.x*0.4 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						 /*2*/	glVertex3f(postemp[temp].x - forehead.x*0.5 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 5, postemp[temp].y - forehead.y*0.5 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 5, postemp[temp].z - forehead.z*0.5 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 5);
						 /*3*/	glVertex3f(postemp[temp].x - forehead.x*0.6 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.6 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.6 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						 /*4*/	glVertex3f(postemp[temp].x - forehead.x*0.6 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.6 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.6 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						 /*5*/	glVertex3f(postemp[temp].x - forehead.x*0.5 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 1, postemp[temp].y - forehead.y*0.5 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 1, postemp[temp].z - forehead.z*0.5 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 1);
						 /*6*/	glVertex3f(postemp[temp].x - forehead.x*0.4 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.4 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.4 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						 /*1*/	glVertex3f(postemp[temp].x - forehead.x*0.4 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);

						 glEnd();
					 }

				 }

			 }

			 if (GS) {

				 forehead = crosstemp[temp] * orienttemp[temp];
				 glEnable(GL_BLEND);
				 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				 glColor4f(0.2f, 0.0f, 0.7f, 0.5f);

				 glBegin(GL_QUADS);
				 temp = (t_time + postemp.size() - 4) % postemp.size();
				 glVertex3f(postemp[temp].x + orienttemp[temp].x * 15, postemp[temp].y + orienttemp[temp].y * 15, postemp[temp].z + orienttemp[temp].z * 15);
				 glVertex3f(postemp[temp].x + orienttemp[temp].x * 30, postemp[temp].y + orienttemp[temp].y * 30, postemp[temp].z + orienttemp[temp].z * 30);
				 temp = t_time% postemp.size();
				 glVertex3f(postemp[temp].x - forehead.x + orienttemp[temp].x * 30, postemp[temp].y - forehead.y + orienttemp[temp].y * 30, postemp[temp].z - forehead.z + orienttemp[temp].z * 30);
				 glVertex3f(postemp[temp].x - forehead.x + orienttemp[temp].x * 15, postemp[temp].y - forehead.y + orienttemp[temp].y * 15, postemp[temp].z - forehead.z + orienttemp[temp].z * 15);

				 glEnd();

				 glBegin(GL_TRIANGLES);
				 temp = (t_time + postemp.size() - 1) % postemp.size();
				 glVertex3f(postemp[temp].x + orienttemp[temp].x * 15, postemp[temp].y + orienttemp[temp].y * 15, postemp[temp].z + orienttemp[temp].z * 15);
				 temp = (t_time + postemp.size() - 2) % postemp.size();
				 glVertex3f(postemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + orienttemp[temp].z * 10);
				 temp = (t_time + postemp.size() - 3) % postemp.size();
				 glVertex3f(postemp[temp].x + orienttemp[temp].x * 15, postemp[temp].y + orienttemp[temp].y * 15, postemp[temp].z + orienttemp[temp].z * 15);
				 glEnd();
				 glDisable(GL_BLEND);

			 }

			 break;
		 case 2://蟲蟲
			 temp = (t_time+2) % postemp.size();
			 forehead = (crosstemp[temp] * orienttemp[temp])*0.6f;
				Oh = orienttemp[temp] * bugOh;

			 glBegin(GL_QUADS);//眼睛
			 glColor3f(255, 255, 255);

			 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.6 + Oh.x * 6, postemp[temp].y - forehead.y + crosstemp[temp].y*0.6 + Oh.y * 6, postemp[temp].z - forehead.z + crosstemp[temp].z*0.6 + Oh.z * 6);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.6 + Oh.x * 9, postemp[temp].y - forehead.y + crosstemp[temp].y*0.6 + Oh.y * 9, postemp[temp].z - forehead.z + crosstemp[temp].z*0.6 + Oh.z * 9);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.9 + Oh.x * 9, postemp[temp].y - forehead.y + crosstemp[temp].y *0.9 + Oh.y * 9, postemp[temp].z - forehead.z + crosstemp[temp].z *0.9 + Oh.z * 9);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.9 + Oh.x * 6, postemp[temp].y - forehead.y + crosstemp[temp].y *0.9 + Oh.y * 6, postemp[temp].z - forehead.z + crosstemp[temp].z  *0.9 + Oh.z * 6);


			 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.6 + Oh.x * 6, postemp[temp].y - forehead.y - crosstemp[temp].y*0.6 + Oh.y * 6, postemp[temp].z - forehead.z - crosstemp[temp].z*0.6 + Oh.z * 6);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.6 + Oh.x * 9, postemp[temp].y - forehead.y - crosstemp[temp].y*0.6 + Oh.y * 9, postemp[temp].z - forehead.z - crosstemp[temp].z*0.6 + Oh.z * 9);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.9 + Oh.x * 9, postemp[temp].y - forehead.y - crosstemp[temp].y *0.9 + Oh.y * 9, postemp[temp].z - forehead.z - crosstemp[temp].z *0.9 + Oh.z * 9);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.9 + Oh.x * 6, postemp[temp].y - forehead.y - crosstemp[temp].y *0.9 + Oh.y * 6, postemp[temp].z - forehead.z - crosstemp[temp].z  *0.9 + Oh.z * 6);

			 glEnd();

			 if (bugOh!=1)
			 {
				 glBegin(GL_QUADS);//嘴巴
				 glColor3f(255, 0, 0);

				 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.6 + Oh.x, postemp[temp].y - forehead.y - crosstemp[temp].y*0.6 + Oh.y , postemp[temp].z - forehead.z - crosstemp[temp].z*0.6 + Oh.z );
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.6 + Oh.x * 4, postemp[temp].y - forehead.y - crosstemp[temp].y*0.6 + Oh.y * 4, postemp[temp].z - forehead.z - crosstemp[temp].z*0.6 + Oh.z * 4);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.6 + Oh.x * 4, postemp[temp].y - forehead.y + crosstemp[temp].y *0.6 + Oh.y * 4, postemp[temp].z - forehead.z + crosstemp[temp].z *0.6 + Oh.z * 4);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.6 + Oh.x , postemp[temp].y - forehead.y + crosstemp[temp].y *0.6 + Oh.y , postemp[temp].z - forehead.z + crosstemp[temp].z  *0.6 + Oh.z );

				 glEnd();
			 }
			

			 forehead = (crosstemp[temp] * orienttemp[temp])*0.59f;

			 glBegin(GL_QUADS);
			 glColor3f(0, 0, 0);
			 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z + crosstemp[temp].z + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*0.5  + Oh.x * 5 , postemp[temp].y + crosstemp[temp].y*0.5	 + Oh.y * 5 , postemp[temp].z + crosstemp[temp].z*0.5	 + Oh.z * 5);
			 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x		+ Oh.x * 10, postemp[temp].y + crosstemp[temp].y		 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z		 + Oh.z * 10);

			 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.5 + Oh.x * 5	, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 5	, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 10		, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 10		, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 10);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 5);

			 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z + crosstemp[temp].z + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 10);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 10);
			
			 /*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z + crosstemp[temp].z + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 10);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 5);
			 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z + crosstemp[temp].z + Oh.z * 5);

			 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z + crosstemp[temp].z + Oh.z * 5);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 5);
			 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 5);
		
			 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 10);

			 ///
			 /*1*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - crosstemp[temp].z + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*3*/	glVertex3f(postemp[temp].x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - crosstemp[temp].z + Oh.z * 10);

			 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 10);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 5);

			 /*3*/	glVertex3f(postemp[temp].x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - crosstemp[temp].z + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 10);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 10);

			 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - crosstemp[temp].z + Oh.z * 10);
			 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 10);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 5);
			 /*1*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - crosstemp[temp].z + Oh.z * 5);

			 /*1*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - crosstemp[temp].z + Oh.z * 5);
			 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 5);
			 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 5);

			 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 5);
			 /*3*/	glVertex3f(postemp[temp].x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 10);
			 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 10);

 			 glEnd();
			 glClearColor(0,0,0,1);
			 
			 for (int b = 0; b < box*2; b++)
			 {
				temp = (t_time + postemp.size() - b * 1) % postemp.size();
				forehead = crosstemp[temp] * orienttemp[temp];
				crosstemp[temp] = crosstemp[temp] * 0.8f;

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glColor4f(0.0f, 1.0f, 0.0f, 0.4f);
				if (b == box * 2 - 1&& bugOh>1)
				{
					glColor4f(1.0f, 0.8f, 0.0f, 0.4f);
				}
				glBegin(GL_QUADS);
				
				/*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
				/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
				/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);
				/*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);

				/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);
				/*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
				/*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);
				/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);

				/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
				/*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
				/*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
				/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);

				/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);
				/*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);
				/*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);
				/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);

				/*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
				/*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);
				/*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);
				/*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);

				/*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
				/*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
				/*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);
				/*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);

				glEnd();
				glDisable(GL_BLEND);

				if (wheel)
				{
					if (t_time%2==0)
					{
						glBegin(GL_POLYGON);
						glColor3d(0, 0, 0);
						/*0*/	glVertex3f(postemp[temp].x - forehead.x*0.5 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.5 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.5 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						/*1*/	glVertex3f(postemp[temp].x - forehead.x*0.3 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.3 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.3 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						/*2*/	glVertex3f(postemp[temp].x - forehead.x*0.4 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						/*3*/	glVertex3f(postemp[temp].x - forehead.x*0.6 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.6 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.6 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						/*4*/	glVertex3f(postemp[temp].x - forehead.x*0.7 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.7 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.7 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						/*5*/	glVertex3f(postemp[temp].x - forehead.x*0.6 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.6 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.6 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						/*6*/	glVertex3f(postemp[temp].x - forehead.x*0.4 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.4 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.4 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						/*1*/	glVertex3f(postemp[temp].x - forehead.x*0.3 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.3 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.3 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);

						glEnd();

						glBegin(GL_POLYGON);
						glColor3d(0, 0, 0);
						/*0*/	glVertex3f(postemp[temp].x - forehead.x*0.5 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.5 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.5 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						/*1*/	glVertex3f(postemp[temp].x - forehead.x*0.3 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.3 + -crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.3 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						/*2*/	glVertex3f(postemp[temp].x - forehead.x*0.4 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						/*3*/	glVertex3f(postemp[temp].x - forehead.x*0.6 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.6 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.6 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						/*4*/	glVertex3f(postemp[temp].x - forehead.x*0.7 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.7 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.7 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						/*5*/	glVertex3f(postemp[temp].x - forehead.x*0.6 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.6 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.6 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						/*6*/	glVertex3f(postemp[temp].x - forehead.x*0.4 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.4 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.4 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						/*1*/	glVertex3f(postemp[temp].x - forehead.x*0.3 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.3 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.3 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);

						glEnd();
					}
					else
					{
						glBegin(GL_POLYGON);
						glColor3d(0, 0, 0);
						/*0*/	glVertex3f(postemp[temp].x - forehead.x*0.5 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.5 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.5 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						/*1*/	glVertex3f(postemp[temp].x - forehead.x*0.4 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						/*2*/	glVertex3f(postemp[temp].x - forehead.x*0.5 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 5, postemp[temp].y - forehead.y*0.5 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 5, postemp[temp].z - forehead.z*0.5 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 5);
						/*3*/	glVertex3f(postemp[temp].x - forehead.x*0.6 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.6 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.6 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						/*4*/	glVertex3f(postemp[temp].x - forehead.x*0.6 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.6 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.6 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						/*5*/	glVertex3f(postemp[temp].x - forehead.x*0.5 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 1, postemp[temp].y - forehead.y*0.5 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 1, postemp[temp].z - forehead.z*0.5 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 1);
						/*6*/	glVertex3f(postemp[temp].x - forehead.x*0.4 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.4 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.4 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						/*1*/	glVertex3f(postemp[temp].x - forehead.x*0.4 - crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 - crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 - crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);

						glEnd();


						glBegin(GL_POLYGON);
						glColor3d(0, 0, 0);
						/*0*/	glVertex3f(postemp[temp].x - forehead.x*0.5 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 3, postemp[temp].y - forehead.y*0.5 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 3, postemp[temp].z - forehead.z*0.5 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 3);
						/*1*/	glVertex3f(postemp[temp].x - forehead.x*0.4 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						/*2*/	glVertex3f(postemp[temp].x - forehead.x*0.5 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 5, postemp[temp].y - forehead.y*0.5 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 5, postemp[temp].z - forehead.z*0.5 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 5);
						/*3*/	glVertex3f(postemp[temp].x - forehead.x*0.6 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.6 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.6 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);
						/*4*/	glVertex3f(postemp[temp].x - forehead.x*0.6 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.6 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.6 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						/*5*/	glVertex3f(postemp[temp].x - forehead.x*0.5 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 1, postemp[temp].y - forehead.y*0.5 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 1, postemp[temp].z - forehead.z*0.5 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 1);
						/*6*/	glVertex3f(postemp[temp].x - forehead.x*0.4 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 2, postemp[temp].y - forehead.y*0.4 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 2, postemp[temp].z - forehead.z*0.4 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 2);
						/*1*/	glVertex3f(postemp[temp].x - forehead.x*0.4 + crosstemp[temp].x *1.1 + orienttemp[temp].x * 4, postemp[temp].y - forehead.y*0.4 + crosstemp[temp].y *1.1 + orienttemp[temp].y * 4, postemp[temp].z - forehead.z*0.4 + crosstemp[temp].z *1.1 + orienttemp[temp].z * 4);

						glEnd();
					}
				
				}
				
			 }
			 
			 if (GS) {
				 
					 forehead = crosstemp[temp] * orienttemp[temp];
					 glEnable(GL_BLEND);
					 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					 glColor4f(0.2f, 0.0f, 0.7f, 0.5f);
					
					 glBegin(GL_QUADS);
					 temp = (t_time + postemp.size() - 4) % postemp.size();
						glVertex3f(postemp[temp].x + orienttemp[temp].x * 15, postemp[temp].y + orienttemp[temp].y * 15, postemp[temp].z + orienttemp[temp].z * 15);
						glVertex3f(postemp[temp].x + orienttemp[temp].x * 30, postemp[temp].y + orienttemp[temp].y * 30, postemp[temp].z + orienttemp[temp].z * 30);
					temp = t_time% postemp.size();
						glVertex3f(postemp[temp].x - forehead.x + orienttemp[temp].x * 30, postemp[temp].y - forehead.y + orienttemp[temp].y * 30, postemp[temp].z - forehead.z + orienttemp[temp].z * 30);
						glVertex3f(postemp[temp].x - forehead.x + orienttemp[temp].x * 15, postemp[temp].y - forehead.y + orienttemp[temp].y * 15, postemp[temp].z - forehead.z + orienttemp[temp].z * 15);

						glEnd();

					glBegin(GL_TRIANGLES);
					temp = (t_time + postemp.size() - 1) % postemp.size();
						glVertex3f(postemp[temp].x + orienttemp[temp].x * 15, postemp[temp].y + orienttemp[temp].y * 15, postemp[temp].z + orienttemp[temp].z * 15);
					temp = (t_time + postemp.size() - 2) % postemp.size();
						glVertex3f(postemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + orienttemp[temp].z * 10);
					temp = (t_time + postemp.size() - 3) % postemp.size();
						glVertex3f(postemp[temp].x + orienttemp[temp].x * 15, postemp[temp].y + orienttemp[temp].y * 15, postemp[temp].z + orienttemp[temp].z * 15);
						glEnd();
					 glDisable(GL_BLEND);
					
				 }
			 



			 ///小原
			 if (people!=0)
			 {
				 int flag = 0;
				 if (people==1)
				 {
					 flag = 12;
				 }
				 
				 temp = (t_time + flag) % postemp.size();
				 forehead = (crosstemp[temp] * orienttemp[temp])*0.6f;
				 Oh = orienttemp[temp];
				 if (people == 2)
				 {
					 Oh = orienttemp[temp] *1.5;
				 }
				 glBegin(GL_QUADS);//眼睛
				 glColor3f(255, 255, 255);

				 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.6 + Oh.x * 6, postemp[temp].y - forehead.y + crosstemp[temp].y*0.6 + Oh.y * 6, postemp[temp].z - forehead.z + crosstemp[temp].z*0.6 + Oh.z * 6);
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.6 + Oh.x * 9, postemp[temp].y - forehead.y + crosstemp[temp].y*0.6 + Oh.y * 9, postemp[temp].z - forehead.z + crosstemp[temp].z*0.6 + Oh.z * 9);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.9 + Oh.x * 9, postemp[temp].y - forehead.y + crosstemp[temp].y *0.9 + Oh.y * 9, postemp[temp].z - forehead.z + crosstemp[temp].z *0.9 + Oh.z * 9);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.9 + Oh.x * 6, postemp[temp].y - forehead.y + crosstemp[temp].y *0.9 + Oh.y * 6, postemp[temp].z - forehead.z + crosstemp[temp].z  *0.9 + Oh.z * 6);


				 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.6 + Oh.x * 6, postemp[temp].y - forehead.y - crosstemp[temp].y*0.6 + Oh.y * 6, postemp[temp].z - forehead.z - crosstemp[temp].z*0.6 + Oh.z * 6);
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.6 + Oh.x * 9, postemp[temp].y - forehead.y - crosstemp[temp].y*0.6 + Oh.y * 9, postemp[temp].z - forehead.z - crosstemp[temp].z*0.6 + Oh.z * 9);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.9 + Oh.x * 9, postemp[temp].y - forehead.y - crosstemp[temp].y *0.9 + Oh.y * 9, postemp[temp].z - forehead.z - crosstemp[temp].z *0.9 + Oh.z * 9);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.9 + Oh.x * 6, postemp[temp].y - forehead.y - crosstemp[temp].y *0.9 + Oh.y * 6, postemp[temp].z - forehead.z - crosstemp[temp].z  *0.9 + Oh.z * 6);

				 glEnd();


				 forehead = (crosstemp[temp] * orienttemp[temp])*0.59f;

				 glBegin(GL_QUADS);
				 glColor3f(0, 0, 0);
				 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z + crosstemp[temp].z + Oh.z * 5);
				 /*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 5);
				 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 10);
				 /*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z + crosstemp[temp].z + Oh.z * 10);

				 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 5);
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 10);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 10);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 5);

				 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 10);
				 /*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z + crosstemp[temp].z + Oh.z * 10);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 10);
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 10);

				 /*4*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z + crosstemp[temp].z + Oh.z * 10);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 10);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 5);
				 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z + crosstemp[temp].z + Oh.z * 5);

				 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z + crosstemp[temp].z + Oh.z * 5);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z + Oh.z * 5);
				 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 5);
				 /*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 5);

				 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 5);
				 /*2*/	glVertex3f(postemp[temp].x + crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 5);
				 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z + crosstemp[temp].z*0.5 + Oh.z * 10);
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z*0.5 + Oh.z * 10);

				 ///
				 /*1*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - crosstemp[temp].z + Oh.z * 5);
				 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 5);
				 /*3*/	glVertex3f(postemp[temp].x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 10);
				 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - crosstemp[temp].z + Oh.z * 10);

				 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 5);
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 10);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 10);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 5);

				 /*3*/	glVertex3f(postemp[temp].x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 10);
				 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - crosstemp[temp].z + Oh.z * 10);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 10);
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 10);

				 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - crosstemp[temp].z + Oh.z * 10);
				 /*7*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 10);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 5);
				 /*1*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - crosstemp[temp].z + Oh.z * 5);

				 /*1*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - crosstemp[temp].z + Oh.z * 5);
				 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z + Oh.z * 5);
				 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 5);
				 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 5);

				 /*5*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x	*0.5 + Oh.x * 5, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 5);
				 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x*0.5 + Oh.x * 5, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 5, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 5);
				 /*3*/	glVertex3f(postemp[temp].x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - crosstemp[temp].z*0.5 + Oh.z * 10);
				 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x *0.5 + Oh.x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y*0.5 + Oh.y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z*0.5 + Oh.z * 10);

				 glEnd();
				 glClearColor(0, 0, 0, 1);

				 for (int b = 0; b < box; b++)
				 {
					 temp = (t_time + flag -1+ postemp.size()*2 - b * 1) % postemp.size();
					 forehead = crosstemp[temp] * orienttemp[temp];
		
					 if (people==2)
					 {
						 orienttemp[temp] = orienttemp[temp] * 1.5;
						 
						 
					 }

					 glEnable(GL_BLEND);
					 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					 glColor4f(1.0f, 0.1f, 0.0f, 0.4f);
					 glBegin(GL_QUADS);

					 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
					 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
					 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);
					 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);

					 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);
					 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
					 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);
					 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);

					 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
					 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
					 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
					 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);

					 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);
					 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);
					 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);
					 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);

					 /*1*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 3);
					 /*5*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 3);
					 /*7*/	glVertex3f(postemp[temp].x - forehead.x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z + crosstemp[temp].z + orienttemp[temp].z * 10);
					 /*3*/	glVertex3f(postemp[temp].x + crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y + crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z + crosstemp[temp].z + orienttemp[temp].z * 10);

					 /*6*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 3);
					 /*2*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 3, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 3, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 3);
					 /*4*/	glVertex3f(postemp[temp].x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - crosstemp[temp].z + orienttemp[temp].z * 10);
					 /*8*/	glVertex3f(postemp[temp].x - forehead.x - crosstemp[temp].x + orienttemp[temp].x * 10, postemp[temp].y - forehead.y - crosstemp[temp].y + orienttemp[temp].y * 10, postemp[temp].z - forehead.z - crosstemp[temp].z + orienttemp[temp].z * 10);

					 glEnd();
					 glDisable(GL_BLEND);

				 }
				 
				 if (YS) {
					
					 forehead = crosstemp[temp] * orienttemp[temp];
					 glEnable(GL_BLEND);
					 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					 glColor4f(1.0f, 0.2f, 0.2f, 0.5f);
					 glBegin(GL_QUADS);
					 temp = (t_time + flag + postemp.size() - 3) % postemp.size(); orienttemp[temp].normalize();
					 glVertex3f(postemp[temp].x + orienttemp[temp].x * 15+ crosstemp[temp].x*0.5, postemp[temp].y + orienttemp[temp].y * 15 + crosstemp[temp].y*0.5, postemp[temp].z + orienttemp[temp].z * 15 + crosstemp[temp].z*0.5);
					 glVertex3f(postemp[temp].x + orienttemp[temp].x * 30 + crosstemp[temp].x*0.5, postemp[temp].y + orienttemp[temp].y * 30 + crosstemp[temp].y*0.5, postemp[temp].z + orienttemp[temp].z * 30 + crosstemp[temp].z*0.5);
					 temp = (t_time + flag+1) % postemp.size(); orienttemp[temp].normalize();
					 glVertex3f(postemp[temp].x - forehead.x + orienttemp[temp].x * 30 + crosstemp[temp].x*0.5, postemp[temp].y - forehead.y + orienttemp[temp].y * 30 + crosstemp[temp].y*0.5, postemp[temp].z - forehead.z + orienttemp[temp].z * 30 + crosstemp[temp].z*0.5);
					 glVertex3f(postemp[temp].x - forehead.x + orienttemp[temp].x * 15 + crosstemp[temp].x*0.5, postemp[temp].y - forehead.y + orienttemp[temp].y * 15 + crosstemp[temp].y*0.5, postemp[temp].z - forehead.z + orienttemp[temp].z * 15 + crosstemp[temp].z*0.5);

					 glEnd();

					 glBegin(GL_TRIANGLES);
					 temp = (t_time + flag ) % postemp.size(); orienttemp[temp].normalize();
					 glVertex3f(postemp[temp].x + orienttemp[temp].x * 15 + crosstemp[temp].x*0.5, postemp[temp].y + orienttemp[temp].y * 15 + crosstemp[temp].y*0.5, postemp[temp].z + orienttemp[temp].z * 15 + crosstemp[temp].z*0.5);
					 temp = (t_time + flag-1) % postemp.size(); orienttemp[temp].normalize();
					 glVertex3f(postemp[temp].x + orienttemp[temp].x * 10 + crosstemp[temp].x*0.5, postemp[temp].y + orienttemp[temp].y * 10 + crosstemp[temp].y*0.5, postemp[temp].z + orienttemp[temp].z * 10 + crosstemp[temp].z*0.5);
					 temp = (t_time + flag-2) % postemp.size(); orienttemp[temp].normalize();
					 glVertex3f(postemp[temp].x + orienttemp[temp].x * 15 + crosstemp[temp].x*0.5, postemp[temp].y + orienttemp[temp].y * 15 + crosstemp[temp].y*0.5, postemp[temp].z + orienttemp[temp].z * 15 + crosstemp[temp].z*0.5);
					 glEnd();
					 glDisable(GL_BLEND);

				 }
			 }

			
			 break;

		
	}
	
	 
	postemp.clear();
	orienttemp.clear();
	crosstemp.clear();
	qtstemp.clear();
  
	//####################################################################
#ifdef EXAMPLE_SOLUTION
	// don't draw the train if you're looking out the front window
	if (!tw->trainCam->value())
		drawTrain(this, doingShadows);
#endif
}

void TrainView::
	doPick(int mx, int my)
	//========================================================================
{
	// since we'll need to do some GL stuff so we make this window as 
	// active window
	makeCurrent();

	// get the viewport - most reliable way to turn mouse coords into GL coords
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();

	gluPickMatrix((double)mx, (double)(viewport[3]-my), 
		5, 5, viewport);

	// now set up the projection
	setProjection();

	// now draw the objects - but really only see what we hit
	GLuint buf[100];
	glSelectBuffer(100,buf);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);


	// draw the cubes, loading the names as we go
	for(size_t i=0; i<m_pTrack->points.size(); ++i) {
		glLoadName((GLuint) (i+1));
		m_pTrack->points[i].draw();
	}

	// go back to drawing mode, and see how picking did
	int hits = glRenderMode(GL_RENDER);
	if (hits) {
		// warning; this just grabs the first object hit - if there
		// are multiple objects, you really want to pick the closest
		// one - see the OpenGL manual 
		// remember: we load names that are one more than the index
		selectedCube = buf[3]-1;
	} else // nothing hit, nothing selected
		selectedCube = -1;
}

void TrainView::loadTexture2D(QString str, GLuint & textureID)
{

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	QImage img(str);
	QImage opengl_grass = QGLWidget::convertToGLFormat(img); 

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, opengl_grass.width(), opengl_grass.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, opengl_grass.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_2D);
}

void TrainView::drawOther()
{
	{

		int skyedge = 1500;
		//天空盒
		if (trainShape != 1)
			glBindTexture(GL_TEXTURE_2D, Sky[0]);
		else
			glBindTexture(GL_TEXTURE_2D, ground2);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(skyedge, skyedge, -skyedge);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(skyedge, skyedge, skyedge);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-skyedge, skyedge, skyedge);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-skyedge, skyedge, -skyedge);
		glEnd();

		if (trainShape != 1)
			glBindTexture(GL_TEXTURE_2D, Sky[0]);
		else
			glBindTexture(GL_TEXTURE_2D, ground2);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(skyedge, -skyedge, -skyedge);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(skyedge, -skyedge, skyedge);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-skyedge, -skyedge, skyedge);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-skyedge, -skyedge, -skyedge);
		glEnd();

		if (trainShape != 1)
			glBindTexture(GL_TEXTURE_2D, Sky[2]);
		else
			glBindTexture(GL_TEXTURE_2D, ground2);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-skyedge, skyedge, skyedge);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-skyedge, -skyedge, skyedge);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(skyedge, -skyedge, skyedge);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(skyedge, skyedge, skyedge);

		glEnd();

		if (trainShape != 1)
			glBindTexture(GL_TEXTURE_2D, Sky[3]);
		else
			glBindTexture(GL_TEXTURE_2D, ground2);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(skyedge, skyedge, -skyedge);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(skyedge, -skyedge, -skyedge);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-skyedge, -skyedge, -skyedge);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-skyedge, skyedge, -skyedge);
		glEnd();

		if (trainShape != 1)
			glBindTexture(GL_TEXTURE_2D, Sky[4]);
		else
			glBindTexture(GL_TEXTURE_2D, ground2);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-skyedge, -skyedge, -skyedge);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-skyedge, -skyedge, skyedge);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-skyedge, skyedge, skyedge);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-skyedge, skyedge, -skyedge);
		glEnd();


		if (trainShape != 1)
			glBindTexture(GL_TEXTURE_2D, Sky[5]);
		else
			glBindTexture(GL_TEXTURE_2D, ground2);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(skyedge, skyedge, -skyedge);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(skyedge, -skyedge, -skyedge);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(skyedge, -skyedge, skyedge);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(skyedge, skyedge, skyedge);

		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	GLUquadricObj *t = gluNewQuadric();
	switch (trainShape)
	{
	case 0:
		//地板
		drawCube(-150, -50, -150,10, 300, 300, citywall2, 3,3, 0.5);
		drawCube(-180, -38, -180, 2, 80, 80, water, 1, 1, 0.5);
		drawCube(-180, -40, -180, 2, 100, 100, ground3, 1, 1, 0.5);
		drawCube(-100, -40, 100, 120, 50, 50, ground1, 1, 1, 2);
		drawCube(20, -40, -150, 80, 30, 30, building1, 1, 1, 1);

		drawBuilding(100, 100, 100, 40, 40, building1, 1, 1, 2);
		drawBuilding(90,80,20, 20, 60, citywall4, 1, 1, 1);
		drawBuilding(40, -3, 20, 120,200, ground3, 2, 2, 1);
	
		drawBuilding(120, -3, -160, 50, 50, ground3, 2, 2, 1);
		drawCube(-80, 150, 20, 60, 30, 30, citywall1, 1, 1, 1);
		drawCube(-30, 150, -20, 80, 50, 20, citywall3, 1, 1, 1);
		drawCube(80, 150, -80, 50, 20, 20, citywall2, 1, 1, 1);


		drawtree1(150,- 150, 100, 4, 2, true);
		drawtree2(50, 100, 50, 5, 1, true);
		drawtree1(60, 180, 80, 3, 1, true);
		//上面透明地板
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0f, 0.2f, 1.0f, 0.2f);
		glBegin(GL_QUADS);

		glVertex3f(100, 150, 100);
		glVertex3f(-100, 150, 100);
		glVertex3f(-100, 150, -100);
		glVertex3f(100, 150, -100);

		glEnd();
		glDisable(GL_BLEND);




		break;
	case 1:
		if (this->camera == 1)
			drawBuilding(-300, -10, -300, 600, 600, ground2, 8, 8, 0.5);
		break;
	case 2:

		if (!isrun && this->camera == 1&&close) {
			glBindTexture(GL_TEXTURE_2D, splash);
			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f);	glVertex3f(250, 0, 200);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-250, 0, 200);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-250, 0, -200);
			glTexCoord2f(1.0f, 1.0f);	glVertex3f(250, 0, -200);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		else
		//草地
		drawBuilding(-300, -40, -300, 600,600, ground3, 8, 8, 0.5);
		
		//土壤
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f, 0.2f, 0.0f, 0.2f);
		glBegin(GL_QUADS);
		
		glVertex3f(300, -1, 300);
		glVertex3f(-300, -1, 300);
		glVertex3f(-300, -1, -300);
		glVertex3f(300, -1, -300);

		glVertex3f(300, -10, 300);
		glVertex3f(-300, -10, 300);
		glVertex3f(-300, -10, -300);
		glVertex3f(300, -10, -300);

		glVertex3f(300, -39, 300);
		glVertex3f(-300, -39, 300);
		glVertex3f(-300, -39, -300);
		glVertex3f(300, -39, -300);

		glEnd();
		glDisable(GL_BLEND); 


		//往下長的地板
		glBindTexture(GL_TEXTURE_2D, ground3);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-200, -40, -200);//1
		glTexCoord2f(0,1.0f);	glVertex3f(200, -40, -200);//2
		glTexCoord2f(1, 1.0f);	glVertex3f(200, -150, -200);//6
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-200, -150, -200);//5

		glTexCoord2f(0, 0.0f);	glVertex3f(200, -40, -200);//2
		glTexCoord2f(0, 1); glVertex3f(200, -40, 200);//3
		glTexCoord2f(1, 0); glVertex3f(200, -150, 200);//7
		glTexCoord2f(1, 1.0f);	glVertex3f(200, -150, -200);//6
		

		glTexCoord2f(0, 0); glVertex3f(200, -40, 200);//3
		glTexCoord2f(0.0f, 1);	glVertex3f(-200, -40, 200);//4
		glTexCoord2f(1.0f, 1);	glVertex3f(-200, -150, 200);//8
		glTexCoord2f(1, 0); glVertex3f(200, -150, 200);//7

		glTexCoord2f(0.0f, 0);	glVertex3f(-200, -40, 200);//4
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-200, -40, -200);//1
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-200, -150, -200);//5
		glTexCoord2f(1.0f, 0);	glVertex3f(-200, -150, 200);//8

		glEnd();
		glDisable(GL_TEXTURE_2D);

		//往下長的地板
		glBindTexture(GL_TEXTURE_2D, wood);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);

		glTexCoord2f(0, 1); glVertex3f(-198, -40, -198);//1
		glTexCoord2f(5, 1);	glVertex3f(198, -40, -198);//2
		glTexCoord2f(5, 0);	glVertex3f(198, -100, -198);//6
		glTexCoord2f(0, 0); glVertex3f(-198, -100, -198);//5

		glTexCoord2f(0, 1);	glVertex3f(198, -40, -198);//2
		glTexCoord2f(5, 1); glVertex3f(198, -40, 198);//3
		glTexCoord2f(5, 0); glVertex3f(198, -100, 198);//7
		glTexCoord2f(0, 0);	glVertex3f(198, -100, -198);//6


		glTexCoord2f(5, 1); glVertex3f(198, -40, 198);//3
		glTexCoord2f(0, 1);	glVertex3f(-198, -40, 198);//4
		glTexCoord2f(0, 0);	glVertex3f(-198, -100, 198);//8
		glTexCoord2f(5, 0); glVertex3f(198, -100, 198);//7

		glTexCoord2f(5, 1);	glVertex3f(-198, -40, 198);//4
		glTexCoord2f(0, 1); glVertex3f(-198, -40, -198);//1
		glTexCoord2f(0, 0); glVertex3f(-198, -100, -198);//5
		glTexCoord2f(5, 0);	glVertex3f(-198, -100, 198);//8

		glEnd();
		glDisable(GL_TEXTURE_2D);


		//錢
		glBindTexture(GL_TEXTURE_2D, money);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);	glVertex3f(-200, -41, -200);
		glTexCoord2f(0, 5);	glVertex3f(200, -41, -200);
		glTexCoord2f(5, 5);	glVertex3f(200, -41, 200);
		glTexCoord2f(5, 0);	glVertex3f(-200, -41, 200);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		//電視
		glBindTexture(GL_TEXTURE_2D, TV);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(40, -60, 197);//3
		glTexCoord2f(1, 0);	glVertex3f(-40, -60, 197);//4
		glTexCoord2f(1, 1);	glVertex3f(-40, -140, 197);//8
		glTexCoord2f(0, 1); glVertex3f(40, -140, 197);//7
		glEnd();
		glDisable(GL_TEXTURE_2D);

		//畫
		glBindTexture(GL_TEXTURE_2D, painting);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-197, -60, 130);//4
		glTexCoord2f(1, 0); glVertex3f(-197, -60, 20);//1
		glTexCoord2f(1, 1); glVertex3f(-197, -145, 20);//5
		glTexCoord2f(0, 1); glVertex3f(-197, -145, 130);//8
		glDisable(GL_TEXTURE_2D);
		glEnd();
		//冰箱
		glBindTexture(GL_TEXTURE_2D, frig);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0.3, 0); glVertex3f(55, -40, -197);//3
		glTexCoord2f(0.7, 0);	glVertex3f(5, -40, -197);//4
		glTexCoord2f(0.7, 1);	glVertex3f(5, -120, -197);//8
		glTexCoord2f(0.3, 1); glVertex3f(55, -120, -197);//7
		glEnd();
		glDisable(GL_TEXTURE_2D);

		//捷運站
		glBindTexture(GL_TEXTURE_2D, MRT);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 1000, -300);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 1000, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(400, 1000, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(400, 1000, -300);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		//711
		glBindTexture(GL_TEXTURE_2D, seven);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 1000, -300);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 1000, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-400, 1000, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-400, 1000, -300);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		drawtree1(-250, -250, 500, 4, 2, true);
		drawtree2(-200, 140, 400,  5, 1, true);
		drawtree2(250, -200, 600, 3, 1, true);
		drawtree2(-200, -250, 200, 6, 2, true);
		drawtree1(250, -100, 200, 2, 1, true);

	

		drawBuilding(300, 80, -300, 10,600, wall, 8, 0.2, 0.5);
		drawBuilding(-300, 80, -300, 600,10, wall, 0.2, 8, 0.5);

			glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0.8f, 0.3f, 0.2f, 0.3f);
			glBegin(GL_POLYGON);

			gluCylinder(t, 400, 380, 0, 100, 30);
			glColor4f(0.8f, 0.8f, 0.3f, 0.3f);
			gluCylinder(t, 370, 350, 0, 100, 30);
			glColor4f(0.2f, 0.9f, 0.2f, 0.3f);
			gluCylinder(t, 340, 320, 0, 100, 30);
			glColor4f(0.2f, 0.3f, 1.0f, 0.3f);
			gluCylinder(t, 310, 290, 0, 100, 30);
			glEnd();
			glDisable(GL_BLEND);
			glPopMatrix();
		

		break;

	default:
		break;
	}
	
	

}

void TrainView::drawBuilding(int x, int y, int z, int w, int h, GLuint sticker, float s, float u, float v)
{
	//大樓
	
		glBindTexture(GL_TEXTURE_2D, sticker);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(x, 0, z);//1
		glTexCoord2f(u, 0.0f);	glVertex3f(x + w, 0, z);//2
		glTexCoord2f(u, s);glVertex3f(x + w, 0, z + h);//3
		glTexCoord2f(0.0f, s);	glVertex3f(x, 0, z + h);//4


		glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z);//5
		glTexCoord2f(u, 0.0f);	glVertex3f(x+ w,y,z);//6
		glTexCoord2f(u, s);	glVertex3f(x + w, y,z+h);//7
		glTexCoord2f(0.0f,s);	glVertex3f(x, y, z + h);//8

		glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, 0, z);//1
		glTexCoord2f(u, 0.0f);	glVertex3f(x + w, 0,z);//2
		glTexCoord2f(u, v);	glVertex3f(x + w, y,z);//6
		glTexCoord2f(0.0f, v);	glVertex3f(x, y, z);//5

		glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + w, 0, z);//2
		glTexCoord2f(s, 0.0f);	glVertex3f(x + w, 0, z + h);//3
		glTexCoord2f(s, v);	glVertex3f(x + w, y, z + h);//7
		glTexCoord2f(0.0f,v);	glVertex3f(x + w, y, z);//6

		glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + w, 0, z + h);//3
		glTexCoord2f(u, 0.0f);	glVertex3f(x, 0, z + h);//4
		glTexCoord2f(u, v);	glVertex3f(x, y, z + h);//8
		glTexCoord2f(0.0f, v);	glVertex3f(x + w, y, z + h);//7

		glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, 0, z + h);//4
		glTexCoord2f(s, 0.0f);	glVertex3f(x, 0, z);//1
		glTexCoord2f(s, v);	glVertex3f(x, y, z);//5
		glTexCoord2f(0.0f,v);	glVertex3f(x, y, z + h);//8

		glEnd();
		glDisable(GL_TEXTURE_2D);
	
}

void TrainView::drawCube(int x, int y, int z, int height, int w, int h, GLuint sticker, float s, float u, float v)
{

	glBindTexture(GL_TEXTURE_2D, sticker);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);//1
	glTexCoord2f(u, 0.0f);	glVertex3f(x + w, y, z);//2
	glTexCoord2f(u, s); glVertex3f(x + w, y, z + h);//3
	glTexCoord2f(0.0f, s);	glVertex3f(x, y, z + h);//4


	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y+height, z);//5
	glTexCoord2f(u, 0.0f);	glVertex3f(x + w,y+ height, z);//6
	glTexCoord2f(u, s);	glVertex3f(x + w, y+height, z + h);//7
	glTexCoord2f(0.0f, s);	glVertex3f(x, y+height, z + h);//8

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z);//1
	glTexCoord2f(u, 0.0f);	glVertex3f(x + w, y, z);//2
	glTexCoord2f(u, v);	glVertex3f(x + w, y+height, z);//6
	glTexCoord2f(0.0f, v);	glVertex3f(x, y+height, z);//5

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + w, y, z);//2
	glTexCoord2f(s, 0.0f);	glVertex3f(x + w, y, z + h);//3
	glTexCoord2f(s, v);	glVertex3f(x + w,y+ height, z + h);//7
	glTexCoord2f(0.0f, v);	glVertex3f(x + w,y+ height, z);//6

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + w, y, z + h);//3
	glTexCoord2f(u, 0.0f);	glVertex3f(x, y, z + h);//4
	glTexCoord2f(u, v);	glVertex3f(x, y+height, z + h);//8
	glTexCoord2f(0.0f, v);	glVertex3f(x + w,y+ height, z + h);//7

	glTexCoord2f(0.0f, 0.0f);	glVertex3f(x, y, z + h);//4
	glTexCoord2f(s, 0.0f);	glVertex3f(x, y, z);//1
	glTexCoord2f(s, v);	glVertex3f(x, y+height, z);//5
	glTexCoord2f(0.0f, v);	glVertex3f(x, y+height, z + h);//8

	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void TrainView::drawtree1(int x, int z, int height, float angle1, float angle2, bool doingShadows)
{
	angle1 = angle1 * 0.5;
	angle2 = angle2 * 0.5;


	glPushMatrix();
	glTranslated(x, 0, z);
	glRotatef(270, 1.0f, 0.0f, 0.0f);
	glScalef(0.3, 0.3, 0.8);

	glPushMatrix();
	glColor3f(0.48, 0.38, 0.08);
	glBegin(GL_POLYGON);
	GLUquadricObj *tree2gun = gluNewQuadric();
	gluCylinder(tree2gun, height / 15, height / 15, height/4, 20, 30);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, height /5);
	glColor3f(0.1, angle1/10, 0.1);
	glBegin(GL_POLYGON);
	GLUquadricObj *tree2leaves1 = gluNewQuadric();
	gluCylinder(tree2leaves1, height*3/ 10, 0, height/4, 20, 30);
	glEnd();
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(0, 0, height / 3.5 );
	glRotatef(-angle2, 1.0f, 0.0f, 0.0f);
	glRotatef(angle1, 0.0f, 1.0f, 0.0f);
	glColor3f(0, (angle1+1)/10, (angle2/10));
	glBegin(GL_POLYGON);
	GLUquadricObj *tree2leaves2 = gluNewQuadric();
	gluCylinder(tree2leaves2, height * 2.5 / 10, 0, height/4, 20, 30);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, height / 2.5);
	glRotatef(angle1, 1.0f, 0.0f, 0.0f);
	glRotatef(angle2, 0.0f, 1.0f, 0.0f);
	glColor3f((angle2+1)/10, (angle1+2)/10, 0.1);
	glBegin(GL_POLYGON);
	GLUquadricObj *tree2leaves3 = gluNewQuadric();
	gluCylinder(tree2leaves3, height * 2 / 10, 0, height/4, 20, 30);
	glEnd();
	glPopMatrix();
	
 
	glPopMatrix();
}

void TrainView::drawtree2(int x, int z, int height,  float angle1, float angle2, bool doingShadows)
{
	angle1 = angle1 * 0.5;
	angle2 = angle2 * 0.5;
	
	glPushMatrix();
	glTranslated(x, 0, z);
	glRotatef(270, 1.0f, 0.0f, 0.0f);
	glScalef(0.3, 0.3, 0.8);

	glPushMatrix();
	glColor3f(0.33, 0.2, 0.2);
	glBegin(GL_POLYGON);
	GLUquadricObj *tree2gun = gluNewQuadric();
	gluCylinder(tree2gun, height / 10, height / 10, height / 5, 20, 30);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, height / 6);
	glColor3f(angle2/10, angle1/10, angle2/10);
	glBegin(GL_POLYGON);
	GLUquadricObj *tree2leaves1 = gluNewQuadric();
	gluCylinder(tree2leaves1, height /2.5, 0, height / 5, 20, 30);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0, height / 3.5);
	glRotatef(-angle2, 1.0f, 0.0f, 0.0f);
	glRotatef(angle1, 0.0f, 1.0f, 0.0f);
	glColor3f(angle1/10, (angle1+1)/10, 0);
	glBegin(GL_POLYGON);
	GLUquadricObj *tree2leaves2 = gluNewQuadric();
	gluCylinder(tree2leaves2, height  / 3, 0, height / 4.5, 20, 30);
	glEnd();
	glPopMatrix();
 
	glPopMatrix();
}

void TrainView::drawtree3(int x, int z, int height, float angle1, float angle2, bool doingShadows)
{
	GLUquadricObj *tree2leaves1 = gluNewQuadric();

	glPushMatrix();
	glTranslated(x, 1, z);
	if (doingShadows)
	{
	glRotatef(270, 1, 0, 0);
	}
 

	glPushMatrix();
	//glTranslatef(0, 0, 30);
	glColor3f((angle2 + 1) / 10, angle1/10, (angle2 - 1) / 10);
	glBegin(GL_POLYGON);

	gluCylinder(tree2leaves1, height/4, 0, 0, 20, 30);
	glTranslated(5, 10, 0.01); glColor3f(0.1, (angle1+1)/10, (angle2 - 1) / 10);
	gluCylinder(tree2leaves1, height/3, 0, 0, 20, 30);
	glTranslated(-10, 5, 0.02); glColor3f((angle2 + 1) / 10, (angle1 + 3) / 10, 0.1);
	gluCylinder(tree2leaves1, height/2, 0, 0, 20, 30);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}
 
