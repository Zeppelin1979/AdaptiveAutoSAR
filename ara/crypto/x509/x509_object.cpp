#include "x509_object.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            X509Provider& X509Object::MyProvider () const noexcept
            {
                return mProvider;
            }
        }
    }
}