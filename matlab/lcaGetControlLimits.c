/* $Id: lcaGetControlLimits.c,v 1.6 2004/02/27 01:24:34 till Exp $ */

/* matlab wrapper for ezcaGetControlLimits */

/* Author: Till Straumann <strauman@slac.stanford.edu>, 2002-2003  */

/* LICENSE: EPICS open license, see ../LICENSE file */

#include "mglue.h"
#include "multiEzca.h"

#include <cadef.h>
#include <ezca.h>

#include <ctype.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
PVs     pvs = { 0 };
MultiArgRec args[]={ { sizeof(double), 0, (void**)0 }, { sizeof(double), 0, (void**)0 } };
void	*pres[NumberOf(args)];
int     i,nargs = 0;

	if ( 0==nlhs )
		nlhs=1;

	if ( NumberOf(args) < nlhs ) {
		MEXERRPRINTF("Too many output args");
		goto cleanup;
	}

	if ( 1 != nrhs ) {
		MEXERRPRINTF("Expected one rhs argument");
		goto cleanup;
	}

	for ( i=0; i<NumberOf(args); i++) {
		args[i].pres = &pres[i];
		plhs[i]=0;
	}

	if ( buildPVs(prhs[0],&pvs) )
		goto cleanup;
	
	if ( !multi_ezca_get_misc(pvs.names, pvs.m, (MultiEzcaFunc)ezcaGetControlLimits, NumberOf(args), args) )
		goto cleanup;

	for ( i=0; i<nlhs; i++ ) {
		if ( !(plhs[i]=mxCreateDoubleMatrix(pvs.m, 1, mxREAL)) ) {
			MEXERRPRINTF("Not enough memory");
			goto cleanup;
		}
		memcpy(mxGetPr(plhs[i]), *args[i].pres, pvs.m * args[i].size);
	}

	nlhs = 0; /* prevent array destruction if everything is OK */

cleanup:
	for ( i=0; i<nlhs; i++ ) {
		if ( plhs[i] ) {
			mxDestroyArray(plhs[i]);
			plhs[i] = 0;
		}
	}
	for ( i=0; i<NumberOf(args); i++ ) {
		if ( args[i].pres )
			mxFree(*args[i].pres);
	}
	releasePVs(&pvs);
	/* do this LAST (in case mexErrMsgTxt is called) */
	ERR_CHECK(nlhs, plhs);
}
