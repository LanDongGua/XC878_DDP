#include "MAIN.H"

//��ɰ�ťɨ�躯��

void COMPLEGE_DONE_SCAN(void)
{
	//��⵽��ɰ�ť���
//������ ����ɨ���Ƹ�
   // if((b_COMPLETE_DONE_flag))
//   ubyte i;
	if(b_COMPLETE_DONE_flag)
	{
	    b_COMPLETE_DONE_flag    =    0;
		
		T0_5MS_count_complete_scan  =  0;
		
	
			if(b_input_yj_flag_for_have_find_same_idcard && (uw_T0_5MS_count_For_Waiting_Hanger_After_Got_IDCARD < (ub_Protect_Too_Long_Hanger * 50)))
			{
				b_input_yj_flag_for_have_find_same_idcard = 0;  
				uw_T0_5MS_count_For_Waiting_Hanger_After_Got_IDCARD = 0; 
				T0_5MS_count_input = 0;
			    input_yj_flag = 1;  
//				if(UID1 > 0)
//			    {
//			        UID1--;
//			    }
                if(UID3 < 250)
			   {
			       UID3++;
			   }
			   else
			   {
			       UID3 = 0;
			   }
				
				can_tx_func_fifo(SUCCESS_INPUT);
				
			}
			else
			{
			    b_input_yj_flag_for_have_find_same_idcard = 0; 
				uw_T0_5MS_count_For_Waiting_Hanger_After_Got_IDCARD = 0; 

			}	    
	}

	if(b_Success_To_Send_Success_Input)
	{
	    b_Success_To_Send_Success_Input = 0;
		dele_id_card_for_input(ub_ID_To_Dele_For_Input); 
	       
	}
}	   

//��ʱ��ɨ��
void T0_INT_SCAN(void)
{
	//��ʱ���жϱ��
    if(b_T0_5MS_flag)
	{
	    b_T0_5MS_flag    =    0;
		if(b_CAN_franme_start)
		{
			if(T0_5MS_count1 > 250)
			{
			    T0_5MS_count1 = 0;
			}
			else
			{
			    T0_5MS_count1++;
			}
		}
		if(FRAME_start_1)
		{
			if(T0_5MS_IDread_frame_count > 250)
			{
			    T0_5MS_IDread_frame_count = 0;
			}
			else
			{
			    T0_5MS_IDread_frame_count++;
			}
		}

		

		 //�¼ܽ�վ������
		 if(input_yj_flag)
		 {
		     if(T0_5MS_count_input < 60000)
			 {
			     T0_5MS_count_input++;
			 }
			 else
			 {
			     T0_5MS_count_input = 0;
			 }
		     
		 }

		 if(!Key)
		 {
		     if(ub_T0_5MS_count_scan_Key < 250)
			 {
			     ub_T0_5MS_count_scan_Key++;
			 }
			 else
			 {
			     ub_T0_5MS_count_scan_Key = 0;
			 }
		     
		 }

		 if(T0_5MS_count_led < 200)
			 {
			     T0_5MS_count_led++;
			 }
			 else
			 {
			     T0_5MS_count_led = 0;
			 }

		

		 //���Ŷ�������ʱ��������Ƶ��
		
		
		

		 //�¼ܶ�������ʱ��������Ƶ��
	
		     if(T0_5MS_count_YJ_id < 250)
			 {
			     T0_5MS_count_YJ_id++;
			 }
			 else
			 {
			     T0_5MS_count_YJ_id = 0;
			 }
	

		 if(!scan_complete)
		 {
		     if(T0_5MS_count_complete_scan < 250)
			 {
			     T0_5MS_count_complete_scan++;
			 }
			 else
			 {
			     T0_5MS_count_complete_scan = 0;
			 }
		 }

		 if(T0_5MS_count_rs485_lk < 250)
			 {
			     T0_5MS_count_rs485_lk++;
			 }
			 else
			 {
			     T0_5MS_count_rs485_lk = 0;
			 }

		if(uw_T0_5MS_count_For_CheckStation_For_TheSameCard < 60000)
		 {
		     uw_T0_5MS_count_For_CheckStation_For_TheSameCard++;
		 }
		 else
		 {
		     uw_T0_5MS_count_For_CheckStation_For_TheSameCard = 0;
		 }

		 if(b_Waiting_CAN_Send_Interupt_Flag)
		{
			if(T0_5MS_count_Waiting_CAN_Send_INTR_Flag > 250)
			{
			    T0_5MS_count_Waiting_CAN_Send_INTR_Flag = 0;
			}
			else
			{
			    T0_5MS_count_Waiting_CAN_Send_INTR_Flag++;
			}
		}
	/*	 else
		 {
		     T0_5MS_count_complete_scan = 0;
		 }	*/
		 
		 //���һ��ֹͣ��Ӧ������΢����ɨ��
		
	/*	 else
		 {
		     T0_5MS_count_scan_stop_moto_1 = 0;
			 b_stop_moto_1_flag    =    0;
			 T0_5MS_count_stop_moto_delay_1 = 0;
		 } */
		 
	

		 //�������ֹͣ��Ӧ������΢����ɨ��
		
	/*	 else
		 {
		     T0_5MS_count_scan_stop_moto_2 = 0;
			 b_stop_moto_2_flag    =    0;
			 T0_5MS_count_stop_moto_delay_2 = 0;
		 }	 */
		 
	

	
		 if(b_rs_485_2_traning)
		 {
		     if(ub_T0_5MS_count_re_485_2_wait_recieve < 250)
			 {
			     ub_T0_5MS_count_re_485_2_wait_recieve++;
			 }
			 else
			 {
			     ub_T0_5MS_count_re_485_2_wait_recieve = 0;
			 }
		 }

		 if(b_input_yj_flag_for_have_find_same_idcard)
			{
				if(uw_T0_5MS_count_For_Waiting_Hanger_After_Got_IDCARD < 60000)
				 {
				     uw_T0_5MS_count_For_Waiting_Hanger_After_Got_IDCARD++;
				 }
				 else
				 {
				     uw_T0_5MS_count_For_Waiting_Hanger_After_Got_IDCARD = 0;
				 }
			}

		  if(b_Start_Caculate_Hanger)
			{
				if(uw_T0_5MS_Count_For_Record_Hanger_Time < 60000)
				 {
				     uw_T0_5MS_Count_For_Record_Hanger_Time++;
				 }
				 else
				 {
				     uw_T0_5MS_Count_For_Record_Hanger_Time = 0;
				 }

				 if(uw_T0_5MS_Count_For_ADD_Hanger_Time < 60000)
				 {
				     uw_T0_5MS_Count_For_ADD_Hanger_Time++;
				 }
				 else
				 {
				     uw_T0_5MS_Count_For_ADD_Hanger_Time = 0;
				 }
			}

		 	
		
	/*	 if(T0_5MS_count_KEY_SCAN < 250)
		 {
		     T0_5MS_count_KEY_SCAN++;
		 }
		 else
		 {
		     T0_5MS_count_KEY_SCAN = 0;
		 } */
	

			if(b_Enable_Heart_INFO)
			{
				if(T0_5MS_count_heart_information < 60000)
				 {
				     T0_5MS_count_heart_information++;
				 }
				 else
				 {
				     T0_5MS_count_heart_information = 0;
				 }
			}

			
			
	
	}
}







