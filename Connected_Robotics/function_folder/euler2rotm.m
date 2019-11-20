function [R] = euler2rotm(rz, ry, rx)
    % Input: Euler angles in ZYX convention
    % Output: Rotation matrix
    Rx = [1, 0, 0; 0, cos(rx), -sin(rx); 0, sin(rx), cos(rx)];
    Ry = [cos(ry), 0, sin(ry); 0, 1, 0; -sin(ry), 0, cos(ry)];
    Rz = [cos(rz), -sin(rz), 0; sin(rz), cos(rz), 0; 0, 0, 1];
    R = Rz*Ry*Rx;
end