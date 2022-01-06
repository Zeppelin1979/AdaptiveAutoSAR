#ifndef ARA_CRYPTO_CRYP_COMMON_VOLATILE_TRUSTED_CONTAINER_H
#define ARA_CRYPTO_CRYP_COMMON_VOLATILE_TRUSTED_CONTAINER_H

#include <memory>
#include "ara/crypto/cryp/common/io_interface.h"

namespace ara
{
    namespace crypto
    {
        /**
         * @brief [SWS_CRYPT_10850]
         * This explicit interface of a volatile Trusted Container is used for buffering CryptoAPI objects in
         * RAM. This class represents a "smart buffer" in that it provides access to the IOInterface, which
         * can be used for querying meta-data of the buffer content.
         */
        class VolatileTrustedContainer
        {
        private:
            IOInterface& mIOInterface;

        public:
            /**
             * @brief [SWS_CRYPT_10852]
             * Unique smart pointer of the interface.
             */
            using Uptr = std::unique_ptr<VolatileTrustedContainer>;

            /**
             * @brief [SWS_CRYPT_30206]
             * Copy-assign another VolatileTrustedContainer to this instance.
             * @param[in] other the other instance
             * @return VolatileTrustedContainer& *this, containing the contents of other
             */
            VolatileTrustedContainer& operator= (const VolatileTrustedContainer &other)=default;

            /**
             * @brief [SWS_CRYPT_30207]
             * Move-assign another VolatileTrustedContainer to this instance.
             * @param[in] other the other instance
             * @return VolatileTrustedContainer& *this, containing the contents of other
             */
            VolatileTrustedContainer& operator= (VolatileTrustedContainer &&other)=default;

            /**
             * @brief [SWS_CRYPT_10853]
             * Retrieve the IOInterface used for importing/exporting objects into this container.
             * @return IOInterface& a reference to the IOInterface of this containe
             */
            virtual IOInterface& GetIOInterface () const noexcept=0;

            /**
             * @brief [SWS_CRYPT_10851] 
             * Destroy the Volatile Trusted Container object
             * 
             */
            virtual ~VolatileTrustedContainer () noexcept=default;
        };
    }
}

#endif // ARA_CRYPTO_CRYP_COMMON_VOLATILE_TRUSTED_CONTAINER_H
