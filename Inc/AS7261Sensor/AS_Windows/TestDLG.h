/*
 * TestDLG.h
 *
 *  Created on: 05.02.2020.
 *      Author: tatjana
 */

#ifndef TESTDLG_H_
#define TESTDLG_H_

#include "DIALOG.h"

#define ID_WINDOW_START (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x02)
#define ID_TEXT_START (GUI_ID_USER + 0x03)
#define ID_PROGBAR_START (GUI_ID_USER + 0x05)
#define ID_EDIT_START (GUI_ID_USER + 0x06)
#define ID_IMAGE_0 (GUI_ID_USER + 0x08)
#define ID_IMAGE_1 (GUI_ID_USER + 0x09)

#define ID_IMAGE_0_IMAGE_0 0x00
#define ID_IMAGE_1_IMAGE_0 0x01

WM_HWIN CreateTest(void);

#endif /* TESTDLG_H_ */
