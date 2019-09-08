/**
 * Copyright (c) 2019, Jason Reiss
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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either expressed or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "lpwan-device-radio.h"

namespace LPWAN::Device {


	/**
	 * Callback when Transmission is done.
	 */
	void RadioEvents::tx_done()
	{
		set_is_transmitting(false);
	}

	/**
	 * Callback when Transmission is timed out.
	 */
	void RadioEvents::tx_timeout()
	{
		set_is_transmitting(false);

	}

	/**
	 * Rx Done callback prototype.
	 *
	 *  @param payload Received buffer pointer.
	 *  @param size    Received buffer size.
	 *  @param rssi    RSSI value computed while receiving the frame [dBm].
	 *  @param snr     Raw SNR value given by the radio hardware.
	 *                     FSK : N/A (set to 0)
	 *                     LoRa: SNR value in dB
	 */
	void RadioEvents::rx_done(const uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
	{

	}

	/**
	 * Callback when Reception is timed out.
	 */
	void RadioEvents::rx_timeout()
	{
	}

	/**
	 * Callback when Reception ends up in error.
	 */
	void RadioEvents::rx_error()
	{

	}

	/**
	 * FHSS Change Channel callback prototype.
	 *
	 *  @param current_channel   The index number of the current channel.
	 */
	void RadioEvents::fhss_change_channeL(uint8_t current_channel)
	{

	}

	/**
	 * CAD Done callback prototype.
	 *
	 *  @param channel_busy    True, if Channel activity detected.
	 */
	void RadioEvents::cad_done(bool channel_busy)
	{

	}

}