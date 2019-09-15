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
#include "tinysh.h"
#include "lpwan-device-command.h"
#include "lpwan-device-version.h"
#include "lora_radio_helper.h"

//serial port to use
Serial pc(USBTX, USBRX);


using namespace LPWAN::Device;

//mandatory tiny shell output function
void tinysh_char_out(char c)
{
    pc.putc(c);
}

int main(void){

    //configure serial baudrate
    pc.baud(115200);

    //print build date
    pc.printf("\r\n\r\n------------------------------------------------------\r\n");
    pc.printf("Dot LPWAN Command Terminal v%d.%d.%d %s %s\r\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, __DATE__,__TIME__);
    pc.printf("Source available at https://github.com/jascori/lpwan-device\r\n\r\n");
    pc.printf("(C) 2019 Jason Reiss ( jason.reiss@jascori.com )\r\n");
    pc.printf("------------------------------------------------------\r\n\r\n");

    tinysh_init(radio, &pc);

    //run command parser loop foverer
    while(true) {
        tinysh_char_in( pc.getc() );
    }

    return 0;
}