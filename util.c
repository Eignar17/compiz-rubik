//a collection of utility methods

#include "rubik-internal.h"
#include <math.h>
#include <float.h>

int
getCurrentDeformation (CompScreen *s)
{
    CUBE_SCREEN (s);

    CompPlugin *p = NULL;
    const char plugin[] = "cubeaddon";
    p = findActivePlugin (plugin);
    if (p && p->vTable->getObjectOptions)
    {
	CompOption *option;
	int  nOption;
	Bool cylinderManualOnly = FALSE;
	Bool unfoldDeformation = TRUE;

	option = (*p->vTable->getObjectOptions) (p, (CompObject *)s,
		&nOption);
	option = compFindOption (option, nOption, "cylinder_manual_only", 0);

	if (option)
	    if (option->value.b)
		cylinderManualOnly = option->value.b;

	option = (*p->vTable->getObjectOptions) (p, (CompObject *)s,
		&nOption);
	option = compFindOption (option, nOption, "unfold_deformation", 0);

	if (option)
	    if (option->value.b)
		unfoldDeformation = option->value.b;

	if (s->hsize * cs->nOutput > 2 && s->desktopWindowCount &&
	    (cs->rotationState == RotationManual ||
	    (cs->rotationState == RotationChange &&
	    !cylinderManualOnly)) &&
	    (!cs->unfolded || unfoldDeformation))
	{
	    option = (*p->vTable->getObjectOptions) (p, (CompObject *)s,
		      &nOption);
	    option = compFindOption (option, nOption, "deformation", 0);

	    if (option)
		return (option->value.i);
	}
    }
    return DeformationNone;
}

int
getDeformationMode (CompScreen *s)
{
    CompPlugin *p = NULL;
    const char plugin[] = "cubeaddon";
    p = findActivePlugin (plugin);
    if (p && p->vTable->getObjectOptions)
    {
	CompOption *option;
	int  nOption;
	option = (*p->vTable->getObjectOptions) (p, (CompObject *)s,
		  &nOption);
	option = compFindOption (option, nOption, "deformation", 0);

	if (option)
	    return (option->value.i);
    }
    return DeformationNone;
}

float randf (float x) { //return random number in range [0,x)
	return rand()/(((double)RAND_MAX + 1) / x);
}
float minimum (float x, float y) {
	return ((x) < (y) ? (x) : (y));
}
float maximum (float x, float y) {
	return ((x) > (y) ? (x) : (y));
}
float symmDistr() { //returns number in range [-1, 1] with bias towards 0, symmetric about 0.
	float x = 2*randf(1)-1;
	return x*(1-cbrt(1-fabsf(x)));
}
void setColor(float* color, float r, float g, float b, float a, float randomOffset, float randomness) {
	float ro = randf(randomOffset);
	color[0]=r+ro+randf(randomness);
	color[1]=g+ro+randf(randomness);
	color[2]=b+ro+randf(randomness);
	color[3]=a;
	
	int i;
	for (i=0; i<4; i++) {
		if (color[i]<0) color[i]=0;
		else if (color[i]>1) color[i]=1;
	}
}
void setSpecifiedColor (float* color, int c) {
	switch (c) {
	case RANDOMCOLOR: setColor(color, 0,0,0,1,0,1); break;
	case BLACK:       setColor(color, 0,0,0,1,0,0); break;
	case BLUE:        setColor(color, 0,0,1,1,0,0); break;
	case BROWN:       setColor(color, 0.5,0.25,0.05,1,0,0); break;
	case CYAN:        setColor(color, 0,1,1,1,0,0); break;
	case GREEN:       setColor(color, 0,1,0,1,0,0); break;
	case GREY:        setColor(color, 0.5,0.5,0.5,1,0,0); break;
	case ORANGE:      setColor(color, 1,0.5,0,1,0,0); break;
	case PINK:        setColor(color, 1,0,1,1,0,0); break;
	case PURPLE:      setColor(color, 0.5,0,1,1,0,0); break;
	case RED:         setColor(color, 1,0,0,1,0,0); break;
	case YELLOW:      setColor(color, 1,1,0,1,0,0); break;
	case WHITE:       setColor(color, 1,1,1,1,0,0); break;
	}
}
