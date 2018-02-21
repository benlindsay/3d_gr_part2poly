#ifndef GLOBALS_H
#define GLOBALS_H 

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cmath>

#define ABS(X) ( (X) < (0) ? ( (-1)*(X) ) : (X) )
#define MIN(A,B) ( ((A) < (B)) ? (A) : (B) )
#define MAX(A,B) ( ((A) > (B)) ? (A) : (B) )
#define PI 3.141592653589793238462643383

using namespace std;

enum xyz {X,Y,Z};

class Globals {

  public:
    Globals ();
    Globals (char*,int,int,int,int,int,int);
    virtual ~Globals ();

    double ***x,**dat,**bx;
    int ncol,ndat,ns,nP,frs;
    int **bonds;

    int read_xyz_traj(char*,int,int,int);
    void read_lmp_log(char*,int,int);

    double legendre(double);

    void reconnectChains(int,int);
    void reconnectChains();

    void addToCoord(double,int);
    double maxCoord(int);
    double minCoord(int);

    void assure(std::ifstream&,const std::string&);
    void assure(std::ofstream&,const std::string&);
    void assure(FILE*,char*);

    int nbonds,chl,nch;
    void setupBonds(int bond_l = 1);
    void writeBonds(int,int,char*);
    void writeAngles(int,int,char*);

    double getDistance(double*,double*,double*); /* gets distance between two vectors, must pass pointer */
    double msd(char*,int dT = 1);

    void log_space(int,int,int);
    void lin_space(int,int);
    int n_times, *times; // for space.cpp

  private:
    char tt[200],**tp;
    FILE *inp;
    int frs_skip,bxcol,frmin,frmax,Dim;
    double L_box;
};



#endif

