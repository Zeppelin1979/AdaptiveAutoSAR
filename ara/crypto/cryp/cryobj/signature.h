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
            class Signature : public ara::crypto::CryptoObject
            {
                static const CryptoObjectType kObjectType = CryptoObjectType::kSignature;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SIGNATURE_H