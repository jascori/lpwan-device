/**
 * Copyright (c) 2019, Jason Reiss ( jason.reiss@jascori.com )
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "lpwan-device-command.h"
#include "lpwan-device-radio.h"
#include "lpwan-device-frame.h"
#include "lpwan-device-config.h"


namespace LPWAN::Device {

char cmd_name_mem[] = "mem";
char cmd_name_srand[] = "srand";
char cmd_name_print[] = "print";
char cmd_name_save[] = "save";
char cmd_name_reset[] = "reset";
char cmd_name_send[] = "send";
char cmd_name_txpow[] = "txp";
char cmd_name_txf[] = "txf";
char cmd_name_txsf[] = "txsf";
char cmd_name_txbw[] = "txbw";
char cmd_name_tx_iq[] = "txiq";
char cmd_name_recv[] = "recv";
char cmd_name_rxf[] = "rxf";
char cmd_name_rxto[] = "rxto";
char cmd_name_rxsf[] = "rxsf";
char cmd_name_rxbw[] = "rxbw";
char cmd_name_rx_iq[] = "rxiq";
char cmd_name_sleep[] = "sleep";

static const char prompt[] = "$ ";

tinysh_cmd_t cmd_mem = {   0,
                           cmd_name_mem,
                           "show free memory",
                           "",
                           cmd_func_mem,
                           0,0,0
                        };

tinysh_cmd_t cmd_sleep = { 0,
                           cmd_name_sleep,
                           "sleep for a set number of milliseconds",
                           "<milliseconds>",
                           cmd_func_sleep,
                           0,0,0
                        };

tinysh_cmd_t cmd_print = { 0,
                           cmd_name_print,
                           "print settings",
                           "",
                           cmd_func_print,
                           0,0,0
                           };

tinysh_cmd_t cmd_send = {  0,
                           cmd_name_send,
                           "send a packet",
                           "[payload]",
                           cmd_func_send,
                           0,0,0
                        };

tinysh_cmd_t cmd_txpow = {  0,
                           cmd_name_txpow,
                           "set the tx power",
                           "<power>",
                           cmd_func_txpow,
                           0,0,0
                        };

tinysh_cmd_t cmd_txsf = {  0,
                           cmd_name_txsf,
                           "set the tx spreading factor",
                           "<spreading factor>",
                           cmd_func_txsf,
                           0,0,0
                        };

tinysh_cmd_t cmd_txbw = {  0,
                           cmd_name_txbw,
                           "set the tx bandwidth",
                           "<bandwidth>",
                           cmd_func_txbw,
                           0,0,0
                        };

tinysh_cmd_t cmd_freq = {  0,
                           cmd_name_txf,
                           "set the tx frequency",
                           "<frequency>",
                           cmd_func_txf,
                           0,0,0
                        };

tinysh_cmd_t cmd_recv = {  0,
                           cmd_name_recv,
                           "recv a packet",
                           "",
                           cmd_func_recv,
                           0,0,0
                        };

tinysh_cmd_t cmd_rxsf = {  0,
                           cmd_name_rxsf,
                           "set the tx spreading factor",
                           "<spreading factor>",
                           cmd_func_rxsf,
                           0,0,0
                        };

tinysh_cmd_t cmd_rxbw = {  0,
                           cmd_name_rxbw,
                           "set the tx bandwidth",
                           "<bandwidth>",
                           cmd_func_rxbw,
                           0,0,0
                        };

tinysh_cmd_t cmd_rxto = {  0,
                           cmd_name_rxto,
                           "set the rx timeout ms",
                           "<timeout>",
                           cmd_func_rxto,
                           0,0,0
                        };

tinysh_cmd_t cmd_rxf = {  0,
                           cmd_name_rxf,
                           "set the tx frequency",
                           "<frequency>",
                           cmd_func_rxf,
                           0,0,0
                        };

tinysh_cmd_t cmd_tx_iq = { 0,
                           cmd_name_tx_iq,
                           "Invert radio I/Q",
                           "<enable>",
                           cmd_func_tx_iq,
                           0,0,0
                        };

tinysh_cmd_t cmd_rx_iq = { 0,
                           cmd_name_rx_iq,
                           "Invert radio I/Q",
                           "<enable>",
                           cmd_func_rx_iq,
                           0,0,0
                        };

ConfigManager config;
DeviceConfig_t radio_config;


SX1272_LoRaRadio* _radio;
Serial* _pc;
radio_events_t _radio_events;
RadioEvents custom_events;

void error()
{
    printf("\r\n\nERROR\r\n");
}

void invalid_args()
{
    printf("\r\ninvalid args");
    error();
}

void ok()
{
    printf("\r\n\nOK\r\n");
}

void tinysh_init(SX1272_LoRaRadio &radio, Serial* pc)
{
   _pc = pc;

   config.Load(radio_config);

   _radio_events.rx_done = callback(&custom_events, &RadioEvents::rx_done);
   _radio_events.tx_done = callback(&custom_events, &RadioEvents::tx_done);
   _radio_events.tx_timeout = callback(&custom_events, &RadioEvents::tx_timeout);
   _radio = &radio;
   _radio->init_radio(&_radio_events);
   _radio->set_public_network(true);

   //set prompt
   tinysh_set_prompt(prompt);

   //add commands here
   tinysh_add_command(&cmd_mem);
   tinysh_add_command(&cmd_print);
   tinysh_add_command(&cmd_send);

   tinysh_add_command(&cmd_txpow);
   tinysh_add_command(&cmd_txsf);
   tinysh_add_command(&cmd_txbw);
   tinysh_add_command(&cmd_freq);
   tinysh_add_command(&cmd_tx_iq);

   tinysh_add_command(&cmd_recv);

   tinysh_add_command(&cmd_rxsf);
   tinysh_add_command(&cmd_rxbw);
   tinysh_add_command(&cmd_rxf);
   tinysh_add_command(&cmd_rxto);
   tinysh_add_command(&cmd_rx_iq);

   tinysh_add_command(&cmd_sleep);
}







void cmd_func_mem(int argc, char * argv[])
{
   printf("\r\n");
   // In order to get free mem within RTOS
   // we need to get the main thread's stack pointer
   // and subtract it with the top of the heap
   // ------+-------------------+   Last Address of RAM (INITIAL_SP)
   //       | Scheduler Stack   |
   //       +-------------------+
   //       | Main Thread Stack |
   //       |         |         |
   //       |         v         |
   //       +-------------------+ <- bottom_of_stack/__get_MSP()
   // RAM   |                   |
   //       |  Available RAM    |
   //       |                   |
   //       +-------------------+ <- top_of_heap
   //       |         ^         |
   //       |         |         |
   //       |       Heap        |
   //       +-------------------+ <- __end__ / HEAP_START (linker defined var)
   //       | ZI                |
   //       +-------------------+
   //       | ZI: Shell Stack   |
   //       +-------------------+
   //       | ZI: Idle Stack    |
   //       +-------------------+
   //       | ZI: Timer Stack   |
   //       +-------------------+
   //       | RW                |
   // ------+===================+  First Address of RAM
   //       |                   |
   // Flash |                   |
   //

   uint32_t bottom_of_stack = __get_MSP();
   char     * top_of_heap =  (char *) malloc(sizeof(char));
   uint32_t diff = bottom_of_stack - (uint32_t) top_of_heap;

   free((void *) top_of_heap);

   printf("Available Memory : %lu bytes", diff);
   ok();
}

void cmd_func_sleep(int argc, char* argv[]) {

}


void cmd_func_print(int argc, char* argv[]) {
   printf("\r\n");
   printf("Configuration:");

   ok();
}


void cmd_func_txf(int argc, char* argv[]) {

   if (argc == 1) {
      printf("\r\n");
      printf("%lu", radio_config.app_settings.tx_freq);
   } else if (argc > 1) {
      int freq = 0;
      if (sscanf(argv[1], "%d", &freq) == 1) {
         if (freq < 902000000 || freq > 928000000) {
            printf("Unsupported Frequency [902000000,928000000] Hz");
            error();
            return;
         } else {
            radio_config.app_settings.tx_freq = freq;
         }
      }
   } else {

   }

   ok();
}


void cmd_func_txpow(int argc, char* argv[]) {

   if (argc == 1) {
      printf("\r\n");
      printf("%u", radio_config.app_settings.tx_power);
   } else if (argc > 1) {
      int pow = 0;
      if (sscanf(argv[1], "%d", &pow) == 1) {
         if (pow < 0 || pow > 20) {
            printf("Unsupported tx power [0,20]");
            error();
            return;
         } else {
            radio_config.app_settings.tx_power = pow;
         }
      }
   } else {

   }
   ok();
}

void cmd_func_tx_iq(int argc, char* argv[]) {

   if (argc == 1) {
      printf("\r\n");
      printf("%s", radio_config.app_settings.tx_iqinv ? "true" : "false");
      ok();
   } else if (argc > 1) {
      if (strncmp(argv[1], "true", 4) != 0 && strncmp(argv[1], "false", 4) != 0) {
         printf("Invalid argument (true|false)");
         error();
         return;
      } else {
         radio_config.app_settings.tx_iqinv = (strncmp(argv[1], "true", 4) == 0);
         ok();
      }
   } else {

   }
}


void cmd_func_rx_iq(int argc, char* argv[]) {

   if (argc == 1) {
      printf("\r\n");
      printf("%s", radio_config.app_settings.tx_iqinv ? "true" : "false");
      ok();
   } else if (argc > 1) {
      if (strncmp(argv[1], "true", 4) != 0 && strncmp(argv[1], "false", 4) != 0) {
         printf("Invalid argument (true|false)");
         error();
         return;
      } else {
         radio_config.app_settings.tx_iqinv = (strncmp(argv[1], "true", 4) == 0);
         ok();
      }
   } else {

   }
}

void cmd_func_txsf(int argc, char* argv[]) {

   if (argc == 1) {
      printf("\r\n");
      printf("%u", radio_config.app_settings.tx_sf);
   } else if (argc > 1) {
      int sf = 0;
      if (sscanf(argv[1], "%d", &sf) == 1) {
         if (sf < 7 || sf > 12) {
            printf("Unsupported Spreading Factor [7,12]");
            error();
            return;
         } else {
            radio_config.app_settings.tx_sf = sf;
         }
      }
   } else {

   }
   ok();
}


void cmd_func_rxf(int argc, char* argv[]) {

   if (argc == 1) {
      printf("\r\n");
      printf("%lu", radio_config.app_settings.rx_freq);
   } else if (argc > 1) {
      int freq = 0;
      if (sscanf(argv[1], "%d", &freq) == 1) {
         if (freq < 902000000 || freq > 928000000) {
            printf("Unsupported Frequency [902000000,928000000] Hz");
            error();
            return;
         } else {
            radio_config.app_settings.rx_freq = freq;
         }
      }
   } else {

   }

   ok();
}


void cmd_func_rxsf(int argc, char* argv[]) {

   if (argc == 1) {
      printf("\r\n");
      printf("%u", radio_config.app_settings.rx_sf);
   } else if (argc > 1) {
      int sf = 0;
      if (sscanf(argv[1], "%d", &sf) == 1) {
         if (sf < 7 || sf > 12) {
            printf("Unsupported Spreading Factor [7,12]");
            error();
            return;
         } else {
            radio_config.app_settings.rx_sf = sf;
         }
      }
   } else {

   }
   ok();
}

void cmd_func_rxto(int argc, char* argv[]) {

   if (argc == 1) {
      printf("\r\n");
      printf("%lu", radio_config.app_settings.rx_timeout);
   } else if (argc > 1) {
      int sf = 0;
      if (sscanf(argv[1], "%d", &sf) == 1) {
         radio_config.app_settings.rx_timeout = sf;
      }
   } else {

   }
   ok();
}



void cmd_func_txbw(int argc, char* argv[]) {

   if (argc == 1) {
      printf("\r\n");
      printf("%u", (1 << radio_config.app_settings.tx_bw) * 125);
   } else if (argc > 1) {
      if (strcmp(argv[1], "125") == 0) {
         radio_config.app_settings.tx_bw = 0;
      } else if (strcmp(argv[1], "250") == 0) {
         radio_config.app_settings.tx_bw = 1;
      } else if (strcmp(argv[1], "500") == 0) {
         radio_config.app_settings.tx_bw = 2;
      } else {
         invalid_args();
         return;
      }
   }
   ok();
}

void cmd_func_rxbw(int argc, char* argv[]) {

   if (argc == 1) {
      printf("\r\n");
      printf("%u", (1 << radio_config.app_settings.rx_bw) * 125);
   } else if (argc > 1) {
      if (strcmp(argv[1], "125") == 0) {
         radio_config.app_settings.rx_bw = 0;
      } else if (strcmp(argv[1], "250") == 0) {
         radio_config.app_settings.rx_bw = 1;
      } else if (strcmp(argv[1], "500") == 0) {
         radio_config.app_settings.rx_bw = 2;
      } else {
         invalid_args();
         return;
      }
   }
   ok();
}

void cmd_func_send(int argc, char* argv[]) {

   if (!custom_events.get_is_idle()) {
      printf("\r\n");
      printf("Radio is not idle");
      error();
      return;
   }

   custom_events.set_is_transmitting(true);

   _radio->set_channel(radio_config.app_settings.tx_freq);



/**
     *  Sets the transmission parameters.
     *
     *  @param modem         The radio modem [0: FSK, 1: LoRa].
     *  @param power         Sets the output power [dBm].
     *  @param fdev          Sets the frequency deviation (FSK only).
     *                          FSK : [Hz]
     *                          LoRa: 0
     *  @param bandwidth     Sets the bandwidth (LoRa only).
     *                          FSK : 0
     *                          LoRa: [0: 125 kHz, 1: 250 kHz,
     *                                 2: 500 kHz, 3: Reserved]
     *  @param datarate      Sets the datarate.
     *                          FSK : 600..300000 bits/s
     *                          LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
     *                                10: 1024, 11: 2048, 12: 4096  chips]
     *  @param coderate      Sets the coding rate (LoRa only).
     *                          FSK : N/A ( set to 0 )
     *                          LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
     *  @param preamble_len  Sets the preamble length.
     *  @param fix_len       Fixed length packets [0: variable, 1: fixed].
     *  @param crc_on        Enables/disables CRC [0: OFF, 1: ON].
     *  @param freq_hop_on   Enables/disables intra-packet frequency hopping [0: OFF, 1: ON] (LoRa only).
     *  @param hop_period    The number of symbols between each hop (LoRa only).
     *  @param iq_inverted   Inverts IQ signals (LoRa only)
     *                          FSK : N/A (set to 0).
     *                          LoRa: [0: not inverted, 1: inverted]
     *  @param timeout       The transmission timeout [ms].

    virtual void set_tx_config(radio_modems_t modem, int8_t power, uint32_t fdev,
                               uint32_t bandwidth, uint32_t datarate,
                               uint8_t coderate, uint16_t preamble_len,
                               bool fix_len, bool crc_on, bool freq_hop_on,
                               uint8_t hop_period, bool iq_inverted, uint32_t timeout) = 0;
    */

   // printf("tx conf: bw: %u sf: %u iq: %d\r\n", radio_config.app_settings.tx_bw,radio_config.app_settings.tx_sf,radio_config.app_settings.tx_iqinv);

   _radio->set_tx_config(MODEM_LORA,
      radio_config.app_settings.tx_power,
      0,
      radio_config.app_settings.tx_bw,
      radio_config.app_settings.tx_sf,
      1,
      8,
      false,
      false,
      false,
      0,
      radio_config.app_settings.tx_iqinv,
      radio_config.app_settings.tx_timeout);

   _radio->send((uint8_t*)&argv[1][0], strlen(&argv[1][0]));

   ok();
}


