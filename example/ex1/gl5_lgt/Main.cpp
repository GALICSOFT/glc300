// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


static char g_CurrentDir[260]={0};


#define MEDIA_DIR	"../../media/"


FixedMesh* LoadMeshFromFile(const char *filename);


CMain::CMain()
{
	LcAux_GetCurrentDir( g_CurrentDir, 260);

	m_pEft = NULL;

	m_pMesh	= NULL;
}


int	CMain::Init()
{
	int hr =0;

	LcAux_SetCurrentDir( g_CurrentDir);


	LCXVECTOR3	eye(0, 40, 60);
	LCXVECTOR3	look(0,0,0);
	LCXVECTOR3	up(0,1,0);
	m_mtViw.ViewGl(&eye, &look, &up);


	// set up projection matrix in 3d pipeline
	float	temp[16]={0};
	float	width, height;
	glGetFloatv(GL_VIEWPORT, temp);		// get viewport to set the screen width and height.
	width = temp[2];
	height= temp[3];
	float	Aspect = (float)width/height;
	float	Near = 1.F;
	float	Far	 = 1000.F;
	m_mtPrj.PerspectiveD3dRH( LCXToRadian(45.F), Aspect, Near, Far);


	TLC_ARGS args;

	char* attlist[] = {"at_pos", NULL};
	MAKE_ARG3(args, (char*)MEDIA_DIR"shader/12sl_vs.glsl", (char*)MEDIA_DIR"shader/12sl_fs.glsl", (char**)attlist);
	hr = LcDev_CreateEffectFromTxtFile(NULL, &m_pEft, m_pDev, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	//Load our scene file
	m_pMesh = LoadMeshFromFile(MEDIA_DIR"model/scene.gsd");

	return LC_OK;
}

int	CMain::Destroy()
{
	 //delete mesh data
	free(m_pMesh->pos);
	free(m_pMesh->Indices);
	free(m_pMesh->nor);
	free(m_pMesh->TexCoord);
	free(m_pMesh);

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
	if(c>8*60*20)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}


	static int n = 0;
	++n;

	if(n>5)
	{
		printf("FPS: %3.f\n", m_TimeFPS);
		n = 0;
	}


	return LC_OK;
}


int	CMain::Render()
{
	glEnable( GL_DEPTH_TEST);
	glDisable( GL_CULL_FACE );

	glClearColor(0.9f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




	// Lighting Position
	static GLfloat Rot=0;
	LCXVECTOR3	lgtDir(0, 1, 0);
	LCXCOLOR	amb(0.f, 0.03f, 0.051f, 0.f);
	LCXCOLOR	dif(1.f, 0.8f, 0.0f, 0.f);

	Rot += 0.04f;
	lgtDir.x = (GLfloat)sin(Rot);
	lgtDir.z = (GLfloat)cos(Rot);
	lgtDir.Normalize();


	// Set Model position
	static GLfloat rotation = 0;
	rotation +=0.4f;

	LCXMATRIX	mtY;

	mtY.RotationY( LCXToRadian(rotation) );

	m_mtWld = mtY;

	m_mtWld._41 =10.0f;
	m_mtWld._42 =-20.0f;
	m_mtWld._43 =-10.0f;


	// setup the shader constant for world * view * projection
	m_mtWVP = m_mtWld * m_mtViw * m_mtPrj;

	// setup the rotation matrix for world
	m_mtRot = m_mtWld;
	m_mtRot._41 = 0;
	m_mtRot._42 = 0;
	m_mtRot._43 = 0;


	// camera position
	LCXVECTOR3	camPos;
	LCXMATRIX mtViw = m_mtViw;
	mtViw.Inverse(NULL, NULL);
	camPos = LCXVECTOR3(mtViw._41, mtViw._42, mtViw._43);

	m_pEft->Begin();

	//m_pEft->Matrix4("um_WVP", &m_mtWVP);

	m_pEft->Matrix4("um_Wld", &m_mtWld);
	m_pEft->Matrix4("um_Viw", &m_mtViw);
	m_pEft->Matrix4("um_Prj", &m_mtPrj);
	m_pEft->Matrix4("um_Rot", &m_mtRot);


	m_pEft->Vector3("uf_cam", &camPos);
	m_pEft->Vector3("uf_dir", &lgtDir);
	m_pEft->Color  ("uf_amb", &amb);
	m_pEft->Color  ("uf_dif", &dif);


	glEnableVertexAttribArray(0);	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, m_pMesh->pos);
	glEnableVertexAttribArray(1);	glVertexAttribPointer(1, 3, GL_FLOAT, 0, 0, m_pMesh->nor);

	glDrawElements(GL_TRIANGLES,m_pMesh->indexCounter,GL_UNSIGNED_SHORT,m_pMesh->Indices);


	glDisableVertexAttribArray(0);


	m_pEft->End();



	return LC_OK;
}









