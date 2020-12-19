/**
 * @brief 
 * 
 */

#ifndef FICHIER_CONFSRV_H
#define FICHIER_CONFSRV_H

typedef struct
{
    const char* ip;
    const char* port;
} configuration;

configuration* config();

#endif /* FICHIER_CONFSRV_H */