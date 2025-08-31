#ifndef __GIT__H
#define __GIT__H


//  �豸ʹ�����趨��
#define OLED 1			// �Ƿ�ʹ��OLED
#define NET_SERVE 1		// ƽ̨ѡ��
#define NETWORK_CHAEK 1 // �Ƿ������߼��
#define KEY_OPEN 1		// �Ƿ��������Ͷ̰����
#define USART2_OPEN 1	// �Ƿ�ʹ�ô��ڶ�

// ���ݶ���
typedef unsigned char U8;
typedef signed char S8;
typedef unsigned short U16;
typedef signed short S16;
typedef unsigned int U32;
typedef signed int S32;
typedef float F32;

//  C��
#include "cjson.h"
#include <string.h>
#include <stdio.h>
// ��Ƭ��ͷ�ļ�
#include "sys.h"
#include "usart.h"	 
// ����Э���
#include "Net.h"
// �����豸
#include "usart3.h"
// ������
#include "task.h"
#include "timer.h"
// Ӳ������
#include "delay.h"
#include "usart.h"
#include "git.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "flash.h"
#include "ds1302.h"
#include "sg90.h"
#include "usart2.h"
#include "net.h"
#include "dht11.h"
// �����ļ�
#include "max30102.h"
#include "heartiic.h"
#include "algorithm.h"

#include "MLX90614.h"

#if OLED // OLED�ļ�����
#include "oled.h"
#endif


// ��������Ϣ
#define SSID "NET"		// ·����SSID����
#define PASS "12345678" // ·��������
#if NET_SERVE == 0
// ��Э���������Onenet�ɰ�֧�֣�
#define ServerIP "183.230.40.39" // ������IP��ַ
#define ServerPort 6002			 // ������IP��ַ�˿ں�
#elif NET_SERVE == 1
// ����������ƽ̨��������֧�֣�
#define ServerIP "iot-06z00bhlj16tvj8.mqtt.iothub.aliyuncs.com" // ������IP��ַ
#define ServerPort 1883											// ������IP��ַ�˿ں�
#elif NET_SERVE == 2
// EMQXƽ̨��������
#define ServerIP "broker.emqx.io" // ������IP��ַ
#define ServerPort 1883			  // ������IP��ַ�˿ں�
#elif NET_SERVE == 3
// ��Ϊ��ƽ̨
#define ServerIP "4a33038a2b.st1.iotda-device.cn-north-4.myhuaweicloud.com" // ������IP��ַ
#define ServerPort 1883			  // ������IP��ַ�˿ں�
#endif
// �豸��Ϣ
#define PROID "smartdevice&k11q5zNEelo"															 // ��ƷID
#define DEVID "k11q5zNEelo.smartdevice|securemode=2,signmethod=hmacsha256,timestamp=1741864657515|" // �豸ID
#define AUTH_INFO "755f7e09aee2211d192edeed9d02acd8feb8f5257ee5553f7c77d5209096f541"						 // ��Ȩ��Ϣ
// MQTT���� /broadcast/
#define S_TOPIC_NAME "/broadcast/k11q5zNEelo/test1" // ��Ҫ���ĵ�����
#define P_TOPIC_NAME "/broadcast/k11q5zNEelo/test2" // ��Ҫ����������

#define P_TOPIC_CMD "/sys/k11q5zNEelo/smartdevice/thing/event/property/post"

// �Զ��岼������
typedef enum
{
	MY_TRUE,
	MY_FALSE
} myBool;

// �Զ���ִ�н������
typedef enum
{
	MY_SUCCESSFUL = 0x01, // �ɹ�
	MY_FAIL = 0x00		  // ʧ��

} mySta; // �ɹ���־λ

typedef enum
{
	OPEN = 0x01, // ��
	CLOSE = 0x00 // �ر�

} On_or_Off_TypeDef; // �ɹ���־λ

typedef enum
{
	DERVICE_SEND = 0x00, // �豸->ƽ̨
	PLATFORM_SEND = 0x01 // ƽ̨->�豸

} Send_directino; // ���ͷ���

typedef struct
{
	U8 App;			 // ָ��ģʽ
	U8 cmd;
	U8 Time;
	U8 Device_State; // ģʽ
	U8 Page;		 // ҳ��
	U8 Error_Time;
	U8 time_cut_page; // ҳ��
	
	F32 temperatuer; // �¶�
	U8 WENDU_H;		 // ���¸�λ
	U8 WENDU_L;		 // ���µ�λ
	
	F32 humiditr;	 // ʪ��
	U8 Flage;		 // ģʽѡ��
	U16 people;		 // ����
	U16 light;		 // ����
	U16 rain;		 // ���

} Data_TypeDef; // ���ݲ����ṹ��

typedef struct
{

	U16 somg_value; // ������ֵ
	U16 humi_value; // ʪ����ֵ
	U16 temp_value; // �¶���ֵ
	U16 Distance_value; // ������ֵ

} Threshold_Value_TypeDef; // ���ݲ����ṹ��

typedef struct
{
	U8 check_device; // ״̬
	U8 check_open;	 // ����Ƿ�������
	U8 Key_State;	 // �������

		
	U8 Alarm_time;
	U8 Alarm1_min;
	U8 Alarm2_min;
	U8 Alarm3_min;
	U8 Alarm4_min;
	
	U8 Alarm1_hour;
	U8 Alarm2_hour;
	U8 Alarm3_hour;
	U8 Alarm4_hour;
	
	U8 door1;
	U8 door2;
	U8 door3;
	
		
	U8 drug1;//ҩƷ
	U8 drug2;//ҩƷ
	U8 drug3;//ҩƷ
	U8 drug;//ҩƷ
	U8 check_time;// ���ʼ�����
	
} Device_Satte_Typedef; // ״̬�����ṹ��


// ȫ������
extern Data_TypeDef Data_init;
extern Device_Satte_Typedef device_state_init; // �豸״̬

extern Threshold_Value_TypeDef threshold_value_init; // �豸��ֵ���ýṹ��

// ��ȡ���ݲ���
mySta Read_Data(Data_TypeDef *Device_Data);
// ��ʼ��
mySta Reset_Threshole_Value(Threshold_Value_TypeDef *Value, Device_Satte_Typedef *device_state);
// ����OLED��ʾ��������
mySta Update_oled_massage(void);
// �����豸״̬
mySta Update_device_massage(void);
// ����json����
mySta massage_parse_json(char *message);
// ����
void Check_Key_ON_OFF(void);
// ��ʱ
void Automation_Close(void);
// ��������
mySta massage_speak(char *message);
#endif
