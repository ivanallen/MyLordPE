// Protect.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "pe.h"

char myshellcode[] = {
	0x55, 0x8b, 0xec, 0x6a, 0xff, 0x68, 0xa0, 0x67, 0x41, 0x00, 0x64, 0xa1, 0x00, 0x00, 0x00, 0x00, 0x50, 0x64, 0x89, 0x25, 0x00, 0x00, 0x00, 0x00, 0x51, 0x81, 0xec, 0x70, 0x06, 0x00, 0x00, 0x53, 0x56, 0x57, 0x89, 0x65, 0xf0, 0xc7, 0x45, 0xec, 0x01, 0x00, 0x00, 0x00, 0xc7, 0x45,
	0xe8, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x45, 0xe4, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x45, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x45, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x50, 0x64, 0xa1, 0x30, 0x00, 0x00, 0x00, 0x8b, 0x40, 0x0c, 0x8b, 0x40, 0x0c, 0x8b, 0x00, 0x8b, 0x00, 0x8b, 0x40, 0x18,
	0x89, 0x45, 0xe0, 0x58, 0xc6, 0x45, 0xd0, 0x47, 0xc6, 0x45, 0xd1, 0x65, 0xc6, 0x45, 0xd2, 0x74, 0xc6, 0x45, 0xd3, 0x50, 0xc6, 0x45, 0xd4, 0x72, 0xc6, 0x45, 0xd5, 0x6f, 0xc6, 0x45, 0xd6, 0x63, 0xc6, 0x45, 0xd7, 0x41, 0xc6, 0x45, 0xd8, 0x64, 0xc6, 0x45, 0xd9, 0x64, 0xc6, 0x45,
	0xda, 0x72, 0xc6, 0x45, 0xdb, 0x65, 0xc6, 0x45, 0xdc, 0x73, 0xc6, 0x45, 0xdd, 0x73, 0xc6, 0x45, 0xde, 0x00, 0xc7, 0x45, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x8b, 0x45, 0xe0, 0x89, 0x45, 0xc8, 0x8b, 0x45, 0xc8, 0x8b, 0x4d, 0xe0, 0x03, 0x48, 0x3c, 0x89, 0x4d, 0xc4, 0xb8, 0x08, 0x00,
	0x00, 0x00, 0x6b, 0xc8, 0x00, 0x8b, 0x55, 0xc4, 0x8b, 0x45, 0xe0, 0x03, 0x44, 0x0a, 0x78, 0x89, 0x45, 0xc0, 0x8b, 0x45, 0xc0, 0x8b, 0x4d, 0xe0, 0x03, 0x48, 0x24, 0x89, 0x4d, 0xbc, 0x8b, 0x45, 0xc0, 0x8b, 0x4d, 0xe0, 0x03, 0x48, 0x20, 0x89, 0x4d, 0xb8, 0x8b, 0x45, 0xc0, 0x8b,
	0x4d, 0xe0, 0x03, 0x48, 0x1c, 0x89, 0x4d, 0xb4, 0xc7, 0x45, 0xb0, 0x00, 0x00, 0x00, 0x00, 0xeb, 0x09, 0x8b, 0x45, 0xb0, 0x83, 0xc0, 0x01, 0x89, 0x45, 0xb0, 0x8b, 0x45, 0xc0, 0x8b, 0x4d, 0xb0, 0x3b, 0x48, 0x18, 0x0f, 0x83, 0x82, 0x00, 0x00, 0x00, 0x8b, 0x45, 0xb0, 0x8b, 0x4d,
	0xb8, 0x8b, 0x55, 0xe0, 0x03, 0x14, 0x81, 0x89, 0x55, 0xac, 0x8b, 0x45, 0xac, 0x89, 0x45, 0xa8, 0x8d, 0x45, 0xd0, 0x89, 0x45, 0xa4, 0xc6, 0x45, 0xa3, 0x01, 0x8b, 0x45, 0xa8, 0x0f, 0xbe, 0x08, 0x85, 0xc9, 0x75, 0x0a, 0x8b, 0x45, 0xa4, 0x0f, 0xbe, 0x08, 0x85, 0xc9, 0x74, 0x2a,
	0x8b, 0x45, 0xa4, 0x0f, 0xbe, 0x08, 0x8b, 0x55, 0xa8, 0x0f, 0xbe, 0x02, 0x3b, 0xc1, 0x74, 0x06, 0xc6, 0x45, 0xa3, 0x00, 0xeb, 0x14, 0x8b, 0x45, 0xa8, 0x83, 0xc0, 0x01, 0x89, 0x45, 0xa8, 0x8b, 0x45, 0xa4, 0x83, 0xc0, 0x01, 0x89, 0x45, 0xa4, 0xeb, 0xc2, 0x0f, 0xb6, 0x45, 0xa3,
	0x85, 0xc0, 0x74, 0x18, 0x8b, 0x45, 0xb0, 0x8b, 0x4d, 0xbc, 0x0f, 0xbf, 0x14, 0x41, 0x8b, 0x45, 0xb4, 0x8b, 0x4d, 0xe0, 0x03, 0x0c, 0x90, 0x89, 0x4d, 0xcc, 0xeb, 0x05, 0xe9, 0x66, 0xff, 0xff, 0xff, 0xc7, 0x45, 0xc8, 0x00, 0x00, 0x00, 0x00, 0xc7, 0x45, 0xc4, 0x00, 0x00, 0x00,
	0x00, 0xc6, 0x45, 0x90, 0x4c, 0xc6, 0x45, 0x91, 0x6f, 0xc6, 0x45, 0x92, 0x61, 0xc6, 0x45, 0x93, 0x64, 0xc6, 0x45, 0x94, 0x4c, 0xc6, 0x45, 0x95, 0x69, 0xc6, 0x45, 0x96, 0x62, 0xc6, 0x45, 0x97, 0x72, 0xc6, 0x45, 0x98, 0x61, 0xc6, 0x45, 0x99, 0x72, 0xc6, 0x45, 0x9a, 0x79, 0xc6,
	0x45, 0x9b, 0x41, 0xc6, 0x45, 0x9c, 0x00, 0xc6, 0x85, 0x7c, 0xff, 0xff, 0xff, 0x47, 0xc6, 0x85, 0x7d, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x7e, 0xff, 0xff, 0xff, 0x74, 0xc6, 0x85, 0x7f, 0xff, 0xff, 0xff, 0x4d, 0xc6, 0x45, 0x80, 0x6f, 0xc6, 0x45, 0x81, 0x64, 0xc6, 0x45, 0x82,
	0x75, 0xc6, 0x45, 0x83, 0x6c, 0xc6, 0x45, 0x84, 0x65, 0xc6, 0x45, 0x85, 0x48, 0xc6, 0x45, 0x86, 0x61, 0xc6, 0x45, 0x87, 0x6e, 0xc6, 0x45, 0x88, 0x64, 0xc6, 0x45, 0x89, 0x6c, 0xc6, 0x45, 0x8a, 0x65, 0xc6, 0x45, 0x8b, 0x41, 0xc6, 0x45, 0x8c, 0x00, 0xc6, 0x85, 0x6c, 0xff, 0xff,
	0xff, 0x43, 0xc6, 0x85, 0x6d, 0xff, 0xff, 0xff, 0x72, 0xc6, 0x85, 0x6e, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x6f, 0xff, 0xff, 0xff, 0x61, 0xc6, 0x85, 0x70, 0xff, 0xff, 0xff, 0x74, 0xc6, 0x85, 0x71, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x72, 0xff, 0xff, 0xff, 0x50, 0xc6, 0x85,
	0x73, 0xff, 0xff, 0xff, 0x72, 0xc6, 0x85, 0x74, 0xff, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0x75, 0xff, 0xff, 0xff, 0x63, 0xc6, 0x85, 0x76, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x77, 0xff, 0xff, 0xff, 0x73, 0xc6, 0x85, 0x78, 0xff, 0xff, 0xff, 0x73, 0xc6, 0x85, 0x79, 0xff, 0xff, 0xff,
	0x41, 0xc6, 0x85, 0x7a, 0xff, 0xff, 0xff, 0x00, 0xc6, 0x85, 0x58, 0xff, 0xff, 0xff, 0x47, 0xc6, 0x85, 0x59, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x5a, 0xff, 0xff, 0xff, 0x74, 0xc6, 0x85, 0x5b, 0xff, 0xff, 0xff, 0x4d, 0xc6, 0x85, 0x5c, 0xff, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0x5d,
	0xff, 0xff, 0xff, 0x64, 0xc6, 0x85, 0x5e, 0xff, 0xff, 0xff, 0x75, 0xc6, 0x85, 0x5f, 0xff, 0xff, 0xff, 0x6c, 0xc6, 0x85, 0x60, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x61, 0xff, 0xff, 0xff, 0x46, 0xc6, 0x85, 0x62, 0xff, 0xff, 0xff, 0x69, 0xc6, 0x85, 0x63, 0xff, 0xff, 0xff, 0x6c,
	0xc6, 0x85, 0x64, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x65, 0xff, 0xff, 0xff, 0x4e, 0xc6, 0x85, 0x66, 0xff, 0xff, 0xff, 0x61, 0xc6, 0x85, 0x67, 0xff, 0xff, 0xff, 0x6d, 0xc6, 0x85, 0x68, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x69, 0xff, 0xff, 0xff, 0x41, 0xc6, 0x85, 0x6a, 0xff,
	0xff, 0xff, 0x00, 0xc6, 0x85, 0x44, 0xff, 0xff, 0xff, 0x47, 0xc6, 0x85, 0x45, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x46, 0xff, 0xff, 0xff, 0x74, 0xc6, 0x85, 0x47, 0xff, 0xff, 0xff, 0x54, 0xc6, 0x85, 0x48, 0xff, 0xff, 0xff, 0x68, 0xc6, 0x85, 0x49, 0xff, 0xff, 0xff, 0x72, 0xc6,
	0x85, 0x4a, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x4b, 0xff, 0xff, 0xff, 0x61, 0xc6, 0x85, 0x4c, 0xff, 0xff, 0xff, 0x64, 0xc6, 0x85, 0x4d, 0xff, 0xff, 0xff, 0x43, 0xc6, 0x85, 0x4e, 0xff, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0x4f, 0xff, 0xff, 0xff, 0x6e, 0xc6, 0x85, 0x50, 0xff, 0xff,
	0xff, 0x74, 0xc6, 0x85, 0x51, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x52, 0xff, 0xff, 0xff, 0x78, 0xc6, 0x85, 0x53, 0xff, 0xff, 0xff, 0x74, 0xc6, 0x85, 0x54, 0xff, 0xff, 0xff, 0x00, 0xc6, 0x85, 0x30, 0xff, 0xff, 0xff, 0x52, 0xc6, 0x85, 0x31, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85,
	0x32, 0xff, 0xff, 0xff, 0x61, 0xc6, 0x85, 0x33, 0xff, 0xff, 0xff, 0x64, 0xc6, 0x85, 0x34, 0xff, 0xff, 0xff, 0x50, 0xc6, 0x85, 0x35, 0xff, 0xff, 0xff, 0x72, 0xc6, 0x85, 0x36, 0xff, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0x37, 0xff, 0xff, 0xff, 0x63, 0xc6, 0x85, 0x38, 0xff, 0xff, 0xff,
	0x65, 0xc6, 0x85, 0x39, 0xff, 0xff, 0xff, 0x73, 0xc6, 0x85, 0x3a, 0xff, 0xff, 0xff, 0x73, 0xc6, 0x85, 0x3b, 0xff, 0xff, 0xff, 0x4d, 0xc6, 0x85, 0x3c, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x3d, 0xff, 0xff, 0xff, 0x6d, 0xc6, 0x85, 0x3e, 0xff, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0x3f,
	0xff, 0xff, 0xff, 0x72, 0xc6, 0x85, 0x40, 0xff, 0xff, 0xff, 0x79, 0xc6, 0x85, 0x41, 0xff, 0xff, 0xff, 0x00, 0xc6, 0x85, 0x18, 0xff, 0xff, 0xff, 0x5a, 0xc6, 0x85, 0x19, 0xff, 0xff, 0xff, 0x77, 0xc6, 0x85, 0x1a, 0xff, 0xff, 0xff, 0x55, 0xc6, 0x85, 0x1b, 0xff, 0xff, 0xff, 0x6e,
	0xc6, 0x85, 0x1c, 0xff, 0xff, 0xff, 0x6d, 0xc6, 0x85, 0x1d, 0xff, 0xff, 0xff, 0x61, 0xc6, 0x85, 0x1e, 0xff, 0xff, 0xff, 0x70, 0xc6, 0x85, 0x1f, 0xff, 0xff, 0xff, 0x56, 0xc6, 0x85, 0x20, 0xff, 0xff, 0xff, 0x69, 0xc6, 0x85, 0x21, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x22, 0xff,
	0xff, 0xff, 0x77, 0xc6, 0x85, 0x23, 0xff, 0xff, 0xff, 0x4f, 0xc6, 0x85, 0x24, 0xff, 0xff, 0xff, 0x66, 0xc6, 0x85, 0x25, 0xff, 0xff, 0xff, 0x53, 0xc6, 0x85, 0x26, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x27, 0xff, 0xff, 0xff, 0x63, 0xc6, 0x85, 0x28, 0xff, 0xff, 0xff, 0x74, 0xc6,
	0x85, 0x29, 0xff, 0xff, 0xff, 0x69, 0xc6, 0x85, 0x2a, 0xff, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0x2b, 0xff, 0xff, 0xff, 0x6e, 0xc6, 0x85, 0x2c, 0xff, 0xff, 0xff, 0x00, 0xc6, 0x85, 0x0c, 0xff, 0xff, 0xff, 0x6e, 0xc6, 0x85, 0x0d, 0xff, 0xff, 0xff, 0x74, 0xc6, 0x85, 0x0e, 0xff, 0xff,
	0xff, 0x64, 0xc6, 0x85, 0x0f, 0xff, 0xff, 0xff, 0x6c, 0xc6, 0x85, 0x10, 0xff, 0xff, 0xff, 0x6c, 0xc6, 0x85, 0x11, 0xff, 0xff, 0xff, 0x2e, 0xc6, 0x85, 0x12, 0xff, 0xff, 0xff, 0x64, 0xc6, 0x85, 0x13, 0xff, 0xff, 0xff, 0x6c, 0xc6, 0x85, 0x14, 0xff, 0xff, 0xff, 0x6c, 0xc6, 0x85,
	0x15, 0xff, 0xff, 0xff, 0x00, 0xc6, 0x85, 0x04, 0xff, 0xff, 0xff, 0x6d, 0xc6, 0x85, 0x05, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x06, 0xff, 0xff, 0xff, 0x6d, 0xc6, 0x85, 0x07, 0xff, 0xff, 0xff, 0x63, 0xc6, 0x85, 0x08, 0xff, 0xff, 0xff, 0x70, 0xc6, 0x85, 0x09, 0xff, 0xff, 0xff,
	0x79, 0xc6, 0x85, 0x0a, 0xff, 0xff, 0xff, 0x00, 0xc6, 0x85, 0xfc, 0xfe, 0xff, 0xff, 0x6d, 0xc6, 0x85, 0xfd, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0xfe, 0xfe, 0xff, 0xff, 0x6d, 0xc6, 0x85, 0xff, 0xfe, 0xff, 0xff, 0x73, 0xc6, 0x85, 0x00, 0xff, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x01,
	0xff, 0xff, 0xff, 0x74, 0xc6, 0x85, 0x02, 0xff, 0xff, 0xff, 0x00, 0xc6, 0x85, 0xf0, 0xfe, 0xff, 0xff, 0x6d, 0xc6, 0x85, 0xf1, 0xfe, 0xff, 0xff, 0x73, 0xc6, 0x85, 0xf2, 0xfe, 0xff, 0xff, 0x76, 0xc6, 0x85, 0xf3, 0xfe, 0xff, 0xff, 0x63, 0xc6, 0x85, 0xf4, 0xfe, 0xff, 0xff, 0x72,
	0xc6, 0x85, 0xf5, 0xfe, 0xff, 0xff, 0x74, 0xc6, 0x85, 0xf6, 0xfe, 0xff, 0xff, 0x2e, 0xc6, 0x85, 0xf7, 0xfe, 0xff, 0xff, 0x64, 0xc6, 0x85, 0xf8, 0xfe, 0xff, 0xff, 0x6c, 0xc6, 0x85, 0xf9, 0xfe, 0xff, 0xff, 0x6c, 0xc6, 0x85, 0xfa, 0xfe, 0xff, 0xff, 0x00, 0xc6, 0x85, 0xe8, 0xfe,
	0xff, 0xff, 0x6d, 0xc6, 0x85, 0xe9, 0xfe, 0xff, 0xff, 0x61, 0xc6, 0x85, 0xea, 0xfe, 0xff, 0xff, 0x6c, 0xc6, 0x85, 0xeb, 0xfe, 0xff, 0xff, 0x6c, 0xc6, 0x85, 0xec, 0xfe, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0xed, 0xfe, 0xff, 0xff, 0x63, 0xc6, 0x85, 0xee, 0xfe, 0xff, 0xff, 0x00, 0xc6,
	0x85, 0xe0, 0xfe, 0xff, 0xff, 0x66, 0xc6, 0x85, 0xe1, 0xfe, 0xff, 0xff, 0x72, 0xc6, 0x85, 0xe2, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0xe3, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0xe4, 0xfe, 0xff, 0xff, 0x00, 0xc6, 0x85, 0xd0, 0xfe, 0xff, 0xff, 0x56, 0xc6, 0x85, 0xd1, 0xfe, 0xff,
	0xff, 0x69, 0xc6, 0x85, 0xd2, 0xfe, 0xff, 0xff, 0x72, 0xc6, 0x85, 0xd3, 0xfe, 0xff, 0xff, 0x74, 0xc6, 0x85, 0xd4, 0xfe, 0xff, 0xff, 0x75, 0xc6, 0x85, 0xd5, 0xfe, 0xff, 0xff, 0x61, 0xc6, 0x85, 0xd6, 0xfe, 0xff, 0xff, 0x6c, 0xc6, 0x85, 0xd7, 0xfe, 0xff, 0xff, 0x41, 0xc6, 0x85,
	0xd8, 0xfe, 0xff, 0xff, 0x6c, 0xc6, 0x85, 0xd9, 0xfe, 0xff, 0xff, 0x6c, 0xc6, 0x85, 0xda, 0xfe, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0xdb, 0xfe, 0xff, 0xff, 0x63, 0xc6, 0x85, 0xdc, 0xfe, 0xff, 0xff, 0x45, 0xc6, 0x85, 0xdd, 0xfe, 0xff, 0xff, 0x78, 0xc6, 0x85, 0xde, 0xfe, 0xff, 0xff,
	0x00, 0xc6, 0x85, 0xbc, 0xfe, 0xff, 0xff, 0x57, 0xc6, 0x85, 0xbd, 0xfe, 0xff, 0xff, 0x72, 0xc6, 0x85, 0xbe, 0xfe, 0xff, 0xff, 0x69, 0xc6, 0x85, 0xbf, 0xfe, 0xff, 0xff, 0x74, 0xc6, 0x85, 0xc0, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0xc1, 0xfe, 0xff, 0xff, 0x50, 0xc6, 0x85, 0xc2,
	0xfe, 0xff, 0xff, 0x72, 0xc6, 0x85, 0xc3, 0xfe, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0xc4, 0xfe, 0xff, 0xff, 0x63, 0xc6, 0x85, 0xc5, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0xc6, 0xfe, 0xff, 0xff, 0x73, 0xc6, 0x85, 0xc7, 0xfe, 0xff, 0xff, 0x73, 0xc6, 0x85, 0xc8, 0xfe, 0xff, 0xff, 0x4d,
	0xc6, 0x85, 0xc9, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0xca, 0xfe, 0xff, 0xff, 0x6d, 0xc6, 0x85, 0xcb, 0xfe, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0xcc, 0xfe, 0xff, 0xff, 0x72, 0xc6, 0x85, 0xcd, 0xfe, 0xff, 0xff, 0x79, 0xc6, 0x85, 0xce, 0xfe, 0xff, 0xff, 0x00, 0xc6, 0x85, 0xa8, 0xfe,
	0xff, 0xff, 0x53, 0xc6, 0x85, 0xa9, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0xaa, 0xfe, 0xff, 0xff, 0x74, 0xc6, 0x85, 0xab, 0xfe, 0xff, 0xff, 0x54, 0xc6, 0x85, 0xac, 0xfe, 0xff, 0xff, 0x68, 0xc6, 0x85, 0xad, 0xfe, 0xff, 0xff, 0x72, 0xc6, 0x85, 0xae, 0xfe, 0xff, 0xff, 0x65, 0xc6,
	0x85, 0xaf, 0xfe, 0xff, 0xff, 0x61, 0xc6, 0x85, 0xb0, 0xfe, 0xff, 0xff, 0x64, 0xc6, 0x85, 0xb1, 0xfe, 0xff, 0xff, 0x43, 0xc6, 0x85, 0xb2, 0xfe, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0xb3, 0xfe, 0xff, 0xff, 0x6e, 0xc6, 0x85, 0xb4, 0xfe, 0xff, 0xff, 0x74, 0xc6, 0x85, 0xb5, 0xfe, 0xff,
	0xff, 0x65, 0xc6, 0x85, 0xb6, 0xfe, 0xff, 0xff, 0x78, 0xc6, 0x85, 0xb7, 0xfe, 0xff, 0xff, 0x74, 0xc6, 0x85, 0xb8, 0xfe, 0xff, 0xff, 0x00, 0xc6, 0x85, 0x98, 0xfe, 0xff, 0xff, 0x52, 0xc6, 0x85, 0x99, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x9a, 0xfe, 0xff, 0xff, 0x73, 0xc6, 0x85,
	0x9b, 0xfe, 0xff, 0xff, 0x75, 0xc6, 0x85, 0x9c, 0xfe, 0xff, 0xff, 0x6d, 0xc6, 0x85, 0x9d, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x9e, 0xfe, 0xff, 0xff, 0x54, 0xc6, 0x85, 0x9f, 0xfe, 0xff, 0xff, 0x68, 0xc6, 0x85, 0xa0, 0xfe, 0xff, 0xff, 0x72, 0xc6, 0x85, 0xa1, 0xfe, 0xff, 0xff,
	0x65, 0xc6, 0x85, 0xa2, 0xfe, 0xff, 0xff, 0x61, 0xc6, 0x85, 0xa3, 0xfe, 0xff, 0xff, 0x64, 0xc6, 0x85, 0xa4, 0xfe, 0xff, 0xff, 0x00, 0xc6, 0x85, 0x84, 0xfe, 0xff, 0xff, 0x54, 0xc6, 0x85, 0x85, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x86, 0xfe, 0xff, 0xff, 0x72, 0xc6, 0x85, 0x87,
	0xfe, 0xff, 0xff, 0x6d, 0xc6, 0x85, 0x88, 0xfe, 0xff, 0xff, 0x69, 0xc6, 0x85, 0x89, 0xfe, 0xff, 0xff, 0x6e, 0xc6, 0x85, 0x8a, 0xfe, 0xff, 0xff, 0x61, 0xc6, 0x85, 0x8b, 0xfe, 0xff, 0xff, 0x74, 0xc6, 0x85, 0x8c, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x8d, 0xfe, 0xff, 0xff, 0x50,
	0xc6, 0x85, 0x8e, 0xfe, 0xff, 0xff, 0x72, 0xc6, 0x85, 0x8f, 0xfe, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0x90, 0xfe, 0xff, 0xff, 0x63, 0xc6, 0x85, 0x91, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x92, 0xfe, 0xff, 0xff, 0x73, 0xc6, 0x85, 0x93, 0xfe, 0xff, 0xff, 0x73, 0xc6, 0x85, 0x94, 0xfe,
	0xff, 0xff, 0x00, 0xc6, 0x85, 0x78, 0xfe, 0xff, 0xff, 0x45, 0xc6, 0x85, 0x79, 0xfe, 0xff, 0xff, 0x78, 0xc6, 0x85, 0x7a, 0xfe, 0xff, 0xff, 0x69, 0xc6, 0x85, 0x7b, 0xfe, 0xff, 0xff, 0x74, 0xc6, 0x85, 0x7c, 0xfe, 0xff, 0xff, 0x50, 0xc6, 0x85, 0x7d, 0xfe, 0xff, 0xff, 0x72, 0xc6,
	0x85, 0x7e, 0xfe, 0xff, 0xff, 0x6f, 0xc6, 0x85, 0x7f, 0xfe, 0xff, 0xff, 0x63, 0xc6, 0x85, 0x80, 0xfe, 0xff, 0xff, 0x65, 0xc6, 0x85, 0x81, 0xfe, 0xff, 0xff, 0x73, 0xc6, 0x85, 0x82, 0xfe, 0xff, 0xff, 0x73, 0xc6, 0x85, 0x83, 0xfe, 0xff, 0xff, 0x00, 0x8d, 0x45, 0x90, 0x50, 0x8b,
	0x4d, 0xe0, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x74, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0x7c, 0xff, 0xff, 0xff, 0x50, 0x8b, 0x4d, 0xe0, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95,
	0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x70, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0x6c, 0xff, 0xff, 0xff, 0x50, 0x8b, 0x4d, 0xe0, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x6c, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0x58, 0xff,
	0xff, 0xff, 0x50, 0x8b, 0x4d, 0xe0, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x68, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0x44, 0xff, 0xff, 0xff, 0x50, 0x8b, 0x4d, 0xe0, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9,
	0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x64, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0x30, 0xff, 0xff, 0xff, 0x50, 0x8b, 0x4d, 0xe0, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x60, 0xfe, 0xff, 0xff,
	0x8d, 0x85, 0xbc, 0xfe, 0xff, 0xff, 0x50, 0x8b, 0x4d, 0xe0, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x5c, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0xd0, 0xfe, 0xff, 0xff, 0x50, 0x8b, 0x4d, 0xe0, 0x51, 0xff, 0x55, 0xcc,
	0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x58, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0xa8, 0xfe, 0xff, 0xff, 0x50, 0x8b, 0x4d, 0xe0, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95,
	0x54, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0x98, 0xfe, 0xff, 0xff, 0x50, 0x8b, 0x4d, 0xe0, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x50, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0x84, 0xfe, 0xff, 0xff, 0x50, 0x8b, 0x4d, 0xe0,
	0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x55, 0xe4, 0x8d, 0x85, 0x78, 0xfe, 0xff, 0xff, 0x50, 0x8b, 0x4d, 0xe0, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89,
	0x95, 0x4c, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0x0c, 0xff, 0xff, 0xff, 0x50, 0xff, 0x95, 0x70, 0xfe, 0xff, 0xff, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x8d, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x8d, 0x48, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0x18, 0xff, 0xff, 0xff, 0x50, 0x8b, 0x8d, 0x48,
	0xfe, 0xff, 0xff, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x44, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0x04, 0xff, 0xff, 0xff, 0x50, 0x8b, 0x8d, 0x48, 0xfe, 0xff, 0xff, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9,
	0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x40, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0xfc, 0xfe, 0xff, 0xff, 0x50, 0x8b, 0x8d, 0x48, 0xfe, 0xff, 0xff, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x3c,
	0xfe, 0xff, 0xff, 0x8d, 0x85, 0xf0, 0xfe, 0xff, 0xff, 0x50, 0xff, 0x95, 0x74, 0xfe, 0xff, 0xff, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x8d, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x8d, 0x38, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0xe8, 0xfe, 0xff, 0xff, 0x50, 0x8b, 0x8d, 0x38, 0xfe, 0xff,
	0xff, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x34, 0xfe, 0xff, 0xff, 0x8d, 0x85, 0xe0, 0xfe, 0xff, 0xff, 0x50, 0x8b, 0x8d, 0x38, 0xfe, 0xff, 0xff, 0x51, 0xff, 0x55, 0xcc, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff,
	0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x30, 0xfe, 0xff, 0xff, 0x6a, 0x00, 0xff, 0x95, 0x70, 0xfe, 0xff, 0xff, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x85, 0x2c, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0x2c, 0xfe, 0xff, 0xff, 0x89, 0x45,
	0xc8, 0x8b, 0x45, 0xc8, 0x8b, 0x8d, 0x2c, 0xfe, 0xff, 0xff, 0x03, 0x48, 0x3c, 0x89, 0x4d, 0xc4, 0x8b, 0x45, 0xc4, 0x0f, 0xb7, 0x48, 0x14, 0x8b, 0x55, 0xc4, 0x8d, 0x44, 0x0a, 0x18, 0x89, 0x85, 0x28, 0xfe, 0xff, 0xff, 0x8b, 0x45, 0xc4, 0x0f, 0xb7, 0x48, 0x06, 0x6b, 0xd1, 0x28,
	0x8b, 0x85, 0x28, 0xfe, 0xff, 0xff, 0x8d, 0x4c, 0x10, 0xd8, 0x89, 0x8d, 0x28, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0x28, 0xfe, 0xff, 0xff, 0x8b, 0x48, 0x0c, 0x8b, 0x95, 0x2c, 0xfe, 0xff, 0xff, 0x8d, 0x84, 0x0a, 0x00, 0x20, 0x00, 0x00, 0x89, 0x85, 0x24, 0xfe, 0xff, 0xff, 0x8b, 0x85,
	0x28, 0xfe, 0xff, 0xff, 0x8b, 0x48, 0x10, 0x81, 0xe9, 0x00, 0x20, 0x00, 0x00, 0x89, 0x8d, 0x20, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0x24, 0xfe, 0xff, 0xff, 0x89, 0x45, 0xc8, 0x8b, 0x45, 0xc8, 0x8b, 0x8d, 0x24, 0xfe, 0xff, 0xff, 0x03, 0x48, 0x3c, 0x89, 0x4d, 0xc4, 0x8b, 0x45, 0xc4,
	0x83, 0xc0, 0x18, 0x89, 0x85, 0x1c, 0xfe, 0xff, 0xff, 0x8b, 0x45, 0xc4, 0x0f, 0xb7, 0x48, 0x14, 0x03, 0x8d, 0x1c, 0xfe, 0xff, 0xff, 0x89, 0x8d, 0x28, 0xfe, 0xff, 0xff, 0x8b, 0x45, 0xc4, 0x0f, 0xb7, 0x48, 0x06, 0x83, 0xe9, 0x01, 0x6b, 0xd1, 0x28, 0x8b, 0x45, 0xc4, 0x0f, 0xb7,
	0x48, 0x06, 0x83, 0xe9, 0x01, 0x6b, 0xc1, 0x28, 0x8b, 0x8d, 0x28, 0xfe, 0xff, 0xff, 0x8b, 0x44, 0x01, 0x0c, 0x8b, 0x8d, 0x28, 0xfe, 0xff, 0xff, 0x03, 0x44, 0x11, 0x10, 0x89, 0x85, 0x18, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0x1c, 0xfe, 0xff, 0xff, 0x8b, 0x8d, 0x18, 0xfe, 0xff, 0xff,
	0x3b, 0x48, 0x38, 0x76, 0x0e, 0x8b, 0x95, 0x18, 0xfe, 0xff, 0xff, 0x89, 0x95, 0x80, 0xf9, 0xff, 0xff, 0xeb, 0x0f, 0x8b, 0x85, 0x1c, 0xfe, 0xff, 0xff, 0x8b, 0x48, 0x38, 0x89, 0x8d, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0x18, 0xfe, 0xff, 0xff,
	0x8b, 0x85, 0x18, 0xfe, 0xff, 0xff, 0x50, 0xff, 0x95, 0x34, 0xfe, 0xff, 0xff, 0x83, 0xc4, 0x04, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x8d, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x8d, 0x14, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0x18, 0xfe, 0xff, 0xff, 0x50, 0x6a, 0x00, 0x8b, 0x8d, 0x14,
	0xfe, 0xff, 0xff, 0x51, 0xff, 0x95, 0x3c, 0xfe, 0xff, 0xff, 0x83, 0xc4, 0x0c, 0x8b, 0x85, 0x1c, 0xfe, 0xff, 0xff, 0x8b, 0x48, 0x3c, 0x51, 0x8b, 0x95, 0x24, 0xfe, 0xff, 0xff, 0x52, 0x8b, 0x85, 0x14, 0xfe, 0xff, 0xff, 0x50, 0xff, 0x95, 0x40, 0xfe, 0xff, 0xff, 0x83, 0xc4, 0x0c,
	0xc7, 0x85, 0x10, 0xfe, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xeb, 0x0f, 0x8b, 0x85, 0x10, 0xfe, 0xff, 0xff, 0x83, 0xc0, 0x01, 0x89, 0x85, 0x10, 0xfe, 0xff, 0xff, 0x8b, 0x45, 0xc4, 0x0f, 0xb7, 0x48, 0x06, 0x39, 0x8d, 0x10, 0xfe, 0xff, 0xff, 0x7d, 0x44, 0x8b, 0x85, 0x28, 0xfe,
	0xff, 0xff, 0x8b, 0x48, 0x10, 0x51, 0x8b, 0x95, 0x28, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0x24, 0xfe, 0xff, 0xff, 0x03, 0x42, 0x14, 0x50, 0x8b, 0x8d, 0x28, 0xfe, 0xff, 0xff, 0x8b, 0x95, 0x14, 0xfe, 0xff, 0xff, 0x03, 0x51, 0x0c, 0x52, 0xff, 0x95, 0x40, 0xfe, 0xff, 0xff, 0x83, 0xc4,
	0x0c, 0x8b, 0x85, 0x28, 0xfe, 0xff, 0xff, 0x83, 0xc0, 0x28, 0x89, 0x85, 0x28, 0xfe, 0xff, 0xff, 0xeb, 0x9e, 0x68, 0x04, 0x01, 0x00, 0x00, 0x8d, 0x85, 0x0c, 0xfd, 0xff, 0xff, 0x50, 0x6a, 0x00, 0xff, 0x95, 0x68, 0xfe, 0xff, 0xff, 0x6a, 0x44, 0x6a, 0x00, 0x8d, 0x85, 0xc8, 0xfc,
	0xff, 0xff, 0x50, 0xff, 0x95, 0x3c, 0xfe, 0xff, 0xff, 0x83, 0xc4, 0x0c, 0x6a, 0x10, 0x6a, 0x00, 0x8d, 0x85, 0xb8, 0xfc, 0xff, 0xff, 0x50, 0xff, 0x95, 0x3c, 0xfe, 0xff, 0xff, 0x83, 0xc4, 0x0c, 0xc7, 0x85, 0xc8, 0xfc, 0xff, 0xff, 0x44, 0x00, 0x00, 0x00, 0x8d, 0x85, 0xb8, 0xfc,
	0xff, 0xff, 0x50, 0x8d, 0x8d, 0xc8, 0xfc, 0xff, 0xff, 0x51, 0x6a, 0x00, 0x6a, 0x00, 0x6a, 0x04, 0x6a, 0x00, 0x6a, 0x00, 0x6a, 0x00, 0x8d, 0x95, 0x0c, 0xfd, 0xff, 0xff, 0x52, 0x6a, 0x00, 0xff, 0x95, 0x6c, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0xb8, 0xfc, 0xff, 0xff, 0x89, 0x45, 0xe8,
	0xc7, 0x85, 0xec, 0xf9, 0xff, 0xff, 0x07, 0x00, 0x01, 0x00, 0x8d, 0x85, 0xec, 0xf9, 0xff, 0xff, 0x50, 0x8b, 0x8d, 0xbc, 0xfc, 0xff, 0xff, 0x51, 0xff, 0x95, 0x64, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0x9c, 0xfa, 0xff, 0xff, 0x89, 0x85, 0xe8, 0xf9, 0xff, 0xff, 0x8b, 0x85, 0x90, 0xfa,
	0xff, 0xff, 0x83, 0xc0, 0x08, 0x89, 0x85, 0xe4, 0xf9, 0xff, 0xff, 0xc7, 0x85, 0xe0, 0xf9, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x6a, 0x00, 0x6a, 0x04, 0x8d, 0x85, 0xe0, 0xf9, 0xff, 0xff, 0x50, 0x8b, 0x8d, 0xe4, 0xf9, 0xff, 0xff, 0x51, 0x8b, 0x95, 0xb8, 0xfc, 0xff, 0xff, 0x52,
	0xff, 0x95, 0x60, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0xe0, 0xf9, 0xff, 0xff, 0x50, 0x8b, 0x8d, 0xb8, 0xfc, 0xff, 0xff, 0x51, 0xff, 0x95, 0x44, 0xfe, 0xff, 0xff, 0x6a, 0x40, 0x68, 0x00, 0x30, 0x00, 0x00, 0x8b, 0x85, 0x1c, 0xfe, 0xff, 0xff, 0x8b, 0x48, 0x38, 0x51, 0x8b, 0x95, 0x1c,
	0xfe, 0xff, 0xff, 0x8b, 0x42, 0x1c, 0x50, 0x8b, 0x8d, 0xb8, 0xfc, 0xff, 0xff, 0x51, 0xff, 0x95, 0x58, 0xfe, 0xff, 0xff, 0x89, 0x85, 0x80, 0xf9, 0xff, 0xff, 0x8b, 0x95, 0x80, 0xf9, 0xff, 0xff, 0x89, 0x95, 0xdc, 0xf9, 0xff, 0xff, 0x83, 0xbd, 0xdc, 0xf9, 0xff, 0xff, 0x00, 0x0f,
	0x85, 0x64, 0x01, 0x00, 0x00, 0x6a, 0x40, 0x68, 0x00, 0x30, 0x00, 0x00, 0x8b, 0x85, 0x1c, 0xfe, 0xff, 0xff, 0x8b, 0x48, 0x38, 0x51, 0x6a, 0x00, 0x8b, 0x95, 0xb8, 0xfc, 0xff, 0xff, 0x52, 0xff, 0x95, 0x58, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0x14, 0xfe, 0xff, 0xff, 0x89, 0x45, 0xc8,
	0x8b, 0x45, 0xc8, 0x8b, 0x8d, 0x14, 0xfe, 0xff, 0xff, 0x03, 0x48, 0x3c, 0x89, 0x4d, 0xc4, 0x8b, 0x45, 0xc4, 0x83, 0xc0, 0x18, 0x89, 0x85, 0xd8, 0xf9, 0xff, 0xff, 0xb8, 0x08, 0x00, 0x00, 0x00, 0x6b, 0xc8, 0x05, 0x8b, 0x95, 0xd8, 0xf9, 0xff, 0xff, 0x8b, 0x85, 0x14, 0xfe, 0xff,
	0xff, 0x03, 0x44, 0x0a, 0x60, 0x89, 0x85, 0xd4, 0xf9, 0xff, 0xff, 0x8b, 0x85, 0xd4, 0xf9, 0xff, 0xff, 0x83, 0x78, 0x04, 0x00, 0x75, 0x0f, 0x8b, 0x85, 0xd4, 0xf9, 0xff, 0xff, 0x83, 0x38, 0x00, 0x0f, 0x84, 0xd8, 0x00, 0x00, 0x00, 0x8b, 0x85, 0xd4, 0xf9, 0xff, 0xff, 0x83, 0xc0,
	0x08, 0x89, 0x85, 0xd0, 0xf9, 0xff, 0xff, 0x8b, 0x85, 0xd4, 0xf9, 0xff, 0xff, 0x8b, 0x48, 0x04, 0x83, 0xe9, 0x08, 0xd1, 0xe9, 0x89, 0x8d, 0xcc, 0xf9, 0xff, 0xff, 0xc7, 0x85, 0xc8, 0xf9, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xeb, 0x0f, 0x8b, 0x85, 0xc8, 0xf9, 0xff, 0xff, 0x83,
	0xc0, 0x01, 0x89, 0x85, 0xc8, 0xf9, 0xff, 0xff, 0x8b, 0x85, 0xc8, 0xf9, 0xff, 0xff, 0x3b, 0x85, 0xcc, 0xf9, 0xff, 0xff, 0x7d, 0x72, 0x8b, 0x85, 0xc8, 0xf9, 0xff, 0xff, 0x8b, 0x8d, 0xd0, 0xf9, 0xff, 0xff, 0x0f, 0xbf, 0x14, 0x41, 0x81, 0xe2, 0xff, 0x0f, 0x00, 0x00, 0x8b, 0x85,
	0xd4, 0xf9, 0xff, 0xff, 0x03, 0x10, 0x89, 0x95, 0xc4, 0xf9, 0xff, 0xff, 0x8b, 0x85, 0xc8, 0xf9, 0xff, 0xff, 0x8b, 0x8d, 0xd0, 0xf9, 0xff, 0xff, 0x0f, 0xbf, 0x14, 0x41, 0x81, 0xe2, 0x00, 0xf0, 0x00, 0x00, 0xc1, 0xfa, 0x0c, 0x83, 0xfa, 0x03, 0x75, 0x2b, 0x8b, 0x85, 0xd8, 0xf9,
	0xff, 0xff, 0x8b, 0x8d, 0xdc, 0xf9, 0xff, 0xff, 0x2b, 0x48, 0x1c, 0x8b, 0x95, 0xc4, 0xf9, 0xff, 0xff, 0x03, 0x95, 0x14, 0xfe, 0xff, 0xff, 0x03, 0x0a, 0x8b, 0x85, 0xc4, 0xf9, 0xff, 0xff, 0x03, 0x85, 0x14, 0xfe, 0xff, 0xff, 0x89, 0x08, 0xe9, 0x71, 0xff, 0xff, 0xff, 0x8b, 0x85,
	0xd4, 0xf9, 0xff, 0xff, 0x8b, 0x8d, 0xd4, 0xf9, 0xff, 0xff, 0x03, 0x48, 0x04, 0x89, 0x8d, 0xd4, 0xf9, 0xff, 0xff, 0xe9, 0x0d, 0xff, 0xff, 0xff, 0x8b, 0x85, 0xd8, 0xf9, 0xff, 0xff, 0x8b, 0x8d, 0xdc, 0xf9, 0xff, 0xff, 0x89, 0x48, 0x1c, 0x6a, 0x00, 0x8b, 0x85, 0x1c, 0xfe, 0xff,
	0xff, 0x8b, 0x48, 0x38, 0x51, 0x8b, 0x95, 0x14, 0xfe, 0xff, 0xff, 0x52, 0x8b, 0x85, 0xdc, 0xf9, 0xff, 0xff, 0x50, 0x8b, 0x8d, 0xb8, 0xfc, 0xff, 0xff, 0x51, 0xff, 0x95, 0x5c, 0xfe, 0xff, 0xff, 0x6a, 0x00, 0x6a, 0x04, 0x8d, 0x85, 0xdc, 0xf9, 0xff, 0xff, 0x50, 0x8b, 0x8d, 0x90,
	0xfa, 0xff, 0xff, 0x83, 0xc1, 0x08, 0x51, 0x8b, 0x95, 0xb8, 0xfc, 0xff, 0xff, 0x52, 0xff, 0x95, 0x5c, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0x1c, 0xfe, 0xff, 0xff, 0x8b, 0x48, 0x1c, 0x8b, 0x95, 0x1c, 0xfe, 0xff, 0xff, 0x03, 0x4a, 0x10, 0x89, 0x8d, 0x9c, 0xfa, 0xff, 0xff, 0x8d, 0x85,
	0xec, 0xf9, 0xff, 0xff, 0x50, 0x8b, 0x8d, 0xbc, 0xfc, 0xff, 0xff, 0x51, 0xff, 0x95, 0x54, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0xbc, 0xfc, 0xff, 0xff, 0x50, 0xff, 0x95, 0x50, 0xfe, 0xff, 0xff, 0x8b, 0x85, 0x14, 0xfe, 0xff, 0xff, 0x50, 0xff, 0x95, 0x30, 0xfe, 0xff, 0xff, 0x83, 0xc4,
	0x04, 0x6a, 0x00, 0xff, 0x95, 0x4c, 0xfe, 0xff, 0xff, 0xeb, 0x1b, 0x83, 0x7d, 0xe8, 0x00, 0x74, 0x09, 0x6a, 0x00, 0x8b, 0x45, 0xe8, 0x50, 0xff, 0x55, 0xe4, 0xb8, 0x8d, 0x40, 0x41, 0x00, 0xc3, 0xb8, 0x84, 0x40, 0x41, 0x00, 0xc3, 0xc7, 0x45, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xeb,
	0x07, 0xc7, 0x45, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x8b, 0x4d, 0xf4, 0x64, 0x89, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x5f, 0x5e, 0x5b, 0x8b, 0xe5, 0x5d, 0xc3, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc
};
void Decrypt();
int _tmain(int argc, _TCHAR* argv[])
{
	char* szShell = "../Debug/LordPE.exe";
	char* szObj = "../Debug/IPMSG.exe";

	HPE shell = loadPE(szShell);
	HPE object = loadPE(szObj);

	int length = getFileLength(object);
	BYTE* src = getFileBuffer(object);
	HPE newObj = addSection(shell, ".src", length + 0x2000, 0x60000020);
	IMAGE_OPTIONAL_HEADER32* pOptionalHeader = getOptionalHeader(newObj);
	
	IMAGE_SECTION_HEADER* pShellSection = getLastSection(newObj);
	pOptionalHeader->AddressOfEntryPoint = pShellSection->VirtualAddress;
	memcpy((void*)(pShellSection->PointerToRawData + (int)getFileBuffer(newObj)), myshellcode, sizeof(myshellcode));
	memcpy((void*)(pShellSection->PointerToRawData + (int)getFileBuffer(newObj) + 0x2000), src, length);
	
	//Decrypt();
	writeFile("../Debug/test.exe", newObj);
	releasePE(newObj);
	return 0;
}

