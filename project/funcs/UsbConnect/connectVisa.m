function isConnected = connectVisa()
    persistent visaObj
    if isempty(visaObj) || ~isvalid(visaObj)
        visaObj = visadev('KEYSIGHT', 'USB0::0x2A8D::0x1783::MY1234567::0::INSTR');
    end
    visaObj.connect();
    isConnected = visaObj.IsConnected;
end
