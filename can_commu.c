#include "MAIN.H"

void scan_can_tx_frame(void)
{
   
    can_tx_status_scan_function();

	if(T0_5MS_count_heart_information > ((ub_Heart_Info_Period_Time * 200) + DEV_ADDR))
	{
	  //  T0_5MS_count_heart_information = 0;
		can_tx_func_fifo(HEART_INFORMATION);

	}

}

void Reorganize_CAN_RX_buff_fun(void)
{
    ubyte i,j, k;
	k = 0;
	for(j = 0; j < 3; j++)
	{
	    for(i = 0; i < 7; i++)
		{
		    CAN_RX_BUFF[k] = CAN_RX_BUFF[(8 * j) + 1 + i];
			k++;
		}
	}
}

void clear_can_rx_buff_fun(void)
{
    ubyte i;
	for(i = 0; i < 25; i++)
	{
	    CAN_RX_BUFF[i] = 0;
	}
	CAN_BYTE_DATA_COUNT = 0;
	b_CAN_franme_start = 0;
	b_CAN_franme_stop  = 0;
	b_receive_can_frame = 0;
	RX_CAN_ID_FOR_DEV_FUN = 0;
	ub_send_lcd_key_data_number = 0;
	ub_CAN_TX_Frame_Count = 0;
}

void clear_can_tx_buff_fun(void)
{
    ubyte i;
	for(i = 0; i < 16; i++)
	{
	    CAN_TX_BUFF[i] = 0;
	}

}

void send_Frame_data_for_can(ubyte send_data[], ubyte Len)
{
	ubyte i, j, k, frame_number;
	k = 0;

	if(Len > 14)
	{
	    Len = 14;
	}
	frame_number = (Len/7);
	if((Len%7) != 0)
	{
	    frame_number++;    
	}	
	if(0 == Len)
	{
	    frame_number = 1;
	}

	for(i = 0; i < frame_number; i++)
	{
		CAN_TX_BUFF[i * 8] = (((frame_number -1) * 16) + i);

    }



	//内容
	for(j = 0; j< frame_number; j++)
	{
		for(i = 0; i < 7; i++)
		{	    	    
		    CAN_TX_BUFF[(8 * j) + i+1]  =  send_data[k];
			k++;
			if(k >= Len)
			{
			    break;
			} 		
		}
		if(k >= Len)
		{
		    break;
		}
	}
	

}

