#ifndef ARA_CRYPTO_KEYS_UPDATES_OBSERVER_H
#define ARA_CRYPTO_KEYS_UPDATES_OBSERVER_H

#include "ara/crypto/keys/elementary_types.h"

namespace ara
{
    namespace crypto
    {
        namespace keys
        {
            /**
             * @brief [SWS_CRYPT_30200]
             * Definition of an "updates observer" interface.
             * The "updates observer" interface should be implemented by a consumer application, if a
             * software developer would like to get notifications about the slots’ content update events.
             */
            class UpdatesObserver
            {
            public:

                /**
                 * @brief [SWS_CRYPT_30201]
                 * Shared smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<UpdatesObserver>;

                /**
                 * @brief [SWS_CRYPT_30210]
                 * Destroy the Updates Observer object
                 * 
                 */
                virtual ~UpdatesObserver() noexcept=default;

                /**
                 * @brief [SWS_CRYPT_30211]
                 * Notification method that should be called if content of specified slots was changed. Key Storage
                 * engine should call this method in a dedicated thread. The provided list may include only slots
                 * subscribed for observing (during openning with the "User" permissions, i.e. for "reading" via a
                 * call of the method OpenAsUser()). Each slot number may present in the provided list only one
                 * time!
                 * @param[in] updatedSlots List of monitored slots that were updated after opening (for reading)
                 */
                virtual void OnUpdate (const TransactionScope &updatedSlots) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_30224]
                 * Copy-assign another UpdatesObserver to this instance.
                 * @param[in] other the other instance
                 * @return UpdatesObserver& *this, containing the contents of other
                 */
                UpdatesObserver& operator= (const UpdatesObserver &other)=default;

                /**
                 * @brief [SWS_CRYPT_30225]
                 * Move-assign another UpdatesObserver to this instance.
                 * @param[in] other the other instance
                 * @return UpdatesObserver& *this, containing the contents of other
                 */
                UpdatesObserver& operator= (const UpdatesObserver &&other)/*=default*/;
            };
        }
    }
}

#endif //ARA_CRYPTO_KEYS_UPDATES_OBSERVER_H