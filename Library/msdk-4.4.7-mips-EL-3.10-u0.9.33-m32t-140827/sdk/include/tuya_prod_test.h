#ifndef _TUYA_PROD_TEST_H_
#define _TUYA_PROD_TEST_H_


#ifdef __cplusplus
extern "C"
{
#endif
#include <stdio.h>
#include <stdbool.h>

//log
#define MAX_LOG_LEN 1024

int log_print(const char *flag_str, char *file, const char *func, unsigned int line, char *fmt, ...);


//#define TYPD_DEBUG(fmt, ...)  printf("PT DEBUG:[%s:%s:%d] "fmt"\r\n", __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
//#define TYPD_ERR(fmt, ...)  printf("PT ERR:[%s:%s:%d] "fmt"\r\n", __FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#define TYPD_DEBUG(fmt, ...)  log_print("PT DEBUG", __FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)
#define TYPD_ERR(fmt, ...)  log_print("PT ERR", __FILE__,__FUNCTION__,__LINE__,fmt,##__VA_ARGS__)


#define TYPD_LOG_PUT(a) printf("%s\r\n",a);

/**************************----define----*************************************/
//协议版本号
#define TUYA_PROD_PROTOCOL "1.0.0"
//sdk版本号
#define TUYA_PROD_SDK_VERSION "1.0.1"


//UDP PORT
#define TUYA_TEST_RECV_PORT 12130

//tuya产测帧长度 根据具体需求自定义
#define TUYA_FRAME_MIN_LEN 7
#define TUYA_FRAME_MAX_LEN 1048

#define IPADDR_TUYATEST_RCVE       ((unsigned int)0x00000000UL)

#define falseFrameResultStr "{\"ret\":false}"
#define trueFrameResultStr  "{\"ret\":true}"

//支持的按键数量
#define TYPT_MAX_KEY 100

/**************************----tcpser----*************************************/
//限制连接上位机为24
#define TYT_CLIENT_LMT 24 
typedef enum {
    TTSS_INIT = 0,
    TTSS_CR_SERV,
    TTSS_SELECT,
}TUYATEST_TCP_SERV_STAT_E;

typedef struct tuyatest_recv_buffer {
    unsigned char *r_buffer[TYT_CLIENT_LMT];
    int r_soc[TYT_CLIENT_LMT];          //接受buffer对应的套接字
    unsigned int handle_cnt;        //当前需要处理套接字的个数
    unsigned int current_handle_index; //当前处理的套接字对应数组中的索引
    unsigned int sum;               //等同于CLIENT_LMT
    int has_malloc;              //表示已经为r_buffer分配了内存
}TUYATEST_R_BUFFER;

//套接字管理结构
typedef struct client_soc_manage
{
    int ser_fd;
    int accep_soc_num;    
    int accep_soc[TYT_CLIENT_LMT];
    int has_recv_buffer[TYT_CLIENT_LMT];
}CLI_SOC_MANAGE;

/**************************----frame----*************************************/
typedef struct tuya_test_frame{
    unsigned char head[2];
    unsigned char version[1];
    unsigned char command[1];
    unsigned char data_len[2];
    unsigned char *data;
    unsigned char check_sum[1];
    unsigned int data_len_uint; //产测帧数据部分长度
    unsigned char *frame_buffer;//指向的buffer含有帧的所有数据，最后要释放掉
}TuyaTestFrame;

typedef enum
{
    TUYATEST_MODE = 0x00,
    TUYATEST_R_MASTER_FIRMWARE = 0x01,
    TUYATEST_R_SLAVE_FIRMWARE = 0x02,
    TUYATEST_W_CFGINFO = 0x03,
    TUYATEST_R_CFGINFO = 0x04,
    TUYATEST_W_MASTER_MAC = 0x05,
    TUYATEST_R_MASTER_MAC = 0x06,
    TUYATEST_W_SLAVE_MAC = 0x07,
    TUYATEST_R_SLAVE_MAC = 0x08,
    TUYATEST_SELF_TEST = 0x09,
    TUYATEST_BUTTON_TEST = 0x0a,
    TUYATEST_LED_TEST = 0x0b,    
    TUYATEST_W_BSN = 0x0c,
    TUYATEST_R_BSN = 0x0d,
    TUYATEST_W_SN = 0x0e,
    TUYATEST_R_SN = 0x0f,
    TUYATEST_MASTER_CAP = 0x10,
    TUYATEST_SLAVE_CAP = 0x11,    
    TUYATEST_SPEAKER = 0x15,      
    TUYATEST_W_COUNTRY = 0x1C, 
    TUYATEST_R_COUNTRY = 0x1D,
    TUYATEST_UPGRADE_CFG = 0x1e,
    TUYATEST_UPGRADE_START = 0x1f,
    TUYATEST_UPGRADEING = 0x20,
    TUYATEST_UPGRADE_END = 0x21,
    TUYATEST_GW_REBOOT = 0x22,    
    TUYATEST_SLAVE_UPGRADE = 0x23,        
    TUYATEST_LTE_TEST = 0x29,
    TUYATEST_FLAG_DECTECT = 0x2A,
    TUYATEST_LTE_READ_CCID = 0x2B,    
    TUYATEST_AGEING_TEST = 0x33,
} TUYATEST_CMD;

//传输数据的方式 目前支持tcp，可扩展
typedef enum
{
    TPM_TCP = 0,
    TPM_SERIAL,
    TPM_MAX
} TUYA_PRODTEST_MODE;

//产测线程运行状态
typedef enum
{
    TEST_THD_NORMAL = 1,
    TEST_THD_EXIT
} TUYA_TEST_THREAD_STATE;

/**************************----callback----*************************************/
typedef TuyaTestFrame * (*TUYA_GET_FRAME)(int buffer_index);
typedef void (*TUYA_PUT_FRAME)(unsigned char cmd,unsigned char *data);
typedef void (*TUYA_FREE_FRAME)(TuyaTestFrame *frame);
typedef void *(*thread_process)(void *pArg);

typedef struct tuya_frame_handler{
    TUYA_GET_FRAME tuya_get_frame;
    TUYA_PUT_FRAME tuya_put_frame;
    TUYA_FREE_FRAME tuya_free_frame;    
 }TF_HANDLER;

typedef int (*TYTEST_COMMON_HANDL)(TuyaTestFrame *frame, char *out_buf);
typedef int (*TYTEST_COMMON_ASYNC_HANDL)(int index,TuyaTestFrame *frame, char *out_buf);
typedef int (*TYTEST_COMMON_HANDL_NOBUF)(TuyaTestFrame *frame);
typedef int (*TYTEST_KEY_HANDL)(TuyaTestFrame *frame ,unsigned int *response_key_num);
typedef int (*TYTEST_KEY_ASYNC_HANDL)(TuyaTestFrame *frame ,int index);
typedef void (*TYTEST_CUSTOMIZE_HANDL)(TuyaTestFrame *frame, char *out_buf);
typedef void (*TYTEST_REBOOT_HANDL)(TuyaTestFrame *frame);

typedef struct {    
    TYTEST_COMMON_HANDL enter_prodtest_cb;              //1.enter prodtest
    TYTEST_COMMON_HANDL master_firm_cb;                 //2.master_firm
    TYTEST_COMMON_HANDL slave_firm_cb;                  //3.slave firm
    TYTEST_COMMON_HANDL_NOBUF w_cfg_cb;                 //4.write cfd info
    TYTEST_COMMON_HANDL r_cfg_cb;                       //5.read cfg info
    TYTEST_COMMON_HANDL_NOBUF w_master_mac_cb;          //6.write master mac
    TYTEST_COMMON_HANDL r_master_mac_cb;                //7.read master mac
    TYTEST_COMMON_HANDL_NOBUF w_slave_mac_cb;           //8.write slave mac
    TYTEST_COMMON_HANDL r_slave_mac_cb;                 //9.read slave mac
    TYTEST_COMMON_HANDL_NOBUF w_bsn_cb;                 //10.write bsn
    TYTEST_COMMON_HANDL r_bsn_cb;                       //11.read bsn
    TYTEST_COMMON_HANDL_NOBUF w_sn_cb;                  //12.write sn
    TYTEST_COMMON_HANDL r_sn_cb;                        //13.read sn
    TYTEST_COMMON_HANDL_NOBUF w_country_cb;             //14.write country
    TYTEST_COMMON_HANDL r_country_cb;                   //15.read country
    TYTEST_KEY_HANDL key_cb;                            //16.key test
    TYTEST_COMMON_HANDL_NOBUF led_cb;                   //17.led test   
    TYTEST_COMMON_ASYNC_HANDL slave_cap_cb;                   //18.slave cap test      
    TYTEST_COMMON_HANDL_NOBUF upgrade_slave_cb;         //19.slave upgrade      
    TYTEST_COMMON_HANDL_NOBUF upgrade_cfg_cb;           //20.upgrade cfg   
    TYTEST_COMMON_HANDL_NOBUF upgrade_start_cb;         //21.upgrade start    
    TYTEST_COMMON_HANDL_NOBUF upgrade_rev_packet_cb;    //22.upgrade receive     
    TYTEST_COMMON_HANDL_NOBUF upgrade_end_cb;           //23.upgrade end   
    TYTEST_REBOOT_HANDL reboot_cb;                      //24.reboot
    TYTEST_COMMON_HANDL_NOBUF speaker_cb;               //25.speaker
    TYTEST_COMMON_HANDL lte_test_cb;                    //26.lte test
    TYTEST_COMMON_HANDL r_ccid_cb;                      //27.read ccid
    TYTEST_COMMON_HANDL flag_dect_cb;                   //28.flag dectect
    TYTEST_CUSTOMIZE_HANDL customize_db;                //29.customize handle    
    TYTEST_KEY_ASYNC_HANDL key_async_cb;                //30.key test async rep
    TYTEST_COMMON_HANDL_NOBUF ageing_test_cb;           //31.ageing test
}TUYA_TEST_CBS_S;

//产测主控制结构体
typedef struct tuya_prodtest_handler{
    int prod_start_flag;
	TUYA_PRODTEST_MODE trans_mode;
	int tcp_port;
    TUYA_TEST_THREAD_STATE thd_run_state;
	TF_HANDLER frame_handle; 
    TUYA_TEST_CBS_S cbs;    
}TP_HANDLER;

//function
int tuya_prodtest_rep_key_event(int index, unsigned int key_num);
int tuya_prodtest_rep_zigbeeRf_event(int index, unsigned int receive_num);
void tuya_prodtest_set_tcp_port(int tcp_port);
void tuya_prodtest_set_start_flag(bool status);
int tuya_prodtest_init(TUYA_PRODTEST_MODE mode, TUYA_TEST_CBS_S *cbs);
int tuya_prodtest_deinit();


#ifdef __cplusplus
}
#endif

#endif

