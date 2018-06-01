/* !!
  Program NRT.c: Program which implements the NRT model [M.J. Norgett,
                 M.T. Robinson and I.M. Torrens, Nucl. Engg. and Design,
		 33 (1975) 50-54]

  Inputs:
    Z1 and Z2 -> Atomic numbers of projectile and target (amu).
    A1 and A2 -> Mass numbers of projectile and target (amu).

  Outputs:
    Number of displaced atoms (Nd)

  Written by Manoj Warrier (manojwar@barc.gov.in) 02-10-2012
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define a0 5.2918e-2     // Bohr radius (nm)
#define echarge 1.4399    // electronic charge (eV nm)
#define Edisp 40.0       // Displacement energy (eV)
#define Kappa 0.8          // Displacement efficiency

int main (int argc, char **argv)
{
  int NDisp;
  double Z1, Z2, A1, A2, E, Ehat, dum1, dum2, TwoByThree,
	 OneBySix, ThreeByFour, eps, gofeps, kay, EMax, ELast, a;
  FILE *NdVsEngy;

  if (argc < 6)
    {
      printf ("Usage: ./NRTModel Z1 Z2 A1 A2 ELast\n");
      printf ("where Z1 Z2 are atomic numbers of the projectile and target,\n");
      printf ("A1 A2 are mass numbers of the projectile and target,\n");
      printf ("ELast is maximum energy (eV) upto which data will be generated.\n");
      exit(1);
    }
  sscanf (argv[1],"%lf",&Z1);
  sscanf (argv[2],"%lf",&Z2);
  sscanf (argv[3],"%lf",&A1);
  sscanf (argv[4],"%lf",&A2);
  sscanf (argv[5],"%lf",&ELast);

  NdVsEngy = fopen ("NdVsEngy.out", "w");
    if (NdVsEngy == NULL)
      {
        printf ("could not write NdVsEngy.out\n");
        exit(1);
      }

  #ifdef DBuG1
    printf ("Z1 = %e\n", Z1);
    printf ("Z2 = %e\n", Z2);
    printf ("A1 = %e\n", A1);
    printf ("A2 = %e\n", A2);
    printf ("ELast = %e\n", ELast);
  #endif /* DBuG1 */

  TwoByThree = 2.0 / 3.0;
  OneBySix = 1.0 / 6.0;
  ThreeByFour = 3.0/4.0;
  EMax = 25.0 * pow(Z1,4.0/3.0) * A1; /* Lindhard's e-stopping valid for
				         energies < 25*Z1^(4/3)A1       */
  
  dum1 = 0.8854 * a0; /* (9.0 * Pii * Pii / 128.0)^(1/3) = 0.88534 */
  dum2 = 1.0/sqrt( (pow(Z1,TwoByThree) + pow(Z2,TwoByThree)) );
  a = dum1 * dum2;

  kay = 0.1337 * pow(Z1,OneBySix) * sqrt(Z1/A1);
  dum1 = A2/(A1+A2) * a/(Z1*Z2*echarge*echarge);
  E = 100.0;
  while (E < ELast)
    {
      eps = dum1 * E;
      printf ("eps = %e, E = %e\n",eps,E);
      gofeps = 3.4008 * pow(eps,OneBySix) +
               0.40244 * pow(eps,ThreeByFour) + eps;
      Ehat = E/(1.0+kay*gofeps);
      NDisp = (int) (Kappa * Ehat / (2.0 * Edisp) );
      fprintf (NdVsEngy, "%e %e %d\n", E/1000.0, Ehat, NDisp);
      if (E > EMax)
        printf("E > (Emax = %e )\n", EMax);
      E = E + 100.0;
    }
  exit(0);
}
