/*
 *
 * Copyright (c) 2011-2016 The University of Waikato, Hamilton, New Zealand.
 * All rights reserved.
 *
 * This file is part of libprotoident.
 *
 * This code has been developed by the University of Waikato WAND
 * research group. For further information please see http://www.wand.net.nz/
 *
 * libprotoident is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libprotoident is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#include <string.h>

#include "libprotoident.h"
#include "proto_manager.h"
#include "proto_common.h"

static inline bool match_steam(lpi_data_t *data, lpi_module_t *mod UNUSED) {

	/* Steam TCP Download */

	if (!match_str_either(data, "\x01\x00\x00\x00"))
                return false;
        if (!match_chars_either(data, 0x00, 0x00, 0x00, ANY))
                return false;

        if (data->payload_len[0] == 4 && data->payload_len[1] == 1) {
                return true;
        }
        if (data->payload_len[0] == 4 && data->payload_len[1] == 5) {
                return true;
        }

        if (data->payload_len[1] == 4 && data->payload_len[0] == 1) {
                return true;
        }
        if (data->payload_len[1] == 4 && data->payload_len[0] == 5) {
                return true;
        }
	

	return false;
}

static lpi_module_t lpi_steam = {
	LPI_PROTO_STEAM,
	LPI_CATEGORY_GAMING,
	"Steam_TCP",
	4, /* Might not be as reliable as some other rules (?) */
	match_steam
};

void register_steam(LPIModuleMap *mod_map) {
	register_protocol(&lpi_steam, mod_map);
}

