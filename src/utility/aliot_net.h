/*
 * aliot_net.h
 *
 *  Created on: May 5, 2017
 *      Author: qibiao.wqb
 */

#ifndef ALIYUN_IOT_COMMON_NET_H
#define ALIYUN_IOT_COMMON_NET_H

#include "aliot_platform.h"

typedef struct {
    char *pHostAddress;     ///< Pointer to a host name string
    char *pHostPort;        ///< destination port
    char *pPubKey;          ///< Pointer to a ca string
} ConnectParams;


/**
 * @brief The structure of network connection(TCP or SSL).
 *   The user has to allocate memory for this structure.
 */

struct Network;

typedef struct Network Network_t;
typedef struct Network *pNetwork_t;

struct Network {
    const char *pHostAddress;
    uint16_t port;
    uint16_t ca_crt_len;
    const char *ca_crt;       //TCP connection when the value is NULL; SSL connection when the value is NOT NULL

    intptr_t handle;    //connection handle

    int (*read)(pNetwork_t, char *, uint32_t, uint32_t);      /**< Read data from server function pointer. */
    int (*write)(pNetwork_t, const char *, uint32_t, uint32_t);     /**< Send data to server function pointer. */
    int (*disconnect)(pNetwork_t);                  /**< Disconnect the network function pointer.此函数close socket后需要初始化为-1，如果为-1则不再执行close操作*/
    intptr_t (*connect)(pNetwork_t);
};


int aliot_net_read(pNetwork_t pNetwork, char *buffer, uint32_t len, uint32_t timeout_ms);
int aliot_net_write(pNetwork_t pNetwork, const char *buffer, uint32_t len, uint32_t timeout_ms);
int aliot_net_disconnect(pNetwork_t pNetwork);
intptr_t aliot_net_connect(pNetwork_t pNetwork);
int aliot_net_init(pNetwork_t pNetwork, const char *host, uint16_t port, const char *ca_crt);

#endif /* ALIYUN_IOT_COMMON_NET_H */
