clc
clear
close all;
%% Cacluate the point
syms t
T = 5;                                                                      % flapping period, unit (s)
dt = 0.08;
% modify coefficient
% M_coff = [0, dt*(2.8-0), dt*(2.8-0), dt*3.2, dt*3.2];                     % [0.18+0.05*(T-1.2), 0.3+0.025*(T-1.2)];
M_coff = [0, dt*(3), dt*(3), dt*(3.2), dt*(3.2), 0, dt*(3), dt*(3.2)];

w_rad = 50/T *360/60/180*pi;                                               % unit (rad/s)
ta_0 = 0/180*pi;                                                           % 需要根据电机的标定值去算

outer_phase = -0.2*T;                                                      % ratio of T                                                     % ratio of T
outer_amp = 100;                                                            % unit (°)
outer_baseoffset = -0; 
twist_phase = -0.5 *T; 
twist_amp = 260 /180*pi;                                                   % unit (rad)
twist_baseoffset = (- 0.5) * twist_amp;                                    % ratio of A

tt_ = linspace(0, T, 21);                                                  % unit (s)

Crak_motor_pos = ta_0 + w_rad * t;                                         % unit (rad)
Crak_motor_pp = double(subs(Crak_motor_pos, t, tt_));

inner_P = 0.07193 + 0.4718*cos(6.283*t/T) - 0.1751*sin(6.283*t/T) ...
    - 0.007227*cos(2*6.283*t/T) + 0.09418*sin(2*6.283*t/T) ... 
    - 0.02573*cos(3*6.283*t/T) - 0.007249*sin(3*6.283*t/T) ...
    + 0.004037*cos(4*6.283*t/T) - 0.007424*sin(4*6.283*t/T);
inner_V = diff(inner_P, t);
inner_Pp = double(subs(inner_P, t, tt_))/pi*180;
inner_Vp = double(subs(inner_V, t, tt_))/pi*180;

outer_P = 1*(outer_amp*0.5* cos(6.283*(t+outer_phase)/T) + outer_amp*outer_baseoffset) /180*pi;
outer_V = diff(outer_P, t);
outer_Pp = double(subs(outer_P, t, tt_))/pi*180;
outer_Vp = double(subs(outer_V, t, tt_))/pi*180;
twist_P = twist_amp/2 * cos(6.283*(t+twist_phase)/T) + twist_baseoffset;
% twist_P = -0/180*pi;
twist_V = diff(twist_P, t);
twist_Pp = double(subs(twist_P, t, tt_))/pi*180;
twist_Vp = double(subs(twist_V, t, tt_))/pi*180;

% figure(1);
% plot(tt_, inner_V, 'k-');
% hold on
% plot(tt_, outer_V, 'k--');
% hold off
figure(10);
plot(tt_, inner_Pp, 'k-');

hold on
plot(tt_, outer_Pp, 'k--');
plot(tt_, twist_Pp, 'k*-');
yyaxis right;
plot(tt_, Crak_motor_pp /pi*180, 'r*-');
hold off
% Present_pos = 20 / 180*pi;
% figure(3);
% plot(inner_motor_pos, inner_P);
 
%% Control tabel
lib_name = '';

if strcmp(computer, 'PCWIN')
  lib_name = 'dxl_x86_c';
elseif strcmp(computer, 'PCWIN64')
  lib_name = 'dxl_x64_c';
elseif strcmp(computer, 'GLNX86')
  lib_name = 'libdxl_x86_c';
elseif strcmp(computer, 'GLNXA64')
  lib_name = 'libdxl_x64_c';
elseif strcmp(computer, 'MACI64')
  lib_name = 'libdxl_mac_c';
end

% Load Libraries
if ~libisloaded(lib_name)
    [notfound, warnings] = loadlibrary(lib_name, 'dynamixel_sdk.h', 'addheader', 'port_handler.h', 'addheader', 'packet_handler.h', ...
        'addheader', 'group_sync_write.h', 'addheader', 'group_sync_read.h', 'addheader', 'group_bulk_read.h', 'addheader', 'group_bulk_write.h');
