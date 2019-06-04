/*
 *  help.c
 */

#include "qlazy.h"

static void _help_print_outline() {
  printf("\
[commands]\n\
* initialize quantum state: %%,init \n\
* print quantum circuitt:   &,circ \n\
* print quantum gates:      !,gates \n\
* print quantum state:      -,show \n\
* print bloch angles:       |,bloch \n\
* echo input string:        @,echo \n\
* output quantum gates:     >,output \n\
* quit:                     .,quit \n\
* help:                     ?,help \n\
[quantum gates]\n\
* 1-qubit gates:            X,Y,Z,XR,XR+,H,S,S+,T,T+,P,RX,RY,RZ\n\
* 2-qubit gates:            CX,CY,CZ,CH,CP,CRX,CRY,CRZ\n\
* 3-qubit gates:            CCX\n\
* measurement:              M,MX,MY,MZ,MB\n\
[notes] \n\
* see \'help <item>\', for more information\n\
");
}

static void _help_print_init() {
  printf("\
== initialize quantum state ==\n\
[description] \n\
  This command makes all qubits to set |0>.\n\
  You must initialize before operating any quantum gate.\n\
[usage] \n\
  >> input <qubit_num> \n\
f[alias] \n\
  %% \n\
");
}

static void _help_print_circ() {
  printf("\
== print quantum circuit ==\n\
[description] \n\
  This command visualize quantum circuit with text.\n\
[usage] \n\
  >> circ \n\
[alias] \n\
  & \n\
");
}

static void _help_print_gates() {
  printf("\
== print quantum gates ==\n\
[description] \n\
   This command print quantum gates in order of operation \n\
[usage] \n\
  >> gates \n\
[alias] \n\
  ! \n\
");
}

static void _help_print_show() {
  printf("\
== print quantum state ==\n\
[description] \n\
   This command shows the probability amplitudes of current quantum state.\n\
[note] \n\
   - Normalize that amplitude of |00..0> is real and positive value,\n\
     and eliminate the phase factor.\n\
   - If 'show' the qubit that entangled to other qubits,\n\
     then result is probabilistic.\n\
[usage] \n\
  >> show \n\
  >> show <qubit_id>...\n\
[alias] \n\
  - \n\
");
}

static void _help_print_bloch() {
  printf("\
== print bloch angles ==\n\
[description] \n\
   This command prints the bloch angles of current quantum state.\n\
[note] \n\
   If no arguments are set, it prints the angles of 0-th qubit.\n\
[usage] \n\
  >> bloch \n\
  >> bloch <qubit_id> \n\
[alias] \n\
  | \n\
");
}

static void _help_print_echo() {
  printf("\
== echo strings ==\n\
[description] \n\
  This command prints any strings you set. \n\
[usage] \n\
  >> echo <strings>\n\
[alias] \n\
  @ \n\
");
}

static void _help_print_output() {
  printf("\
== output quantum gates ==\n\
[description] \n\
  This command outputs current quantum gates to quantum gates file.\n\
[usage] \n\
  >> output <file>\n\
[alias] \n\
  > \n\
");
}

static void _help_print_quit() {
  printf("\
== quit interactive mode ==\n\
[description] \n\
  This command is to quit interactive mode and return to your shell. \n\
[usage] \n\
  >> quit\n\
[alias] \n\
  . \n\
");
}

static void _help_print_m() {
  printf("\
== M gate ==\n\
[description] \n\
  M gate is to measure the current quantum state from any direction.\n\
  You can set number of mesurements (=shots), mesurement direction (=angle,phase),\n\
  and set qubit id you want to measure.\n\
  Default shots is %d, default angle,phase is 0.0 (z-axis), \n\
  and default qubit id's are all (all of the qubit id's are measured).\n\
[note] \n\
  Definition of 'angle' and 'phase' ... \n\
  - angle ... angle formed by z-axis in bloch sphere (unit: PI radian) \n\
  - phase ... angle around z-axis in bloch sphere (unit: PI radian) \n\
  If angle,phase aren't zero value, then measured state is u/d instead of 0/1. \n\
[usage] \n\
  >> M \n\
  >> M <qubit_id>...\n\
  >> M(<shots>)\n\
  >> M(<shots>,<angle>,<phase>)\n\
  >> M(<shots>,<angle>,<phase>) <qubit_id>...\n\
[alias] \n\
  m \n\
", DEF_SHOTS);
}

