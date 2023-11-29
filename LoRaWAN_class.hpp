#ifndef LORAWAN_CLASS
#define LORAWAN_CLASS

#include <iostream>
#include <stdio.h>
#include <string>

#include "lorawan/LoRaWANInterface.h"
#include "lorawan/system/lorawan_data_structures.h"
#include "events/EventQueue.h"

// Application helpers
#include "./mbed_honeywell-hpma115/hpma115/hpma115.h"
#include "trace_helper.h"
#include "lora_radio_helper.h"
#include <PinNames.h>

#endif

using namespace events;
 
// Define a template class
template <typename T>

class LoRaWAN_app {

private:

    // Max payload size can be LORAMAC_PHY_MAXPAYLOAD.
    // This example only communicates with much shorter messages (<30 bytes).
    // If longer messages are used, these buffers must be changed accordingly.
    uint8_t tx_buffer[30];
    uint8_t rx_buffer[30];

    /*
    * Sets up an application dependent transmission timer in ms. Used only when Duty Cycling is off for testing
    */
    #define TX_TIMER                        10000

    /**
    * Maximum number of events for the event queue.
    * 10 is the safe number for the stack events, however, if application
    * also uses the queue for whatever purposes, this number should be increased.
    */
    #define MAX_NUMBER_OF_EVENTS            10

    /**
    * Maximum number of retries for CONFIRMED messages before giving up
    */
    #define CONFIRMED_MSG_RETRY_COUNTER     3

    /**
    * Application specific callbacks
    */
    static lorawan_app_callbacks_t callbacks;

    /**
    * Constructing Mbed LoRaWANInterface and passing it the radio object from lora_radio_helper.
    */
    static LoRaWANInterface lorawan(radio);

    /**
    * This event queue is the global event queue for both the
    * application and stack. To conserve memory, the stack is designed to run
    * in the same thread as the application and the application is responsible for
    * providing an event queue to the stack that will be used for ISR deferment as
    * well as application information event queuing.
    */
    static EventQueue ev_queue(MAX_NUMBER_OF_EVENTS *EVENTS_EVENT_SIZE)

    /**
    * Event handler.
    *
    * This will be passed to the LoRaWAN stack to queue events for the
    * application which in turn drive the application.
    */
    static void lora_event_handler(lorawan_event_t event);

    // stores the status of a call to LoRaWAN protocol
    lorawan_status_t retcode;

    /**
    * Sends a message to the Network Server
    */
    static void send_message();

    /**
    * Receive a message from the Network Server
    */
    static void receive_message();

    /**
    * Event handler
    */
    static void lora_event_handler(lorawan_event_t event);

public:
    // Constructor
    MyClass(T value) : data(value) {}

    // Member function
    void Init();

    void Connect();

    void Disconnect();
};