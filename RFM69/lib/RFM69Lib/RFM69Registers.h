#pragma once
#include <stdint.h>
#include <utils.h>

namespace RFM69Radio {
    


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
    RFM69Register& operator = ( uint8_t byte) { this->set_byte(byte); return *this;}

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
        WIDEBITFIELD_SET_FROM(byte, _mode, 3, 2);
        return byte;
    }

    void set_byte(uint8_t byte) {
        _sequencerOff = BIT_CHECK(byte, 7);
        _listenOn = BIT_CHECK(byte, 6);
        _listenAbort = BIT_CHECK(byte, 5);
        _mode = WIDEBITFIELD_GET_FROM( byte, 3, 2);
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
    : RFM69Register(0x04, 0x04, RFM69RegisterAddresses::RegTemp1),
     _tempMeasStart(false) ,
    _tempMeasRunning(false)
    {}
   
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

    RegTemp2(): RFM69Register(0x00, 0x00, RFM69RegisterAddresses::RegTemp2) {}

     uint8_t get_byte() {   
        return _tempValue;
    }

    void set_byte(uint8_t byte) {
        _tempValue = byte;   
    }
};

/**
 * @brief Data Modulation option register.
 * 
 */
struct RegDataModul : public RFM69Register 
{
    uint8_t _dataMode;  // 2 bits
    uint8_t _modulationType; // 2 bits
    uint8_t _modulationShaping; // 2 bits

    RegDataModul(): RFM69Register(0x00, 0x00, RFM69RegisterAddresses::RegDataModul) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        WIDEBITFIELD_SET_FROM(byte, _dataMode, 2, 5);
        WIDEBITFIELD_SET_FROM(byte, _modulationType, 2, 3);
        WIDEBITFIELD_SET_FROM(byte, _modulationShaping, 2, 0);
        return byte;
    }

    void set_byte(uint8_t byte) {
        _dataMode = WIDEBITFIELD_GET_FROM( byte, 2, 5);
        _modulationType = WIDEBITFIELD_GET_FROM( byte, 2, 3);
        _modulationShaping = WIDEBITFIELD_GET_FROM( byte, 2, 0);
    }
};

/**
 * @brief Most significant Byte of Bit rate selection register.
 * 
 */
struct RegBitrateMsb : public RFM69Register 
{
    uint8_t _bitrateMsb;  // Bitrate bits 15:8

    RegBitrateMsb(): RFM69Register(0x1A, 0x1A, RFM69RegisterAddresses::RegBitrateMsb) {}

    uint8_t get_byte() { 
        return _bitrateMsb;
    }

    void set_byte(uint8_t byte) {
        _bitrateMsb = byte;
    }
};

/**
 * @brief Least significant Byte of Bit rate selection register.
 * 
 */
struct RegBitrateLsb : public RFM69Register 
{
    uint8_t _bitrateLsb;  // Bitrate bits 7:0

    RegBitrateLsb(): RFM69Register(0x0B, 0x0B, RFM69RegisterAddresses::RegBitrateLsb) {}

    uint8_t get_byte() { 
        return _bitrateLsb;
    }

    void set_byte(uint8_t byte) {
        _bitrateLsb = byte;
    }
};

/**
 * @brief Most significant Byte of freq. divider register.
 * 
 */
struct RegFdevMsb : public RFM69Register 
{
    uint8_t _fDevMsb;  // Bits 13:8

    RegFdevMsb(): RFM69Register(0x00, 0x00, RFM69RegisterAddresses::RegFdevMsb) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        WIDEBITFIELD_SET_FROM(byte, _fDevMsb, 5, 0);
        return byte;
    }

    void set_byte(uint8_t byte) {
        _fDevMsb = WIDEBITFIELD_GET_FROM( byte, 5, 0);
    }
};

/**
 * @brief Least Significant Byte of freq. divider register.
 * 
 */
struct RegFdevLsb : public RFM69Register 
{
    uint8_t _fDevMsb;  // Bits 7:0

    RegFdevLsb(): RFM69Register(0x52, 0x52, RFM69RegisterAddresses::RegFdevLsb) {}

    uint8_t get_byte() { 
        return _fDevMsb ;
    }

    void set_byte(uint8_t byte) {
        _fDevMsb = byte;
    }
};

/**
 * @brief Most Significant Byte of the RF carrier register.
 */
struct RegFrfMsb : public RFM69Register 
{
    uint8_t _fRFMsb;  // Bits 23:16

    RegFrfMsb(): RFM69Register(0xe4, 0xe4, RFM69RegisterAddresses::RegFrfMsb) {}

