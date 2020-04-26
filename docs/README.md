# Video Player

My name is Santiago Moliner, I’m a student at the Bachelor’s Degree in Video Games by UPC at CITM. This is my personal research about a functional video player inside Visual Studio C++ using SDL Library and ffmpeg libraries.


## Introduction:

In this research project, i will teach you how you can implement a video player in your C++ code using the SDL Library and ffmpeg libraries, implementing a module that can reproduce AVI files. Video Playing inside your game is a complex task, and there are many ways of implementing a video player inside.I have chosen one that i could understand with my programming knowledge.

## Pre-rendered cutscenes vs Real Time cutscenes:

In video games cutscenes can be classified in many ways, but when talking about video rendering, there are two different categories: pre-rendered and real time cutscenes. Real time cutscenes use the game engine to generate a cutscene that is rendered while the game is playing. Pre-rendered cutscenes, as the name implies, are cutscenes that have been rendered before, and the game just plays the cutscene

### Example of Real Time cutscene:

<div style="position:relative;height:0;padding-bottom:52.18%"><iframe src="https://www.youtube.com/watch?v=prmL4_rcbOE" style="position:absolute;width:100%;height:100%;left:0" width="690" height="360" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe></div>
Bloodborne bossfight intro.


### Example of Pre-rendered cutscene:

<div style="position:relative;height:0;padding-bottom:52.18%"><iframe src="https://www.youtube.com/watch?v=ylFzJ3wRgHw" style="position:absolute;width:100%;height:100%;left:0" width="690" height="360" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe></div>
Dark Souls Intro.



## Codec ecosystem and options

Creating your own solution to the problem can have legal problems, there are thousands of broad patents covering different aspects of video decompression. So if you want to do it by yourself you will have to read, understand and memorize all these patents so that you can carefully tip-toe your code and algorithms around them.

The best option is to pick one of the existing alternatives and do the best you can with it. Some of the best alternatives are: Bink, Platform specific, H.264, WebM, Dirac, Theora, and DivX.


### Bink

Bink from RAD game tools is as close as you can get to a de facto standard in the games industry, being used in more than 5800 games on 14 different platforms.

The main drawback of Bink is the pricing. At $ 8500 per platform per game, which can be a problem for a small game targeting multiple platforms.

People who want to play a lot of video in CPU taxing situations can still choose to integrate Bink. For them, the price and effort will be worth it.



### Platform specific

Another approach to video playing is to not develop a platform-independent library but instead use the video playing capabilities inherent in each platform. For example, Windows has Windows Media Foundation, MacOS has QuickTime, etc.

The biggest advantage is that on low-end platforms, using the built-in platform libraries can give you access to special video decoding hardware. For example, many phones have built-in H.264 decoding hardware. This means you can play video nearly for free, something that otherwise would be very costly on a low-end CPU.

But going platform specific also has a lot of drawbacks. If you target many platforms you have your work cut out for you in integrating all their different video playing backends. It adds an additional chunk of work that you need to do whenever you want to add a new platform.

Furthermore, it may be tricky to support the same capabilities on all different platforms.


### H.264

H.264 is used in Blu-ray players, video cameras, on iTunes, YouTube, etc. If you want a codec with good tool support and high quality, H.264 is the best choice.

However, H.264 is covered by patents. Patents that need to be licensed if you want to use H.264 without risking a lawsuit.

The H.264 patents are managed by an entity known as MPEG LA. They have gathered all the patents that they believe pertain to H.264 in “patent pool” that you can license all at once, with a single agreement.



### VP8 (WebM)

VP8 is a “free” video codec owned by Google. It is covered by patents, but Google has granted free use of those patents and also provides a BSD licensed library libvpx for encoding and decoding video files. The format is also endorsed by the Free Software Foundation.

It is generally acknowledged that when it comes to quality, VP8 is not quite as good as H.264, though the differences are not enormous. So you are trading some visual quality for the convenience of a license free format.



## The Video Player

The explanation of how it works is quite simple. First, we have to read the avi file and the stream data. Then, on each loop we will take the bitmap data of a frame. With that, we will create a surface and a texture from that surface, and we will blit it on screen. Of course there are more steps to follow inbetween those, but that is a brief explanation of how it works. Here we have a representaion of how the algorith works.


### The Video Module

MAIN FUNCTIONS:

-**OpenAVI**:  Opens the avi file and reads its stream data.

-**Initialize**: Calls OpenAVI with the path to the file (we will call this function whenever we want to play a video)

-**GrabAVIFrame**: Gets the frame data, makes a surface and a texture, and blit it.

-**CloseAVI**: Frees the memory we have used.


