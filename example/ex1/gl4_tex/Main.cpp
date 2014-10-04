// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"

#define MEDIA_DIR	"../../media/"

static char g_CurrentDir[260]={0};



int Tga_FileRead(BYTE** pOutPxl			// Output Pixel
				, int*	pOutImgW		// Output Image Width
				, int*	pOutImgH		// Output Image Height
				, int*	pOutImgC		// Output Image Channel(byte)
				, char* sFile			// Source File
				);



#define MEDIA_DIR	"../../media/"




CMain::CMain()
{
	LcAux_GetCurrentDir( g_CurrentDir, 260);

	m_pEft = NULL;
	m_TexID0 = 0;
}


int	CMain::Init()
{
	int hr =0;

	LcAux_SetCurrentDir( g_CurrentDir);



	TLC_ARGS args;

	char* attlist[] = {"at_pos", NULL};
	MAKE_ARG3(args, (char*)MEDIA_DIR"shader/07sl_vs.glsl", (char*)MEDIA_DIR"shader/07sl_fs.glsl", (char**)attlist);
	hr = LcDev_CreateEffectFromTxtFile(NULL, &m_pEft, m_pDev, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	int	ImgW	= 0;
	int	ImgH	= 0;
	int	ImgC	= 0;
	int	ImgF	= 0;
	BYTE* pPxl = NULL;	


	hr = Tga_FileRead(&pPxl, &ImgW, &ImgH, &ImgC, (char*)MEDIA_DIR"tex/bg512x256.tga");

	if(0>hr)
		return LC_EFAIL;


	if(3 == ImgC)
		ImgF = GL_RGB;
	else if(4 == ImgC)
		ImgF = GL_RGBA;
	else
		ImgF = GL_LUMINANCE;

	// Generate Texture
	glGenTextures(1, &m_TexID0);
	glBindTexture(GL_TEXTURE_2D, m_TexID0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, ImgF, ImgW, ImgH, 0, ImgF, GL_UNSIGNED_BYTE, pPxl);

	free(pPxl);

	return LC_OK;
}

int	CMain::Destroy()
{
	if(m_TexID0)
	{
		glDeleteTextures(1, &m_TexID0);
		m_TexID0 = 0;
	}

	SAFE_RELEASE(	m_pEft	);

	return LC_OK;
}


int	CMain::FrameMove()
{
#if defined(_WIN32)
	LcAux_Sleep(10);
#endif

	static int c=0;
	++c;

	//	if(c>20*60*20)
	if(c>8*60*2)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}

	static int n = 0;
	++n;


	float fps = (float)this->GetFPS();

	if(n>5)
	{
		printf("FPS: %3.f\n", fps);
		n = 0;
	}


	return LC_OK;
}


// Vertex Stream data
// position buffer
GLfloat vertexArray[8] =
{
	-0.97F, -0.95F,
	 0.97F, -0.95F,
	 0.97F,  0.95F,
	-0.97F,  0.95F,
};

// texture coordinate buffer
GLfloat texCoordArray[8] =
{
	0.0F,          1.0F - 240.0F/256.0F,
	320.0F/512.0F, 1.0F - 240.0F/256.0F,
	320.0F/512.0F, 1.0F,
	0.0F,          1.0F
};



LCXCOLOR color(2.0F, 2.0F, 2.0F, 1.0F);


int	CMain::Render()
{
	int hr = 0;

	glDisable( GL_DEPTH_TEST);		// disable depth test
	glDisable( GL_CULL_FACE );		// disalbe culling face

	glClearColor(0.9f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	m_pEft->Begin();

	hr = m_pEft->Int	   ("un_tex", m_TexID0);
	hr = m_pEft->Color  ("uv_Dif", &color);
	hr = m_pEft->Texture("us_tex", 0, m_TexID0);

	glEnableVertexAttribArray(0);	glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, vertexArray);
	glEnableVertexAttribArray(1);	glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, texCoordArray);

	
	// Binding Texture
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_TexID0);

	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	
	glDrawArrays(GL_TRIANGLE_FAN, 0,4);
	

	// Unbinding texture...
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	m_pEft->End();


	return LC_OK;
}



