#include "p2Log.h"
#include "j1App.h"
#include "j1Window.h"
#include "j1Textures.h"
#include "j1Render.h"

#include "j1Video.h"

j1Video::j1Video()
{
	name.create("video");
}

j1Video::~j1Video()
{
}

bool j1Video::Awake(pugi::xml_node &)
{
	return true;
}

bool j1Video::CleanUp()
{
	return true;
}

void j1Video::Initialize(char* path)
{
	App->win->SetTitle("Video Player");

	OpenAVI(path);                  // Open The AVI File
		// TODO 6: Play the music of the video using the audio module. 


}

void j1Video::OpenAVI(LPCSTR path)
{
	AVIFileInit();                          // Opens The AVIFile Library

	/*TODO 2.1: Use AVIStreamOpenFromFile(...) to open a single stream from the AVI file.
				- The first parameter is a pointer to a buffer that receives the stream handle.
				- The second parameter is the path to the file.
				- The third parameter is the type of stream we want to open (in this case streamtypeVIDEO).
				- The fourth parameter is which video stream we want (there can be more than one), in this case: 0.
	*/

	AVIStreamInfo(pavi, &psi, sizeof(psi));					// Reads Information About The Stream Into psi
	width = psi.rcFrame.right - psi.rcFrame.left;           // Width Is Right Side Of Frame Minus Left
	height = psi.rcFrame.bottom - psi.rcFrame.top;          // Height Is Bottom Of Frame Minus Top
	lastFrame = AVIStreamLength(pavi);						// The Last Frame Of The Stream
	
	

	// TODO 3.1: Use AVIStreamFrameOpen(...) to decompress video frames from the AVI file. On the second parameter you can pass AVIGETFRAMEF_BESTDISPLAYFMT to select the best display format.
	// Hint: this function returns a PGETFRAME	

	isVideoFinished = false;
}

bool j1Video::GrabAVIFrame()
{

	LPBITMAPINFOHEADER lpbi;													 // Holds The Bitmap Header Information
	lpbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf, frame);					// Grab Data From The AVI Stream
	pdata = (char *)lpbi + lpbi->biSize + lpbi->biClrUsed * sizeof(RGBQUAD);    // Pointer To Data Returned By AVIStreamGetFrame
	
	
																					
	/*TODO 5 Create a surface using the bitmap data we have above this TODO, and create the texture of the frame with that surface (use LoadSurface from textures module)
				- pdata holds the texture data (pixels)
				- biBitCount holds the depht in bits and is contained in the LPBITMAPINFOHEADER structure
				- pitch is the length of a row of pixels in bytes (width x 3)
	*/



	//uncoment after todo 5
	//App->render->Blit(texture, 0, 0, NULL, SDL_FLIP_VERTICAL);


	if (i % 2 == 0)
	{
		frame++;
	}
	i++;
	if (frame >= lastFrame)
	{
		frame = 0;
		isVideoFinished = true;
	}
	
	// TODO 5: Unload the texture and free the surface after the blit.

	return true;
}

void j1Video::CloseAVI()
{
	// TODO 3: Use AVIStreamGetFrameClose to deallocate the getframe resources.

	//TODO 2: Use AVIStreamRelease(...) to release the stream.

	AVIFileExit();                              // Release The File
}
