/*
This file is part of CanFestival, a library implementing CanOpen Stack. 

Copyright (C): Edouard TISSERANT and Francis DUPIN

See COPYING file for copyrights details.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __objdictdef_h__
#define __objdictdef_h__

/************************* CONSTANTES **********************************/
/** this are static defined datatypes taken fCODE the canopen standard. They
 *  are located at index 0x0001 to 0x001B. As described in the standard, they
 *  are in the object dictionary for definition purpose only. a device does not
 *  to support all of this datatypes.
 */
enum ds301_obj_types
{
    boolean         = 0x01,
    int8            = 0x02,
    int16           = 0x03,
    int32           = 0x04,
    uint8           = 0x05,
    uint16          = 0x06,
    uint32          = 0x07,
    real32          = 0x08,
    visible_string  = 0x09,
    octet_string    = 0x0A,
    unicode_string  = 0x0B,
    time_of_day     = 0x0C,
    time_difference = 0x0D,

    domain          = 0x0F,
    int24           = 0x10,
    real64          = 0x11,
    int40           = 0x12,
    int48           = 0x13,
    int56           = 0x14,
    int64           = 0x15,
    uint24          = 0x16,

    uint40          = 0x18,
    uint48          = 0x19,
    uint56          = 0x1A,
    uint64          = 0x1B,

    pdo_communication_parameter = 0x20,
    pdo_mapping                 = 0x21,
    sdo_parameter               = 0x22,
    identity                    = 0x23,

/* CanFestival is using 0x24 to 0xFF to define some types containing a 
 value range (See how it works in objdict.c)
 */
};


/** Each entry of the object dictionary can be READONLY (RO), READ/WRITE (RW),
 *  WRITE-ONLY (WO)
 */
enum ds301_obj_access
{
    RW     = 0x00,
    WO     = 0x01,
    RO     = 0x02,

    TO_BE_SAVE  = 0x04,
    DCF_TO_SEND = 0x08,
};

/************************ STRUCTURES ****************************/
/** This are some structs which are neccessary for creating the entries
 *  of the object dictionary.
 */
typedef struct td_indextable indextable;

typedef UNS32 (*ODCallback_t)(CO_Data* d, const indextable *, UNS8 bSubindex);

typedef struct td_subindex
{
    UNS8                    bAccessType;
    UNS8                    bDataType; /* Defines of what datatype the entry is */
    UNS32                   size;      /* The size (in Byte) of the variable */
    void*                   pObject;   /* This is the pointer of the Variable */
	ODCallback_t            callback;  /* Callback function on write event */
} subindex;

/** Struct for creating entries in the communictaion profile
 */
struct td_indextable
{
    subindex*   pSubindex;   /* Pointer to the subindex */
    UNS8   bSubCount;   /* the count of valid entries for this subindex
                         * This count here defines how many memory has been
                         * allocated. this memory does not have to be used.
                         */
    UNS16   index;
};

typedef struct s_quick_index{
	UNS16 SDO_SVR;
	UNS16 SDO_CLT;
	UNS16 PDO_RCV;
	UNS16 PDO_RCV_MAP;
	UNS16 PDO_TRS;
	UNS16 PDO_TRS_MAP;
}quick_index;


typedef const indextable * (*scanIndexOD_t)(CO_Data* d, UNS16 wIndex, UNS32 * errorCode);

/************************** MACROS *********************************/

/* CANopen usefull helpers */
#define GET_NODE_ID(m)         (UNS16_LE(m.cob_id) & 0x7f)
#define GET_FUNCTION_CODE(m)   (UNS16_LE(m.cob_id) >> 7)

#endif /* __objdictdef_h__ */
