/*
 * StringFunction.h
 *
 *  Created on: 29 Jan 2020
 *      Author: tatjana
 */

#ifndef AS7261SENSOR_STRINGFUNCTION_H_
#define AS7261SENSOR_STRINGFUNCTION_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char** str_split(char* a_str, const char a_delim);
void ClearSpace(char* String);
void DelateOKinMSG (char *RecPoruka);
void DelateOKinMSGPlus (char *String);
void ChangeCom(char* String);

#endif /* AS7261SENSOR_STRINGFUNCTION_H_ */
