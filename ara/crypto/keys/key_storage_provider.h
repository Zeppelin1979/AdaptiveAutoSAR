#ifndef ARA_CRYPTO_KEYS_KEY_STORAGE_PROVIDER_H
#define ARA_CRYPTO_KEYS_KEY_STORAGE_PROVIDER_H

#include "ara/crypto/keys/elementary_types.h"
#include "ara/core/result.h"
#include "ara/core/instance_specifier.h"

namespace ara
{
    namespace crypto
    {
        namespace keys
        {
            /**
             * @brief [SWS_CRYPT_30100]
             * Key Storage Provider interface. Any object is uniquely identified by the combination of its UUID
             * and type. HSMs/TPMs implementing the concept of "non-extractable keys" should use own
             * copies of externally supplied crypto objects. A few software Crypto Providers can share single
             * key slot if they support same format.
             */
            class KeyStorageProvider
            {
            public:

                /**
                 * @brief [SWS_CRYPT_30101]
                 * 
                 */
                using Uptr = std::unique_ptr<KeyStorageProvider>;

                /**
                 * @brief [SWS_CRYPT_30123]
                 * Begin new transaction for key slots update. In order for a keyslot to be part of a transaction
                 * scope, the reserveSpareSlot model parameter of the keyslot has to be set to true. A transaction
                 * is dedicated for updating related key slots simultaneously (in an atomic, all-or-nothing, way). All
                 * key slots that should be updated by the transaction have to be opened and provided to this
                 * function. Any changes to the slots in scope are executed by calling commit().
                 * @param[in] targetSlots a list of KeySlots that should be updated during this transaction.
                 * @return ara::core::Result<TransactionId> a unique ID assigned to this transaction
                 * @exception CryptoErrorDomain::kUnreservedResource if targetSlots list has a slot that has not been
                 * configured with the reserveSpareSlot parameter in the manifest
                 * @exception CryptoErrorDomain::kBusyResource if targetSlots list has key slots that are already
                 * involved to another pending transaction or opened in writing mode
                 */
                virtual ara::core::Result<TransactionId> BeginTransaction (const TransactionScope &targetSlots) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30124]
                 * Commit changes of the transaction to Key Storage. Any changes of key slots made during a
                 * transaction are invisible up to the commit execution. The commit command permanently saves
                 * all changes made during the transaction in Key Storage.
                 * @param[in] id an ID of a transaction that should be commited
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kInvalidArgument if provided id is invalid, i.e. this ID is unknown or
                 * correspondent transaction already was finished (commited or rolled back)
                 */
                virtual ara::core::Result<void> CommitTransaction (TransactionId id) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30110]
                 * Destroy the Key Storage Provider object
                 * 
                 */
                virtual ~KeyStorageProvider () noexcept=default;

                /**
                 * @brief [SWS_CRYPT_30131]
                 * Get pointer of registered Updates Observer. The method returns nullptr if no observers have
                 * been registered yet!
                 * @return UpdatesObserver::Uptr unique pointer to the registered Updates Observer
                 * interface (copy of an internal unique pointer is returned, i.e. the Key Storage provider continues to
                 * keep the ownership)
                 */
                virtual UpdatesObserver::Uptr GetRegisteredObserver () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30115]
                 * Load a key slot. The functions loads the information associated with a KeySlot into a KeySlot
                 * object.
                 * @param[in] iSpecify the target key-slot instance specifier
                 * @return ara::core::Result<KeySlot::Uptr> an unique smart pointer to allocated key slot
                 * @exception CryptoErrorDomain::kUnreservedResource if the InstanceSpecifier is incorrect (the slot is not
                 * allocated)
                 */
                virtual ara::core::Result<KeySlot::Uptr> LoadKeySlot ( ara::core::InstanceSpecifier &iSpecify) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30130]
                 * Register consumer Updates Observer. Only one instance of the UpdatesObserver may be
                 * registered by an application process, therefore this method always unregister previous observer
                 * and return its unique pointer. If (nullptr == observer) then the method only unregister the
                 * previous observer! The method returns nullptr if no observers have been registered yet!
                 * @param[in] observer optional pointer to a client-supplied Updates
                 * Observer instance that should be registered inside Key Storage implementation and called every time,
                 * when an opened for usage/loading key slot is updated externally (by its "Owner" application)
                 * @return UpdatesObserver::Uptr unique pointer to previously registered Updates
                 * Observer interface (the pointer ownership is "moved out" to the caller code)
                 */
                virtual UpdatesObserver::Uptr RegisterObserver (UpdatesObserver::Uptr observer=nullptr) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30125]
                 * Rollback all changes executed during the transaction in Key Storage. The rollback command
                 * permanently cancels all changes made during the transaction in Key Storage. A rolled back
                 * transaction is completely invisible for all applications.
                 * @param[in] id an ID of a transaction that should be rolled back
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kInvalidArgument if provided id is invalid, i.e. this ID is unknown or
                 * correspondent transaction already was finished (commited or rolled back)
                 */
                virtual ara::core::Result<void> RollbackTransaction (TransactionId id) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30126]
                 * Unsubscribe the Update Observer from changes monitoring of the specified slot.
                 * @param[in] slot number of a slot that should be unsubscribed from the updates observing
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kInvalidArgument if the specified slot is not monitored now (i.e. if it
                 * was not successfully opened via OpenAsUser() or it was already unsubscribed by this method)
                 */
                virtual ara::core::Result<void> UnsubscribeObserver (KeySlot &slot) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30222]
                 * Copy-assign another KeyStorageProvider to this instance.
                 * @param other the other instance
                 * @return KeyStorageProvider& *this, containing the contents of other
                 */
                KeyStorageProvider& operator= (const KeyStorageProvider &other)=default;

                /**
                 * @brief [SWS_CRYPT_30223]
                 * Move-assign another KeyStorageProvider to this instance.
                 * @param other the other instance
                 * @return KeyStorageProvider& *this, containing the contents of other
                 */
                KeyStorageProvider& operator= (const KeyStorageProvider &&other)=default;
            };
        }
    }
}

#endif //ARA_CRYPTO_KEYS_KEY_STORAGE_PROVIDER_H