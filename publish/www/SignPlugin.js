//either of these methods work to create the echo function - 
//but neither are actually necessary for the native windows app, which
//skips the interface and goes to the proxy page.


module.exports = {
    loginPIV: function (successCallback, errorCallback, [signer]) {
        cordova.exec(successCallback,  errorCallback, "SignPlugin", "loginPIV", [signer]);
    },
    signPIV: function (successCallback, errorCallback, [args]) {
	cordova.exec(successCallback,  errorCallback, "SignPlugin", "signPIV", [args]);
    },
    verifyPIV: function (successCallback, errorCallback, [args]) {
	cordova.exec(successCallback,  errorCallback, "SignPlugin", "verifyPIV", [args]);
    }
};