static void _help_print_mx() {
  printf("\
== MX gate ==\n\
[description] \n\
  MX gate is to measure the current quantum state from x-direction in bloch sphere.\n\
  You can set number of mesurements (=shots) and set qubit id you want to measure.\n\
  Default shots is %d, and default qubit id's are all \n\
  (all of the qubit id's are measured).\n\
[note] \n\
  Measured state is u/d instead of 0/1. \n\
[usage] \n\
  >> MX \n\
  >> MX <qubit_id>... \n\
  >> MX(<shots>) \n\
  >> MX(<shots>) <qubit_id>... \n\
[alias] \n\
  mx \n\
", DEF_SHOTS);
}

static void _help_print_my() {
  printf("\
== MY gate ==\n\
[description] \n\
  MY gate is to measure the current quantum state from y-direction in bloch sphere.\n\
  You can set number of mesurements (=shots) and set qubit id you want to measure.\n\
  Default shots is %d, and default qubit id's are all \n\
  (all of the qubit id's are measured).\n\
[note] \n\
  Measured state is u/d instead of 0/1. \n\
[usage] \n\
  >> MY \n\
  >> MY <qubit_id>... \n\
  >> MY(<shots>) \n\
  >> MY(<shots>) <qubit_id>... \n\
[alias] \n\
  my \n\
", DEF_SHOTS);
}

static void _help_print_mz() {
  printf("\
== MZ gate ==\n\
[description] \n\
  MZ gate is to measure the current quantum state from z-direction in bloch sphere.\n\
  You can set number of mesurements (=shots) and set qubit id you want to measure.\n\
  Default shots is %d, and default qubit id's are all \n\
  (all of the qubit id's are measured).\n\
[usage] \n\
  >> MZ \n\
  >> MZ <qubit_id>... \n\
  >> MZ(<shots>) \n\
  >> MZ(<shots>) <qubit_id>... \n\
[alias] \n\
  mz \n\
", DEF_SHOTS);
}

static void _help_print_mb() {
  printf("\
== MB gate ==\n\
[description] \n\
  MB gate is to execute 2-qubit Bell-measurement.\n\
  You can set number of mesurements (=shots) and set 2 qubit ids you want to bell-measure.\n\
  Default shots is %d.\n\
[usage] \n\
  >> MB <qubit_id> <qubit_id> \n\
  >> MB(<shots>) <qubit_id> <qubit_id> \n\
[alias] \n\
  mb \n\
", DEF_SHOTS);
}

static void _help_print_x() {
  printf("\
== X gate ==\n\
[description] \n\
  X gate is 1-qubit gate called \'pauli X gate\'. \n\
  - matrix expression:\n\
    | 0 1 | \n\
    | 1 0 | \n\
[usage] \n\
  >> X <qubit_id>\n\
[alias] \n\
  x \n\
");
}

static void _help_print_y() {
  printf("\
== Y gate ==\n\
[description] \n\
  Y gate is 1-qubit gate called \'pauli Y gate\'. \n\
  - matrix expression:\n\
    | 0 -i | \n\
    | i  0 | \n\
[usage] \n\
  >> Y <qubit_id>\n\
[alias] \n\
  y \n\
");
}

static void _help_print_z() {
  printf("\
== Z gate ==\n\
[description] \n\
  Z gate is 1-qubit gate called \'pauli Z gate\'. \n\
  - matrix expression:\n\
    | 1  0 | \n\
    | 0 -1 | \n\
[usage] \n\
  >> Z <qubit_id>\n\
[alias] \n\
  z \n\
");
}

