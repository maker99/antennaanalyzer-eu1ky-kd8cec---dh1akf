/*
 *   (c) Yury Kuchura
 *   kuchura@gmail.com
 *
 *   This code can be used on terms of WTFPL Version 2 (http://www.wtfpl.net/).
 */

#include <stdio.h>
#include <string.h>
#include "config.h"
#include "LCD.h"
#include "font.h"
#include "touch.h"
#include "hit.h"
#include "textbox.h"
#include "oslfile.h"

extern void Sleep(uint32_t);

static uint32_t rqExit = 0;
static uint32_t shortScanned = 0;
static uint32_t loadScanned = 0;
static uint32_t openScanned = 0;
static char progresstxt[16];
static int progressval;
static TEXTBOX_t hbEx;
static TEXTBOX_t hbScanShort;
static uint32_t hbScanShortIdx;
static TEXTBOX_t hbScanOpen;
static TEXTBOX_t hbScanLoad;
static TEXTBOX_t hbScanProgress;
static uint32_t hbScanProgressId;
static TEXTBOX_t hbSave;
static TEXTBOX_CTX_t osl_ctx = {0};
// static int percents = 0; // unused
extern volatile uint32_t autosleep_timer;

static void _hit_ex(void)
{
    if (shortScanned || openScanned || loadScanned)
        OSL_Select(OSL_GetSelected()); //Reload OSL file
    rqExit = 1;
}

static void progress_cb(uint32_t new_percent)
{
    if (new_percent == progressval || new_percent > 100)
        return;
    progressval = new_percent;
    sprintf(progresstxt, "%u%%", (unsigned int)progressval);
    TEXTBOX_SetText(&osl_ctx, hbScanProgressId, progresstxt);
    autosleep_timer = 30000; //CFG_GetParam(CFG_PARAM_LOWPWR_TIME);
}

static void _hb_scan_short(void)
{
    progressval = 100;
    progress_cb(0);

    hbScanShort.bgcolor = LCD_RGB(128, 128, 0);
    TEXTBOX_DrawContext(&osl_ctx);

    OSL_ScanShort(progress_cb);
    shortScanned = 1;
    hbScanShort.bgcolor = LCD_RGB(0, 128, 0);
    if (shortScanned && openScanned && loadScanned)
        hbSave.bgcolor = LCD_RGB(0, 128, 0);
    progresstxt[0] = '\0';
    TEXTBOX_SetText(&osl_ctx, hbScanProgressId, progresstxt);
    TEXTBOX_DrawContext(&osl_ctx);
}

static void _hb_scan_open(void)
{
    progressval = 100;
    progress_cb(0);

    hbScanOpen.bgcolor = LCD_RGB(128, 128, 0);
    TEXTBOX_DrawContext(&osl_ctx);

    OSL_ScanOpen(progress_cb);
    openScanned = 1;
    hbScanOpen.bgcolor = LCD_RGB(0, 128, 0);
    if (shortScanned && openScanned && loadScanned)
        hbSave.bgcolor = LCD_RGB(0, 128, 0);
    progresstxt[0] = '\0';
    TEXTBOX_SetText(&osl_ctx, hbScanProgressId, progresstxt);
    TEXTBOX_DrawContext(&osl_ctx);
}

static void _hb_scan_load(void)
{
    progressval = 100;
    progress_cb(0);

    hbScanLoad.bgcolor = LCD_RGB(128, 128, 0);
    TEXTBOX_DrawContext(&osl_ctx);

    OSL_ScanLoad(progress_cb);
    loadScanned = 1;
    hbScanLoad.bgcolor = LCD_RGB(0, 128, 0);
    if (shortScanned && openScanned && loadScanned)
        hbSave.bgcolor = LCD_RGB(0, 128, 0);
    progresstxt[0] = '\0';
    TEXTBOX_SetText(&osl_ctx, hbScanProgressId, progresstxt);
    TEXTBOX_DrawContext(&osl_ctx);
}

static void _hit_save(void)
{
    if (!(shortScanned && openScanned && loadScanned))
        return;
    OSL_Calculate();
    Sleep(500);
    rqExit = 1;
}