end

% Control table address
ADDR_PRO_TORQUE_ENABLE       = 64;        % Control table address is different in Dynamixel model
BAUD_RATE                    = 8;         % Set Baud Rate, often 57600bps

ADDR_PRO_GOAL_VELOCITY       = 104;
ADDR_PRO_PRESENT_VELOCITY    = 128;
ADDR_PRO_GOAL_POSITION       = 116;
ADDR_PRO_PRESENT_POSITION    = 132;
ADDR_PRO_PRESENT_CURRENT     = 126;

PRO_ACC                      = 108;
PRO_VEL                      = 112;

DRIVE_MODE                   = 10;
OPERATING_MODE               = 11;

% Data Byte Length
LEN_PRO_GOAL_POSITION       = 4;
LEN_PRO_GOAL_VELOCITY       = 4;
LEN_PRO_PRESENT_POSITION    = 4;
LEN_PRO_PRESENT_VELOCITY    = 4;

% Protocol version
PROTOCOL_VERSION            = 2.0;         % See which protocol version is used in the Dynamixel

% Default setting
DXL_ID                      = [6, 7, 8];   % Dynamixel#ID: 1-5, ID=1:inner, ID=2,3:outer_flap ID=4,5:outer_twist
BAUDRATE                    = 57600;
DEVICENAME                  = 'COM5';      % Check which port is being used on your controller

%% Parameter
TORQUE_ENABLE               = 1;           % Value for enabling the torque
TORQUE_DISABLE              = 0;           % Value for disabling the torque
V_MODE                      = 1;           % value for velocity control  
P_MODE                      = 3;           % value for position control  
EP_MODE                     = 4;

ESC_CHARACTER               = 'e';         % Key for escaping loop

COMM_SUCCESS                = 0;           % Communication Success result value
COMM_TX_FAIL                = -1001;       % Communication Tx Failed
dxl_addparam_result = false;               % AddParam result
dxl_getdata_result = false;                % GetParam result
dxl_comm_result = COMM_TX_FAIL;            % Communication result

Goal_velocity              = zeros(1, 8);
Goal_position              = zeros(1, 8);
Present_velocity           = zeros(1, 8); 
Present_position           = zeros(1, 8);
Present_current            = zeros(1, 8); 

Position_0                 = [1750, 2048, 2048, 2048, 2048, 2700, 2048, -1450];               % 舵机1 的初始值需要修改
Limited_position           = [5000, 1593, 2503, 2503, 1593, 5000, 2503, -1950; ...
                              5000, 2503, 1593, 1593, 2503, 5000, 1593, -950];
%                           3645 1650
% DXL_v_unit                 = [ 68.7, 45.8, 45.8, 111.01, 111.01; ...
%                                 300,  200,  200,    485,    485];          % row-1: rpm_max; row-2: write_unit
DXL_v_unit                 = 0.229;                                        % rpm / DXL_unit
DXL_c_unit                 = 2.69;                                         % unit (mA)   
Drive_ratio                = [1.5, 1.5, 1.5, 1, 1, 36/54, 23/22, 1];
Drive_direction            = [1, 1, -1, -1, 1, 1, -1, 1];
Max_vel                    = [300, 200, 200, 485, 485, 300, 200, 485];
profile_time               = [0, 1, 1, 1.2, 1.2, 0, 1, 1.2]*dt * 1000;                                                % ms
dxl_error = 0;                             % Dynamixel error
%%  Initialization
% Initialize PortHandler Structs
% Set the port path
% Get methods and members of PortHandlerLinux or PortHandlerWindows 
port_num = portHandler(DEVICENAME);

% Initialize PacketHandler Structs
packetHandler();

% Open port
if (openPort(port_num))
    fprintf('Succeeded to open the port!\n');
else
    unloadlibrary(lib_name);
    fprintf('Failed to open the port!\n');
    input('Press any key to terminate...\n');
    return;
end

