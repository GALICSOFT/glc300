//
//
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#if defined(_MSC_VER)
  #pragma comment(linker, "/subsystem:console")
  #pragma comment(lib, "lgpwn_a30_.lib")
  #pragma comment(lib, "lgpwn_b30_.lib")

#endif


#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#include <string>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <ac/tinyxml2.h>
using namespace tinyxml2;

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcAux.h>


#define MEDIA_DIR	"../../media/"


int main(int argc, char* argv[])
{
	XMLDocument*	xml_doc  = NULL;
	XMLElement*		xml_grp  = NULL;
	XMLElement*		xml_elm  = NULL;
	XMLElement*		xml_sub  = NULL;

	char	xmlFile[] = MEDIA_DIR"data/layout.xml";
	char*	buf    = NULL;
	int		length = 0;
	

	PLC_FILE	fp = NULL;
	if(LC_FAILED(LcFile_Open(NULL, &fp, xmlFile, (char*)"rb")))
	{
		printf("XML::Err fopen:%s\n", xmlFile);
		return LC_CANNT_FIND_RESOURCE;
	}

	fp->ReadBytes( (BYTE**)&buf, &length);
	xml_doc = Txml_CreateDoc(buf, length);

	SAFE_RELEASE(fp);
	SAFE_FREE(buf);

	if(NULL == xml_doc)
	{
		printf("XML::Valid Failed::%s\n", xmlFile);
		return LC_CANNT_FIND_RESOURCE;
	}


	xml_grp = xml_doc->FirstChildElement();							// get the node of script_app -> stage
	if(NULL == xml_grp)
	{
		Txml_Release(&xml_doc);
		return LC_CANNT_FIND_RESOURCE;
	}


	xml_elm = xml_grp->FirstChildElement("ani");

	printf("image path: %\n", (char*)xml_elm->Attribute("imagePath") );
	printf("image width: %d\n", xml_elm->IntAttribute("width" ) );
	printf("image height: %d\n", xml_elm->IntAttribute("height") );

	printf("---------------------%\n");

	xml_sub = xml_elm->FirstChildElement("sprite");
	while(xml_sub)
	{
		char* s_name = NULL;
		LCXRECT	rc;

		s_name = (char*)xml_sub->Attribute("n");
		rc.x   = (FLOAT)xml_sub->IntAttribute( "x");
		rc.y   = (FLOAT)xml_sub->IntAttribute( "y");
		rc.w   = (FLOAT)xml_sub->IntAttribute( "w");
		rc.h   = (FLOAT)xml_sub->IntAttribute( "h");
		xml_sub = xml_sub->NextSiblingElement();

		printf("rect: %.f %.f %.f %.f   nameL: %s\n", rc.x, rc.y, rc.w, rc.h, s_name);

	}


	printf("---------------------%\n");

	xml_elm = xml_grp->FirstChildElement("dialog")->FirstChildElement("bg");

	xml_sub = xml_elm->FirstChildElement("rc");
	while(xml_sub)
	{
		char* s_name = NULL;
		LCXRECT	rc;

		s_name = (char*)xml_sub->Attribute("n");
		rc.x   = (FLOAT)xml_sub->IntAttribute( "x");
		rc.y   = (FLOAT)xml_sub->IntAttribute( "y");
		rc.w   = (FLOAT)xml_sub->IntAttribute( "w");
		rc.h   = (FLOAT)xml_sub->IntAttribute( "h");
		xml_sub = xml_sub->NextSiblingElement();

		printf("rect: %.f %.f %.f %.f   nameL: %s\n", rc.x, rc.y, rc.w, rc.h, s_name);

	}

	Txml_Release(&xml_doc);

	return 0;
}
