#ifndef WIFISERVER_H

#define WIFISERVER_H

#include <avr/pgmspace.h>
#include "wifiCore.h"
#include "../config/config.h"

#define wifiServerSendPGMP(str, stream) fputs_P(str, stream);

const PROGMEM char http200[] = "HTTP/1.1 200 OK\r\nConnection: close\r\n\r\n";
const PROGMEM char http200gzip[] = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent-Encoding: gzip\r\n\r\n";
const PROGMEM char http200json[] = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n"
                                   "Connection: close\r\n\r\n";
const PROGMEM char http404[] = "HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\nHTTP 404 Not Found";
const PROGMEM char http400[] = "HTTP/1.1 400 Bad Request\r\nConnection: close\r\n\r\nHTTP 400 Bad Request";
const PROGMEM char success[] = "{\"result\":\"success\"}";
const PROGMEM unsigned char index[] = {
  0x1f, 0x8b, 0x08, 0x08, 0x94, 0x63, 0x90, 0x57, 0x02, 0x03, 0x69, 0x6e,
  0x64, 0x65, 0x78, 0x33, 0x2e, 0x68, 0x74, 0x6d, 0x6c, 0x00, 0xd5, 0x5a,
  0x7b, 0x6f, 0xdb, 0x38, 0x12, 0xff, 0x2a, 0xaa, 0x8b, 0x2d, 0xe2, 0xab,
  0xe4, 0x48, 0x7e, 0x25, 0x91, 0x2c, 0xef, 0x2b, 0xc1, 0x35, 0xb8, 0x5d,
  0x6c, 0x70, 0xe9, 0x01, 0x77, 0xd8, 0xee, 0x1f, 0xb4, 0x44, 0xdb, 0x6c,
  0xf4, 0x3a, 0x89, 0x8a, 0xe3, 0x1a, 0xfe, 0xee, 0x37, 0x7c, 0x48, 0xa2,
  0x1e, 0x76, 0xdc, 0x6c, 0x16, 0xe8, 0xb5, 0x88, 0x23, 0xcd, 0x0c, 0x67,
  0x7e, 0x9c, 0x19, 0xce, 0x90, 0x74, 0x66, 0x6f, 0xae, 0x7f, 0xfb, 0xf9,
  0xe3, 0x7f, 0xee, 0x6e, 0xb4, 0x35, 0x0d, 0x83, 0xf9, 0x2c, 0xc4, 0x14,
  0x69, 0x5e, 0x1c, 0x51, 0x1c, 0x51, 0xb7, 0x47, 0x22, 0x42, 0x09, 0x0a,
  0x8c, 0xcc, 0x43, 0x01, 0x76, 0x2d, 0x3d, 0xcf, 0x70, 0xca, 0x5f, 0xd0,
  0x02, 0xde, 0xa3, 0xb8, 0x17, 0xa1, 0x10, 0xbb, 0x8f, 0x04, 0x6f, 0x92,
  0x38, 0xa5, 0xf3, 0x19, 0x25, 0x34, 0xc0, 0xf3, 0x6b, 0xfc, 0x48, 0x3c,
  0xcc, 0xb4, 0x2c, 0xc9, 0x2a, 0x4f, 0x11, 0x25, 0x71, 0x34, 0x3b, 0x17,
  0xbc, 0x59, 0x46, 0xb7, 0xf0, 0x8b, 0x19, 0xdb, 0x2d, 0xc1, 0x8c, 0xb1,
  0x44, 0x21, 0x09, 0xb6, 0x76, 0x86, 0xa2, 0xcc, 0x00, 0xed, 0x64, 0xe9,
  0x18, 0x61, 0x66, 0x50, 0xfc, 0x44, 0x8d, 0x8c, 0x7c, 0xc1, 0x06, 0xf2,
  0x3f, 0xe7, 0x19, 0xb5, 0x2d, 0xd3, 0xfc, 0xce, 0x31, 0x36, 0x78, 0xf1,
  0x40, 0x68, 0x37, 0x77, 0xbf, 0x88, 0xfd, 0xed, 0x2e, 0x44, 0xe9, 0x8a,
  0x44, 0xb6, 0xb9, 0x5f, 0x08, 0xf5, 0x1b, 0x4c, 0x56, 0x6b, 0x6a, 0x5f,
  0x98, 0xe6, 0x7e, 0x6d, 0x09, 0x12, 0x1b, 0x68, 0x0f, 0x71, 0xe8, 0x48,
  0xd9, 0xc1, 0xf4, 0x02, 0x87, 0x1a, 0x8c, 0xc8, 0x29, 0x8d, 0x23, 0x9d,
  0x44, 0x49, 0x4e, 0x77, 0x5e, 0x1c, 0xc4, 0xa9, 0x4d, 0xa2, 0x35, 0x40,
  0xa2, 0x0e, 0x1b, 0x57, 0xbe, 0x54, 0x26, 0xf8, 0x80, 0x5d, 0xfc, 0x88,
  0xd3, 0x65, 0x10, 0x6f, 0xec, 0x47, 0x92, 0x11, 0xf0, 0x4b, 0x41, 0xe7,
  0x28, 0x69, 0x0a, 0x13, 0x5b, 0xc6, 0x69, 0x68, 0x47, 0x71, 0x54, 0xb2,
  0x8a, 0x89, 0xa0, 0x24, 0xc1, 0x08, 0x24, 0x3c, 0x6c, 0x0b, 0x8e, 0xe3,
  0xe5, 0x69, 0x06, 0x86, 0x93, 0x98, 0x40, 0x08, 0x52, 0x29, 0xff, 0xbb,
  0x4f, 0x32, 0xe6, 0x71, 0xff, 0x8f, 0x9d, 0xe4, 0xfb, 0x78, 0x89, 0xf2,
  0x80, 0x4a, 0xbe, 0x6d, 0x1b, 0x61, 0xfc, 0xc5, 0x58, 0xc6, 0x5e, 0x9e,
  0x19, 0x24, 0x8a, 0x70, 0x2a, 0x66, 0xd1, 0xa6, 0xef, 0x16, 0x71, 0xea,
  0xe3, 0xd4, 0x36, 0x9d, 0x04, 0xf9, 0x3e, 0x89, 0x56, 0x30, 0x0d, 0x31,
  0xe1, 0x80, 0x44, 0xd8, 0x58, 0x0b, 0x6f, 0x45, 0x80, 0x17, 0x05, 0x82,
  0xf1, 0x3b, 0xdd, 0x26, 0xd8, 0xf5, 0xd6, 0xd8, 0x7b, 0x58, 0xc4, 0x4f,
  0x7f, 0x94, 0xd0, 0xe1, 0x85, 0x79, 0x92, 0xa9, 0x10, 0x3a, 0x19, 0xc5,
  0xe1, 0xf6, 0xba, 0x59, 0xdd, 0xd4, 0x0a, 0xc6, 0xdf, 0x5e, 0x59, 0xf5,
  0xde, 0x46, 0x4b, 0x70, 0xa1, 0x6e, 0x2f, 0x30, 0xf8, 0x1f, 0xbf, 0xb6,
  0xf6, 0x2a, 0x83, 0x79, 0x3e, 0x59, 0x66, 0xf2, 0x54, 0xe5, 0x27, 0x4a,
  0x8c, 0x35, 0x78, 0x32, 0x60, 0xde, 0x34, 0x44, 0x2a, 0xf1, 0x44, 0x48,
  0x50, 0x0a, 0xeb, 0x4a, 0x64, 0xaa, 0x9a, 0xfd, 0x1f, 0x70, 0xf0, 0x88,
  0x29, 0xf1, 0x90, 0xfe, 0x63, 0x0a, 0xeb, 0x4d, 0x57, 0x56, 0x83, 0x62,
  0x62, 0x02, 0x26, 0xd4, 0x30, 0x59, 0x83, 0xf1, 0xf0, 0x72, 0x72, 0x61,
  0x8d, 0x47, 0x8e, 0xb0, 0xf1, 0x76, 0xe8, 0x8d, 0xf0, 0xc4, 0x74, 0x16,
  0xc8, 0x7b, 0x58, 0xa5, 0x71, 0x1e, 0xf9, 0xd2, 0xf8, 0xdb, 0xe5, 0x72,
  0x59, 0xcf, 0x6f, 0xd5, 0xba, 0x9a, 0xe5, 0xc2, 0x54, 0x41, 0x51, 0xad,
  0x49, 0x5a, 0xb9, 0x8c, 0x4e, 0x84, 0x2e, 0x17, 0xe0, 0xd8, 0x34, 0x1b,
  0xd8, 0x2d, 0xa7, 0xb6, 0xc6, 0x98, 0x5e, 0xb1, 0xb2, 0x0c, 0x1a, 0x27,
  0xf6, 0xd0, 0x82, 0xc9, 0xca, 0xf7, 0x45, 0x0c, 0xc0, 0x43, 0x70, 0xf1,
  0x00, 0x3c, 0x50, 0x5f, 0xc6, 0xa3, 0x2b, 0xa0, 0x0c, 0x58, 0xbd, 0x42,
  0xa0, 0x3c, 0x35, 0x96, 0x41, 0x4e, 0xfc, 0x42, 0x4f, 0xca, 0x2d, 0xa1,
  0x9c, 0xc6, 0x85, 0xa6, 0x00, 0x2f, 0x25, 0x41, 0xe6, 0x9d, 0xa0, 0x70,
  0xcf, 0x16, 0x14, 0x31, 0x8a, 0x91, 0x98, 0x62, 0xa8, 0x7d, 0xa1, 0x61,
  0xe9, 0xe5, 0x93, 0x59, 0x3e, 0x0e, 0xcb, 0xa7, 0x51, 0xf9, 0x34, 0x2d,
  0x9f, 0xae, 0x76, 0x49, 0x9c, 0x11, 0x56, 0xf9, 0xec, 0x14, 0x07, 0x50,
  0x02, 0x1f, 0xb1, 0x13, 0x02, 0x82, 0x62, 0xfa, 0x8a, 0xc1, 0xa3, 0x10,
  0x7e, 0x08, 0xb1, 0x4f, 0x90, 0x76, 0xc6, 0xc6, 0x6e, 0x88, 0x4f, 0xd7,
  0xf6, 0xc5, 0xf4, 0x32, 0x79, 0xea, 0xef, 0xfe, 0x14, 0x36, 0x28, 0x57,
  0x88, 0xda, 0xcc, 0x70, 0x35, 0x47, 0x73, 0x27, 0xf4, 0x5f, 0x8e, 0x06,
  0x23, 0xf9, 0xef, 0xbb, 0x7d, 0x35, 0x44, 0x1a, 0x9f, 0x54, 0xb4, 0xa9,
  0xa4, 0x4d, 0xcc, 0x8a, 0x36, 0x92, 0xb4, 0xa1, 0x22, 0x37, 0x94, 0x34,
  0x6b, 0x3a, 0x98, 0x8a, 0x7f, 0x17, 0x15, 0xd3, 0x2a, 0xac, 0x76, 0x18,
  0x8d, 0x97, 0xcb, 0x0c, 0x53, 0xd0, 0xa9, 0x46, 0x8f, 0x69, 0xde, 0x43,
  0xff, 0xc1, 0xc1, 0x0e, 0xaa, 0x62, 0x12, 0x20, 0x96, 0xbf, 0x3c, 0xb3,
  0x16, 0x41, 0xec, 0x3d, 0x40, 0xa4, 0x9f, 0xa4, 0xa3, 0x78, 0xcb, 0xa8,
  0xa7, 0x10, 0x73, 0x72, 0xb3, 0x2d, 0x74, 0x56, 0x39, 0x59, 0xe3, 0xc7,
  0xc9, 0x93, 0x66, 0x6a, 0xa6, 0xa3, 0x24, 0x26, 0x44, 0xee, 0xd3, 0x95,
  0x73, 0x62, 0xb5, 0xb4, 0x79, 0xe9, 0xdd, 0xc5, 0x39, 0x65, 0x03, 0x6c,
  0xba, 0x26, 0x91, 0xe6, 0x03, 0x14, 0xec, 0x3b, 0x05, 0x0d, 0x20, 0x69,
  0x2c, 0x23, 0xb5, 0xa2, 0x78, 0x88, 0x6a, 0x9d, 0xb2, 0x3c, 0xe0, 0x0b,
  0xa4, 0x90, 0x94, 0xee, 0xb0, 0x8d, 0x21, 0xcb, 0x4c, 0xd6, 0x52, 0x0c,
  0x96, 0xf7, 0x69, 0x5c, 0x39, 0x42, 0x78, 0x40, 0x99, 0xbd, 0x44, 0x38,
  0x56, 0x92, 0x8b, 0x57, 0x2a, 0xcd, 0x2a, 0x3d, 0xf1, 0x1a, 0xa5, 0x45,
  0xa5, 0x92, 0x10, 0xad, 0x30, 0x6f, 0x76, 0x8e, 0xec, 0x35, 0xe0, 0x31,
  0x2d, 0x8b, 0x03, 0xe2, 0x6b, 0x6f, 0x7d, 0x0f, 0x8f, 0xb1, 0x27, 0x19,
  0x46, 0x8a, 0x7c, 0x92, 0x67, 0xcc, 0xc9, 0x4e, 0xad, 0x38, 0xaf, 0x91,
  0x0f, 0xdd, 0x94, 0x44, 0x30, 0x5b, 0xf0, 0x3e, 0x1b, 0xce, 0x7e, 0xd2,
  0xd5, 0x02, 0x9d, 0x99, 0x3a, 0xfb, 0x3f, 0x30, 0x2f, 0x26, 0x7d, 0xe7,
  0x6b, 0x64, 0xcb, 0xca, 0xcc, 0xaa, 0xb0, 0x58, 0x96, 0x12, 0x04, 0x9f,
  0x85, 0x86, 0x51, 0x86, 0xa1, 0x43, 0x1a, 0xe0, 0x6b, 0x6d, 0x60, 0x4d,
  0x32, 0xbd, 0x0d, 0xa8, 0x25, 0xe3, 0x18, 0xf1, 0xe9, 0xfa, 0x8e, 0xe9,
  0x79, 0x0d, 0x25, 0xf5, 0x8c, 0x90, 0x79, 0xa7, 0x6a, 0x2b, 0x23, 0x58,
  0x24, 0x9e, 0xf9, 0x12, 0xa7, 0xeb, 0xb0, 0x1a, 0xb4, 0xcb, 0x82, 0x31,
  0x1e, 0xeb, 0xd3, 0xa1, 0x7e, 0x09, 0xbc, 0xe9, 0x57, 0x85, 0xe3, 0xb0,
  0x96, 0xc6, 0x34, 0xc4, 0xfe, 0x05, 0x72, 0xdb, 0xc3, 0xeb, 0x38, 0x80,
  0xb9, 0xc8, 0x7d, 0xd9, 0x5b, 0xe4, 0x2d, 0xa6, 0x1e, 0xcc, 0x25, 0x41,
  0x1e, 0xa1, 0x5b, 0xdb, 0x6a, 0x8c, 0x63, 0x5b, 0x48, 0xbe, 0x1e, 0x0f,
  0x8f, 0x6d, 0x5b, 0xca, 0x0c, 0xfc, 0x94, 0xa0, 0xc8, 0xaf, 0xf6, 0x48,
  0xad, 0x64, 0x57, 0x9b, 0xb8, 0x18, 0xcf, 0xd8, 0xc9, 0xae, 0xd1, 0xa8,
  0x44, 0xef, 0x90, 0x45, 0xa0, 0xa3, 0x11, 0xd4, 0xd7, 0xab, 0x5a, 0x5c,
  0xcc, 0x8e, 0xae, 0xa7, 0x2a, 0xd3, 0x44, 0xe5, 0x53, 0x3a, 0xc9, 0xb0,
  0xd5, 0x4a, 0x86, 0x6d, 0x25, 0x66, 0xab, 0x17, 0x37, 0xf6, 0x99, 0x95,
  0x81, 0xce, 0x72, 0x58, 0x4e, 0x01, 0x2d, 0x60, 0x25, 0xe7, 0x14, 0xd7,
  0x1a, 0xaa, 0xa1, 0x5a, 0x64, 0xd3, 0x18, 0xb3, 0x1a, 0x29, 0x1d, 0xb4,
  0x8e, 0x53, 0xf2, 0x85, 0xf5, 0xe7, 0x40, 0xab, 0x5c, 0xa2, 0xc8, 0x9a,
  0x2d, 0xa8, 0xc5, 0x64, 0xb8, 0x43, 0xac, 0xb2, 0xd8, 0x75, 0x2b, 0xaa,
  0x1c, 0x31, 0x1a, 0x76, 0x8a, 0xb6, 0xa3, 0x24, 0x30, 0xf3, 0x92, 0x57,
  0xdb, 0x28, 0x18, 0xcf, 0x34, 0xdc, 0x36, 0x0a, 0x91, 0x3b, 0x86, 0x88,
  0x09, 0xdf, 0xee, 0x23, 0xd8, 0xf2, 0x41, 0xa0, 0x99, 0xbe, 0xe7, 0xe7,
  0xb5, 0x1f, 0x2c, 0x68, 0x74, 0xa8, 0x8b, 0x1d, 0x0f, 0x9f, 0x62, 0xcc,
  0xc3, 0x2c, 0x82, 0x0e, 0x1c, 0x42, 0xd8, 0x2e, 0x2c, 0x90, 0xd4, 0x90,
  0xf8, 0x7e, 0x80, 0xc5, 0x59, 0x2a, 0xce, 0xbd, 0xb5, 0x81, 0x3c, 0x1e,
  0xc0, 0x10, 0x45, 0x24, 0xc9, 0x03, 0x7e, 0x26, 0x73, 0x0e, 0x73, 0xea,
  0xe9, 0x71, 0x6a, 0x7d, 0x57, 0x96, 0x87, 0xb3, 0x59, 0x13, 0x8a, 0x0d,
  0x78, 0xf3, 0x98, 0xf4, 0x26, 0x45, 0xc9, 0x8b, 0x3b, 0xd0, 0xe1, 0x76,
  0x21, 0xce, 0xa3, 0x38, 0xc0, 0x1e, 0x15, 0x90, 0x78, 0xbd, 0xe8, 0xa0,
  0x66, 0x6d, 0x62, 0x93, 0xc0, 0xa3, 0x61, 0x33, 0x67, 0x3c, 0x62, 0x51,
  0x3f, 0x75, 0x4e, 0xf9, 0xcb, 0x5a, 0x78, 0xa9, 0x5c, 0xd8, 0x59, 0xb3,
  0x73, 0xe4, 0x4e, 0x69, 0xaa, 0x3c, 0xc6, 0x3e, 0xf6, 0x62, 0x71, 0x82,
  0x6e, 0x81, 0xdc, 0x55, 0x95, 0xbc, 0x3b, 0x3e, 0x47, 0xea, 0xfb, 0x08,
  0x20, 0x4f, 0x1a, 0x95, 0xd9, 0x1a, 0x76, 0x37, 0xd5, 0x43, 0xb2, 0x1c,
  0x4b, 0xfb, 0x68, 0x1a, 0xc5, 0x2c, 0x33, 0xe1, 0x3c, 0xcc, 0x3c, 0x24,
  0xeb, 0xf3, 0x60, 0x3a, 0x71, 0x96, 0x24, 0x80, 0x54, 0xb2, 0x51, 0x90,
  0xac, 0xd1, 0x99, 0x64, 0xb8, 0x53, 0xa5, 0x37, 0x2b, 0xa6, 0x65, 0x7a,
  0xd5, 0xde, 0xb9, 0x39, 0x23, 0x49, 0x61, 0x82, 0xe9, 0x76, 0xd7, 0xbd,
  0xf9, 0x68, 0xec, 0x55, 0x3a, 0xda, 0x5f, 0x4d, 0x8b, 0x8c, 0xed, 0x51,
  0x5d, 0x16, 0x1a, 0x8e, 0x87, 0xcb, 0x86, 0x2e, 0xd3, 0x6c, 0x28, 0x6a,
  0x05, 0xef, 0x44, 0x45, 0xd6, 0xd4, 0x5a, 0x0e, 0xaf, 0xea, 0xba, 0x64,
  0x74, 0x5f, 0x53, 0x99, 0x92, 0x67, 0x4d, 0xce, 0x09, 0xc8, 0x4d, 0xdf,
  0x1a, 0x59, 0x97, 0xcf, 0xb9, 0x40, 0xc2, 0xee, 0x4c, 0xc5, 0x9a, 0x64,
  0x95, 0x32, 0x1d, 0xb0, 0x14, 0xa6, 0x40, 0xf6, 0x82, 0xe8, 0xf2, 0x12,
  0x7a, 0x70, 0x53, 0xbc, 0x1f, 0x6c, 0x70, 0x50, 0x6f, 0xa1, 0xa6, 0xba,
  0x3d, 0xbe, 0x6a, 0x75, 0x4f, 0xce, 0x6f, 0xe3, 0xc0, 0xde, 0xd2, 0x5c,
  0x5a, 0xc7, 0xab, 0xe0, 0x9f, 0xdf, 0xe9, 0x7e, 0xc5, 0x46, 0x97, 0x2d,
  0xc9, 0xc6, 0x51, 0x58, 0xde, 0x81, 0xb4, 0xc8, 0xe2, 0x4e, 0x44, 0x3f,
  0xd6, 0x2e, 0x8b, 0xa1, 0xc7, 0x44, 0xe4, 0xd5, 0x8a, 0xbc, 0x2f, 0xb4,
  0x7b, 0x5a, 0xaf, 0xdc, 0xdb, 0x50, 0x16, 0xc5, 0x83, 0x78, 0x9e, 0xb5,
  0xbb, 0xf3, 0x02, 0x8c, 0x52, 0xd8, 0x0f, 0xd3, 0xf5, 0xfe, 0x07, 0x56,
  0xbf, 0x8b, 0x4b, 0x46, 0x79, 0x5e, 0xf4, 0xf9, 0x1d, 0xa3, 0xe8, 0xd0,
  0xa2, 0x8f, 0x4a, 0x57, 0xcb, 0xf3, 0x67, 0x51, 0x60, 0x65, 0x56, 0x9e,
  0x5c, 0x63, 0xd4, 0x4d, 0xa1, 0xbc, 0x2a, 0x69, 0x2a, 0x76, 0x5e, 0xa4,
  0x4c, 0xe6, 0xba, 0xb8, 0x97, 0x13, 0x75, 0xe7, 0x64, 0x3d, 0x3c, 0x61,
  0x4f, 0x95, 0xe6, 0x97, 0x4b, 0x55, 0xb6, 0xda, 0xc5, 0x38, 0xd6, 0x2a,
  0x50, 0x0a, 0x3e, 0x86, 0x5c, 0x84, 0x60, 0x9d, 0x59, 0xa3, 0x89, 0x8f,
  0x57, 0xba, 0x92, 0x41, 0x66, 0x5f, 0x83, 0xd3, 0xb5, 0xa0, 0x0c, 0x27,
  0x13, 0xbd, 0xf8, 0x19, 0x0c, 0x8f, 0x30, 0xe0, 0xf4, 0xdf, 0xd0, 0xd1,
  0xa6, 0x5c, 0x1c, 0x1a, 0x0c, 0x8c, 0xbe, 0x7e, 0x08, 0xe0, 0xf8, 0x1b,
  0xc1, 0x07, 0xa5, 0xee, 0xea, 0xea, 0xea, 0xc2, 0x51, 0x7d, 0xca, 0xb6,
  0x19, 0x4d, 0xbc, 0xc6, 0xb7, 0x02, 0xb8, 0x13, 0xdd, 0x37, 0xec, 0xcd,
  0x6f, 0xd6, 0x91, 0xff, 0x3f, 0x3e, 0x34, 0xaa, 0x13, 0x1a, 0xdb, 0x88,
  0xf2, 0x2b, 0xce, 0xb2, 0x60, 0x54, 0x52, 0x50, 0x70, 0xd9, 0xb5, 0x56,
  0x71, 0x12, 0xe1, 0xb7, 0xdb, 0x47, 0xb9, 0x1d, 0x3a, 0xbc, 0x80, 0x24,
  0xb5, 0xeb, 0xf1, 0xc3, 0xac, 0x8e, 0xd1, 0xf2, 0xb2, 0xdc, 0xc4, 0xa1,
  0xc6, 0x3f, 0x9d, 0x0e, 0x1e, 0xeb, 0x6d, 0x26, 0x3f, 0xf6, 0xf2, 0xc2,
  0xd7, 0xee, 0xbc, 0x37, 0x37, 0x37, 0x6a, 0xd9, 0x63, 0xb7, 0x09, 0x23,
  0x36, 0x6a, 0x95, 0xe2, 0xad, 0xec, 0xf4, 0x57, 0xe6, 0xe3, 0x46, 0xb9,
  0x0b, 0xbc, 0x34, 0xab, 0x23, 0x2a, 0xef, 0xe7, 0xdc, 0x45, 0xfb, 0xd9,
  0xb9, 0xf8, 0x3a, 0x6a, 0xe6, 0x93, 0x47, 0xcd, 0x0b, 0x50, 0x96, 0xb9,
  0x8d, 0x86, 0xa5, 0xb2, 0x18, 0x9a, 0xf9, 0x6c, 0x6d, 0x1d, 0xf8, 0x82,
  0x0b, 0x18, 0xb3, 0x45, 0x3a, 0x9f, 0xb1, 0xaa, 0x2f, 0x47, 0x34, 0xdb,
  0x5c, 0x1c, 0x65, 0xf9, 0x22, 0x24, 0xd4, 0x4d, 0x31, 0xcd, 0xd3, 0xe8,
  0x8d, 0xa5, 0x41, 0x67, 0xc0, 0x5c, 0x4c, 0x35, 0x54, 0x35, 0x43, 0x95,
  0xda, 0x2b, 0x6f, 0x6a, 0xb5, 0xc6, 0x05, 0x69, 0xaf, 0x36, 0x01, 0x79,
  0x36, 0x9e, 0xcf, 0xf8, 0xb9, 0x74, 0x3e, 0xe3, 0x2d, 0x47, 0x23, 0xbe,
  0x9b, 0x51, 0x40, 0xea, 0x69, 0xb5, 0xb3, 0x3d, 0x40, 0x9e, 0xff, 0x2b,
  0xc3, 0x9a, 0xe4, 0xdd, 0xde, 0xcd, 0xce, 0x17, 0xf3, 0xd9, 0xb9, 0x1c,
  0x7a, 0x0e, 0x6a, 0xeb, 0x9f, 0xcc, 0x4e, 0xa9, 0xca, 0x20, 0xc9, 0x21,
  0xd8, 0x5c, 0x41, 0x05, 0x5c, 0x39, 0x28, 0x17, 0xe0, 0x47, 0x3d, 0x90,
  0x77, 0x41, 0xc3, 0xed, 0x9d, 0x06, 0x19, 0x97, 0xe2, 0x2c, 0x2b, 0xed,
  0xaa, 0xe1, 0x10, 0xf7, 0xcf, 0xca, 0x34, 0x48, 0xa2, 0xda, 0x93, 0xba,
  0x35, 0xe5, 0xa2, 0xc7, 0xb5, 0xae, 0x86, 0x03, 0x6b, 0x7a, 0x39, 0xb0,
  0x06, 0x56, 0x1b, 0xfd, 0xcb, 0xb1, 0x42, 0xec, 0x22, 0x4c, 0xe7, 0xf7,
  0xfc, 0x97, 0x16, 0xa2, 0xec, 0xe1, 0x34, 0xc0, 0x62, 0xdc, 0x73, 0xa0,
  0x61, 0x85, 0x0f, 0x8a, 0x1f, 0xf3, 0x35, 0x61, 0xaf, 0x10, 0xc5, 0x1b,
  0xb4, 0x85, 0xac, 0xe5, 0xdf, 0x19, 0x6a, 0xf2, 0xfd, 0x34, 0xec, 0x52,
  0xf8, 0xc5, 0x1e, 0x7f, 0x15, 0xbf, 0x67, 0xb0, 0x0e, 0xef, 0xef, 0x6f,
  0xaf, 0x4f, 0x74, 0x37, 0x88, 0x77, 0xe0, 0x7d, 0x6d, 0x44, 0x09, 0x08,
  0x6d, 0xa0, 0xd6, 0x71, 0x64, 0x5a, 0xf1, 0x76, 0x1a, 0xc4, 0x42, 0xba,
  0xcb, 0xad, 0x7c, 0x79, 0x96, 0xca, 0x5f, 0x11, 0xf4, 0x3a, 0xce, 0xe8,
  0xfc, 0x03, 0x7c, 0x1c, 0xc6, 0x38, 0x55, 0x30, 0x32, 0xf1, 0x23, 0x6e,
  0x7c, 0xde, 0xaa, 0xc5, 0xad, 0xf2, 0x3f, 0x0c, 0xb8, 0x83, 0x8f, 0xc3,
  0x56, 0x87, 0xaa, 0x67, 0x40, 0xf2, 0xa0, 0x57, 0xa2, 0x3c, 0x5c, 0xe0,
  0x54, 0x7b, 0x44, 0x41, 0x8e, 0xdd, 0xcb, 0x57, 0x5d, 0x24, 0xd0, 0xba,
  0xa0, 0xc3, 0x43, 0x9e, 0xfd, 0xcc, 0x1f, 0xb4, 0x53, 0x93, 0xad, 0x18,
  0xf7, 0x17, 0x27, 0x1c, 0x4a, 0xc8, 0x03, 0xde, 0xce, 0x7f, 0xbc, 0xbb,
  0xd5, 0xe0, 0xf7, 0x69, 0xd0, 0xc4, 0x98, 0x67, 0x81, 0x89, 0xaf, 0x85,
  0x0b, 0x0c, 0x70, 0x66, 0xd2, 0xca, 0x33, 0x34, 0x7f, 0x0a, 0xa0, 0x69,
  0x62, 0x4d, 0x39, 0xa2, 0xf7, 0xd8, 0x1a, 0x43, 0x8f, 0x58, 0xc4, 0x44,
  0x0c, 0x9f, 0xdf, 0x33, 0x02, 0x34, 0x23, 0x0a, 0x3b, 0x07, 0xa8, 0xe3,
  0x92, 0x3a, 0x3b, 0x17, 0xad, 0x4d, 0xb5, 0x97, 0x79, 0x29, 0x49, 0xe8,
  0x7c, 0x99, 0x47, 0xfc, 0xde, 0x51, 0x5b, 0x61, 0xe2, 0x9f, 0xa1, 0xfe,
  0x4e, 0xb4, 0x44, 0xcd, 0x87, 0xa3, 0x51, 0x08, 0x2e, 0x1d, 0xac, 0x30,
  0xbd, 0x09, 0x30, 0x7b, 0xfc, 0x69, 0x7b, 0xcb, 0x24, 0xf6, 0xe5, 0x10,
  0x6f, 0x8d, 0xa2, 0x15, 0xbe, 0xbd, 0xbb, 0x65, 0x53, 0xbd, 0x87, 0x56,
  0x84, 0x99, 0x02, 0xf4, 0x3d, 0x57, 0xd5, 0x2b, 0x7b, 0x53, 0xaf, 0x3f,
  0xe0, 0xed, 0x7d, 0x20, 0xcf, 0xa4, 0xe5, 0xdf, 0xb3, 0xf4, 0xec, 0x67,
  0x25, 0xd9, 0x51, 0xaa, 0x57, 0x59, 0x0c, 0x62, 0xe4, 0x5f, 0x23, 0x8a,
  0xce, 0xc0, 0xcc, 0x67, 0xf4, 0xe4, 0x46, 0x78, 0xa3, 0xfd, 0xfb, 0xd7,
  0x5f, 0x3e, 0x50, 0x9a, 0xfc, 0x13, 0xff, 0x37, 0xc7, 0x19, 0xd5, 0x19,
  0x7d, 0x00, 0x5d, 0x2c, 0x81, 0x26, 0x8f, 0x3f, 0x32, 0xd7, 0xf4, 0x3e,
  0x67, 0x71, 0xd4, 0x13, 0x8c, 0x38, 0xc1, 0xd1, 0x59, 0xef, 0xef, 0x37,
  0x1f, 0x7b, 0x7a, 0xef, 0xdc, 0xcb, 0xd3, 0xf4, 0x5e, 0xf8, 0xaa, 0xd7,
  0x97, 0xfc, 0x28, 0xc5, 0xc8, 0xdf, 0x32, 0x44, 0x58, 0x4c, 0xcf, 0x2d,
  0x8c, 0x83, 0xcd, 0xb1, 0xeb, 0x4a, 0xf5, 0x20, 0xc3, 0x27, 0xfc, 0xee,
  0xdd, 0xd0, 0x34, 0x25, 0x95, 0x0d, 0xca, 0xb3, 0x77, 0xef, 0xce, 0x7c,
  0x40, 0xe8, 0xd6, 0x70, 0xe8, 0x62, 0xa2, 0x7c, 0x86, 0x62, 0xd9, 0x30,
  0x99, 0x01, 0x49, 0x24, 0x43, 0xb4, 0xa6, 0x3a, 0x53, 0xd0, 0xa4, 0x80,
  0xac, 0xff, 0x75, 0x09, 0x49, 0x2c, 0x74, 0x40, 0x31, 0x6c, 0x68, 0x00,
  0x8a, 0x64, 0x16, 0x85, 0xac, 0x2e, 0x50, 0x50, 0xa5, 0x10, 0x2b, 0x35,
  0x75, 0x01, 0x46, 0x29, 0x34, 0x40, 0x45, 0x68, 0x8c, 0x06, 0x8a, 0x64,
  0x16, 0xcb, 0xaf, 0x2e, 0x20, 0xa8, 0xb7, 0xd7, 0x52, 0x48, 0x2c, 0x84,
  0xba, 0x08, 0xd0, 0xfe, 0x81, 0xb7, 0xba, 0xe5, 0x4a, 0xc4, 0x3c, 0x13,
  0x6a, 0x09, 0x04, 0xf2, 0x7c, 0x93, 0x84, 0x7d, 0xf7, 0x8d, 0x69, 0x1f,
  0xe2, 0x58, 0x7a, 0x47, 0x32, 0x76, 0x0b, 0xf7, 0xfb, 0x7b, 0x11, 0xeb,
  0x0c, 0x47, 0xfe, 0x59, 0x7f, 0xdf, 0x90, 0x8a, 0x23, 0x80, 0xed, 0x3d,
  0xa8, 0x61, 0x3f, 0x5d, 0xf5, 0xbe, 0x88, 0x05, 0x2c, 0xc3, 0x6e, 0x5d,
  0x35, 0x7e, 0x71, 0xc9, 0x06, 0x33, 0xd3, 0x49, 0xe2, 0x36, 0x93, 0x44,
  0x17, 0x29, 0xe0, 0x76, 0xe5, 0x88, 0x2e, 0x83, 0xef, 0x76, 0xe6, 0x87,
  0xce, 0x42, 0xcf, 0xff, 0x28, 0xac, 0x9d, 0x1b, 0x9c, 0x77, 0x27, 0x23,
  0xef, 0x76, 0xa7, 0x87, 0xce, 0x02, 0xef, 0xb6, 0xb3, 0x42, 0x67, 0x31,
  0x77, 0xdb, 0x09, 0xa1, 0x17, 0x09, 0xe0, 0x76, 0xe7, 0x83, 0x2e, 0x62,
  0xef, 0x76, 0x25, 0x82, 0xde, 0xed, 0xcb, 0xef, 0x05, 0xc1, 0xb5, 0x6c,
  0xf9, 0x60, 0xea, 0x7c, 0x5d, 0xf5, 0x3e, 0x45, 0x0b, 0x0c, 0xc7, 0x87,
  0x4f, 0x11, 0x71, 0x7b, 0xef, 0x49, 0xf2, 0x1e, 0x08, 0x50, 0x30, 0xdf,
  0x0b, 0xf7, 0xb0, 0xb7, 0x15, 0xbc, 0x49, 0x7f, 0xb0, 0x57, 0x9f, 0x31,
  0xa5, 0x3b, 0xd8, 0x7b, 0x22, 0xdf, 0x0b, 0x17, 0x30, 0xda, 0x1a, 0x68,
  0x6c, 0x9e, 0xec, 0x39, 0x86, 0x67, 0x36, 0x37, 0xf6, 0xec, 0xc1, 0x73,
  0x31, 0x17, 0xf6, 0x0e, 0xe6, 0xdf, 0x0b, 0xf4, 0xec, 0xed, 0x89, 0x69,
  0xe2, 0xe0, 0xd8, 0x1b, 0x64, 0xd3, 0x27, 0x28, 0x33, 0x50, 0xdc, 0x33,
  0x38, 0x4c, 0x0c, 0x82, 0x78, 0xc5, 0x0b, 0x81, 0x28, 0x2c, 0x07, 0x2b,
  0x95, 0x28, 0x48, 0x77, 0xbf, 0xdd, 0xf3, 0x8a, 0x24, 0xf2, 0xe2, 0x15,
  0x4b, 0x51, 0x2d, 0xdd, 0xf8, 0x9f, 0x9e, 0x7d, 0xf8, 0xf8, 0xeb, 0x2f,
  0x6e, 0xaf, 0xd6, 0x27, 0x7a, 0xfa, 0x81, 0xac, 0xb4, 0x6a, 0x4b, 0x45,
  0xcc, 0xe6, 0x88, 0x46, 0x56, 0x47, 0xf7, 0x3a, 0x68, 0xfd, 0x48, 0x42,
  0x1c, 0xe7, 0xf4, 0xac, 0x28, 0xd7, 0xfa, 0xc4, 0xec, 0xc3, 0x19, 0x4f,
  0x74, 0x9c, 0xff, 0x01, 0x9f, 0x47, 0xfe, 0xdd, 0xeb, 0x28, 0x00, 0x00
};
const size_t indexLen = 2700;
void wifiServerInit();
void wifiServerListener();
void wifiServerSendIndex(FILE* stream);
void wifiServerSendSSID(FILE* stream, char linkID);
void wifiServerSaveConfig();
void wifiServerSendConfig(FILE* stream);
#endif
