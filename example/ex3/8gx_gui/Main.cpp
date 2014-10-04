// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/"



CMain::CMain()
{
	m_pInput	= NULL;
	m_pXYZ		= NULL;

	m_pUi0		= NULL;
}


#define IDC_BUTTON1		0x001
#define IDC_BUTTON2		0x002
#define IDC_BUTTON3		0x003

INT	CMain::Init()
{
	TLC_ARGS	args;
	INT			i  = 0;
	INT			hr = LC_OK;


	// Input 생성
	if(LC_FAILED(LcxEnt_CreateInput(NULL, &m_pInput)))
		return LC_EFAIL;


	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_AXIS, &m_pXYZ)))
		return LC_EFAIL;



	// Create gui Method 1: defaut
	//if(false)
	{
		//TLC_FONT	tFont((char*)"../../media/font/mwg_b.otf", LC_FONT_AN_INTERNAL, 12);
		TLC_FONT	tFont(LCCMD_DEFAULT, LC_FONT_AN_FTF, 12);
		
		TXDSC_UI	t;
		LCXRECT		rc_evnt;
		PLCX_UI		Dlg  = NULL;					// Gui Dialog

		strcpy(t.name, "world");
		rc_evnt    = LCXRECT(200, 20, 380, 250);	// Gui x, y, width, Height
		t.rc_area  = rc_evnt;
		t.clzz     = LXUI_DIALOG;

		MAKE_ARG1(args, &t);
		hr = LcxUi_Create(NULL, &Dlg, &args);


		strcpy(t.name, "Hi");
		rc_evnt    = LCXRECT(150, 150, 460, 260);	// Gui x, y, width, Height
		t.rc_area  = rc_evnt;
		t.clzz     = LXUI_DIALOG;

		MAKE_ARG1(args, &t);
		hr = LcxUi_Create(NULL, &Dlg, &args);


		// Create buttons
		PLCX_UI     Btn  = NULL;					// Gui Button
		PLCX_UI     Stt  = NULL;					// Gui Static
		LCXVECTOR2   vcPos(0,0);

		vcPos  = LCXVECTOR2(100, 100);
		strcpy(t.name, "안녕하세요");
		t.qid.Ids(IDC_BUTTON1);
		t.clzz = LXUI_BUTTON;

		MAKE_ARG1(args, &t);
		hr = LcxUi_Create(NULL, &Btn, &args);

		Btn->Position(&vcPos);
		Btn->SetAttrib(LXUI_FONT, &tFont);
		Btn->Text(t.name, 0xFFFF0000);
		Dlg->AttachChild(Btn);


		vcPos  = LCXVECTOR2(230, 100);
		strcpy(t.name, "button2");
		t.qid.Ids(IDC_BUTTON2);
		t.clzz = LXUI_BUTTON;

		MAKE_ARG1(args, &t);
		hr = LcxUi_Create(NULL, &Btn, &args);

		Btn->Position(&vcPos);
		Btn->SetAttrib(LXUI_FONT, &tFont);
		Btn->Text(t.name);
		LCXVECTOR2	vcScl(2.3F,1);
		//Btn->Scaling(&vcScl);
		Dlg->AttachChild(Btn);


		vcPos  = LCXVECTOR2(100, 150);
		strcpy(t.name, "button3");
		t.qid.Ids(IDC_BUTTON3);
		t.clzz = LXUI_BUTTON;

		MAKE_ARG1(args, &t);
		hr = LcxUi_Create(NULL, &Btn, &args);

		Btn->Position(&vcPos);
		Btn->SetAttrib(LXUI_FONT, &tFont);
		Btn->Text("Hello");
		Dlg->AttachChild(Btn);


		// Create Static
		vcPos  = LCXVECTOR2(100, 180);
		strcpy(t.name, "static1");
		t.qid.Ids(IDC_BUTTON3);
		t.clzz = LXUI_STICKER;

		MAKE_ARG1(args, &t);
		hr = LcxUi_Create(NULL, &Stt, &args);

		Stt->Position(&vcPos);
		Stt->SetAttrib(LXUI_FONT, &tFont);
		Dlg->AttachChild(Stt);
	}


	// Create gui Method 2: extern value
	//if(false)
	{
		PLCX_UI     dialog  = NULL;					// Gui Dialog

		PLC_TEXTURE pTex = LcxUi_FindTexture((char*)MEDIA_DIR"gui/login.png");

		// setup the extern value
		TXDSC_UI	dlg_inf;
		TLCXUI_EXT	dlg_ext;

		LCXRECT		rc_area  = LCXRECT(20, 200, 148,   196);
		LCXRECT		rc_title = LCXRECT(  0,  0,  148,   23);	// tbar
		LCXRECT		rc_body  = LCXRECT(  0, 23,  148,  196);	// body

		//rc_area  .ToRegion();
		rc_title .ToRegion();
		rc_body  .ToRegion();

		dlg_inf.qid.Id(0, 12345);
		strcpy(dlg_inf.name, "Hello");					// save the name
		dlg_inf.clzz   = LXUI_DIALOG;

		dlg_inf.rc_area= rc_area;
		dlg_inf.rc_aux0= rc_title;
		dlg_inf.rc_aux1= rc_body;

		dlg_ext.img_w  = pTex->ImgW();
		dlg_ext.img_h  = pTex->ImgH();


		MAKE_ARG2(args, &dlg_inf, &dlg_ext);
		hr = LcxUi_Create(NULL, &dialog, &args);
		dialog->SetAttrib(LXUI_TEXTURE, pTex);



		// setup the extern value
		{
			PLCX_UI		pGui = NULL;
			TXDSC_UI	bt_inf;
			TLCXUI_EXT	bt_ext;

			LCXVECTOR2 bt_pos= LCXVECTOR2(125,  4);	// system button position
			LCXRECT    bt_r0 = LCXRECT(150,  0,  166,   13);	// system button normal
			LCXRECT    bt_r1 = LCXRECT(170,  0,  186,   13);	// system button over
			LCXRECT    bt_r2 = LCXRECT(190,  0,  206,   13);	// system button pressed

			bt_r0   .ToRegion();
			bt_r1   .ToRegion();
			bt_r2   .ToRegion();

			bt_inf.qid.Id(0, 45678);
			strcpy(bt_inf.name, "system button 1");				// save the name
			bt_inf.clzz      = LXUI_SBUTTON;					// type
			bt_inf.parent    = dialog;							// set up the parent

			bt_inf.rc_area.x = bt_pos.x;
			bt_inf.rc_area.y = bt_pos.y;
			bt_inf.rc_area.w = bt_r0.w;
			bt_inf.rc_area.h = bt_r0.h;

			bt_inf.rc_aux0 = bt_r0;
			bt_inf.rc_aux1 = bt_r1;
			bt_inf.rc_aux2 = bt_r2;

			bt_ext.img_w   = pTex->ImgW();
			bt_ext.img_h   = pTex->ImgH();

			MAKE_ARG2(args, &bt_inf, &bt_ext);
			hr = LcxUi_Create(NULL, &pGui, &args);
			pGui->SetAttrib(LXUI_TEXTURE, pTex);
		}


		{
			PLCX_UI		pGui = NULL;
			TXDSC_UI	bt_inf;
			TLCXUI_EXT	bt_ext;

			LCXVECTOR2 bt_pos= LCXVECTOR2(7, 170);				// button position
			LCXRECT    bt_r0 = LCXRECT(150, 15, 216, 34);		// button normal
			LCXRECT    bt_r1 = LCXRECT(150, 34, 216, 53);		// button over
			LCXRECT    bt_r2 = LCXRECT(150, 53, 216, 72);		// button pressed

			bt_r0   .ToRegion();
			bt_r1   .ToRegion();
			bt_r2   .ToRegion();

			bt_inf.qid.Id(0, 10001);
			strcpy(bt_inf.name, "Start 1");						// save the name
			bt_inf.clzz      = LXUI_BUTTON;						// type
			bt_inf.parent    = dialog;							// set up the parent

			bt_inf.rc_area.x = bt_pos.x;
			bt_inf.rc_area.y = bt_pos.y;
			bt_inf.rc_area.w = bt_r0.w;
			bt_inf.rc_area.h = bt_r0.h;

			bt_inf.rc_aux0 = bt_r0;
			bt_inf.rc_aux1 = bt_r1;
			bt_inf.rc_aux2 = bt_r2;

			bt_ext.img_w   = pTex->ImgW();
			bt_ext.img_h   = pTex->ImgH();

			MAKE_ARG2(args, &bt_inf, &bt_ext);
			hr = LcxUi_Create(NULL, &pGui, &args);
			pGui->SetAttrib(LXUI_TEXTURE, pTex);
		}

		{
			PLCX_UI		pGui = NULL;
			TXDSC_UI	bt_inf;
			TLCXUI_EXT	bt_ext;

			LCXVECTOR2 bt_pos= LCXVECTOR2(75, 170);				// button position
			LCXRECT    bt_r0 = LCXRECT(150,  80, 216,  99);		// button normal
			LCXRECT    bt_r1 = LCXRECT(150,  99, 216, 118);		// button over
			LCXRECT    bt_r2 = LCXRECT(150, 118, 216, 137);		// button pressed

			bt_r0   .ToRegion();
			bt_r1   .ToRegion();
			bt_r2   .ToRegion();

			bt_inf.qid.Id(0, 10002);
			strcpy(bt_inf.name, "Start 2");						// save the name
			bt_inf.clzz      = LXUI_BUTTON;						// type
			bt_inf.parent    = dialog;							// set up the parent

			bt_inf.rc_area.x = bt_pos.x;
			bt_inf.rc_area.y = bt_pos.y;
			bt_inf.rc_area.w = bt_r0.w;
			bt_inf.rc_area.h = bt_r0.h;

			bt_inf.rc_aux0 = bt_r0;
			bt_inf.rc_aux1 = bt_r1;
			bt_inf.rc_aux2 = bt_r2;

			bt_ext.img_w   = pTex->ImgW();
			bt_ext.img_h   = pTex->ImgH();

			MAKE_ARG2(args, &bt_inf, &bt_ext);
			hr = LcxUi_Create(NULL, &pGui, &args);
			pGui->SetAttrib(LXUI_TEXTURE, pTex);
		}
	}




	// Create gui Method 3: gui list from file
	//if(false)
	{
		PLCX_UI  dialog = NULL;
		int	hr = LcxUi_CreateDialogFromGUT(NULL, &dialog
											, (char*)"Login Dialog 11"
											, (char*)MEDIA_DIR"gui/login.gut"
											);

		VEC2	pos(200, 100);
		dialog->Position(&pos);
	}


	//if(false)
	{
		PLCX_UI  dialog = NULL;
		int	hr = LcxUi_CreateDialogFromXML(NULL, &dialog
										, (char*)"Login Dialog 21"
										, (char*)MEDIA_DIR"gui/login_new.grp"
										, (char*)MEDIA_DIR"gui/login_new.xml");

		VEC2	pos(400, 100);
		dialog->Position(&pos);
	}

	//if(false)
	{
		PLCX_UI  dialog = NULL;
		int	hr = LcxUi_CreateDialogFromXML(NULL, &dialog
										, (char*)"Login Dialog 22"
										, (char*)MEDIA_DIR"gui/login_new.grp"
										, (char*)MEDIA_DIR"gui/login_new.xml");

		VEC2	pos(600, 100);
		dialog->Position(&pos);


		int nCount = 0;
		vector<PLCX_UI >* pList = (vector<PLCX_UI >*)LcxUi_DialogChildList(&nCount, dialog, LXUI_TYPE);

		if(pList)
		{
			int iSize = (int)pList->size();
			for(int i=0;  i<iSize; ++i)
			{
				PLCX_UI pUi = (*pList)[i];
				pUi->m_qid;
			}
		}
	}

	//if(false)
	{
		int	hr = LcxUi_CreateIconFromXML(NULL, &m_pUi0
										, (char*)"Icon1"
										, (char*)MEDIA_DIR"gui/mario.grp"
										, (char*)MEDIA_DIR"gui/mario.xml");

		VEC2	pos(600, 100);
		m_pUi0->Position(&pos);
	}


	return LC_OK;
}



