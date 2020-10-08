#ifndef _BLUETOOTH_RUNTIME_HPP
#define _BLUETOOTH_RUNTIME_HPP

// Arduino and mbed libaries. 
#include <Arduino.h>
#include <mbed.h>
#include "platform/Callback.h"
#include "events/EventQueue.h"
#include "platform/NonCopyable.h"
#include "rtos.h"

// Bluetooth libraries. 
#include "ble/BLE.h"
#include "ble/GattServer.h"

void start_bluetooth_runtime(void);

#endif