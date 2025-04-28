
#include <nds.h>
#include <stdio.h>
#include <nf_lib.h>
#include <filesystem.h>


int cookies = 0;

int main(void) {
	NF_Set2D(0, 0);
    NF_Set2D(1, 0);
	consoleDemoInit();
	NF_InitRawSoundBuffers();
	soundEnable();
	nitroFSInit(NULL);
    NF_SetRootFolder("NITROFS");
	NF_Set2D(0, 0);
    NF_Set2D(1, 0);
    // Initialize tiled backgrounds system
    NF_InitTiledBgBuffers();    // Initialize storage buffers
    NF_InitTiledBgSys(0);       // Top screen
    NF_InitTiledBgSys(1);       // Bottom screen

	NF_LoadRawSound("yum", 0, 22050, 0);
	NF_LoadTiledBg("cookie_flat", "cookie", 256, 256);
	NF_CreateTiledBg(1, 3, "cookie");
	// load text
	NF_InitTextSys(0);          // Top screen
	NF_LoadTextFont16("font16", "normal", 256, 256, 0);   // Load rotated text
	NF_CreateTextLayer16(0, 0, 0, "normal");
	char buffer[64];  // <-- Make space for the final text


	

	touchPosition touchXY;


	

	while(1) {
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;
		if (keys & KEY_TOUCH) {
			cookies++;
			NF_PlayRawSound(0, 127, 64, false, 0);
		}
		printf("\x1b[0;0HCookies Clicked = %d",cookies);
		NF_UpdateTextLayers();
		sprintf(buffer, "Cookies clicked = %d", cookies);
		NF_WriteText16(0, 0, 1, 1, buffer);
		



		touchRead(&touchXY);

		// print at using ansi escape sequence \x1b[line;columnH


	//	printf("\x1b[16;0HTouch x = %04X, %04X\n", touchXY.rawx, touchXY.px);
	//	printf("Touch y = %04X, %04X\n", touchXY.rawy, touchXY.py);

	}

	return 0;
}
