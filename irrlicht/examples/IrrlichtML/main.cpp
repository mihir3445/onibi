/*
 * Irrlicht FreeType Demo
 */
#include <irrlicht.h>
#include <stdio.h>
#include "driverChoice.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// Change your favorite settings
#define	SIZE_FONT_NORMAL  12
#define SIZE_FONT_BIG  24
#ifdef _IRR_WINDOWS_
    #define FONTPATH1 L"C:\\Windows\\Fonts\\arial.ttf"
    #define FONTPATH2 L"C:\\Windows\\Fonts\\times.ttf"
    #define FONTPATH3 L"C:\\Windows\\Fonts\\msgothic.ttc"
#else // for Linux (Ubuntu)
    #define FONTPATH1 L"/usr/share/fonts/truetype/freefont/FreeSans.ttf"
    #define FONTPATH2 L"/usr/share/fonts/truetype/freefont/FreeSerif.ttf"
    #define FONTPATH3 L"/usr/share/fonts/truetype/ttf-japanese-gothic.ttf"
#endif

IrrlichtDevice *Device;
s32 cnt = 0;
s32 lang = 0;
IGUIListBox* listbox = 0;
IGUIListBox* lstLang = 0;
IGUIStaticText* txtTrans = 0;
IGUIStaticText* txtLog = 0;
IGUIButton *btnQuit = 0;
IGUIButton *btnNew = 0;
IGUIButton *btnFile = 0;
IGUIEditBox *edtName = 0;
IGUIEditBox *edtMemo = 0;

IGUIFont *fonts[6],*font,*font2;
IGUISkin* skin;
/*
 *	Japanese Texts
 */
wchar_t	jtxtTrans[] = {0x900f,0x660e,0x5ea6,0x8a2d,0x5b9a,0x003a,0};
wchar_t	jtxtQuit[] = {0x7d42,0x308f,0x308b,0};
wchar_t	jtxtNew[] = {0x65b0,0x898f,0x30a6,0x30a3,0x30f3,0x30c9,0x30a6,0};
wchar_t	jtxtFile[] = {0x30d5,0x30a1,0x30a4,0x30eb,0x3092,0x958b,0x304f,0};
wchar_t	jtxtLog[] = {0x64cd,0x4f5c,0x30ed,0x30b0,0};
wchar_t	jtxtTfont[] = {0x900f,0x904e,0x30d5,0x30a9,0x30f3,0x30c8,0};
wchar_t	jtxtHello[] = {0x3053,0x3093,0x306b,0x3061,0x306f,0x30c8,0x30a5,0x30eb,0x30fc,0x30bf,0x30a4,0x30d7,0};

void ChangeCaption(s32 newlang){
	lang = newlang;
	switch(lang){
	case	0:	// English
		txtTrans->setText(L"Transparency:");
		btnQuit->setText(L"Quit");
		btnNew->setText(L"New Window");
		btnFile->setText(L"Open File");
		txtLog->setText(L"Logging ListBox:");
		break;
	case	1:	// Japanese
		txtTrans->setText(jtxtTrans);
		btnQuit->setText(jtxtQuit);
		btnNew->setText(jtxtNew);
		btnFile->setText(jtxtFile);
		txtLog->setText(jtxtLog);
		break;
	}
}

class MyEventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{

			case EGET_SCROLL_BAR_CHANGED:
				if (id == 104)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					
					for (s32 i=0; i<EGDC_COUNT ; ++i)
					{
						SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
						col.setAlpha(pos);
						env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
					}
					
				}
				break;

			case EGET_BUTTON_CLICKED:

				if (id == 101)
				{
					Device->closeDevice();
					return true;
				}

				if (id == 102)
				{
					listbox->addItem(L"Window created");
					cnt += 30;
					if (cnt > 200) 
						cnt = 0;

					IGUIWindow* window = env->addWindow(
						rect<s32>(100 + cnt, 100 + cnt, 300 + cnt, 200 + cnt), 
						false, // modal?
						L"Test window");

					env->addStaticText(L"Please close me",  
						rect<s32>(35,35,140,50),
						true, // border?
						false, // wordwrap?
						window);

					return true;
				}

				if (id == 103)
				{
					listbox->addItem(L"File open");
					env->addFileOpenDialog(L"Please choose a file.");
					return true;
				}

				break;
			case EGET_LISTBOX_CHANGED:
			case EGET_LISTBOX_SELECTED_AGAIN:
				if (id == 120){
					int sel = lstLang->getSelected();
					font = fonts[sel * 2];
					font2 = fonts[sel * 2 + 1];
					skin->setFont(font);
					if (sel == 2){
						ChangeCaption(1);
					} else {
						ChangeCaption(0);
					}
				}
				break;
			}
		}

		return false;
	}
};

