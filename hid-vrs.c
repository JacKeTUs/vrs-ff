// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * HID driver for VRS Steering Wheels
 *
 * Copyright (c) 2024 Makarenko Oleg
 */

#include <linux/device.h>
#include <linux/hid.h>
#include <linux/module.h>
#include "hid-vrs.h"

static const struct hid_device_id vrs_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_VRS, USB_DEVICE_ID_VRS_DFP) },
	{ }
};
MODULE_DEVICE_TABLE(hid, vrs_devices);

static int vrs_probe(struct hid_device *hdev, 
				const struct hid_device_id *id) 
{
	int ret;
	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "parse failed\n");
		goto err;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	if (ret) {
		hid_err(hdev, "hw start failed\n");
		goto err;
	}

	ret = hid_pidff_init_vrs(hdev);
	if (ret) {
		hid_warn(hdev, "Force feedback not supported\n");
		goto err;
	}

	return 0;
err:
	return ret;
}

static int vrs_input_configured(struct hid_device *hdev,
				struct hid_input *hidinput) 
{
	struct input_dev *input = hidinput->input;
	input_set_abs_params(input, ABS_X, 
		input->absinfo[ABS_X].minimum, input->absinfo[ABS_X].maximum, 0, 0);

	return 0;
}

static struct hid_driver vrs_ff = {
	.name = "vrs-ff",
	.id_table = vrs_devices,
	.probe = vrs_probe,
	.input_configured = vrs_input_configured,
};
module_hid_driver(vrs_ff);

MODULE_AUTHOR("Oleg Makarenko <oleg@makarenk.ooo>");
MODULE_DESCRIPTION("VRS HID FF Driver");
MODULE_LICENSE("GPL");
