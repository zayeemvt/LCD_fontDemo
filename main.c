#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <stdbool.h>
#include <stdio.h>

#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"

// Initialization function for graphics
void initializeGraphics(Graphics_Context* g_sContext_p) {
    // Initialize the LCD
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    // Initialize context
    Graphics_initContext(g_sContext_p, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);

    // Set colors and fonts
    Graphics_setForegroundColor(g_sContext_p, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(g_sContext_p, GRAPHICS_COLOR_BLACK);
    Graphics_setFont(g_sContext_p, &g_sFontFixed6x8);

    // Clear the screen
    Graphics_clearDisplay(g_sContext_p);
}

int main(void)
{
    // Stop watchdog timer
    MAP_WDT_A_holdTimer();

    // Initializations
    Graphics_Context g_sContext; // Create context
    initializeGraphics(&g_sContext);

    // Set new fonts, then print them out
    const Graphics_Font* myFonts[4] = {&g_sFontCm14, &g_sFontCmsc14, &g_sFontCmss14, &g_sFontCmtt12};
    const char* myMessage[4] = {"This is Cm14", "This is Cmsc14", "This is Cmss14", "This is Cmtt12"};

    int i = 0;
    for(i = 0; i < 4; i++) {
        Graphics_setFont(&g_sContext, myFonts[i]);
        Graphics_drawString(&g_sContext, (int8_t*) myMessage[i], -1, 5, 20+i*20, false);
    }

    while(1);
}
