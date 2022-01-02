#ifndef ARA_CRYPTO_CRYP_PRIVATE_KEY_H
#define ARA_CRYPTO_CRYP_PRIVATE_KEY_H

#include "ara/crypto/cryp/common/base_id_types.h"
#include "ara/crypto/cryp/cryobj/restricted_use_object.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_22500]
             * Generalized Asymmetric Private Key interface.
             */
            class PrivateKey : public RestrictedUseObject
            {
            public:
                
                /**
                 * @brief [SWS_CRYPT_22503]
                 * Static mapping of this interface to specific value of CryptoObjectType enumeration.
                 */
                static const CryptoObjectType kObjectType = CryptoObjectType::kPrivateKey;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_PRIVATE_KEY_H