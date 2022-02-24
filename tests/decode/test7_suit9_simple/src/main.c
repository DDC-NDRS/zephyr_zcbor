/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include "manifest9_simple_decode.h"
#include "zcbor_debug.h" // Enables use of print functions when debugging tests.


/* draft-ietf-suit-manifest-09 Example B.2 */
uint8_t test_vector2[] = {
   0xa2, 0x02, 0x58, 0x92, 0x81, 0x58, 0x8f, 0xd2, 0x84, 0x43,
   0xa1, 0x01, 0x26, 0xa0, 0x58, 0x44, 0x82, 0x02, 0x58, 0x40,
   0x39, 0x38, 0x37, 0x65, 0x65, 0x63, 0x38, 0x35, 0x66, 0x61,
   0x39, 0x39, 0x66, 0x64, 0x33, 0x31, 0x64, 0x33, 0x33, 0x32,
   0x33, 0x38, 0x31, 0x62, 0x39, 0x38, 0x31, 0x30, 0x66, 0x39,
   0x30, 0x62, 0x30, 0x35, 0x63, 0x32, 0x65, 0x30, 0x64, 0x34,
   0x66, 0x32, 0x38, 0x34, 0x61, 0x36, 0x66, 0x34, 0x32, 0x31,
   0x31, 0x32, 0x30, 0x37, 0x65, 0x64, 0x30, 0x30, 0x66, 0x66,
   0x66, 0x37, 0x35, 0x30, 0x58, 0x40, 0x49, 0x31, 0xdf, 0x82,
   0xe1, 0x53, 0xbf, 0x1e, 0x3a, 0xf5, 0xa5, 0x98, 0x00, 0x21,
   0x6d, 0x8a, 0x47, 0xc3, 0x3a, 0x37, 0x83, 0x9e, 0x7d, 0x63,
   0xd9, 0xf5, 0x26, 0xfd, 0x36, 0x9a, 0xa8, 0x35, 0x9d, 0xaa,
   0xe1, 0x8f, 0x76, 0x19, 0xc9, 0x59, 0x12, 0x3e, 0x7f, 0x7f,
   0x92, 0x8e, 0xe9, 0x2a, 0x98, 0x93, 0xaf, 0xed, 0xd3, 0x5d,
   0x06, 0xa9, 0x36, 0xd6, 0xed, 0x3d, 0x58, 0x43, 0xbf, 0x2a,
   0x03, 0x58, 0x94, 0xa5, 0x01, 0x01, 0x02, 0x01, 0x03, 0x58,
   0x5f, 0xa2, 0x02, 0x81, 0x81, 0x41, 0x00, 0x04, 0x58, 0x56,
   0x86, 0x14, 0xa4, 0x01, 0x50, 0xfa, 0x6b, 0x4a, 0x53, 0xd5,
   0xad, 0x5f, 0xdf, 0xbe, 0x9d, 0xe6, 0x63, 0xe4, 0xd4, 0x1f,
   0xfe, 0x02, 0x50, 0x14, 0x92, 0xaf, 0x14, 0x25, 0x69, 0x5e,
   0x48, 0xbf, 0x42, 0x9b, 0x2d, 0x51, 0xf2, 0xab, 0x45, 0x03,
   0x58, 0x24, 0x82, 0x02, 0x58, 0x20, 0x00, 0x11, 0x22, 0x33,
   0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd,
   0xee, 0xff, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
   0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10, 0x0e, 0x19,
   0x87, 0xd0, 0x01, 0x0f, 0x02, 0x0f, 0x09, 0x58, 0x25, 0x86,
   0x13, 0xa1, 0x15, 0x78, 0x1b, 0x68, 0x74, 0x74, 0x70, 0x3a,
   0x2f, 0x2f, 0x65, 0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x2e,
   0x63, 0x6f, 0x6d, 0x2f, 0x66, 0x69, 0x6c, 0x65, 0x2e, 0x62,
   0x69, 0x6e, 0x15, 0x02, 0x03, 0x0f, 0x0a, 0x43, 0x82, 0x03,
   0x0f
};

