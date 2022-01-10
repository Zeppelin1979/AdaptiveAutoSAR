#ifndef ARA_CRYPTO_CRYP_SIGNATURE_H
#define ARA_CRYPTO_CRYP_SIGNATURE_H

#include "ara/crypto/cryp/cryobj/crypto_object.h"
#include "ara/crypto/cryp/common/base_id_types.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_23300]
             * Signature container interface This interface is applicable for keeping the Digital Signature, Hash
             * Digest, (Hash-based) Message Authentication Code (MAC/HMAC). In case of a keyed
             * signature (Digital Signature or MAC/HMAC) a COUID of the signature verification key can be
             * obtained by a call of CryptoObject::HasDependence()!
             */
            class Signature : public CryptoObject
            {
            public:

                /**
                 * @brief [SWS_CRYPT_23301]
                 * Unique smart pointer of the interface.
                 */
                using Uptrc = std::unique_ptr<const Signature>;

                static const CryptoObjectType kObjectType = CryptoObjectType::kSignature;

                /**
                 * @brief [SWS_CRYPT_23311]
                 * Get an ID of hash algorithm used for this signature object production.
                 * @return CryptoPrimitiveId::AlgId ID of used hash algorithm only (without signature algorithm specification)
                 */
                virtual CryptoPrimitiveId::AlgId GetHashAlgId () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23312]
                 * Get the hash size required by current signature algorithm.
                 * @return std::size_t required hash size in bytes
                 */
                virtual std::size_t GetRequiredHashSize () const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SIGNATURE_H