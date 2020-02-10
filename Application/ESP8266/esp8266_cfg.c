#include "esp8266_cfg.h"

//===>>>AT命令组	开始	//////////////////////////////////////////////////////////////////////////////////////
//===AT返回命令
const char ESP8266_AT_RESPONSE_OK[] = "OK\r\n";																			//---正确
const char ESP8266_AT_RESPONSE_ERROR[] = "ERROR\r\n";																	//---错误
const char ESP8266_AT_RESPONSE_FAIL[] = "FAIL";																			//---失败
const char ESP8266_AT_RESPONSE_READY[] = "READY!";																		//---准备
const char ESP8266_AT_RESPONSE_RECEIVED[] = "+IPD,";																	//---接收到服务器发来的数据

//===AT基本指令
const char ESP8266_AT_CMD_TEST[] = "AT";																					//---测试命令
const char ESP8266_AT_CMD_RESET[] = "AT+RST";																				//---模块重启
const char ESP8266_AT_CMD_VERSION[] = "AT+GMR";																			//---查看固件版本
const char ESP8266_AT_CMD_DEEP_SLEEP[] = "AT+GSLP";																		//---进入DepSleep睡眠模式
const char ESP8266_AT_CMD_SET_SLEEP[] = "AT+SLEEP";																		//---设置休眠模式
const char ESP8266_AT_CMD_ECHO_OPEN[] = "ATE1";																			//---打开回显
const char ESP8266_AT_CMD_ECHO_CLOSE[] = "ATE0";																			//---关闭回显
const char ESP8266_AT_CMD_RESTORE[] = "AT+RESTORE";																		//---恢复出厂设置
const char ESP8266_AT_CMD_UART[] = "AT+UART";																				//---设置串口模式
const char ESP8266_AT_CMD_UART_CUR[] = "AT+UART_CUR";																		//---当前临时配置
const char ESP8266_AT_CMD_UART_DEF[] = "AT+UART_DEF";																		//---UART默认配置，保存到Flash
const char ESP8266_AT_CMD_SYSRAM[] = "AT+SYSRAM";																			//---查询系统当前剩余内存
const char ESP8266_AT_CMD_SYSMSG_CUR[] = "AT+SYSMSG_CUR";																	//---设置当前系统消息
const char ESP8266_AT_CMD_SYSMSG_DEG[] = "AT+SYSMSG_DEF";																	//---设置默认系统消息

//===WIFI功能命令
const char ESP8266_AT_WIFI_MODE[] = "AT+CWMODE";																			//---设置模式，响应OK
const char ESP8266_AT_WIFI_DEF[] = "AT+CWMODE_DEF";																		//---配置WiFi模组工作模式为单STA模式，并把配置保存在flash
const char ESP8266_AT_WIFI_CONNECT_AP[] = "AT+CWJAP";																		//---加入热点，连接路由器，响应OK
const char ESP8266_AT_WIFI_LIST_IP[] = "AT+CIFSR";																		//---查询设备的IP地址
const char ESP8266_AT_WIFI_LIST_AP[] = "AT+CWLAP";																		//---产看当前的无线路由器列表
const char ESP8266_AT_WIFI_DISCONNECT[] = "AT+CWQAP";																		//---退出热点
const char ESP8266_AT_WIFI_AP_CONFIG[] = "AT+CWSAP";																		//---设置热点
const char ESP8266_AT_WIFI_STA_IP[] = "AT+CWLIF";																			//---获取连接信息
const char ESP8266_AT_WIFI_DHCP_EN[] = "AT+CWDHCP";																		//---设置DHCO
const char ESP8266_AT_WIFI_AUTO_CONNECT[] = "AT+CWAUTOCONN";																//---使能上电自动连接AP
const char ESP8266_AT_WIFI_SET_STA_MAC[] = "AT+CIPSTAMAC";																//---设置MAC地址							
const char ESP8266_AT_WIFI_SET_STA_IP[] = "AT+CIPSTA";																	//---设置IP地址
const char ESP8266_AT_WIFI_SET_AP_IP[] = "AT+CIPAP";																		//---设置热点的IP地址
const char ESP8266_AT_WIFI_STARTSMART[] = "AT+CWSTARTSMART";																//---无论配网是否成功，都需要释放快连所占的内存
const char ESP8266_AT_WIFI_STOPSMART[] = "AT+CWSTOPSMART";																//---无论配网是否成功，都需要释放快连所占的内存
const char ESP8266_AT_WIFI_STARTDISCOVER[] = "AT+CWSTARTDISCOVER";														//---开启可被局域网的微信探测的模式
const char ESP8266_AT_WIFI_STOPDISCOVER[] = "AT+CWSTOPDISCOVER";															//---关闭可被局域网的微信探测的模式
const char ESP8266_AT_WIFI_WPS[] = "AT+WPS";																				//---设置WPS
const char ESP8266_AT_WIFI_MDNS[] = "AT+MDNS";																			//---设置MDNS功能
const char ESP8266_AT_WIFI_SET_STA_NAME[] = "AT+CWHOSTNAME";																//---设置STA的主机名称
const char ESP8266_AT_WIFI_SET_STA_COUNTRY[] = "AT+CWCOUNTRY";															//---设置WIFI的国家码

