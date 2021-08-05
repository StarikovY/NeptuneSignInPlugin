#include "SignFileComponent.h"
#include <stdexcept>

// in the implementation file .cpp
using namespace SignFileComponent;
using namespace Platform;
using namespace Windows;
using namespace Concurrency;
using namespace Windows::Storage;

IAsyncOperation<Platform::String^>^ SignPluginRT::Sign(Platform::String^ subject, Platform::String^ data, Platform::Boolean saveResults)
{
    if(data->IsEmpty() || subject->IsEmpty())
    {
        throw std::invalid_argument::invalid_argument("Error: input string or subject is empty");
    }
    else
    {
        try
        {
            Platform::String^ file = "signed.sgn";

            return create_async([subject, data, file, saveResults]()
            {               
                SigningFile SgnFile;

                return SgnFile.HrSignData(
                    subject,
                    data, file, saveResults); });
        }
        catch (Exception^ ex)
        {
            auto msg = ex->Message;

            return create_async([msg]() {return msg; });
        }
    }
}

IAsyncOperation<Platform::Boolean>^ SignPluginRT::Verify(Platform::String^ subject, Platform::String^ data, Platform::String^ signature)
{
    if (data->IsEmpty() || subject->IsEmpty())
    {
        throw std::invalid_argument::invalid_argument("Error: input string or subject is empty");
    }
    else
    {
        return create_async([subject, data, signature]()
        {
            SigningFile SgnFile;

            return SgnFile.HrVerifySign(
                subject,
                data, signature); 
        });
    }
}

IAsyncOperation<Platform::String^>^ SignPluginRT::Login(Platform::String^ subject)
{
    if (subject->IsEmpty())
    {
        throw std::invalid_argument::invalid_argument("Error: subject is empty");
    }
    else
    {
        Platform::String^ data = "Login";
        Platform::String^ file = "login.sgn";

        try
        {
            return create_async([subject, data, file]()
            {
                SigningFile SgnFile;

                return SgnFile.HrSignData(
                    subject,
                    data, file, false); });
        }
        catch (Exception^ ex)
        {
            auto msg = ex->Message;

            return create_async([msg]() {return msg; });
        }
    }
}

Platform::String^ SignPluginRT::TestCall(Platform::String^ Data)
{
    return "test call success";
}