//OSL calibration window **********************************************************************************************
void OSL_CalWnd(void)
{
    if (-1 == OSL_GetSelected())
        return;

    rqExit = 0;
    shortScanned = 0;
    openScanned = 0;
    loadScanned = 0;
    progresstxt[0] = '\0';

    LCD_FillAll(LCD_BLACK);
    while (TOUCH_IsPressed());

    FONT_Print(FONT_FRANBIG, LCD_WHITE, LCD_BLACK, 110, 0, "OSL Calibration, file %s", OSL_GetSelectedName());

    TEXTBOX_InitContext(&osl_ctx);

    static char shortvalue[50];
    sprintf(shortvalue, " Scan short: %d Ohm ", (int)CFG_GetParam(CFG_PARAM_OSL_RSHORT));
    static char loadvalue[50];
    sprintf(loadvalue, " Scan load: %d Ohm ", (int)CFG_GetParam(CFG_PARAM_OSL_RLOAD));
    static char openvalue[50];
    if (CFG_GetParam(CFG_PARAM_OSL_ROPEN) < 10000)
        sprintf(openvalue, " Scan open: %d Ohm ", (int)CFG_GetParam(CFG_PARAM_OSL_ROPEN));
    else
        strcpy(openvalue, " Scan open: infinite ");

    hbEx = (TEXTBOX_t){.x0 = 10, .y0 = 220, .text = " Cancel and exit ", .font = FONT_FRANBIG,
                            .fgcolor = LCD_BLUE, .bgcolor = LCD_YELLOW, .cb = _hit_ex };
    hbScanShort = (TEXTBOX_t){.x0 = 10, .y0 = 50, .text = shortvalue, .font = FONT_FRANBIG,
                            .fgcolor = LCD_BLUE, .bgcolor = LCD_RGB(64,64,64), .cb = _hb_scan_short };
    hbScanLoad = (TEXTBOX_t){.x0 = 10, .y0 = 100, .text = loadvalue, .font = FONT_FRANBIG,
                            .fgcolor = LCD_BLUE, .bgcolor = LCD_RGB(64,64,64), .cb = _hb_scan_load };
    hbScanOpen = (TEXTBOX_t){.x0 = 10, .y0 = 150, .text = openvalue, .font = FONT_FRANBIG,
                            .fgcolor = LCD_BLUE, .bgcolor = LCD_RGB(64,64,64), .cb = _hb_scan_open };
    hbSave = (TEXTBOX_t){.x0 = 300, .y0 = 220, .text = " Save and exit ", .font = FONT_FRANBIG,
                            .fgcolor = LCD_RGB(128,128,128), .bgcolor = LCD_RGB(64,64,64), .cb = _hit_save };
    hbScanProgress = (TEXTBOX_t){.x0 = 350, .y0 = 50, .text = progresstxt, .font = FONT_FRANBIG, .nowait = 1, .fgcolor = LCD_WHITE, .bgcolor = LCD_BLACK };

    TEXTBOX_Append(&osl_ctx, &hbEx);
    TEXTBOX_Append(&osl_ctx, &hbScanShort);
    TEXTBOX_Append(&osl_ctx, &hbScanLoad);
    TEXTBOX_Append(&osl_ctx, &hbScanOpen);
    TEXTBOX_Append(&osl_ctx, &hbSave);
    hbScanProgressId = TEXTBOX_Append(&osl_ctx, &hbScanProgress);
    TEXTBOX_DrawContext(&osl_ctx);

    for(;;)
    {
        if (TEXTBOX_HitTest(&osl_ctx))
        {
            if (rqExit)
            {
                CFG_Init();
                return;
            }
            Sleep(50);
        }
        autosleep_timer = 30000; //CFG_GetParam(CFG_PARAM_LOWPWR_TIME);
        Sleep(0);
    }
}

static void _hit_err_scan(void) // ************************************************************************
{
    progressval = 100;
    progress_cb(0);

    hbScanShort.bgcolor = LCD_RGB(128, 128, 0);
    TEXTBOX_DrawContext(&osl_ctx);

    OSL_ScanErrCorr(progress_cb);

    hbScanShort.bgcolor = LCD_RGB(0, 128, 0);
    TEXTBOX_SetText(&osl_ctx, hbScanShortIdx, "  Success  ");

    progresstxt[0] = '\0';
    TEXTBOX_SetText(&osl_ctx, hbScanProgressId, progresstxt);
    TEXTBOX_DrawContext(&osl_ctx);
}

