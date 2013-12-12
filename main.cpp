#include <iostream>
#include <windows.h>
#include "helper.h"
#include "Matrix2D.h"
#include "Distances2D.h"
using namespace std;

#define Red RGB (255,0,0)
#define Lime RGB (206,255,0)
#define Blue RGB (0,0,255)
 
static HWND hConWnd;
static int width;
static int height;
 
int BCX_Line (HWND,int,int,int,int,int=0,HDC=0);
int BCX_Circle (HWND,int,int,int,int=0,int=0,HDC=0);
int  GetWindowHeight(HWND hwnd);
int  GetWindowWidth(HWND hwnd);
void drawLine(int,int,int,int,int=0);
void drawCircle(int,int,int,int=0);
void drawAxes(unsigned int);
 
HWND GetConsoleWndHandle (void);

int main()
{
	/*Vector2D p = Vector2D(-40.0, 160.0);
	Polyline2D l = Polyline2D();
	l.AddPoint(Vector2D(200.0, 40.0));
	l.AddPoint(Vector2D(50.0, 200.0));
	l.AddPoint(Vector2D(10.0, 150.0));
	l.AddPoint(Vector2D(-50.0, 250.0));
	l.AddPoint(Vector2D(-100.0, 100.0));
	l.AddPoint(Vector2D(50.0, -200.0));*/
	Line p = Line(Vector2D(0.0, 0.0), Vector2D(1.0, 1.0));
	Segment l = Segment(Vector2D(100.0, 20.0), Vector2D(120.0, 50.0));
	hConWnd = GetConsoleWndHandle();
	cout<<Distance(p, l)<<endl;
	if (hConWnd)
	{
		width = GetWindowWidth(hConWnd);
		height = GetWindowHeight(hConWnd);
		drawAxes(10);
		int max_y = -(int)((p.c()+p.a()*(width/2.0))/p.b());
		int min_y = -(int)((p.c()-p.a()*(width/2.0))/p.b());
		drawLine(width/2, max_y, -width/2, min_y, Red);
		//max_y = -(int)((l.c()+l.a()*(width/2.0))/l.b());
		drawLine((int)l.P().X(), (int)l.P().Y(), (int)l.P1().X(), (int)l.P1().Y(), Red);
		/*vector<Vector2D> vert = l.Vertices();
		for(int i=0;i<vert.size()-1;i++)
		{
			drawLine(vert[i].X(), vert[i].Y(), vert[i+1].X(), vert[i+1].Y(), Red);
		}
		drawCircle(p.X(), p.Y(), 2, Red);*/
	}
	WaitForKeyPress("");
	return(0);
}

void drawAxes(unsigned int step)
{
	BCX_Line(hConWnd, width/2, 0, width/2, height, Red);
	BCX_Line(hConWnd, 0, height/2, width, height/2, Red);
	for(int i=0;i<width;i+=step)
	{
		BCX_Line(hConWnd, i, height/2-2, i, height/2+2, Red);
	}
	for(int i=0;i<height;i+=step)
	{
		BCX_Line(hConWnd, width/2-2, i, width/2+2, i, Red);
	}
}

void drawLine(int x1,int y1,int x2,int y2,int color)
{
	BCX_Line(hConWnd, x1+width/2, height/2-y1, x2+width/2, height/2-y2, color);
}
void drawCircle(int x,int y,int r,int color)
{
	BCX_Circle(hConWnd, x+width/2, height/2-y, r, color);
}

int BCX_Line (HWND Wnd,int x1,int y1,int x2,int y2,int Pen,HDC DrawHDC)
{
	int a,b=0;
	HPEN hOPen;
	// penstyle, width, color
	HPEN hNPen = CreatePen(PS_SOLID, 2, Pen);
	if (!DrawHDC) DrawHDC = GetDC(Wnd), b = 1;
	hOPen = (HPEN)SelectObject(DrawHDC, hNPen);
	// starting point of line
	MoveToEx(DrawHDC, x1, y1, NULL);
	// ending point of line
	a = LineTo(DrawHDC, x2, y2);
	DeleteObject(SelectObject(DrawHDC, hOPen));
	if (b) ReleaseDC(Wnd, DrawHDC);
	return a;
}
 
 
// converts circle(centerX,centerY,radius,pen) to WinApi function
// ellipse inside box with upper left and lower right coordinates
int BCX_Circle(HWND Wnd,int X,int Y,int R,int Pen,int Fill,HDC DrawHDC)
{
	int a, b = 0;
	if (!DrawHDC) DrawHDC = GetDC(Wnd), b = 1;
	// penstyle, width, color
	HPEN hNPen = CreatePen(PS_SOLID, 2, Pen);
	HPEN hOPen = (HPEN)SelectObject(DrawHDC, hNPen);
	HBRUSH hOldBrush;
	HBRUSH hNewBrush;
	// if true will fill circle with pencolor
	if (Fill)
	{
	hNewBrush = CreateSolidBrush(Pen);
	hOldBrush = (HBRUSH)SelectObject(DrawHDC, hNewBrush);
	}
	else
	{
	hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	hOldBrush = (HBRUSH)SelectObject(DrawHDC, hNewBrush);
	}
	a = Ellipse(DrawHDC, X-R, Y+R, X+R, Y-R);
	DeleteObject(SelectObject(DrawHDC, hOPen));
	DeleteObject(SelectObject(DrawHDC, hOldBrush));
	if (b) ReleaseDC(Wnd, DrawHDC);
	return a;
}
 
 
// the hoop ...
HWND GetConsoleWndHandle(void)
{
	HWND hConWnd;
	OSVERSIONINFO os;
	char szTempTitle[64], szClassName[128], szOriginalTitle[1024];
	 
	os.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
	GetVersionEx( &os );
	// may not work on WIN9x
	if ( os.dwPlatformId == VER_PLATFORM_WIN32s ) return 0;
	 
	GetConsoleTitle( szOriginalTitle, sizeof( szOriginalTitle ) );
	sprintf( szTempTitle,"%u - %u", GetTickCount(), GetCurrentProcessId() );
	SetConsoleTitle( szTempTitle );
	Sleep( 40 );
	// handle for NT
	hConWnd = FindWindow( NULL, szTempTitle );
	SetConsoleTitle( szOriginalTitle );
	 
	// may not work on WIN9x
	if ( os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
	{
	hConWnd = GetWindow( hConWnd, GW_CHILD );
	if ( hConWnd == NULL ) return 0;
	GetClassName( hConWnd, szClassName, sizeof ( szClassName ) );
	while ( strcmp( szClassName, "ttyGrab" ) != 0 )
	{
	hConWnd = GetNextWindow( hConWnd, GW_HWNDNEXT );
	if ( hConWnd == NULL ) return 0;
	GetClassName( hConWnd, szClassName, sizeof( szClassName ) );
	}
	}
	return hConWnd;
}

int  GetWindowHeight(HWND hwnd)
{
  if (hwnd == 0) return 0;

  RECT windowRect;

  GetWindowRect(hwnd, &windowRect);

  return windowRect.bottom - windowRect.top;
}

int  GetWindowWidth(HWND hwnd)
{
  if (hwnd == 0) return 0;

  RECT windowRect;

  GetWindowRect(hwnd, &windowRect);

  return windowRect.right - windowRect.left;
}