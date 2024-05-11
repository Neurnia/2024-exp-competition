function [dataBuffer, deviceID] = readOriginWave(numberOfPoints)
    persistent visaObj  % 使用persistent保持visaObj状态
    dataBuffer = [];    % 初始化返回的数据缓冲区

    % 检查visaObj是否已经初始化和有效
    if isempty(visaObj) || ~isvalid(visaObj)
        deviceID = "请先点击连接示波器。";
        return;
    end

    % 检查设备是否已经连接
    if visaObj.IsConnected
        fprintf(visaObj, 'DATA:SOURCE CH1');       % 设置数据源为通道1
        fprintf(visaObj, 'DATA:WIDTH 1');          % 设置数据宽度为1
        fprintf(visaObj, 'DATA:ENC RPB');          % 设置数据编码格式
        fprintf(visaObj, 'CURVe?');                % 请求数据
        dataBuffer = binblockread(visaObj, 'uint8', numberOfPoints); % 读取指定数量的波形数据
        flushinput(visaObj);                       % 清除输入缓冲区
        deviceID = string(writeread(visaObj, '*IDN?'));       % 返回成功读取数据的信息
    else
        deviceID = "请先点击连接示波器。";
    end
    
    return;  % 返回数据和设备ID或错误信息
end
