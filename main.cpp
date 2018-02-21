#include "globals.h"
using namespace std;
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream> 

int main(int argc, char *argv[])
{

  if (argc < 8) {
    cout << "Usage: file [gr_dr] [traj.xyz] [box col] [frmin] [frmax] [nP] [frs_skip]" << endl;
    exit(1);
  }

  int ttnP = atoi(argv[6]) ,frmin = atoi(argv[4]), frmax = atoi(argv[5]), bxcol = atoi(argv[3]);

  double gr_dr = atof(argv[1]);

  Globals *globals = new Globals(argv[2],3,frmin,frmax,bxcol,ttnP,atoi(argv[7]));

  //globals->reconnectChains();

  double **bx = globals->bx,***x = globals->x; // "copy" globals->x to local variable

  int frs = globals->frs;



  /***********************************************************************
   * Begin code-specific calculations
   ***********************************************************************/

  //globals->log_space(1,frs,frs/2);

  double *gr,*gr_n,dr1[3],dot,mg1;
  int delt, gr_N = int(bx[0][2]/2.0/gr_dr +1 );

  gr = (double*) malloc( gr_N*sizeof(double) );
  gr_n = (double*) malloc( gr_N*sizeof(double) );

  for (int t=0; t<gr_N; ++t)
    gr[t] = gr_n[t] = 0.0;

  for (int t_int=0; t_int<frs; t_int++) {

    for(int i = 0; i<ttnP ;i++){
      for(int j=i+1;j<ttnP; j++){
        for(int k = 0;k<3 ;k++){
          dr1[k] = x[t_int][i][k] - x[t_int][j][k];
          if(dr1[k] > bx[0][k]/2.0)
            dr1[k] = bx[0][k] - dr1[k];
          else if(dr1[k] < -bx[0][k]/2.0)
            dr1[k] = bx[0][k] + dr1[k]; 
          else {}


        }
        mg1 = dr1[0]*dr1[0] + dr1[1]*dr1[1] +dr1[2]*dr1[2];
        mg1 = sqrt(mg1);
        /*if(mg1*10 <4.0){	
          cout<<i+1<<" "<<j+1<<" "<<mg1*10<<endl;

          }*/
        delt = int(mg1/gr_dr);
        if(delt<gr_N) gr[delt] +=2.0 ; 


      }	
    }
  }

  double V = bx[0][1]*bx[0][0]*bx[0][2];
  for(int i =1 ;i<gr_N ;i++){
    gr[i] /= 4.0/3.0*(pow(i+1,3.0)-pow(i,3.0))*pow(gr_dr,3.0)*PI;
    gr[i] /= double(ttnP)*double(ttnP)/V*frs; 
  }

  gr[0] = 0;
  char  name[30] ;
  sprintf(name,"gr_skp%s.dat",argv[7]);

  ofstream otp (name);

  for (int i=0; i<gr_N; ++i)
    otp<<gr_dr*(i+0.5)<<" "<<gr[i]/((double(ttnP) - 1.0 )/double(ttnP))<<endl;
  otp.close();

  delete globals;

  return 0;
}
