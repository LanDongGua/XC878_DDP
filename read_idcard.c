#include "MAIN.H" 

//读卡器扫描
void Idreader_scan(void)
{

	bool have_id_data_temp;
	have_id_data_temp    =    0;
	  //
	  if(((ub_RFID_Freq * 50) <= T0_5MS_count_YJ_id))
	 // if(Hanger_RFID_Frequency <= T0_5MS_count_YJ_id)
	  {
	      T0_5MS_count_YJ_id = 0;
		  rs_485_2_tx_func_fifo(READ_ID_READER);	    
	  }	
	  

	  if(FRAME_start_1&&(!FRAME_end_1)&&(8 <= T0_5MS_IDread_frame_count))
	  {
	      T0_5MS_IDread_frame_count = 0;
	      byte_count_1     =    0;
		  FRAME_end_1      =  0;
		  FRAME_start_1    =    0;
	      return;
	  }
	  if(!FRAME_end_1)
	  {
	      return;
	  }
	  b_rs_485_2_traning = 0;
	  ub_T0_5MS_count_re_485_2_wait_recieve = 0;
	  T0_5MS_IDread_frame_count  =  0;
	  FRAME_end_1      =    0; 
	  if(byte_count_1 < 16)
	  {	      
		  FRAME_end_1       =    0;	
		  FRAME_start_1     =    0;
		  byte_count_1      =    0;
		  return;
	  }
	        	      
      if(check_BCC_1(byte_count_1 - 7))
	  {
	      //	T0_5MS_count_input = 0;
		   // input_yj_flag = 1; 
	       
				IDCARD_data[0] =  ASC_TurnTO_Hex(send_data[5]);
				IDCARD_data[0] <<= 4;
				IDCARD_data[0] +=  ASC_TurnTO_Hex(send_data[6]);
				
				IDCARD_data[1] =  ASC_TurnTO_Hex(send_data[7]);
				IDCARD_data[1] <<= 4;
				IDCARD_data[1] +=  ASC_TurnTO_Hex(send_data[8]);
				
				IDCARD_data[2] =  ASC_TurnTO_Hex(send_data[9]);
				IDCARD_data[2] <<= 4;
				IDCARD_data[2] +=  ASC_TurnTO_Hex(send_data[10]);
				
				IDCARD_data[3] =  ASC_TurnTO_Hex(send_data[11]);
				IDCARD_data[3] <<= 4;
				IDCARD_data[3] +=  ASC_TurnTO_Hex(send_data[12]);	
			  have_id_data = 1;
			  if(STATION_type == check_station)
			  {
			      if(cmopare_IDcard(IDCARD_data, ub_ID_To_Dele_For_Input))
				  {
					  can_tx_func_fifo(YJ_ID);
					  ub_ID_To_Dele_For_Input[0] =  IDCARD_data[0];
	
					  ub_ID_To_Dele_For_Input[1] =  IDCARD_data[1];
	
					  ub_ID_To_Dele_For_Input[2] =  IDCARD_data[2];
	
					  ub_ID_To_Dele_For_Input[3] =  IDCARD_data[3];

					  uw_T0_5MS_count_For_CheckStation_For_TheSameCard = 0;
					  if(UID4 < 250)
				   {
				       UID4++;
				   }
				   else
				   {
				       UID4 = 0;
				   }
			
				  }
				  else
				  {
				      if(uw_T0_5MS_count_For_CheckStation_For_TheSameCard > 600)
					  {
					      can_tx_func_fifo(YJ_ID);    
						  uw_T0_5MS_count_For_CheckStation_For_TheSameCard = 0;	
						  if(UID4 < 250)
				   {
				       UID4++;
				   }
				   else
				   {
				       UID4 = 0;
				   }				
					  }
				  }
				  
			  }
			  else
			  {
			      if(cmopare_IDcard(IDCARD_data, ub_ID_To_Dele_For_Input))
				  {
				      
					    if(UID2 < 250)
					   {
					       UID2++;
					   }
					   else
					   {
					       UID2 = 0;
					   }
				        ub_ID_To_Dele_For_Input[0] =  IDCARD_data[0];
	
						ub_ID_To_Dele_For_Input[1] =  IDCARD_data[1];
	
						ub_ID_To_Dele_For_Input[2] =  IDCARD_data[2];
	
						ub_ID_To_Dele_For_Input[3] =  IDCARD_data[3];
	
	//					if(compare_id(id_for_card_buffer))
	//					{
	//					    b_input_yj_flag_for_have_find_same_idcard = 1;
	//						test_id_card[0] =   0xff;
	//					  test_id_card[1] =   0xff;
	//					  test_id_card[2] =   0xff;
	//					  test_id_card[3] =   0xff;
	//					}
						if(find_will_input_idcard(ub_ID_To_Dele_For_Input))
						{
						    if(b_InPut_Enable)
							{
								b_input_yj_flag_for_have_find_same_idcard = 1;
								uw_T0_5MS_count_For_Waiting_Hanger_After_Got_IDCARD = 0;
							//	b_COMPLETE_DONE_flag = 1;							
								
								//dele_id_card_for_input(id_for_card_buffer);
							}					
						} 
						else
						{
						    b_input_yj_flag_for_have_find_same_idcard = 0;
						} 
				  }
			      

			  }
		  
		 	      
	  }
	  else
	  {		 
		  byte_count_1     =    0;
		  FRAME_end_1      =  0;
		  FRAME_start_1    =    0;	  	  
	  }	  	  
}		 	


//	   异卡比较

bool cmopare_IDcard(ubyte A_Block[], ubyte B_Block[])
{
    ubyte i;
	for(i = 0; i < 4; i++)
	{
	    if(A_Block[i] != B_Block[i])
		{
		    return 1;
		} 
	}
	return 0;

}


/****   组装发送包  *********/
void send_IdReader_Frame(ubyte ID_data, ubyte FC_data, ubyte IdReaer_data[], ubyte Len)
{
    ubyte i,BCC_DATA,  BCC1_DATA,  BCC2_DATA;
	if(Len > 9)
	{
	    Len = 9;
	}
    send_data[0]  =   Fram_Head_1_MtoS;
	send_data[1]  =    'A';
	send_data[2]  =    ID_data;
	send_data[3]  =    FC_data;
	for(i = 0; i < Len; i++)
	{
	   
	    send_data[i+4]  =  IdReaer_data[i];  
	}

	BCC_DATA = 	createBCC_1(Len);
	BCC1_DATA = Hex_TurnTO_ASC((BCC_DATA&0xF0)>>4);

	send_data[Len + 4] = BCC1_DATA;

	BCC2_DATA = Hex_TurnTO_ASC(BCC_DATA&0x0F);
	send_data[Len + 5] = BCC2_DATA;
	send_data[Len + 6] = Fram_End_1;    
}




