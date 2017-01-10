/*********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/**********************************************************************************************************
 *  B. APP sepecific Includes
*********************************************************************************************************/
#include "devmoncfg.h"
#include "mcp23s17.h"

/**********************************************************************************************************
 *  C. Object like Macro
*********************************************************************************************************/

/********************************
  For banked setting is clear, i.e. (to one signel 16bit bank) mode only
  *******************************/
  
// IO Direction REG
#define  MCP2317_REG_IODIRA     0x00    
#define  MCP2317_REG_IODIRB     0x01

// Input Polarity REG
#define  MCP2317_REG_IPOLA      0x02    
#define  MCP2317_REG_IPOLB      0x03

// Interrupt On Change REG
#define  MCP2317_REG_GPINTENA   0x04    
#define  MCP2317_REG_GPINTENB   0x05

// Default Compare Register for Interrupt On Change REG
#define  MCP2317_REG_DEFVALA    0x06   
#define  MCP2317_REG_DEFVALB    0x07

// Interrupt Control REG
#define  MCP2317_REG_INTCONA    0x08    
#define  MCP2317_REG_INTCONB    0x09

// I/O Expander Configuration REG
#define  MCP2317_REG_IOCONA     0x0A    
#define  MCP2317_REG_IOCONB     0x0B
    #define CMP2317_REG_IOCON_MULTIPLE_BANK     0x80u
    #define CMP2317_REG_IOCON_SINGLE_BANK       0x00u
    
    #define CMP2317_REG_IOCON_INT_MIRROR_SET    0x40u
    #define CMP2317_REG_IOCON_INT_MIRROR_CLEAR  0x00u
    
    #define CMP2317_REG_IOCON_SEQOP             0x20u
    #define CMP2317_REG_IOCON_NON_SEQOP         0x00u
    
    #define CMP2317_REG_IOCON_DIS_SLEW_RATE     0x10u
    #define CMP2317_REG_IOCON_EN_SLEW_RATE      0x00u
    
    #define CMP2317_REG_IOCON_EN_HW_ADDR        0x08u
    #define CMP2317_REG_IOCON_DIS_HW_ADDR       0x00u
    
    #define CMP2317_REG_IOCON_EN_OPEN_DRAIN     0x04u
    #define CMP2317_REG_IOCON_DIS_OPEN_DRAIN    0x00u
    
    #define CMP2317_REG_IOCON_EN_INT_OUT        0x02u
    #define CMP2317_REG_IOCON_DIS_INT_OUT       0x00u
    
    /* Bit7: Bank: control how the registers are addressed.
             1= the register associated with each port are separated into different banks.
             0= the registers are in the same bank. (addresses are sequential)
       Bit6: Mirror: INT Pins Mirror bit
             1= The INT pints are internally connected.
             0= the INT pins are not connected. INTA is associated with PORTA and INTB is associated with PortB.
       Bit5: SEQOP: Seuential Operation mode bit.
             1=Sequential operation disabled. address pointer does not increment.
             0= sequential operation enabled. address pointer increments.
       Bit4: DISSLW: Slew Rate control bit for SDA output.
             1=Slew rate disabled.
             0=Slew rate enabled.
        bit3: HAEN: Hardware Address Enable bit (MCP23S17 only).
              Address pins are always enabled on MCP23017.
              1 = Enables the MCP23S17 address pins.
              0 = Disables the MCP23S17 address pins.
        bit2: ODR: This bit configures the INT pin as an open-drain output.
              1 = Open-drain output (overrides the INTPOL bit).
              0 = Active driver output (INTPOL bit sets the polarity).
        bit1: INTPOL: This bit sets the polarity of the INT output pin.
              1 = Active-high.
              0 = Active-low.
        bit0: Unimplemented: Read as ‘0’. */

//PULL-UP resistor configuration register
// 1=Pull-up Enabled. 
// 0=Pull-up Disabled.
#define  MCP2317_REG_GPPUA      0x0C
#define  MCP2317_REG_GPPUB      0x0D

/* Interrupt Flag Register.
   1=Pin caused interrupt.
   0=interrupt not pending. */
#define  MCP2317_REG_INTFA      0x0E
#define  MCP2317_REG_INTFB      0x0F

/* Interrupt Capature Register
   1=Logic-High.
   0=Logic-Low */