    uint8_t get_byte() { 
        return _fRFMsb ;
    }

    void set_byte(uint8_t byte) {
        _fRFMsb = byte;
    }
};


/**
 * @brief Mid Byte of the RF carrier register.
 */
struct RegFrfMid : public RFM69Register 
{
    uint8_t _fRFMid;  // Bits 15:8

    RegFrfMid(): RFM69Register(0xc0, 0xc0, RFM69RegisterAddresses::RegFrfMid) {}

    uint8_t get_byte() { 
        return _fRFMid;
    }

    void set_byte(uint8_t byte) {
        _fRFMid = byte;
    }
};

/**
 * @brief Least Significant Byte of the RF carrier register.
 */
struct RegFrfLsb : public RFM69Register 
{
    uint8_t _fRFLsb;  // Bits 7:0

    RegFrfLsb(): RFM69Register(0x00, 0x00, RFM69RegisterAddresses::RegFrfLsb) {}

    uint8_t get_byte() { 
        return _fRFLsb ;
    }

    void set_byte(uint8_t byte) {
        _fRFLsb = byte;
    }
};

/**
 * @brief Oscillator register 1.
 */
struct RegOsc1 : public RFM69Register 
{
    bool _rcCalStart;
    bool _rcCalDone;

    RegOsc1(): RFM69Register(0x41, 0x41, RFM69RegisterAddresses::RegOsc1) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        BIT_SET_FROM(byte, 7, _rcCalStart);
        BIT_SET_FROM(byte, 6, _rcCalDone);
        return byte;
    }

    void set_byte(uint8_t byte) {
        _rcCalStart = BIT_CHECK(byte, 7);
        _rcCalDone = BIT_CHECK(byte, 6);
    }
};

/**
 * @brief AFC control register.
 */
struct RegAfcCtrl : public RFM69Register 
{
    bool _afcLowBetaOn;

    RegAfcCtrl(): RFM69Register(0x00, 0x00, RFM69RegisterAddresses::RegAfcCtrl) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        BIT_SET_FROM(byte, 5, _afcLowBetaOn);
        return byte;
    }

    void set_byte(uint8_t byte) {
        _afcLowBetaOn = BIT_CHECK(byte, 5);
    }
};

/// \todo Adde the listen registers here.

/**
 * @brief PA Level register.
 */
struct RegPaLevel : public RFM69Register 
{
    bool Pa0On;
    bool Pa1On;
    bool Pa2On;
    uint8_t outputPower;

    RegPaLevel(): RFM69Register(0x8F, 0x8F, RFM69RegisterAddresses::RegPaLevel) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        BIT_SET_FROM(byte, 7, Pa0On);
        BIT_SET_FROM(byte, 6, Pa1On);
        BIT_SET_FROM(byte, 5, Pa2On);
        WIDEBITFIELD_SET_FROM(byte, outputPower, 5, 0);
        return byte;
    }

    void set_byte(uint8_t byte) {
        Pa0On = BIT_CHECK(byte, 7);
        Pa1On = BIT_CHECK(byte, 6);
        Pa2On = BIT_CHECK(byte, 5);
        outputPower = WIDEBITFIELD_GET_FROM( byte, 5, 0);
    }
};

/**
 * @brief PA Ramp register.
 */
struct RegPaRamp : public RFM69Register 
{
    uint8_t PaRmap;

    RegPaRamp(): RFM69Register(0x09, 0x09, RFM69RegisterAddresses::RegPaRamp) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        WIDEBITFIELD_SET_FROM(byte, PaRmap, 4, 0);
        return byte;
    }

    void set_byte(uint8_t byte) {
        PaRmap = WIDEBITFIELD_GET_FROM( byte, 4, 0);
    }
};

/**
 * @brief Overload current protection register.
 */
struct RegOcp : public RFM69Register 
{
    bool OcpOn;
    uint8_t OcpTrim;

    RegOcp(): RFM69Register(0x1A, 0x1A, RFM69RegisterAddresses::RegOcp) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        BIT_SET_FROM(byte, 4, OcpOn);
        WIDEBITFIELD_SET_FROM(byte, OcpTrim, 4, 0);
        return byte;
    }

    void set_byte(uint8_t byte) {
        OcpOn = BIT_CHECK(byte, 4);
        OcpTrim = WIDEBITFIELD_GET_FROM( byte, 4, 0);
    }

    void set_current_Trim( uint8_t current_ma) {
        OcpTrim = (current_ma - 45 ) / 5; // Formula from datasheet.
    }
};

/**
 * @brief Low Noise Amplifier register.
 */
