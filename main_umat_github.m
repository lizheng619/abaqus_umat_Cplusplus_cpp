clear
clc
close all
system('del *.asv')
system('del aba*')
system('del *.dat')
system('del *.msg')
system('del *.mdl')
system('del *.sta')
system('del *.loc')
system('del *.odb')
system('del *.log')
system('del *.com')
system('del *.sim')
system('del *.res')
system('del *.prt')
system('del *.stt')
% C++
system('abaqus job=C3D8R_3D_umat user=umat_Cplusplus_3D_git int')
%
system('abaqus cae noGUI=Post_step_01.py')
%
%%%%%%%%%%%%%%%%%%%%%%%%%
load E11.dat
load E22.dat
load E33.dat
load E12.dat
load E13.dat
load E23.dat

load S11.dat
load S22.dat
load S33.dat
load S12.dat
load S13.dat
load S23.dat

load PS_1.dat
load PS_2.dat
load PS_3.dat
%%%%%%%%%%%%%%%%%%%%%%%%%
E_v=E11+E22+E33;
%%%%%%%%%%%%%%%%%%%%%%%%%
p=(PS_1+PS_2+PS_3)/3;

q=(((PS_1-PS_2).^2+(PS_1-PS_3).^2+(PS_2-PS_3).^2)/2).^(1/2);
%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1)
set(1,'Position',[200,50,800,600], 'color','w')
set(gca, 'fontsize',22)
set(gca,'LineWidth',1.0);
h01=plot(-E22*100,q*1000,'b-o','Linewidth',1.5,'MarkerSize',5); hold on
%
%     xlim([0 12])
%     ylim([0 1550])
%
xlabel('Axial Strain (%)','FontSize',22)
ylabel('Deviatoric Stress, q (kPa)','FontSize',22)
grid on