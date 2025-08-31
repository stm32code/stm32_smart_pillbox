// �����豸
#include "usart3.h"
#include "led.h"
// Э���ļ�
#include "GA10.h"
#include "mqttkit.h"
#include "delay.h"
// Ӳ������
#include "usart.h"
#include "flash.h"
//  C��
#include <string.h>
#include <stdio.h>
extern Device_Satte_Typedef device_state_init;		 // �豸״̬
extern Threshold_Value_TypeDef threshold_value_init; // �豸��ֵ���ýṹ��
extern unsigned char esp8266_buf[256];
//==========================================================
//	�������ܣ�	ʹ��GA10����Ϣ
//==========================================================
void GA10_SendData(unsigned char *data, unsigned short len)
{
	ESP8266_Clear();			  // ��ս��ջ���
	Usart3_SendString(data, len); // �����豸������������
}
//==========================================================
//	�������ܣ�	��GA6��ָ��
//==========================================================
_Bool GA10_SendCmd(char *cmd, char *res, u16 time)
{
	char str[256];
	sprintf(str, "%s\r\n", cmd);
	// printf("%s",str);
	Usart3_SendString((unsigned char *)str, strlen((const char *)str));

	while (time--)
	{
		if (ESP8266_WaitRecive() == REV_OK) // ����յ�����
		{
			//printf("%s\n", esp8266_buf);
			if (strstr((const char *)esp8266_buf, res) != NULL) // ����������ؼ���
			{
				ESP8266_Clear(); // ��ջ���
				return 0;
			}
		}
		delay_ms(10);
	}
	return 1;
}
//==========================================================
//	�������ܣ�	��ʼ��GA10
//==========================================================
void GA10_Init(void)
{
	char str[125];
	delay_ms(250);

	ESP8266_Clear();

	printf("����ͨ���Ƿ�ɹ�... ...\r\n"); // ���������Ϣ

	while (GA10_SendCmd("AT", "OK", 500))
		delay_ms(300);

	printf("������������.. ...\r\n"); // ���������Ϣ

	memset(str, 0, sizeof(str));
	sprintf(str, "AT+MTCFG=\"cloud\",0,2,1");
	while (GA10_SendCmd(str, "OK", 500))
		delay_ms(300);

	printf("�������Ӳ���... ...\r\n"); // ���������Ϣ

	memset(str, 0, sizeof(str));
	sprintf(str, "AT+MTCFG=\"aliauth\",0,\"%s\",\"%s\",\"%s\"", PROID, DEVID,AUTH_INFO);
	while (GA10_SendCmd(str, "OK", 500))
		delay_ms(300);

	printf("���ӷ�����\r\n");

	memset(str, 0, sizeof(str));
	sprintf(str, "AT+MTOPEN=0,\"%s\",%d", ServerIP, ServerPort);
	while (GA10_SendCmd(str, "OK", 500))
		delay_ms(300);
	
	printf("�����豸\r\n");

	memset(str, 0, sizeof(str));
	sprintf(str, "AT+MTCONN=0,\"aliauth\" ");
	while (GA10_SendCmd(str, "OK", 500))
		delay_ms(300);
	
	printf("��������\r\n");

	memset(str, 0, sizeof(str));
	sprintf(str, "AT+MTSUB=0,1,\"%s\",0",S_TOPIC_NAME);
	while (GA10_SendCmd(str, "OK", 500))
		delay_ms(300);

	printf("GA10 OK\r\n");
	// Sys_Restart();//�����λ
}
//==========================================================
//	�������ܣ�	������Ϣ
//==========================================================

extern int32_t n_sp02;		 // SPO2 value
extern int8_t ch_spo2_valid; // indicator to show if the SP02 calculation is valid
extern int32_t n_heart_rate; // heart rate value
extern int8_t ch_hr_valid;	 // indicator to show if the heart rate calculation is valid
unsigned char FillBuf(char *buf)
{
	char text[256];
	memset(text, 0, sizeof(text));

	strcpy(buf, "{");
	if(20 < n_heart_rate && n_heart_rate < 150 && ch_spo2_valid){
		memset(text, 0, sizeof(text));
		sprintf(text, "\"heart\":\"%d\",", n_heart_rate); // Temp����������һ�����ƣ�temper���¶�ֵ
		strcat(buf, text);
		memset(text, 0, sizeof(text));
		sprintf(text, "\"blood\":\"%d\",", n_sp02); // Temp����������һ�����ƣ�temper���¶�ֵ
		strcat(buf, text);
	}
	if( Data_init.WENDU_H < 50){
		memset(text, 0, sizeof(text));
		sprintf(text, "\"temp\":\"%02d.%02d\",", Data_init.WENDU_H,	Data_init.WENDU_L); // Temp����������һ�����ƣ�temper���¶�ֵ
		strcat(buf, text);
	}
	memset(text, 0, sizeof(text));
	sprintf(text, "\"drug1_s\":\"%d\",", device_state_init.door1); // Temp����������һ�����ƣ�temper���¶�ֵ
	strcat(buf, text);

	memset(text, 0, sizeof(text));
	sprintf(text, "\"drug2_s\":\"%d\",", device_state_init.door2); // Temp����������һ�����ƣ�temper���¶�ֵ
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"drug3_s\":\"%d\",", device_state_init.door3); // Temp����������һ�����ƣ�temper���¶�ֵ
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"drug1\":\"%d\",", device_state_init.drug1); // Temp����������һ�����ƣ�temper���¶�ֵ
	strcat(buf, text);

	memset(text, 0, sizeof(text));
	sprintf(text, "\"drug2\":\"%d\",", device_state_init.drug2); // Temp����������һ�����ƣ�temper���¶�ֵ
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"drug3\":\"%d\",", device_state_init.drug3); // Temp����������һ�����ƣ�temper���¶�ֵ
	strcat(buf, text);
	
	memset(text, 0, sizeof(text));
	sprintf(text, "\"waning\":\"%d\"", device_state_init.Key_State); // Temp����������һ�����ƣ�temper���¶�ֵ
	strcat(buf, text);

	memset(text, 0, sizeof(text));
	sprintf(text, "}");
	strcat(buf, text);

	return strlen(buf);
}
unsigned char drugBuf(char *buf)
{
	char text[256];
	memset(text, 0, sizeof(text));

	strcpy(buf, "{");


	memset(text, 0, sizeof(text));
	sprintf(text, "\"drug\":\"%d\"", device_state_init.drug); // Temp����������һ�����ƣ�temper���¶�ֵ
	strcat(buf, text);

	memset(text, 0, sizeof(text));
	sprintf(text, "}");
	strcat(buf, text);

	return strlen(buf);
}
void Mqtt_Pub(u8 cmd)
{

	char buf[256];
	char str[256];
	short body_len = 0;
	memset(buf, 0, sizeof(buf));
	switch (cmd)
	{
	case 1:
		body_len = FillBuf(buf); // ������
		break;
	case 2:
		body_len = drugBuf(buf); // ������
		break;
	default:
		break;
	}


	if (body_len)
	{
		sprintf(str, "AT+MTPUB=0,0,0,0,\"%s\",\"%s\"\r\n",P_TOPIC_NAME,buf);
		//GA10_SendCmd(str, "OK", 500);
		Usart3_SendString((unsigned char *)str,strlen(str)); // �����豸������������
		delay_ms(100);
	}
	
	
}

