#pragma once
#include "stdint.h"

/**
 * @brief Function point for SPI read function.
 * 
 * @param first address of SPI chip, gotten from init function.
 * @param second Number of bytes to read. 
 * @param third Buffer to store results of read. Ensure at least length long.
 * 
 * @return Whether the result was successful or not.
 * 
 */
typedef bool (*RFM69spiReadFnc)(uint8_t , uint16_t, uint8_t*);


class RFM69 {
    public:  

        /******************Constructors/Desctructors**************************************/
        // Defaults
        RFM69();
        ~RFM69(); 
        /*********************************************************************************/
        
        



};

// Enumeration of all of the possible register address in the RFM69HCW
enum class RFM69RegisterAddresses;


class RFM69Register {
protected:
    uint8_t _default_value;
    uint8_t _recommended_value;
    RFM69RegisterAddresses _address;

public:
    uint8_t get_default_value()  {return _default_value;}
    uint8_t get_recommended_value() { return _recommended_value;}
    uint8_t get_address() {return (uint8_t)_address;}
 
    //! Returns the Current set value.
    virtual uint8_t get_value() = 0;

    RFM69Register(uint8_t default_value, uint8_t recommended_value, RFM69RegisterAddresses address) {
        _default_value = default_value;  
        _recommended_value = recommended_value;
        _address = address;
    }

};