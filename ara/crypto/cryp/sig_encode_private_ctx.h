#ifndef ARA_CRYPTO_CRYP_SIG_ENCODE_PRIVATE_CTX_H
#define ARA_CRYPTO_CRYP_SIG_ENCODE_PRIVATE_CTX_H

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_23200]
             * A private key context for asymmetric signature calculation and short message encoding
             * (RSA-like). Restricted groups of trusted subscribers can use this primitive for simultaneous
             * provisioning of confidentiality, authenticity and non-repudiation of short messages, if the public
             * key is generated appropriately and kept in secret.
             */
            class SigEncodePrivateCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_23201]
                 * Unique smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<SigEncodePrivateCtx>;

                /**
                 * @brief [SWS_CRYPT_23210]
                 * Extension service member class.
                 * @return ExtensionService::Uptr 
                 */
                virtual ExtensionService::Uptr GetExtensionService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23213]
                 * Get maximum expected size of the input data block. If (IsEncryption() == false) then a value
                 * returned by this method is independent from the suppressPadding argument and it will be equal
                 * to the block size.
                 * @param[in] suppressPadding if true then the method calculates the size for the case when the whole space of the plain data block is used for the payload only
                 * @return std::size_t maximum size of the input data block in bytes
                 */
                virtual std::size_t GetMaxInputSize (bool suppressPadding=false) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23214]
                 * Get maximum possible size of the output data block. If (IsEncryption() == true) then a value
                 * returned by this method is independent from the suppressPadding argument and will be equal
                 * to the block size.
                 * @param[in] suppressPadding if true then the method calculates the size for the case when the whole space of the plain data block is used for the payload only
                 * @return std::size_t maximum size of the output data block in bytes
                 */
                virtual std::size_t GetMaxOutputSize (bool suppressPadding=false) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23215]
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
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > the output buffer actual size of output data 
                 * (it always <= out.size()) or 0 if the input data block has incorrect content
                 * @exception CryptoErrorDomain::kIncorrectInputSize if the mentioned above rules about the input size is violated
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by a key value
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > SignAndEncode (ReadOnlyMemRegion in) const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23216]
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
                 * @tparam Alloc a custom allocator type of the output container
                 * @param[in] in the input data block
                 * @return ara::core::Result<ByteVector<Alloc> > the managed container for output block
                 * @exception CryptoErrorDomain::kIncorrectInputSize if the mentioned above rules about the input size is violated
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by a key value
                 */
//                template <typename Alloc = <implementation-defined>>
//                ara::core::Result<ByteVector<Alloc> > SignAndEncode (ReadOnlyMemRegion in) const noexcept;

                /**
                 * @brief [SWS_CRYPT_23212]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23211]
                 * Set (deploy) a key to the sig encode private algorithm context.
                 * @param[in] key the source key object
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrc::kIncompatibleObject if the provided key object is incompatible with this symmetric key context
                 * @exception CryptoErrc::kUsageViolation if the transformation type associated with this context is prohibited by the "allowed usage" restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const PrivateKey &key) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_SIG_ENCODE_PRIVATE_CTX_H