% Set port baudrate
if (setBaudRate(port_num, BAUDRATE))
    fprintf('Succeeded to change the baudrate!\n');
else
    unloadlibrary(lib_name);
    fprintf('Failed to change the baudrate!\n');
    input('Press any key to terminate...\n');
    return;
end

for ID_i = DXL_ID
    % Try reboot Dynamixel LED will flicker while it reboots
    reboot(port_num, PROTOCOL_VERSION, ID_i);
    if getLastTxRxResult(port_num, PROTOCOL_VERSION) ~= COMM_SUCCESS
        printTxRxResult(PROTOCOL_VERSION, getLastTxRxResult(port_num, PROTOCOL_VERSION));
    elseif getLastRxPacketError(port_num, PROTOCOL_VERSION) ~= 0
        printRxPacketError(PROTOCOL_VERSION, getLastRxPacketError(port_num, PROTOCOL_VERSION));
    end
    fprintf('[ID:%03d] reboot Succeeded\n', ID_i);
end
pause(6);
fprintf('waiting for 6s to reboot\n');

% % Initialize Groupsyncwrite Structs
% groupwrite_vel = groupSyncWrite(port_num, PROTOCOL_VERSION, ADDR_PRO_GOAL_VELOCITY, LEN_PRO_GOAL_VELOCITY);
% groupwrite_pos = groupSyncWrite(port_num, PROTOCOL_VERSION, ADDR_PRO_GOAL_POSITION, LEN_PRO_GOAL_POSITION);
% Initialize groupBulkWrite Struct
bulkwrite_vel_pos = groupBulkWrite(port_num, PROTOCOL_VERSION);

% Initialize Groupsyncread Structs for Present Position, Velocity 
groupread_vel = groupSyncRead(port_num, PROTOCOL_VERSION, ADDR_PRO_PRESENT_VELOCITY, LEN_PRO_PRESENT_VELOCITY);
groupread_pos = groupSyncRead(port_num, PROTOCOL_VERSION, ADDR_PRO_PRESENT_POSITION, LEN_PRO_PRESENT_POSITION);
groupread_cur = groupSyncRead(port_num, PROTOCOL_VERSION, ADDR_PRO_PRESENT_CURRENT, 2);

%Add parameter storage
for ID_i = DXL_ID
    %Set operating mode
    if ID_i == 1 || ID_i == 6
        write1ByteTxRx(port_num, PROTOCOL_VERSION, ID_i, OPERATING_MODE, V_MODE);
    elseif ID_i == 2 || ID_i == 3 || ID_i == 7
        write1ByteTxRx(port_num, PROTOCOL_VERSION, ID_i, OPERATING_MODE, P_MODE);
    else
        write1ByteTxRx(port_num, PROTOCOL_VERSION, ID_i, OPERATING_MODE, EP_MODE);
    end
    %Set driving mode
     write1ByteTxRx(port_num, PROTOCOL_VERSION, ID_i, DRIVE_MODE, 4);
     
    % Enable Dynamixel# Torque
    write1ByteTxRx(port_num, PROTOCOL_VERSION, ID_i, ADDR_PRO_TORQUE_ENABLE, TORQUE_ENABLE);
    
    % Add parameter storage for Dynamixel# present velocity/position/current value
    groupSyncReadAddParam(groupread_vel, ID_i);
    groupSyncReadAddParam(groupread_pos, ID_i);
    groupSyncReadAddParam(groupread_cur, ID_i);
    
    write4ByteTxRx(port_num, PROTOCOL_VERSION, ID_i, PRO_VEL, profile_time(ID_i));
end
fprintf('Changing [ID_1 or ID_6] to velocity mode successfully, changing [ID_2 or 3 or 4 or 5 or 7 or 8] to position mode successfully!\n');

