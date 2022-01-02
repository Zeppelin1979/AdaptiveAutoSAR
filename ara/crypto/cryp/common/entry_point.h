#ifndef ARA_CRYPTO_ENTRY_POINT_H
#define ARA_CRYPTO_ENTRY_POINT_H

#include "ara/crypto/cryp/crypto_provider.h"
//#include "ara/crypto/cryp/key_storage_provider.h"
#include "ara/core/result.h"
#include "ara/core/vector.h"

#include <cinttypes>

namespace ara
{
    namespace crypto
    {
        /**
         * @brief [SWS_CRYPT_30001]
         * 128 bit secure counter made up of most significant and least significant quad-word of the
         * hardware counter.
         */
        struct SecureCounter
        {
            /**
             * @brief [SWS_CRYPT_30002]
             * least significant 64 bits
             */
            std::uint64_t mLSQW;

            /**
             * @brief [SWS_CRYPT_30003]
             * most significant 64 bits
             */
            std::uint64_t mMSQW;
        };

        /**
         * @brief [SWS_CRYPT_20099]
         * Factory that creates or return existing single instance of specific Crypto Provider. If (providerUid
         * == nullptr) then platform default provider should be loaded.
         * @param iSpecify the globally unique identifier of required Crypto Provider
         * @return cryp::CryptoProvider::Uptr unique smart pointer to loaded Crypto Provider
         */
        cryp::CryptoProvider::Uptr LoadCryptoProvider (const ara::core::InstanceSpecifier &iSpecify) noexcept;

        /**
         * @brief [SWS_CRYPT_30099]
         * Factory that creates or return existing single instance of the Key Storage Provider.
         * @return keys::KeyStorageProvider::Uptr unique smart pointer to loaded Key Storage Provider
         * @exception CryptoErrorDomain::kRuntimeFault if the Key Storage Provider instance cannot be created
         */
        keys::KeyStorageProvider::Uptr LoadKeyStorageProvider () noexcept;

        /**
         * @brief [SWS_CRYPT_40099]
         * Factory that creates or return existing single instance of the X.509 Provider. X.509 Provider
         * should use the default Crypto Provider for hashing and signature verification! Therefore when
         * you load the X.509 Provider, in background it loads the default Crypto Provider too.
         * @return x509::X509Provider::Uptr unique smart pointer to loaded X.509 Provider
         * @exception CryptoErrorDomain::kRuntimeFault if the X.509 Provider cannot be loaded
         */
        x509::X509Provider::Uptr LoadX509Provider () noexcept;

        /**
         * @brief [SWS_CRYPT_30098]
         * Return an allocated buffer with a generated random sequence of the requested size.
         * @param[in] count number of random bytes to generate
         * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > a buffer filled with the generated random sequence
         * @exception CryptoErrorDomain::kBusyResource if the used RNG is currently out-of-entropy and therefore cannot provide the requested number of random bytes
         */
        ara::core::Result<ara::core::Vector<ara::core::Byte> > GenerateRandomData (std::uint32_t count) noexcept;

        /**
         * @brief [SWS_CRYPT_20098]
         * Get current value of 128 bit Secure Counter supported by the Crypto Stack. Secure Counter is
         * a non-rollover monotonic counter that ensures incrementation of its value for each following
         * call. The Secure Counter is presented by two 64 bit components: Most Significant Quadword
         * (MSQW) and Least Significant Quadword (LSQW). During normal operation of the Crypto
         * Stack, the MSQW value is fixed (unchangeable) and only LSQW should be incremented. The
         * LSQW counter can be implemented in the "low-power" (always-powered-up) domain of the
         * main CPU, but the MSQW in the Flash/EEPROM storage. But the MSQW must be incremented
         * if the LSQW reaches the maximum value of all ones. Also the MSQW must be incremented
         * during reinitialisation of the whole Crypto Stack (e.g. if the "low-power" supply was interrupted
         * by some reason). Permission to execute this routine is subject of Identity and Access
         * Management control and may be restricted by application manifest!
         * 
         * @return ara::core::Result<SecureCounter> a SecureCounter struct made up of the two unsigned 64 bit values (LSQW and MSQW)
         */
        ara::core::Result<SecureCounter> GetSecureCounter () noexcept;
    }
}

#endif // ARA_CRYPTO_ENTRY_POINT_H
