//****************************************************************************
// @Module        Project Settings
// @Filename      MAIN.C
// @Project       170306.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC878CM-16FF
//
// @Compiler      Keil
//
// @Codegenerator 2.2
//
// @Description   This file contains the Project initialization function.
//
//----------------------------------------------------------------------------
// @Date          2017/3/24 15:02:38
//
//****************************************************************************

// USER CODE BEGIN (MAIN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (MAIN_General,2)
ubyte  ub_Have_BootLoader_APP;
uword  pdata    T0_5MS_count_input, uw_T0_5MS_Count_For_Record_Hanger_Time, uw_T0_5MS_Count_For_ADD_Hanger_Time,
                uw_T0_5MS_count_For_Waiting_Hanger_After_Got_IDCARD, uw_T0_5MS_count_For_CheckStation_For_TheSameCard;  //4个5毫秒定时计数变量。分别应用于，进站传感器满、出站传感器满、进站持续时间，出站持续时间的定时。
ubyte  pdata   T0_5MS_count1,	//count1计数。应用于判断和主机通信时间是否过长时使用。5ms一个计数。	count_worker_id应用于定时扫描登陆读卡器。
      T0_5MS_count_YJ_id,  T0_5MS_IDread_frame_count,  // count_YJ_id应用于定时扫描出站处的读卡器。	 IDcard_send_count，发送同一个衣架卡号的次数。满几次后，发送本机状态，针对ask命令。
	   T0_5MS_count_complete_scan, ub_T0_5MS_count_scan_Key, ub_3LED_flash_flag, T0_5MS_count_led, T0_5MS_count_Waiting_CAN_Send_INTR_Flag;
	
bool   FRAME_start_1,     b_InPut_Enable,	b_Key_Flag,
  
      FRAME_end_1, have_id_data,    input_yj_flag, 	b_input_yj_flag_for_have_find_same_idcard,	   b_Complete_Done_Key_Have_Done,  b_Start_Caculate_Hanger,	b_Get_Caculate_Hanger,
	
	       b_T0_5MS_flag, b_COMPLETE_DONE_flag;
	  

bool  b_CAN_franme_start, b_CAN_franme_stop, b_CAN_traning, b_CAN_waiting_interrupt, b_CAN_tran_complete,  b_Success_To_Send_Success_Input,
      b_Communicate_Error, b_Waiting_CAN_Send_Interupt_Flag, b_CAN_Send_Fail_Flag;
ubyte       byte_count_1, DEV_ADDR, error_data[1], in_out_time[2], 	STATION_type,	ub_LoginStatus, CAN_Error_data,
           ub_Protect_Too_Long_Hanger, ub_RFID_Freq, 
         // buff[27]，和主机通信的buff。byte_count，和主机通信的，一帧通信字节计数器。
		 //	byte_count_1，和读卡器通信的通信字节计数器。
		 //DEV_ADDR，设备地址。	 error_data[1]，报错内容。	in_out_time[2]，进站和出站延时时间。
          send_data[17],IDCARD_data[5];
		  //send_data[17],   和读卡器通信的buff。  IDCARD_data[10]，存储卡号的buff。同时也用作键盘登陆时候，保存的6位卡号和4位密码	、
		  //full_data[1]工站状态字节。包括是否登陆，是否进站满，是否出站满
		    


ubyte idata in_time_last, out_time_last, CAN_TX_BUFF[18], CAN_RX_BUFF[26], CAN_BYTE_DATA_COUNT,  can_tx_status, can_traning_frame_number;
ubyte idata TX_FIFO_FUNC[4], TX_FIFO_COUNTER;


bool  b_receive_can_frame, b_Enable_Heart_INFO;
ubyte idata   RX_CAN_ID_FOR_DEV_ADDR, RX_CAN_ID_FOR_DEV_FUN,  UID1, UID2, UID3, UID4, HEART_INFO[6], ub_Heart_Info_Period_Time, ub_CAN_TX_Frame_Count;
uword idata  	 T0_5MS_count_heart_information;

ubyte idata  ub_Add_Input_id[4];

ubyte pdata ub_ID_To_Dele_For_Input[4], ub_Soft_Complete_Count;
uword pdata uw_Have_Hanger_By_Soft;