VARIABLES:

To be able to declare those, we have to include the video for windows library and header files. I also included the direct show header files beacause vfw is a little bit old and outdated, and we will be able to decompress videos with diferent codecs.

**frame**: Current frame we want to display from the animation. We start off at 0 (first frame). 
**psi**: The structure that will hold information about our AVI file later in the code. 
**pavi**: Pointer to a buffer that receives the new stream handle once the AVI file has been opened. 
**pgf**: Pointer to our GetFrame object. 
**lastframe**: Hold the number of the last frame in the AVI animation. 
**width and height**: Hold the dimensions of the AVI stream.
**pdata**: Pointer to the image data returned after we get a frame of animation from the AVI.
**mpf**: Used to calculate how many milliseconds each frame is displayed for.

```
int			frame = 0;			
AVISTREAMINFO       	psi;      
PAVISTREAM		pavi;     
PGETFRAME		pgf;      

long			lastFrame;
int			width;    
int			height;   
char*			pdata;		
int			mpf;      
```



## Exercise (TODO)

### TODO 1: Call the initialize function.

- You have to pass the path to the AVI file.

SOLUTION:
```
App->video->Initialize("video/sample(good).avi");
```


### TODO 2: Open and then release the stream from the AVI file.

TODO 2.1: Open a single stream from the AVI file.
- Use AVIStreamOpenFromFile(...).
- The first parameter is a pointer to a buffer that receives the stream handle.
- The second parameter is the path to the file.
- The third parameter is the type of stream we want to open (in this case streamtypeVIDEO).
- The fourth parameter is which video stream we want (there can be more than one), in this case: 0.
- The rest (RGB masks), are 0 if you do not want to put a mask on it.

SOLUTION:
```
if (AVIStreamOpenFromFile(&pavi, path, streamtypeVIDEO, 0, OF_READ, NULL) != 0)
	LOG("Failed To Open The AVI Stream");
```

TODO 2.2: Release the stream.
- Use AVIStreamRelease(...)

SOLUTION:
```
AVIStreamRelease(pavi);
```


### TODO 3: Decompress video frames from the AVI file and deallocate the GetFrame resources.

TODO 3.1: Decompress video frames from the AVI file.
- Use AVIStreamFrameOpen(...).
- This function returns a PGETFRAME.
- On the second parameter you can pass AVIGETFRAMEF_BESTDISPLAYFMT to select the best display format. Cast it to LPBITMAPINFOHEADER.

SOLUTION:
```
pgf = AVIStreamGetFrameOpen(pavi, (LPBITMAPINFOHEADER)AVIGETFRAMEF_BESTDISPLAYFMT);
	if (pgf == NULL)
		LOG("Failed To Open The AVI Frame");
```

TODO 3.2: Deallocate the getframe resources.
- AVIStreamGetFrameClose(...).

SOLUTION:
```
AVIStreamGetFrameClose(pgf);
```

### TODO 4: Prepare the video.
If you want to be able to play any video, you will need to compress it with the right codec. You have many ways to do this. There are lots of video converters that allows you to chose an especific codec. In my case I use Adobe Premiere 2018. I am confortable with it because I am more used to it and it has export options like a video converter, but you can use other softwares if you feel more confortable with them.

Follow the next steps:
1. Go to File->Export->Media...
2. Go to Video Codec options and select "Códec Intel IYUV"

SOLUTION
If you have done that steps right, the program should not break now.

### TODO 5: Create the surface and the texture, and then free them.

TODO 5.1: Create a surface using the bitmap data we have above this TODO, and create the texture of the frame with that surface (use LoadSurface from textures module)
- pdata holds the texture data (pixels)
- biBitCount holds the depht in bits and is contained in the LPBITMAPINFOHEADER structure
- pitch is the length of a row of pixels in bytes (widht x 3)

SOLUTION:
```
SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pdata, width, height, lpbi->biBitCount, width * 3, 0, 0, 0, 0);
	SDL_Texture* texture = App->tex->LoadSurface(surface);
```

TODO 5.2: Unload the texture and free the surface after the blit.
- Use UnLoad(...) from the textures module and SDL_FreeSurface(...).

SOLUTION:
```
App->tex->UnLoad(texture);
	SDL_FreeSurface(surface);
```

### TODO 6: Play the music of the video.

-  Use the audio module.

SOLUTION:
```
App->audio->PlayMusic("video/sample.ogg", 0.0f);
```

# References:

https://docs.microsoft.com/en-us/windows/uwp/files/quickstart-managing-folders-in-the-music-pictures-and-videos-libraries
https://www.gamasutra.com/view/news/170671/Indepth_Playing_with_video.php

