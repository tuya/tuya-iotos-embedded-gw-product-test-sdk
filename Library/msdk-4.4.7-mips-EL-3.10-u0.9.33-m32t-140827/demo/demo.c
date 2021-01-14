#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "tuya_testframe_handle.h"

//线程创建接口
static int creat_thread_and_start(pthread_t *thrid, thread_process thr_process, void *args)
{
    int opRet = 0;
    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    opRet = pthread_create(thrid,&attr, thr_process, args);
    pthread_attr_destroy(&attr);
    if(opRet != 0)
    {
        TYPD_ERR("Create Thread Fails %d", opRet);
        return -1;
    }  
    return 0;
}

//线程销毁
static int cancel_thread(pthread_t thrid)
{
#ifdef __ANDROID__
    //NOTE:
    //安卓不支持 pthread_cancel
    //如果被其他线程退出，安卓版本该接口暂不支持
    pthread_exit((void*)thrid);
    return 0;
#else
    return pthread_cancel(thrid);
#endif
}

/*进入产测模式*/
static int tuya_prod_enter(void)
{
    printf("enter prodtest\n");
    return 0;
}

/*退出产测模式*/
static int tuya_prod_exit(void)
{
    printf("exit prodtest\n");
    return 0;
}

/*读取主固件版本信息*/
static int tuya_prod_r_master_firmware_info(char *out_buf)
{
    if(out_buf == NULL)
        return -1;
    sprintf(out_buf,"{\"ret\":true,\"firmName\":\"home_security_gw\",\"firmVer\":\"1.2.3\"}");
    return 0;
    
}

/*读取次固件版本信息*/
static int tuya_prod_r_slave_firmware_info(char *out_buf)
{
    if(out_buf == NULL)
        return -1;
    sprintf(out_buf,"{\"ret\":true,\"firmName\":\"z3_ncp_firmware\",\"firmVer\":\"1.0.6\"}");
    return 0;
}

/*写入配置信息*/
static int tuya_prod_w_auth_info(char *auzkey, char *uuid, char *pid, int prodtest, char *ap_ssid, char *ap_pwd)
{
    printf("auzkey:%s  uuid:%s prodtest:%d\n",auzkey,uuid,prodtest);
    if(pid)        
        printf("pid:%s\n",pid);
    if(ap_ssid)        
        printf("apssid:%s\n",ap_ssid);
    if(ap_pwd)        
        printf("appwd:%s\n",ap_pwd);

    return 0;
}

/*读取配置信息*/
static int tuya_prod_r_auth_info(char *auzkey, char *uuid, char *pid, int *prodtest, char *ap_ssid, char *ap_pwd)
{
    sprintf(auzkey,"U4Ri3GGd6VOR255oumyfgLPbJ8ITtH8W");    
    sprintf(uuid,"bc85a0edd3458fce");
    //sprintf(pid,"kjkjkjkjsasa");
    *prodtest = 0;    
    //sprintf(ap_ssid,"smartlife-0009");    
    //sprintf(ap_pwd,"buzhidao");
    return 0;        
}

/*写入主mac地址*/
static int tuya_prod_w_master_mac(char *mac)
{
    printf("master mac is:%s\n",mac);
    return 0;
}

/*读取主mac地址*/
static int tuya_prod_r_master_mac(char *mac)
{
    sprintf(mac,"080027a2b63c");
    return 0;    
}

/*写入次mac地址*/
static int tuya_prod_w_slave_mac(int cpunum,char *mac)
{
    printf("slave mac%d is:%s\n",cpunum,mac);
    return 0;
}

/*读取次mac地址*/
static int tuya_prod_r_slave_mac(int cpunum,char *mac)
{
    printf("read cpunum %d\n",cpunum);
    sprintf(mac,"080027a2b64d");
    return 0;    
}

/*写入bsn*/
static int tuya_prod_w_bsn(char *bsn)
{
    printf("bsn is:%s\n",bsn);
    return 0;
}

/*读取bsn*/
static int tuya_prod_r_bsn(char *bsn)
{
    sprintf(bsn,"bsn1234567");
    return 0;    
}

/*写入sn*/
static int tuya_prod_w_sn(char *sn)
{
    printf("sn is:%s\n",sn);
    return 0;
}

/*读取sn*/
static int tuya_prod_r_sn(char *sn)
{
    sprintf(sn,"sn12345678");
    return 0;    
}

/*写入国家码*/
static int tuya_prod_w_country_code(char *country_code)
{
    printf("country_code is:%s\n",country_code);
    return 0;
}

/*读取国家码*/
static int tuya_prod_r_country_code(char *country_code)
{
    sprintf(country_code,"CN");
    return 0;    
}

