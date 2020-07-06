#pragma once
#include <stdint.h>

/**
 * @brief Structure to hold all function pointers for SPI access.
 * 
 */
struct RFM69SPI {

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
    typedef uint8_t (*InitFnc)();

    /**
     * @brief Function point to a function that sets up the SPI driver to begin a transfer.
     * 
     *  This function is called by the RFM69 class before any bytes are transferred. This function
     *  takes in the SPI ID and should perform any tasks at the driver level to prepare for a transfer.
     *  This may include saving any settings and change over to RFM69 ones and set the chip select pin.
     * 
     *  @param first SPI ID for the RFM69 module.
     * 
     *  @return Whether the task was successful or not. Used to determine if transfer can begin.
     * 
     */
    typedef bool (*BeginFnc)(uint8_t);

    /**
     * @brief Function point to a function that sets up the SPI driver to end a transfer.
     * 
     *  This function is called by the RFM69 class after all bytes are transferred. This function
     *  takes in the SPI ID and should perform any tasks at the driver level to end a transfer.
     *  This may include loading any saved settings and deselect the chip select pin.
     * 
     *  @param first SPI ID for the RFM69 module.
     * 
     *  @return Whether the task was successful or not.
     * 
     */
    typedef bool (*EndFnc)(uint8_t);


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
    typedef bool (*ReadFnc)(uint8_t , uint16_t, uint8_t*);

    /**
     * @brief Function pointer type for SPI write function.
     * 
     * @param first address of SPI chip. Used by function to determine chip.
     * @param second Number of bytes to write to device. 
     * @param third Buffer containing bytes to write. Must be at least length long.
     * 
     * @return Whether the result was successful or not.
     */
    typedef bool (*WriteFnc)(uint8_t , uint16_t, uint8_t*);


/*****************************************************Function Pointer Holders*********************/
    InitFnc init_function;
    BeginFnc begin_function;
    EndFnc end_function;
    ReadFnc read_function;
    WriteFnc write_function;
};