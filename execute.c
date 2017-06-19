#include "MAIN.H" 

void dele_id_card_for_input(ubyte id_card[])
{
    ubyte id_1, id_2, id_3, id_4, i;
	p_ID_card_buffer = ID_CARD_StartADDR_At_XDATA;

	for(i = 0; i < 200; i++)
	{	    
	    id_1 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_2 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_3 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_4 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		if((id_1 == id_card[0])&&(id_2 == id_card[1])&&(id_3 == id_card[2])&&(id_4 == id_card[3]))
		{
		    p_ID_card_buffer = (p_ID_card_buffer - 4);
	
			*p_ID_card_buffer = 0xFF;
			p_ID_card_buffer++;

			*p_ID_card_buffer = 0xFF;
			p_ID_card_buffer++;

			*p_ID_card_buffer = 0xFF;
			p_ID_card_buffer++;

			*p_ID_card_buffer = 0xFF;
			p_ID_card_buffer++;						    
		}			
	}
}
 

void add_id_card_for_input(ubyte id_card[])
{
    ubyte id_1, id_2, id_3, id_4, i;
	p_ID_card_buffer = ID_CARD_StartADDR_At_XDATA;
	
    if(find_same_id_card(id_card))
	{
		if(find_empty_buff_addrss())
		{
//		    if(UID1 < 250)
//			{
//				UID1++;
//			}
		    
		   	
			for(i = 0; i < 200; i++)
			{	    
			    id_1 = 	*p_ID_card_buffer;
				p_ID_card_buffer++;
				
				id_2 = 	*p_ID_card_buffer;
				p_ID_card_buffer++;
				
				id_3 = 	*p_ID_card_buffer;
				p_ID_card_buffer++;
				
				id_4 = 	*p_ID_card_buffer;
				p_ID_card_buffer++;
				if((id_1 == 0xFF)&&(id_2 == 0xFF)&&(id_3 == 0xFF)&&(id_4 == 0xFF))
				{
				    p_ID_card_buffer = (p_ID_card_buffer - 4);
					
					*p_ID_card_buffer = id_card[0];
					p_ID_card_buffer++;
					
					*p_ID_card_buffer = id_card[1];
					p_ID_card_buffer++;
					
					*p_ID_card_buffer = id_card[2];
					p_ID_card_buffer++;
					
					*p_ID_card_buffer = id_card[3]; 
					p_ID_card_buffer++; 
					break; 
				}
			
			}	    		
		}
	}    	  
} 


bool find_will_input_idcard(ubyte id_card[])
{
    ubyte id_1, id_2, id_3, id_4, i;
	p_ID_card_buffer = ID_CARD_StartADDR_At_XDATA;

	for(i = 0; i < 200; i++)
	{	    
	    id_1 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_2 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_3 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_4 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		if((id_1 == id_card[0])&&(id_2 == id_card[1])&&(id_3 == id_card[2])&&(id_4 == id_card[3]))
		{
		    return 1;
		}	
	}
	return 0;
}



bool find_same_id_card(ubyte id_card[])
{
    ubyte id_1, id_2, id_3, id_4, i;
	p_ID_card_buffer = ID_CARD_StartADDR_At_XDATA;

	for(i = 0; i < 200; i++)
	{	    
	    id_1 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_2 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_3 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_4 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		if((id_1 == id_card[0])&&(id_2 == id_card[1])&&(id_3 == id_card[2])&&(id_4 == id_card[3]))
		{
		    return 0;
		}
		
	
	}
	return 1;

}





bool find_empty_buff_addrss(void)
{
    
    ubyte id_1, id_2, id_3, id_4, i;
	p_ID_card_buffer = ID_CARD_StartADDR_At_XDATA;
	for(i = 0; i < 200; i++)
	{	    
	    id_1 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_2 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_3 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
		
		id_4 = 	*p_ID_card_buffer;
		p_ID_card_buffer++;
	
		if((id_1 == 0xFF)&&(id_2 == 0xFF)&&(id_3 == 0xFF)&&(id_4 == 0xFF))
		{
		    return 1;
		}
	
	}
	return 0;

}


			
void clear_id_card_buffer(void)
{
    uword i;
	p_ID_card_buffer = ID_CARD_StartADDR_At_XDATA;
	for(i = 0; i < 800; i++ )
	{
	    *p_ID_card_buffer = 0xFF;
		p_ID_card_buffer++;
	}
}

void Scan_Hanger(void)
{
    if((!scan_complete)&&(T0_5MS_count_complete_scan >= 2) && (!b_Complete_Done_Key_Have_Done))
	  {
	      b_COMPLETE_DONE_flag    =    1; 
		  b_Complete_Done_Key_Have_Done = 1;
		  T0_5MS_count_complete_scan = 0;  
		  ub_Soft_Complete_Count = 0;
		  if(b_Start_Caculate_Hanger)
		  {
		      if(0 == uw_Have_Hanger_By_Soft)
			  {
			      uw_Have_Hanger_By_Soft = 	 (uw_T0_5MS_Count_For_Record_Hanger_Time + 20);    
			  }
			  else 
			  {
			      if((uw_T0_5MS_Count_For_Record_Hanger_Time < uw_Have_Hanger_By_Soft))
				  {
					  uw_Have_Hanger_By_Soft = 	 (uw_T0_5MS_Count_For_Record_Hanger_Time + 20);
				  }			      
			  }		     		      
		  }
		  b_Start_Caculate_Hanger = 1;  
		  uw_T0_5MS_Count_For_Record_Hanger_Time = 0;  
		  uw_T0_5MS_Count_For_ADD_Hanger_Time = 0;  
	  }
	if(scan_complete)
	{
	    b_Complete_Done_Key_Have_Done = 0; 
	}

	if(uw_T0_5MS_Count_For_ADD_Hanger_Time > uw_Have_Hanger_By_Soft)
	{
	    b_COMPLETE_DONE_flag = 1;
		uw_T0_5MS_Count_For_ADD_Hanger_Time = 20;
		ub_Soft_Complete_Count++;
	}
	if(ub_Soft_Complete_Count > 4)
	{
	  //  b_Start_Caculate_Hanger = 0;    
		ub_Soft_Complete_Count = 0;
	}

}


//扫描执行动作函数
void execute_scan(void)
{
   
	//进站动作命令标识
	if(input_yj_flag)
	{
	    
		

		//进站延时，按100ms单位计算,5ms为计算尺度。
		//比如1S延时，10 *20 = 200.   200*5 = 1000ms
		if((in_out_time[0] * 20) <= T0_5MS_count_input)
		{
			//进站动作
			INPUT_YJ_ENABLE    =    1;
//			OUTPUT_YJ_ENABLE = 1;

			//持续时间后撤销进站动作
			if(((in_time_last*20) + (in_out_time[0]*20)) <= T0_5MS_count_input)
			{	  
				T0_5MS_count_input =    0;
				input_yj_flag      =    0;
				
				INPUT_YJ_ENABLE    =    0;
//				OUTPUT_YJ_ENABLE = 0;
				
			}		     
		}
	}
	
	 
	  if((!Key)&&(ub_T0_5MS_count_scan_Key >= 2))
	  {
	      b_Key_Flag = 1;
		  ub_T0_5MS_count_scan_Key = 0;
		 
	  }
	  if((b_Key_Flag)&&(Key))
	  {
			b_InPut_Enable = 1;
			ub_T0_5MS_count_scan_Key = 0;
			b_Key_Flag    =    0;
			 
			can_tx_func_fifo(Enable_Input);
			
			
	  }	 



	

}