#define  MCP2317_REG_INTCAPA    0x10
#define  MCP2317_REG_INTCAPB    0x11

/* Port Register.
   1=Logic-High.
   0=Logic-Low */
#define  MCP2317_REG_GPIOA      0x12
#define  MCP2317_REG_GPIOB      0x13

/* Output Latch Register.
   1=Logic-High.
   0=Logic-Low */
#define  MCP2317_REG_OLATA      0x14   
#define  MCP2317_REG_OLATB      0x15

#define  MCP2317_SPI_CHANNEL     1u

/**********************************************************************************************************
 *  D. Function like Macro
*********************************************************************************************************/


/**********************************************************************************************************
 *  E. Type defines
**********************************************************************************************************/



/**********************************************************************************************************
 *  F. Local Function Declarations
**********************************************************************************************************/




/**********************************************************************************************************
 *  G. Local Object/Variable
*********************************************************************************************************/

const int       mcp2317_spiChannel  = 0;

/**********************************************************************************************************
 *  h. Exported Object/Variable
*********************************************************************************************************/
 
 
/**********************************************************************************************************
 *  I. Local Function Implementations
**********************************************************************************************************/

static  bool_t mcp2317_getRegAddress( MCP2317_eCmd_t eCmd, MCP2317_ePort_t ePort, uint8_t* pRegAddr )
{
    bool_t  bRet = TRUE;
    uint8_t regByte;

    if( MCP2317_ePortA == ePort )
    {
        switch( eCmd )
        {
            case MCP2317_eCmdDirection:             regByte = MCP2317_REG_IODIRA;    break;
            case MCP2317_eCmdInputPolarity:         regByte = MCP2317_REG_IPOLA;     break;
            case MCP2317_eCmdIntOnChange:           regByte = MCP2317_REG_GPINTENA;  break;
            case MCP2317_eCmdCompareDfltValue:      regByte = MCP2317_REG_DEFVALA;   break;
            case MCP2317_eCmdIoControl:             regByte = MCP2317_REG_IOCONA;    break;
            case MCP2317_eCmdIntControlMode:        regByte = MCP2317_REG_INTCONA;   break;
            case MCP2317_eCmdPullup:                regByte = MCP2317_REG_GPPUA;     break;
            case MCP2317_eCmdIntFlag:               regByte = MCP2317_REG_INTFA;     break;
            case MCP2317_eCmdGetValueAtInterupt:    regByte = MCP2317_REG_INTCAPA;   break;
            case MCP2317_eCmdPortValue:             regByte = MCP2317_REG_GPIOA;     break;
            case MCP2317_eCmdPortOutLatchValue:     regByte = MCP2317_REG_OLATA;     break;
            default:  bRet = FALSE; break;
        }   
    }
    else if( MCP2317_ePortB == ePort )
    {
        switch( eCmd )
        {
            case MCP2317_eCmdDirection:             regByte = MCP2317_REG_IODIRB;    break;
            case MCP2317_eCmdInputPolarity:         regByte = MCP2317_REG_IPOLB;     break;
            case MCP2317_eCmdIntOnChange:           regByte = MCP2317_REG_GPINTENB;  break;
            case MCP2317_eCmdCompareDfltValue:      regByte = MCP2317_REG_DEFVALB;   break;
            case MCP2317_eCmdIoControl:             regByte = MCP2317_REG_IOCONB;    break;
            case MCP2317_eCmdIntControlMode:        regByte = MCP2317_REG_INTCONB;   break;
            case MCP2317_eCmdPullup:                regByte = MCP2317_REG_GPPUB;     break;
            case MCP2317_eCmdIntFlag:               regByte = MCP2317_REG_INTFB;     break;
            case MCP2317_eCmdGetValueAtInterupt:    regByte = MCP2317_REG_INTCAPB;   break;
            case MCP2317_eCmdPortValue:             regByte = MCP2317_REG_GPIOB;     break;
            case MCP2317_eCmdPortOutLatchValue:     regByte = MCP2317_REG_OLATB;     break;
            default:  bRet = FALSE; break;
        }   
    }
    else
    {
        bRet = FALSE;
    }
    
    if( ( bRet ) &&
        ( pRegAddr != NULL ))
    {
        *pRegAddr = regByte;
    }
    
    return bRet;
}