%% Using position mode to reset the position of Dynamixel to the first point separately
Goal_position([1, 6]) = Position_0([1, 6]);                                          % !!!! 需要修改
Goal_position([2, 3, 7]) = Position_0([2, 3, 7]) + Drive_direction([2, 3, 7]) * double(subs(outer_P, t, 0)) ./ Drive_ratio([2, 3, 7]) /pi*2048;
Goal_position([4, 5, 8]) = Position_0([4, 5, 8]) + Drive_direction([4, 5, 8]) * double(subs(twist_P, t, 0)) ./ Drive_ratio([4, 5, 8]) /pi*2048;

% Syncread present position
groupSyncReadTxRxPacket(groupread_pos);
if getLastTxRxResult(port_num, PROTOCOL_VERSION) ~= COMM_SUCCESS
    printTxRxResult(PROTOCOL_VERSION, getLastTxRxResult(port_num, PROTOCOL_VERSION));
end

for DXL_i = DXL_ID
    Present_position(DXL_i) = groupSyncReadGetData(groupread_pos, DXL_i, ADDR_PRO_PRESENT_POSITION, LEN_PRO_PRESENT_POSITION);
    Present_position(DXL_i) = typecast(uint32(Present_position(DXL_i)),'int32');
    if DXL_i == 1 || DXL_i == 6
        syb = sign(typecast(uint32(Goal_position(DXL_i)),'int32') - Present_position(DXL_i)) * 60;
        % Add parameter storage for Dynamixel#1&6 goal velocity
        dxl_addparam_result = groupBulkWriteAddParam(bulkwrite_vel_pos, DXL_i, ADDR_PRO_GOAL_VELOCITY, LEN_PRO_GOAL_VELOCITY, ...
            typecast(int32(syb), 'uint32'), LEN_PRO_GOAL_VELOCITY);
        if dxl_addparam_result ~= true
            fprintf(stderr, '[ID:%03d] groupBulkWrite addparam failed', DXL_i);
            return;
        end
        
    else
        % Add parameter storage for Dynamixel#[2 3 4 5 7 8] goal position
        dxl_addparam_result = groupBulkWriteAddParam(bulkwrite_vel_pos, DXL_i, ADDR_PRO_GOAL_POSITION, LEN_PRO_GOAL_POSITION, ...
            typecast(int32(Goal_position(DXL_i)), 'uint32'), LEN_PRO_GOAL_POSITION);
        if dxl_addparam_result ~= true
            fprintf(stderr, '[ID:%03d] groupBulkWrite addparam failed', DXL_i);
            return;
        end
        
    end

end

% Bulkwrite goal position and velocity
groupBulkWriteTxPacket(bulkwrite_vel_pos);
if getLastTxRxResult(port_num, PROTOCOL_VERSION) ~= COMM_SUCCESS
    printTxRxResult(PROTOCOL_VERSION, getLastTxRxResult(port_num, PROTOCOL_VERSION));
end
% Clear bulkwrite parameter storage
groupBulkWriteClearParam(bulkwrite_vel_pos);

% Judgment value(0: not reach, 1 reached) 
Initialize_judge = zeros(1, 8);

while 1
    % Syncread present position
    groupSyncReadTxRxPacket(groupread_pos);
%     if getLastTxRxResult(port_num, PROTOCOL_VERSION) ~= COMM_SUCCESS
%         printTxRxResult(PROTOCOL_VERSION, getLastTxRxResult(port_num, PROTOCOL_VERSION));
%     end
    % Syncread present velocity
    groupSyncReadTxRxPacket(groupread_vel);
%     if getLastTxRxResult(port_num, PROTOCOL_VERSION) ~= COMM_SUCCESS
%         printTxRxResult(PROTOCOL_VERSION, getLastTxRxResult(port_num, PROTOCOL_VERSION));
%     end
    
    for DXL_i = DXL_ID
        % Check if groupsyncread position of Dynamixel is available
        dxl_getdata_result = groupSyncReadIsAvailable(groupread_pos, DXL_i, ADDR_PRO_PRESENT_POSITION, LEN_PRO_PRESENT_POSITION);
