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
 * @return Returns an ID used for read and write functions. 0xFF if failure.
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


// Enumeration of all of the possible register address in the RFM69HCW
enum class RFM69RegisterAddresses;
//! Operational Mode Register definition.
struct RegOpMode;

/**
 * @brief Base class for RFM69 register definitions.
 * 
 */
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


/**
 * @brief Main class for RFM69 access. 
 * 
 */
class RFM69 {

    private:
        //! Function pointers to control SPI channel.
        RFM69spiInitFnc init_function;
        RFM69spiReadFnc read_function;
        RFM69spiWriteFnc write_function;
        //! ID for the SPI channel.
        uint8_t spi_id = 0xFF;

    public:  
        // Defines the maximum SPI clock for the RFM69, in hertz.
        static const uint32_t max_spi_clock = 10000000u;

        /******************Constructors/Desctructors**************************************/
        // Defaults
        RFM69();
        ~RFM69(); 
        /*********************************************************************************/
        
        /**
         * @brief Sets the spi function pointers for SPI control.
         * 
         * @param init_function Function pointer to the SPI init function.
         * @param read_function  Function pointer to the SPI read function. 
         * @param write_function Function pointer to the SPi write function.
         */
        void set_spi(RFM69spiInitFnc init_function, RFM69spiReadFnc read_function, RFM69spiWriteFnc write_function);







        /**
         * @brief Writes a buffer to a given register.
         * 
         * @param reg Register to access.
         * @param num_to_write Number of bytes to write. 
         * @param buff Buffer containing bytes to write. Must be at least num_to_write long.
         * @return true When all bytes were written successfully.
         * @return false When either an error occurred or not all bytes written.
         */
        bool write_reg( RFM69RegisterAddresses reg, uint8_t num_to_write, uint8_t* buff );

        /**
         * @brief Writes a buffer to a given register.
         * 
         * @param reg Register to access.
         * @param num_to_read Number of bytes to write. 
         * @param buff Buffer where read in bytes are stored. Must be at least num_to_read long.
         * @return true When all bytes were written successfully.
         * @return false When either an error occurred or not all bytes written.
         */
        bool read_reg( RFM69RegisterAddresses reg, uint8_t num_to_read, uint8_t* buff );


        void poll_mode( void );


};