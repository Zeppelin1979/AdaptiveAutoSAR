#ifndef ARA_CRYPTO_CRYPTO_OBJECT_H
#define ARA_CRYPTO_CRYPTO_OBJECT_H

#include "ara/crypto/cryp/common/crypto_object_uid.h"

namespace ara
{
    namespace crypto
    {
        /**
         * @brief [SWS_CRYPT_20500]
         * A common interface for all cryptograhic objects recognizable by the Crypto Provider. This
         * interface (or any its derivative) represents a non-mutable (after completion) object loadable to a
         * temporary transformation context.
         */
        class CryptoObject
        {
            struct COIdentifier
            {
                /**
                 * @brief [SWS_CRYPT_20506]
                 * type of objext
                 */
                CryptoObjectType mCOType;

                /**
                 * @brief [SWS_CRYPT_20507]
                 * object identifier
                 */
                CryptoObjectUid mCouid;
            };
        };
    }
}

#endif // ARA_CRYPTO_CRYPTO_OBJECT_H
