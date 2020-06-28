#include "RFM69.h"

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))        // '!!' to make sure this returns 0 or 1

/* x=target variable, y=mask */
#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_FLIP(x,y) ((x) ^= (y))
#define BITMASK_CHECK_ALL(x,y) (((x) & (y)) == (y))   // warning: evaluates y twice
#define BITMASK_CHECK_ANY(x,y) ((x) & (y))


//! a = target, b = bit to set, c = condition to check. 

//Only sets bit if C == true.
#define BIT_SET_IF_TRUE(a,b,c) ( (c) ? BIT_SET(a,b) :  )
// Only sets bit if C == false.
#define BIT_SET_IF_FALSE(a,b,c) ( (c) ?  :  BIT_SET(a,b) )

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
            RegeBitrateLsb,
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

struct RegOpMode : public RFM69Register 
{
    bool _sequencerOff;
    bool _listenOn;
    bool _listenAbort;
    uint8_t _mode; // Only uses 3 bits.

    RegOpMode(bool sequencerOff, bool listenOn, bool listenAbort, uint8_t mode) 
    : RFM69Register(0x04, 0x04, RFM69RegisterAddresses::RegOpMode) {
        _sequencerOff = sequencerOff;
        _listenOn = listenOn;
        _listenAbort = listenAbort;
        _mode = mode;
    }

    uint8_t get_value() {
        uint8_t byte = 0;

        byte |= (_mode & 0x07) << 1;
        //byte |= BIT

        return byte;
    }
};