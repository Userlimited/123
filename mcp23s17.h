#ifndef _MCP23S17_H_
#define _MCP23S17_H_

typedef enum MCP2317_ePort_t
{
	    MCP2317_ePortA = 0,
		    MCP2317_ePortB,
}   MCP2317_ePort_t;

typedef enum MCP2317_eRW_t
{
	    MCP2317_eRead = 0,
		    MCP2317_eWrite,
}   MCP2317_eRW_t;

typedef enum MCP2317_eCmd_t
{
	    MCP2317_eCmdDirection  =0u,
		    MCP2317_eCmdInputPolarity,
			    MCP2317_eCmdIntOnChange,
				    MCP2317_eCmdCompareDfltValue,
					    MCP2317_eCmdIoControl,
						    MCP2317_eCmdIntControlMode,
							    MCP2317_eCmdPullup,
								    MCP2317_eCmdIntFlag,
									    MCP2317_eCmdGetValueAtInterupt,
										    MCP2317_eCmdPortValue,
											    MCP2317_eCmdPortOutLatchValue,
												    
}   MCP2317_eCmd_t;


bool_t  MCP2317_Open( uint8_t deviceAddr );
bool_t  MCP2317_Cmd( uint8_t deviceAddr, MCP2317_eRW_t  eReadOrWrite, MCP2317_ePort_t  ePort, MCP2317_eCmd_t eCmd, uint8_t* pByte );
bool_t  MCP2317_Close( uint8_t deviceAddr );



bool_t MCP2317_Init( void );
bool_t MCP2317_ReadValue ( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue );
bool_t MCP2317_ReadOutLatchValue( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue );
bool_t MCP2317_WriteValue( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue );

bool_t MCP2317_ReadIntFlag( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue );
bool_t MCP2317_ReadValueAtInterupt( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue );

bool_t MCP2317_SetDirection( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue );
bool_t MCP2317_GetDirection( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue );


#endif //_MCP23S17_H_
