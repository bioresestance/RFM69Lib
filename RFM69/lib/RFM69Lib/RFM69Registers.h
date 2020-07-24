#pragma once
#include <stdint.h>
#include <utils.h>

// Enumeration of all of the possible register address in the RFM69HCW
/**
 *  @brief Address values for all Registers that can be accessed.
 *  @note The order that the values are defined are critical. Do not change unless the datasheet is consulted.
 */
enum class RFM69RegisterAddresses
{
            RegFifo = 0x00,
            RegOpMode,
            RegDataModul,
            RegBitrateMsb,
            RegBitrateLsb,
            RegFdevMsb,
            RegFdevLsb,
            RegFrfMsb,
            RegFrfMid,
            RegFrfLsb,
            RegOsc1,
            RegAfcCtrl,
            //Reserved Value Here
            RegListen1 = 0x0D,
            RegListen2,
            RegListen3,
            RegVersion,
            RegPaLevel,
            RegPaRamp,
            RegOcp,
            //Reserved Value Here
            //Reserved Value Here
            //Reserved Value Here
            //Reserved Value Here
            RegLna = 0x18,
            RegRxBw,
            RegAfcBw,
            RegOokPeak,
            RegOokAvg,
            RegOokFix,
            RegAfcFei,
            RegAfcMsb,
            RegAfcLsb,
            RegFeiMsb,
            RegFeiLsb,
            RegRssiConfig,
            RegRssiValue,
            RegDioMapping1,
            RegDioMapping2,
            RegIrqFlags1,
            RegIrqFlags2,
            RegRssiThresh,
            RegRxTimeout1,
            RegRxTimeout2,
            RegPreambleMsb,
            RegPreambleLsb,
            RegSyncConfig,
            RegSyncValue1,
            RegSyncValue2,
            RegSyncValue3,
            RegSyncValue4,
            RegSyncValue5,
            RegSyncValue6,
            RegSyncValue7,
            RegSyncValue8,
            RegPacketConfig1,
            RegPayloadLength,
            RegNodeAdrs,
            RegBroadcastAdrs,
            RegAutoModes,
            RegFifoThresh,
            RegPacketConfig2,
            RegAesKey1,
            RegAesKey2,
            RegAesKey3,
            RegAesKey4,
            RegAesKey5,
            RegAesKey6,
            RegAesKey7,
            RegAesKey8,
            RegAesKey9,
            RegAesKey10,
            RegAesKey11,
            RegAesKey12,
            RegAesKey13,
            RegAesKey14,
            RegAesKey15,
            RegAesKey16,
            RegTemp1,
            RegTemp2,
            RegTestLna = 0x58,
            RegTestPa1 = 0x5A,
            RegTestPa2 = 0x5C,
            RegTestDagc = 0x6F,
            RegTestAfc = 0x71,
};

/***************************************************Base Register Class Definition*******************/
/**
 * @brief Base class for RFM69 register definitions.
 * 
 *  Used to store and convert register values between raw bits and 
 *  their individual values. This base class is the template for all
 *  individual register class to implement. 
 * 
 *  Classes that inherit should call the base constructor to fill in 
 *  the generic values and will need to overide the get_byte method
 *  to fill in the byte that is returned as the register defines.
 * 
 */
class RFM69Register {
protected:
    uint8_t _default_value;
    uint8_t _recommended_value;
    RFM69RegisterAddresses _address;

public:
    /**
     * @brief Get the default value of the register.
     * 
     * @return uint8_t default value of the register
     */
    uint8_t get_default_value()  {return _default_value;}

    /**
     * @brief Get the recommended value of the register.
     * 
     * @return uint8_t recommended value of the register
     */
    uint8_t get_recommended_value() { return _recommended_value;}
    /**
     * @brief Get the address of the register
     * 
     * @return uint8_t address of the register
     */

    uint8_t get_address() {return (uint8_t)_address;}

    /**
     * @brief Get the address as an enum.
     * 
     * @return RFM69RegisterAddresses The register address as an enum.
     */
    RFM69RegisterAddresses get_reg_address() {return _address;}
 
