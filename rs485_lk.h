#ifndef _RS485_LK_H_
#define _RS485_LK_H_


#define  RS485_LK_Frequency    80 

#define  CLEAR_LCD                  0x90
#define  DISPLAY_LCD_ONE_LINE              0x31
#define  CLEAR_LCD_ONE_LINE                0x32
#define  LOCK_KEY                          0x33
#define  UNLOCK_KEY                        0x34
#define  EDIT_INIT_PAGE                    0x35
#define  SET_TEMP_ADDR        0x71		 //lcd链接站位板的时候，因为只连着一块，每次开机的时候，临时设置他的地址为站位地址.为了不和flash里的地址冲突。
#define  Toggle_485_232                    0x3A
#define  DISPLAY_LCD_ONE_LINE_For_Set_ADDR                    0x3B


#define  LCD_KEY_TO_PC        0x72

#define  EnterToPC          0x15
#define  MenuToPC           0x16
#define  SwitchToPC         0x10
#define  BackToPC           0x17
#define  PgUpToPC           0x11
#define  LogOutToPC         0x14
#define  LogInToPC          0x13
#define  PgDnToPC           0x12



void rs485_lk_scan(void);
bool cmopare_IDcard_for_rs485_lcd_key(void);
ubyte createBCC_rs485_lk(ubyte Len);
void send_Frame_data_rs485_lk(ubyte FC_data, ubyte DEVE_TYPE_RS485_LK, ubyte DEV_ADDR_RS485_LK, ubyte send_data[], ubyte Len);
void send_command_rs485_lk(ubyte send_buff[], ubyte Len);
void rs_485_2_tx_func_fifo(ubyte tx_function);
void rs_485_2_FIFO_displace(void);
#endif