%         if dxl_getdata_result ~= true
%             fprintf('[ID:%03d] groupSyncRead getdata failed, initializing position', DXL_i);
%             return;
%         end
        Present_position(DXL_i) = typecast(uint32(...
            groupSyncReadGetData(groupread_pos, DXL_i, ADDR_PRO_PRESENT_POSITION, LEN_PRO_PRESENT_POSITION)),'int32');
        
        % Check if groupsyncread velocity of Dynamixel is available
        dxl_getdata_result = groupSyncReadIsAvailable(groupread_vel, DXL_i, ADDR_PRO_PRESENT_VELOCITY, LEN_PRO_PRESENT_VELOCITY);
%         if dxl_getdata_result ~= true
%             fprintf('[ID:%03d] groupSyncRead getdata failed, initializing velocity', DXL_i);
%             return;
%         end
        Present_velocity(DXL_i) = typecast(uint32(...
            groupSyncReadGetData(groupread_vel, DXL_i, ADDR_PRO_PRESENT_VELOCITY, LEN_PRO_PRESENT_VELOCITY)),'int32');
        
        % Determine if the position is reached
        if  DXL_i == 1 || DXL_i == 6
            if  abs(Present_position(DXL_i) - Goal_position(DXL_i)) <= 50 || (Present_position(DXL_i) - Goal_position(DXL_i))*syb > 0
                Initialize_judge(DXL_i) = 1;
                write4ByteTxRx(port_num, PROTOCOL_VERSION, DXL_i, ADDR_PRO_GOAL_VELOCITY, typecast(int32(0), 'uint32'));
            end
        elseif DXL_i == 2 || DXL_i == 3 || DXL_i == 7
            if  abs(Present_position(DXL_i) - Goal_position(DXL_i)) <= 100
                Initialize_judge(DXL_i) = 1;
            end
        else
            if  abs(Present_position(DXL_i) - Goal_position(DXL_i)) <= 800
                Initialize_judge(DXL_i) = 1;
            end
        end
        fprintf('[ID:%03d] GoalPos:%03d  PresPos:%03d\n', ...
            DXL_i, int32(Goal_position(DXL_i)), Present_position(DXL_i));
    end
    
    if all(Initialize_judge(DXL_ID))
        break;
    end
end

fprintf('reset to the first point successfully!\n');
fprintf('press any key to continue!\n');
pause;

%% Cycle motion
ppv_ = zeros(8 +1, 500, 2);
k = 0;
c_num = 1;
error_v = zeros(8, 500);
error_p = zeros(8, 500);
curr_store = zeros(8, 500);
Time_ob = cell(1, 500);

% write constant velocity to ID=1
Goal_velocity(1) = 60/T /Drive_ratio(1)/DXL_v_unit;
Goal_velocity(6) = 60/T /Drive_ratio(6)/DXL_v_unit;
if ismember(1, DXL_ID)
    write4ByteTxRx(port_num, PROTOCOL_VERSION, 1, ADDR_PRO_GOAL_VELOCITY, typecast(int32(Goal_velocity(1)), 'uint32'));
else
    write4ByteTxRx(port_num, PROTOCOL_VERSION, 6, ADDR_PRO_GOAL_VELOCITY, typecast(int32(Goal_velocity(6)), 'uint32'));
end

t1 = clock;
while 1
    k = k+1;
    t2 = clock;
    
    % Syncread present position
    groupSyncReadTxRxPacket(groupread_pos);
%     if getLastTxRxResult(port_num, PROTOCOL_VERSION) ~= COMM_SUCCESS
%         printTxRxResult(PROTOCOL_VERSION, getLastTxRxResult(port_num, PROTOCOL_VERSION));
%     end
    % Syncread present velocity
    groupSyncReadTxRxPacket(groupread_vel);
%     if getLastTxRxResult(port_num, PROTOCOL_VERSION) ~= COMM_SUCCESS
%         printTxRxResult(PROTOCOL_VERSION, getLastTxRxResult(port_num, PROTOCOL_VERSION));
%     end
    % Syncread present current
    groupSyncReadTxRxPacket(groupread_cur);