static void _help_print_xr() {
  printf("\
== XR gate ==\n\
[description] \n\
  XR gate is 1-qubit gate called \'root pauli X gate\', satisfied X=XR*XR. \n\
  - matrix expression:\n\
    | (1+i)/2 (1-i)/2 | \n\
    | (1-i)/2 (1+i)/2 | \n\
[usage] \n\
  >> XR <qubit_id>\n\
[alias] \n\
  xr \n\
");
}

static void _help_print_xr_dagger() {
  printf("\
== XR+ gate ==\n\
[description] \n\
  XR+ gate is 1-qubit gate called \'hermitian conjugate of root pauli X gate\'. \n\
  - matrix expression:\n\
    | (1-i)/2 (1+i)/2 | \n\
    | (1+i)/2 (1-i)/2 | \n\
[usage] \n\
  >> XR+ <qubit_id>\n\
[alias] \n\
  xr+ \n\
");
}

static void _help_print_h() {
  printf("\
== H gate ==\n\
[description] \n\
  H gate is 1-qubit gate called \'hadamard gate\'. \n\
  - matrix expression:\n\
    | 1/sqrt(2)  1/sqrt(2) | \n\
    | 1/sqrt(2) -1/sqrt(2) | \n\
[usage] \n\
  >> H <qubit_id>\n\
[alias] \n\
  h \n\
");
}

static void _help_print_s() {
  printf("\
== S gate ==\n\
[description] \n\
  S gate is 1-qubit gate called \'phase shift gate\'.\n\
  It rotate through PI/2 around z-axis in bloch shpere. \n\
  - matrix expression:\n\
    | 1 0 | \n\
    | 0 i | \n\
[usage] \n\
  >> S <qubit_id>\n\
[alias] \n\
  s \n\
");
}

static void _help_print_s_dagger() {
  printf("\
== S+ gate ==\n\
[description] \n\
  S+ gate is 1-qubit gate, hermitian conjugate of S gate. \n\
  - matrix expression:\n\
    | 1  0 | \n\
    | 0 -i | \n\
[usage] \n\
  >> S+ <qubit_id>\n\
[alias] \n\
  s+ \n\
");
}

static void _help_print_t() {
  printf("\
== T gate ==\n\
[description] \n\
  T gate is 1-qubit gate called \'phase shift gate\'.\n\
  It rotate through PI/4 around z-axis in bloch shpere. \n\
  - matrix expression:\n\
    | 1 0             | \n\
    | 0 (1+i)/sqrt(2) | \n\
[usage] \n\
  >> T <qubit_id>\n\
[alias] \n\
  t \n\
");
}

static void _help_print_t_dagger() {
  printf("\
== T+ gate ==\n\
[description] \n\
  T+ gate is 1-qubit gate, hermitian conjugate of T gate. \n\
  - matrix expression:\n\
    | 1 0             | \n\
    | 0 (1-i)/sqrt(2) | \n\
[usage] \n\
  >> T+ <qubit_id>\n\
[alias] \n\
  t+ \n\
");
}

static void _help_print_p() {
  printf("\
== P gate ==\n\
[description] \n\
  P gate is 1-qubit gate, It transform phase.\n\
  - matrix expression:\n\
    | 1 0               | \n\
    | 0 exp(i*phase*PI) | \n\
[usage] \n\
  >> P(<phase>) <qubit_id>\n\
[alias] \n\
  p \n\
");
}

static void _help_print_rx() {
  printf("\
== RX gate ==\n\
[description] \n\
  RX gate is 1-qubit gate. It rotate through any phase around x-axis in bloch sphere. \n\
  - matrix expression:\n\
    |  cos(phase*PI/2)   -i*sin(phase*PI/2) | \n\
    | -i*sin(phase*PI/2)  cos(phase*PI/2)   | \n\
[usage] \n\
  >> RX(<phase>) <qubit_id>\n\
[alias] \n\
  rx \n\
");
}

