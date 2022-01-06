#ifndef ARA_CRYPTO_X509_OSPC_RESPONSE_H
#define ARA_CRYPTO_X509_OSPC_RESPONSE_H

#include <memory>
#include <cinttypes>

#include "ara/crypto/x509/x509_object.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            /**
             * @brief [SWS_CRYPT_40800]
             * On-line Certificate Status Protocol Response.
             */
            class OcspResponse : public X509Object
            {
            public:

                /**
                 * @brief [SWS_CRYPT_40802]
                 * Shared smart pointer of the interface.
                 */
                using Uptrc = std::unique_ptr<const OcspResponse>;

                /**
                 * @brief [SWS_CRYPT_40801]
                 * Shared smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<OcspResponse>;

                /**
                 * @brief [SWS_CRYPT_40002]
                 * On-line Certificate Status Protocol (OCSP) Certificate Status.
                 */
                enum class OcspCertStatus : std::uint32_t
                {
                    kGood= 0,       // The certificate is not revoked.
                    kRevoked= 1,    // The certificate has been revoked (either permanantly or temporarily (on hold))
                    kUnknown= 2     // The responder doesn’t know about the certificate being requested.
                };

                /**
                 * @brief [SWS_CRYPT_40001]
                 * On-line Certificate Status Protocol (OCSP) Response Status.
                 */
                enum class OcspResponseStatus : std::uint32_t
                {
                    kSuccessful= 0,         // Response has valid confirmations.
                    kMalformedRequest= 1,   // Illegal confirmation request.
                    kInternalError= 2,      // Internal error in issuer.
                    kTryLater= 3,           // Try again later.
                    kSigRequired= 5,        // Must sign the request.
                    kUnauthorized= 6        // Request unauthorized.
                };

                /**
                 * @brief [SWS_CRYPT_40811]
                 * Get version of the OCSP response format.
                 * @return std::uint32_t OCSP response format version
                 */
                virtual std::uint32_t Version () const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_X509_OSPC_RESPONSE_H