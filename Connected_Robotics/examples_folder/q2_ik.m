clc;
clear;
close all;

addpath("../function_folder");

% Description: Given End-effector pose, computes joint variables

%/////////////////////////////////////////////
%//////////////// Input //////////////////////
%/////////////////////////////////////////////
T = [-0.9991, -0.0416, 0, 0.1230;
      0.0416, -0.9991, 0, 0.3399;
      0, 0, 1.0000, -0.0500;
      0, 0, 0, 1];
  
joint_sol = dobotM1_ik2(T);
if isnan(joint_sol)
    fprintf("No solution found. \n");
else
    fprintf("Joint Solution: \n");
    disp(joint_sol);
end