/*File generated automatically in miguel-K56CB by miguel on Seg Jan 29 01:47:27 WET 2018*/
#ifdef __cplusplus
extern "C" {
#endif
/* client.c */
/* myfclient.c */
int pari_AskDataFromServer(char *ip, int port, char *message, char *server_reply, int maxChars);
srv_status pari_TestServer(char *addr, int port, struct timeval * tv);
#ifdef __cplusplus
}
#endif
