/*
 * CO_debug.h
 *
 *  Created on: Apr 28, 2020
 *      Author: jlange
 */

#ifndef APPS_EXTERNAL_TD_COMMS_CANOPENNODE_CO_DEBUG_H_
#define APPS_EXTERNAL_TD_COMMS_CANOPENNODE_CO_DEBUG_H_

//#define WANT_CO_DEBUG

#ifdef WANT_CO_DEBUG
#define CO_DBG(...)  syslog(LOG_INFO, __VA_ARGS__)
#else
#define CO_DBG(...)
#endif

#endif /* APPS_EXTERNAL_TD_COMMS_CANOPENNODE_CO_DEBUG_H_ */
