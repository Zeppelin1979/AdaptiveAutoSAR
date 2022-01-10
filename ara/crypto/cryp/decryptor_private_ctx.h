#ifndef ARA_CRYPTO_CRYP_DECRIPTOR_PRIVATE_CTX_H
#define ARA_CRYPTO_CRYP_DECRIPTOR_PRIVATE_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

#include "ara/crypto/cryp/crypto_service.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_20800]
             * Asymmetric Decryption Private key Context interface.
             */
            class DecryptorPrivateCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_20801]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<DecryptorPrivateCtx>;

                /**
                 * @brief [SWS_CRYPT_20802]
                 * Get CryptoService instance.
                 * @return CryptoService::Uptr 
                 */
                virtual CryptoService::Uptr GetCryptoService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20812]
                 * Process (encrypt / decrypt) an input block according to the cryptor configuration. Encryption
                 * with (suppressPadding == true) expects that: in.size() == GetMaxInputSize(true) && out.size()
                 * >= GetMaxOutputSize(true). Encryption with (suppressPadding == false) expects that: in.size()
                 * <= GetMaxInputSize(false) && in.size() > 0 && out.size() >= GetMaxOutputSize(false).
                 * Decryption expects that: in.size() == GetMaxInputSize() && out.size() >= GetMaxOutput
                 * Size(suppressPadding). The case (out.size() < GetMaxOutputSize()) should be used with
                 * caution, only if you are strictly certain about the size of the output data! In case of (suppress
                 * Padding == true) the actual size of plain text should be equal to full size of the plain data block
                 * (defined by the algorithm)!
                 * @param[in] in the input data block
                 * @param[in] suppressPadding if true then the method doesn’t apply the padding, but the payload should fill the whole block of the plain data
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > actual size of output data (it always <= out.size()) or 0 if the input data block has incorrect content
                 * @exception CryptoErrorDomain::kIncorrectInputSize if the mentioned above rules about the input size is violated
                 * @exception CryptoErrorDomain::kInsufficientCapacity if the out.size() is not enough to store the transformation result
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by a key value
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20813]
                 * Process (encrypt / decrypt) an input block according to the cryptor configuration. This method
                 * sets the size of the output container according to actually saved value! Encryption with
                 * (suppressPadding == true) expects what: in.size() == GetMaxInputSize(true) && out.capacity()
                 * >= GetMaxOutputSize(true). Encryption with (suppressPadding == false) expects what:
                 * in.size() <= GetMaxInputSize(false) && in.size() > 0 && out.capacity() >= GetMaxOutput
                 * Size(false). Decryption expects what: in.size() == GetMaxInputSize() && out.capacity() >= Get
                 * MaxOutputSize(suppressPadding). The case (out.capacity() < GetMaxOutputSize()) should be
                 * used with caution, only if you are strictly certain about the size of the output data! In case of
                 * (suppressPadding == true) the actual size of plain text should be equal to full size of the plain
                 * data block (defined by the algorithm)!
                 * @tparam Alloc 
                 * @param[in] in the input data block
                 * @param[in] suppressPadding if true then the method doesn’t apply the padding, but the payload should fill the whole block of the plain data
                 * @return ara::core::Result<ByteVector<Alloc> > the managed container for output block
                 * @exception CryptoErrorDomain::kIncorrectInputSize if the mentioned above rules about the input size is violated
                 * @exception CryptoErrorDomain::kInsufficientCapacity if the out.size() is not enough to store the transformation result
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by a key value
                 */
/*                template <typename Alloc = <implementation-defined>>
                ara::core::Result<ByteVector<Alloc> > ProcessBlock (ReadOnlyMemRegion in, bool suppressPadding=false) const noexcept;*/

                /**
                 * @brief [SWS_CRYPT_20811]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_20810]
                 * Set (deploy) a key to the decryptor private algorithm context.
                 * @param[in] key the source key object
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kIncompatibleObject if the provided key object is incompatible with this symmetric key context
                 * @exception CryptoErrorDomain::kUsageViolation if the transformation type associated with this context is prohibited by the "allowed usage" restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const PrivateKey &key) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_DECRIPTOR_PRIVATE_CTX_H