static void _help_print_ry() {
  printf("\
== RY gate ==\n\
[description] \n\
  RY gate is 1-qubit gate. It rotate through any phase around y-axis in bloch sphere. \n\
  - matrix expression:\n\
    | cos(phase*PI/2) -sin(phase*PI/2) | \n\
    | sin(phase*PI/2)  cos(phase*PI/2) | \n\
[usage] \n\
  >> RY(<phase>) <qubit_id>\n\
[alias] \n\
  ry \n\
");
}

static void _help_print_rz() {
  printf("\
== RZ gate ==\n\
[description] \n\
  RZ gate is 1-qubit gate, It rotate through any phase around z-axis in bloch sphere.\n\
  - matrix expression:\n\
    | exp(-i*phase/2) 0              | \n\
    | 0               exp(i*phase/2) | \n\
[usage] \n\
  >> RZ(<phase>) <qubit_id>\n\
[alias] \n\
  rz \n\
");
}

static void _help_print_cx() {
  printf("\
== CX gate ==\n\
[description] \n\
  CX gate is 2-qubit gate called \'controlled X gate\' or \'controlled NOT (CNOT) gate\'.\n\
  It flips the second qubit if and only if the first qubit is |1>.\n\
  - matrix expression:\n\
    | 1 0 0 0 | \n\
    | 0 1 0 0 | \n\
    | 0 0 0 1 | \n\
    | 0 0 1 0 | \n\
[usage] \n\
  >> CX <qubit_id> <qubit_id>\n\
[alias] \n\
  cx \n\
");
}

static void _help_print_cy() {
  printf("\
== CY gate ==\n\
[description] \n\
  CY gate is 2-qubit gate called \'controlled Y gate\'.\n\
  - matrix expression:\n\
    | 1 0 0 0  | \n\
    | 0 1 0 0  | \n\
    | 0 0 0 -i | \n\
    | 0 0 i 0  | \n\
[usage] \n\
  >> CY <qubit_id> <qubit_id>\n\
[alias] \n\
  cy \n\
");
}

static void _help_print_cz() {
  printf("\
== CZ gate ==\n\
[description] \n\
  CZ gate is 2-qubit gate called \'controlled Z gate\'.\n\
  It operate Z gate to the second qubit if and only if the first qubit is |1>.\n\
  - matrix expression:\n\
    | 1 0 0  0 | \n\
    | 0 1 0  0 | \n\
    | 0 0 1  0 | \n\
    | 0 0 0 -1 | \n\
[usage] \n\
  >> CZ <qubit_id> <qubit_id>\n\
[alias] \n\
  cz \n\
");
}

static void _help_print_ch() {
  printf("\
== CH gate ==\n\
[description] \n\
  CH gate is 2-qubit gate called \'controlled H gate\'.\n\
  It operate H gate to the second qubit if and only if the first qubit is |1>.\n\
[usage] \n\
  >> CH <qubit_id> <qubit_id>\n\
[alias] \n\
  ch \n\
");
}

static void _help_print_cp() {
  printf("\
== CP gate ==\n\
[description] \n\
  CP gate is 2-qubit gate called \'controlled Phase Shift gate\'.\n\
  It operate P gate to the second qubit if and only if the first qubit is |1>.\n\
[usage] \n\
  >> CP(<phase>) <qubit_id> <qubit_id>\n\
[alias] \n\
  cp \n\
");
}

static void _help_print_crx() {
  printf("\
== CRX gate ==\n\
[description] \n\
  CRX gate is 2-qubit gate called \'controlled RX gate\'.\n\
  It operate RX gate to the second qubit if and only if the first qubit is |1>.\n\
[usage] \n\
  >> CRX(<phase>) <qubit_id> <qubit_id>\n\
[alias] \n\
  crx \n\
");
}

static void _help_print_cry() {
  printf("\
== CRY gate ==\n\
[description] \n\
  CRY gate is 2-qubit gate called \'controlled RY gate\'.\n\
  It operate RY gate to the second qubit if and only if the first qubit is |1>.\n\
[usage] \n\
  >> CRY(<phase>) <qubit_id> <qubit_id>\n\
[alias] \n\
  cry \n\
");
}

