#ifndef ARA_CRYPTO_KEYS_KEY_SLOT_PROTOTYPE_PROPS_H
#define ARA_CRYPTO_KEYS_KEY_SLOT_PROTOTYPE_PROPS_H

#include "ara/crypto/cryp/common/base_id_types.h"

namespace ara
{
    namespace crypto
    {
        namespace keys
        {
            /**
             * @brief [SWS_CRYPT_30300]
             * Prototyped Properties of a Key Slot.
             */
            struct KeySlotPrototypeProps
            {
                
                /**
                 * @brief [SWS_CRYPT_30302]
                 * 
                 */
                using Uptr = std::unique_ptr<KeySlotPrototypeProps>;

                /**
                 * @brief [SWS_CRYPT_30306]
                 * Cryptoalgorithm restriction (kAlgIdAny means without restriction). The algorithm can be
                 * specified partially: family & length, mode, padding.
                 */
                CryptoAlgId mAlgId;

                /**
                 * @brief [SWS_CRYPT_30309]
                 * Indicates whether FC Crypto shall allocate sufficient storage space for a shadow copy of this
                 * KeySlot.
                 */
                bool mAllocateSpareSlot;

                /**
                 * @brief [SWS_CRYPT_30310]
                 * Indicates whether the content of this key-slot may be changed, e.g. from storing a symmetric
                 * key to storing an RSA key If this is set to false, then the mObjectType of this KeySlotPrototype
                 * Props must be a) valid and b) cannot be changed ( i.e. only objects of mObjectType may be
                 * stored in this key-slot).
                 */
                bool mAllowContentTypeChange;

                /**
                 * @brief [SWS_CRYPT_30313]
                 * Indicates how the content may be used. The following use cases of this attribute are
                 * considered:
                 * the object to be stored in this key-slot has it’s AllowedUsageFlags set to kAllowPrototypedOnly.
                 * In this case this attribute must be observed when loading the content into a runtime instance
                 * (e.g. the AllowedUsageFlags of a SymmetricKey object should be set according to this
                 * attribute) mMaxUpdatesAllowed==0, in this case the content is provided during production
                 * while the AllowedUsageFlags is modeled using this attribute when this key-slot is flexibly
                 * updated the runtime object’s AllowedUsageFlags override this attribute upon a later loading
                 * from this key-slot
                 */
                AllowedUsageFlags mContentAllowedUsage;

                /**
                 * @brief [SWS_CRYPT_30312]
                 * Indicates whether the key-slot content may be exported.
                 */
                bool mExportAllowed;

                /**
                 * @brief [SWS_CRYPT_30311]
                 * Specifies how many times this key-slot may be updated, e.g.:
                 * a value of 0 means the key-slot content will be pre-set during production a value of 1 means the
                 * key-slot content can be updated only once ("OTP") a negative value means the key-slot content
                 * can be updated inifinitely
                 */
                std::int32_t mMaxUpdateAllowed;

                /**
                 * @brief [SWS_CRYPT_30305]
                 * Key-slot type configuration: all key-slots used by the adaptive machine to provide serives such
                 * as secure communication, diagnostics, updates, secure storage etc. shall use the type k
                 * Machine. All key-slots that will be used by the adaptive user application must use kApplication.
                 * A key-manager user application may define kMachine key-slots as well; in this case the
                 * integrator must match a corresponding machine key-slot to be managed.
                 */
                KeySlotType mSlotType;

                /**
                 * @brief [SWS_CRYPT_30307]
                 * Capacity of the slot in bytes
                 */
                std::size_t mSlotCapacity;

                /**
                 * @brief [SWS_CRYPT_30308]
                 * Restriction of an object type that can be stored the slot. If this field contains CryptoObject
                 * Type::kUnknown then without restriction of the type.
                 */
                CryptoObjectType mObjectType;

                /**
                 * @brief [SWS_CRYPT_30301]
                 * 
                 */
                KeySlotPrototypeProps ()=default;
            };

            /**
             * @brief [SWS_CRYPT_30350]
             * Comparison operator "equal" for KeySlotPrototypeProps operands.
             * @param lhs left-hand side operand
             * @param rhs right-hand side operand
             * @return true if all members’ values of lhs is equal to rhs
             * @return false otherwise
             */
            constexpr bool operator== (const KeySlotPrototypeProps &lhs, const KeySlotPrototypeProps &rhs) noexcept
            {
                return ((lhs.mAlgId == rhs.mAlgId) && 
                        (lhs.mAllocateSpareSlot == rhs.mAllocateSpareSlot) &&
                        (lhs.mAllowContentTypeChange == rhs.mAllowContentTypeChange) &&
                        (lhs.mContentAllowedUsage == rhs.mContentAllowedUsage) &&
                        (lhs.mExportAllowed == rhs.mExportAllowed) &&
                        (lhs.mMaxUpdateAllowed == rhs.mMaxUpdateAllowed) &&
                        (lhs.mSlotType == rhs.mSlotType) &&
                        (lhs.mSlotCapacity == rhs.mSlotCapacity) &&
                        (lhs.mObjectType == rhs.mObjectType));
            }

            /**
             * @brief [SWS_CRYPT_30351]
             * Comparison operator "not equal" for KeySlotPrototypeProps operands.
             * @param lhs left-hand side operand
             * @param rhs right-hand side operand
             * @return true f at least one member of lhs has a value not equal to correspondent member of rhs
             * @return false otherwise
             */
            constexpr bool operator!= (const KeySlotPrototypeProps &lhs, const KeySlotPrototypeProps &rhs) noexcept
            {
                return !(lhs == rhs);
            }
        }
    }
}

#endif // ARA_CRYPTO_KEYS_KEY_SLOT_PROTOTYPE_PROPS_H
            