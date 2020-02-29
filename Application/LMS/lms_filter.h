#ifndef	LSM_FILTER_H_
#define	LSM_FILTER_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	#define LMS_COUNT									1024
	#define LMS_M 20

	float* LMS_Filter(int itr, const float* xn, const float* dn, double mu, int length);

	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*LSM_FILTER_H_ */