int Tga_FileRead(BYTE** pOutPxl			// Output Pixel
				, int*	pOutImgW		// Output Image Width
				, int*	pOutImgH		// Output Image Height
				, int*	pOutImgC		// Output Image Channel(byte)
				, char* sFile			// Source File
				)
{
	FILE*		fp =NULL;

	// Header
	BYTE	IDLength	=0;		// ID Length
	BYTE	ColorMapType=0;		// Color Map Type
	BYTE	ImageType	=0;		// Image type


	// Color Map Specification
	WORD	OffsetMapTable=0;
	WORD	ColorMapLength=0;
	BYTE	ColorBits=0;


	// Image dimensions and format
	WORD	x_org =0;			// absolute coordinate of lower-left corner for displays where origin is at the lower left
	WORD	y_org =0;			// as for X-origin
//	WORD	nImgW =0;			// Image Width
//	WORD	nImgH =0;			// Image Height
	BYTE	nDepth=0;			// Pixel depth: bits per pxl
	BYTE	ImgDsc=0;			// Image descriptor (1 byte): bits 3-0 give the alpha channel depth, bits 5-4 give direction



	// For Final Targa Data
	WORD	nImgW =0;			// Image Width
	WORD	nImgH =0;			// Image Height
	BYTE	nImgC =0;			// Channel Count
	long	nImgSize=0;			// size of TGA image
	BYTE*	pPxlS = NULL;		// Dest Pixel
	BYTE*	pPxlT = NULL;		// Temp Pixel


	BYTE src[8]={0};
	int n=0, i=0, j=0;
	int nRead =0;


	// open the TGA file
	fp = fopen(sFile, "rb" );

	if (!fp)
	{
		printf("TGA File Open Err:%s\n", (char*)sFile);
		return LC_EFAIL;
	}

	// Read 3 bytes
	nRead = fread(&IDLength		, 1, 1, fp);	// Length of the image Id field
	nRead = fread(&ColorMapType	, 1, 1, fp);	// Whether a color map is included
	nRead = fread(&ImageType	, 1, 1, fp);	// Compression and color types

	// Read Color Map Specification
	nRead = fread(&OffsetMapTable, 2, 1, fp);	// First entry index (2 bytes): Offset into the color map table
	nRead = fread(&ColorMapLength, 2, 1, fp);	// Color map length (2 bytes): number of entries
	nRead = fread(&ColorBits     , 1, 1, fp);	// Color map entry size (1 byte): number of bits per pxl

	// Read Image Specification
	nRead = fread(&x_org  , 2, 1, fp);			// X-origin (2 bytes): absolute coordinate of lower-left corner for displays where origin is at the lower left
	nRead = fread(&y_org  , 2, 1, fp);			// Y-origin (2 bytes): as for X-origin
	nRead = fread(&nImgW  , 2, 1, fp);			// Image width (2 bytes): width in pixels
	nRead = fread(&nImgH  , 2, 1, fp);			// Image height (2 bytes): height in pixels
	nRead = fread(&nDepth , 1, 1, fp);			// Pixel depth (1 byte): bits per pxl
	nRead = fread(&ImgDsc , 1, 1, fp);			// Image descriptor (1 byte): bits 3-0 give the alpha channel depth, bits 5-4 give direction


	//	ImageType:
	//	0 no image data is present,
	//	1 uncompressed, color-mapped image,
	//	2 uncompressed, true-color image,
	//	3 uncompressed, black-and-white image,
	//	9 run-length encoded, color-mapped Image,
	//	10 run-length encoded, true-color image and,
	//	11 run-length encoded, black-and-white Image
	if( !(2 == ImageType || 10 == ImageType))
	{
		printf("TGA Err: We can only support only true-color(2 or 10).\n");
		fclose(fp);
		return LC_EFAIL;
	}


	fseek(fp, IDLength + ColorMapType * ColorMapLength, SEEK_CUR);


	// colormode -> 3 = BGR, 4 = BGRA
	nImgC		= nDepth>>3;
	nImgSize	= nImgW * nImgH * nImgC;
	pPxlS		= (BYTE*)malloc(nImgSize);


	// Uncompressed
	if(2 == ImageType)
	{
		nRead = fread(pPxlS, sizeof(BYTE), nImgSize, fp);
	}

	// Compressed
	else if(10 == ImageType)
	{
		pPxlT	= pPxlS;

		while (n < nImgW * nImgH)
		{

			if (fread(src, 1, nImgC+1, fp) != (size_t)(nImgC+1))
				break;

			j = src[0] & 0x7f;

			memcpy(&pPxlT[n*nImgC], &src[1], nImgC);
			++n;

			// RLE chunk
			if (src[0] & 0x80)
			{
				for (i=0;i<j;++i)
				{
					memcpy(&pPxlT[n*nImgC], &src[1], nImgC);
					++n;
				}
			}

			// Normal chunk
			else
			{
				for (i=0;i<j;++i)
				{
					if (fread(src, 1, nImgC, fp) != nImgC)
						break;

					memcpy( &pPxlT[n*nImgC], src, nImgC);
					++n;
				}
			}

		}// while

	}

	fclose(fp);


	// bgr to rgb
	for(int y=0; y<nImgH; ++y)
	{
		for(int x=0; x<nImgW; ++x)
		{
			if(3 == nImgC)
			{
				int n = y * nImgW + x;

				int r  = pPxlS[n * nImgC + 0];
				int g  = pPxlS[n * nImgC + 1];
				int b  = pPxlS[n * nImgC + 2];

				pPxlS[n * nImgC + 0] = b;
				pPxlS[n * nImgC + 1] = g;
				pPxlS[n * nImgC + 2] = r;
			}
		}
	}


	// Setting Pixel and Pixel Info
	*pOutPxl  = pPxlS;
	*pOutImgW = nImgW;
	*pOutImgH = nImgH;
	*pOutImgC = nImgC;

	return LC_OK;
}

