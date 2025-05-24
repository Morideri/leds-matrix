/*
 * mathFunctions.h
 *
 * Created: 15/06/2024 10:19:58
 *  Author: gabriel
 */ 


#ifndef MATHFUNCTIONS_H_
#define MATHFUNCTIONS_H_

#define module(x) \
({\
	typeof(x) _x = (x); \
	((_x >> (8 * sizeof(_x) - 1)) & 1) ? (~_x + 1) : _x;\
})


#endif /* MATHFUNCTIONS_H_ */