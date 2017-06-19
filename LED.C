#include "MAIN.H" 

void turn_on_led_1(void)
{
    LED1_PIN = 1;
}

void turn_off_led_1(void)
{
    LED1_PIN = 0;    
}

void turn_on_led_2(void)
{
    LED2_PIN = 1;
}

void turn_off_led_2(void)
{
    LED2_PIN = 0;    
}

void turn_on_led_3(void)
{
    LED3_PIN = 1;
}

void turn_off_led_3(void)
{
    LED3_PIN = 0;    
}

void flash_LED_1(void)
{
    if(T0_5MS_count_led <= 100)
	{
	    turn_on_led_1();    
	}
	else
	{
	    turn_off_led_1();    
	}
}

void flash_LED_2(void)
{
    if(T0_5MS_count_led <= 100)
	{
	    turn_on_led_2();    
	}
	else
	{
	    turn_off_led_2();    
	}
}

void flash_LED_3(void)
{
    if(T0_5MS_count_led <= 100)
	{
	    turn_on_led_3();    
	}
	else
	{
	    turn_off_led_3();    
	}
}

void scan_LED(void)
{
    ubyte status_LED_1, status_LED_2, status_LED_3; 
	status_LED_1 = ((ub_3LED_flash_flag & 0xC0) >> 6);
	status_LED_2 = ((ub_3LED_flash_flag & 0x30) >> 4);
	status_LED_3 = ((ub_3LED_flash_flag & 0x0C) >> 2);
	switch(status_LED_1) 
	{
	    case 0:
		    turn_off_led_1(); 
		    break;
		case 2:
		    turn_on_led_1();   
		    break;
		case 3:
		    flash_LED_1();
		    break;
		default:
		    break;	
	} 
	switch(status_LED_2) 
	{
	    case 0:
		    turn_off_led_2(); 
		    break;
		case 2:
		    turn_on_led_2();   
		    break;
		case 3:
		    flash_LED_2();
		    break;
		default:
		    break;	
	} 
	switch(status_LED_3) 
	{
	    case 0:
		    turn_off_led_3(); 
		    break;
		case 2:
		    turn_on_led_3();   
		    break;
		case 3:
		    flash_LED_3();
		    break;
		default:
		    break;	
	} 
}

