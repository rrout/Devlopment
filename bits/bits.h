#include <stdio.h>

#define SET_BIT(data, pos)	(data |= (1 << pos))
#define CLEAR_BIT(data, pos)	(data &= ~(1 << pos))
#define IS_BIT_SET(data, pos)	(data & (1 << pos))
#define IS_BIT_CLEAR(data, pos)	~(data & (1 << pos))

#define SET_LONG_BIT(data, pos)		(data[pos/32] |= (1 << pos/32))
#define CLEAR_LONG_BIT(data, pos)       (data[pos/32] &= ~(1 << pos/32))
#define IS_LONG_BIT_SET(data, pos)      (data[pos/32] & (1 << pos/32))
#define IS_LONG_BIT_SET(data, pos)      ~(data[pos/32] & (1 << pos/32))