void can_send_data(ubyte Len)
{
    ubyte i, j,frame_number, ub_TX_DLC;
	if(Len > 14)
	{
	    Len = 14;
	}
	
	frame_number = (Len/7);
	if((Len%7) != 0)
	{
	    frame_number++;    
	}
	if(0 == Len)
	{
	    frame_number = 1;
	}

	for(j = 0; j < frame_number; j++)
	{
	    i = j * 8;	
		ub_TX_DLC  = (Len + 1 - (j * 7));
		CAN_DATA0 = CAN_TX_BUFF[i];  	// load to CAN Data register 0 
		i++; 
		CAN_DATA1 =	CAN_TX_BUFF[i];
		i++;
		CAN_DATA2 = CAN_TX_BUFF[i];  	// load to CAN Data register 0  
		i++;
		CAN_DATA3 = CAN_TX_BUFF[i];
		i++;			
													
	    CAN_vWriteCANAddress(CAN_MODATAL0);	  				// address MO0 Data register
	    CAN_vWriteEN(ALL_DATA_VALID);	
	
		CAN_DATA0 = CAN_TX_BUFF[i];  	// load to CAN Data register 0 
		i++; 
		CAN_DATA1 =	CAN_TX_BUFF[i];
		i++;
		CAN_DATA2 = CAN_TX_BUFF[i];  	// load to CAN Data register 0  
		i++;
		CAN_DATA3 = CAN_TX_BUFF[i];
		i++;
	 
		
		CAN_vWriteCANAddress(CAN_MODATAH0);	  				// address MO0 Data register
	    CAN_vWriteEN(ALL_DATA_VALID);
		switch(ub_TX_DLC)
		{
		    case 0:
			    set_tx_can_dlc(0);	
			    break;
			case 1:
			    set_tx_can_dlc(1);
				break;
			case 2:
			    set_tx_can_dlc(2);			    	
			    break;
			case 3:
			    set_tx_can_dlc(3);	
			    break;
			case 4:
			    set_tx_can_dlc(4);
				break;
			case 5:
			    set_tx_can_dlc(5);			    	
			    break;
			case 6:
			    set_tx_can_dlc(6);
				break;
			case 7:
			    set_tx_can_dlc(7);			    	
			    break;
			case 8:
			    set_tx_can_dlc(8);			    	
			    break;
			default:
				set_tx_can_dlc(8);	
			    break;
		}
								   
	    CAN_vTransmit(0);	
		b_Waiting_CAN_Send_Interupt_Flag = 1;
		T0_5MS_count_Waiting_CAN_Send_INTR_Flag = 0;
	
		while(b_CAN_tran_complete == 0)
		{
		    T0_INT_SCAN();
		    if(T0_5MS_count_Waiting_CAN_Send_INTR_Flag > 2)
			{	   
			    Cancel_CAN_vTransmit(0);
			    Recover_CAN_BUS();
			    CAN_vInit();
				b_CAN_tran_complete = 1;
				b_CAN_Send_Fail_Flag = 1;	
				j = frame_number;	
				if(error_data[0] < 250)
				{
					error_data[0]++;
				}
				
				can_tx_func_fifo(CAN_TX_TimeOut);	
			}	    
		}
			b_CAN_tran_complete	 = 0;
			b_Waiting_CAN_Send_Interupt_Flag = 0;
	}
}


void Recover_CAN_BUS(void)
{
    CAN_vWriteCANAddress(CAN_NCR0); // Addressing CAN_NCR0
    CAN_DATA0 = 0x41;            // load NODE 0 control register[7-0]
    CAN_vWriteEN(D0_VALID);

	CAN_vWriteCANAddress(CAN_NECNT0);
	CAN_DATA0 = 0x00;
	CAN_DATA1 = 0x00;
	CAN_DATA2 = 0x60;
	CAN_DATA3 = 0x00;  
	CAN_vWriteEN(ALL_DATA_VALID);

	CAN_vWriteCANAddress(CAN_NCR0); // Addressing CAN_NCR0
    CAN_vReadEN();               // Read Mode is Enabled
    CAN_DATA0  &= ~0x41;         // reset INIT and CCE
    CAN_vWriteEN(D0_VALID); 

}


void Cancel_CAN_vTransmit(ubyte ubObjNr)
{
    CAN_pushAMRegs();    //   PUSH the CAN Access Mediator Register

    CAN_vWriteCANAddress(CAN_MOCTR(ubObjNr));  //Addressing CAN_MOCTR register
    CAN_vWriteCANData(0x00000720);      // set TXRQ,TXEN0,TXEN1,MSGVAL

    CAN_popAMRegs();    //   POP the CAN Access Mediator Register

}

void set_tx_can_dlc(ubyte dlc)
{
    ulong can_dlc;
	can_dlc = dlc;
	can_dlc = (can_dlc << 24);
	CAN_vWriteCANAddress(CAN_MOFCR0);
	can_dlc = (0x00020000)|(can_dlc);
	CAN_vWriteAMData(can_dlc);

}

void Set_TX_CAN_ID(ubyte Func,  ubyte Dev_Type, ubyte TX_ADDR, ubyte RX_ADDR)
{
    ulong can_id_forset;
	ubyte temp_data;
	can_id_forset = 0;


	temp_data = (Func & 0x7F);
	can_id_forset |= temp_data;
	can_id_forset = (can_id_forset << 6);


	temp_data = (Dev_Type & 0x3F);
	can_id_forset |= temp_data;
	can_id_forset = (can_id_forset << 8);



	can_id_forset |= TX_ADDR;

	can_id_forset = (can_id_forset << 8);
	can_id_forset |= RX_ADDR;
	


	CAN_vWriteCANAddress(CAN_MOAR0);
	can_id_forset = (0xE0000000)|(can_id_forset);
	CAN_vWriteAMData(can_id_forset);

}

