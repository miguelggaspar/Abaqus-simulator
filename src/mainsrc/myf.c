/**
 *      @file  myf.c
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
#include "myf.h"
#include <myutils.h>

/**
 * @brief  Leave gtk main loop
 *
 * @param widget - the one that originated the call
 * @param user_data - Custom data with a widget ID to fetch some info
 * @return void
 */
 void pari_delete_event(GtkWidget * window, GdkEvent * event, gpointer data) {
   g_print("you should not use the os to force leave");
   gtk_main_quit();
 }


 /**
  * @brief  Callback to catch CTRL-C
  */
 void InterceptCTRL_C(int a)
 {
   g_print("Sair por CTRL-C\n");
   gtk_main_quit();
 }

/**
 * @brief  Prints red message from child process
 *
 * @param  str - message to print
 * @return void
 */
 void MessageFromChild( char *str)
 {
   textcolor(RESET,RED,WHITE);  //from pcolor
   printf("%s",str);
   ResetTextColors();           //from pcolor
 }

 /**
  * @brief  Prints green message from parent process
  *
  * @param  str - message to print
  * @return void
  */
 void MessageFromParent( char *str)
 {
   textcolor(RESET,GREEN,WHITE);  //from pcolor
   printf("%s",str);
   ResetTextColors();             //from pcolor
 }

/**
 * @brief This Function enables or disables stress, displacement, graph
 *    buttons depending on simulation status.
 *
 * @param  mode - TRUE or FALSE depending on simulation status
 * @return void
 */
void ChangeButtons(int mode) {
    /* Get widget ID for "btn_stress" */
    GtkWidget *btn_stress = GTK_WIDGET(gtk_builder_get_object(builderG, "btn_stress"));
    /* Get widget ID for "btn_displacement" */
    GtkWidget *btn_displacement = GTK_WIDGET(gtk_builder_get_object(builderG, "btn_displacement"));
    /* Get widget ID for "btn_graph" */
    GtkWidget *btn_graph = GTK_WIDGET(gtk_builder_get_object(builderG, "btn_graph"));
      switch (mode) {
        case FALSE: /* if no simulation was ever submited or completed */
              gtk_widget_set_sensitive (btn_stress, FALSE);
              gtk_widget_set_sensitive (btn_displacement, FALSE);
              gtk_widget_set_sensitive (btn_graph, FALSE);
              break;
        case TRUE: /* if a simulation is completed */
              gtk_widget_set_sensitive (btn_stress, TRUE);
              gtk_widget_set_sensitive (btn_displacement, TRUE);
              gtk_widget_set_sensitive (btn_graph, TRUE);
              break;
}
}


 /**
  * @brief  Gets a shared memory and connects to it
  *
  * The function first creates a random key to identify
  * the memory and then connects to it with some specific permissions
  * @return int The Shared memory ID. Returns -1 in case of failure.
  */
 int GetSharedMem()
 {
   key_t key;                    /*it's a long int */
   int shm_id;
   key = ftok("../src/mainsrc/main.c", 'X');       /* generate a random key based on a file name and char */
   if(key == -1) { perror("ftok"); return -1; }
   /* now connect to (or possibly create) the shared memory segment with permission 644 */
   shm_id = shmget(key, sizeof(struct datashr), IPC_CREAT | 0644);
   if(shm_id == -1) { perror("shmget"); return -1; }
   return shm_id;
 }

/**
 * @brief  Prints all data from shared memory struct.
 *
 *
 * @param  mode - choose between GUI and Manager printing
 * @return void
 */
void PrintStatus(int mode){
  switch (mode) {
    case 1: textcolor(RESET,GREEN,WHITE);  // on GUI
            printf("GUI:flag=%d\t length: %s\tyoungM: %s\tpoisson: %s\tsim: %d\n",data->flag,data->length,data->youngM,data->poisson,data->simstatus);
            break;
    case 2: textcolor(RESET,RED,WHITE);  //on Manager
            printf("Manager:flag=%d\t length: %s\tyoungM: %s\tpoisson: %s\tsim: %d\n",data->flag,data->length,data->youngM,data->poisson,data->simstatus);
            break;
  }
  ResetTextColors();           //from pcolor
}

/**
 * @brief  Prints system state on a Gtk text view. Wheather a simulation
 *    is completed, submited or aborted with erros.
 *
 * @param  text - Text to print on Gtk text view.
 * @return void
 */
void PrintOnLog (char *text)
{
    GtkTextBuffer *buffer;  // stores attributed text for display in a GtkTextView
    GtkTextMark *mark;      // A position in the buffer preserved across buffer modifications
    GtkTextView *textview;
    /* Get widget ID for "txt_log" */
    textview = GTK_TEXT_VIEW(gtk_builder_get_object(builderG, "txt_log"));
    /* Get buffer from textview */
    buffer = gtk_text_view_get_buffer(textview);
    /* Returns the mark that represents the cursor (insertation point)*/
    mark = gtk_text_buffer_get_insert(buffer);
    /* Initializes iter with the current position of mark */
    gtk_text_buffer_get_iter_at_mark(buffer, &iter, mark);
    /*Inserts len bytes of text at position iter . If len is -1,
    text must be nul-terminated and will be inserted in its entirety.*/
    gtk_text_buffer_insert(buffer, &iter, text, -1);
}