//typedef struct _LDR_DATA_TABLE_ENTRY
//{
//	LIST_ENTRY InLoadOrderLinks;
//	LIST_ENTRY InMemoryOrderLinks;
//	LIST_ENTRY InInitializationOrderLinks;
//	PVOID DllBase;
//	PVOID EntryPoint;
//	ULONG SizeOfImage;
//	UNICODE_STRING FullDllName;
//	UNICODE_STRING BaseDllName;
//	ULONG Flags;
//	WORD LoadCount;
//	WORD TlsIndex;
//	union
//	{
//		LIST_ENTRY HashLinks;
//		struct
//		{
//			PVOID SectionPointer;
//			ULONG CheckSum;
//		};
//	};
//	union
//	{
//		ULONG TimeDateStamp;
//		PVOID LoadedImports;
//	};
//	_ACTIVATION_CONTEXT * EntryPointActivationContext;
//	PVOID PatchInformation;
//	LIST_ENTRY ForwarderLinks;
//	LIST_ENTRY ServiceTagLinks;
//	LIST_ENTRY StaticLinks;
//} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef FARPROC (WINAPI *GETPROCADDRESS)(_In_ HMODULE hModule, _In_ LPCSTR  lpProcName);
typedef HMODULE (WINAPI *LOADLIBRARY)(_In_ LPCSTR lpFileName);
typedef HMODULE (WINAPI *GETMODULEHANDLE)(_In_opt_ LPCSTR lpModuleName);
typedef BOOL (WINAPI *SETTHREADCONTEXT)(_In_ HANDLE hThread, _In_ const CONTEXT *lpContext);
typedef DWORD (WINAPI *GETMODULEFILENAME)(_In_opt_ HMODULE hModule, _Out_ LPSTR lpFilename, _In_ DWORD nSize);
typedef BOOL (WINAPI *GETTHREADCONTEXT)(_In_ HANDLE hThread, _Inout_ LPCONTEXT lpContext);
typedef DWORD (WINAPI *RESUMETHREAD)(_In_ HANDLE hThread);
typedef VOID (WINAPI *EXITPROCESS)(_In_ UINT uExitCode);



