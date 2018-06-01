# YenAreTea
Implementation of the Norgett-Robinson-Terrence model for irradiation damage
  Program NRT.c: Program which implements the NRT model [M.J. Norgett,
                 M.T. Robinson and I.M. Torrens, Nucl. Engg. and Design,
                 33 (1975) 50-54]

  Inputs:
    Z1 and Z2 -> Atomic numbers of projectile and target (amu).
    A1 and A2 -> Mass numbers of projectile and target (amu).

  Outputs:
    Number of displaced atoms (Nd)

  Written by Manoj Warrier (Manoj.Warrier@gmail.com) 02-10-2012

  Compilation
    gcc -Wall -g NRT.c -lm -o NRT

  Run
    ./NRTModel Z1 Z2 A1 A2 ELast
    where atomic numbers of the projectile and target,
    A1 A2 are mass numbers of the projectile and target,
   ELast is maximum energy (eV) upto which data will be generated.