void Set_RX_CAN_ID(void)
{
    ulong can_id_forset;
	can_id_forset = 0;
	can_id_forset =  DEV_ADDR;
  
	CAN_vWriteCANAddress(CAN_MOAR1);	
	can_id_forset = (0xE03FFE00)|(can_id_forset);
	CAN_vWriteAMData(can_id_forset);

}

void can_tx_status_scan_function(void)
{
    
    if((0 != TX_FIFO_COUNTER)&&(!b_CAN_traning))
	{
	    can_tx_status =  TX_FIFO_FUNC[0];
//		TX_FIFO_COUNTER--;
//		FIFO_displace();
		clear_can_tx_buff_fun();
		T0_5MS_count_heart_information = 0;	   //闲时心跳。每次有数据发送就对心跳周期重新计时。
		switch(can_tx_status)
		{

			case YJ_ID:
			   
			        HEART_INFO[0] =  IDCARD_data[0];
					HEART_INFO[1] =  IDCARD_data[1];
					HEART_INFO[2] =  IDCARD_data[2];
					HEART_INFO[3] =  IDCARD_data[3];
				    

					Set_TX_CAN_ID(33, DEV_TYPE, DEV_ADDR, 0XFE);
					 
				    send_Frame_data_for_can(HEART_INFO, 4);
					can_send_data(4);
				    
				
			    break;
	
		
			case SUCCESS_INPUT:

					//等待补充下放的卡号。

					HEART_INFO[0] =  IDCARD_data[0];
					HEART_INFO[1] =  IDCARD_data[1];
					HEART_INFO[2] =  IDCARD_data[2];
					HEART_INFO[3] =  IDCARD_data[3];


				    Set_TX_CAN_ID(32, DEV_TYPE, DEV_ADDR, 0XFE);
				    send_Frame_data_for_can(HEART_INFO, 4);
					can_send_data(4);
					b_Success_To_Send_Success_Input = 1;
				
			    break;
//			case FAIL_INPUT:
//
//					//等待补充下放失败的卡号
//				    Set_TX_CAN_ID(2, 0, DEV_TYPE, DEV_ADDR, 0XFE);
//				    send_Frame_data_for_can(0x00, HEART_INFO, 4);
//					can_send_data(4);
//				
//			    break;
			case Enable_Input:

					//等待补充下放失败的卡号
				    Set_TX_CAN_ID(37, DEV_TYPE, DEV_ADDR, 0XFE);
				    send_Frame_data_for_can(HEART_INFO, 0);
					can_send_data(0);
				
			    break;
			case HEART_INFORMATION:
			        
					HEART_INFO[0] = UID1;
					HEART_INFO[1] = UID2;
					HEART_INFO[2] = UID3;
					HEART_INFO[3] = UID4;
					HEART_INFO[4] = ub_LoginStatus;
			   
				    Set_TX_CAN_ID(63, DEV_TYPE, DEV_ADDR, 0XFE);
				    send_Frame_data_for_can(HEART_INFO, 5);
					can_send_data(5);
				
			    break;
			case CAN_TX_TimeOut:
			        
	
				    Set_TX_CAN_ID(CAN_TX_TimeOut, DEV_TYPE, DEV_ADDR, 0XFE);
				    send_Frame_data_for_can(error_data, 1);
					can_send_data(1);
				
			    break;
			case Dont_Have_BootLoader:
			        HEART_INFO[0] = 0x01;
				    Set_TX_CAN_ID(Dont_Have_BootLoader, DEV_TYPE, DEV_ADDR, 0XFE);
				    send_Frame_data_for_can(HEART_INFO, 1);
					can_send_data(1);
			    break;
			case Turn_To_BootLoader_APP:

			        HEART_INFO[0] = 0x00;
				    Set_TX_CAN_ID(Turn_To_BootLoader_APP, DEV_TYPE, DEV_ADDR, 0XFE);
				    send_Frame_data_for_can(HEART_INFO, 1);
					can_send_data(1);
					b_Turn_To_BootLoader_Flag = 1;
						    		    
			    break;
			case LCD_KEY_TO_PC:

			        
				    Set_TX_CAN_ID(LCD_Data_To_PC, DEV_TYPE, DEV_ADDR, 0XFE);
				    send_Frame_data_for_can(RS485_LK_buff, (ub_lcd_key_send_pc_number-6));
					can_send_data((ub_lcd_key_send_pc_number-6));
				
						    		    
			    break;
			case test:
			   
				    HEART_INFO[0] = UID1;
					HEART_INFO[1] = UID2;
					HEART_INFO[2] = UID3;
					HEART_INFO[3] = UID4;
					HEART_INFO[4] = ub_LoginStatus;
				    Set_TX_CAN_ID(test, DEV_TYPE, DEV_ADDR, 0XFE);
				    send_Frame_data_for_can(HEART_INFO, 5);
					can_send_data(5);
				
			    break;
		    case CAN_Error:
			   
				    HEART_INFO[0] = CAN_Error_data;
				    Set_TX_CAN_ID(CAN_Error, DEV_TYPE, DEV_ADDR, 0XFE);
				    send_Frame_data_for_can(HEART_INFO, 1);
					can_send_data(1);
				
			    break;
	
			default:
			    can_tx_status = 0;
				b_CAN_traning = 0;
				b_CAN_waiting_interrupt = 0;
				can_traning_frame_number = 1;
				clear_can_tx_buff_fun();
			    break;
		
		}
		if(!b_CAN_Send_Fail_Flag)
		{

		    TX_FIFO_COUNTER--;
		    FIFO_displace();		
		}
		else
		{
			if(can_tx_status == HEART_INFORMATION)
			{
			    TX_FIFO_COUNTER--;
			    FIFO_displace();
			}
		}
		
		b_CAN_Send_Fail_Flag = 0;
	}
    

}




