#ifndef SCREENCAPTURE
#define SCREENCAPTURE

/*
 * Grab the OpenGL screen and save it as a .tga
 * Copyright (C) Marius Andra 2001
 * http://cone3d.gz.ee EMAIL: cone3d@hot.ee
 * with modifications from drlbs
 */


int screencapture (int const num)
{
	typedef unsigned char uchar;

	//this acts as the image data storage
	uchar *pixels;

	//this is the file writer
	FILE * shot;

	//This array will store the screen width and height
	int screenStats[4];
	char charNum[5];
	std::string strNum;

	//retrieves the values of the width/height
	//glGetIntegerv (GL_VIEWPORT, screenStats);
	screenStats[0] = 0; screenStats[1] = 0; screenStats[2] = GLOBAL.WINDOW_MAX_X; screenStats[3] = GLOBAL.WINDOW_MAX_Y;

	//array that holds pixel data
	pixels = new unsigned char [screenStats[2]*screenStats[3]*3];

	//reads pixel data
	glReadPixels(0, 0, screenStats[2], screenStats[3], 0x80E0, GL_UNSIGNED_BYTE, pixels);

	//opens file for writing, if unsuccesful, return 1
	//might rewrite this later to optimize it --chris
	sprintf (charNum, "%d", num);
	strNum = std::string(charNum);
	std::string filename = "";
	if(num < 10) 
	{
		filename = "screenshots/Plot-000000" + strNum + ".tga";
	}
	else if (num < 100)
	{
		filename = "screenshots/Plot-00000" + strNum + ".tga";
	}
	else if(num < 1000)
	{
		filename = "screenshots/Plot-0000" + strNum + ".tga";
	}
	else if(num < 10000)
	{
		filename = "screenshots/Plot-000" + strNum + ".tga";
	}
	else if(num < 100000)
	{
		filename = "screenshots/Plot-00" + strNum + ".tga";
	}
	else if(num < 1000000)
	{
		filename = "screenshots/Plot-0" + strNum + ".tga";
	}
	else
	{
		filename = "/screenshots/Plot-" + strNum + ".tga";
	}

	shot = fopen(filename.c_str(), "wb");
	
	if (shot == NULL)
	{
		return 1;
	}
	
	//this is the tga header. it must be in the beginning of every (uncompressed) .tga
	uchar TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
	
	/* the header that is used to get the dimensions of the .tga
	 * header[1]*256+header[0] - width
	 * header[3]*256+header[2] - height
	 * header[4] - bits per pixel
	 * header[5] - ?
	 */
	//uchar header[6] = {((int)(screenStats[2]%256)), ((int)(screenStats[2]/256)), ((int)(screenStats[3]%256)), ((int)(screenStats[3]/256)), 24, 0};
	uchar header[6] = {((uchar)(screenStats[2]%256)), ((uchar)(screenStats[2]/256)), ((uchar)(screenStats[3]%256)), ((uchar)(screenStats[3]/256)), 24, 0};
	
	//write out the TGA header
	fwrite (TGAheader, sizeof (uchar), 12, shot);
	
	//write out the header
	fwrite (header, sizeof (uchar), 6, shot);
	
	//write the pixels
	fwrite (pixels, sizeof (uchar), screenStats[2]*screenStats[3]*3, shot);
	
	//close the file
	fclose(shot);
	
	//free memory
	delete [] pixels;
	
	//return success
	return 0;
}

#endif
	
