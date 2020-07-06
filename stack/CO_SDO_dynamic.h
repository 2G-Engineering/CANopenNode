/*
 * CO_SDO_dynamic.h
 *
 *  Created on: Apr 6, 2020
 *      Author: ctaglia
 */

#ifndef APPS_EXTERNAL_TD_COMMS_CANOPENNODE_STACK_CO_SDO_DYNAMIC_H_
#define APPS_EXTERNAL_TD_COMMS_CANOPENNODE_STACK_CO_SDO_DYNAMIC_H_

/* "Manufacturer-defined objects start at index 0x2000 */
#define CANOPEN_OBJECT_OFFSET (0x2000)
/* "Manufacturer-defined objects end at index 0x5999 */
#define CANOPEN_OBJECT_MAX    (0x5999)

const CO_OD_entry_t* CO_lookup_object(uint16_t index, CO_OD_entry_t* source_object);

#endif /* APPS_EXTERNAL_TD_COMMS_CANOPENNODE_STACK_CO_SDO_DYNAMIC_H_ */
