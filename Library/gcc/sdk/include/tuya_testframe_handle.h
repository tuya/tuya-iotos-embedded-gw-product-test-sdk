#ifndef _TUYA_TESTFRAME_HANDLE_H_
#define _TUYA_TESTFRAME_HANDLE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "tuya_prod_test.h"

#define TYPT_FRAME_DATA_MAX_LEN 1048
#define falseStr "{\"ret\":false}"
#define trueStr  "{\"ret\":true}"

/*
    次固件测试支持的类型
    zigbee wifi ble
*/
typedef enum {
    WT_ZIGBEE = 1,
    WT_WIFI = 2,
    WT_BLE = 3
}WIRELESS_TYPE;


//灯状态
typedef enum {
    TYPT_LED_ALL_ON = 0,
    TYPE_LED_ALL_OFF,
    TYPT_LED_FLASH
}TYPT_LED_STATE;

//扬声器的开关
typedef enum {
    TYPT_SOUND_OFF = 0,    
    TYPT_SOUND_ON
}TYPT_SOUND_STATE;

//lte测试步骤
typedef enum{
    TYPT_LTE_ENTER_TEST = 1,
    TYPT_LTE_EXIT_TEST,
    TYPT_LTE_TEST_MODE1,    
    TYPT_LTE_TEST_MODE2,
    TYPT_LTE_TEST_MODE3,
}TYPT_LTE_TEST;

//板载flag检测
typedef enum{
    TYPT_FLAG_WIFIRF = 0,    
    TYPT_FLAG_BOARDTEST = 1,
}TYPT_FLAG_TYPE;

//次固件升级类型
typedef enum {
    UG_ZIGBEE_IMAGE = 1,    
    UG_ZWAVE_IMAGE = 2,
    UG_BLE_IMAGE = 3,
    UG_MAX,
}UPGRADE_TYPE;

//CALLBACK
typedef void (*TYTEST_F_COMMON_VOID_HANDL)(void);
typedef int (*TYTEST_F_COMMON_HANDL)(void);
typedef int (*TYTEST_F_WR_HANDL)(char *buf);
typedef int (*TYTEST_F_W_CFG_HANDL)(char *auzkey, char *uuid, char *pid, int prodtest, char *ap_ssid, char *ap_pwd);
typedef int (*TYTEST_F_R_CFG_HANDL)(char *auzkey, char *uuid, char *pid, int *prodtest, char *ap_ssid, char *ap_pwd);
typedef int (*TYTEST_F_WR_SLAVEMAC_HANDL)(int cpunum,char *mac);
typedef int (*TYTEST_F_KEY_HANDL)(unsigned int *response_key_num);
typedef void (*TYTEST_F_LED_HANDL)(TYPT_LED_STATE state);
typedef int (*TYTEST_F_ZIGBEE_RF_HANDL)(int index,int channel, int num);
typedef int (*TYTEST_F_WIFIBLE_RF_HANDL)(char *ssid, int *rssi);
typedef int (*TYTEST_F_UG_SLAVE_HANDL)(UPGRADE_TYPE image_type);
typedef int (*TYTEST_F_UG_CFG_HANDL)(unsigned long baud, unsigned long crc32, unsigned long size);
typedef int (*TYTEST_F_UG_REV_HANDL)(char *data, unsigned int data_len);
typedef void (*TYTEST_F_SPEAKER_HANDL)(TYPT_SOUND_STATE state);
typedef int (*TYTEST_F_LTE_HANDL)(TYPT_LTE_TEST state);
typedef int (*TYTEST_F_R_CCID_HANDL)(char *ccid);
typedef int (*TYTEST_F_R_FLAGTYPE_HANDL)(TYPT_FLAG_TYPE type);
typedef int (*TYTEST_F_CUSTOMIZE_HANDL)(char *data, char *out_buf);
typedef int (*TYTEST_F_KEY_ASYNC_HANDL)(int index);


