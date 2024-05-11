function [isConnected, deviceID] = connectVisa()
    persistent visaObj
    try
        if isempty(visaObj) || ~isvalid(visaObj)
            visaObj = visadev('KEYSIGHT', 'USB0::0x2A8D::0x1783::MY1234567::0::INSTR');
        end
        visaObj.connect();
        isConnected = visaObj.IsConnected;
        if isConnected
            deviceID = string(writeread(visaObj, '*IDN?'));  % 确保转换为字符串
        else
            deviceID = "无法识别设备";  % 使用字符串直接赋值
        end
    catch
        isConnected = false;
        deviceID = "连接失败或设备无响应";
    end
end
