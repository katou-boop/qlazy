/*
 *  mdata.c
 */

#include "qlazy.h"

int mdata_init(int qubit_num, int state_num, int shot_num,
		    double angle, double phase, int qubit_id[MAX_QUBIT_NUM],
		    void** mdata_out)
{
  MData* mdata = NULL;

  g_Errno = NO_ERROR;
  
  if (!(mdata = (MData*)malloc(sizeof(MData)))) goto ERROR_EXIT;
  mdata->qubit_num = qubit_num;
  mdata->state_num = state_num;
  mdata->shot_num = shot_num;
  mdata->angle = angle;
  mdata->phase = phase;
  memcpy(mdata->qubit_id, qubit_id, sizeof(int)*MAX_QUBIT_NUM);

  if (!(mdata->freq = (int*)malloc(sizeof(int)*state_num))) goto ERROR_EXIT;
  for (int i=0; i<state_num; i++) mdata->freq[i] = 0;

  *mdata_out = mdata;

  return TRUE;

 ERROR_EXIT:
  g_Errno = ERROR_MDATA_INIT;
  return FALSE;
}

int mdata_print(MData* mdata)
{
  char	state[MAX_QUBIT_NUM+1];
  char	last_state[MAX_QUBIT_NUM+1];
  int   zflag = ON;

  g_Errno = NO_ERROR;

  if (mdata == NULL) goto ERROR_EXIT;

  if ((mdata->angle != 0.0) || (mdata->phase != 0.0)) zflag = OFF;
  else zflag = ON;

  if ((mdata->angle == 0.5) && (mdata->phase == 0.0)) {
    printf("direction of measurement: x-axis\n");
  }
  else if ((mdata->angle == 0.5) && (mdata->phase == 0.5)){
    printf("direction of measurement: y-axis\n");
  }
  else if ((mdata->angle == 0.0) && (mdata->phase == 0.0)){
    printf("direction of measurement: z-axis\n");
  }
  else {
    printf("direction of measurement: theta=%.3f*PI, phi=%.3f*PI\n",
	   mdata->angle, mdata->phase);
  }
  
  for (int i=0; i<mdata->state_num; i++) {
    if (get_binstr_from_decimal(state, mdata->qubit_num, i, zflag) == FALSE)
      return FALSE;
    if (mdata->freq[i] > 0) {
      printf("frq[%s] = %d\n", state, mdata->freq[i]);
    }
  }

  if (get_binstr_from_decimal(last_state, mdata->qubit_num,
			      mdata->last, zflag) == FALSE) return FALSE;
  printf("last state => %s\n", last_state);

  return TRUE;

 ERROR_EXIT:
  g_Errno = ERROR_MDATA_PRINT;
  return FALSE;
}

int mdata_print_bell(MData* mdata)
{
  g_Errno = NO_ERROR;

  if (mdata == NULL) goto ERROR_EXIT;
  if (mdata->state_num != 4) goto ERROR_EXIT;

  printf("bell-measurement\n");
  
  for (int i=0; i<mdata->state_num; i++) {
    if (mdata->freq[i] > 0) {
      if (i == BELL_PHI_PLUS)       printf("frq[phi+] = %d\n", mdata->freq[i]);
      else if (i == BELL_PSI_PLUS)  printf("frq[psi+] = %d\n", mdata->freq[i]);
      else if (i == BELL_PSI_MINUS) printf("frq[psi-] = %d\n", mdata->freq[i]);
      else if (i == BELL_PHI_MINUS) printf("frq[phi-] = %d\n", mdata->freq[i]);
      else goto ERROR_EXIT;
    }
  }

  if (mdata->last == BELL_PHI_PLUS)       printf("last state => phi+\n");
  else if (mdata->last == BELL_PSI_PLUS)  printf("last state => psi+\n");
  else if (mdata->last == BELL_PSI_MINUS) printf("last state => psi-\n");
  else if (mdata->last == BELL_PHI_MINUS) printf("last state => phi-\n");
  else goto ERROR_EXIT;
  
  return TRUE;
  
 ERROR_EXIT:
  g_Errno = ERROR_MDATA_PRINT;
  return FALSE;
}

void mdata_free(MData* mdata)
{
  if (mdata != NULL) {
    if (mdata->freq != NULL) {
      free(mdata->freq); mdata->freq = NULL;
    }
    free(mdata);
  }
}
