#ifndef ARA_CRYPTO_CRYP_PUBLIC_KEY_H
#define ARA_CRYPTO_CRYP_PUBLIC_KEY_H

#include "ara/crypto/cryp/common/base_id_types.h"
#include "ara/crypto/cryp/cryobj/restricted_use_object.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_22700]
             * General Asymmetric Public Key interface.
             */
            class PublicKey : public RestrictedUseObject
            {
            public:
            
                /**
                 * @brief [SWS_CRYPT_22702]
                 * const object type
                 */
                static const CryptoObjectType kObjectType = CryptoObjectType::kPublicKey;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_PUBLIC_KEY_H