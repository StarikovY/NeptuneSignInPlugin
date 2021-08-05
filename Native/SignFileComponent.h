// in your header file .h
#include <ppltasks.h>

using namespace Windows::Foundation;

namespace SignFileComponent
{
    public ref class SignPluginRT sealed
    {
        public:
		
		static IAsyncOperation<Platform::String^>^ Sign(Platform::String^ Subject, Platform::String^ Data, Platform::Boolean saveResults);
		static IAsyncOperation<Platform::Boolean>^ Verify(Platform::String^ Subject, Platform::String^ Data, Platform::String^ Signature);
		static IAsyncOperation<Platform::String^>^ Login(Platform::String^ Subject);
		static Platform::String^ TestCall(Platform::String^ Data);

	};

	public ref class SigningFile sealed
	{
	public:
		IAsyncOperation<Platform::String^>^ HrSignData(Platform::String^ Subject, Platform::String^ Data, Platform::String^ SaveToFile, Platform::Boolean saveResults);
		IAsyncOperation<Platform::Boolean>^ HrVerifySign(Platform::String^ Subject, Platform::String^ Data, Platform::String^ Signature);

	};

}

