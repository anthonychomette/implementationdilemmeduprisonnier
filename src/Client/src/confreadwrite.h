#ifndef CONFREADWRITE_H
#define CONFREADWRITE_H

//void confwrite(NumClient,ip,port);
//void confread(int NumClient,char ip,int port);
static int handler(void* user,const char* section,const char* name,const char* value);

typedef struct
{
    const char* ip;
    const char* port;
    const char* IdClient;
} configuration;

configuration * config();

#endif /* CONFREADWRITE_H */