/*
    led测试：亮 灭 闪烁
*/
void tuya_prod_ledtest(TYPT_LED_STATE state)
{
    printf("led blink\n");
}

/*
    按键测试
    函数说明：返回值为按键测试成功的个数，可阻塞，比如板子上有两个按键，
              如果测试两个按键都没有问题，*response_key_num = 2即可
*/
static int tuya_prod_keytest(unsigned int *response_key_num)
{
    *response_key_num = 2;
    return 0;
}

static int zb_index[1024] = {0};
static void* tuya_prod_zbrf_thread_process(void *pArg)
{
    int *index = (int*)pArg;
    sleep(5);

    TYPD_DEBUG("*****************************ZBRF INDEX:%d\n",*index);
    tuya_testframe_rep_zigbeeRf_event(*index,100);
    
    return (void*)0;
}


/*
    zigbee rf测试
    函数说明：异步上报；入参为index（异步上报需要用到，和上报用到的index一一对应，是同一个值），信道，发包的个数，出参为收到的报文个数
*/
static int tuya_prod_zigbee_rf_test(int index, int channel, int num)
{
    printf("index:%d ,zigbee rf test:channel %d,num:%d",index,channel, num);    
    //thread 
	pthread_t pt_thr;
	int ret = 0;

    zb_index[index] = index;
	
	ret = creat_thread_and_start(&pt_thr,tuya_prod_zbrf_thread_process,(void*)(&zb_index[index]));
    if(0 != ret)
    {
        TYPD_ERR("start tuya_prod_key_thread_process fails %d", ret);
        return -1;
    }
    return 0;
}

/*
    wifi rf测试
    函数说明：可阻塞；入参为ssid，出参为该ssid的信号强度
*/
static int tuya_prod_wifi_rf_test(char *ssid, int *rssi)
{
    printf("wifi rf test:%s\n",ssid);
    *rssi = -30;
    return 0;
}

/*
    ble rf测试
    函数说明：可阻塞；入参为ssid，出参为该ssid的信号强度
*/
static int tuya_prod_ble_rf_test(char *ssid, int *rssi)
{
    printf("ble rf test:%s\n",ssid);
    *rssi = -20;
    return 0;
}

/*
    扬声器测试：开，关
*/
static void tuya_prod_speaker_test(TYPT_SOUND_STATE state)
{
    printf("speaker test!\n");
}

/*
    lte测试
    函数说明：入参为lte测试模式的进入，退出，及三个频段测试模式，用户要根据当前传进来的模式做具体的方案实施
*/
static int tuya_prod_lte_test(TYPT_LTE_TEST state)
{
    printf("lte test:%d\n",state);
    return 0;
}

/*
    板载flag测试：目前只有rokidk18平台用到
*/
static int tuya_prod_r_flagtype(TYPT_FLAG_TYPE type)
{
    printf("%d flagtype read",type);
    return 0;
}

/*重启系统*/
static void tuya_prod_reboot(void)
{
    printf("reboot now!\n");
}

/*
    自定义产测协议接口
    函数说明：入参为产测帧的data字段，用户需要自行解析；
              返回给上位机的产测帧的data部分放到out_buf中
*/
static int tuya_prod_customize(char *data, char *out_buf)
{    
    if(data)    
        printf("data is %s\n",data);
    sprintf(out_buf,"customize handle");
    return 0;
}

/*读取ccid*/
static int tuya_prod_r_ccid(char *ccid)
{   
    printf("read ccid\n");    
    sprintf(ccid,"123456789012345678");
    return 0;
}

/*选择进行次固件产测升级*/
static int tuya_prod_upgrade_slaveimg_cfg(UPGRADE_TYPE image_type)
{
    printf("upgrade slave:%d\n",image_type);
    return 0;
}

/*产测升级配置：入参：串口波特率，固件crc32校验，固件大小*/
static int tuya_prod_upgrade_cfg(unsigned long baud, unsigned long crc32, unsigned long size)
{
    printf("upgrade cfg:%lul %lul %lul\n",baud, crc32, size);
    return 0;
}

/*产测升级开始*/
static int tuya_prod_upgrade_start(void)
{
    printf("upgrade start\n");
    return 0;
}

/*产测升级接受数据*/
static int tuya_prod_upgrade_rev(char *data, unsigned int data_len)
{    
    printf("upgrade receive data len:%d\n",data_len);
    return 0;
}

/*产测升级结束*/
static int tuya_prod_upgrade_end(void)
{    
    printf("upgrade end\n");
    return 0;
}

