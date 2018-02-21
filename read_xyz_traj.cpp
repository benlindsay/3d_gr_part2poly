#include "globals.h"

int Globals::read_xyz_traj(char *nm, int frmin_val , int frmax_val ,int frs_skip_var) {

  int i, j;

  inp = fopen(nm,"r");
  assure(inp,nm);
  int  tmp_frs,tmp_np,tmp_var;
  int MAX = frmax_val - frmin_val ;
  x = (double***) calloc(frs+2,sizeof(double**));
  //  frs = MAX;


  double tmp_vard, tmp_bl[3];
  fgets( tt , 200 , inp );
  fscanf(inp,"%d",&ns);fgets( tt , 200 , inp );
  if(ns < nP) {
    cout<<"ns < nP!!"<<endl;	
    exit(1);}
  for(i=0; i<ns; i++)
    fgets( tt , 200 , inp );

  fscanf(inp,"%lf %lf %lf",&tmp_bl[0],&tmp_bl[1],&tmp_bl[2]);

  fclose(inp);

  cout<<"bl1 "<<tmp_bl[0]<<" bl2 "<<tmp_bl[1]<<" bl3 "<<tmp_bl[2]<<endl;

  inp = fopen( nm, "r" );

  for ( i=0 ; i < frmin_val ; i++ ) {
    for ( j=0 ; j < ns+3 ; j++ )
      fgets( tt , 200 , inp );

    printf(" skip frame %d of %d frmin\n", i, frmin_val); fflush(stdout);

  }

  bx = (double**) calloc(frs,sizeof(double*));
  for ( int t=0; t<frs; t++ ) {
    bx[t] = (double*) calloc(3,sizeof(double));
    for(int m=0;m<3; m++){
      bx[t][m] = tmp_bl[m];//dat[t][bxcol];

    }

  }

  for ( j=0 ; j<frs ; j++ ) {

    for (i=0; i<(ns+3)*(frs_skip_var-1); i++)
      fgets(tt,200,inp);




    fgets(tt,200,inp);
    fgets(tt,200,inp); // skip the first 2 lines (# of ns, "Atoms")

    x[j] = (double**) calloc(nP,sizeof(double*));
    for (i=0; i<nP; i++)
      x[j][i] = (double*) calloc(3,sizeof(double));

    // Allocate memory for the particle types //
    if (j==0) {
      tp = (char**) calloc(ns,sizeof(char*));
      for (i=0; i<ns; i++)
        tp[i] = (char*) calloc(10,sizeof(char));
    }
    tmp_np = 0;
    //cout<<"reach here"<<endl;
    // Read the frame
    for (i=0; i<ns; i++) {
      //  cout<<i<<endl; 

      fscanf(inp,"%d",&tmp_var); if (feof(inp)) break;
      fscanf(inp,"%s",tp[i]); if (feof(inp)) break;
      fscanf(inp,"%s",tp[i]); if (feof(inp)) break;
      if(tp[i][1] == 0) fscanf(inp,"%d",&tmp_var); if (feof(inp)) break;
      // cout<<(tp[i][1] == 0)<<" "<<tmp_var<<endl;
      if(tp[i][0] == 'O'){
        fscanf(inp,"%lf",&x[j][tmp_np][0]);if (feof(inp)) break;
        fscanf(inp,"%lf",&x[j][tmp_np][1]);if (feof(inp)) break;
        fscanf(inp,"%lf",&x[j][tmp_np][2]);if (feof(inp)) break;
        //cout<<tmp_np+1<<" "<<x[j][tmp_np][0]<<" "<<x[j][tmp_np][1]<<" "<<x[j][tmp_np][2]<<endl;
        tmp_np +=1;
      }
      else {
        fscanf(inp,"%lf",&tmp_vard);if (feof(inp)) break;
        fscanf(inp,"%lf",&tmp_vard);if (feof(inp)) break;
        fscanf(inp,"%lf",&tmp_vard);if (feof(inp)) break;
      }
      fgets(tt,200,inp);if (feof(inp)) break;

    }
    fgets(tt,200,inp);//skip the last line about box dim
    if (tmp_np  != nP ) {cout<<"nP ! = tmp_np !!!"<<endl; exit(1);}
    printf("frame %d of %d frs read\n", j, frs); fflush(stdout); 
  }
  printf("\n");
  printf("Read %d frames with %d sites\n",frs,ns);
  return frs;

}
