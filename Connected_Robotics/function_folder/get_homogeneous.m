function [H] = get_homogeneous(px, py, pz, rz, ry, rx)
    R = euler2rotm(rz, ry, rx);
    H = [R, [px; py; pz]; zeros(1, 3), 1];
end