void cmd_func_recv(int argc, char* argv[]) {

   if (!custom_events.get_is_idle()) {
      printf("\r\n");
      printf("Radio is not idle");
      error();
      return;
   }

   custom_events.set_is_receiving(true);

   _radio->set_channel(radio_config.app_settings.rx_freq);



/**
     *  Sets reception parameters.
     *
     *  @param modem         The radio modem [0: FSK, 1: LoRa].
     *  @param bandwidth     Sets the bandwidth.
     *                          FSK : >= 2600 and <= 250000 Hz
     *                          LoRa: [0: 125 kHz, 1: 250 kHz,
     *                                 2: 500 kHz, 3: Reserved]
     *  @param datarate      Sets the datarate.
     *                          FSK : 600..300000 bits/s
     *                          LoRa: [6: 64, 7: 128, 8: 256, 9: 512,
     *                                10: 1024, 11: 2048, 12: 4096  chips]
     *  @param coderate      Sets the coding rate (LoRa only).
     *                          FSK : N/A ( set to 0 )
     *                          LoRa: [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
     *  @param bandwidth_afc Sets the AFC bandwidth (FSK only).
     *                          FSK : >= 2600 and <= 250000 Hz
     *                          LoRa: N/A (set to 0)
     *  @param preamble_len  Sets the preamble length (LoRa only).
     *                          FSK : N/A (set to 0)
     *                          LoRa: Length in symbols (the hardware adds four more symbols).
     *  @param symb_timeout  Sets the RxSingle timeout value.
     *                          FSK : Timeout number of bytes
     *                          LoRa: Timeout in symbols
     *  @param fix_len        Fixed length packets [0: variable, 1: fixed].
     *  @param payload_len   Sets the payload length when fixed length is used.
     *  @param crc_on        Enables/disables CRC [0: OFF, 1: ON].
     *  @param freq_hop_on   Enables/disables intra-packet frequency hopping [0: OFF, 1: ON] (LoRa only).
     *  @param hop_period    The number of symbols bewteen each hop (LoRa only).
     *  @param iq_inverted   Inverts the IQ signals (LoRa only).
     *                          FSK : N/A (set to 0)
     *                          LoRa: [0: not inverted, 1: inverted]
     *  @param rx_continuous Sets the reception to continuous mode.
     *                          [false: single mode, true: continuous mode]

    virtual void set_rx_config(radio_modems_t modem, uint32_t bandwidth,
                               uint32_t datarate, uint8_t coderate,
                               uint32_t bandwidth_afc, uint16_t preamble_len,
                               uint16_t symb_timeout, bool fix_len,
                               uint8_t payload_len,
                               bool crc_on, bool freq_hop_on, uint8_t hop_period,
                               bool iq_inverted, bool rx_continuous) = 0;
   */

   // printf("rx conf: bw: %u sf: %u iq: %d\r\n", radio_config.app_settings.rx_bw,radio_config.app_settings.rx_sf,radio_config.app_settings.rx_iqinv);

   _radio->set_rx_config(MODEM_LORA,
      radio_config.app_settings.rx_bw,
      radio_config.app_settings.rx_sf,
      1,
      0,
      8,
      50,
      false,
      0,
      false,
      false,
      0,
      radio_config.app_settings.rx_iqinv,
      true);

   _radio->receive();

   Timer tm;
   tm.start();

   printf("\r\n");

   while(tm.read_ms() < (int)radio_config.app_settings.rx_timeout) {

      if (custom_events.get_size() > 0) {
         printf("%u ", custom_events.get_size());
         for (size_t i = 0; i < custom_events.get_size(); ++i)
            printf("%c", custom_events.get_buffer()[i]);
         printf("\r\n");
         custom_events.reset_size();
      }

      wait_ms(10);
   }

   custom_events.set_is_receiving(false);

   ok();
}



}