%     if getLastTxRxResult(port_num, PROTOCOL_VERSION) ~= COMM_SUCCESS
%         printTxRxResult(PROTOCOL_VERSION, getLastTxRxResult(port_num, PROTOCOL_VERSION));
%     end
    
    pt_ = etime(t2, t1);
    ppv_(1, k, :) = pt_;
    Time_ob{k} = t2;
    
    for DXL_i = DXL_ID
        Present_position(DXL_i) = groupSyncReadGetData(groupread_pos, DXL_i, ADDR_PRO_PRESENT_POSITION, LEN_PRO_PRESENT_POSITION);
        Present_position(DXL_i) = typecast(uint32(Present_position(DXL_i)),'int32');
        Present_velocity(DXL_i) = groupSyncReadGetData(groupread_vel, DXL_i, ADDR_PRO_PRESENT_VELOCITY, LEN_PRO_PRESENT_VELOCITY);
        Present_velocity(DXL_i) = typecast(uint32(Present_velocity(DXL_i)),'int32');
        Present_current(DXL_i) = groupSyncReadGetData(groupread_cur, DXL_i, ADDR_PRO_PRESENT_CURRENT, 2);
        Present_current(DXL_i) = typecast(uint16(Present_current(DXL_i)), 'int16')*DXL_c_unit;
        % store values
        ppv_(DXL_i+1, k, 1) = Present_position(DXL_i);
        ppv_(DXL_i+1, k, 2) = Present_velocity(DXL_i);
        curr_store(DXL_i, k) = Present_current(DXL_i);
    end
    
    % Calculating the time of ID=1||6 at current position
    if ismember(1, DXL_ID)
       t_num = (Present_position(1)-Position_0(1)) /2048*180 / (60/T * 6) * Drive_ratio(1);
    else
        t_num = (Present_position(6)-Position_0(6)) /2048*180 / (60/T * 6) * Drive_ratio(6);
    end
    
    % goal velocity and position for other DXL
    Goal_position(1) = double(subs(Crak_motor_pos, t, t_num))/pi*2048;
    Goal_position(6) = double(subs(Crak_motor_pos, t, t_num))/pi*2048;
    Goal_position(2) = Position_0(2) + Drive_direction(2) .* double(subs(outer_P, t, t_num + M_coff(2))) ./Drive_ratio(2) /pi*2048;
    Goal_position(3) = Position_0(3) + Drive_direction(3) .* double(subs(outer_P, t, t_num + M_coff(3))) ./Drive_ratio(3) /pi*2048;
    Goal_position(7) = Position_0(7) + Drive_direction(7) .* double(subs(outer_P, t, t_num + M_coff(7))) ./Drive_ratio(7) /pi*2048;
    Goal_position(4) = Position_0(4) + Drive_direction(4) .* double(subs(twist_P, t, t_num + M_coff(4))) ./Drive_ratio(4) /pi*2048;
    Goal_position(5) = Position_0(5) + Drive_direction(5) .* double(subs(twist_P, t, t_num + M_coff(5))) ./Drive_ratio(5) /pi*2048;
    Goal_position(8) = Position_0(8) + Drive_direction(8) .* double(subs(twist_P, t, t_num + M_coff(8))) ./Drive_ratio(8) /pi*2048;
    Goal_velocity(2) = Drive_direction(2) * double(subs(outer_V, t, t_num + M_coff(2))) /Drive_ratio(2) ;
    Goal_velocity(3) = Drive_direction(3) * double(subs(outer_V, t, t_num + M_coff(3))) /Drive_ratio(3) ;
    Goal_velocity(7) = Drive_direction(7) * double(subs(outer_V, t, t_num + M_coff(7))) /Drive_ratio(7) ;
    Goal_velocity(4) = Drive_direction(4) * double(subs(twist_V, t, t_num + M_coff(4))) /Drive_ratio(4) ;
    Goal_velocity(5) = Drive_direction(5) * double(subs(twist_V, t, t_num + M_coff(5))) /Drive_ratio(5) ;
    Goal_velocity(8) = Drive_direction(8) * double(subs(outer_V, t, t_num + M_coff(8))) /Drive_ratio(8) ;
    
    error_v(:, k) = ((Present_velocity - Goal_velocity) *pi/30)';
    der_v = diff(error_v, 1, 2);
    error_p(:, k) = ((Present_position - Goal_position)/2048*pi)';
    der_p = diff(error_p, 1, 2);
    
    % modify vel
    if ismember(1, DXL_ID)
        DXL1_vel = 1*Goal_velocity(1) -0.08*error_v(1, k) - 1*0.08*sum(error_v(1, :), 2);
        % Add parameter storage for Dynamixel#1 goal velocity
        dxl_addparam_result = groupBulkWriteAddParam(bulkwrite_vel_pos, 1, ADDR_PRO_GOAL_VELOCITY, LEN_PRO_GOAL_VELOCITY, ...
            typecast(int32(DXL1_vel), 'uint32'), LEN_PRO_GOAL_VELOCITY);
        if dxl_addparam_result ~= true
            fprintf(stderr, '[ID:%03d] groupBulkWrite addparam failed', 1);
            return;
        end
    else
        DXL6_vel = 1*Goal_velocity(6) -0.08*error_v(6, k) - 1*0.08*sum(error_v(6, :), 2);
        % Add parameter storage for Dynamixel#6 goal velocity
        dxl_addparam_result = groupBulkWriteAddParam(bulkwrite_vel_pos, 6, ADDR_PRO_GOAL_VELOCITY, LEN_PRO_GOAL_VELOCITY, ...
            typecast(int32(DXL6_vel), 'uint32'), LEN_PRO_GOAL_VELOCITY);
        if dxl_addparam_result ~= true
            fprintf(stderr, '[ID:%03d] groupBulkWrite addparam failed', 6);
            return;
        end
    end
    
    for DXL_i = DXL_ID(DXL_ID ~= 1 & DXL_ID ~= 6)
        % Add parameter storage for Dynamixel# goal position
        dxl_addparam_result = groupBulkWriteAddParam(bulkwrite_vel_pos, DXL_i, ADDR_PRO_GOAL_POSITION, LEN_PRO_GOAL_POSITION, ...
            typecast(int32(Goal_position(DXL_i)), 'uint32'), LEN_PRO_GOAL_POSITION);
        if dxl_addparam_result ~= true
            fprintf('[ID:%03d] groupBulkWrite addparam failed', DXL_i);
            return;
        end
        fprintf('[ID:%03d] {GoalPos:%03d  PresPos:%03d}; {GoalVel:%03d  PresVel:%03d} \n', ...
            DXL_i, int32(Goal_position(DXL_i)), Present_position(DXL_i),  round(Goal_velocity(DXL_i)), Present_velocity(DXL_i));
    end
    
    % Bulkwrite goal position and velocity
    groupBulkWriteTxPacket(bulkwrite_vel_pos);