ubyte xdata *p_ID_card_buffer;


bool b_Flag, b_Turn_To_BootLoader_Flag;
ubyte code *DFlash_ADDR;
ubyte xdata *XDATA_P;
ubyte code *PFlash_ADDR;

/*********LCD_KEY**********/

bool b_rs_485_2_traning, FRAME_start_rs485_lk, FRAME_end_rs485_lk, b_have_LCD_KEY_DATA, b_check_have_lcd_key;
ubyte idata ub_rs_485_2_TX_FIFO_COUNTER, ub_rs485_2_TX_FIFO_FUNC[4], ub_rs485_2_TX_status, ub_T0_5MS_count_re_485_2_wait_recieve;
ubyte idata LCD_KEY_DATA[24], byte_count_rs485_lk, T0_5MS_rs485_lk_frame_count, T0_5MS_count_rs485_lk, RS485_LK_buff[24],
            ub_send_lcd_key_data_number, ub_lcd_key_send_pc_number, ub_Send_LCD_Data_Number_For_485;


    
// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (MAIN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (MAIN_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (MAIN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************


// USER CODE BEGIN (MAIN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (MAIN_General,9)

// USER CODE END


//****************************************************************************
// @Function      void MAIN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes the microcontroller. It is 
//                assumed that the SFRs are in their reset state.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2017/3/24
//
//****************************************************************************

// USER CODE BEGIN (MAIN_Init,1)

// USER CODE END

void MAIN_vInit(void)
{
  // USER CODE BEGIN (MAIN_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the System Clock:
  ///  -----------------------------------------------------------------------
  ///  - External Osc is selected (configuration is done in the startup file 
  ///    'START_XC.A51')
  ///  - PLL Mode, NDIV =  36, PDIV =  2, KDIV =  1
  ///  - input frequency is 8 MHz


  //   FCLK for MultiCAN runs at 2 times the frequency of PCLK.
  //   FCLK for CCU6 runs at 2 times the frequency of PCLK.
  //   FCLK for T2CCU runs at 2 times the frequency of PCLK.
  SFR_PAGE(_su1, noSST);         // switch to page1

  CMCON         =  0x10;         // load Clock Control Register
  CR_MISC       =  0x30;         // load Clock and Reset Miscellaneous 
                                 // Register

  SFR_PAGE(_su0, noSST);         // switch to page0


  ///  *********************************************************************************
  ///  Note : All peripheral related IO configurations are done in the 
  ///  respective peripheral modules (alternate functions selection)
  ///  *********************************************************************************

  ///  Initialization of module 'GPIO'
  IO_vInit();

  ///  Initialization of module 'Interrupt Unit'
  INT_vInit();

  ///  Initialization of module 'Timer 0/1'
  T01_vInit();

  ///  Initialization of module 'Watch Dog Timer'
  WDT_vInit();

  ///  Initialization of module 'MultiCAN Controller '
  CAN_vInit();

  ///  Initialization of module 'UART1 (Serial Interface)'
  UART1_vInit();

  ///  Initialization of  'Shared interrupts'
  SHINT_vInit();

  ///  -----------------------------------------------------------------------
  ///  Configuration of the External Interface Control Register (EINTCON):
  ///  -----------------------------------------------------------------------
  ///  - External interface globally disabled
  ///  - External data direction: Input
  ///  - All Bits of EINTCON can be written
  ///  - Address lines A8 to A15 disabled
  ///  - Address line A16 disabled
  ///  - Address line A17 disabled
  ///  - Address line A18 disabled
  ///  - Address line A19 disabled

  ///  *********************************************************************************
  ///  Note : Please make sure that proper Off-chip XDATA memory start 
  ///  address and size should be entered in the Off-chip Xdata memory 
  ///  section under Target settings option of Keil compiler.
  ///
  ///  Ex : If 0xFD00 is start address and 0x0100 is the size,
  ///  For KEIL these values should be entered in the keil IDE Off-chip Xdata 
  ///  memory section with ubyte xdata extmem_data[256] _at_ (0xFD00) 
  ///  declaration.
  ///  For SDCC it should be done using xdata at 0xfd00 ubyte 
  ///  extmem_data[256] declaration.
  ///  For IAR it should be done using __xdata __no_init ubyte 
  ///  extmem_data[256] @ 0xFD00 declaration.
  ///  *********************************************************************************

  SFR_PAGE(_su3, SST0);          // switch to page3
  EINTCON       =  0x00;         // External Interface Control Register
  SFR_PAGE(_su3, RST0);          // restore original page




  //   Interrupt Priority

  IP            =  0x20;         // load Interrupt Priority Register
  IPH           =  0x22;         // load Interrupt Priority High Register
  IP1           =  0x01;         // load Interrupt Priority 1 Register
  IPH1          =  0x01;         // load Interrupt Priority 1 High Register


  // USER CODE BEGIN (MAIN_Init,3)

  // USER CODE END

  //// Interrupt structure 2 mode 0 is selected.

  //// Interrupt service routine choice 2 is selected.

  //   globally enable interrupts
  EA            =  1;           

} //  End of function MAIN_vInit


