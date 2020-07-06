#pragma once
#include <stdint.h>
#include <RFM69SPI.h>

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
        //! Holds all of the function pointer for SPI access.
        RFM69SPI spi_func;

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
         * @brief Attaches the spi function pointers for SPI control.
         * 
         * @param init_function Function pointer to the SPI init function.
         * @param begin_func Function pointer to the SPI Begin transfer function.
         * @param end_func Function pointer to the SPI End transfer function.
         * @param read_function  Function pointer to the SPI read function. 
         * @param write_function Function pointer to the SPi write function.
         */
        void spi_attach(RFM69SPI::InitFnc init_function, 
                        RFM69SPI::BeginFnc begin_func,
                        RFM69SPI::EndFnc end_func,
                        RFM69SPI::ReadFnc read_function, 
                        RFM69SPI::WriteFnc write_function);

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