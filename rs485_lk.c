#include "MAIN.H" 

void rs485_lk_scan(void)
{

	ubyte i;

	if(RS485_LK_Frequency <= T0_5MS_count_rs485_lk)
	{
	    T0_5MS_count_rs485_lk = 0;	
		if(b_have_LCD_KEY_DATA)
		{
		    b_check_have_lcd_key = 0;
		    ub_LoginStatus &= 0xBF;
		}
		b_have_LCD_KEY_DATA = 1;
		if(!b_check_have_lcd_key)
		{
		    rs_485_2_tx_func_fifo(HELLO);	    
		}
		else
		{
			rs_485_2_tx_func_fifo(ASK);
		}
	    		
	}  

    

	
	if(FRAME_start_rs485_lk&&(!FRAME_end_rs485_lk)&&(16 <= T0_5MS_rs485_lk_frame_count))
    {
        T0_5MS_rs485_lk_frame_count  =    0;
		byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;

	  
	    return;
  //�˺���Ϊ�жϣ��յ�֡ͷ���м���10ms����û���յ�֡β��˵��ͨ�Ŵ���
    }
	if(!FRAME_end_rs485_lk)
    {
      return;
    }
	b_rs_485_2_traning = 0;
	ub_T0_5MS_count_re_485_2_wait_recieve = 0;
	
	FRAME_end_rs485_lk = 0;
	T0_5MS_rs485_lk_frame_count = 0;
//	T0_5MS_count_rs485_lk_b_flag_time = 0;

	if(26 < byte_count_rs485_lk)
    {
        byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;
		
	    return;
  
    }
	if(7 > byte_count_rs485_lk)
    {
        byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;
	  
	    return;  
    }
/*	if(!check_BCC_rs485_lk(byte_count_rs485_lk-7))
	{
	    byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;
	  
	    return;    
	
	}				 
	byte_count_rs485_lk = 0;
    FRAME_start_rs485_lk = 0;
    FRAME_end_rs485_lk   = 0;	*/

	if(RS485_LK_buff[1] != 0x13)
	{
	    byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;
		b_check_have_lcd_key = 0;
		ub_LoginStatus &= 0xBF;
	  
	    return; 
	}

	
	if(RS485_LK_buff[2] != 1)
	{
	    byte_count_rs485_lk = 0;
	    FRAME_start_rs485_lk = 0;
	    FRAME_end_rs485_lk   = 0;
		b_check_have_lcd_key = 0;
		ub_LoginStatus &= 0xBF;
		rs_485_2_tx_func_fifo(SET_TEMP_ADDR);	
	  
	    return; 
	}
	b_check_have_lcd_key = 1;
	ub_LoginStatus |= 0x40;
	b_have_LCD_KEY_DATA = 0;
	
	if((RS485_LK_buff[3] != ANS) && (RS485_LK_buff[3] != ACT))
	{
	    for(i = 0; i < (ub_lcd_key_send_pc_number-6); i++)
		{
		    RS485_LK_buff[i] = RS485_LK_buff[i + 3];
		}

		if(RS485_LK_buff[0] != PgDnToPC)  
		{
		    can_tx_func_fifo(LCD_KEY_TO_PC);   
		}
		else
		{
		    if((byte_count_rs485_lk > 10) && (RS485_LK_buff[1] == RS485_LK_buff[2]) && (RS485_LK_buff[1] == 0x2A) && ((RS485_LK_buff[3] <= 0x32) && (RS485_LK_buff[3] >= 0x30)) && ((RS485_LK_buff[4] <= 0x39) && (RS485_LK_buff[4] >= 0x30)) && ((RS485_LK_buff[5] <= 0x39) && (RS485_LK_buff[5] >= 0x30)))
			{
			    if(((RS485_LK_buff[3] == 0x32) && (RS485_LK_buff[4] > 0x35)) || ((RS485_LK_buff[3] == 0x32) && (RS485_LK_buff[4] == 0x35) && (RS485_LK_buff[5] > 0x34)) || ((RS485_LK_buff[3] == 0x30) && (RS485_LK_buff[4] == 0x30) && (RS485_LK_buff[5] == 0x30)))
				{
				    can_tx_func_fifo(LCD_KEY_TO_PC); 
				}
				else
				{
					DEV_ADDR =  ASC_TurnTO_Hex(RS485_LK_buff[3]);
				    DEV_ADDR *= 100;
				    DEV_ADDR +=  (ASC_TurnTO_Hex(RS485_LK_buff[4]) * 10);
					DEV_ADDR +=  ASC_TurnTO_Hex(RS485_LK_buff[5]);
				    write_parameter_to_flash();                 			      				  		  				 				 				  		
					For_Set_Addr_Display_Func(DEV_ADDR);	
					rs_485_2_tx_func_fifo(DISPLAY_LCD_ONE_LINE_For_Set_ADDR); 
				}
			    			
			}
		
			can_tx_func_fifo(LCD_KEY_TO_PC);   
			
		}
	   
	    //b_have_LCD_KEY_DATA = 1;   
	//	can_tx_func_fifo(LCD_KEY_TO_PC);    		 
	}
    

	
	


}
//	   �쿨�Ƚ�



ubyte createBCC_rs485_lk(ubyte Len)
{
       ubyte BCC_data = 0x55; 
	ubyte i;
	
	if(Len > 19)
	{
	    return BCC_data;
	}
	
	BCC_data = RS485_LK_buff[0];
	
	for(i = 1; i < (Len + 4); i++)	  //DATA�ĳ��ȼ���ǰ���4���ֽڣ�ͷ�����ͣ���ַ��FC���͡�
	{
	    BCC_data    ^=    RS485_LK_buff[i];	    	    
	}

	return BCC_data;
}

/****   ��װ���Ͱ� ***********
�������Ϊ���������ͣ�DATA�������ڵ����飬DATA���ݵĳ���
����λ��ͨ��ʹ��
 *********/
void send_Frame_data_rs485_lk(ubyte FC_data, ubyte DEV_TYPE_RS485_LK_SLAVE, ubyte DEV_ADDR_RS485_LK_SLAVE, ubyte send_data[], ubyte Len)
{
	ubyte i,BCC_DATA,  BCC1_DATA,  BCC2_DATA;
	  
	//��������
	if(Len > 19)
	{
	    Len = 19;
	}
	
    RS485_LK_buff[0]  =    Fram_Head;    //��ͷ
	RS485_LK_buff[1]  =    DEV_TYPE_RS485_LK_SLAVE;     //����
	RS485_LK_buff[2]  =    DEV_ADDR_RS485_LK_SLAVE;   //��ַ
	RS485_LK_buff[3]  =    FC_data;      //����

	//����
	for(i = 0; i < Len; i++)
	{	    	    
	    RS485_LK_buff[i+4]  =  send_data[i]; 		
	}

	BCC_DATA = 	createBCC_rs485_lk(Len);	   //ΪҪ���͵����ݲ���BCC����ת��2���ֽڵ��ַ���BCC1��BCC2
	
	//BCCת��
	BCC1_DATA = Hex_TurnTO_ASC((BCC_DATA&0xF0)>>4);

	RS485_LK_buff[Len + 4] = BCC1_DATA;

	BCC2_DATA = Hex_TurnTO_ASC(BCC_DATA&0x0F);
	RS485_LK_buff[Len + 5] = BCC2_DATA;
	RS485_LK_buff[Len + 6] = Fram_End;	   //���ݽ�����
}





