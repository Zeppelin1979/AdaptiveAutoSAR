#ifndef ARA_CRYPTO_CRYP_KEY_DERIVATION_FUNCTION_CTX_H
#define ARA_CRYPTO_CRYP_KEY_DERIVATION_FUNCTION_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_21500]
             * Key Derivation Function interface.
             */
            class KeyDerivationFunctionCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_21501]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<KeyDerivationFunctionCtx>;

                /**
                 * @brief [SWS_CRYPT_21514]
                 * Configure the number of iterations that will be applied by default. Implementation can restrict
                 * minimal and/or maximal value of the iterations number.
                 * @param[in] iterations the required number of iterations of the base function (0 means implementation default number)
                 * @return std::uint32_t actual number of the iterations configured in the context now (after this method call)
                 */
                virtual std::uint32_t ConfigIterations (std::uint32_t iterations=0) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21515]
                 * Derive a symmetric key from the provided key material and provided context configuration.
                 * @param[in] isSession the "session" (or "temporary") attribute for the target key (if true)
                 * @param[in] isExportable the exportability attribute for the target key (if true)
                 * @return ara::core::Result<SymmetricKey::Uptrc> unique smart pointer to the created instance of derived symmetric key
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not sufficiently initialized
                 */
                virtual ara::core::Result<SymmetricKey::Uptrc> DeriveKey (bool isSession=true, bool isExportable=false) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21516]
                 * 
                 * @param[in] isSession the "session" (or "temporary") attribute for the target key (if true)
                 * @param[in] isExportable the exportability attribute for the target key (if true)
                 * @return ara::core::Result<SecretSeed::Uptrc> unique smart pointer to the created SecretSeed object
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not sufficiently initialized
                 */
                virtual ara::core::Result<SecretSeed::Uptrc> DeriveSeed (bool isSession=true, bool isExportable=false) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21524]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21517]
                 * Get ExtensionService instance.
                 * @return ExtensionService::Uptr 
                 */
                virtual ExtensionService::Uptr GetExtensionService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21519]
                 * Get the fixed size of the target key ID required by diversification algorithm. Returned value is
                 * constant for each instance of the interface, i.e. independent from configuration by.
                 * Returned value is constant for this instance of the key derivation context, i.e. independent from
                 * configuration by
                 * @return std::size_t size of the key ID in bytes the @c Init() call.
                 */
                virtual std::size_t GetKeyIdSize () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21520]
                 * Get the symmetric algorithm ID of target (slave) key. If the context was not configured yet by a
                 * call of the Init() method then kAlgIdUndefined should be.
                 * @return AlgId the symmetric algorithm ID of the target key,
                 * configured by the last call of the Init() method returned.
                 */
                virtual AlgId GetTargetAlgId () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21521]
                 * Get allowed key usage of target (slave) key. The returned value depends on the source
                 * key-material allowed usage flags and the argument allowedUsage of last call of the Init()
                 * method. If the context has not yet been configured by a call of the Init() method, the allowed
                 * usage flags of the source key-material shall be returned. If the context has not yet been
                 * configured by a call of the Init() method and no source key-material has been set either, kAllow
                 * KdfMaterialAnyUsage shall be returned.
                 * @return AllowedUsageFlags allowed key usage bit-flags of target keys
                 */
                virtual AllowedUsageFlags GetTargetAllowedUsage () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21522]
                 * Get the bit-length of target (diversified) keys. Returned value is configured by the context
                 * factory method, i.e. independent from configuration by.
                 * @return std::size_t the length of target (diversified) key in bits the @c Init() calls.
                 */
                virtual std::size_t GetTargetKeyBitLength () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21523]
                 * Initialize this context by setting at least the target key ID. The byte sequence provided via
                 * argument ctxLabel can include a few fields with different meaning separated by single 0x00
                 * byte. If (targetAlgId == kAlgIdAny) then a diversified key can be loaded to any symmetric
                 * context that supports the same key length (if the "allowed usage" flags are also satisfied)!
                 * @param[in] targetKeyId ID of the target key
                 * @param[in] targetAlgId the identifier of the target symmetric crypto algorithm
                 * @param[in] allowedUsage bit-flags that define a list of allowed transformations’ types in which the target key may be used
                 * @param[in] ctxLabel an optional application specific "context label" (this can identify the purpose of the target key and/or communication parties)
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kIncompatibleArguments if targetAlgId specifies a cryptographic algorithm different from a symmetric one with key length equal to GetTargetKeyBitLength();
                 * @exception CryptoErrorDomain::kUsageViolation if allowedUsage specifies more usages of the derived key-material than the source key-material, i.e. usage of the derived key-material may not be expanded beyond what the source key-material allows
                 */
                virtual ara::core::Result<void> Init (ReadOnlyMemRegion targetKeyId, AlgId targetAlgId=kAlgIdAny, AllowedUsageFlags allowedUsage=kAllowKdfMaterialAnyUsage, ReadOnlyMemRegion ctxLabel=ReadOnlyMemRegion()) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_21525]
                 * Set (deploy) key-material to the key derivation algorithm context.
                 * @param[in] sourceKM the source key-material
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kIncompatibleObject if the provided key object is incompatible with this symmetric key context
                 * @exception CryptoErrorDomain::kUsageViolation if deriving a key is prohibited by the "allowed usage" restrictions of the provided source key-material
                 * @exception CryptoErrorDomain::kBruteForceRisk if key length of the sourceKm is below of an internally defined limitation
                 */
                virtual ara::core::Result<void> SetSourceKeyMaterial (const RestrictedUseObject &sourceKM) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_KEY_DERIVATION_FUNCTION_CTX_H