//****************************************************************************
// @Function      void main(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the main function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2017/3/24
//
//****************************************************************************

// USER CODE BEGIN (MAIN_Main,1)
void Delay_function(int num)//延时函数
{
	while(num--);
}

void Ram_Init(void)
{
    p_ID_card_buffer = ID_CARD_StartADDR_At_XDATA;
	
	  FRAME_start_1  =    0;
	
	  FRAME_end_1    =    0;
	
	  b_T0_5MS_flag   =  0;
	
	  byte_count_1   = 0;
	
	  have_id_data     =    0;
	
	
	  input_yj_flag  =  0;
	
	  INPUT_YJ_ENABLE   =     0;
	  OUTPUT_YJ_ENABLE  =     0;
	  DONE_YJ_ENABLE    =     0;
	  MOTO_ENABLE       =     0;
	  P4_3              =     0;
	  P4_4              =     0;
	  P3_6              =     0;
	  P3_5              =     0;
	
	  b_COMPLETE_DONE_flag = 0;
	 
	 // ID_reader_wrong_count = 0;
		
	
	  T0_5MS_count_input = 0;
	
	
	
	  T0_5MS_count_YJ_id = 0;
	
	  b_InPut_Enable = 1;
	
	  b_Waiting_CAN_Send_Interupt_Flag = 0;
	  T0_5MS_count_Waiting_CAN_Send_INTR_Flag = 0;
	  b_CAN_Send_Fail_Flag = 0;

	  b_Enable_Heart_INFO = 1;
	
	  
	
	
	 // b_receive_can_frame = 0;
	 
	
	
	  b_input_yj_flag_for_have_find_same_idcard = 0;
	
	  clear_id_card_buffer();
	
	  LED1_PIN = 0;               
	  LED2_PIN = 0;              
	  LED3_PIN = 0;

	  b_Turn_To_BootLoader_Flag = 0;

	  ub_LoginStatus = 0;

	  T0_5MS_count_heart_information = (DEV_ADDR * 4);

	  UID3 = 0;
	  UID4 = 0;
	  UID2 = 0;
	  UID1 = 0;

	  b_Start_Caculate_Hanger = 0;

	  uw_Have_Hanger_By_Soft = 0;
	
	
	  Enable_Rxd();				//使能485芯片的接收功能。
	  
	 // can_tx_func_fifo(HEART_INFORMATION);
}

  
			

// USER CODE END

