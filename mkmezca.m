function mkmezca()
mk('ecget.c')
mk('ezcaGetControlLimits.c')
mk('ezcaPut.c')
mk('ezcaGet.c')
mk('ezcaGetNelem.c')
%
%
function mk(feil)
eval(['mex -cxx -DMATLAB_APP -DmexErrMsgTxt=mexWarnMsgTxt -I. -Iezca -I/afs/slac/g/spear/3.14.2epics/base/include -I/afs/slac/g/spear/3.14.2epics/base/include/os/Linux -L. ',feil,' -lmezcaglue'])
%-L/afs/slac/g/spear/epics/base/lib/linux-x86 -Llib/linux-x86 -lezca314 -lca -lCom
