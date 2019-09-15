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

#ifndef __LPWAN_DEVICE_RADIO_H__
#define __LPWAN_DEVICE_RADIO_H__

#include "mbed.h"

namespace LPWAN::Device {

	class RadioEvents {

	private:
		uint8_t _buffer[255];
		uint8_t _size;
		int16_t _rssi;
		int16_t _snr;
		bool _is_transmitting;
		bool _is_receiving;

	public:

		RadioEvents() :
			_is_transmitting(false),
			_is_receiving(false)
			{

			}

		bool get_is_idle() {
			return !(get_is_transmitting() || get_is_receiving());
		}

		bool get_is_transmitting() {
			return _is_transmitting;
		}

		void set_is_transmitting(bool val) {
			_is_transmitting = val;
		}

		bool get_is_receiving() {
			return _is_receiving;
		}

		void set_is_receiving(bool val) {
			if (val) _size = 0;
			_is_receiving = val;
		}

		uint8_t* get_buffer() {
			return _buffer;
		}

		void reset_size() {
			_size = 0;
		}

		uint8_t get_size() {
			return _size;
		}

		int16_t get_rssi() {
			return _rssi;
		}

		int16_t get_snr() {
			return _snr;
		}

	    /**
	     * Callback when Transmission is done.
	     */
	    void tx_done();

	    /**
	     * Callback when Transmission is timed out.
	     */
	    void tx_timeout();

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
	    void rx_done(const uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);

	    /**
	     * Callback when Reception is timed out.
	     */
	    void rx_timeout();

	    /**
	     * Callback when Reception ends up in error.
	     */
	    void rx_error();

	    /**
	     * FHSS Change Channel callback prototype.
	     *
	     *  @param current_channel   The index number of the current channel.
	     */
	    void fhss_change_channeL(uint8_t current_channel);

	    /**
	     * CAD Done callback prototype.
	     *
	     *  @param channel_busy    True, if Channel activity detected.
	     */
	    void cad_done(bool channel_busy);

	};

}

#endif // __LPWAN_DEVICE_RADIO_H__