bool compare_command(ubyte tx_function_for_compare)
{
    ubyte i;

	for(i = 0; i < 4; i++)
	{
	  if(TX_FIFO_FUNC[i]  == tx_function_for_compare)
	  {	     
		 return 0;
	  }	
	}	
	return 1;

}

ubyte Find_Heart_Info(void)
{
    ubyte i;
	for(i = 0; i < 4; i++)
	{
	    if(TX_FIFO_FUNC[i]  == HEART_INFORMATION)
	    {		   	     
		   return i;
	    }
	}
	return 0;
}

void can_tx_func_fifo(ubyte tx_function)
{
    if(compare_command(tx_function))
	{
	    if(!Find_Heart_Info())
		{
			if(TX_FIFO_COUNTER < 4)
			{
			    TX_FIFO_FUNC[TX_FIFO_COUNTER] = tx_function;   
				TX_FIFO_COUNTER++; 
			}
			else
			{
			    TX_FIFO_FUNC[3] = tx_function;   
				TX_FIFO_COUNTER = 4;
			}
		}
		else
		{
		     TX_FIFO_FUNC[Find_Heart_Info()] = tx_function; 
		}
		
	}
	
}

void FIFO_displace(void)
{
    ubyte i;
	for(i = 0; i < 3; i++)
	{
	    TX_FIFO_FUNC[0 + i] = TX_FIFO_FUNC[1 + i];
	}
	TX_FIFO_FUNC[3] = 0;
}

