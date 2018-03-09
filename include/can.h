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

#ifndef __can_h__
#define __can_h__

#include "applicfg.h"

/** 
 * @brief The CAN message structure 
 * @ingroup can
 */
typedef struct {
#ifdef CANLIB_USE_EXT_FRAME
  UNS32 cob_id;	/**< message's ID which support extended frame format */
  UNS8 res0;		/**< padding */
  UNS8 res1;		/**< padding */
#else
  UNS16 cob_id;	/**< message's ID */
#endif
  UNS8 rtr;		/**< remote transmission request. (0 if not rtr message, 1 if rtr message) */
  UNS8 len;		/**< message's length (0 to 8) */
  UNS8 data[8]; /**< message's datas */
} Message;

#ifdef CANLIB_USE_EXT_FRAME
#define Message_Initializer {0,0,0,0,0,{0,0,0,0,0,0,0,0}}
#else
#define Message_Initializer {0,0,0,{0,0,0,0,0,0,0,0}}
#endif

typedef UNS8 (*canSend_t)(Message *);

#endif /* __can_h__ */
