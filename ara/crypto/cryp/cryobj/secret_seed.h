#ifndef ARA_CRYPTO_CRYP_SECRET_SEED_H
#define ARA_CRYPTO_CRYP_SECRET_SEED_H

#include "ara/crypto/cryp/common/base_id_types.h"
#include "ara/crypto/cryp/cryobj/restricted_use_object.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_23000]
             * Secret Seed object interface. This object contains a raw bit sequence of specific length (without
             * any filtering of allowed/disallowed values)! The secret seed value can be loaded only to a
             * non-key input of a cryptographic transformation context (like IV/salt/nonce)! Bit length of the
             * secret seed is specific to concret crypto algorithm and corresponds to maximum of its input/
             * output/salt block-length.
             */
            class SecretSeed : public RestrictedUseObject
            {
            public:
            
                /**
                 * @brief [SWS_CRYPT_23003]
                 * Static mapping of this interface to specific value of CryptoObjectType enumeration.
                 */
                static const CryptoObjectType kObjectType = CryptoObjectType::kSecretSeed;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SECRET_SEED_H