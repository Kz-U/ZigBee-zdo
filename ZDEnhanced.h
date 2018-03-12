/**************************************************************************************************
  Filename:       ZDEnhanced.h
  Revised:        $Date: 2014-1-4
  Revision:       $Revision: 00001 $

  Description:    This file contains the interface to the Zigbee Device Enhanced


  新增协议，增强zigbee device功能，当前拥有功能包括白名单管理功能，入网限制功能
  可以作为ZDO层一个新增的子集加入到ZDO层
**************************************************************************************************/

#ifndef _ZD_ENHANCED_H
#define _ZD_ENHANCED_H

/*********************************************************************
 * INCLUDES
 */
#include "ZComDef.h"
#include "NLMEDE.h"
#include "AF.h"
#include "ZDProfile.h"
#include "ZDConfig.h"
  
/*********************************************************************
 * CONSTANTS
 */
//ZDO Command
#define ZDE_Join_Denied            ((uint16)0x0040)
#define ZDE_Join_Accept_req        ((uint16)0x0041)
#define ZDE_Join_Verify_req        ((uint16)0x0042)

#define ZDE_Join_Accept_rsp        (ZDE_Join_Accept_req | ZDO_RESPONSE_BIT)
#define ZDE_Join_Verify_rsp        (ZDE_Join_Verify_req | ZDO_RESPONSE_BIT)

#define ZDE_JOIN_ACCEPT_LIST_SIZE   64


#define ZDE_WHITE_LIST_CLEAR_WAIT       10
#define ZDE_WHITE_LIST_REFRESH_PERIOD   1000
#define ZDE_DENIED_NOTIFY_WAIT          333    //3秒广播10次
#define ZDE_WHITE_LIST_VERIFY_WAITE     250

#define ZDE_EVT_WHITE_LIST_REFRESH      0x0001
#define ZDE_EVT_DENIED_NOTIFY           0x0002
#define ZDE_EVT_PARENT_VERIFY           0x0004

#define ZDE_JOIN_DENIED_NONE           0x00
#define ZDE_JOIN_DENIED_ASSOC          0x01
#define ZDE_JOIN_DENIED_REJOIN_UNSEC   0x02
#define ZDE_JOIN_DENIED_REJOIN_ALL     0x03

/*********************************************************************
 * TYPEDEFS
 */
typedef struct
{
  uint8 extAddr[Z_EXTADDR_LEN];
  uint8 capability;
  uint8 rejoin;
}ZDE_JoinDenied_t;

typedef struct
{
  sAddrExt_t  extAddrs;
  uint8 life;
}ZDE_JoinAcceptReq_t;

typedef void(*ZDE_JoinDeniedCb_t)(uint16 parent,ZDE_JoinDenied_t* pDenied,uint8 count);

/*********************************************************************
 * GLOBAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL VARIABLES
 */

extern uint8 ZDE_TaskID;

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

extern void ZDE_Init(uint8 task_id);

extern uint16 ZDE_event_loop( uint8 task_id, uint16 events);

extern afStatus_t ZDE_JoinDenied(ZDE_JoinDenied_t* pDenied,uint8 count);

extern afStatus_t ZDE_JoinAcceptReq(zAddrType_t* dstAddr,ZDE_JoinAcceptReq_t* accept,byte SecurityEnable); 

extern afStatus_t ZDE_JoinVerifyReq(uint16 parentAddr,uint8* extAddr,byte SecurityEnable);

extern uint8 ZDE_WhiteListInput(ZDE_JoinAcceptReq_t* list);

extern uint8 ZDE_WhiteListCheck(uint8* extAddr);

extern void ZDE_RegisterJoinDeniedCB(ZDE_JoinDeniedCb_t cb);

#endif