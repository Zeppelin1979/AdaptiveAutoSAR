#ifndef ARA_CRYPTO_CRYP_SYMMETRIC_BLOCK_CIPHER_CTX_H
#define ARA_CRYPTO_CRYP_SYMMETRIC_BLOCK_CIPHER_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_23700]
             * Interface of a Symmetric Block Cipher Context with padding.
             */
            class SymmetricBlockCipherCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_23701]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<SymmetricBlockCipherCtx>;

                /**
                 * @brief [SWS_CRYPT_23702]
                 * Get CryptoService instance.
                 * @return CryptoService::Uptr 
                 */
                virtual CryptoService::Uptr GetCryptoService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23711]
                 * Get the kind of transformation configured for this context: kEncrypt or kDecrypt.
                 * @return ara::core::Result<CryptoTransform> CryptoTransform
                 * @exception CryptoErrorDomain::kUninitializedContext if SetKey() has not been called yet.
                 */
                virtual ara::core::Result<CryptoTransform> GetTransformation () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23716]
                 * Process (encrypt / decrypt) an input block according to the configuration.
                 * @param[in] in the input data block
                 * @param[in] suppressPadding if true then this method doesn’t apply padding, hence the input buffer be of the same size as the block-size, i.e. either the data to be processed exactly fits the block-size or the user must apply padding to the same effect.
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > the output buffer containing the transformation result
                 * @exception CryptoErrorDomain::kInvalidInputSize if the boolean parameter \ARApiRef{suppressPadding} was set to TRUE and the provided input buffer does not match the block-size.
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by calling SetKey()
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23717]
                 * Process (encrypt / decrypt) an input block according to the configuration.
                 * @tparam Alloc a custom allocator type of the output container
                 * @param[in] in the input data block
                 * @param[in] suppressPadding if true then the method doesn’t apply the padding, but the payload should fill the whole block of the plain data
                 * @return ara::core::Result<ByteVector<Alloc> > the managed container for output block
                 * @exception CryptoErrorDomain::kIncorrectInputSize if the mentioned above rules about the input size is violated
                 * @exception CryptoErrorDomain::kInsufficientCapacity if the out.size() is not enough to store the transformation result
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by calling SetKey()
                  */
                template <typename Alloc = <implementation-defined>>
                ara::core::Result<ByteVector<Alloc> > ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept;

                /**
                 * @brief [SWS_CRYPT_23715]
                 * Process (encrypt / decrypt) an input block according to the configuration. The in must have a
                 * size that is divisible by the block size (see GetBlockSize()). The pointer to the input buffer must
                 * be aligned to the block-size boundary!
                 * @param[in] in an input data buffer
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > an output data buffer
                 * @exception CryptoErrorDomain::kInvalidInputSize if size of the input buffer is not divisible by the block size (see GetBlockSize())
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by calling SetKey()
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ProcessBlocks (ReadOnlyMemRegion in) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23712]
                 * Indicate that the currently configured transformation accepts only complete blocks of input data.
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kUninitializedContext if the transformation direction of this context is configurable during an initialization, but the context was not initialized yet
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23710]
                 * Set (deploy) a key to the symmetric algorithm context.
                 * @param[in] key the source key object
                 * @param[in] transform the "direction" indicator: deploy the key for direct transformation (if true) or for reverse one (if false)
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kIncompatibleObject if the provided key object belongs to a different CryptoProvider instance
                 * @exception CryptoErrorDomain::kUsageViolation if the transformation type associated with this context (taking into account the direction specified by transform) is prohibited by the "allowed usage" restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const SymmetricKey &key, CryptoTransform transform=CryptoTransform::kEncrypt) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SYMMETRIC_BLOCK_CIPHER_CTX_H