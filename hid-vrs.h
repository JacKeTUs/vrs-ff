/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __HID_VRS_H
#define __HID_VRS_H

#define USB_VENDOR_ID_VRS		0x0483
#define USB_DEVICE_ID_VRS_DFP   0xa355

int hid_pidff_init_vrs(struct hid_device *hdev);

#endif
