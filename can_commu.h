#ifndef _CAN_COMMU_H_
#define _CAN_COMMU_H_

void Reorganize_CAN_RX_buff_fun(void);
void clear_can_rx_buff_fun(void);
void clear_can_tx_buff_fun(void);
void Recover_CAN_BUS(void);
void Cancel_CAN_vTransmit(ubyte ubObjNr);
void Set_TX_CAN_ID(ubyte Func,  ubyte Dev_Type, ubyte TX_ADDR, ubyte RX_ADDR);
void Set_RX_CAN_ID(void);
void set_tx_can_dlc(ubyte dlc);
void can_tx_status_scan_function(void);
ubyte CAN_createBCC(ubyte Len);
void can_send_data(ubyte frame_number);
void send_command(ubyte send_buff[], ubyte Len);
void can_tx_for_traning(void);
void scan_can_tx_frame(void);
void can_tx_status_traning(void);
void can_tran_complete_for_delay(void);
bool compare_command(ubyte tx_function_for_compare);
ubyte Find_Heart_Info(void);
void can_tx_func_fifo(ubyte tx_function);
void FIFO_displace(void);
void Get_CAN_Data(void);
void send_Frame_data_for_can(ubyte send_data[], ubyte Len);

#endif