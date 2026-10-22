function frame = armdroid_pwm_frame(duty)
%ARMDROID_PWM_FRAME Build the 14-byte PC -> power-MCU PWM frame.
%   frame = armdroid_pwm_frame(duty)
%   duty : 5x1 (or 1x5) signed duty cycles in [-1, 1]
%          sign = direction (+ forward, IN1 high), |duty| = 0..1
%          NaN is sent as 0; values outside [-1, 1] are saturated.
%   frame: 14x1 uint8, ready for a Packet Output block ('14*uint8')
%          or a Serial Send block (115200 bps, 8N1).
%
%   Code-generation compatible: use it inside a MATLAB Function block
%   (Simulink Desktop Real-Time, Run in Kernel mode).
%
%   [0]0xAA [1]0x0C [2..11] 5 x int16 LE (duty*10000) [12]CRC-8/SMBUS(0..11) [13]0x55
%
%   v1.1: NaN -> 0 (min/max ignore NaN in MATLAB, so v1.0 sent NaN as full duty)

frame = zeros(14, 1, 'uint8');
frame(1) = uint8(170);   % 0xAA
frame(2) = uint8(12);    % bytes covered by CRC

d = double(duty(:));
d(isnan(d)) = 0;                     % must come BEFORE min/max
d = max(min(d, 1), -1);

for k = 1:5
    v = int32(round(d(k) * 10000));
    if v < 0
        v = v + int32(65536);          % two's complement
    end
    frame(1 + 2*k) = uint8(bitand(v, int32(255)));          % low byte
    frame(2 + 2*k) = uint8(bitshift(v, -8));                % high byte
end

frame(13) = crc8_smbus(frame(1:12));
frame(14) = uint8(85);   % 0x55
end

function crc = crc8_smbus(data)
crc = uint8(0);
for i = 1:numel(data)
    crc = bitxor(crc, data(i));
    for b = 1:8
        if bitand(crc, uint8(128))
            crc = bitxor(bitshift(crc, 1), uint8(7));
        else
            crc = bitshift(crc, 1);
        end
    end
end
end
