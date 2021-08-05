//either of these methods work to create the echo function - 
//but neither are actually necessary for the native windows app, which
//skips the interface and goes to the proxy page.


module.exports = {
    neptuneLogin: function (successCallback, errorCallback, [signer]) {
        cordova.exec(successCallback,  errorCallback, "SignPlugin", "loginMethod", [signer]);
    },
    neptuneSign: function (successCallback, errorCallback, [args]) {
	cordova.exec(successCallback,  errorCallback, "SignPlugin", "signMethod", [args]);
    },
    neptuneVerify: function (successCallback, errorCallback, [args]) {
	cordova.exec(successCallback,  errorCallback, "SignPlugin", "verifyMethod", [args]);
    }
};