typedef struct {    
    TYTEST_F_COMMON_HANDL enter_prodtest_frame_cb;          //1.enter prodtest    
    TYTEST_F_COMMON_HANDL exit_prodtest_frame_cb;           //1.exit prodtest
    TYTEST_F_WR_HANDL master_firm_frame_cb;                 //2.master_firm
    TYTEST_F_WR_HANDL slave_firm_frame_cb;                  //3.slave firm
    TYTEST_F_W_CFG_HANDL w_cfg_frame_cb;                    //4.write cfd info
    TYTEST_F_R_CFG_HANDL r_cfg_frame_cb;                    //5.read cfg info
    TYTEST_F_WR_HANDL w_master_mac_frame_cb;                //6.write master mac
    TYTEST_F_WR_HANDL r_master_mac_frame_cb;                //7.read master mac
    TYTEST_F_WR_SLAVEMAC_HANDL w_slave_mac_frame_cb;        //8.write slave mac
    TYTEST_F_WR_SLAVEMAC_HANDL r_slave_mac_frame_cb;        //9.read slave mac
    TYTEST_F_WR_HANDL w_bsn_frame_cb;                       //10.write bsn
    TYTEST_F_WR_HANDL r_bsn_frame_cb;                       //11.read bsn
    TYTEST_F_WR_HANDL w_sn_frame_cb;                        //12.write sn
    TYTEST_F_WR_HANDL r_sn_frame_cb;                        //13.read sn
    TYTEST_F_WR_HANDL w_country_frame_cb;                   //14.write country
    TYTEST_F_WR_HANDL r_country_frame_cb;                   //15.read country
    TYTEST_F_KEY_HANDL key_frame_cb;                        //16.key test
    TYTEST_F_LED_HANDL led_frame_cb;                        //17.led test 
    TYTEST_F_ZIGBEE_RF_HANDL zigbee_rf_frame_cb;            //18.zigbee wifi ble rf test  
    TYTEST_F_WIFIBLE_RF_HANDL wifi_rf_frame_cb;    
    TYTEST_F_WIFIBLE_RF_HANDL ble_rf_frame_cb;
    TYTEST_F_UG_SLAVE_HANDL upgrade_slave_frame_cb;         //19.slave upgrade      
    TYTEST_F_UG_CFG_HANDL upgrade_cfg_frame_cb;             //20.upgrade cfg   
    TYTEST_F_COMMON_HANDL upgrade_start_frame_cb;           //21.upgrade start    
    TYTEST_F_UG_REV_HANDL upgrade_rev_packet_frame_cb;      //22.upgrade receive     
    TYTEST_F_COMMON_HANDL upgrade_end_frame_cb;             //23.upgrade end   
    TYTEST_F_COMMON_VOID_HANDL reboot_frame_cb;             //24.reboot
    TYTEST_F_SPEAKER_HANDL speaker_frame_cb;                //25.speaker
    TYTEST_F_LTE_HANDL lte_test_frame_cb;                   //26.lte test
    TYTEST_F_R_CCID_HANDL r_ccid_frame_cb;                  //27.read ccid
    TYTEST_F_R_FLAGTYPE_HANDL flag_dect_frame_cb;           //28.flag dectect
    TYTEST_F_CUSTOMIZE_HANDL customize_frame_cb;            //29.customize handle    
    TYTEST_F_KEY_ASYNC_HANDL key_async_frame_cb;            //30.key test
}TYTEST_FRAME_CBS_S;

//产测帧处理主控制结构体
typedef struct tuya_test_frame_handler{
	int register_status;
    TYTEST_FRAME_CBS_S cbs;
}TYTEST_FRAME_HANDLER;

//function
int tuya_testframe_rep_key_event(int index, unsigned int key_num);
int tuya_testframe_rep_zigbeeRf_event(int index, unsigned int receive_num);
void tuya_testframe_set_tcp_port(int tcp_port);
int tuya_testframe_handle_init(TUYA_PRODTEST_MODE mode, TYTEST_FRAME_CBS_S *cbs);
int tuya_testframe_handle_deinit();


#ifdef __cplusplus
}
#endif

#endif

