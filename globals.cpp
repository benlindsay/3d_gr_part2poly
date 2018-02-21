#include "globals.h"

void Globals::assure(FILE *file, char* nm)
{
  if (file==NULL) {
    cout << "Could not open " << nm << "!" << endl;
    exit(1);
  }
}

void Globals::assure(std::ifstream& in,
    const std::string& filename = "") {
  using namespace std;
  if(!in) {
    fprintf(stderr, "Could not open file %s\n",
        filename.c_str());
    exit(1);
  }
}

void Globals::assure(std::ofstream& out,
    const std::string& filename = "") {
  using namespace std;
  if(!out) {
    fprintf(stderr, "Could not open file %s\n",
        filename.c_str());
    exit(1);
  }
}

Globals::~Globals() 
{
  free(x);
}

Globals::Globals()
{
}

/***********************************************************************
 * Constructor. Initialize, read lmp log, read xyz coordinates. 
 ***********************************************************************/
 
Globals::Globals( char* xyz , int Dim_var, int frmin_val , int frmax_val , int bxcol_val ,int nP_var,int frs_skip_var):Dim(Dim_var),frmin(frmin_val), frmax(frmax_val), bxcol(bxcol_val),nP(nP_var),frs_skip(frs_skip_var){

  frs = int(double(frmax - frmin)/double(frs_skip));
 // read_lmp_log( log , frmin , frmax );
  
  cout << "Read " << ndat << " times, " << ncol  << endl;
  
  frs = read_xyz_traj( xyz , frmin , frmax, frs_skip );

 // if (frs > ndat)
 //   frs = ndat;

/*  for (int i=0; i<frs; i++)
    if (dat[i][bxcol+0]==0.0 || dat[i][bxcol+1]==0.0 || dat[i][bxcol+2]==0.0) {
      frs=i;
      break;
    }
*/
  cout << frs << " frames" << endl;


}

/***********************************************************************
 * Reconnecting Chains. Two versions...
 ***********************************************************************/
void Globals::reconnectChains()
{
  double dx;
  for ( int t=1; t<frs; t++ ) {
    for ( int i=0; i<ns; i++ ) {
      for ( int j=0; j<3; j++ ) {
        double bl = 0.5 * ( bx[t][j] + bx[t-1][j] );

        dx = (x[t][i][j] - x[t-1][i][j]);
        while ( dx > bl/2. ) {
          x[t][i][j] -= bl;
          dx = (x[t][i][j] - x[t-1][i][j]);
        }
        while ( dx <= -bl/2. ) {
          x[t][i][j] += bl;
          dx = (x[t][i][j] - x[t-1][i][j]);
        }

        dx = (x[t][i][j] - x[t-1][i][j]);
        if ( dx > 0.5 * bl || dx < -0.5*bl ) {
          cout << "You suck! " << dx << " " << t << " " << i << " " << j << endl;
          exit(1);
        }
      }
    }
  }
}

