/* $Id: lcaClear.c,v 1.1 2004/03/24 04:05:23 till Exp $ */

/* matlab wrapper for ezcaGetNelem */

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
char	**s;
int		m = -1;

	if ( 0 == nlhs )
		nlhs = 1;

	if ( 1 < nlhs ) {
		MEXERRPRINTF("Too many lhs args");
		goto cleanup;
	}

	if ( 1 < nrhs ) {
		MEXERRPRINTF("Too many rhs args");
		goto cleanup;
	}


	if ( nrhs > 0 && buildPVs(prhs[0],&pvs) )
		goto cleanup;

	if ( (s = pvs.names) )
		m = pvs.m;

#if 0 /* lcaClear('') or lcaClear({''}) do not pass buildPVs() ;=( */
	if ( 1 == m  && 0 == *s[0] ) {
		/* special case: lcaClear('') clears only disconnected channels */
		s = 0;
		m = 0;
	}
#endif

    if ( multi_ezca_clear_channels( s, m ) )
		goto cleanup;

	nlhs = 0;

cleanup:
	releasePVs(&pvs);
	/* do this LAST (in case mexErrMsgTxt is called) */
	ERR_CHECK(nlhs, plhs);
}
