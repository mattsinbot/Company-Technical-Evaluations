clc;
clear;
close all;

addpath("..\function_folder");

% Desccription: Computes joint trajectories, to draw a square, given four
% vertices, using tashspace scheme.

% /////////////// Input ////////////////////////
pen_height = 0.050;  % Pen height
tm_per_seg = 1;      % Allowable time to draw one side of the square

% Tool poses of the four corner points
rz = 0; ry = 0; rx = 0;
px1 = 0.400; py1 = 0; pz1 = pen_height;
px2 = 0.500; py2 = 0; pz2 = pen_height;
px3 = 0.500; py3 = 0.100; pz3 = pen_height;
px4 = 0.400; py4 = 0.100; pz4 = pen_height;

T1 = get_homogeneous(px1, py1, pz1, rz, ry, rx);
T2 = get_homogeneous(px2, py2, pz2, rz, ry, rx);
T3 = get_homogeneous(px3, py3, pz3, rz, ry, rx);
T4 = get_homogeneous(px4, py4, pz4, rz, ry, rx);

% R = eye(3, 3);
% T1 = [R, [0.400; 0; pen_height]; zeros(1, 3), 1];
% T2 = [R, [0.500; 0; pen_height]; zeros(1, 3), 1];
% T3 = [R, [0.500; 0.100; pen_height]; zeros(1, 3), 1];
% T4 = [R, [0.400; 0.100; pen_height]; zeros(1, 3), 1];

figure(1);
sgtitle("Segment1: Profile of ${\theta_2, \theta_3, \theta_4}$", "interpreter", "latex");
sol_seg1 = straight_line_taskspace_trajectory(T1, T2, tm_per_seg);

figure(2);
sgtitle("Segment2: Profile of ${\theta_2, \theta_3, \theta_4}$", "interpreter", "latex");
sol_seg2 = straight_line_taskspace_trajectory(T2, T3, tm_per_seg);

figure(3);
sgtitle("Segment3: Profile of ${\theta_2, \theta_3, \theta_4}$", "interpreter", "latex");
sol_seg3 = straight_line_taskspace_trajectory(T3, T4, tm_per_seg);

figure(4);
sgtitle("Segment4: Profile of ${\theta_2, \theta_3, \theta_4}$", "interpreter", "latex");
sol_seg4 = straight_line_taskspace_trajectory(T4, T1, tm_per_seg);

function[sol_vec] = straight_line_taskspace_trajectory(Tee_Start, Tee_Goal, tf)
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
end