    /**
     * @brief Returns the stored value as a single raw byte.
     * 
     * @return uint8_t Raw byte as defined in register.
     */
    virtual uint8_t get_byte() = 0;

    /**
     * @brief Allows the register to be set as a byte.
     * 
     * @param byte The byte to set the register to.
     */
    virtual void set_byte( uint8_t byte) = 0;

    //! Allows the object to be directly cast as an uint8_t.
    operator uint8_t() {return get_byte();}

    //! Allows the register to be assigned a byte value directly. 
    RFM69Register& operator=( uint8_t byte) { this->set_byte(byte); return *this;}

    RFM69Register(uint8_t default_value, uint8_t recommended_value, RFM69RegisterAddresses address) 
    : _default_value(default_value), 
    _recommended_value( recommended_value),
    _address(address) {

    }
};

/***********************************************Individual Register Classes*************************************/

//! Operational Mode Register Definition.
struct RegOpMode : public RFM69Register 
{
    bool _sequencerOff;
    bool _listenOn;
    bool _listenAbort;
    uint8_t _mode; // Only uses 3 bits.

    RegOpMode()
    :RFM69Register(0x04, 0x04, RFM69RegisterAddresses::RegOpMode) {

    }


    RegOpMode(bool sequencerOff, bool listenOn, bool listenAbort, uint8_t mode) 
    :RFM69Register(0x04, 0x04, RFM69RegisterAddresses::RegOpMode),
    _sequencerOff(sequencerOff),
    _listenOn(listenOn),
    _listenAbort(listenAbort),
    _mode(mode){

    }
    

    uint8_t get_byte() {
        uint8_t byte = 0;

        BIT_SET_FROM(byte, 7, _sequencerOff);
        BIT_SET_FROM(byte, 6, _listenOn);
        BIT_SET_FROM(byte, 5, _listenAbort);
        // bits 2 - 4 are mode.
        byte |= (_mode & 0b00000111) << 2;
        return byte;
    }

    void set_byte(uint8_t byte) {
        _sequencerOff = BIT_CHECK(byte, 7);
        _listenOn = BIT_CHECK(byte, 6);
        _listenAbort = BIT_CHECK(byte, 5);
        _mode = (byte & 0b00011100) >> 2;
    }
};

/**
 * @brief Temperature Register 1.
 * 
 */
struct RegTemp1 : public RFM69Register 
{
    bool _tempMeasStart;
    bool _tempMeasRunning;

    RegTemp1() 
    : RFM69Register(0x04, 0x04, RFM69RegisterAddresses::RegOpMode),
     _tempMeasStart(false) ,
    _tempMeasRunning(false)
    {}

    RegTemp1(bool tempMeasStart, bool tempMeasRunning) 
    : RFM69Register(0x01, 0x01, RFM69RegisterAddresses::RegTemp1),
    _tempMeasStart(tempMeasStart), 
    _tempMeasRunning(tempMeasRunning) {

    }

   
    uint8_t get_byte() {
        uint8_t byte = 0;      
        // Set the bits in the byte.
        BIT_SET_FROM(byte, 3, _tempMeasStart);
        BIT_SET_FROM(byte, 2, _tempMeasRunning);     
        return byte;
    }

    void set_byte(uint8_t byte) {
        _tempMeasStart = BIT_CHECK(byte, 3);
        _tempMeasRunning = BIT_CHECK(byte, 2);
        // Rest is ignored.
    }
};

/**
 * @brief Temperature Register 2.
 * 
 */
struct RegTemp2 : public RFM69Register 
{
    uint8_t _tempValue;

    RegTemp2(): RFM69Register(0x00, 0x00, RFM69RegisterAddresses::RegOpMode) {}

    RegTemp2(uint8_t tempValue) 
    : RFM69Register(0x00, 0x00, RFM69RegisterAddresses::RegTemp2), _tempValue(tempValue) {
        
    }

    uint8_t get_byte() {   
        return _tempValue;
    }

    void set_byte(uint8_t byte) {
        _tempValue = byte;   
    }
};