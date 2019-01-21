/**
 *      @file  manager.c
 *      @brief  Comunications Manager
 *
 *
 *
 *     @author  Miguel Gaspar, miguel.gaspar124@ua.pt
 *
 *   @internal
 *     Created  10-Sep-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Miguel Gaspar
 *
 ***************************************************
 */

#include "myf.h"

#define MAXCHARS 4096   //just a large buffer for data chunks

/**
 * @brief  This function is always checking for changes in
 *        simulation events, and changes flags back to 0.
 *
 * @param  none
 * @return TRUE
 */

int ManagerMain()
{
  int n, shm_id;
  char str[100];                  //string to put a message
  char server_reply[MAXCHARS-1];
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
  /* loop until parent (gui) kills this process*/
  while(1){
    PrintStatus(2);
    sleep(1);
    if (data->flag){   //Simulation is submited
      PrintStatus(2);
      /* fill str with parameters for simulation */
      sprintf(str,"simulate,%s,%s,%s,%s",data->length,data->youngM,data->poisson,data->jobname);
      /* Send parameters through Client function to Server */
      if (Client(str,port)){
        data->simstatus = SUCCESS;    // Simulation Succeeded
      } else {
        data->simstatus = FAIL;       // Simulation Failed
      }
      sleep(1);
      }
    }
  /* detach from the mem segment */
   if( shmdt((void *)data) == -1)
   {
           perror("shmdt");
           exit(1);
   }
  return 0;
}