typedef BOOL(WINAPI *CREATEPROCESS)(
	_In_opt_    LPCSTR               lpApplicationName,
	_Inout_opt_ LPSTR                lpCommandLine,
	_In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes,
	_In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_        BOOL                  bInheritHandles,
	_In_        DWORD                 dwCreationFlags,
	_In_opt_    LPVOID                lpEnvironment,
	_In_opt_    LPCSTR               lpCurrentDirectory,
	_In_        LPSTARTUPINFO         lpStartupInfo,
	_Out_       LPPROCESS_INFORMATION lpProcessInformation
	);
typedef BOOL (WINAPI *READPROCESSMEMORY)(
	_In_  HANDLE  hProcess,
	_In_  LPCVOID lpBaseAddress,
	_Out_ LPVOID  lpBuffer,
	_In_  SIZE_T  nSize,
	_Out_ SIZE_T  *lpNumberOfBytesRead
	);
typedef LPVOID (WINAPI *VIRTUALALLOCEX)(
	_In_     HANDLE hProcess,
	_In_opt_ LPVOID lpAddress,
	_In_     SIZE_T dwSize,
	_In_     DWORD  flAllocationType,
	_In_     DWORD  flProtect
	);
typedef BOOL (WINAPI *WRITEPROCESSMEMORY)(
	_In_  HANDLE  hProcess,
	_In_  LPVOID  lpBaseAddress,
	_In_  LPCVOID lpBuffer,
	_In_  SIZE_T  nSize,
	_Out_ SIZE_T  *lpNumberOfBytesWritten
	);