uint8_t test_vector5[] = {
   0xa2, 0x02, 0x58, 0x92, 0x81, 0x58, 0x8f, 0xd2, 0x84, 0x43,
   0xa1, 0x01, 0x26, 0xa0, 0x58, 0x44, 0x82, 0x02, 0x58, 0x40,
   0x32, 0x31, 0x30, 0x62, 0x31, 0x32, 0x38, 0x35, 0x30, 0x63,
   0x32, 0x33, 0x39, 0x30, 0x39, 0x31, 0x64, 0x38, 0x65, 0x38,
   0x32, 0x63, 0x30, 0x65, 0x39, 0x65, 0x39, 0x31, 0x30, 0x36,
   0x36, 0x32, 0x62, 0x36, 0x38, 0x61, 0x63, 0x38, 0x34, 0x32,
   0x34, 0x35, 0x38, 0x61, 0x36, 0x34, 0x31, 0x38, 0x65, 0x33,
   0x33, 0x66, 0x36, 0x37, 0x30, 0x31, 0x65, 0x64, 0x35, 0x38,
   0x33, 0x34, 0x32, 0x63, 0x58, 0x40, 0xb5, 0xb8, 0xcb, 0x30,
   0xc2, 0xbb, 0xb6, 0x46, 0xc4, 0xd3, 0x24, 0x26, 0xd7, 0x27,
   0x68, 0x66, 0x8d, 0x6d, 0x6a, 0xf5, 0x4c, 0x26, 0xac, 0x46,
   0xc4, 0x02, 0x0c, 0xa3, 0x7a, 0xda, 0x47, 0xb9, 0x46, 0x83,
   0x40, 0xb4, 0xd0, 0xb2, 0xdd, 0xd1, 0x5d, 0xb8, 0x24, 0xa7,
   0xe6, 0xb0, 0xbc, 0x23, 0x3e, 0x75, 0x39, 0x40, 0xdf, 0xb7,
   0x13, 0x1f, 0xa1, 0x45, 0xdd, 0xc4, 0x56, 0xda, 0x3c, 0xf6,
   0x03, 0x59, 0x01, 0x03, 0xa6, 0x01, 0x01, 0x02, 0x05, 0x03,
   0x58, 0x95, 0xa2, 0x02, 0x82, 0x81, 0x41, 0x00, 0x81, 0x41,
   0x01, 0x04, 0x58, 0x89, 0x8c, 0x0c, 0x00, 0x14, 0xa4, 0x01,
   0x50, 0xfa, 0x6b, 0x4a, 0x53, 0xd5, 0xad, 0x5f, 0xdf, 0xbe,
   0x9d, 0xe6, 0x63, 0xe4, 0xd4, 0x1f, 0xfe, 0x02, 0x50, 0x14,
   0x92, 0xaf, 0x14, 0x25, 0x69, 0x5e, 0x48, 0xbf, 0x42, 0x9b,
   0x2d, 0x51, 0xf2, 0xab, 0x45, 0x03, 0x58, 0x24, 0x82, 0x02,
   0x58, 0x20, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
   0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x01, 0x23,
   0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98,
   0x76, 0x54, 0x32, 0x10, 0x0e, 0x19, 0x87, 0xd0, 0x01, 0x0f,
   0x02, 0x0f, 0x0c, 0x01, 0x14, 0xa2, 0x03, 0x58, 0x24, 0x82,
   0x02, 0x58, 0x20, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd,
   0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10, 0x00,
   0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa,
   0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x0e, 0x1a, 0x00, 0x01, 0x2c,
   0x22, 0x09, 0x58, 0x4f, 0x90, 0x0c, 0x00, 0x13, 0xa1, 0x15,
   0x78, 0x1c, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x65,
   0x78, 0x61, 0x6d, 0x70, 0x6c, 0x65, 0x2e, 0x63, 0x6f, 0x6d,
   0x2f, 0x66, 0x69, 0x6c, 0x65, 0x31, 0x2e, 0x62, 0x69, 0x6e,
   0x15, 0x02, 0x03, 0x0f, 0x0c, 0x01, 0x13, 0xa1, 0x15, 0x78,
   0x1c, 0x68, 0x74, 0x74, 0x70, 0x3a, 0x2f, 0x2f, 0x65, 0x78,
   0x61, 0x6d, 0x70, 0x6c, 0x65, 0x2e, 0x63, 0x6f, 0x6d, 0x2f,
   0x66, 0x69, 0x6c, 0x65, 0x32, 0x2e, 0x62, 0x69, 0x6e, 0x15,
   0x02, 0x03, 0x0f, 0x0a, 0x49, 0x88, 0x0c, 0x00, 0x03, 0x0f,
   0x0c, 0x01, 0x03, 0x0f, 0x0c, 0x47, 0x86, 0x0c, 0x00, 0x17,
   0x02, 0x17, 0x02
};

static struct SUIT_Envelope envelope1;
static struct SUIT_Manifest manifest;

void test_suit9_simple2(void)
{
	uint_fast8_t res;

	zcbor_print("test_vector at: 0x%zx\r\n", (size_t)test_vector2);
	zcbor_print("test_vector end at: 0x%zx\r\n",
				((size_t)test_vector2) + sizeof(test_vector2));
	memset(&envelope1, 0, sizeof(envelope1));
	res = cbor_decode_SUIT_Envelope(test_vector2,
					sizeof(test_vector2), &envelope1, NULL);
	zassert_equal(ZCBOR_SUCCESS, res, "top-level decoding failed.");

	res = cbor_decode_SUIT_Manifest(
		envelope1._SUIT_Envelope_suit_manifest.value,
		envelope1._SUIT_Envelope_suit_manifest.len, &manifest, NULL);

	zassert_equal(ZCBOR_SUCCESS, res, "manifest decoding failed.");
}


void test_suit9_simple5(void)
{
	uint_fast8_t res;

	zcbor_print("test_vector at: 0x%zx\r\n", (size_t)test_vector5);
	zcbor_print("test_vector end at: 0x%zx\r\n",
				((size_t)test_vector5) + sizeof(test_vector5));
	memset(&envelope1, 0, sizeof(envelope1));
	res = cbor_decode_SUIT_Envelope(test_vector5,
					sizeof(test_vector5), &envelope1, NULL);
	zassert_equal(ZCBOR_SUCCESS, res, "top-level decoding failed.");

	res = cbor_decode_SUIT_Manifest(
		envelope1._SUIT_Envelope_suit_manifest.value,
		envelope1._SUIT_Envelope_suit_manifest.len, &manifest, NULL);

	zassert_equal(ZCBOR_SUCCESS, res, "manifest decoding failed.");
}

void test_main(void)
{
	ztest_test_suite(cbor_decode_test7,
			 ztest_unit_test(test_suit9_simple2),
			 ztest_unit_test(test_suit9_simple5)
	);
	ztest_run_test_suite(cbor_decode_test7);
}
