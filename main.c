#include"LIB\LSTD_TYPES.h"
#include"HAL\HKPD\HKPD_Interface.h"
#include"HAL\HCLCD\HCLCD_Interface.h"
#include<util/delay.h>



// Number of Parameters like 32 + 12  , 32 is a parameter and 12 is anther parameter and + is Math_Parameters

// Max 10 Parameters in one Operation
static u32 Prametars[10] ;

// Number of Parameters like 32 + 112  , 32 has two parameter digit ( 3 is digit equal 30 , 2 is digit ) and 112 has 3 digit
 u8 Prametar_Digit[10] ;

//like + ,- , / , *
 u8 Math_Parameters[10] ;

 //Number of parameters of Operation
 u8 Count_Prametars=0 ;
 //Number of parameter Digit of Operation
 u8 Count_Digit_Prametar=0 ;
 //Number of Math Operators of Operation
 u8 Count_Math_Operators=0 ;
 //Final Result of Operation
 u32 Result=0 ;
u32 HKPD_U8Calculator(u8 Copy_U8Calculate_Result){

	if(Copy_U8Calculate_Result=='C'){
	}
	else if (Copy_U8Calculate_Result=='='||(Copy_U8Calculate_Result=='+')||(Copy_U8Calculate_Result=='-')||(Copy_U8Calculate_Result=='/')||(Copy_U8Calculate_Result=='*')){
		 u32 Prametar=0 ;

						for(u8 i=0 ;i<Count_Digit_Prametar;i++){
							u8 Power=0 ;
							u32 Power_Result =1 ;
							// so 225 => P[0]=2 ==> power= 3-1-0 for first i = 2 ==> so 2 will be 200
							Power=(Count_Digit_Prametar-1)-i;
						    while (Power != 0) {
						    	Power_Result *= 10;
						        --Power;
						    }
							Prametar+=((Prametar_Digit[i])*(Power_Result));
						}

						Prametars[Count_Prametars]=Prametar;
						Count_Prametars++;

						Math_Parameters[Count_Math_Operators]=Copy_U8Calculate_Result;
						Count_Math_Operators++;

						Count_Digit_Prametar=0 ;

						if(Copy_U8Calculate_Result=='='){

							for(u8 i=0 ;i<Count_Math_Operators-1 ;i++){

										switch (Math_Parameters[i])
										{
										case '+':
											Prametars[i+1]=(Prametars[i]+Prametars[i+1]);
											Result=Prametars[i+1];
											break ;
										case '-':
											Prametars[i+1]=(Prametars[i]-Prametars[i+1]);
											Result=Prametars[i+1];
											break ;
										case '/':
											Prametars[i+1] =Prametars[i]/Prametars[i+1];
											Result=Prametars[i+1];
											break ;
										case '*':
											Prametars[i+1] =Prametars[i]*Prametars[i+1];
											Result=Prametars[i+1];
											break ;

										}

									}


						}

	}

		else{
			Prametar_Digit[Count_Digit_Prametar]=Copy_U8Calculate_Result-'0';
			Count_Digit_Prametar++;
		}




	return Result ;
}





int main(void)
{
	// Return of KPad Value ( Pressed Button  )
	u8 LOC_u8KeyValue;

	// Key Pad Initialize
	HKPD_Vid_Init();

	// CLCD Initialize
	HCLCD_Vid8Bits_Init();

	//Print Welcome Message and wait 1s and delete it
	HCLCD_VidWriteString_8Bits("Welcome...");
	_delay_ms(1000);
	HCLCD_VidWriteCommand_8Bits(DISPLAY_CLEAR);


	while(1)
	{
		// Return of KPad Value ( Pressed Button  )
		LOC_u8KeyValue=HKPD_U8GetPressedButton();

		// 255 main No Press
		if(LOC_u8KeyValue!=255)
		{
			// If Press C clear Screen
			if(LOC_u8KeyValue=='C')
			{
				HCLCD_VidWriteCommand_8Bits(DISPLAY_CLEAR);
			}
			// If press = will clear Screen and Print the Result of Operation on screen
			else if(LOC_u8KeyValue=='='){
				// Clear Screen
				HCLCD_VidWriteCommand_8Bits(DISPLAY_CLEAR);
				//Write the Result word in First Line
				HCLCD_VidSetPosition(HCLCD_LINE1,0);
				HCLCD_VidWriteString_8Bits("The Result is : ");
				//Write the Result  in second Line
				HCLCD_VidSetPosition(HCLCD_LINE2,0);
				HCLCD_VidWriteNumber_8Bits(HKPD_U8Calculator(LOC_u8KeyValue));

			}
			else
			{
				// if input is Number or Mathematics operator send to Calculator function
				HKPD_U8Calculator(LOC_u8KeyValue);
				HCLCD_VidWriteChar_8Bits(LOC_u8KeyValue);
			}
		}
		else
		{
			/*Do Nothing*/
		}

	}
	return 0;
}

