#ifndef ARA_CRYPTO_CRYP_CRYOBJ_RESTRICTED_USE_OBJECT_H
#define ARA_CRYPTO_CRYP_CRYOBJ_RESTRICTED_USE_OBJECT_H

#include "ara/crypto/cryp/cryobj/crypto_object.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_24800]
             * A common interface for all objects supporting the usage restriction.
             */
            class RestrictedUseObject : public CryptoObject
            {
            public:

                /**
                 * @brief [SWS_CRYPT_24802]
                 * Unique smart pointer of the interface.
                 */
                using Uptrc = std::unique_ptr<const RestrictedUseObject>;

                /**
                 * @brief [SWS_CRYPT_24801]
                 * Alias to the container type for bit-flags of allowed usages of the object.
                 */
                using Usage = AllowedUsageFlags;

                /**
                 * @brief [SWS_CRYPT_24811]
                 * Get allowed usages of this object.
                 * @return Usage a combination of bit-flags that specifies allowed applications of the object
                 */
                virtual Usage GetAllowedUsage () const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_CRYOBJ_RESTRICTED_USE_OBJECT_H
