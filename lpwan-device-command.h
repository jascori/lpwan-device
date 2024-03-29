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

#ifndef __LPWAN_DEVICE_COMMAND_H__
#define __LPWAN_DEVICE_COMMAND_H__

#include "tinysh.h"
#include "config.h"
#include "SX1272_LoRaRadio.h"

namespace LPWAN::Device {

	void tinysh_init(SX1272_LoRaRadio &radio, Serial* pc);
	void cmd_func_mem(int argc, char * argv[]);
	void cmd_func_print(int argc, char* argv[]);

	void cmd_func_send(int argc, char* argv[]);
	void cmd_func_txpow(int argc, char* argv[]);
	void cmd_func_txsf(int argc, char* argv[]);
	void cmd_func_txbw(int argc, char* argv[]);
	void cmd_func_txf(int argc, char* argv[]);
	void cmd_func_tx_iq(int argc, char* argv[]);

	void cmd_func_recv(int argc, char* argv[]);
	void cmd_func_rxto(int argc, char* argv[]);
	void cmd_func_rxsf(int argc, char* argv[]);
	void cmd_func_rxbw(int argc, char* argv[]);
	void cmd_func_rxf(int argc, char* argv[]);
	void cmd_func_rx_iq(int argc, char* argv[]);

	void cmd_func_sleep(int argc, char* argv[]);

}
#endif // __LPWAN_DEVICE_COMMAND_H__