//Structure to hold the data readed from the file
struct GenericObjectData
{
  char Name[128];
  char ParentName[128];
  unsigned int *Indices;
  GLfloat *pos;
  GLfloat *nor;
  GLfloat *TexCoord;
  unsigned long iC;
  unsigned long vC;
};

//GSD file header
struct GSDHeader
{
  char id[32];
  char version[16];
  int numberOfSubObjects;
};


FixedMesh* LoadMeshFromFile(const char *filename)
{
	GenericObjectData o;
	FixedMesh* mesh= (FixedMesh*)malloc(sizeof(struct FixedMesh));
	unsigned int i;

	struct GSDHeader header;
	FILE *meshFile = fopen(filename,"rb");

	if(!meshFile)
		return NULL;

	/*The header holds a brief description of the file, the version number, and the number of meshes
	that are stored in the file. This type of files are thought for static meshes only*/
	fread(&header,sizeof(struct GSDHeader),1,meshFile);

	//Check if there is at least one object
	if(header.numberOfSubObjects < 1)
		return NULL;

	// we only will use the first object, so we won't iterate over the others, if they exist
	fread(o.Name,sizeof(char)*128,1,meshFile); //read the object name
	fread(o.ParentName,sizeof(char)*128,1,meshFile); //Read the name of the parent object (useful for hierarchies)
	fread(&o.iC,sizeof(unsigned long),1,meshFile); //read the number of vertex indices
	fread(&o.vC,sizeof(unsigned long),1,meshFile); //read the number of vertices

	//allocate enough space for the indices and the GLshort version of them
	o.Indices = (unsigned int *)malloc(sizeof(unsigned int)*(o.iC));
	mesh->Indices = (short *)malloc(sizeof(GLshort)*(o.iC));
	fread(o.Indices, sizeof(unsigned int) * o.iC,1,meshFile); // read all indices

	//allocate enough space for the vertices and the GLfloat version of them
	o.pos = (GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 3));
	mesh->pos = (GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 3));
	fread(o.pos,o.vC * 3 * sizeof(GLfloat),1,meshFile); //read all vertices (1 vertex = 3 floats)

	//allocate enough space for the texture coordinates and the GLfloat version of them
	o.TexCoord = (GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 2));
	mesh->TexCoord = (GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 2));
	fread(o.TexCoord,o.vC * 2 * sizeof(GLfloat),1,meshFile);//read all texcoords (1 tex coord = 2 floats)

	//allocate enough space for the normals and the GLfloat version of them
	o.nor=(GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 3));
	mesh->nor = (GLfloat *)malloc(sizeof(GLfloat)*(o.vC * 3));
	fread(o.nor,o.vC * 3* sizeof(GLfloat),1,meshFile);//read all normals (1 normal = 3 floats)
	fclose(meshFile); //Do not need the file opened anymore

	// Convert data to optimized data types for OpenGL ES (GLfloat and GLshort)
	for(i=0;i<o.vC * 3;i++)
	{
		mesh->pos[i]= (o.pos[i]);
		mesh->nor[i] = (o.nor[i]);
	}

	for(i=0;i<o.vC * 2;i++)
		mesh->TexCoord[i] = (o.TexCoord[i]);

	for(i=0;i<o.iC;i++)
		mesh->Indices[i] = (GLshort)o.Indices[i];

	mesh->indexCounter = (GLshort)o.iC;
	mesh->vertexCounter= (GLshort)o.vC;

	//delete original values, we will use only the optimized ones
	free(o.Indices);
	free(o.pos);
	free(o.nor);
	free(o.TexCoord);

	return mesh;
}


