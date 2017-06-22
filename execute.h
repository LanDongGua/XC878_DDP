#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#define    OFFSET_TIME_OF_CACULATE_HANG     60
void execute_scan(void);


void dele_id_card_for_input(ubyte id_card[]);

void add_id_card_for_input(ubyte id_card[]);
void clear_id_card_buffer(void);
bool find_will_input_idcard(ubyte id_card[]);
bool find_same_id_card(ubyte id_card[]);

bool find_empty_buff_addrss(void);
void Scan_Hanger(void);



bool compare_id(ubyte idcard[]);


#endif