%     if getLastTxRxResult(port_num, PROTOCOL_VERSION) ~= COMM_SUCCESS
%         printTxRxResult(PROTOCOL_VERSION, getLastTxRxResult(port_num, PROTOCOL_VERSION));
%     end
    % Clear bulkwrite parameter storage
    groupBulkWriteClearParam(bulkwrite_vel_pos);
    
    % Break cycle when t==n*T
    if pt_>=T*6
        % stop ID = 1
        if ismember(1, DXL_ID)
            write4ByteTxRx(port_num, PROTOCOL_VERSION, 1, ADDR_PRO_GOAL_VELOCITY, typecast(int32(0), 'uint32'));
        else
            write4ByteTxRx(port_num, PROTOCOL_VERSION, 6, ADDR_PRO_GOAL_VELOCITY, typecast(int32(0), 'uint32'));
        end
        break;
    end
    t22 = clock;
    dt = etime(t22, t2);
end
t3 = clock;
Time_thrd = {t1, t3};
input('<Press any key to plot data>\n');
%%
% Disable Dynamixel# Torque
for to_ = DXL_ID
    write1ByteTxRx(port_num, PROTOCOL_VERSION, to_, ADDR_PRO_TORQUE_ENABLE, TORQUE_DISABLE);
    dxl_comm_result = getLastTxRxResult(port_num, PROTOCOL_VERSION);
    dxl_error = getLastRxPacketError(port_num, PROTOCOL_VERSION);
    if dxl_comm_result ~= COMM_SUCCESS
        fprintf('[ID:%03d]\t%s\n', to_, getTxRxResult(PROTOCOL_VERSION, dxl_comm_result));
    elseif dxl_error ~= 0
        fprintf('[ID:%03d]\t%s\n', to_, getRxPacketError(PROTOCOL_VERSION, dxl_error));
    end
