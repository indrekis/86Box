/*
 * 86Box	A hypervisor and IBM PC system emulator that specializes in
 *		running old operating systems and software designed for IBM
 *		PC systems and compatibles from 1981 through fairly recent
 *		system designs based on the PCI bus.
 *
 *		This file is part of the 86Box distribution.
 *
 *		Implementation of Socket 423 machines.
 *
 *
 *
 * Authors:	Miran Grca, <mgrca8@gmail.com>
 *
 *		Copyright 2016-2019 Miran Grca.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <86box/86box.h>
#include <86box/mem.h>
#include <86box/io.h>
#include <86box/rom.h>
#include <86box/pci.h>
#include <86box/device.h>
#include <86box/chipset.h>
#include <86box/hwm.h>
#include <86box/keyboard.h>
#include <86box/flash.h>
#include <86box/sio.h>
#include "cpu.h"
#include <86box/machine.h>

int
machine_at_845pro_init(const machine_t *model)
{
    int ret;

    ret = bios_load_linear("roms/machines/845pro/A6529IMS.130",
			   0x000c0000, 262144, 0);

    if (bios_only || !ret)
	return ret;

    intel_ich2_setup(845, 0, 5, model);

    device_add(&w83627hf_device);
    w83627hf_stabilizer(0x7a,    /* CPU Voltage (Mendocino's are utilizing 2 Volts ) */
                        0x6f,    /* 1.8V Rail */
                        0x1c,    /* FAN 2 */
                        0x1e,    /* FAN 3 */
                        0x1d     /* FAN 1 */
    );
    device_add(&intel_flash_bxt_device); /* Needs Intel or SST FWH */

    return ret;
}
