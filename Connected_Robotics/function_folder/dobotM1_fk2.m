function[T] = dobotM1_fk2(d1, th2, th3, th4)
    %/////////////////////////////////////////////////////
    %/////////////// Forward kinematics //////////////////
    %/////////////////////////////////////////////////////
    l2 = 0.150; l3 = 0.200; l4 = 0.200;
    d2 = 0.250; d3 = -0.050; d4 = -0.050;

    a_vec = [0, l2, l3, l4];
    alp_vec = [0, 0, 0, 0];
    d_vec = [d1, d2, d3, d4];
    th_vec = [0, th2, th3, th4];
    
    T = eye(4, 4);
    for i = 1:4
        T = T * local_transforms(a_vec(i), alp_vec(i), d_vec(i), th_vec(i));
    end
    fprintf("Tool Transformation to Base frame\n");
    disp(T);
end

%//////////////////////////////////////////////////////////////
%//////////// Function to compute local transformation ////////
%//////////////////////////////////////////////////////////////
function [mat] = local_transforms(a, alpha, d, theta)
    mat = [cos(theta), -sin(theta), 0, a;
        sin(theta)*cos(alpha), cos(theta)*cos(alpha), -sin(alpha), -sin(alpha)*d;
        sin(theta)*sin(alpha), cos(theta)*sin(alpha), cos(alpha), cos(alpha)*d;
        0, 0 , 0, 1];
end