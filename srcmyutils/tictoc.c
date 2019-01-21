/**
 * @brief  Simple Chronograph
 * @param  none
 * @return void
 */
#include "myutils.h"

long tictoc(int mode){
  static struct timeval t1;
  struct timeval t2;
  long total;
  if(mode==0){
    gettimeofday(&t1,NULL);
    return 0;
  } else {
    gettimeofday(&t2,NULL);
    total = 1e6*(t2.tv_sec - t1.tv_sec)+(t2.tv_usec-t1.tv_usec);
    return total;
  }
}