
module.exports = {
	signMethod: function (successCallback, errorCallback, args) {

		try {
			var res = SignFileComponent.SignPluginRT.sign(args[0], args[1], args[2]);

			if (!res) {
				errorCallback("Unable to sign data");
			}
			else {
				successCallback(res);
			}
		}
		catch (error) {
			errorCallback("Unable to sign data");
		}
	},

	loginMethod: function (successCallback, errorCallback, strInput) {

		try {
			var res = SignFileComponent.SignPluginRT.login([strInput]);

			if (!res) {
				errorCallback("Unable to login");
			}
			else {
				successCallback(res);
			}
		}
		catch (error) {
			errorCallback("Unable to login");
		}
	},

	verifyMethod: function (successCallback, errorCallback, args) {

		try {
			var res = SignFileComponent.SignPluginRT.verify(args[0], args[1], args[2]);

			if (!res) {
				errorCallback("Unable to verify signature");
			}
			else {
				successCallback(res);
			}
		}
		catch (error) {
			errorCallback("Unable to verify signature");
		}
	}
};

require('cordova/exec/proxy').add('SignPlugin', module.exports);