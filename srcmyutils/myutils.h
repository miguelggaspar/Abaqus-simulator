/**
 *       @file  pcolor.h
 *      @brief  Definitions for Text attributes and colors
 *
 *
 *     @author  Joana, joanacarvalhomota@ua.pt
 *
 *   @internal
 *     Created  10-Out-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Joana
 *
 * =====================================================================================
 */




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h> 

/**
* @Attributes
*/

#define RESET           0
#define BRIGHT          1
#define DIM                 2
#define UNDERLINE       3
#define BLINK           4
#define REVERSE         7
#define HIDDEN          8

/**
* @Colors
*/

#define BLACK           0
#define RED                 1
#define GREEN           2
#define YELLOW          3
#define BLUE            4
#define MAGENTA         5
#define CYAN            6
#define GRAY            7
#define WHITE           8

void textcolor(int attr, int fg, int bg);
void PrintRedLine(void);
void ResetTextColors(void);
void HighLightText(void);

#include "prototypes.h"