//Hardware error calibration window **********************************************************************
void OSL_CalErrCorr(void)
{
    rqExit = 0;
    shortScanned = 0; //To prevent OSL file reloading at exit
    openScanned = 0;  //To prevent OSL file reloading at exit
    loadScanned = 0;  //To prevent OSL file reloading at exit
    progresstxt[0] = '\0';

    LCD_FillAll(LCD_BLACK);
    while (TOUCH_IsPressed());

    FONT_Write(FONT_FRANBIG, LCD_WHITE, LCD_BLACK, 80, 0, "HW Error Correction Calibration");
    FONT_Write(FONT_FRAN, LCD_RED, LCD_BLACK, 0, 50, "Set jumper to HW calibration position and hit Start button");

    TEXTBOX_InitContext(&osl_ctx);

    TEXTBOX_t hbEx = {.x0 = 10, .y0 = 220, .text = " Exit ", .font = FONT_FRANBIG,
                            .fgcolor = LCD_BLUE, .bgcolor = LCD_YELLOW, .cb = _hit_ex };
    TEXTBOX_Append(&osl_ctx, &hbEx);

    //Reusing hbScanShort
    hbScanShort = (TEXTBOX_t){.x0 = 100, .y0 = 120, .text = " Start HW calibration ", .font = FONT_FRANBIG,
                            .fgcolor = LCD_RED, .bgcolor = LCD_RGB(64, 64, 64), .cb = _hit_err_scan };
    hbScanShortIdx = TEXTBOX_Append(&osl_ctx, &hbScanShort);

    hbScanProgress = (TEXTBOX_t){.x0 = 350, .y0 = 50, .text = progresstxt, .font = FONT_FRANBIG, .nowait = 1,
                                 .fgcolor = LCD_WHITE, .bgcolor = LCD_BLACK };
    hbScanProgressId = TEXTBOX_Append(&osl_ctx, &hbScanProgress);

    TEXTBOX_DrawContext(&osl_ctx);

    for(;;)
    {
        if (TEXTBOX_HitTest(&osl_ctx))
        {
            if (rqExit)
                return;
            Sleep(50);
        }
        Sleep(0);
    }
}

//=====================================================================
//TX Calibration for Network Analyzer
//KD8CEC
//---------------------------------------------------------------------
static void _hit_tx_scan(void) // ************************************************************************
{
    progressval = 100;
    progress_cb(0);

    hbScanShort.bgcolor = LCD_RGB(128, 128, 0);
    TEXTBOX_DrawContext(&osl_ctx);

    OSL_ScanTXCorr(progress_cb);

    hbScanShort.bgcolor = LCD_RGB(0, 128, 0);
    TEXTBOX_SetText(&osl_ctx, hbScanShortIdx, "  Success  ");

    progresstxt[0] = '\0';
    TEXTBOX_SetText(&osl_ctx, hbScanProgressId, progresstxt);
    TEXTBOX_DrawContext(&osl_ctx);
}

void OSL_CalTXCorr(void)
{
    rqExit = 0;
    shortScanned = 0; //To prevent OSL file reloading at exit
    openScanned = 0;  //To prevent OSL file reloading at exit
    loadScanned = 0;  //To prevent OSL file reloading at exit
    progresstxt[0] = '\0';

    LCD_FillAll(LCD_BLACK);
    while (TOUCH_IsPressed());

    FONT_Write(FONT_FRANBIG, LCD_WHITE, LCD_BLACK, 80, 0, "TX (S2) Strength Calibration");
    FONT_Write(FONT_FRAN, LCD_RED, LCD_BLACK, 0, 50, "Connect S1 and S2 with coaxial cable and hit Start button");

    TEXTBOX_InitContext(&osl_ctx);

    TEXTBOX_t hbEx = {.x0 = 10, .y0 = 220, .text = " Exit ", .font = FONT_FRANBIG,
                            .fgcolor = LCD_BLUE, .bgcolor = LCD_YELLOW, .cb = _hit_ex };
    TEXTBOX_Append(&osl_ctx, &hbEx);

    //Reusing hbScanShort
    hbScanShort = (TEXTBOX_t){.x0 = 100, .y0 = 120, .text = " Start TX calibration ", .font = FONT_FRANBIG,
                            .fgcolor = LCD_RED, .bgcolor = LCD_RGB(64, 64, 64), .cb = _hit_tx_scan };
    hbScanShortIdx = TEXTBOX_Append(&osl_ctx, &hbScanShort);

    hbScanProgress = (TEXTBOX_t){.x0 = 350, .y0 = 50, .text = progresstxt, .font = FONT_FRANBIG, .nowait = 1,
                                 .fgcolor = LCD_WHITE, .bgcolor = LCD_BLACK };
    hbScanProgressId = TEXTBOX_Append(&osl_ctx, &hbScanProgress);

    TEXTBOX_DrawContext(&osl_ctx);

    for(;;)
    {
        if (TEXTBOX_HitTest(&osl_ctx))
        {
            if (rqExit)
                return;
            Sleep(50);
        }
        Sleep(0);
    }
}
