/**
 *      @file  myf.h
 *      @brief  Programa Principal
 *
 * Descrição mais detalhada do ficheiro
 *
 *     @author  Miguel Gaspar, miguel.gaspar124@ua.pt
 *
 *   @internal
 *     Created  27-Sep-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Miguel Gaspar
 *
 ***************************************************
 */

#define YES 1
#define NO 0

#include <gtk/gtk.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <sys/sem.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

#define MAXFFBUFFER 1000

typedef struct {
        int count;
        double x[MAXFFBUFFER];
        double y[MAXFFBUFFER];
} free_form;

struct datashr
{
    int simstatus;
    int flag;
    char length[100];
    char youngM[100];
    char poisson[100];
    char jobname[100];
}; //  struct data for shared memory

#ifdef _MAIN_C_
GtkBuilder *builderG;
free_form ffG={0};   //init count to zero. Do not affect x and y.
struct datashr *data;
int port;
GdkPixbuf *image;
cairo_t *cr;
GtkTextIter iter;
#else
extern GtkBuilder *builderG;
//char *data;
extern struct datashr *data;
extern int port;
bool scan;
extern GdkPixbuf *image;
extern cairo_t *cr;
extern GtkTextIter iter;
#endif

#define SHM_SIZE 128 /**< 128 bytes for shared memory */
#define NOT_READY -1
#define FAIL 0
#define SUCCESS 1

#include "prototypes.h"