typedef BOOL (WINAPI *TERMINATEPROCESS)(HANDLE hProcess, UINT uExitCode);


typedef NTSTATUS (WINAPI *ZWUNMAPVIEWOFSECTION)(_In_ HANDLE ProcessHandle, _In_opt_ PVOID BaseAddress);
typedef void* (_cdecl *MEMSET)(void *dest, int c, size_t count);
typedef void* (_cdecl *MEMCPY)(void *dest, const void *src, size_t count);
typedef void* (_cdecl *MALLOC)(size_t size);
typedef void (_cdecl *FREE)(void *memblock);

void Decrypt()
{
	BOOL bResult = TRUE;
	HANDLE hProcess = NULL;
	TERMINATEPROCESS TerminateProcess = NULL;
	try
	{

		HINSTANCE hKernel32 = NULL;
		__asm
		{
			push eax
				mov eax, fs:[0x30]		// PEB
				mov eax, [eax + 0x0c]		// LDR
				mov eax, [eax + 0x0c]		// 本进程模块, LDA_DATA_TABLE_ENTRY 结构
				mov eax, [eax]			// ntdll 模块
				mov eax, [eax]			// kernel32 模块
				mov eax, [eax + 0x18]		// dllBase
				mov hKernel32, eax
				pop eax
		}

		char szGetProcAddress[] = { 'G', 'e', 't', 'P', 'r', 'o', 'c', 'A', 'd', 'd', 'r', 'e', 's', 's', '\0' };
		GETPROCADDRESS GetProcAddress = NULL;
		// 在 kernel32中寻找 GetProcAddress 函数
		IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)hKernel32;
		IMAGE_NT_HEADERS* pNtHeader = (IMAGE_NT_HEADERS*)((DWORD)hKernel32 + pDosHeader->e_lfanew);
		IMAGE_EXPORT_DIRECTORY* pExportDirectory = (IMAGE_EXPORT_DIRECTORY*)((DWORD)hKernel32 + pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
		short* functionOrdinals = (short*)((DWORD)hKernel32 + pExportDirectory->AddressOfNameOrdinals);
		int* adddressOfNames = (int*)((DWORD)hKernel32 + pExportDirectory->AddressOfNames);
		int* addressOfFunctions = (int*)((DWORD)hKernel32 + pExportDirectory->AddressOfFunctions);
		for (int i = 0; i < pExportDirectory->NumberOfNames; ++i)
		{
			// 第 i 个函数名地址
			char* name = (char*)((DWORD)hKernel32 + adddressOfNames[i]);
			char* left = name;
			char* right = szGetProcAddress;

			bool res = true;
			while (*left || *right)
			{
				if (*left != *right)
				{
					res = false;
					break;
				}
				++left;
				++right;
			}
			if (res)
			{
				GetProcAddress = (GETPROCADDRESS)((DWORD)hKernel32 + addressOfFunctions[functionOrdinals[i]]);
				break;
			}
		}

		pDosHeader = NULL;
		pNtHeader = NULL;

		char szLoadLibrary[] = { 'L', 'o', 'a', 'd', 'L', 'i', 'b', 'r', 'a', 'r', 'y', 'A', '\0' };
		char szGetModuleHandle[] = { 'G', 'e', 't', 'M', 'o', 'd', 'u', 'l', 'e', 'H', 'a', 'n', 'd', 'l', 'e', 'A', '\0' };
		char szCreateProcess[] = { 'C', 'r', 'e', 'a', 't', 'e', 'P', 'r', 'o', 'c', 'e', 's', 's', 'A', '\0' };
		char szGetModuleFileName[] = { 'G', 'e', 't', 'M', 'o', 'd', 'u', 'l', 'e', 'F', 'i', 'l', 'e', 'N', 'a', 'm', 'e', 'A', '\0' };
		char szGetThreadContext[] = { 'G', 'e', 't', 'T', 'h', 'r', 'e', 'a', 'd', 'C', 'o', 'n', 't', 'e', 'x', 't', '\0'};
		char szReadProcessMemory[] = { 'R', 'e', 'a', 'd', 'P', 'r', 'o', 'c', 'e', 's', 's', 'M', 'e', 'm', 'o', 'r', 'y', '\0' };
		char szZwUnmapViewOfSection[] = { 'Z', 'w', 'U', 'n', 'm', 'a', 'p', 'V', 'i', 'e', 'w', 'O', 'f', 'S', 'e', 'c', 't', 'i', 'o', 'n', '\0' };
		char szNtDll[] = { 'n', 't', 'd', 'l', 'l', '.', 'd', 'l', 'l', '\0' };
		char szMemcpy[] = { 'm', 'e', 'm', 'c', 'p', 'y', '\0' };
		char szMemset[] = { 'm', 'e', 'm', 's', 'e', 't', '\0' };
		char szMSVCRT[] = { 'm', 's', 'v', 'c', 'r', 't', '.', 'd', 'l', 'l', '\0' };
		char szMalloc[] = { 'm', 'a', 'l', 'l', 'o', 'c', '\0' };
		char szFree[] = { 'f', 'r', 'e', 'e', '\0' };
		char szVirtualAllocEx[] = { 'V', 'i', 'r', 't', 'u', 'a', 'l', 'A', 'l', 'l', 'o', 'c', 'E', 'x', '\0' };
		char szWriteProcessMemory[] = { 'W', 'r', 'i', 't', 'e', 'P', 'r', 'o', 'c', 'e', 's', 's', 'M', 'e', 'm', 'o', 'r', 'y', '\0' };
		char szSetThreadContext[] = { 'S', 'e', 't', 'T', 'h', 'r', 'e', 'a', 'd', 'C', 'o', 'n', 't', 'e', 'x', 't', '\0' };
		char szResumeThread[] = { 'R', 'e', 's', 'u', 'm', 'e', 'T', 'h', 'r', 'e', 'a', 'd', '\0' };
		char szTerminateProcess[] = { 'T', 'e', 'r', 'm', 'i', 'n', 'a', 't', 'e', 'P', 'r', 'o', 'c', 'e', 's', 's', '\0' };
		char szExitProcess[] = { 'E', 'x', 'i', 't', 'P', 'r', 'o', 'c', 'e', 's', 's', '\0' };

		LOADLIBRARY LoadLibraryA = (LOADLIBRARY)GetProcAddress(hKernel32, szLoadLibrary);
		GETMODULEHANDLE GetModuleHandleA = (GETMODULEHANDLE)GetProcAddress(hKernel32, szGetModuleHandle);
		CREATEPROCESS CreateProcessA = (CREATEPROCESS)GetProcAddress(hKernel32, szCreateProcess);
		GETMODULEFILENAME GetModuleFileNameA = (GETMODULEFILENAME)GetProcAddress(hKernel32, szGetModuleFileName);
		GETTHREADCONTEXT GetThreadContext = (GETTHREADCONTEXT)GetProcAddress(hKernel32, szGetThreadContext);
		READPROCESSMEMORY ReadProcessMemory = (READPROCESSMEMORY)GetProcAddress(hKernel32, szReadProcessMemory);
		WRITEPROCESSMEMORY WriteProcessMemory = (WRITEPROCESSMEMORY)GetProcAddress(hKernel32, szWriteProcessMemory);
		VIRTUALALLOCEX VirtualAllocEx = (VIRTUALALLOCEX)GetProcAddress(hKernel32, szVirtualAllocEx);
		SETTHREADCONTEXT SetThreadContext = (SETTHREADCONTEXT)GetProcAddress(hKernel32, szSetThreadContext);
		RESUMETHREAD ResumeThread = (RESUMETHREAD)GetProcAddress(hKernel32, szResumeThread);
		TerminateProcess = (TERMINATEPROCESS)GetProcAddress(hKernel32, szTerminateProcess);
		EXITPROCESS ExitProcess = (EXITPROCESS)GetProcAddress(hKernel32, szExitProcess);

		HMODULE hNtDll = GetModuleHandleA(szNtDll);
		ZWUNMAPVIEWOFSECTION ZwUnmapViewOfSection = (ZWUNMAPVIEWOFSECTION)GetProcAddress(hNtDll, szZwUnmapViewOfSection);
		MEMCPY memcpy = (MEMCPY)GetProcAddress(hNtDll, szMemcpy);
		MEMSET memset = (MEMSET)GetProcAddress(hNtDll, szMemset);

		HMODULE hMSVCRT = LoadLibraryA(szMSVCRT);
		MALLOC malloc = (MALLOC)GetProcAddress(hMSVCRT, szMalloc);
		FREE free = (FREE)GetProcAddress(hMSVCRT, szFree);


		HANDLE hModule = GetModuleHandleA(NULL);
		pDosHeader = (IMAGE_DOS_HEADER*)hModule;
		pNtHeader = (IMAGE_NT_HEADERS*)((DWORD)hModule + pDosHeader->e_lfanew);
		IMAGE_SECTION_HEADER* pSectionHeader = (IMAGE_SECTION_HEADER*)((DWORD)&pNtHeader->OptionalHeader + pNtHeader->FileHeader.SizeOfOptionalHeader);
		pSectionHeader = pSectionHeader + pNtHeader->FileHeader.NumberOfSections - 1;

		// 获取程序数据
		char* src = (char*)((DWORD)hModule + pSectionHeader->VirtualAddress + 0x2000);
		int srcSize = pSectionHeader->SizeOfRawData - 0x2000;

		// 拉伸
		pDosHeader = (IMAGE_DOS_HEADER*)src;
		pNtHeader = (IMAGE_NT_HEADERS*)((DWORD)src + pDosHeader->e_lfanew);
		IMAGE_OPTIONAL_HEADER32* pOptionalHeader = &pNtHeader->OptionalHeader;
		pSectionHeader = (IMAGE_SECTION_HEADER*)((DWORD)pOptionalHeader + pNtHeader->FileHeader.SizeOfOptionalHeader);
		int length = pSectionHeader[pNtHeader->FileHeader.NumberOfSections - 1].VirtualAddress + pSectionHeader[pNtHeader->FileHeader.NumberOfSections - 1].SizeOfRawData;

		//有时候会出现length比Image还要大
		length = length > pOptionalHeader->SizeOfImage ? length : pOptionalHeader->SizeOfImage;

		char* imageBuffer = (char*)malloc(length);
		memset(imageBuffer, 0, length);
		memcpy(imageBuffer, src, pOptionalHeader->SizeOfHeaders);
		for (int i = 0; i < pNtHeader->FileHeader.NumberOfSections; ++i)
		{
			memcpy(imageBuffer + pSectionHeader->VirtualAddress, src + pSectionHeader->PointerToRawData, pSectionHeader->SizeOfRawData);
			++pSectionHeader;
		}


		char szModuleName[MAX_PATH];
		GetModuleFileNameA(NULL, szModuleName, MAX_PATH);

		STARTUPINFO si;
		memset(&si, 0, sizeof(si));
		PROCESS_INFORMATION pi;
		memset(&pi, 0, sizeof(pi));
		si.cb = sizeof(si);
		CreateProcessA(NULL, szModuleName, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
		hProcess = pi.hProcess;
		CONTEXT context;
		context.ContextFlags = CONTEXT_FULL;
		GetThreadContext(pi.hThread, &context);
		DWORD dwEntryPoint = context.Eax;
		DWORD baseAddress = context.Ebx + 8;
		DWORD shellImageBase = 0;
		ReadProcessMemory(pi.hProcess, (LPVOID)baseAddress, &shellImageBase, 4, NULL);
		ZwUnmapViewOfSection(pi.hProcess, (PVOID)shellImageBase);
		LPVOID buffer = VirtualAllocEx(pi.hProcess, (LPVOID)pOptionalHeader->ImageBase, pOptionalHeader->SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (!buffer)
		{
			VirtualAllocEx(pi.hProcess, NULL, pOptionalHeader->SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			pDosHeader = (IMAGE_DOS_HEADER*)imageBuffer;
			pNtHeader = (IMAGE_NT_HEADERS*)((DWORD)imageBuffer + pDosHeader->e_lfanew);
			IMAGE_OPTIONAL_HEADER32* pOptionalHeader = &pNtHeader->OptionalHeader;
			IMAGE_BASE_RELOCATION* pBaseRelocation = (IMAGE_BASE_RELOCATION*)((DWORD)imageBuffer + pOptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);

			while (pBaseRelocation->SizeOfBlock || pBaseRelocation->VirtualAddress)
			{
				short* pTable = (short*)((int)pBaseRelocation + 8);
				int len = (pBaseRelocation->SizeOfBlock - 8) / 2;
				for (int i = 0; i < len; ++i)
				{
					DWORD RVA = pBaseRelocation->VirtualAddress + (pTable[i] & 0x0FFF);
					if (((pTable[i] & 0xF000) >> 12) == 3)
					{
						*(DWORD*)(RVA + (DWORD)imageBuffer) += ((DWORD)buffer - pOptionalHeader->ImageBase);
					}
				}
				pBaseRelocation = (IMAGE_BASE_RELOCATION*)((DWORD)pBaseRelocation + pBaseRelocation->SizeOfBlock);
			}
			pOptionalHeader->ImageBase = (DWORD)buffer;
		}
		WriteProcessMemory(pi.hProcess, buffer, imageBuffer, pOptionalHeader->SizeOfImage, NULL);
		WriteProcessMemory(pi.hProcess, (LPVOID)(context.Ebx + 8), &buffer, 4, NULL);
		context.Eax = pOptionalHeader->ImageBase + pOptionalHeader->AddressOfEntryPoint;
		SetThreadContext(pi.hThread, &context);
		ResumeThread(pi.hThread);
		free(imageBuffer);
		ExitProcess(0);
	}
	catch (...)
	{
		if (hProcess) TerminateProcess(hProcess, 0);
		return;
	}
}

