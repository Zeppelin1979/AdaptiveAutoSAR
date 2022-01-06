#ifndef ARA_CRYPTO_X509_X509_OBJECT_H
#define ARA_CRYPTO_X509_X509_OBJECT_H

#include "ara/crypto/cryp/common/serializable.h"

#include "ara/crypto/x509/x509_provider.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            /**
             * @brief [SWS_CRYPT_40900]
             * Common interface of all objects created by X.509 Provider.
             */
            class X509Object : public Serializable
            {
            private:
                X509Provider &mProvider;
            public:
            
                /**
                 * @brief [SWS_CRYPT_40911]
                 * Get a reference to X.509 Provider of this object.
                 * @return X509Provider& a reference to X.509 Provider instance that provides
                 * this object
                 */
                virtual X509Provider& MyProvider () const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_X509_X509_OBJECT_H