void Get_CAN_Data(void)
{
    ubyte temp_can_data, ub_Frame_Number, ub_Frame_High_Number, ub_Frame_Low_Number;
    ubyte ubTempMsgID = 0;
	ubyte ubTempVarObjHandler = 0;
	un_32bit ulBit_Pos_Mask;
	Scan_Hanger();
	CAN_pushAMRegs();              // push the CAN Access Mediator Registers

    SFR_PAGE(_su0, SST0); 


    //   ---------------------------------------------------------------------
    //   Interrupts of CAN Msg Obj x 
    //   ---------------------------------------------------------------------

    CAN_vWriteCANAddress(CAN_MSIMASK);    // set message index mask register
    CAN_DATA0   =   0x06;        // set message index mask register
    CAN_DATA1   =   0x00;        // set message index mask register
    CAN_DATA2   =   0x00;        // set message index mask register
    CAN_DATA3   =   0x00;        // set message index mask register

    CAN_vWriteEN(ALL_DATA_VALID); // Write mode Enabled

    // USER CODE BEGIN (SRN1,1)

    // USER CODE END
    CAN_vWriteCANAddress(CAN_MSID0);   // message index register
    CAN_vReadEN();               // Read Mode is enabled

    ubTempMsgID = CAN_DATA0;

    if(ubTempMsgID != 0x20)
    {
      do
      {
      CAN_vWriteCANAddress(CAN_MOCTR(ubTempMsgID)); // Addressing CAN_MOCTRn
      CAN_vReadEN();               // Read Mode is enabled
      ubTempVarObjHandler = CAN_DATA0;

      ulBit_Pos_Mask.ulVal = ((unsigned long) 1 << ubTempMsgID);
      CAN_vWriteCANAddress(CAN_MSPND0); // Addressing CAN_MSPND0

      CAN_DATA0 = ~ulBit_Pos_Mask.ubDB[3]; // clear message pending register
      CAN_DATA1 = ~ulBit_Pos_Mask.ubDB[2]; // clear message pending register
      CAN_DATA2 = ~ulBit_Pos_Mask.ubDB[1]; // clear message pending register
      CAN_DATA3 = ~ulBit_Pos_Mask.ubDB[0]; // clear message pending register
      CAN_vWriteEN(ALL_DATA_VALID);  // Write mode Enabled



      // USER CODE BEGIN (SRN1_OBJ,1)
	  if( ubTempVarObjHandler & MOSTAT_RXPND)   // if RXPND is set
           {         
             if( ubTempVarObjHandler & MOSTAT_NEWDAT)   // if NEWDAT is set
             {	                				   
				   if(CAN_BYTE_DATA_COUNT > 25)
				   {
				       clear_can_rx_buff_fun();
				   }
				   CAN_vWriteCANAddress(CAN_MODATAL(ubTempMsgID));
				  // CAN_vWriteCANAddress(CAN_MODATAL1);	 		// Show received ADC value on port 3 LED's
	               CAN_vReadEN();
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA0;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA1;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA2;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA3;
				   CAN_BYTE_DATA_COUNT++;
				   ub_Frame_Number                                 =    CAN_DATA0;
				   ub_Frame_High_Number                            =    ((ub_Frame_Number & 0xF0) >> 4);				   
				   ub_Frame_Low_Number							   =   	(ub_Frame_Number & 0x0F);
				   
                   CAN_vWriteCANAddress(CAN_MODATAH(ubTempMsgID));
				  // CAN_vWriteCANAddress(CAN_MODATAH1);	 		// Show received ADC value on port 3 LED's
	               CAN_vReadEN();
				   
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA0;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA1;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA2;
				   CAN_BYTE_DATA_COUNT++;
				   CAN_RX_BUFF[CAN_BYTE_DATA_COUNT]				   =  	CAN_DATA3;
				   CAN_BYTE_DATA_COUNT++;
				   

				   if(ub_Frame_Low_Number == 0)
				   {
				       b_CAN_franme_start = 1;
				   }
				   if(CAN_BYTE_DATA_COUNT != ((ub_Frame_Low_Number * 8) + 8))
				   {
				       b_CAN_franme_start = 0;
					   b_CAN_franme_stop = 0;
					   CAN_BYTE_DATA_COUNT = 0;
					   T0_5MS_count1 = 0;

					   CAN_vWriteCANAddress(CAN_MOAR(ubTempMsgID));					  
		               CAN_vReadEN();
					   RX_CAN_ID_FOR_DEV_ADDR = CAN_DATA0;
		
					   RX_CAN_ID_FOR_DEV_FUN = CAN_DATA3;
	
					   temp_can_data        =  CAN_DATA2;
		
					    RX_CAN_ID_FOR_DEV_FUN &= 0x1F;	
					
						RX_CAN_ID_FOR_DEV_FUN <<= 2;
	
						temp_can_data         &= 0xC0;
	
						temp_can_data         >>= 6;
	
				
					    RX_CAN_ID_FOR_DEV_FUN |= temp_can_data;

						CAN_Error_data =  RX_CAN_ID_FOR_DEV_FUN;
						can_tx_func_fifo(CAN_Error);
					   
				   }
				   if((ub_Frame_High_Number == ub_Frame_Low_Number) && (CAN_BYTE_DATA_COUNT > (ub_Frame_High_Number * 8)) && b_CAN_franme_start)
				   {
					   b_receive_can_frame = 1;
					   b_CAN_franme_stop = 1;
						   
					   CAN_vWriteCANAddress(CAN_MOAR(ubTempMsgID));					  
		               CAN_vReadEN();
					   RX_CAN_ID_FOR_DEV_ADDR = CAN_DATA0;
		
					   RX_CAN_ID_FOR_DEV_FUN = CAN_DATA3;
	
					   temp_can_data        =  CAN_DATA2;
		
					    RX_CAN_ID_FOR_DEV_FUN &= 0x1F;	
					
						RX_CAN_ID_FOR_DEV_FUN <<= 2;
	
						temp_can_data         &= 0xC0;
	
						temp_can_data         >>= 6;
	
				
					    RX_CAN_ID_FOR_DEV_FUN |= temp_can_data;

						CAN_vWriteCANAddress(CAN_MOFCR(ubTempMsgID));					  
		                CAN_vReadEN();
						ub_Frame_Number   =  CAN_DATA3;
						ub_Frame_Number  &=  0x0F;
						CAN_BYTE_DATA_COUNT += 	ub_Frame_Number;
						CAN_BYTE_DATA_COUNT -= 8;
						ub_send_lcd_key_data_number = CAN_BYTE_DATA_COUNT;
						ub_send_lcd_key_data_number -= (ub_Frame_High_Number + 1);


				   }

              }

          
          // Reset RXPND, NEWDAT, MSGLST (if set)
          
            CAN_vWriteCANAddress(CAN_MOCTR(ubTempMsgID)); // Addressing CAN_MOCTRn
          
            CAN_DATA0 = (ubTempVarObjHandler & MOSTAT_RST_MNR); // load CAN Data Register 0
            CAN_DATA1 = 0x00; // load CAN Data Register 1
            CAN_DATA2 = 0x00; // load CAN Data Register 2
            CAN_DATA3 = 0x00; // load CAN Data Register 3
            CAN_vWriteEN(ALL_DATA_VALID);   // Writemode is Enabled
           }

      // USER CODE END

      CAN_vWriteCANAddress(CAN_MSIMASK);    // set message index mask register
      CAN_DATA0  =   0x06;       // set message index mask register
      CAN_DATA1  =   0x00;       // set message index mask register
      CAN_DATA2  =   0x00;       // set message index mask register
      CAN_DATA3  =   0x00;       // set message index mask register

      CAN_vWriteEN(ALL_DATA_VALID); // Write mode Enabled

      // USER CODE BEGIN (SRN1,5)

      // USER CODE END

      CAN_vWriteCANAddress(CAN_MSID0);   // message index register
      CAN_vReadEN();               // Read Mode is enabled
      ubTempMsgID = CAN_DATA0;

      }while (ubTempMsgID != 0x20); // end while

    }  // end if


	SFR_PAGE(_su0, RST0);          // restore the old SCU page

    CAN_popAMRegs();  

}