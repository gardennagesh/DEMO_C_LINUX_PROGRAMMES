/*************************************File1: logmsg.h ***************************************************************
 This is Headerfile: logmsg.h 
 Pls look in comments of main.c 
*********************************************************************************************************************/

#define INFO  0x1
#define WARN  0x2
#define ERROR 0x4
#define DEBUG 0x8
void logmsg(int ltype, char *msg);
void ABC_func (void); 
void XYZ_func (void); 
