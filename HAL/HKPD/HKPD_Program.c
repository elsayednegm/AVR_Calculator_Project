#include"..\..\LIB\LSTD_TYPES.h"
#include"..\..\MCAL\MDIO\MDIO_Interface.h"

#include"HKPD_Private.h"
#include"HKPD_Config.h"
#include"HKPD_Interface.h"



const  u8  ArrayValue[4][4]={
		{'7','4','1','C'}
		,{'8','5','2','0'}
		,{'9','6','3','='}
		,{'/','*','-','+'} ,
};


void HKPD_Vid_Init(void){

	MDIO_Error_State_SetPinDirection(CULM_PIN0 ,CULM_PORT,PIN_INPUT);
	MDIO_Error_State_SetPinDirection(CULM_PIN1 ,CULM_PORT,PIN_INPUT);
	MDIO_Error_State_SetPinDirection(CULM_PIN2 ,CULM_PORT,PIN_INPUT);
	MDIO_Error_State_SetPinDirection(CULM_PIN3 ,CULM_PORT,PIN_INPUT);

//// Active Pull Up Resistor
	MDIO_Error_State_SetPinValue(CULM_PIN0 ,CULM_PORT,PIN_HIGH);
	MDIO_Error_State_SetPinValue(CULM_PIN1 ,CULM_PORT,PIN_HIGH);
	MDIO_Error_State_SetPinValue(CULM_PIN2 ,CULM_PORT,PIN_HIGH);
	MDIO_Error_State_SetPinValue(CULM_PIN3 ,CULM_PORT,PIN_HIGH);




	MDIO_Error_State_SetPinDirection(ROW_PIN0 ,ROW_PORT,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(ROW_PIN1 ,ROW_PORT,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(ROW_PIN2 ,ROW_PORT,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(ROW_PIN3 ,ROW_PORT,PIN_OUTPUT);

	MDIO_Error_State_SetPinValue(ROW_PIN0 ,ROW_PORT,PIN_HIGH);
	MDIO_Error_State_SetPinValue(ROW_PIN1 ,ROW_PORT,PIN_HIGH);
	MDIO_Error_State_SetPinValue(ROW_PIN2 ,ROW_PORT,PIN_HIGH);
	MDIO_Error_State_SetPinValue(ROW_PIN3 ,ROW_PORT,PIN_HIGH);


}
u8 HKPD_U8GetPressedButton(void){
	u8 PressedValue  ;
	u8 ReturnPressedValue=255 ;
	for(u8 row_count=4 ;row_count<8 ;row_count++){

		MDIO_Error_State_SetPinValue(row_count ,ROW_PORT,PIN_LOW);
		for(u8 culm_count=0  ;culm_count<4 ;culm_count++){
			MDIO_Error_State_GetPinValue(culm_count,CULM_PORT,&PressedValue);
			if(PressedValue==0){
				ReturnPressedValue=ArrayValue[row_count-4][culm_count];
				// Write Digit one time in Click Until Release
				while(PressedValue==0){
					MDIO_Error_State_GetPinValue(culm_count,CULM_PORT,&PressedValue);
				}
			}else {


			}
			}

		MDIO_Error_State_SetPinValue(row_count ,ROW_PORT,PIN_HIGH);



	}

	return ReturnPressedValue ;

}

