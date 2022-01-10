#ifndef ARA_CRYPTO_KEYS_KEYSLOT_H
#define ARA_CRYPTO_KEYS_KEYSLOT_H

#include "ara/core/result.h"

#include "ara/crypto/cryp/common/io_interface.h"
#include "ara/crypto/cryp/crypto_provider.h"

#include "ara/crypto/keys/key_slot_content_props.h"
#include "ara/crypto/keys/key_slot_prototype_props.h"

namespace ara
{
    namespace crypto
    {
        namespace keys
        {
            /**
             * @brief [SWS_CRYPT_30400]
             * Key slot port-prototype interface. This class enables access to a physicl key-slot.
             */
            class KeySlot
            {
            public:

                /**
                 * @brief [SWS_CRYPT_30402]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<KeySlot>;

                /**
                 * @brief [SWS_CRYPT_30405]
                 * Clear the content of this key-slot. This method must perform a secure cleanup without the
                 * ability to restore the object data! This method may be used for atomic update of a key slot
                 * scoped to some transaction. In such case the the slot will be updated only after correspondent
                 * call of CommitTransaction().
                 * @return ara::core::Result<void>
                 * @exception CryptoErrorDomain::kUnreservedResource if the target slot is not opened writeable.
                 */
                virtual ara::core::Result<void> Clear () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30401]
                 * Destroy the Key Slot object
                 * 
                 */
                virtual ~KeySlot () noexcept/*=default*/;

                /**
                 * @brief [SWS_CRYPT_30408]
                 * Get an actual properties of a content in the key slot. If this method called by a "User" Actor then
                 * always: props.exportability == false.
                 * @return ara::core::Result<KeySlotContentProps> 
                 * @exception CryptoErrorDomain::kEmptyContainer if the slot is empty
                 * @exception CryptoErrorDomain::kAccessViolation if this method is called by an Actor, which has no any ("Owner" or "User") access rights to the key slot
                 */
                virtual ara::core::Result<KeySlotContentProps> GetContentProps () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30403]
                 * Retrieve an instance of the CryptoProvider that owns this KeySlot. Any key slot always has an
                 * associated default Crypto Provider that can serve this key slot. In the simplest case all key slots
                 * can be served by a single Crypto Provider installed on the Adaptive Platform. But in a more
                 * complicated case a few different Crypto Providers may coexist in the system, for example if
                 * ECU has one or a few HSMs and software cryptography implementation too, and each of them
                 * has own physical key storage. In such case different dedicated Crypto Providers may serve
                 * mentioned HSMs and the software implementation.
                 * @return ara::core::Result<cryp::CryptoProvider::Uptr> a unique_pointer to the CryptoProvider to be used with this KeySlot
                 */
                virtual ara::core::Result<cryp::CryptoProvider::Uptr> MyProvider () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30407]
                 * Get the prototyped properties of the key slot.
                 * @return ara::core::Result<KeySlotPrototypeProps> 
                 */
                virtual ara::core::Result<KeySlotContentProps> GetPrototypedProps () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30404]
                 * Check the slot for emptiness.
                 * @return true if the slot is empty
                 * @return false otherwise
                 */
                virtual bool IsEmpty () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30409]
                 * Open this key slot and return an IOInterface to its content. If the UpdatesObserver interface
                 * was provided to the call of RegisterObserver() then the UpdatesObserver::OnUpdate() method
                 * should be called by Key Storage engine (in a dedicated thread) every time when this slot is
                 * updated (and become visible for "Users"). Monitoring of the opened key slot will be continued
                 * even after destruction of the returned TrustedContainer, because content of the slot may be
                 * loaded to volatile memory (as a CryptoObject or to a CryptoContext of a crypto primitive), but
                 * the TrustedContainer may be destroyed after this. Therefore if you need to terminate monitoring
                 * of the key slot then you should directly call method UnsubscribeObserver(SlotNumber).
                 * @param[in] subscribeForUpdates if this flag is true then the UpdatesObserver instance
                 * (previously registered by a call of the method RegisterObserver()) will be subscribed for updates
                 * of the opened key slot
                 * @param[in] writeable indicates whether the key-slot shall be opened read-only (default) or with write access
                 * @return ara::core::Result<IOInterface::Uptr> an unique smart pointer to the IOInterface
                 * associated with the slot content
                 * @exception CryptoErrorDomain::kInvalidUsageOrder if (true == subscribeForUpdates), but there is no
                 * registered instance of the UpdatesObserver in the Key Storage Provider context
                 * @exception CryptoErrorDomain::kBusyResource if the specified slot is busy because writeable ==
                 * true but (a) the keyslot is already opened writable,
                 * and/or (b) the keyslot is in scope of another ongoing
                 * transaction
                 * @exception CryptoErrorDomain::kModifiedResource if the specified slot has been modified after the Key
                 * Slot has been opened
                 */
                virtual ara::core::Result<IOInterface::Uptr> Open (bool subscribeForUpdates=false, bool writeable=false) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30406]
                 * Save the content of a provided source IOInterface to this key-slot. The source container may
                 * represent a volatile trusted container or another KeySlot This method may be used for atomic
                 * update of a key slot scoped to some transaction. In such case the the slot will be updated only
                 * after correspondent call of CommitTransaction().
                 * @param[in] container the source IOInterface
                 * @return ara::core::Result<void> true if successfully saved
                 * @exception CryptoErrorDomain::kIncompatibleObject if the source object has property "session" or if the
                 * source IOInterface references a KeySlot from a different CryptoProvider
                 * @exception CryptoErrorDomain::kEmptyContainer if the source IOInterface is empty
                 * @exception CryptoErrorDomain::kContentRestrictions if the source object doesn’t satisfy the slot
                 * restrictions (including version control)
                 * @exception CryptoErrorDomain::kUnreservedResource if the target slot is not opened writeable.
                 */
                virtual ara::core::Result<void> SaveCopy (const IOInterface &container) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30220]
                 * Copy-assign another KeySlot to this instance.
                 * @param other the other instance
                 * @return KeySlot& *this, containing the contents of other
                 */
                KeySlot& operator= (const KeySlot &other)=default;
 
                /**
                 * @brief [SWS_CRYPT_30221]
                 * Move-assign another KeySlot to this instance.
                 * @param other the other instance
                 * @return KeySlot& *this, containing the contents of other
                 */
                KeySlot& operator= (const KeySlot &&other)/*=default*/;
            };
        }
    }
}

#endif // ARA_CRYPTO_KEYS_KEYSLOT_H