static int key_index[1024] = {0};
static void* tuya_prod_key_thread_process(void *pArg)
{
    int *index = (int*)pArg;
    sleep(5);
    
    TYPD_DEBUG("*****************************KEY INDEX:%d\n",*index);
    tuya_testframe_rep_key_event(*index,3);    

    return (void*)0;
}

/*
    按键测试异步
    函数说明：入参为index（异步上报需要用到，和上报用到的index一一对应，是同一个值）
*/
static int tuya_prod_key_async_test(int index)
{
    //thread 
	pthread_t pt_thr;
	int ret = 0;
    static int sindex[1024] = {0};
    
    key_index[index] = index;
	
	ret = creat_thread_and_start(&pt_thr,tuya_prod_key_thread_process,(void*)(&key_index[index]));
    if(0 != ret)
    {
        TYPD_ERR("start tuya_prod_key_thread_process fails %d", ret);
        return -1;
    }
    return 0;
}

/*
    老化测试检测，返回0 说明进行过老化测试，-1说明没有
*/
static int tuya_prod_ageing_test()
{
    return 0;
}

int main()
{
    TYTEST_FRAME_CBS_S prodframe_cbs = {
        .enter_prodtest_frame_cb = tuya_prod_enter,                            //1.enter prodtest    
        .exit_prodtest_frame_cb = tuya_prod_exit,                             //1.exit prodtest
        .master_firm_frame_cb = tuya_prod_r_master_firmware_info,           //2.master_firm
        .slave_firm_frame_cb = tuya_prod_r_slave_firmware_info,            //3.slave firm
        .w_cfg_frame_cb = tuya_prod_w_auth_info,                      //4.write cfd info
        .r_cfg_frame_cb = tuya_prod_r_auth_info,                      //5.read cfg info
        .w_master_mac_frame_cb = tuya_prod_w_master_mac,                     //6.write master mac
        .r_master_mac_frame_cb = tuya_prod_r_master_mac,                     //7.read master mac
        .w_slave_mac_frame_cb = tuya_prod_w_slave_mac,                      //8.write slave mac
        .r_slave_mac_frame_cb = tuya_prod_r_slave_mac,                      //9.read slave mac
        .w_bsn_frame_cb = tuya_prod_w_bsn,                            //10.write bsn
        .r_bsn_frame_cb = tuya_prod_r_bsn,                            //11.read bsn
        .w_sn_frame_cb = tuya_prod_w_sn,                             //12.write sn
        .r_sn_frame_cb = tuya_prod_r_sn,                             //13.read sn
        .w_country_frame_cb = tuya_prod_w_country_code,                   //14.write country
        .r_country_frame_cb = tuya_prod_r_country_code,                   //15.read country
        .key_frame_cb = tuya_prod_keytest,                          //16.key test
        .led_frame_cb = tuya_prod_ledtest,                          //17.led test 
        .zigbee_rf_frame_cb = tuya_prod_zigbee_rf_test,                   //18.zigbee wifi ble rf test  
        .wifi_rf_frame_cb = tuya_prod_wifi_rf_test,
        .ble_rf_frame_cb = tuya_prod_ble_rf_test,
        .upgrade_slave_frame_cb = tuya_prod_upgrade_slaveimg_cfg,             //19.slave upgrade      
        .upgrade_cfg_frame_cb = tuya_prod_upgrade_cfg,                      //20.upgrade cfg   
        .upgrade_start_frame_cb = tuya_prod_upgrade_start,                    //21.upgrade start    
        .upgrade_rev_packet_frame_cb = tuya_prod_upgrade_rev,                      //22.upgrade receive     
        .upgrade_end_frame_cb = tuya_prod_upgrade_end,                      //23.upgrade end   
        .reboot_frame_cb = tuya_prod_reboot,                           //24.reboot
        .speaker_frame_cb = tuya_prod_speaker_test,                     //25.speaker
        .lte_test_frame_cb = tuya_prod_lte_test,                         //26.lte test
        .r_ccid_frame_cb = tuya_prod_r_ccid,                            //27.read ccid
        .flag_dect_frame_cb = tuya_prod_r_flagtype,                       //28.flag dectect
        .customize_frame_cb = tuya_prod_customize,                        //29.customize handle
        .key_async_frame_cb = tuya_prod_key_async_test,
        .ageing_test_frame_cb = tuya_prod_ageing_test,         //31.ageing test
    };

	int ret;

	//如果不调用此接口设置端口号 端口号默认是12130
	//tuya_testframe_set_tcp_port(12131);
	
	ret = tuya_testframe_handle_init(TPM_TCP,&prodframe_cbs);
	if(ret < 0) {
	    printf("tuya_testframe_handle_init failed\n");
	    return -1;
	}
    	
	while(1) {
		sleep(1000);
	}
	return 0;
}

