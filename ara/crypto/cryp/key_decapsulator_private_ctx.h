#ifndef ARA_CRYPTO_CRYP_KEY_DECAPSULATOR_PRIVATE_CTX_H
#define ARA_CRYPTO_CRYP_KEY_DECAPSULATOR_PRIVATE_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_21400]
             * Asymmetric Key Encapsulation Mechanism (KEM) Private key Context interface.
             */
            class KeyDecapsulatorPrivateCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_21401]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<KeyDecapsulatorPrivateCtx>;

                /**
                 * @brief [SWS_CRYPT_21412]
                 * Decapsulate the keying data to be used for subsequent processing (e.g. secure
                 * communication). Produced SymmetricKey object has following attributes: session,
                 * non-exportable.
                 * @param[in] input an input buffer (its size should be equal GetEncapsulatedSize() bytes)
                 * @param[in] keyingDataAlgId algorithm ID of the returned symmetric key
                 * @param[in] kdf a context of a key derivation function, which should be used for KEK production
                 * @param[in] kekAlgId an algorithm ID of the KEK
                 * @param[in] allowedUsage the allowed usage scope of the returned symmetric key object (default = kAllowKdfMaterialAnyUsage)
                 * @return ara::core::Result<SymmetricKey::Uptrc> unique smart pointer of the symmetric key object instantiated from the decapsulated keying data
                 * @exception CryptoErrc::kUninitializedContext if the context was not initialized by a private key value
                 * @exception CryptoErrc::kInvalidArgument if kekAlgId or kdf are incompatible with this context
                 * @exception CryptoErrc::kInvalidInputSize if this context does not support the size of input
                 */
                virtual ara::core::Result<SymmetricKey::Uptrc> DecapsulateKey (ReadOnlyMemRegion input, CryptoAlgId keyingDataAlgId, KeyDerivationFunctionCtx &kdf, CryptoAlgId kekAlgId, ara::core::Optional< AllowedUsageFlags > allowedUsage) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21411]
                 * Decapsulate key material. Produced SecretSeed object has following attributes: session,
                 * non-exportable, AlgID = this KEM AlgID.
                 * @param[in] input a buffer with the encapsulated seed (its size should be equal GetEncapsulatedSize() bytes)
                 * @param[in] allowedUsage the allowed usage scope of the target seed (default = kAllowKdfMaterialAnyUsage)
                 * @return ara::core::Result<SecretSeed::Uptrc> unique smart pointer to SecretSeed object, which
                 * keeps the key material decapsulated from the input buffer
                 * @exception CryptoErrc::kUninitializedContext if the context was not initialized by a private key value
                 * @exception CryptoErrc::kInvalidInputSize if this context does not support the size of input
                 */
                virtual ara::core::Result<SecretSeed::Uptrc> DecapsulateSeed (ReadOnlyMemRegion input, ara::core::Optional< AllowedUsageFlags > allowedUsage) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21416]
                 * Get fixed size of the encapsulated data block.
                 * @return std::size_t size of the encapsulated data block in bytes
                 */
                virtual std::size_t GetEncapsulatedSize () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21402]
                 * Get ExtensionService instance.
                 * @return ExtensionService::Uptr 
                 */
                virtual ExtensionService::Uptr GetExtensionService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21415]
                 * Get entropy (bit-length) of the key encryption key (KEK) material. For RSA system the returned
                 * value corresponds to the length of module N (minus 1). For DH-like system the returned value
                 * corresponds to the length of module q (minus 1).
                 * @return std::size_t 
                 */
                virtual std::size_t GetKekEntropy () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21414]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21413]
                 * Set (deploy) a key to the key decapsulator private algorithm context.
                 * @param[in] key the source key object
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrc::kIncompatibleObject if the provided key object is incompatible with this private key context
                 * @exception CryptoErrc::kUsageViolation if the transformation type associated with this context is prohibited by the "allowed usage" restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const PrivateKey &key) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21512]
                 * Add a salt value stored in a (non-secret) ReadOnlyMemRegion.
                 * @param[in] salt a salt value (if used, it should be unique for each instance of the target key)
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> AddSalt (ReadOnlyMemRegion salt) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21513]
                 * Add a secret salt value stored in a SecretSeed object.
                 * @param[in] salt a salt value (if used, it should be unique for each instance of the target key)
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> AddSecretSalt (const SecretSeed &salt) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_KEY_DECAPSULATOR_PRIVATE_CTX_H