clc;
clear;
close all;

addpath("../function_folder");

% Description: Position, Velocity, Acceleration trajectory using single spline at
% position level.

% //////////// Inputs ///////////////////////////
t0 = 0; tf = 3; th_0 = 0.3; th_f = pi/3; ddth = 40*pi/180; tm_cycle = 0.01;

% ////////// Obtain trajectory ///////////////////////
[th_profile, dth_profile, ddth_profile, time_profile] = dobotM1_gentraj(t0, tf, th_0, th_f, ddth, tm_cycle);