struct RegLna : public RFM69Register 
{
    bool LnaZin;
    uint8_t LnaCurrentGain;
    uint8_t LnaGainSelect; 

    RegLna(): RFM69Register(0x88, 0x88, RFM69RegisterAddresses::RegLna) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        BIT_SET_FROM(byte, 7, LnaZin);
        WIDEBITFIELD_SET_FROM(byte, LnaCurrentGain, 3, 3);
        WIDEBITFIELD_SET_FROM(byte, LnaGainSelect, 3, 0);
        return byte;
    }

    void set_byte(uint8_t byte) {
        LnaZin = BIT_CHECK(byte, 7);
        LnaCurrentGain = WIDEBITFIELD_GET_FROM( byte, 3, 3);
        LnaGainSelect = WIDEBITFIELD_GET_FROM( byte, 3, 0);
    }
};

/**
 * @brief RX Bandwidth register.
 */
struct RegRxBw : public RFM69Register 
{
    uint8_t DccFreq;
    uint8_t RxBwMant;
    uint8_t RxBwExp; 

    RegRxBw(): RFM69Register(0x88, 0x88, RFM69RegisterAddresses::RegRxBw) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        WIDEBITFIELD_SET_FROM(byte, DccFreq, 3, 5);
        WIDEBITFIELD_SET_FROM(byte, RxBwMant, 2, 3);
        WIDEBITFIELD_SET_FROM(byte, RxBwExp, 3, 0);
        return byte;
    }

    void set_byte(uint8_t byte) {
        DccFreq = WIDEBITFIELD_GET_FROM( byte, 3, 5);
        RxBwMant = WIDEBITFIELD_GET_FROM( byte, 2, 3);
        RxBwExp = WIDEBITFIELD_GET_FROM( byte, 3, 0);
    }
};

/**
 * @brief AFC Bandwidth register.
 */
struct RegAfcBw : public RFM69Register 
{
    uint8_t DccFreqAfc;
    uint8_t RxBwMantAfc;
    uint8_t RxBwExpAfc; 

    RegAfcBw(): RFM69Register(0x88, 0x88, RFM69RegisterAddresses::RegAfcBw) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        WIDEBITFIELD_SET_FROM(byte, DccFreqAfc, 3, 5);
        WIDEBITFIELD_SET_FROM(byte, RxBwMantAfc, 2, 3);
        WIDEBITFIELD_SET_FROM(byte, RxBwExpAfc, 3, 0);
        return byte;
    }

    void set_byte(uint8_t byte) {
        DccFreqAfc = WIDEBITFIELD_GET_FROM( byte, 3, 5);
        RxBwMantAfc = WIDEBITFIELD_GET_FROM( byte, 2, 3);
        RxBwExpAfc = WIDEBITFIELD_GET_FROM( byte, 3, 0);
    }
};

/**
 * @brief OOK Peak register.
 */
struct RegOokPeak : public RFM69Register 
{
    uint8_t OokThreshType;
    uint8_t OokPeakTheshStep;
    uint8_t OokPeakThreshDec; 

    RegOokPeak(): RFM69Register(0x88, 0x88, RFM69RegisterAddresses::RegOokPeak) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        WIDEBITFIELD_SET_FROM(byte, OokThreshType, 2, 6);
        WIDEBITFIELD_SET_FROM(byte, OokPeakTheshStep, 3, 3);
        WIDEBITFIELD_SET_FROM(byte, OokPeakThreshDec, 3, 0);
        return byte;
    }

    void set_byte(uint8_t byte) {
        OokThreshType = WIDEBITFIELD_GET_FROM( byte, 2, 6);
        OokPeakTheshStep = WIDEBITFIELD_GET_FROM( byte, 3, 3);
        OokPeakThreshDec = WIDEBITFIELD_GET_FROM( byte, 3, 0);
    }
};

/**
 * @brief OOK Average register.
 */
struct RegOokAvg : public RFM69Register 
{
    uint8_t OokAverageThreshFilt;

    RegOokAvg(): RFM69Register(0x88, 0x88, RFM69RegisterAddresses::RegOokAvg) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        WIDEBITFIELD_SET_FROM(byte, OokAverageThreshFilt, 2, 6);
        return byte;
    }

    void set_byte(uint8_t byte) {
        OokAverageThreshFilt = WIDEBITFIELD_GET_FROM( byte, 2, 6);
    }
};


/**
 * @brief OOK Fixed Threshold register.
 */
struct RegOokFix : public RFM69Register 
{
    uint8_t OokFixedThresh;

