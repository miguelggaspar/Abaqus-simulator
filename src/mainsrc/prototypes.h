/*File generated automatically in miguel-K56CB by miguel on Dom Jan 28 01:47:40 WET 2018*/
#ifdef __cplusplus
extern "C" {
#endif
/* manager.c */
int ManagerMain();
int Client(char *message,int port);
/* main.c */
int main(int argc, char *argv[]);
/* gui.c */
int GUIMain();
/* callbacks.c */
void on_simulation_clicked(GtkWidget * widget, GdkEvent * event, gpointer user_data);
gboolean p_ForceRefreshDA(gpointer user_data);
gboolean my_timeout(gpointer user_data);
void p_RedrawFreeForm(cairo_t * cr);
void p_RedrawText(cairo_t * cr);
void p_InitTimer();
/* myf.c */
void ChangeButtons(int mode);
int GetSharedMem();
void InterceptCTRL_C(int a);
void MessageFromChild(char *str);
void MessageFromParent(char *str);
void PrintStatus(int mode);
void pari_delete_event(GtkWidget * window, GdkEvent * event, gpointer data);
void PrintOnLog (char *text);
#ifdef __cplusplus
}
#endif
