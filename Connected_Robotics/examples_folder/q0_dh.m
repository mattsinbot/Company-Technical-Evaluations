clc;
close all;
clear all;

% Define the link and offsets lengths
l2 = 0.150; l3 = 0.200; l4 = 0.200;
d2 = 0.250; d3 = -0.050; d4 = -0.050;

% Define the DH parameters of the dobotM1
a_vec = [0, l2, l3, l4];
alp_vec = [0, 0, 0, 0];
d_vec = [d1, d2, d3, d4];
th_vec = [0, th2, th3, th4];