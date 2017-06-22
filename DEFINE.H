#ifndef _DEFINE_H_
#define _DEFINE_H_
////////////////////////////////////// KING_DEFINE
#define  ID_CARD_NUMBER_FOR_4_BYTE          0x03
#define  in_station_status_for_king         0x01
#define  out_station_status_for_king		0x04


#define  in_lost_time_for_station           0x01
#define  out_lost_time_for_station          0x02
#define  complete_for_group_station         0x03
		 

#define  can_BROAD_ADDRESS                  0xFF



	#define  enable_input                       0x24

	#define  disenable_input                    0x13



    #define  Loading                            0x0F
	    #define  Login                            0x01
		#define  Logout                           0x00
	    
	#define  input_delay_time                   0x40
//	#define  output_delay_time                  0x02
	#define  input_last_time                    0x41
//	#define  output_last_time                   0x04
//	#define  loading_and_quit                   0x05
    #define  RFID_Freq_AND_Protect_Too_Long_Hanger         0x42
	#define  STOP_CACULATE_HANG                 0x43



	#define  STATION_TYPE                       0x0E
	    #define   work_station                 0x00
		#define   check_station                0x01
	#define  CLEAR_TEST_UID                       0x56



	
	   // #define   start_complete_key                0x03
	#define  reset_ID_CARD                0x31
	#define  Stop_Input                   0x19
	#define  control_LED                  0x32

#define  CAN_Error                         0x54



	#define  set_board_addrss                   0x50
	    #define  Set_UID_addrss                   0x00
		#define  Set_DEV_addrss                   0x01
		#define  Set_DEV_addrss_With_UID          0x02


	#define  Change_board_addrss                0x51
	#define  Switch_For_Heart_INFO              0x52
	#define  Heart_INFO_Period_Time             0x53
	#define  TrunTo_BootLoader                  0x55
	#define  CAN_TX_TimeOut                     0x3E

	#define  DisPlay_AT_LCD                     0x63
	#define  Clear_LCD_PC_TO_LCD                0x62
	#define  Lock_OR_Unlock_LCD                 0x61
	    #define  Unlock_LCD                          0x00 
		#define  Lock_LCD                            0x01    
	#define  LCD_Data_To_PC                     0x60

	





#define  test                                0x73

#define  LED1_PIN               P4_4
#define  LED2_PIN               P4_3
#define  LED3_PIN               P1_5
/////////////////////////////////////
#define  Enable_Txd_1()          P3_0 = 1		  //串口2的发送，接收切换。
#define  Enable_Rxd_1()          P3_0 = 0

#define  Enable_Txd()            P1_2 = 1		   //串口1的发送，接收切换。
#define  Enable_Rxd()            P1_2 = 0
#define  OUTPUT_YJ_ENABLE            P4_7 		   //衣架出站使能脚，打开电磁阀
#define  INPUT_YJ_ENABLE            P4_6		   //衣架进站，打开相应电磁阀
#define  DONE_YJ_ENABLE            P4_5			   //衣架中转的相应电磁阀。
#define  MOTO_ENABLE               P3_4			   //驱动电机。
#define  LED1_ENABLE               P0_7
#define  LED2_ENABLE               P4_2
#define  BUZZ_ENABLE               P4_1
#define  Fram_Head          0xED
#define  Fram_End           0xEE
#define  Fram_Head_1          0x0A
#define  Fram_End_1           0x0D
#define  Fram_Head_1_MtoS		  0x09
#define  ID_NUM    0x09								//RFID卡的考号数量。

#define  DEV_TYPE         0x02
#define  BROAD_ADDRESS    0x00

#define  True              1 
#define  False              0 
#define  Max_DevAddr    254   //最大设备地址
#define  Execute_Last_Time    440   //进出站动作持续时间,5ms一个单位
#define  Worker_RFID_Frequency    400   //员工读卡器频率,5ms一个单位
#define  Hanger_RFID_Frequency    30   //衣架读卡器频率,5ms一个单位

#define  HELLO            0x01					   //相应的协议命令。
#define  ACT       		  0x02
#define  ASK              0x0A
#define  ANS              0x0B
#define  EEROR            0x0E
#define  TOTAL_AND_EFFICIENCY        0x13
#define  LOAD_FAIL        0x14
#define  LOAD_SUCCESS     0x16
#define  ERROR_WORKERID_OR_PASS     0x15
#define  WORKER_QUIT_TURE     0x17
#define  IN_STATION_STATUS     0x6F
#define  OUT_STATION_STATUS     0x6E

#define  IN_OUT_TIME          0x25
#define  DEMO_COMPLETE          0x26
#define  SET_ADDRESS          0x28



#define  INPUT_YJ         0x83
#define  OUTPUT_YJ        0x85
#define  IN_TIME_LAST          0x86
#define  OUT_TIME_LAST          0x87
#define  BUZZER_LED          0x88
#define  DEMO_do              0x99
#define  DEMO_complete_for_station              0x89

#define  WORKER_ID                   0x50					 
#define  WORKER_NUM_AND_PASS        0x51
#define  WORKER_QUIT        0x52

#define  YJ_ID                      0x55
#define  HEART_INFORMATION          0X58
#define  SUCCESS_INPUT              0X59
#define  FAIL_INPUT                 0X5A
#define  Enable_Input               0X5B

//#define  Key               P4_0
//#define  scan_complete     P0_3
#define  Key               P0_3
#define  scan_complete     P4_0
//#define  scan_stop_moto_1  P0_4
//#define  scan_stop_moto_2  P0_6