//===TCP/IP Commands
const char ESP8266_TCP_IP_STARTSMART[] = "AT+CWSTARTSMART";																//---无论配网是否成功，都需要释放快连所占的内存
const char ESP8266_TCP_IP_STOPSMART[] = "AT+CWSTOPSMART";																	//---无论配网是否成功，都需要释放快连所占的内存
const char ESP8266_TCP_IP_STATUS[] = "AT+CIPSTATUS";																		//---查询网络连接状态，响应OK
const char ESP8266_TCP_IP_DOMAIN[] = "AT+CIPDOMAIN";																		//---查域名解析功能
const char ESP8266_TCP_IP_CONNECT[] = "AT+CIPSTART";																		//---连接服务器
const char ESP8266_TCP_IP_SSL_SIZE[] = "AT+CIPSSLSIZE";																	//---设置SSL的缓存区大小
const char ESP8266_TCP_IP_SSL_CONF[] = "AT+CIPSSLCONF";																	//---设置SSL Client
const char ESP8266_TCP_IP_SEND[] = "AT+CIPSEND";																			//---启动透传
const char ESP8266_TCP_IP_SENDX[] = "AT+CIPSENDX";																		//---发送数据，达到设置⻓长度，或者遇到字符 \0，则发送数据
const char ESP8266_TCP_IP_SENDBUF[] = "AT+CIPSENDBUF";																	//---数据写⼊入TCP 发包缓存
const char ESP8266_TCP_IP_BUFRESET[] = "AT+CIPBUFRESET";																	//---重置计数（TCP 发包缓存）
const char ESP8266_TCP_IP_BUFSTATUS[] = "AT+CIPBUFSTATUS";																//---查询 TCP 发包缓存的状态
const char ESP8266_TCP_IP_CHECKSEQ[] = "AT+CIPCHECKSEQ";																	//---查询写⼊入 TCP 发包缓存的某包是否成功发送
const char ESP8266_TCP_IP_CLOSE[] = "AT+CIPCLOSE";																		//---关闭传输
const char ESP8266_TCP_IP_LIST_IP[] = "AT+CIFSR";																			//---查询设备的IP地址
const char ESP8266_TCP_IP_IP_MUX[] = "AT+CIPMUX";																			//---使能多连接
const char ESP8266_TCP_IP_SERVER_CONFIG[] = "AT+CIPSERVER";																//---建立TCP服务器
const char ESP8266_TCP_IP_SERVER_MAX_COUNT[] = "AT+CIPSERVERMAXCOUT";														//---设置服务器器允许建⽴立的最⼤大连接
const char ESP8266_TCP_IP_MODE[] = "AT+CIPMODE";																			//---设置透传模式，0---普通传输模式，1---透传模式，仅⽀支持 TCP 单连接和 UDP 固定通信对端的情况
const char ESP8266_TCP_IP_SAVE_TRANS_LINK[] = "AT+SAVETRANSLINK";															//---保存透传连接到 Flash
const char ESP8266_TCP_IP_SET_SERVER_TIMEOUT[] = "AT+CIPSTO";																//---设置作为 TCP 服务器器时的超时时间
const char ESP8266_TCP_IP_PING[] = "AT+PING";																				//---pin功能
const char ESP8266_TCP_IP_UPDATE[] = "AT+CIUPDATE";																		//---通过WiFi升级软件
const char ESP8266_TCP_IP_IPDINFO[] = "AT+CIPDINFO";																		//---接收⽹网络数据时，+IPD 是否提示对端 IP 和端⼝口
const char ESP8266_TCP_IP_RECVMODE[] = "AT+CIPRECVMODE";																	//---设置 TCP 接收模式
const char ESP8266_TCP_IP_RECVDATA[] = "AT+CIPRECVDATA";																	//---TCP 被动接收模式下，读取缓存的 TCP 数据
const char ESP8266_TCP_IP_RECVLEN[] = "AT+CIPRECVLEN";																	//---TCP 被动接收模式下，查询缓存 TCP 数据的⻓长度TCP 数据
const char ESP8266_TCP_IP_SNTPCFG[] = "AT+CIPSNTPCFG";																	//---设置时域和 SNTP 服务器器
const char ESP8266_TCP_IP_SNTPTIME[] = "AT+CIPSNTPTIME";																	//---查询 SNTP 时间
const char ESP8266_TCP_IP_DNS[] = "AT+CIPDNS";																			//---⾃自定义 DNS 服务器器

//===GPIO Commands
const char ESP8266_GPIO_PINMODE[] = "AT+PINMODE";																			//---配置端口输入输出模式
const char ESP8266_GPIO_PINWRITE[] = "AT+PINWRITE";																		//---设置的端口输出高低电平
const char ESP8266_GPIO_PINREAD[] = "AT+PINREAD";																			//---读取端口的电平信号
//===<<<AT命令组	结束//////////////////////////////////////////////////////////////////////////////////////

UINT8_T g_ESP8266_RX_BUFFER[ESP8266_BUFFER_MAX_SIZE] = { 0 };															//---接收缓存区
UINT8_T g_ESP8266_TX_BUFFER[ESP8266_BUFFER_MAX_SIZE] = { 0 };															//---接收缓存区


UINT8_T ESP8266_Init()
{
	return OK_0;
}

UINT8_T ESP8266_SendString(void)
{
	return OK_0;
}

UINT8_T ESP8266_ExitTransparentMode(void)
{
	return OK_0;
}

