clc;
clear;
close all;

addpath("..\function_folder");

% Description: Given end-effector poses at the start and goal, compute
% joint trajectories using taskspace scheme.

% Straight line motion between start and goal in taskspace
% //////////////// Input /////////////////////
rz = 0.3; ry = 0.0; rx = 0.0;                  % End-effector orientation
px1 = 0.5450; py1 = 0.0597; pz1 = -0.0500;     % Start end-effector position
px2 = 0.1230; py2 = 0.3399; pz2 = -0.0500;     % Goal end-effector position
tf = 3;                                        % Time to reach goal

Tee_Start = get_homogeneous(px1, py1, pz1, rx, ry, rx);
Tee_Goal = get_homogeneous(px2, py2, pz2, rx, ry, rx);

% Tee_Start = [0.9553, -0.2955, 0, 0.5450;
%              0.2955, 0.9553, 0, 0.0597;
%              0, 0, 1.0000, -0.0500;
%              0, 0, 0, 1.0000];
%          
% Tee_Goal = [Tee_Start(1:3, 1:3), [0.1230; 0.3399; -0.0500]; 0, 0, 0, 1];


% /////////////// Get taskspace points /////////////////
dir_vec = Tee_Goal(1:2, 4) - Tee_Start(1:2, 4);
dist = norm(dir_vec);
dir_vec = dir_vec/dist;
discrete_pts = 0:0.001:dist;
ee_poses = zeros(4, 4, length(discrete_pts));

sol_vec = [];
for i = 1:length(discrete_pts)
    ee_poses(:, :, i) = [Tee_Start(1:3, 1:3), [Tee_Start(1:2, 4) + discrete_pts(i)*dir_vec; Tee_Start(3, 4)]; 0, 0, 0, 1];
    sol = dobotM1_ik2(ee_poses(:, :, i));
    sol_vec(i, :) = sol(1, :);
    disp(sol_vec(i, :));
end

% Plot the profiles of the joint positions
time_vec = linspace(0, tf, size(sol_vec, 1));
figure(1);
sgtitle("Profile of ${\theta_2, \theta_3, \theta_4}$", "interpreter", "latex");
subplot(3, 1, 1);
plot(time_vec, sol_vec(:, 2)); grid on;
ylabel("${\theta_2}$ [rad]", 'interpreter', 'latex');
subplot(3, 1, 2);
plot(time_vec, sol_vec(:, 3)); grid on;
ylabel("${\theta_3}$ [rad]", "interpreter", "latex");
subplot(3, 1, 3);
plot(time_vec, sol_vec(:, 4)); grid on;
xlabel("time [s]");
ylabel("${\theta_4}$ [rad]", "interpreter", "latex");
