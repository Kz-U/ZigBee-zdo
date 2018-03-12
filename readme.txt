z-stack版本：2.6.1

优化后的特点：
1，在有多个协调器并存的环境中，只需要在协调器上输入对应节点的MAC地址，节点就能加入到该协调器的网络中，不用对节点进行任何配置，节点上也不需要有任何配置接口，方便连接。建议在第一次为节点烧写程序时，就把节点的MAC地址读出来，打印成条码，然后通过连接协调器上位机的条码读取设备进行组网。

2，应用层可以判断节点当前是否处于有Zigbee网络的范围内，是否掉网，是否无法入网等多种异常情况。节点可以在不能入网的情况下进入低功耗。原版z-stack的原则是“节点必须加入一个网络，哪怕这个网络是未经认证”，而优化后的协议，则是“未经认证的协调器，不能加入其网络”

3，节点带有黑名单功能，能够把未经认证的协调器PANID录入到黑名单中。

使用方法：
1，删除原Z-stack中的zdo文件夹，并用此文件夹替换原来的文件夹。

2，原工程中workspace中，删除ZDO条目下所有内容，并把该文件夹下所有文件拖到原ZDO条目下。

3，如果需要使用MAC地址过滤，在原工程的tasksArr中，添加ZDE_event_loop，并且在osalInitTasks中添加ZDE_Init。

4，调用函数ZDE_RegisterJoinDeniedCB（位于ZDEnhanced.h中）注册一个回调函数，该回调函数可以显示被MAC地址过滤掉的节点信息，参数parent为过滤的父节点,pDenied为被过滤掉的节点的信息，为结构体ZDE_JoinDenied_t组成的数组,count为被过滤掉的节点的个数。如果一个或多个节点都通过某一个父节点（协调器或者任意路由）入网，如果这些节点的MAC地址未有被预先录入父节点的白名单中，就会被父节点过滤掉，父节点会将过滤掉的这些节点的信息广播给其它路由节点和协调器，协调器可以通过向父节点白名单输入被允许入网的节点的MAC地址，父节点可以解除该节点的过滤拦截，准许其入网。

5，调用函数ZDE_WhiteListInput，可以把节点的MAC地址添加到本地白名单。函数ZDE_JoinAcceptReq则用于把白名单发送至其它路由节点，该命令支持广播发送，建议广播时使用0xFFFC，只对协调器和路由器广播。

6，强化了ZDO_STATE_CHANGE状态机功能，节点在入网失败，掉网后不能重新入网时，都会最终返回到DEV_INIT状态。应用层可以结合当前状态与上次状态，判断当前节点的情况。如果希望节点能在搜索不到网络时进入休眠模式，当前模式为DEV_INIT而上一次状态为DEV_NWK_DISC，说明节点未有搜索到可以加入的网络。应用层可以调用ZDApp_StopJoiningCycle停止下一次入网。调用ZDApp_StartJoiningCycle则可以唤醒下一次入网。

7，结构体说明：

设备过滤
typedef struct
{
  uint8 extAddr[Z_EXTADDR_LEN]; - 被过滤的MAC地址
  uint8 capability; - 被过滤的设备类型，见NLMEDE.h中的定义
  uint8 rejoin; - 是否为rejoin模式加入，可以忽略掉该字节
}ZDE_JoinDenied_t;

定义如下
#define CAPINFO_ALTPANCOORD           0x01
#define CAPINFO_DEVICETYPE_FFD        0x02
#define CAPINFO_DEVICETYPE_RFD        0x00
#define CAPINFO_POWER_AC              0x04
#define CAPINFO_RCVR_ON_IDLE          0x08
#define CAPINFO_SECURITY_CAPABLE      0x40
#define CAPINFO_ALLOC_ADDR            0x80


添加白名单
typedef struct
{
  sAddrExt_t  extAddrs; - 白名单的MAC地址
  uint8 life; - 该条白名单记录的超时时间，单位（秒），在该时间内，对应的设备才能加入网络
}ZDE_JoinAcceptReq_t;