void main(void)
{
  // USER CODE BEGIN (MAIN_Main,2)

  // USER CODE END

  MAIN_vInit();

  // USER CODE BEGIN (MAIN_Main,3)

  Read_Parameter_To_Ram();
  Ram_Init();
  Set_RX_CAN_ID();

  UID2 = 0;
  

  // USER CODE END

  while(1)
  {

  // USER CODE BEGIN (MAIN_Main,4)

	  ubyte n;

	  WDT_vRefresh();
	  
	  execute_scan();	

	  Idreader_scan();

	  COMPLEGE_DONE_SCAN();
	  T0_INT_SCAN();
	  rs485_lk_scan();
	  scan_rs_485_2();
	  rs_485_2_tx_status();
	  scan_can_tx_frame();
	  scan_LED();
	  Scan_Hanger();
	  if(b_Turn_To_BootLoader_Flag)
	  {

		  WDT_vRefresh();
		  EA = 0;
	      Load_BootLoader_INTR_Table_To_MCU_Start_ADDR();
          ((void (code *) (void)) MCU_Start_ADDR_At_PFlash) ();
	  }
	 
	  if(b_Communicate_Error)
	  {
	      b_Communicate_Error = 0;
		  	      
		  Get_CAN_Data();
		  
	  }
	 



      if(b_CAN_franme_start&&(!b_CAN_franme_stop)&&(10 <= T0_5MS_count1))
	  {
	      T0_5MS_count1  =    0;
		  b_CAN_franme_start = 0;
		  clear_can_rx_buff_fun();
		  continue;
	  //此函数为判断，收到帧头后，中间间隔10ms以上没有收到帧尾，说明通信错误。
	  }
/***********************
if(!b_CAN_franme_stop) 
未接收到报尾。默认结束本次循环。不进行后续的处理。
************************/

      if(!b_CAN_franme_stop)       //接收完整一帧的标志。1为接收完一帧。0为未接收完。全局变量。
	  {						//在串口接收函数中处理。
	      continue;
	  }
	  b_CAN_franme_stop = 0;
	  Reorganize_CAN_RX_buff_fun();
	  

	  T0_5MS_count1 = 0;
//	  HEART_INFO[3] = RX_CAN_ID_FOR_DEV_ADDR;
//	  HEART_INFO[2] = RX_CAN_ID_FOR_DEV_FUN;
//	  can_tx_func_fifo(test);

		

/***********************
if((buff[2] != DEV_ADDR)&&(buff[2] != BROAD_ADDRESS))
接收到完整正确的报文。进行设备地址判断。如果不是本设备地址或者广播地址。丢弃该报文。
并把各个标记复位。等待下个报文
推出本次循环。

不返回信息
************************/	
	  
	  if((RX_CAN_ID_FOR_DEV_ADDR != DEV_ADDR)&&(RX_CAN_ID_FOR_DEV_ADDR != can_BROAD_ADDRESS))
	  {

	      clear_can_rx_buff_fun();
		  continue; 
	     
	  }	
	 // 		 error_data[0] = rx_can_id+0x80;
      //  can_tx_func_fifo(test);
	  T0_5MS_count_heart_information = 0;	
/***********************
if(BROAD_ADDRESS == buff[2])
接收到完整正确的报文。进行设备地址判断。如果是广播地址。进行相应处理
并把各个标记复位。等待下个报文。
退出本次循环。

广播地址命令。无法返回信息。下位机会冲突。
************************/
  //如果是广播地址
	  if(RX_CAN_ID_FOR_DEV_ADDR == can_BROAD_ADDRESS)	
	  {
			    	
	      switch(RX_CAN_ID_FOR_DEV_FUN)
		  {

		      case set_board_addrss:

			      switch(CAN_RX_BUFF[0])
				  {
				      case Set_DEV_addrss:
					      DEV_ADDR =  CAN_RX_BUFF[1];
			
						   write_parameter_to_flash();
						   Set_RX_CAN_ID();
					    
					      break;
					  case Set_UID_addrss:
					     // UID1 =  CAN_RX_BUFF[1];
						  UID2 =  CAN_RX_BUFF[2];
						  UID3 =  CAN_RX_BUFF[3];
						  UID4 =  CAN_RX_BUFF[4];			
						   write_parameter_to_flash();					     
					      break;
					  case Set_DEV_addrss_With_UID:
					      if((UID2 == CAN_RX_BUFF[2]) && (UID3 == CAN_RX_BUFF[3]) && (UID4 == CAN_RX_BUFF[4]))
						  {
							  DEV_ADDR =  CAN_RX_BUFF[5];
				
							   write_parameter_to_flash();
							   Set_RX_CAN_ID();
						  }
					      					    
					      break;
				      
					  default:
					      break;
				  }
			       
			      break;
			  case RFID_Freq_AND_Protect_Too_Long_Hanger:
				     
			      ub_RFID_Freq    =    CAN_RX_BUFF[0];
				  ub_Protect_Too_Long_Hanger = 	CAN_RX_BUFF[1];
				  write_parameter_to_flash();
			      break;
			  case STOP_CACULATE_HANG:
			      b_Start_Caculate_Hanger = 0;    
		          ub_Soft_Complete_Count = 0;
				  uw_Have_Hanger_By_Soft = 0;				     
			      break;
			  case CLEAR_TEST_UID:
			      UID1 = 0;
				  UID2 = 0;
				  UID3 = 0;
				  UID4 = 0;
				     
			      break;
			  case Heart_INFO_Period_Time:
			       ub_Heart_Info_Period_Time =  CAN_RX_BUFF[0];	
				   write_parameter_to_flash();				   
			      break;
			  case DisPlay_AT_LCD:
			       for(n = 0; n < ub_send_lcd_key_data_number; n++)
				   {
				       LCD_KEY_DATA[n] = CAN_RX_BUFF[n];
					   if(LCD_KEY_DATA[n] <= 0x15)
					   {
					       LCD_KEY_DATA[n] = 0x15;
					   }
					   else
					   {
						   LCD_KEY_DATA[n] -= 0x15;
					   }
					   
				   }
				   ub_Send_LCD_Data_Number_For_485 =  ub_send_lcd_key_data_number;
			       rs_485_2_tx_func_fifo(DISPLAY_LCD_ONE_LINE);	
				  // write_parameter_to_flash();				   
			      break;
			  case Clear_LCD_PC_TO_LCD:
			       rs_485_2_tx_func_fifo(CLEAR_LCD_ONE_LINE);	
				 //  write_parameter_to_flash();				   
			      break;
			 case Lock_OR_Unlock_LCD:
			      switch(CAN_RX_BUFF[0])
				  {
				      case Unlock_LCD:
					      rs_485_2_tx_func_fifo(UNLOCK_KEY);
					    
					      break;
					  case Lock_LCD:
					      rs_485_2_tx_func_fifo(LOCK_KEY);
					     
					      break;
				      
					  default:
					      break;
				  }
		
			      break;

			  case TrunTo_BootLoader:
			       if(ub_Have_BootLoader_APP != ub_True_Flag)
				  {
					  can_tx_func_fifo(Dont_Have_BootLoader);
				  }
				  else
				  {
				      can_tx_func_fifo(Turn_To_BootLoader_APP);    
				  }				   
			      break;

			  case Switch_For_Heart_INFO:
			      switch(CAN_RX_BUFF[0])
				  {
				      case True:
					      b_Enable_Heart_INFO = True;
					    
					      break;
					  case False:
					      b_Enable_Heart_INFO = False;
					     
					      break;
				      
					  default:
					      break;
				  }
		
			      break;
		
			  default:
			      break;
   
		  }
		  clear_can_rx_buff_fun();		  	      
		  continue;
	  }	




/***********************
switch(buff[3])
接收到正确报文，并通过以上判断确定为没有任何错误的，属于本机的独立报文。
并被给予总线发送权。
跟进命令类型进入各个命令处理函数。
************************/
	 

	 // error_data[0] = rx_can_id;
     // can_tx_func_fifo(test);
	 	
      switch(RX_CAN_ID_FOR_DEV_FUN)	  //以上都符合本机要求。则对命令类型进行判断处理
	  {

	      case Clear_LCD_PC_TO_LCD:
		       rs_485_2_tx_func_fifo(CLEAR_LCD_ONE_LINE);	
			 //  write_parameter_to_flash();				   
		      break;
		  case DisPlay_AT_LCD:
		       for(n = 0; n < ub_send_lcd_key_data_number; n++)
			   {
			       LCD_KEY_DATA[n] = CAN_RX_BUFF[n];
				   if(LCD_KEY_DATA[n] <= 0x15)
				   {
				       LCD_KEY_DATA[n] = 0x15;
				   }
				   else
				   {
					   LCD_KEY_DATA[n] -= 0x15;
				   }
				   
			   }
			   ub_Send_LCD_Data_Number_For_485 =  ub_send_lcd_key_data_number;
			  // can_tx_func_fifo(test);
		       rs_485_2_tx_func_fifo(DISPLAY_LCD_ONE_LINE);	

			  // write_parameter_to_flash();				   
		      break;

	      case TrunTo_BootLoader:
		       if(ub_Have_BootLoader_APP != ub_True_Flag)
			  {
				  can_tx_func_fifo(Dont_Have_BootLoader);
			  }
			  else
			  {
			      can_tx_func_fifo(Turn_To_BootLoader_APP);    
			  }				   
		      break;
		  case Lock_OR_Unlock_LCD:
		      switch(CAN_RX_BUFF[0])
			  {
			      case Unlock_LCD:
				      rs_485_2_tx_func_fifo(UNLOCK_KEY);
				    
				      break;
				  case Lock_LCD:
				      rs_485_2_tx_func_fifo(LOCK_KEY);
				     
				      break;
			      
				  default:
				      break;
			  }
	
		      break;

	      case STATION_TYPE:
		      UID2 = 0;
			  UID3 = 0;
			  UID4 = 0;
			    ub_ID_To_Dele_For_Input[0] =  0;
	
				ub_ID_To_Dele_For_Input[1] =  0;
	
				ub_ID_To_Dele_For_Input[2] =  0;
	
				ub_ID_To_Dele_For_Input[3] =  0;
		      switch(CAN_RX_BUFF[0])
			  {
			      case work_station:
				      STATION_type = work_station;
					  ub_LoginStatus &= 0xEF;
				    
				      break;
				  case check_station:
				      STATION_type = check_station;
					  ub_LoginStatus |= 0x10;
				     
				      break;
			      
				  default:
				      break;
			  }
	
		      break;
		  case disenable_input:
		      ub_Add_Input_id[0] = CAN_RX_BUFF[0];
			  ub_Add_Input_id[1] = CAN_RX_BUFF[1];
			  ub_Add_Input_id[2] = CAN_RX_BUFF[2];
			  ub_Add_Input_id[3] = CAN_RX_BUFF[3];

		      dele_id_card_for_input(ub_Add_Input_id);
//					  if(UID1 > 0)
//					  {
//					      UID1--;
//					  }
		       
		      break;
		  case Stop_Input:
		  	  b_InPut_Enable = 0;

			 

		      break;

		  case enable_input:
		      if(UID1 < 250)
			{
				UID1++;
			}
			  ub_Add_Input_id[0] = CAN_RX_BUFF[0];
			  ub_Add_Input_id[1] = CAN_RX_BUFF[1];
			  ub_Add_Input_id[2] = CAN_RX_BUFF[2];
			  ub_Add_Input_id[3] = CAN_RX_BUFF[3];
		   	  
			  add_id_card_for_input(ub_Add_Input_id);
		      break;

		  case reset_ID_CARD:
		  	  clear_id_card_buffer(); 
			  UID1 = 0;  
		      break;

		  case input_delay_time:
				     
		      in_out_time[0]    =    CAN_RX_BUFF[0];
			  	
	           write_parameter_to_flash();
		      break;
		  case input_last_time:
				     
		      in_time_last    =    CAN_RX_BUFF[0];
			  	
			  write_parameter_to_flash();
		      break;
		  case RFID_Freq_AND_Protect_Too_Long_Hanger:
				     
		      ub_RFID_Freq    =    CAN_RX_BUFF[0];
			  ub_Protect_Too_Long_Hanger = 	CAN_RX_BUFF[1];
			  write_parameter_to_flash();
		      break;
		  case Loading:
		      switch(CAN_RX_BUFF[0])
			  {
			      case Login:
				      ub_LoginStatus |= 0x80;
				    
				      break;
				  case Logout:
				      ub_LoginStatus &= 0x7F;
				     
				      break;
			      
				  default:
				      break;
			  }
		      
		     
		      break;
		  case control_LED:
		      ub_3LED_flash_flag = CAN_RX_BUFF[0];
		      
		      break;
		  case Change_board_addrss:
		       DEV_ADDR =  CAN_RX_BUFF[0];

			   write_parameter_to_flash();
			   Set_RX_CAN_ID();
		      break;

		  default:
		  //返回错误信息，或者调用错误函数
			  clear_can_rx_buff_fun();
			  
		      break;
	  }
	  clear_can_rx_buff_fun();


  // USER CODE END

  }

} //  End of function main


// USER CODE BEGIN (MAIN_General,10)

// USER CODE END