static void _help_print_crz() {
  printf("\
== CRZ gate ==\n\
[description] \n\
  CRZ gate is 2-qubit gate called \'controlled RZ gate\'.\n\
  It operate RZ gate to the second qubit if and only if the first qubit is |1>.\n\
[usage] \n\
  >> CRZ(<phase>) <qubit_id> <qubit_id>\n\
[alias] \n\
  crz \n\
");
}

static void _help_print_ccx() {
  printf("\
== CCX gate ==\n\
[description] \n\
  CCX gate is 3-qubit gate called \'controlled-controlled-X gate\' or \'toffoli gate\'.\n\
  It flips the third qubit if and only if the first and second qubit are both |1>.\n\
  - quantum circuit expresson:\n\
    0 --*---- \n\
    1 --*---- \n\
    2 --CCX-- \n\
  - equivalent another expresson:\n\
    0 ----------*----------*--------*--T----*--- \n\
    1 ----*----------*--------T-----CX---T+-CX-- \n\
    2 --H-CX-T+-CX-T-CX-T+-CX---T-H------------- \n\
[usage] \n\
  >> CCX <qubit_id> <qubit_id> <qubit_id>\n\
[alias] \n\
  ccx \n\
");
}

bool help_print(char* item)
{
  Kind kind;

  if (item == NULL) {
    _help_print_outline();
    SUC_RETURN(true);
  }
  
  qgate_get_kind(item, &kind);

  switch (kind) {
  case INIT:
    _help_print_init();
    break;
  case CIRC:
    _help_print_circ();
    break;
  case GATES:
    _help_print_gates();
    break;
  case SHOW:
    _help_print_show();
    break;
  case BLOCH:
    _help_print_bloch();
    break;
  case ECHO:
    _help_print_echo();
    break;
  case OUTPUT:
    _help_print_output();
    break;
  case HELP:
    _help_print_outline();
    break;
  case QUIT:
    _help_print_quit();
    break;
  case MEASURE:
    _help_print_m();
    break;
  case MEASURE_X:
    _help_print_mx();
    break;
  case MEASURE_Y:
    _help_print_my();
    break;
  case MEASURE_Z:
    _help_print_mz();
    break;
  case MEASURE_BELL:
    _help_print_mb();
    break;
  case PAULI_X:
    _help_print_x();
    break;
  case PAULI_Y:
    _help_print_y();
    break;
  case PAULI_Z:
    _help_print_z();
    break;
  case ROOT_PAULI_X:
    _help_print_xr();
    break;
  case ROOT_PAULI_X_:
    _help_print_xr_dagger();
    break;
  case HADAMARD:
    _help_print_h();
    break;
  case PHASE_SHIFT_S:
    _help_print_s();
    break;
  case PHASE_SHIFT_S_:
    _help_print_s_dagger();
    break;
  case PHASE_SHIFT_T:
    _help_print_t();
    break;
  case PHASE_SHIFT_T_:
    _help_print_t_dagger();
    break;
  case PHASE_SHIFT:
    _help_print_p();
    break;
  case ROTATION_X:
    _help_print_rx();
    break;
  case ROTATION_Y:
    _help_print_ry();
    break;
  case ROTATION_Z:
    _help_print_rz();
    break;
  case CONTROLLED_X:
    _help_print_cx();
    break;
  case CONTROLLED_Y:
    _help_print_cy();
    break;
  case CONTROLLED_Z:
    _help_print_cz();
    break;
  case CONTROLLED_H:
    _help_print_ch();
    break;
  case CONTROLLED_P:
    _help_print_cp();
    break;
  case CONTROLLED_RX:
    _help_print_crx();
    break;
  case CONTROLLED_RY:
    _help_print_cry();
    break;
  case CONTROLLED_RZ:
    _help_print_crz();
    break;
  case TOFFOLI:
    _help_print_ccx();
    break;
  default:
    ERR_RETURN(ERROR_INVALID_ARGUMENT,false);
  }

  SUC_RETURN(true);
}
