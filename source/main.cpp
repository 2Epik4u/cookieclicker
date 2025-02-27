/*---------------------------------------------------------------------------------

	$Id: main.cpp,v 1.13 2008-12-02 20:21:20 dovoto Exp $

	Simple console print demo
	-- dovoto


---------------------------------------------------------------------------------*/
#include <nds.h>

#include <stdio.h>

#include <nf_lib.h>
#include <filesystem.h>

static volatile int frame = 0;
int cookies = 0;

//---------------------------------------------------------------------------------
// VBlank interrupt handler. This function is executed in IRQ mode - be careful!
//---------------------------------------------------------------------------------
static void Vblank() {
//---------------------------------------------------------------------------------
	frame++;
}

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	NF_InitRawSoundBuffers();
	soundEnable();
	nitroFSInit(NULL);
    NF_SetRootFolder("NITROFS");
	NF_LoadRawSound("yum", 0, 22050, 0);

	touchPosition touchXY;

	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();


//	printf("      Hello DS dev'rs\n");
//	printf("     \x1b[32mwww.devkitpro.org\n");
//	printf("   \x1b[32;1mwww.drunkencoders.com\x1b[39m");

	while(1) {

		swiWaitForVBlank();
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;
		if (keys & KEY_TOUCH) {
			cookies = cookies + 1;
			NF_PlayRawSound(0, 127, 64, false, 0);
		}


		touchRead(&touchXY);

		// print at using ansi escape sequence \x1b[line;columnH
		printf("\x1b[10;0HCookies Clicked = %d",cookies);

	//	printf("\x1b[16;0HTouch x = %04X, %04X\n", touchXY.rawx, touchXY.px);
	//	printf("Touch y = %04X, %04X\n", touchXY.rawy, touchXY.py);

	}

	return 0;
}
