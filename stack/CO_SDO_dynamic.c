/*
 * CO_SDO_dynamic.c
 *
 * Used to perform run-time mapping of CANopen objects and Modbus registers
 *
 *  Created on: Apr 6, 2020
 *      Author: jlange
 */
#include "globals.h"

#include "CO_SDO_dynamic.h"
#include "CO_SDO.h"
#include "modbus_registers.h"
#include "CO_debug.h"

/* Stores the highest register nubmer that is present in the modbus register map.
 * Calculated on startup; do not use before
 */
extern uint16_t modbus_holding_reg_cnt;
/*
 * Our modbus registers are numbered starting at 0.
 * CANopen allows user-defined (Manufacturer-specific) objects in the range [0x2000, 0x5999] (a total of 16,383 objects)
 * We will map each modbus register to a VAR object of type Octet String.  The object index will be the Modbus address number + 0x2000.
 *
 */



const CO_OD_entry_t* CO_lookup_object(uint16_t index, CO_OD_entry_t* source_object) {
    /* Make sure the object index is in the range of valid manufacturer-specific objects */
    if ((index < CANOPEN_OBJECT_OFFSET) || (index > CANOPEN_OBJECT_MAX))  {
        CO_DBG("CANopen object out of Modbus range\n");
        return NULL;
    }
    if (!source_object) {
        syslog(LOG_INFO, "source_object is NULL!\n");
        return NULL;
    }

    /* Let's look the specified index to see if it corresponds to a modbus address in our map.*/
    uint16_t address = index - CANOPEN_OBJECT_OFFSET;

    CO_DBG("CANopen request for Modbus address %d\n", address);

    const modbusreg_t *mbreg = lookup_by_modbus_addr(address);

    if (mbreg) {
      CO_DBG("Modbus register found.\n");
        /* We have found a modbus register corresponding to this index.
           We'll set some attributes for convenience, and set the data pointer
           to the mbreg struct.
           Any consumers of this object will need to look for the CO_ODA_FROM_MODBUS
           flag and handle the data register appropriately.*/
      source_object->attribute = CO_ODA_MEM_RAM | CO_ODA_FROM_MODBUS;
      if (mbreg->getter) {
          source_object->attribute |= CO_ODA_READABLE;
      }
      if (mbreg->setter) {
          source_object->attribute |= CO_ODA_WRITEABLE;
      }
      source_object->length = mbreg->nWords * 2;
      source_object->pData = mbreg;
      source_object->index = index;
      return source_object;
    } else {
      CO_DBG("Modbus register NOT found.\n");
        /* Not a valid modbus address */
        return NULL;
    }

}

