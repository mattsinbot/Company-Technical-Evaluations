clc;
clear;
close all;

addpath("../function_folder");

% Description: Given joint variables, compute forward kinematics.

%/////////////////////////////////////////////
%//////////////// Input //////////////////////
%/////////////////////////////////////////////
d1 = -0.200; th2 = 1.100; th3 = 1.100; th4 = 1.100;
% d1 = -0.2000;  th2 = 0.0993; th3 = 0.1014; th4 = 0.0994;
% d1 = -0.200; th2 = 0.00; th3 = 0.00; th4 = 0.00;

% /////////// Solve Forward Kinematics //////////
Tee = dobotM1_fk2(d1, th2, th3, th4);