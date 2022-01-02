#ifndef ARA_CRYPTO_CRYP_SYMMETRIC_KEY_H
#define ARA_CRYPTO_CRYP_SYMMETRIC_KEY_H

#include "ara/crypto/cryp/cryobj/restricted_use_object.h"
#include "ara/crypto/cryp/common/base_id_types.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_23800]
             * Symmetric Key interface.
             */
            class SymmetricKey : public RestrictedUseObject
            {
            public:
                
                /**
                 * @brief [SWS_CRYPT_23801]
                 * Unique smart pointer of the interface.
                 */
                using Uptrc = std::unique_ptr<const SymmetricKey>;

                /**
                 * @brief [SWS_CRYPT_23802]
                 * const object type
                 */
                static const CryptoObjectType kObjectType = CryptoObjectType::kSymmetricKey;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SYMMETRIC_KEY_H