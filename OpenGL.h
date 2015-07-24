#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <gl\glew.h>
#include "camera.h"
using namespace System::Windows::Forms;

namespace OpenGLForm 
{
	public ref class COpenGL: public System::Windows::Forms::NativeWindow
	{

	public:
		COpenGL(System::Windows::Forms::Form ^ parentForm, GLsizei iWidth, GLsizei iHeight,Tree *_tree)
		{
			CreateParams^ cp = gcnew CreateParams;
			tree = _tree;
			// Set the position on the form
			cp->X = 0;
			cp->Y = 0;
			cp->Height = iHeight;
			cp->Width = iWidth;

			// Specify the form as the parent.
			cp->Parent = parentForm->Handle;

			// Create as a child of the specified parent and make OpenGL compliant (no clipping)
			cp->Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

			// Create the actual window
			this->CreateHandle(cp);

			m_hDC = GetDC((HWND)this->Handle.ToPointer());
			//m_hDC = GetDC((HWND)parentForm->Handle.ToPointer());
			//this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &COpenGL::OpenGL_MouseDown);
			if(m_hDC)
			{
				MySetPixelFormat(m_hDC);
				ReSizeGLScene(iWidth, iHeight);
				InitGL(iHeight,iWidth);
			}
		}
		void setTree(Tree *_tree){
			tree = _tree;
		}
		System::Void Render(System::Void)
		{
			glMatrixMode(GL_MODELVIEW);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();
			gluLookAt((c->mX)*c->distance+c->offX,(c->mY)*c->distance+c->offY,(c->mZ)*c->distance+c->offZ,c->offX,c->offY,c->offZ,0,1,0);
			glColor3f(0.4f,0.4f,0.8f);
			//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			glClearDepth(1.0);
			if(tree->branches.size() > 0){
				tree->draw();
			}
			c->updateCamera();
		}

		System::Void SwapOpenGLBuffers(System::Void)
		{
			SwapBuffers(m_hDC) ;
		}

	private:
		HDC m_hDC;
		HGLRC m_hglrc;
		Camera *c;
		Form^ parent;
		Tree *tree;
		bool lMouseDown;
		bool mMouseDown;

	protected:
		~COpenGL(System::Void)
		{
			this->DestroyHandle();
		}
		
		GLint MySetPixelFormat(HDC hdc)
		{
			static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
				{
					sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
					1,											// Version Number
					PFD_DRAW_TO_WINDOW |						// Format Must Support Window
					PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
					PFD_DOUBLEBUFFER,							// Must Support Double Buffering
					PFD_TYPE_RGBA,								// Request An RGBA Format
					16,										// Select Our Color Depth
					0, 0, 0, 0, 0, 0,							// Color Bits Ignored
					0,											// No Alpha Buffer
					0,											// Shift Bit Ignored
					0,											// No Accumulation Buffer
					0, 0, 0, 0,									// Accumulation Bits Ignored
					16,											// 16Bit Z-Buffer (Depth Buffer)  
					0,											// No Stencil Buffer
					0,											// No Auxiliary Buffer
					PFD_MAIN_PLANE,								// Main Drawing Layer
					0,											// Reserved
					0, 0, 0										// Layer Masks Ignored
				};
			
			GLint  iPixelFormat; 
		 
			// get the device context's best, available pixel format match 
			if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
			{
				MessageBox::Show("ChoosePixelFormat Failed");
				return 0;
			}
			 
			// make that match the device context's current pixel format 
			if(SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
			{
				MessageBox::Show("SetPixelFormat Failed");
				return 0;
			}

			if((m_hglrc = wglCreateContext(m_hDC)) == NULL)
			{
				MessageBox::Show("wglCreateContext Failed");
				return 0;
			}

			if((wglMakeCurrent(m_hDC, m_hglrc)) == NULL)
			{
				MessageBox::Show("wglMakeCurrent Failed");
				return 0;
			}


			return 1;
		}

		bool InitGL(int Height,int Width)										// All setup for opengl goes here
		{
			glShadeModel(GL_SMOOTH);							// Enable smooth shading
			glClearColor(0.7f, 0.7f, 0.7f, 0.5f);				// Black background
			glClearDepth(1.0f);									// Depth buffer setup
			glEnable(GL_DEPTH_TEST);							// Enables depth testing
			glDepthFunc(GL_LEQUAL);								// The type of depth testing to do
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really nice perspective calculations
			if (GLEW_OK != glewInit())
			{
				// GLEW failed!
				exit(1);
			}
			c = new Camera(Height,Width);
			c->updateCamera();
			return TRUE;										// Initialisation went ok
		}

		GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize and initialise the gl window
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
			glLoadIdentity();									// Reset The Modelview Matrix
		}
		protected:

   virtual void WndProc( Message %m ) override
   {
		unsigned short X,Y;
		short mDelta;
		DWORD value;
		value = GetMessagePos();
		X = LOWORD(value);
		Y = HIWORD(value);
		HWND handle;

		switch ( m.Msg )
		{
		case WM_LBUTTONDOWN:
			c->mousePosPress(X,Y);
			handle = static_cast<HWND>(m.HWnd.ToPointer());
			SetCapture(handle); 
			SetFocus(handle);
			lMouseDown = true;
			break;

		case WM_MOUSEMOVE:
			if(lMouseDown){
				c->updateMousePos(X,Y);
			}
			else if(mMouseDown){
				c->updateOffset(X,Y);
			}
			break;
		case 514:
			if(lMouseDown){
			//	c->mousePosRelease(X,Y);
			}
			ReleaseCapture(); 
			lMouseDown = false;
			break;
		case WM_MOUSEWHEEL:
			mDelta = GET_WHEEL_DELTA_WPARAM((int)m.WParam);
			c->setDistance(mDelta);
			break;
		case WM_MBUTTONDOWN:
			c->mDown(X,Y);
			handle = static_cast<HWND>(m.HWnd.ToPointer());
			SetCapture(handle); 
			SetFocus(handle);
			mMouseDown = true;
			break;
			
		case WM_MBUTTONUP:
			ReleaseCapture(); 
			mMouseDown = false;
			break;
		case WM_ACTIVATEAPP:

            break;
		}
	//	string String = static_cast<ostringstream*>( &(ostringstream() << m.Msg) )->str();
	//	OutputDebugString(String.c_str());
		//OutputDebugString("\n");
		NativeWindow::WndProc( m );
   }
			
	};
}