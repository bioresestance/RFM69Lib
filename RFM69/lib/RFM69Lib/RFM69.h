#pragma once
#include "stdint.h"

/**
 * @brief Function pointer to a function that will perform initializing of SPI channel.
 * 
 *  This function will be called by the RFM69 class to perform initialization of the 
 *  SPI channel. What the function actually does is up to the implementation. After
 *  all initialization is complete, the function will return an ID value for the SPI channel.
 *  This ID value has no meaning to the class, but is used by the read and write function to 
 *  access the SPI channel.
 * 
 * @return Returns an ID used for read and write functions.
 */
typedef uint8_t (*RFM69spiInitFnc)();

/**
 * @brief Function pointer type for SPI read function.
 * 
 * @param first address of SPI chip. Used by function to determine chip.
 * @param second Number of bytes to read. 
 * @param third Buffer to store results of read. Ensure at least length long.
 * 
 * @return Whether the result was successful or not.
 * 
 */
typedef bool (*RFM69spiReadFnc)(uint8_t , uint16_t, uint8_t*);

/**
 * @brief Function pointer type for SPI write function.
 * 
 * @param first address of SPI chip. Used by function to determine chip.
 * @param second Number of bytes to write to device. 
 * @param third Buffer containing bytes to write. Must be at least length long.
 * 
 * @return Whether the result was successful or not.
 */
typedef bool (*RFM69spiWriteFnc)(uint8_t , uint16_t, uint8_t*);


class RFM69 {

    private:
        //! Function pointers to control SPI channel.
        RFM69spiInitFnc init_function;
        RFM69spiReadFnc read_function;
        RFM69spiWriteFnc write_function;
        //! ID for the SPI channel.
        uint8_t spi_id;
        
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