int main()
{
	// ask user for driver
	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;

	// create device and exit if creation failed

	Device = createDevice(driverType, core::dimension2d<u32>(640, 480));
	if(Device == NULL)
        return 1;

	IVideoDriver *Driver = Device->getVideoDriver();
	IGUIEnvironment* env = Device->getGUIEnvironment();
	ISceneManager *Scene = Device->getSceneManager();

	Scene->addCameraSceneNode(0, vector3df(0,10,-40), vector3df(0,0,0));

	MyEventReceiver receiver;
	Device->setEventReceiver(&receiver);

	// Load fonts
 	fonts[0] = env->getFont(FONTPATH1);
 	fonts[1] = env->getFont(FONTPATH1);
 	fonts[2] = env->getFont(FONTPATH2);
 	fonts[3] = env->getFont(FONTPATH2);
 	fonts[4] = env->getFont(FONTPATH3);
 	fonts[5] = env->getFont(FONTPATH3);

	font = fonts[0];
	font2 = fonts[1];

	skin = env->getSkin();
	skin->setFont(font);

	txtTrans = env->addStaticText(L"Transparency:", rect<s32>(50,20,250,40), true);
	IGUIScrollBar* scrollbar = env->addScrollBar(true, rect<s32>(50, 45, 250, 60), 0, 104);
	scrollbar->setMax(255);
	SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)0);
	scrollbar->setPos(col.getAlpha());

	txtLog = env->addStaticText(L"Logging ListBox:", rect<s32>(50,80,250,100), true);
	listbox = env->addListBox(rect<s32>(50, 110, 250, 180));

	btnQuit = env->addButton(rect<s32>(10,210,100,240), 0, 101, L"Quit");
	btnNew = env->addButton(rect<s32>(10,250,100,290), 0, 102, L"New Window");
	btnFile = env->addButton(rect<s32>(10,300,100,340), 0, 103, L"Open File");

	edtName = env->addEditBox(L"",rect<s32>(300,60,580,80));
	edtName->setMax(40);
	edtMemo = env->addEditBox(L"",rect<s32>(300,100,580,450));
	edtMemo->setMultiLine(true);
	edtMemo->setTextAlignment(EGUIA_UPPERLEFT, EGUIA_UPPERLEFT);

	lstLang = env->addListBox(rect<s32>(10, 400, 250, 470),0,120);
	lstLang->addItem(L"Arial");
	lstLang->addItem(L"Times Roman");
	lstLang->addItem(L"MS-Gothic(Japanese)");
	lstLang->setSelected(0);

	int lastFPS = -1;

	while(Device->run())
	{
		Driver->beginScene(true, true, SColor(0,64,64,128));

		Scene->drawAll();

		if (!lang){
			font2->draw(L"Hello TrueType",rect<s32>(250,20,640,100),SColor(255,255,64,64),true);
		} else {
			font2->draw(jtxtHello,rect<s32>(250,20,640,100),SColor(255,255,64,64),true);
		}
		env->drawAll();
		Driver->endScene();

		int fps = Driver->getFPS();
		if (lastFPS != fps)
		{
			wchar_t tmp[1024];
			//snwprintf(tmp, 1024, L"Irrlicht TrueType Demo (fps:%d)", fps);
			swprintf(tmp, L"Irrlicht TrueType Demo (fps:%d)", fps);
			Device->setWindowCaption(tmp);
			lastFPS = fps;
		}

	}
	
#if !defined(_IRR_COMPILE_WITH_CGUITTFONT_)
	for(int i= 0; i < 6; i++)
	{
		if(fonts[i] != NULL)
			fonts[i]->drop();
	}
#endif

	Device->drop();
	return 0;
}
