function isConnected = disconnectVisa()
    persistent visaObj
    if ~isempty(visaObj) && isvalid(visaObj)
        visaObj.disconnect();
        isConnected = ~visaObj.IsConnected;
        clear visaObj
    else
        isConnected = false;
    end
end