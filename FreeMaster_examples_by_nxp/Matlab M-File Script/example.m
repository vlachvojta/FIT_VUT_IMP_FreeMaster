%% Copyright 2019-2020 NXP
%% 
%% This software is owned or controlled by NXP and may
%% only be used strictly in accordance with the applicable license terms.
%% By expressly accepting such terms or by downloading, installing,
%% activating and/or otherwise using the software, you are agreeing that
%% you have read, and that you agree to comply with and are bound by,
%% such license terms.  If you do not agree to be bound by the applicable
%% license terms, then you may not retain, install, activate or otherwise
%% use the software.

% create FreeMASTER ActiveX object
pcm = actxserver ('MCB.PCM');

% write 10 value into "var16" variable 
bSucc = pcm.WriteVariable('var16inc', 10);
var16 = 0;

% read the "var16" variable as defined in FreeMASTER project
bSucc = pcm.ReadVariable('var16');
if bSucc
    var16 = pcm.LastVariable_vValue;
end
% show the value
var16

% configure matlab to accept safe array as single dimension
feature('COM_SafeArraySingleDim', 1) ;
% write 4 bytes to 'arr8' array. WriteMemory function expects SafeArray as input data
bSucc = pcm.WriteMemory('arr8', 4, {11;22;33;44})
% reads 4 bytes from memory at address of var32inc variable
bSucc = pcm.ReadMemory('var32inc', 4);
if bSucc
    % reads data of last call the ReadMemory()function.
    readMemResult =  pcm.LastMemory_data
end