clc;
clear;
close all;

% Position, Velocity, Acceleration trajectory using singe s pline at
% position level.

% //////////// Inputs ///////////////////////////
t0 = 0; tf = 3; th_0 = 15; th_f = 70; ddth = 40; tm_cycle = 0.01;

% Compute tb
tb = (tf/2) - sqrt((ddth*tf)^2 - 4*ddth*(th_f - th_0))/(2*ddth);

% Generate vector between t0 and tb
subplot(3, 1, 1);
tb_vec = t0:tm_cycle:tb;
th_vec = th_0 + 0.5*ddth*tb_vec.^2;
ylabel("${\theta}$ [degree]", 'interpreter','latex');
title("Profile for ${\theta}$, ${\dot{\theta}}$, ${\ddot{\theta}}$", 'interpreter','latex');
grid on;
hold on;

% Generate vector between t0+tb and tf-tb
tb_vec2 = tb:tm_cycle:tf-tb;
th_vec2 = th_0 + ddth*tb*(tb_vec2-0.5*tb);

% Generate vector between tf-tb and tf
tb_vec3 = tf-tb:tm_cycle:tf;
th_vec3 = th_f - 0.5*ddth*(tf-tb_vec3).^2;
plot([tb_vec, tb_vec2, tb_vec3], [th_vec, th_vec2, th_vec3]);

% \\\\\\\\\\\ Velocity Profile \\\\\\\\\\\\\\\\\\\\
subplot(3, 1, 2);
% Segment 1
dth_vec = ddth*tb_vec;
ylabel("${\dot{\theta}}$ [degree/s]", 'interpreter','latex');
grid on;
hold on;

% Segment 2
dth_vec2 = ddth*tb*ones(1, length(tb_vec2));

% Segment 3
dth_vec3 = ddth*(tf - tb_vec3);
plot([tb_vec, tb_vec2, tb_vec3], [dth_vec, dth_vec2, dth_vec3])

% \\\\\\\\\\\ Acceleration Profile \\\\\\\\\\\\\\\\\\\\
subplot(3, 1, 3);
% Segment 1
ddth_vec = ddth*ones(1, length(tb_vec));
hold on;
xlabel("time [s]"); ylabel("${\ddot{\theta}}$ ${[degree/s^2]}$", 'interpreter','latex'); 

% Segment 2
ddth_vec2 = zeros(1, length(tb_vec2));

% Segment 3
ddth_vec3 = -ddth*ones(1, length(tb_vec3));
plot([tb_vec, tb_vec2, tb_vec3], [ddth_vec, ddth_vec2, ddth_vec3])
grid on;