/**********************************************************************************************************
 *  J. Public Function Implementations
*********************************************************************************************************/


bool_t  MCP2317_Open( uint8_t deviceAddr )
{
    uint8_t  controlCfg = 
          CMP2317_REG_IOCON_SINGLE_BANK
        | CMP2317_REG_IOCON_INT_MIRROR_SET
        | CMP2317_REG_IOCON_SEQOP
        | CMP2317_REG_IOCON_DIS_SLEW_RATE
        | CMP2317_REG_IOCON_EN_HW_ADDR
        | CMP2317_REG_IOCON_EN_OPEN_DRAIN
        | CMP2317_REG_IOCON_EN_INT_OUT ;
    // IO Control Register Settings.
    MCP2317_Cmd( deviceAddr, MCP2317_eWrite, MCP2317_ePortA, MCP2317_eCmdIoControl, &controlCfg );
    MCP2317_Cmd( deviceAddr, MCP2317_eWrite, MCP2317_ePortB, MCP2317_eCmdIoControl, &controlCfg );
    
}

bool_t  MCP2317_Cmd( uint8_t            deviceAddr,
                     MCP2317_eRW_t      eReadOrWrite, 
                     MCP2317_ePort_t    ePort, 
                     MCP2317_eCmd_t     eCmd, 
                     uint8_t*           pByte )
{
    bool_t   bRet;
    uint8_t  buff[3];
    uint8_t  regByte;

    memset ( &buff[0], 0, sizeof(buff) );
    // opcode byte
    buff[0] = ( 0x40u ) | 
              (( deviceAddr & 0x07u) << 1u ) |
              (( eReadOrWrite == MCP2317_eWrite ) ?  0x00u : 0x01u );
    
    // Reg Address byte
    bRet = mcp2317_getRegAddress( eCmd, ePort, &regByte );
    if( bRet )
    {
        buff[1] = regByte;
    }
    
    // Reg data byte
    if( eReadOrWrite == MCP2317_eWrite )
    {
        if( pByte != NULL )
        {
            buff[2] = *pByte;
        }
        else
        {
            bRet = FALSE;
        }
    }
    
    if( bRet )
    {
        /* send data to the SPI bus and data is recived at the same time */
        wiringPiSPIDataRW ( MCP2317_SPI_CHANNEL , buff, sizeof(buff) );

        /* receive/interpret the data TODO: verify */
        if( ( eReadOrWrite == MCP2317_eRead ) 
            )
        {
            if( pByte != NULL )
            {
                *pByte = buff[2];
            }
            else
            {
                bRet = FALSE;
            }
        }
    }

    return bRet;
}

bool_t  MCP2317_Close( uint8_t deviceAddr )
{
    return TRUE;
}



bool_t MCP2317_Init( void )
{
    return TRUE;
}


bool_t MCP2317_ReadValue ( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue )
{
    return MCP2317_Cmd( deviceAddr, MCP2317_eRead, ePort, MCP2317_eCmdPortValue, pValue );
}

bool_t MCP2317_ReadOutLatchValue( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue )
{
    return MCP2317_Cmd( deviceAddr, MCP2317_eRead, ePort, MCP2317_eCmdPortOutLatchValue, pValue );
}

bool_t MCP2317_WriteValue( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue )
{
    return MCP2317_Cmd( deviceAddr, MCP2317_eWrite, ePort, MCP2317_eCmdPortOutLatchValue, pValue );
}

bool_t MCP2317_ReadIntFlag( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue )
{
    return MCP2317_Cmd( deviceAddr, MCP2317_eRead, ePort, MCP2317_eCmdIntFlag, pValue );
}


bool_t MCP2317_ReadValueAtInterupt( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue )
{
    return MCP2317_Cmd( deviceAddr, MCP2317_eRead, ePort, MCP2317_eCmdGetValueAtInterupt, pValue );
}

bool_t MCP2317_SetDirection( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue )
{
    return MCP2317_Cmd( deviceAddr, MCP2317_eWrite, ePort, MCP2317_eCmdDirection, pValue );
}

bool_t MCP2317_GetDirection( uint8_t deviceAddr, MCP2317_ePort_t ePort, uint8_t* pValue )
{
    return MCP2317_Cmd( deviceAddr, MCP2317_eRead, ePort, MCP2317_eCmdDirection, pValue );
}

