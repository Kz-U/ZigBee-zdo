z-stack�汾��2.6.1

�Ż�����ص㣺
1�����ж��Э��������Ļ����У�ֻ��Ҫ��Э�����������Ӧ�ڵ��MAC��ַ���ڵ���ܼ��뵽��Э�����������У����öԽڵ�����κ����ã��ڵ���Ҳ����Ҫ���κ����ýӿڣ��������ӡ������ڵ�һ��Ϊ�ڵ���д����ʱ���Ͱѽڵ��MAC��ַ����������ӡ�����룬Ȼ��ͨ������Э������λ���������ȡ�豸����������

2��Ӧ�ò�����жϽڵ㵱ǰ�Ƿ�����Zigbee����ķ�Χ�ڣ��Ƿ�������Ƿ��޷������ȶ����쳣������ڵ�����ڲ�������������½���͹��ġ�ԭ��z-stack��ԭ���ǡ��ڵ�������һ�����磬�������������δ����֤�������Ż����Э�飬���ǡ�δ����֤��Э���������ܼ��������硱

3���ڵ���к��������ܣ��ܹ���δ����֤��Э����PANID¼�뵽�������С�

ʹ�÷�����
1��ɾ��ԭZ-stack�е�zdo�ļ��У����ô��ļ����滻ԭ�����ļ��С�

2��ԭ������workspace�У�ɾ��ZDO��Ŀ���������ݣ����Ѹ��ļ����������ļ��ϵ�ԭZDO��Ŀ�¡�

3�������Ҫʹ��MAC��ַ���ˣ���ԭ���̵�tasksArr�У�����ZDE_event_loop��������osalInitTasks������ZDE_Init��

4�����ú���ZDE_RegisterJoinDeniedCB��λ��ZDEnhanced.h�У�ע��һ���ص��������ûص�����������ʾ��MAC��ַ���˵��Ľڵ���Ϣ������parentΪ���˵ĸ��ڵ�,pDeniedΪ�����˵��Ľڵ����Ϣ��Ϊ�ṹ��ZDE_JoinDenied_t��ɵ�����,countΪ�����˵��Ľڵ�ĸ��������һ�������ڵ㶼ͨ��ĳһ�����ڵ㣨Э������������·�ɣ������������Щ�ڵ��MAC��ַδ�б�Ԥ��¼�븸�ڵ�İ������У��ͻᱻ���ڵ���˵������ڵ�Ὣ���˵�����Щ�ڵ����Ϣ�㲥������·�ɽڵ��Э������Э��������ͨ���򸸽ڵ���������뱻���������Ľڵ��MAC��ַ�����ڵ���Խ���ýڵ�Ĺ������أ�׼����������

5�����ú���ZDE_WhiteListInput�����԰ѽڵ��MAC��ַ���ӵ����ذ�����������ZDE_JoinAcceptReq�����ڰѰ���������������·�ɽڵ㣬������֧�ֹ㲥���ͣ�����㲥ʱʹ��0xFFFC��ֻ��Э������·�����㲥��

6��ǿ����ZDO_STATE_CHANGE״̬�����ܣ��ڵ�������ʧ�ܣ�����������������ʱ���������շ��ص�DEV_INIT״̬��Ӧ�ò���Խ�ϵ�ǰ״̬���ϴ�״̬���жϵ�ǰ�ڵ����������ϣ���ڵ�����������������ʱ��������ģʽ����ǰģʽΪDEV_INIT����һ��״̬ΪDEV_NWK_DISC��˵���ڵ�δ�����������Լ�������硣Ӧ�ò���Ե���ZDApp_StopJoiningCycleֹͣ��һ������������ZDApp_StartJoiningCycle����Ի�����һ��������

7���ṹ��˵����

�豸����
typedef struct
{
  uint8 extAddr[Z_EXTADDR_LEN]; - �����˵�MAC��ַ
  uint8 capability; - �����˵��豸���ͣ���NLMEDE.h�еĶ���
  uint8 rejoin; - �Ƿ�Ϊrejoinģʽ���룬���Ժ��Ե����ֽ�
}ZDE_JoinDenied_t;

��������
#define CAPINFO_ALTPANCOORD           0x01
#define CAPINFO_DEVICETYPE_FFD        0x02
#define CAPINFO_DEVICETYPE_RFD        0x00
#define CAPINFO_POWER_AC              0x04
#define CAPINFO_RCVR_ON_IDLE          0x08
#define CAPINFO_SECURITY_CAPABLE      0x40
#define CAPINFO_ALLOC_ADDR            0x80


���Ӱ�����
typedef struct
{
  sAddrExt_t  extAddrs; - ��������MAC��ַ
  uint8 life; - ������������¼�ĳ�ʱʱ�䣬��λ���룩���ڸ�ʱ���ڣ���Ӧ���豸���ܼ�������
}ZDE_JoinAcceptReq_t;