    RegOokFix(): RFM69Register(0x88, 0x88, RFM69RegisterAddresses::RegOokFix) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        WIDEBITFIELD_SET_FROM(byte, OokFixedThresh, 8, 0);
        return byte;
    }

    void set_byte(uint8_t byte) {
        OokFixedThresh = WIDEBITFIELD_GET_FROM( byte, 8, 0);
    }
};

/**
 * @brief AFC FEI register.
 */
struct RegAfcFei : public RFM69Register 
{
    bool FeiDone;
    bool FeiStart;
    bool AfcDone;
    bool AfcAutoclearOn;
    bool AfcAutoOn;
    bool AfcClear;
    bool AfcStart;

    RegAfcFei(): RFM69Register(0x88, 0x88, RFM69RegisterAddresses::RegAfcFei) {}

    uint8_t get_byte() { 
        uint8_t byte = 0;
        BIT_SET_FROM(byte, 6, FeiDone);
        BIT_SET_FROM(byte, 5, FeiStart);
        BIT_SET_FROM(byte, 4, AfcDone);
        BIT_SET_FROM(byte, 3, AfcAutoclearOn);
        BIT_SET_FROM(byte, 2, AfcAutoOn);
        BIT_SET_FROM(byte, 1, AfcClear);
        BIT_SET_FROM(byte, 0, AfcStart);
        return byte;
    }

    void set_byte(uint8_t byte) {
        FeiDone = BIT_CHECK(byte, 6);
        FeiStart = BIT_CHECK(byte, 5);
        AfcDone = BIT_CHECK(byte, 4);
        AfcAutoclearOn = BIT_CHECK(byte, 3);
        AfcAutoOn = BIT_CHECK(byte, 2);
        AfcClear = BIT_CHECK(byte, 1);
        AfcStart = BIT_CHECK(byte, 0);
    }
};

/**
 * @brief AFC value MSB register.
 */
struct RegAfcMsb : public RFM69Register 
{
    uint8_t AfcValueMsb;

    RegAfcMsb(): RFM69Register(0x0, 0x00, RFM69RegisterAddresses::RegAfcMsb) {}

    uint8_t get_byte() { 
        return AfcValueMsb;
    }

    void set_byte(uint8_t byte) {
       AfcValueMsb = byte;
    }
};

/**
 * @brief AFC value LSB register.
 */
struct RegAfcLsb : public RFM69Register 
{
    uint8_t AfcValueLsb;

    RegAfcLsb(): RFM69Register(0x0, 0x00, RFM69RegisterAddresses::RegAfcLsb) {}

    uint8_t get_byte() { 
        return AfcValueLsb;
    }

    void set_byte(uint8_t byte) {
       AfcValueLsb = byte;
    }
};


/**
 * @brief Fei value MSB register.
 */
struct RegFeiMsb : public RFM69Register 
{
    uint8_t FeiValueMsb;

    RegFeiMsb(): RFM69Register(0x0, 0x00, RFM69RegisterAddresses::RegFeiMsb) {}

    uint8_t get_byte() { 
        return FeiValueMsb;
    }

    void set_byte(uint8_t byte) {
       FeiValueMsb = byte;
    }
};


/**
 * @brief Fei value LSB register.
 */
struct RegFeiLsb : public RFM69Register 
{
    uint8_t FeiValueMsb;

    RegFeiLsb(): RFM69Register(0x0, 0x00, RFM69RegisterAddresses::RegFeiLsb) {}

    uint8_t get_byte() { 
        return FeiValueMsb;
    }

    void set_byte(uint8_t byte) {
       FeiValueMsb = byte;
    }
};

/**
 * @brief RSSI Config register.
 */
struct RegRssiConfig : public RFM69Register 
{
    bool RssiDone;
    bool RssiStart;

    RegRssiConfig(): RFM69Register(0x02, 0x02, RFM69RegisterAddresses::RegRssiConfig) {}

    uint8_t get_byte() {
        uint8_t byte = 0;
        BIT_SET_FROM(byte, 1, RssiDone);
        BIT_SET_FROM(byte, 0, RssiStart); 
        return byte;
    }

    void set_byte(uint8_t byte) {
        RssiDone = BIT_CHECK(byte, 1);
        RssiStart = BIT_CHECK(byte, 0);
    }
};

/**
 * @brief RSSI Value Register.
 */
struct RegRssiValue : public RFM69Register 
{
    uint8_t rssiValue;

    RegRssiValue(): RFM69Register(0x0, 0x00, RFM69RegisterAddresses::RegRssiValue) {}

    uint8_t get_byte() { 
        return rssiValue;
    }

    void set_byte(uint8_t byte) {
       rssiValue = byte;
    }
};

}