#ifndef ARA_CRYPTO_X509_OSPC_REQUEST_H
#define ARA_CRYPTO_X509_OSPC_REQUEST_H

#include <cinttypes>
#include <memory>

#include "ara/crypto/x509/x509_object.h"


namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            /**
             * @brief [SWS_CRYPT_40700]
             * On-line Certificate Status Protocol Request.
             */
            class OcspRequest : public X509Object
            {
            public:

                /**
                 * @brief [SWS_CRYPT_40702]
                 * Shared smart pointer of the interface.
                 */
                using Uptrc = std::unique_ptr<const OcspRequest>;

                /**
                 * @brief [SWS_CRYPT_40701]
                 * Shared smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<OcspRequest>;

                /**
                 * @brief [SWS_CRYPT_40711]
                 * Get version of the OCSP request format.
                 * @return std::uint32_t OCSP request format version
                 */
                virtual std::uint32_t Version () const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_X509_OSPC_REQUEST_H