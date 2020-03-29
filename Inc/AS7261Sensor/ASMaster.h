/*
 * ASMaster.h
 *
 *  Created on: 29 Jan 2020
 *      Author: tatjana
 */

#ifndef AS7261SENSOR_ASMASTER_H_
#define AS7261SENSOR_ASMASTER_H_


#include "AS7261Sensor/AS_ATCommands.h"

#include "AS7261Sensor/AS_Windows/TestDLG.h"
#include "AS7261Sensor/AS_Windows/Kolorimetrija.h"


void ConfigMenu();

void AS7261_Sensor();
void TestConnection();
void Gain();
void IntegrationTime();
void Merenja();


#endif /* AS7261SENSOR_ASMASTER_H_ */
