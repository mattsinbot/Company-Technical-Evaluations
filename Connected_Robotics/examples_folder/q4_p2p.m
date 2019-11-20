clc;
clear;
close all;

addpath("../function_folder");

% Description: Given end-effector poses at the start and goal, compute
% joint trajectories using jointspace scheme.

% //////////////////// Input ////////////////////////////
rz1 = 0.300; ry1 = 0.000; rx1 = 0.000;
px1 = 0.5450; py1 = 0.0597; pz1 = -0.050;
% d1 = -0.200; th2 = 0.100; th3 = 0.100; th4 = 0.100;

rz2 = -2.9832; ry2 = 0.000; rx2 = 0.000;
px2 = 0.1230; py2 = 0.3399; pz2 = -0.050;
% d1 = -0.200; th2 = 1.100; th3 = 1.100; th4 = 1.100;

Tee_Start = get_homogeneous(px1, py1, pz1, rz1, ry1, rx1);
Tee_Goal = get_homogeneous(px2, py2, pz2, rz2, ry2, rx2);


% Tee_Start = [0.9553, -0.2955, 0, 0.5450;
%              0.2955, 0.9553, 0, 0.0597;
%              0, 0, 1.0000, -0.0500;
%              0, 0, 0, 1.0000];
% [rx_Start, ry_Start, rz_Start] = rotm2eul(Tee_Start(1:3, 1:3));
% d1 = -0.200; th2 = 0.100; th3 = 0.100; th4 = 0.100;
% 
% Tee_Goal = [-0.9875, 0.1577, 0, 0.1230;
%             -0.1577,-0.9875, 0, 0.3399;
%              0, 0, 1.0000, -0.0500;
%              0, 0, 0, 1.0000];
% d1 = -0.200; th2 = 1.100; th3 = 1.100; th4 = 1.100;

% //////////// Solve Inverse Kinematics ////////////////////
sol_Start = dobotM1_ik2(Tee_Start);
sol_Goal = dobotM1_ik2(Tee_Goal);

% /////////////// Get the joint solutions //////////////////
js_Start = sol_Start(1, 2:end);
js_Goal = sol_Goal(1, 2:end);

% ///////////////  Get the joint trajectories //////////////////
t0 = 0; tf = 3; ddth = 30*pi/180; tm_cycle = 0.01;
for i = 1:length(js_Start)
    th_0 = js_Start(i); th_f = js_Goal(i);
    figure(i);
    [th_profile, dth_profile, ddth_profile, time_profile] = dobotM1_gentraj(t0, tf, th_0, th_f, ddth, tm_cycle);
end



