#include "color_comparison.h"

uint64_t    matchColorEuclidean(void *color1, void *color2)
{
    Pixel       C1;
    Pixel       C2;
	int64_t		delta_channel[3];
	uint64_t	dE;

    C1 = *(Pixel *)color1;
    C2 = *(Pixel *)color2;

    delta_channel[R] = C1.channel[R] - C2.channel[R];
    delta_channel[G] = C1.channel[G] - C2.channel[G];
    delta_channel[B] = C1.channel[B] - C2.channel[B];
    delta_channel[R] *= delta_channel[R];
    delta_channel[G] *= delta_channel[G];
    delta_channel[B] *= delta_channel[B];
    dE = delta_channel[R] + delta_channel[G] + delta_channel[B];
    return dE;
}
