# abaqus_umat_C++
Example of abaqus umat code by C++

1. C3D8R_3D_umat.inp
   Abaqus input file. There is just one single element (C3D8R) inside. The boundary condition is set to simulate a drained triaxial test.
   There are three parameters. The first is E Young's modulus and the second is Poisson's ratio. The third one is not a material parameter which is used to control the write to sreen of the C++ subroutine.
2. umat_Cplusplus_3D_git.cpp
   UMAT is programmed in C++. A simple 3D elastic constitutive model is demonstrated.
3. main_umat_github.m
   A Matlab controller for submitting the abaqus job and for extracting the results automatically by python post-processing.
4. Post_step_01.py
   Python script to do the automatic post-processing.

The code is programmed by Zheng Li at University Gustave Eiffel. 
