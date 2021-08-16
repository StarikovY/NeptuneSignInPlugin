
module.exports = {
	signPIV: function (successCallback, errorCallback, args) {

		try {
			var res = SignFileComponent.SignPluginRT.sign(args[0], args[1], args[2]);

			if (!res) {
				errorCallback("Unable to sign data. No result from method call");
			}
			else {
				successCallback(res);
			}
		}
		catch (error) {
			errorCallback("Unable to sign data. Inner exception on sign data operation");
		}
	},

	loginPIV: function (successCallback, errorCallback, strInput) {

		try {
			var res = SignFileComponent.SignPluginRT.login([strInput]);

			if (!res) {
				errorCallback("Unable to login. No result from method call");
			}
			else {
				successCallback(res);
			}
		}
		catch (error) {
			errorCallback("Unable to login. Inner exception on login operation");
		}
	},

	verifyPIV: function (successCallback, errorCallback, args) {

		try {
			var res = SignFileComponent.SignPluginRT.verify(args[0], args[1], args[2]);

			if (!res) {
				errorCallback("Unable to verify signature. No result from method call");
			}
			else {
				successCallback(res);
			}
		}
		catch (error) {
			errorCallback("Unable to verify signature. Inner exception on verify signature operation");
		}
	}
};

require('cordova/exec/proxy').add('SignPlugin', module.exports);