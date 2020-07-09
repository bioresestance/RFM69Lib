#pragma once
#include <stdint.h>
#include <RFM69SPI.h>
#include <RFM69Registers.h>

/**
 * @brief Main class for RFM69 access. 
 * 
 */
class RFM69 {

    //! Enum to specify how the RFM69 module should be controlled.
    public:
        enum class RFM69controlMode {
            POLLING_MODE,   //!< The object will periodically poll the module for changes.
            INTERRUPT_MODE  //!< The object will use interrupt pins to know when a change occurs.
        };

    private:
        //! Holds all of the function pointer for SPI access.
        RFM69SPI spi_func;
        //! ID for the SPI channel.
        uint8_t spi_id = 0xFF;
        //! Holds the current control state.
        RFM69controlMode currControlMode;

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
         * @param begin_function Function pointer to the SPI Begin transfer function.
         * @param end_function Function pointer to the SPI End transfer function.
         * @param read_function  Function pointer to the SPI read function. 
         * @param write_function Function pointer to the SPi write function.
         */
        void spi_attach(RFM69SPI::InitFnc init_function, 
                        RFM69SPI::BeginFnc begin_function,
                        RFM69SPI::EndFnc end_function,
                        RFM69SPI::ReadFnc read_function, 
                        RFM69SPI::WriteFnc write_function);

        /**
         * @brief Attaches the spi function pointers for SPI control.
         * 
         * @param spiFuncs Struct that holds all required spi access func pointers.
         */
        void spi_attach( RFM69SPI &spiFuncs);

        //TODO
        void io_attach();


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
         * @brief Writes the content of a register object to its corresponding RFM69 register. 
         * 
         * @param reg Register object to write its content to. Used to determine address.
         * @return true If the write was successful.
         * @return false If something went wrong in the register write.
         */
        bool write_reg( RFM69Register &reg );

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

        /**
         * @brief Reads in the contents of a register to a Register object
         * 
         * @param reg Register object to hold the contents of the read. Used to determine address.
         * @return true If the read was successful.
         * @return false If something went wrong in the register read. 
         */
        bool read_reg( RFM69Register &reg );

        

        //TODO
        void poll_mode( void );
};