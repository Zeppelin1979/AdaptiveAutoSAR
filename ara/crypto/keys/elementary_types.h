#ifndef ARA_CRYPTO_KEYS_ELEMENTARY_TYPES_H
#define ARA_CRYPTO_KEYS_ELEMENTARY_TYPES_H

#include <cinttypes>
#include "ara/core/vector.h"
#include "ara/crypto/keys/keyslot.h"

namespace ara
{
    namespace crypto
    {
        namespace keys
        {
            /**
             * @brief [SWS_CRYPT_30010]
             * Definition of a transaction identifier type. The zero value should be reserved for especial cases.
             */
            using TransactionId = std::uint64_t;

            /**
             * @brief [SWS_CRYPT_30011]
             * Definition of a "transaction scope" type. The "transaction scope" defines a list of key slots that
             * are target for update in a transaction.
             */
            using TransactionScope = ara::core::Vector<KeySlot>;
        }
    }
}


#endif // ARA_CRYPTO_KEYS_ELEMENTARY_TYPES_H