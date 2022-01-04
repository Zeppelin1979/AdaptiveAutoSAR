#ifndef ARA_CRYPTO_CRYP_KEY_AGREEMENT_PRIVATE_CTX_H
#define ARA_CRYPTO_CRYP_KEY_AGREEMENT_PRIVATE_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_21300]
             * Key Agreement Private key Context interface (Diffie Hellman or conceptually similar).
             */
            class KeyAgreementPrivateCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_21301]
                 * Unique smart pointer of this interface.
                 */
                using Uptr = std::unique_ptr<KeyAgreementPrivateCtx>;

                /**
                 * @brief [SWS_CRYPT_21312]
                 * Produce a common symmetric key via execution of the key-agreement algorithm between this
                 * private key and a public key of another side. Produced SymmetricKey object has following
                 * attributes: session, non-exportable. This method can be used for direct production of the target
                 * key, without creation of the intermediate SecretSeed object.
                 * @param[in] otherSideKey the public key of the other side of the Key-Agreement
                 * @param[in] targetAlgId identifier of the target symmetric algorithm (also defines a target key-length)
                 * @param[in] allowedUsage the allowed usage scope of the target key
                 * @param[in] kdf the optional context of a Key Derivation Function, which can be used for the target key production
                 * @param[in] salt an optional salt value (if used, it should be unique for each instance of the target key)
                 * @param[in] ctxLabel an optional application specific "context label" (it can identify purpose of the target key and/or communication parties)
                 * @return ara::core::Result<SymmetricKey::Uptrc> a unique pointer to SymmetricKey object, which
                 * contains the computed shared secret or key material produced by the Key-Agreement algorithm
                 * @exception CryptoErrc::kUninitializedContext if the context was not initialized by a key value
                 * @exception CryptoErrc::kIncompatibleObject if the public and private keys correspond to different algorithms
                 */
                virtual ara::core::Result<SymmetricKey::Uptrc> AgreeKey (const PublicKey &otherSideKey, CryptoAlgId targetAlgId, AllowedUsageFlags allowedUsage, ara::core::Optional< const KeyDerivationFunctionCtx::Uptr > kdf, ara::core::Optional< ReadOnlyMemRegion > salt,ara::core::Optional< ReadOnlyMemRegion > ctxLabel) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21311]
                 * Produce a common secret seed via execution of the key-agreement algorithm between this
                 * private key and a public key of another side. Produced SecretSeed object has following
                 * attributes: session, non-exportable, AlgID (this Key-Agreement Algorithm ID).
                 * @param[in] otherSideKey the public key of the other side of the Key-Agreement
                 * @param[in] allowedUsage the allowed usage scope of the target seed
                 * @return ara::core::Result<SecretSeed::Uptrc> unique pointer to SecretSeed object, which contains
                 * the key material produced by the Key-Agreement algorithm
                 * @exception CryptoErrc::kUninitializedContext if the context was not initialized by a key value
                 * @exception CryptoErrc::kIncompatibleObject if the public and private keys correspond to different algorithms
                 */
                virtual ara::core::Result<SecretSeed::Uptrc> AgreeSeed (const PublicKey &otherSideKey, ara::core::Optional< AllowedUsageFlags > allowedUsage) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21302]
                 * Get ExtensionService instance.
                 * @return ExtensionService::Uptr 
                 */
                virtual ExtensionService::Uptr GetExtensionService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21314]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21313]
                 * Set (deploy) a key to the key agreement private algorithm context.
                 * @param[in] key the source key object
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrc::kIncompatibleObject if the provided key object is incompatible with this private key context
                 * @exception CryptoErrc::kUsageViolation if the transformation type associated with this context is prohibited by the "allowed usage" restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const PrivateKey &key) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_KEY_AGREEMENT_PRIVATE_CTX_H