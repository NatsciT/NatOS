#pragma once

#define MAX_DIGITS	20

#define int_to_ascii(x)		( ( x ) + '0' )
#define ascii_to_int(x)		( ( x ) - '0' )



void int_to_string(int num, char* buffer);
void hex_to_string(int hex, char* buffer);