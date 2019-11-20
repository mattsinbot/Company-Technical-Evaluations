function [sol_checked] = dobotM1_ik2(ee_pose)
    %///////////////////////////////////////////////////////
    %/////////// Solve Inverse Kinematics //////////////////
    %///////////////////////////////////////////////////////

    % Robot link parameters
    l2 = 0.150; l3 = 0.200; l4 = 0.200;
    d2 = 0.250; d3 = -0.050; d4 = -0.050;
    
    px = ee_pose(1, 4); py = ee_pose(2, 4); pz = ee_pose(3, 4); r11 = ee_pose(1, 1);
    
    % Compute theta3
    c3 = ((px - l2)^2 + py^2 - l3^2 - l4^2)/(2*l3*l4);
    if c3 >= 1 && c3 <= -1
        sol = NaN;
        return;
    end
    th31 = acos(c3);
    th32 = -th31;
    
    % Compute theta2
    beta = atan2(py, px - l2);
    cos_psi = ((px - l2)^2 + (py)^2 + l3^2 -l4^2)/(2*l3*sqrt((px - l2)^2 + (py)^2));
    
    if cos_psi >= 1 && cos_psi <= -1
        sol = NaN;
        return;
    end
    
    psi = acos(cos_psi);
    if th31 > 0
        th21 = beta - psi;
        th22 = beta + psi;
    else
        th21 = beta + psi;
        th22 = beta - psi;
    end
    
    % Compute theta4
    if th31 > 0
        th41 = acos(r11) - th21 - th31;
        th42 = -acos(r11) - th22 - th32;
    else
        th41 = -acos(r11) - th21 - th31;
        th42 = acos(r11) - th22 - th32;
    end
    
    % Compute d1
    d1 = pz - (d2 + d3 + d4);
    
    % Get all the solution in an array
    sol = [d1, th21, th31, th41; d1, th22, th32, th42];
    
    % Check joint limit avoidance
    sol_checked = check_joint_limit(sol);
end

function [js_checked] = check_joint_limit(js)
    js_checked = [];
    for i = 1:2
        one_sol = js(i, :);
        if one_sol(1) <= 0 && one_sol(1) >= -0.250
            if one_sol(2) >= -pi/2 && one_sol(2) <= pi/2
                if one_sol(3) >= -2.4435 && one_sol(3) <= 2.4435
                    js_checked = [js_checked; one_sol];
                end
            end
        end
    end
end