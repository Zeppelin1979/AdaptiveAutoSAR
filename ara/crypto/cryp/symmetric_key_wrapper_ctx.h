#ifndef ARA_CRYPTO_CRYP_SYMMETRIC_KEY_WRAPPER_CTX_H
#define ARA_CRYPTO_CRYP_SYMMETRIC_KEY_WRAPPER_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"
#include "ara/crypto/cryp/cryobj/symmetric_key.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_24000]
             * Context of a symmetric key wrap algorithm (for AES it should be compatible with RFC3394 or
             * RFC5649). The public interface of this context is dedicated for raw key material wrapping/
             * unwrapping, i.e. without any meta-information assigned to the key material in source crypto
             * object. But additionally this context type should support some "hidden" low-level methods
             * suitable for whole crypto object exporting/importing. Key Wrapping of a whole crypto object
             * (including associated meta-information) can be done by methods: ExportSecuredObject() and
             * ImportSecuredObject(), but without compliance to RFC3394 or RFC5649.
             */
            class SymmetricKeyWrapperCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_24001]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<SymmetricKeyWrapperCtx>;

                /**
                 * @brief [SWS_CRYPT_24013]
                 * Calculate size of the wrapped key in bytes from original key length in bits. This method can be
                 * useful for some implementations different from RFC3394 / RFC5649.
                 * @param keyLength original key length in bits
                 * @return std::size_t size of the wrapped key in bytes
                 */
                virtual std::size_t CalculateWrappedKeySize (std::size_t keyLength) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24002]
                 * Get ExtensionService instance.
                 * @return ExtensionService::Uptr 
                 */
                virtual ExtensionService::Uptr GetExtensionService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24012]
                 * Get maximum length of the target key supported by the implementation. This method can be
                 * useful for some implementations different from RFC3394 / RFC5649.
                 * @return std::size_t maximum length of the target key in bits
                 */
                virtual std::size_t GetMaxTargetKeyLength () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24011]
                 * Get expected granularity of the target key (block size). If the class implements RFC3394 (KW
                 * without padding) then this method should return 8 (i.e. 8 octets = 64 bits). If the class
                 * implements RFC5649 (KW with padding) then this method should return 1 (i.e. 1 octet = 8 bits)
                 * @return std::size_t size of the block in bytes
                 */
                virtual std::size_t GetTargetKeyGranularity () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24019]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24018]
                 * Set (deploy) a key to the symmetric key wrapper algorithm context.
                 * @param[in] key the source key object
                 * @param[in] transform the "direction" indicator: deploy the key for direct transformation (if true) or for reverse one (if false)
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kIncompatibleObject if the provided key object is incompatible with this symmetric key context
                 * @exception CryptoErrorDomain::kUsageViolation if the transformation type associated with this context (taking into account the direction specified by transform) is prohibited by the "allowed usage" restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const SymmetricKey &key, CryptoTransform transform) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24017]
                 * Execute the "key unwrap" operation for provided BLOB and produce a Key object of expected
                 * type. For additional details see UnwrapKey()
                 * @tparam ExpectedKey the expected type of concrete key
                 * @param[in] wrappedKey a memory region that contains wrapped key
                 * @param[in] algId an identifier of the target symmetric crypto algorithm
                 * @param[in] allowedUsage bit-flags that define a list of allowed transformations’ types in which the target key can be used
                 * @return ara::core::Result<typename ExpectedKey::Uptrc> unique smart pointer to ExpectedKey object, which keeps unwrapped key material
                 * @exception CryptoErrorDomain::kInvalidInputSize if the size of provided wrapped key is unsupported
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by a key value
                 */
                template <typename ExpectedKey>
                ara::core::Result<typename ExpectedKey::Uptrc> UnwrapConcreteKey (ReadOnlyMemRegion wrappedKey, AlgId algId, AllowedUsageFlags allowedUsage) noexcept;

                /**
                 * @brief [SWS_CRYPT_24016]
                 * Execute the "key unwrap" operation for provided BLOB and produce Key object. This method
                 * should be compliant to RFC3394 or RFC5649, if implementation is based on the AES block
                 * cipher and applied to an AES key. The created Key object has following attributes: session and
                 * non-exportable (because it was imported without meta-information)! SymmetricKey may be
                 * unwrapped in following way: SymmetricKey::Uptrc key = SymmetricKey::Cast(Unwrap
                 * Key(wrappedKey, ...)); PrivateKey may be unwrapped in following way: PrivateKey::Uptrc key =
                 * PrivateKey::Cast(UnwrapKey(wrappedKey, ...)); In both examples the Cast() method may
                 * additionally throw the BadObjectTypeException if an actual type of the unwrapped key differs
                 * from the target one!
                 * @param[in] wrappedKey a memory region that contains wrapped key
                 * @param[in] algId an identifier of the target symmetric crypto algorithm
                 * @param[in] allowedUsage bit-flags that define a list of allowed transformations’ types in which the target key can be used
                 * @return ara::core::Result<RestrictedUseObject::Uptrc> unique smart pointer to Key object, which keeps unwrapped key material
                 * @exception CryptoErrorDomain::kInvalidInputSize if the size of provided wrapped key is unsupported
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by a key value
                 */
                virtual ara::core::Result<RestrictedUseObject::Uptrc> UnwrapKey (ReadOnlyMemRegion wrappedKey, AlgId algId, AllowedUsageFlags allowedUsage) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24015]
                 * Execute the "key unwrap" operation for provided BLOB and produce SecretSeed object. This
                 * method should be compliant to RFC3394 or RFC5649, if implementation is based on the AES
                 * block cipher and applied to an AES key material. The created SecretSeed object has following
                 * attributes: session and non-exportable (because it was imported without meta-information).
                 * @param[in] wrappedSeed a memory region that contains wrapped seed
                 * @param[in] targetAlgId the target symmetric algorithm identifier (also defines a target seed-length)
                 * @param[in] allowedUsage allowed usage scope of the target seed
                 * @return ara::core::Result<SecretSeed::Uptrc> unique smart pointer to SecretSeed object, which keeps unwrapped key material
                 * @exception CryptoErrorDomain::kInvalidInputSize if the size of provided wrapped seed is unsupported
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by a key value
                 */
                virtual ara::core::Result<SecretSeed::Uptrc> UnwrapSeed (ReadOnlyMemRegion wrappedSeed, AlgId targetAlgId, SecretSeed::Usage allowedUsage) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_24014]
                 * Execute the "key wrap" operation for the provided key material. This method should be
                 * compliant to RFC3394 or RFC5649, if an implementation is based on the AES block cipher and
                 * applied to an AES key. Method CalculateWrappedKeySize() can be used for size calculation of
                 * the required output buffer.
                 * @param[in] key a key that should be wrapped
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > 
                 * @exception CryptoErrorDomain::kInsufficientCapacity if the size of the wrapped buffer is not enough for storing the result
                 * @exception CryptoErrorDomain::kInvalidInputSize if the key object has an unsupported length
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by a key value
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > WrapKeyMaterial (const RestrictedUseObject &key) const noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SYMMETRIC_KEY_WRAPPER_CTX_H