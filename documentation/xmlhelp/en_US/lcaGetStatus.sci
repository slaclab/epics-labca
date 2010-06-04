function lcaGetStatus
// Retrieve the alarm severity and status of a number of PVs.
//  Calling Sequence
//[severity, status, timestamp] = lcaGetStatus(pvs)
//  Description
//   Retrieve the alarm severity and status of a number of PVs along with
//   their timestamp.
//  Parameters
//   pvs: Column vector (in matlab: m x 1 cell- matrix) of m strings.
//   severity: m x 1 column vector of the alarm severities.
//   status: m x 1 column vector of the alarm status.
//   timestamp: m x 1 complex column vector holding the PV <link linkend='lca_common_timestamp_val'>timestamps</link>.
endfunction
