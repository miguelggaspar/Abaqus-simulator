/**
*      @file  auxfuncs.c
*      @brief  auxiliary functions
*
*
* =====================================================================================
*/

#include "myserver.h"

/**
 * @brief  Error handling
 *
 * @param  msg - type of error
 * @return void
 */
void myerror(const char *msg)
{
	perror(msg);
	exit(1);
}

/**
 * @brief  Cancels infinite loop
 */
void ManageCTRL_C(int dummy)
{
	printf("User CTRL-C pressed. Closing server.\n");
	infinite_loopG=0;
}

/**
 * @brief  Actual time
 */
char *vsTimeString()
{
	char *auxstr = (char *)malloc(100);
	bzero(auxstr,100);
	time_t t=time(NULL);
	struct tm *lt = localtime(&t);
	sprintf(auxstr, "%02d:%02d:%02d", lt->tm_hour, lt->tm_min, lt->tm_sec);
	return auxstr;
}

/**
 * @brief Here the simulation is pre executed using an executable shell script.
 * First, all  of parameters are stored in an array (command) as string with
 * spaces between them. Then the command string is passed through a pip stream
 * and executed on shell with the output available to read.
 *
 * @param  length - char with length value for simulation
 * @param  youngM - char with youngM value for simulation
 * @param  poisson - char with poisson value for simulation
 * @param  jobname - char with jobname value for simulation
 * @return none
 */
int StartSimulation(char *length, char *youngM, char *poisson, char *jobname){
		char  line[BUFFSIZE];         /* the input line */
		char  *argv[64];              /* the command line argument */
		char *str=malloc(1000);       /* variable to read all output from pipe stream*/
		int N;
		char command[3072];
		/* Fill command char with all parameters to execute a shell script.
 		 If you change the directory of this script, this operation will fail.
		 To do so, you have to change here too. */
//		strcat(command,"../shScript/simulation.sh");
		strcat(command,"../src/SimScripts/simulation.sh");
		strcat(command," ");
		strcat(command,length);
		strcat(command," ");
		strcat(command,youngM);
		strcat(command," ");
		strcat(command,poisson);
		strcat(command," ");
		strcat(command,jobname);
		printf("command right before execution:%s\n", command);
  	FILE *out = popen(command, "r");   //Execute command on shell and make output available to read
		N=fread(str, 1, 1000, out);        //read the command output into str
		str[N]='\0';										   //read the command output into str
		printf("OUTPUT: %s\n",str);
}
