clc;
clear;
close all;

% Generate Position, velocity and Acceleration profiles
th_0 = 0; th_f = 1.0; dth_0 = 0; dth_f = 0; ddth_0 = 0; ddth_f = 0;
tf = 6;

b_vec = [th_0; th_f; dth_0; dth_f; ddth_0; ddth_f];
A = zeros(6, 6);
A(1, 1) = 1; A(3, 2) = 1; A(5, 3) = 1;
A(2, :) = [1, tf, tf^2, tf^3, tf^4, tf^5];
A(4, :) = [0, 1, 2*tf, 3*tf^2, 4*tf^3, 5*tf^4];
A(6, :) = [0, 0, 2, 6*tf, 12*tf^2, 20*tf^3];
coeff = A\b_vec;

t_vec = 0:0.01:tf;
p_vec = zeros(1, length(t_vec));
v_vec = zeros(1, length(t_vec));
accl_vec = zeros(1, length(t_vec));
jerk_vec = zeros(1, length(t_vec));
count = 1;
for t = t_vec
    p_vec(count) = [1, t, t^2, t^3, t^4, t^5]*coeff;
    v_vec(count) = [0, 1, 2*t, 3*t^2, 4*t^3, 5*t^4]*coeff;
    accl_vec(count) = [0, 0, 2, 6*t, 12*t^2, 20*t^3]*coeff;
    count = count + 1;
end
subplot(3, 1, 1); plot(t_vec, p_vec); ylabel("${\theta}$", 'interpreter','latex'); 
grid on;
subplot(3, 1, 2); plot(t_vec, v_vec); ylabel("${\dot{\theta}}$", 'interpreter','latex'); 
grid on;
subplot(3, 1, 3); plot(t_vec, accl_vec); xlabel("time [s]"); ylabel("${\ddot{\theta}}$", 'interpreter','latex'); 
grid on;
