#ifndef KULKI_RAWDATACELL_HPP
#define KULKI_RAWDATACELL_HPP
#include "rawdata.hpp"
namespace RD {
static constexpr RawData cell{
    "PNG",
    to_array_const<const char>(
        {'\x89', '\x50', '\x4e', '\x47', '\x0d', '\x0a', '\x1a', '\x0a', '\x00', '\x00', '\x00', '\x0d', '\x49',
         '\x48', '\x44', '\x52', '\x00', '\x00', '\x00', '\x2d', '\x00', '\x00', '\x00', '\x2d', '\x08', '\x02',
         '\x00', '\x00', '\x00', '\xb5', '\x78', '\x75', '\xcd', '\x00', '\x00', '\x01', '\x84', '\x69', '\x43',
         '\x43', '\x50', '\x49', '\x43', '\x43', '\x20', '\x70', '\x72', '\x6f', '\x66', '\x69', '\x6c', '\x65',
         '\x00', '\x00', '\x28', '\x91', '\x7d', '\x91', '\x3d', '\x48', '\xc3', '\x50', '\x14', '\x85', '\x4f',
         '\x5b', '\xa5', '\x45', '\x2a', '\x82', '\xed', '\x50', '\xc4', '\x21', '\x43', '\x75', '\xb2', '\x20',
         '\x2a', '\xe2', '\xa8', '\x55', '\x28', '\x42', '\x85', '\x50', '\x2b', '\xb4', '\xea', '\x60', '\xf2',
         '\xd2', '\x3f', '\x68', '\xd2', '\x90', '\xa4', '\xb8', '\x38', '\x0a', '\xae', '\x05', '\x07', '\x7f',
         '\x16', '\xab', '\x0e', '\x2e', '\xce', '\xba', '\x3a', '\xb8', '\x0a', '\x82', '\xe0', '\x0f', '\x88',
         '\x9b', '\x9b', '\x93', '\xa2', '\x8b', '\x94', '\x78', '\x5f', '\x52', '\x68', '\x11', '\xe3', '\x83',
         '\xcb', '\xfb', '\x38', '\xef', '\x9d', '\xc3', '\x7d', '\xf7', '\x01', '\xfe', '\x66', '\x95', '\xa9',
         '\x66', '\xcf', '\x38', '\xa0', '\x6a', '\x96', '\x91', '\x49', '\x25', '\x85', '\x5c', '\x7e', '\x55',
         '\x08', '\xbe', '\x22', '\x84', '\x41', '\xaa', '\x18', '\x22', '\x12', '\x33', '\xf5', '\x39', '\x51',
         '\x4c', '\xc3', '\x73', '\x7d', '\xdd', '\xc3', '\xc7', '\xf7', '\xbb', '\x04', '\xcf', '\xf2', '\xbe',
         '\xf7', '\xe7', '\xea', '\x57', '\x0a', '\x26', '\x03', '\x7c', '\x02', '\xf1', '\x2c', '\xd3', '\x0d',
         '\x8b', '\x78', '\x83', '\x78', '\x7a', '\xd3', '\xd2', '\x39', '\xef', '\x13', '\x47', '\x59', '\x59',
         '\x52', '\x88', '\xcf', '\x89', '\xc7', '\x0c', '\x6a', '\x90', '\xf8', '\x91', '\xeb', '\xb2', '\xcb',
         '\x6f', '\x9c', '\x4b', '\x0e', '\xfb', '\x79', '\x66', '\xd4', '\xc8', '\x66', '\xe6', '\x89', '\xa3',
         '\xc4', '\x42', '\xa9', '\x8b', '\xe5', '\x2e', '\x66', '\x65', '\x43', '\x25', '\x9e', '\x22', '\x8e',
         '\x2b', '\xaa', '\x46', '\xf9', '\xfe', '\x9c', '\xcb', '\x0a', '\xe7', '\x2d', '\xce', '\x6a', '\xb5',
         '\xce', '\xda', '\x7d', '\xf2', '\x17', '\x86', '\x0b', '\xda', '\xca', '\x32', '\xd7', '\xa9', '\x86',
         '\x91', '\xc2', '\x22', '\x96', '\x20', '\x42', '\x80', '\x8c', '\x3a', '\x2a', '\xa8', '\xc2', '\x42',
         '\x82', '\x76', '\x8d', '\x14', '\x13', '\x19', '\x3a', '\x4f', '\x7a', '\xf8', '\x87', '\x1c', '\xbf',
         '\x48', '\x2e', '\x99', '\x5c', '\x15', '\x30', '\x72', '\x2c', '\xa0', '\x06', '\x15', '\x92', '\xe3',
         '\x07', '\xff', '\x83', '\xdf', '\xb3', '\x35', '\x8b', '\x93', '\x13', '\x6e', '\x52', '\x38', '\x09',
         '\xf4', '\xbe', '\xd8', '\xf6', '\xc7', '\x08', '\x10', '\xdc', '\x05', '\x5a', '\x0d', '\xdb', '\xfe',
         '\x3e', '\xb6', '\xed', '\xd6', '\x09', '\x10', '\x78', '\x06', '\xae', '\xb4', '\x8e', '\xbf', '\xd6',
         '\x04', '\x66', '\x3e', '\x49', '\x6f', '\x74', '\xb4', '\xf8', '\x11', '\x30', '\xb0', '\x0d', '\x5c',
         '\x5c', '\x77', '\x34', '\x79', '\x0f', '\xb8', '\xdc', '\x01', '\x62', '\x4f', '\xba', '\x64', '\x48',
         '\x8e', '\x14', '\xa0', '\xf2', '\x17', '\x8b', '\xc0', '\xfb', '\x19', '\x7d', '\x53', '\x1e', '\x88',
         '\xdc', '\x02', '\x7d', '\x6b', '\xee', '\xdc', '\xda', '\xe7', '\x38', '\x7d', '\x00', '\xb2', '\x34',
         '\xab', '\xf4', '\x0d', '\x70', '\x70', '\x08', '\x8c', '\x96', '\x28', '\x7b', '\xdd', '\xe3', '\xdd',
         '\xa1', '\xee', '\xb9', '\xfd', '\x7b', '\xa7', '\x3d', '\xbf', '\x1f', '\x2d', '\x3b', '\x72', '\x8b',
         '\x4b', '\x69', '\x39', '\xbb', '\x00', '\x00', '\x00', '\x09', '\x70', '\x48', '\x59', '\x73', '\x00',
         '\x00', '\x0e', '\xc4', '\x00', '\x00', '\x0e', '\xc4', '\x01', '\x95', '\x2b', '\x0e', '\x1b', '\x00',
         '\x00', '\x00', '\x07', '\x74', '\x49', '\x4d', '\x45', '\x07', '\xe5', '\x08', '\x12', '\x08', '\x20',
         '\x26', '\x09', '\xa7', '\x04', '\xa3', '\x00', '\x00', '\x00', '\x54', '\x49', '\x44', '\x41', '\x54',
         '\x58', '\xc3', '\xed', '\xd8', '\xb1', '\x11', '\x00', '\x20', '\x0c', '\x42', '\x51', '\xf4', '\xb2',
         '\xff', '\x4c', '\x64', '\xb2', '\x58', '\x78', '\xba', '\x42', '\x52', '\x7c', '\x3a', '\xba', '\x77',
         '\x94', '\xac', '\xaa', '\x52', '\x77', '\x32', '\x73', '\x4f', '\x40', '\xd8', '\x8e', '\x5f', '\xba',
         '\x1c', '\xb6', '\x25', '\xf5', '\xef', '\x71', '\x83', '\x03', '\x07', '\x0e', '\x1c', '\x38', '\x70',
         '\xe0', '\xc0', '\x81', '\x03', '\x07', '\x0e', '\x1c', '\x38', '\x70', '\xe0', '\xc0', '\x81', '\x03',
         '\x07', '\x0e', '\x1c', '\xd3', '\x1c', '\xa1', '\xf7', '\xe8', '\x36', '\xef', '\x31', '\x01', '\x21',
         '\xe9', '\x00', '\xd8', '\x1a', '\x17', '\xaa', '\x51', '\xe7', '\xc1', '\x3e', '\x00', '\x00', '\x00',
         '\x00', '\x49', '\x45', '\x4e', '\x44', '\xae', '\x42', '\x60', '\x82'})};
}
#endif