//#define  In_station_flag   P0_3
//#define  scan_complete     P4_0
//#define  scan_stop_moto_1  P0_4
//#define  scan_stop_moto_2  P3_7

extern ubyte  ub_Have_BootLoader_APP;
extern uword  pdata uw_T0_5MS_Count_For_Check_Time,  test_data,  T0_5MS_count_input, T0_5MS_count_input_2, T0_5MS_count_input_3, 	uw_T0_5MS_Count_For_Record_Hanger_Time, uw_T0_5MS_Count_For_ADD_Hanger_Time,
                       uw_T0_5MS_count_For_Waiting_Hanger_After_Got_IDCARD, uw_T0_5MS_count_For_CheckStation_For_TheSameCard;  //4个5毫秒定时计数变量。分别应用于，进站传感器满、出站传感器满、进站持续时间，出站持续时间的定时。
extern ubyte  pdata   T0_5MS_count1,	//count1计数。应用于判断和主机通信时间是否过长时使用。5ms一个计数。	count_worker_id应用于定时扫描登陆读卡器。
      T0_5MS_count_YJ_id,  T0_5MS_IDread_frame_count,  // count_YJ_id应用于定时扫描出站处的读卡器。	 IDcard_send_count，发送同一个衣架卡号的次数。满几次后，发送本机状态，针对ask命令。
	   T0_5MS_count_complete_scan, ub_T0_5MS_count_scan_Key, ub_3LED_flash_flag, T0_5MS_count_led, T0_5MS_count_Waiting_CAN_Send_INTR_Flag;
	
extern bool   FRAME_start_1,     b_InPut_Enable,	b_Key_Flag,
  
      FRAME_end_1, have_id_data,    input_yj_flag, input_yj_flag_2, input_yj_flag_3, 	b_input_yj_flag_for_have_find_same_idcard,	b_Complete_Done_Key_Have_Done, b_Start_Caculate_Hanger,    b_Get_Caculate_Hanger,
	
	       b_T0_5MS_flag, b_COMPLETE_DONE_flag;
	  

extern bool  b_CAN_franme_start, b_CAN_franme_stop, b_CAN_traning, b_CAN_waiting_interrupt, b_CAN_tran_complete,  b_Success_To_Send_Success_Input,
      b_Communicate_Error, b_Waiting_CAN_Send_Interupt_Flag, b_CAN_Send_Fail_Flag;
extern ubyte       byte_count_1, DEV_ADDR, error_data[1], in_out_time[2], 	STATION_type,	ub_LoginStatus,	CAN_Error_data,
                  ub_Protect_Too_Long_Hanger, ub_RFID_Freq,
         // buff[27]，和主机通信的buff。byte_count，和主机通信的，一帧通信字节计数器。
		 //	byte_count_1，和读卡器通信的通信字节计数器。
		 //DEV_ADDR，设备地址。	 error_data[1]，报错内容。	in_out_time[2]，进站和出站延时时间。
          send_data[17],IDCARD_data[5];
		  //send_data[17],   和读卡器通信的buff。  IDCARD_data[10]，存储卡号的buff。同时也用作键盘登陆时候，保存的6位卡号和4位密码	、
		  //full_data[1]工站状态字节。包括是否登陆，是否进站满，是否出站满
		    


extern ubyte idata in_time_last, out_time_last, CAN_TX_BUFF[18], CAN_RX_BUFF[26], CAN_BYTE_DATA_COUNT,  can_tx_status, can_traning_frame_number;
extern ubyte idata TX_FIFO_FUNC[4], TX_FIFO_COUNTER;


extern bool  b_receive_can_frame, b_Enable_Heart_INFO;
extern ubyte idata   RX_CAN_ID_FOR_DEV_ADDR, RX_CAN_ID_FOR_DEV_FUN,  UID1, UID2, UID3, UID4, HEART_INFO[6], ub_Heart_Info_Period_Time, ub_CAN_TX_Frame_Count;
extern uword idata  	 T0_5MS_count_heart_information;

extern ubyte idata  ub_Add_Input_id[4];
extern ubyte pdata  ub_ID_To_Dele_For_Input[4], ub_Soft_Complete_Count;
extern uword pdata uw_Have_Hanger_By_Soft;


extern ubyte xdata *p_ID_card_buffer;


extern bool b_Flag, b_Turn_To_BootLoader_Flag;
extern ubyte code *DFlash_ADDR;
extern ubyte xdata *XDATA_P;
extern ubyte code *PFlash_ADDR;

/*********LCD_KEY**********/

extern bool b_rs_485_2_traning, FRAME_start_rs485_lk, FRAME_end_rs485_lk, b_have_LCD_KEY_DATA, b_check_have_lcd_key;
extern ubyte idata ub_rs_485_2_TX_FIFO_COUNTER, ub_rs485_2_TX_FIFO_FUNC[4], ub_rs485_2_TX_status, ub_T0_5MS_count_re_485_2_wait_recieve;
extern ubyte idata LCD_KEY_DATA[24], byte_count_rs485_lk, T0_5MS_rs485_lk_frame_count, T0_5MS_count_rs485_lk, RS485_LK_buff[24],
            ub_send_lcd_key_data_number, ub_lcd_key_send_pc_number, ub_Send_LCD_Data_Number_For_485;


//extern ubyte xdata test_id_card[4];
void Delay_function(int num);
void Ram_Init(void);
void clear_communicate_flag(void);
void on_buzzer_led(void);
void off_buzzer_led(void);
//void clear_buff(void);
#endif 