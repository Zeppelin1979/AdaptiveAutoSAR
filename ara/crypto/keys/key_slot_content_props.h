#ifndef ARA_CRYPTO_KEYS_KEY_SLOT_CONTENT_PROPS_H
#define ARA_CRYPTO_KEYS_KEY_SLOT_CONTENT_PROPS_H

#include "ara/crypto/cryp/cryobj/crypto_object.h"
#include "ara/crypto/cryp/common/base_id_types.h"
#include "ara/crypto/cryp/common/crypto_object_uid.h"

namespace ara
{
    namespace crypto
    {
        namespace keys
        {
            /**
             * @brief [SWS_CRYPT_30500]
             * Properties of current Key Slot Content, i.e. of a current instance stored to the Key Slot. A value
             * of the mAllowedUsage field is bitwise AND of the common usage flags defined at run-time and
             * the usage flags defined by the UserPermissions prototype for current "Actor".
             */
            struct KeySlotContentProps
            {
                /**
                 * @brief [SWS_CRYPT_30511]
                 * shared pointer of interface
                 */
                using Uptr = std::unique_ptr<KeySlotContentProps>;

                /**
                 * @brief [SWS_CRYPT_30503]
                 * Cryptoalgorithm of actual object stored to the slot.
                 */
                CryptoAlgId mAlgId;

                /**
                 * @brief [SWS_CRYPT_30505]
                 * Actual size of an object currently stored to the slot.
                 */
                std::size_t mObjectSize;

                /**
                 * @brief [SWS_CRYPT_30508]
                 * Actual type of an object stored to the slot.
                 */
                CryptoObjectType mObjectType;

                /**
                 * @brief [SWS_CRYPT_30501]
                 * UID of a Crypto Object stored to the slot.
                 */
                CryptoObjectUid mObjectUid;

                /**
                 * @brief [SWS_CRYPT_30506]
                 * Actual usage restriction flags of an object stored to the slot for the current "Actor".
                 */
                AllowedUsageFlags mContentAllowedUsage;

                /**
                 * @brief [SWS_CRYPT_30510]
                 * set content properties
                 */
                KeySlotContentProps ()=default;
            };

            /**
             * @brief [SWS_CRYPT_30550]
             * Comparison operator "equal" for KeySlotContentProps operands.
             * @param lhs left-hand side operand
             * @param rhs right-hand side operand
             * @return true if all members’ values of lhs is equal to rhs
             * @return false otherwise
             */
            constexpr bool operator== (const KeySlotContentProps &lhs, const KeySlotContentProps &rhs) noexcept
            {
                return ((lhs.mAlgId == rhs.mAlgId) && 
                        (lhs.mObjectSize == rhs.mObjectSize) &&
                        (lhs.mObjectType == rhs.mObjectType) &&
                        (lhs.mObjectUid == rhs.mObjectUid) &&
                        (lhs.mContentAllowedUsage == rhs.mContentAllowedUsage));
            }

            /**
             * @brief [SWS_CRYPT_30551]
             * Comparison operator "not equal" for KeySlotContentProps operands.
             * @param lhs left-hand side operand
             * @param rhs right-hand side operand
             * @return true if at least one member of lhs has a value not equal to correspondent member of rhs
             * @return false otherwise
             */
            constexpr bool operator!= (const KeySlotContentProps &lhs, const KeySlotContentProps &rhs) noexcept
            {
                return !(lhs == rhs);
            }
        }
    }
}

#endif // ARA_CRYPTO_KEYS_KEY_SLOT_CONTENT_PROPS_H
            