#include <iostream>
#include <string>
#include <omi_for_c.h> // abaqus 2022
#include <aba_for_c.h> // abaqus 6.14

extern "C" void FOR_NAME(umat, UMAT)(double stress[6], double statev[80], double DDSDDE[6][6], double& sse, double& spd,
		double& scd, double& rpl, double& ddsddt, double& drplde, double& drpldt,
		double stran[6], double dstran[6], double& time, double& dtime, double& temp,
		double& dtemp, double& predef, double& dpred, char cmname, int& ndi,
		int& nshr, int& ntens, int& nstatv, double props[40], int& nprops, 
		double& coords, double& drot, double& pnewdt, double& celent, double& dfgrd0, 
		double& dfgrd1, int& noel, int& npt, int& layer, int& kspt, 
		int& kstep, int& kinc, short cmname_len)
{
    int i, j, k;
    double DSTRESS[6], DDS[6][6]; // DDS is the elastic tangent matrix
    double zero, one, two, three;
    double six, nine, toler;
    double E, XNUE, EBULK3, EG2, EG, ELAM;
    double TRVAL;
	double temp_var;
	double LAMBDA, MU;

    zero  = 0.0;
    one   = 1.0;
    two   = 2.0;
    three = 3.0;
    six   = 6.0;
    nine  = 9.0;
    toler = 0.000001;

    E = props[0];

    XNUE = props[1];

	double plot_flag = props[2];
	
	// if (props[2] == 1)
	// {
	// std::cout << "E =  " << E << std::endl;
	// std::cout << "XNUE =  " << XNUE << std::endl;
	std::cout << "Step =  "      << kstep << std::endl;
	std::cout << "Increment =  " << kinc << std::endl;
	// }
//
// empty DDS
//
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
        DDS[i][j] = zero;
        }
    }
//
// calculate DDS
//
// method 1
//    EBULK3 = E / (one - two * XNUE);
//    EG2 = E / (one + XNUE);
//    EG = EG2 / two;
//    ELAM = (EBULK3 - EG2) / three;
//
//    for (i = 0; i < 3; i++)
//    {
//        for (j = 0; j < 3; j++)
//        {
//            DDS[j][i] = ELAM;
//        }
//        DDS[i][i] = EG2 + ELAM;
//    }
//	
//  DDS[3][3] = EG;
//	DDS[4][4] = EG;
//	DDS[5][5] = EG;
//
// method 2
    LAMBDA=E*XNUE/((one+XNUE)*(one-two*XNUE));
    MU=E/(two*(one+XNUE));
	  
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            DDS[j][i] = LAMBDA;
        }
        DDS[i][i] = LAMBDA + two*MU;
    }
	
    DDS[3][3] = MU;
	DDS[4][4] = MU;
	DDS[5][5] = MU;
    EG = MU;
    ELAM = LAMBDA;
//
// write to screen DDS
//
	if (props[2] == 1)
	{
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
        std::cout << DDS[i][j] << "	";
        }
        std::cout << std::endl;
    }
	}
//
// calculate dstress
//	
    TRVAL = dstran[0] + dstran[1] + dstran[2];
    for (k = 0; k < 3; k++)
    {
        DSTRESS[k] = 2 * EG * dstran[k] + ELAM * TRVAL;
    }
    DSTRESS[3] = EG * dstran[3];
	DSTRESS[4] = EG * dstran[4];
	DSTRESS[5] = EG * dstran[5];
//
// update stress
//
    for (k = 0; k < 6; k++)
    {
        stress[k] += DSTRESS[k];
    }
//
// update consistent tangent stiffness modulus
//
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 6; j++)
        {
		DDSDDE[i][j] = DDS[i][j];
        }
    }
//
return;
//
}


