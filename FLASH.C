#include "MAIN.H"


bit FLASH_Erase (unsigned char code* FlashDstAddr,unsigned char KindOfErase)
{
	volatile bit tmpEA, success;						// bit tmpEA --> overwrites CY ( in KEIL )
														// that's why use second var

	(EA)?(tmpEA = 1,EA=0):(tmpEA = 0);					// save EA bit for restoring at end
														// required by UM
	 ACC = KindOfErase;									// desire MASS or PAGE erase 

	DPTR = (unsigned int) FlashDstAddr;


	MEX1 = 0x02;


	((void (code *) (void)) FLASH_ERASE) ();			// BROM call KEIL



	MEX1 = 0x00;

	success = CY;
	EA = tmpEA;											// restore old EA state either '0' or '1' 
	return(!success);
}

bit FLASH_Prog (ubyte code * DestWordLine, unsigned char NrOfBytes, ubyte xdata *xdata_addr)	
{
	volatile bit tmpEA, success;						// bit tmpEA --> overwrites CY ( in KEIL )
														// that's why use second var

	(EA)?(tmpEA = 1,EA=0):(tmpEA = 0);					// save EA bit for restoring at end
														// required by UM


	MEX1 = 0x02;


	REG[0x0001] = NrOfBytes;							// Number of bytes to be programmed - max. 32 DFLASH

	EO |= 0x01;											// select DPTR1 to hold Buffer Address
	DPTR = xdata_addr;
	EO &= ~(0x01);										// ensure DPTR0 is set as active before leave

	DPTR = (unsigned int)DestWordLine;


	((void (code *) (void)) FLASH_PROG) ();				// BROM call KEIL




	MEX1 = 0x00;

	success = CY;
	EA = tmpEA;											// restore old EA state either '0' or '1' 
	return(!success);
}

void Read_Parameter_To_Ram(void)
{
  
	DFlash_ADDR    =  APP_DATA_StartADDR_At_DFlash;	
	DEV_ADDR         =    *DFlash_ADDR;
	  
	  if(DEV_ADDR < 1 || DEV_ADDR > Max_DevAddr)
	  {
	      DEV_ADDR = 1;
	  }
	
	  
	  DFlash_ADDR++;
	
	  in_out_time[0]   =    *DFlash_ADDR;
	  if(in_out_time[0] > 25)
	  {
	      in_out_time[0] = 2;  
	  }
	  DFlash_ADDR++;
	
	  in_out_time[1]   =    *DFlash_ADDR;
	  if(in_out_time[1] > 25)
	  {
	      in_out_time[1] = 2;
	  
	  }
	  DFlash_ADDR++;
	  in_time_last = *DFlash_ADDR;
	  if((in_time_last < 3)||(in_time_last > 30))
	  {
	      in_time_last  =  20;
	  }
	
	  DFlash_ADDR++;
	  out_time_last = *DFlash_ADDR;
	  if((out_time_last < 3)||(out_time_last > 30))
	  {
	      out_time_last  =  8;
	  }
	  DFlash_ADDR++;

	  ub_RFID_Freq = *DFlash_ADDR;
	  if((ub_RFID_Freq < 3)||(ub_RFID_Freq > 20))
	  {
	      ub_RFID_Freq  =  4;
	  }
	  DFlash_ADDR++;

	  ub_Protect_Too_Long_Hanger = *DFlash_ADDR;
	  if((ub_Protect_Too_Long_Hanger < 10)||(ub_Protect_Too_Long_Hanger > 30))
	  {
	      ub_Protect_Too_Long_Hanger  =  16;
	  }
	  DFlash_ADDR++;

	 // UID1 =  *DFlash_ADDR;
	  UID1 = 0;
	  DFlash_ADDR++;
	  UID2 =  *DFlash_ADDR;
	  DFlash_ADDR++;
	  UID3 =  *DFlash_ADDR;
	  DFlash_ADDR++;
	  UID4 =  *DFlash_ADDR;
	  DFlash_ADDR++;
	  ub_Heart_Info_Period_Time =  *DFlash_ADDR;
	  if((ub_Heart_Info_Period_Time < 1)||(ub_Heart_Info_Period_Time > 20))
	  {
	      ub_Heart_Info_Period_Time  =  5;
	  }

	  DFlash_ADDR++;

	  DFlash_ADDR   =  BootLoader_APP_For_UpAPP_Data_Start_ADDR_At_DFlash;

	  DFlash_ADDR++;

	  DFlash_ADDR++;

	  DFlash_ADDR++;

	  DFlash_ADDR++;
	  ub_Have_BootLoader_APP = *DFlash_ADDR;
	  DFlash_ADDR++;
}
void write_parameter_to_flash(void)
{

	DFlash_ADDR    =  APP_DATA_StartADDR_At_DFlash;
	XDATA_P = For_Program_Flash_Temp_StartADDR_At_XDATA;
	
	*XDATA_P  =	 DEV_ADDR;
	XDATA_P++;
	DFlash_ADDR++;
	
	*XDATA_P  = in_out_time[0];
	XDATA_P++;
	DFlash_ADDR++;
	
	*XDATA_P  = in_out_time[1];
	XDATA_P++;
	DFlash_ADDR++;
	
	*XDATA_P = in_time_last;	
	XDATA_P++;
	DFlash_ADDR++;
	
	
	*XDATA_P = out_time_last;
	XDATA_P++;
	DFlash_ADDR++;

	*XDATA_P = ub_RFID_Freq;
	XDATA_P++;
	DFlash_ADDR++;

	*XDATA_P = ub_Protect_Too_Long_Hanger;
	XDATA_P++;
	DFlash_ADDR++;

	*XDATA_P = UID1;
	XDATA_P++;
	DFlash_ADDR++;

	*XDATA_P = UID2;
	XDATA_P++;
	DFlash_ADDR++;

	*XDATA_P = UID3;
	XDATA_P++;
	DFlash_ADDR++;

	*XDATA_P = UID4;
	XDATA_P++;
	DFlash_ADDR++;

	*XDATA_P = ub_Heart_Info_Period_Time;
	XDATA_P++;
	DFlash_ADDR++;
  
						   			  				  
	FLASH_Erase (APP_DATA_StartADDR_At_DFlash,0);
	Delay_function(600);
	FLASH_Prog (APP_DATA_StartADDR_At_DFlash, 32, For_Program_Flash_Temp_StartADDR_At_XDATA);

}


