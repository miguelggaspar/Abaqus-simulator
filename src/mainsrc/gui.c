/**
 *      @file  gui.c
 *      @brief Graphical User Interface
 *
 * This file initialize and config some parameters for GTK interface.
 *
 *     @author  Miguel Gaspar, miguel.gaspar124@ua.pt
 *
 *   @internal
 *     Created  10-Jan-2018
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Miguel Gaspar
 *
 ***************************************************
 */

#include "myf.h"


/**
 * @brief  GUI main function
 *
 * This function configs and starts Gtk main loop. It also atach and detach from
 * a shared memory.
 *
 * @param  none
 * @return shm_id - ID to destroy shared memory
 */
int GUIMain()
{
    int n, shm_id;
    char str[100];   //string to put a message

    /* get shm id for shared memory */
    shm_id = GetSharedMem();
    if(shm_id == -1) return -1;     //failure
    /* attach to the memory segment to get a pointer to it */
    data = (struct datashr *) shmat(shm_id, NULL, 0);
    //handling erros
    if(data == (struct datashr *) (-1))
    {
            perror("shmat");
            exit(1);
    }

    PrintStatus(1);

    /* set  */
    if (data->flag==1) {
            data->flag = 0;
            PrintStatus(1);
    }
    gtk_init(NULL, NULL);
    /* load the interface after a configuration file*/
    builderG = gtk_builder_new();
    gtk_builder_add_from_file(builderG, "exp.glade", NULL);
    /* connect the signals in the interface */
    gtk_builder_connect_signals(builderG, NULL);
    /* get main window Widget ID and connect special signals */
    GtkWidget *window1 = GTK_WIDGET(gtk_builder_get_object(builderG, "window1"));
    if(window1)
    {
            g_signal_connect(G_OBJECT(window1), "delete_event", G_CALLBACK(pari_delete_event), NULL);
    }
    /* use signal to catch SIGINT  (CTRL-C) */
    signal(SIGINT, InterceptCTRL_C);
    /* add my_timeout function to a thread */
    g_timeout_add (1000, my_timeout, NULL);
    /* disable stress,displacement and graphs buttons */
    ChangeButtons(FALSE);
    //p_InitTimer();
    /* start the event loop */
    gtk_main();
    /* detach from the mem segment since it is leaving */
    if(  shmdt(data) == -1 )
    {
            perror("shmdt");
            exit(1);
    }
    return shm_id; /* return id to destroy shared memory */
}
