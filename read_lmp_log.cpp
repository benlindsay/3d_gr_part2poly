#include "globals.h"

void Globals::read_lmp_log(char* nm, int frmin_val , int frmax_val ) {

  inp = fopen(nm,"r");
  assure(inp,nm);
  
  int i,j;
  double dm;

  fgets(tt,200,inp); 
  
  ncol = 1; 
  /*char prev_char = 'a';
  for ( i=0; i<200 ; i++ ) {
    if ( tt[i] == ' ' && prev_char != ' ' )
      ncol++;
    else if ( tt[i] == '\n' ) 
      break;
    prev_char = tt[i];
  }*/

  fclose(inp);

  ndat = frmax_val - frmin_val ;

  dat = ( double** ) calloc( ndat , sizeof(double*) ); //allocate memory for # of rows
  for ( i=0; i<ndat; i++) 
    dat[i] = ( double* ) calloc( ncol , sizeof(double) ); //allocate memory for # of columns

  inp = fopen(nm,"r");

//  for ( i=0 ; i<frmin ; i++ ) //stores the first line of frmin into array tt[200]
  //  fgets(tt,200,inp);

 /* for ( i=0 ; i<ndat; i++ ) {
    for ( j=0 ; j<ncol ; j++ ) {
      fscanf(inp,"%lf" , &dm );
      dat[i][j] = dm ;
    }
  }*/

  fclose(inp);
}
