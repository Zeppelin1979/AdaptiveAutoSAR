#ifndef ARA_CRYPTO_X509_X509_EXTENSIONS_H
#define ARA_CRYPTO_X509_X509_EXTENSIONS_H

#include <memory>

#include "ara/crypto/x509/x509_object.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            /**
             * @brief [SWS_CRYPT_40500]
             * Interface of X.509 Extensions.
             */
            class X509Extensions : public X509Object
            {
            public:

                /**
                 * @brief [SWS_CRYPT_40501]
                 * Shared smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<X509Extensions>;

                /**
                 * @brief [SWS_CRYPT_40511]
                 * Count number of elements in the sequence.
                 * @return std::size_t number of elements in the sequence
                 */
                virtual std::size_t Count () const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_X509_X509_EXTENSIONS_H