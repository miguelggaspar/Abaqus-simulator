/*File generated automatically in robotica4 by vitor on Ter Dez 13 12:00:42 WET 2016*/
#ifdef __cplusplus
extern "C" {
#endif
/* auxfuncs.c */
void ManageCTRL_C(int dummy);
void myerror(const char *msg);
char *vsTimeString();
int StartSimulation(char *length, char *youngM, char *poisson, char *jobname);
/* server.c */
int main(int argc, char *argv[]);
void processclient(int sock, char *clientID);
#ifdef __cplusplus
}
#endif