INT	CMain::Destroy()
{
	SAFE_RELEASE(	m_pXYZ		);
	SAFE_RELEASE(	m_pInput	);

	SAFE_RELEASE(	m_pUi0	);

	return LC_OK;
}


INT	CMain::FrameMove()
{
#if defined(_WIN32)
	//LcAux_Sleep(1);
#endif

	static INT c=0;
	++c;

	if(c>20*60*120)
	//if(c>8*60*2)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}


	static int n = 0;
	++n;

	if(n>5)
	{
		//printf("FPS: %3.f\n", m_TimeFPS);
		n = 0;
	}

	int hr = 0;


	// Input Update
	m_pInput->Update();

	const BYTE* keyState = m_pInput->KeyMap();
	FLOAT*      mtsPos0  = (FLOAT*)m_pInput->MtsPosition(0);
	FLOAT*      mtsPos1  = (FLOAT*)m_pInput->MtsPosition(1);
	FLOAT*      mtsGrd0  = (FLOAT*)m_pInput->MtsDelta(0);
	FLOAT*      mtsGrd1  = (FLOAT*)m_pInput->MtsDelta(1);
	INT         mtsSt0   = m_pInput->MtsState(0);
	INT         mtsSt1   = m_pInput->MtsState(1);

	if(keyState[LCIK_ESCAPE])
		return LC_EFAIL;

	if(mtsSt0)
	{
		int c;
		c=10;
	}

	if(keyState[LCIK_W])
	{
		int c;
		c=10;
	}


	hr = LcxUi_ProcSet(m_pInput);
	LcxUi_Proc();

	PLC_EVENT pEvnt = NULL;
	int cnt = LcxUi_Events(&pEvnt);
	if(0<cnt)
	{
		//LOGI("Event Receice: %d\n", cnt);
		for(int i=0; i<cnt; ++i)
		{
			PLCX_UI prn  = NULL;
			PLCX_UI pGui = (PLCX_UI)pEvnt[i].e_o;

			UINT  nType = 0;
			UINT  nId   = 0;
			INT   nMsg  = pEvnt[i].e_m;
			char  name[LXUI_MAX_NAME]={0};
			char  text[1024]={0};
			
			if(NULL == pGui)
				continue;

			nType = pGui->RscType();
			pGui->GetAttrib(LXUI_ID, &nId);
			pGui->GetAttrib(LXUI_NAME, name);
			pGui->GetAttrib(LXUI_TEXT, text);

			prn = pGui->UiParent();

			if(LXUI_EVNT_UP == nMsg)	// && IDC_BUTTON1 <= nId && nId <= IDC_BUTTON3)
			{
				printf("Evnt button Up Id: %d, Name: %s", nId, name);

				if(prn)
				{
					prn->GetAttrib(LXUI_NAME, &name);
					printf("   parent: %s", name);
				}

				printf("\n");
			}

			if(LXUI_EVNT_DOWN == nMsg)	// && IDC_BUTTON1 <= nId && nId <= IDC_BUTTON3)
			{
				printf("Evnt button Down Id: %d, Name: %s", nId, name);

				if(prn)
				{
					prn->GetAttrib(LXUI_NAME, &name);
					printf("   parent: %s", name);
				}

				printf("\n");
			}
		}
	}

	if(m_pUi0)
		m_pUi0->FrameMove();


	if(m_pUi0)
		m_pUi0->Position( (const LCXVECTOR2*)mtsPos0);

	return LC_OK;
}


INT	CMain::Render()
{
	m_pDev->BeginScene();

	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);


	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_LIGHTING, LC_ST_DISABLE);


	m_pXYZ->Render();


	LcxUi_DrawBegin();

	LcxUi_Draw();


	if(m_pUi0)
		m_pUi0->Render();


	LcxUi_DrawEnd();
	
	m_pDev->EndScene();

	return LC_OK;
}


