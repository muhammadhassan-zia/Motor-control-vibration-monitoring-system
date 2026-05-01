%% ===== USER SETTINGS =====
port = "COM5";      % Change this to your Arduino COM port
baud = 9600;
bufferSize = 500;   % Number of samples in rolling window for FFT
Fs = 50;            % Approx sample rate in Hz (adjust if needed)

%% ===== SERIAL SETUP =====
s = serialport(port, baud);
flush(s);           % clear old data
pause(2);           % wait for Arduino

disp("Real-time vibration monitoring started... Press Ctrl+C to stop.");

%% ===== INITIALIZE DATA BUFFER =====
data = zeros(1, bufferSize);

%% ===== SETUP FIGURES =====
hTime = figure('Name','Time-Domain Vibration','NumberTitle','off');
timeLine = plot(data);
ylim([-0.2 1.2]);
xlabel('Sample #');
ylabel('Vibration');
grid on;

hFFT = figure('Name','FFT of Vibration','NumberTitle','off');
fftLine = plot(linspace(0, Fs/2, bufferSize/2+1), zeros(1, bufferSize/2+1));
xlabel('Frequency (Hz)');
ylabel('Magnitude');
grid on;

%% ===== REAL-TIME LOOP =====
while true
    % Read a new sample from Arduino
    if s.NumBytesAvailable > 0
        line = readline(s);
        value = str2double(line);

        if isnan(value)
            value = 0; % fallback
        end

        % Update rolling data buffer
        data = [data(2:end) value];

        % --- Update time-domain plot ---
        set(0, 'CurrentFigure', hTime);
        set(timeLine, 'YData', data);
        drawnow limitrate

        % --- Compute and update FFT ---
        Y = fft(data);
        L = length(data);
        P2 = abs(Y/L);
        P1 = P2(1:L/2+1);
        P1(2:end-1) = 2*P1(2:end-1);
        f = Fs*(0:(L/2))/L;

        set(0, 'CurrentFigure', hFFT);
        set(fftLine, 'XData', f, 'YData', P1);
        drawnow limitrate
    end
end

%% ===== CLEANUP =====
% (script stops with Ctrl+C)
clear s
disp('Real-time monitoring stopped.');