end

% Close port
closePort(port_num);
% Unload Library

unloadlibrary(lib_name);
fprintf('Succeeded to exit from program\n');

%% Plot data
plot_t = ppv_(1, ppv_(1, :, 1)~=0, 1);

figure(1);
for i = DXL_ID(DXL_ID ~= 1)
    subplot(3, 7, i-1);
    plot(plot_t, Drive_direction(i)*(ppv_(i+1, ppv_(1, :, 1) ~= 0, 1) -Position_0(i))/2048*180, '--');
    title(['pos of 1 and', num2str(i)]);
    if i == 2 || i == 3
        hold on
        plot(plot_t, double(subs(outer_P, t, plot_t)) /pi *180 ./Drive_ratio(i), '-');
        yyaxis right;
        plot(plot_t, double(subs(Crak_motor_pos, t, plot_t))/Drive_ratio(1)/pi*180, '-');
        plot(plot_t, Drive_direction(1)*(ppv_(2, ppv_(1, :, 1) ~= 0, 1) - Position_0(1))/2048*180, '--');
        hold off
    else

        hold on
        plot(plot_t, double(subs(twist_P, t, plot_t)) /pi *180 ./Drive_ratio(i), '-');
        yyaxis right;
        plot(plot_t, double(subs(Crak_motor_pos, t, plot_t))/Drive_ratio(1)/pi*180, '-');
        plot(plot_t, Drive_direction(1)*(ppv_(2, ppv_(1, :, 1) ~= 0, 1) - Position_0(1))/2048*180, '--');
        hold off
    end
    
    subplot(3, 7, i+3);
    plot(plot_t, Drive_direction(i)*ppv_(i+1, ppv_(1, :, 2) ~= 0, 2));
    title(['vel of ', num2str(i)]);
    if i == 2 || i==3
        hold on
        plot(plot_t, double(subs(outer_V, t, plot_t))/pi*30  ./Drive_ratio(i) / DXL_v_unit);
        hold off
    else
        hold on
        plot(plot_t, double(subs(twist_V, t, plot_t))/pi*30  ./Drive_ratio(i) / DXL_v_unit);
        hold off
    end
    
    subplot(3, 7, i+7);
    plot(plot_t, Drive_direction(i)*curr_store(i, ppv_(1, :, 1) ~= 0));
    title(['Current of 1 and', num2str(i)]);
    hold on
    plot(plot_t,  Drive_direction(1)*curr_store(1, ppv_(1, :, 1) ~= 0));
    hold off
end
figure(15);
plot(plot_t, double(subs(Crak_motor_pos, t, plot_t)) /Drive_ratio(1) /pi*180, '-');
hold on
plot(plot_t, Drive_direction(1)*(ppv_(2, ppv_(1, :, 1) ~= 0, 1) - Position_0(1))/2048*180, '--');
hold off

figure(16);
plot(ppv_(2, (ppv_(1,:, 1)~= 0), 2));


%%
saveas(1, ['figure_', num2str(1), '.png']);
save ppv_

% input_ = double(subs(outer_P, t, plot_t))';
% output_ = ppv_(3, :, 1)';
% output_(1) = [];
% output_ = output_(output_~=0)/2048*pi-pi;
