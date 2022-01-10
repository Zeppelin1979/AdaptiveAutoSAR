#ifndef ARA_CRYPTO_CRYP_STREAM_CIPHER_CTX_H
#define ARA_CRYPTO_CRYP_STREAM_CIPHER_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_23600]
             * Generalized Stream Cipher Context interface (it covers all modes of operation).
             */
            class StreamCipherCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_23601]
                 * Unique smart pointer of the interface
                 */
                using Uptr = std::unique_ptr<StreamCipherCtx>;

                /**
                 * @brief [SWS_CRYPT_23620]
                 * Count number of bytes now kept in the context cache. In block-wise modes if an application has
                 * supplied input data chunks with incomplete last block then the context saves the rest part of the
                 * last (incomplete) block to internal "cache" memory and wait a next call for additional input to
                 * complete this block.
                 * @return std::size_t number of bytes now kept in the context cache
                 */
                virtual std::size_t CountBytesInCache () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23621]
                 * Estimate maximal number of input bytes that may be processed for filling of an output buffer
                 * without overflow.
                 * @param[in] outputCapacity capacity of the output buffer
                 * @return std::size_t maximum number of input bytes
                 */
                std::size_t EstimateMaxInputSize (std::size_t outputCapacity) const noexcept;

                /**
                 * @brief [SWS_CRYPT_23622]
                 * Estimate minimal required capacity of the output buffer, which is enough for saving a result of
                 * input data processing.
                 * @param inputSize size of input data
                 * @param isFinal flag that indicates processing of the last data chunk (if true)
                 * @return std::size_t required capacity of the output buffer (in bytes)
                 */
                std::size_t EstimateRequiredCapacity (std::size_t inputSize, bool isFinal=false) const noexcept;

                /**
                 * @brief [SWS_CRYPT_23618]
                 * Processe the final part of message (that may be not aligned to the block-size boundary). If (Is
                 * BytewiseMode() == false) then it must be: bs = GetBlockSize(), out.size() >= (((in.size() + bs *
                 * ((CryptoTransform::kEncrypt == GetTransformation().Value()) ? 2 : 1)
                 * 1) / bs) * bs) If (IsBytewiseMode() == true) then it must be: out.size() >= in.size() The input and
                 * output buffers must not intersect! Usage of this method is mandatory for processing of the last
                 * data chunk in block-wise modes! This method may be used for processing of a whole message
                 * in a single call (in any mode)! in an input data buffer an output data buffer CryptoError
                 * Domain::kInsufficientCapacity if capacity of the output buffer is not enough CryptoError
                 * Domain::kInOutBuffersIntersect if the input and output buffers intersect CryptoErrorDomain::k
                 * ProcessingNotStarted if data processing was not started by a call ofthe Start() method
                 * @param[in] in an input data buffer
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > an output data buffer
                 * @exception CryptoErrorDomain::kInsufficientCapacity if capacity of the output buffer is not enough
                 * @exception CryptoErrorDomain::kInOutBuffersIntersect if the input and output buffers intersect
                 * @exception CryptoErrorDomain::kProcessingNotStarted if data processing was not started by a call of the Start() method
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > FinishBytes (ReadOnlyMemRegion in) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23619]
                 * Processe the final part of message (that may be not aligned to the block-size boundary). This
                 * method sets the size of the output container according to actually saved value. If (IsBytewise
                 * Mode() == false) then it must be: bs = GetBlockSize(), out.capacity() >= (((in.size() + bs *
                 * ((CryptoTransform::kEncrypt == GetTransformation.Value()) ? 2 : 1) - 1) / bs) * bs) If (Is
                 * BytewiseMode() == true) then it must be: out.capacity() >= in.size() Usage of this method is
                 * mandatory for processing of the last data chunk in block-wise modes! This method may be
                 * used for processing of a whole message in a single call (in any mode)!
                 * @tparam Alloc a custom allocator type of the output container
                 * @param[in] in an input data buffer The input buffer must not point inside the output container!
                 * @return ara::core::Result<ByteVector<Alloc> > a managed container for output data
                 * @exception CryptoErrorDomain::kInsufficientCapacity if capacity of the output buffer is not enough
                 * @exception CryptoErrorDomain::kInOutBuffersIntersect if the input and output buffers intersect
                 * @exception CryptoErrorDomain::kProcessingNotStarted if data processing was not started by a call of the Start() method
                 */
//                template <typename Alloc = <implementation-defined>>
//                ara::core::Result<ByteVector<Alloc> > FinishBytes (ReadOnlyMemRegion in) noexcept;

                /**
                 * @brief [SWS_CRYPT_23602]
                 * Get BlockService instance.
                 * @return BlockService::Uptr 
                 */
                virtual BlockService::Uptr GetBlockService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23611]
                 * Check the operation mode for the bytewise property.
                 * @return true if the mode can process messages the byte-by-byte (without padding up to the block boundary) and false if only the block-by-block (only full blocks can be processed, the padding is mandatory)
                 * @return false otherwise
                 */
                virtual bool IsBytewiseMode () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23624]
                 * Get the kind of transformation configured for this context: kEncrypt or kDecrypt.
                 * @return ara::core::Result<CryptoTransform> CryptoTransform
                 * @exception CryptoErrorDomain::kUninitializedContext if the transformation direction of this context is configurable during an iitialization, but the context was not initialized yet
                 */
                virtual ara::core::Result<CryptoTransform> GetTransformation () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23612]
                 * Check if the seek operation is supported in the current mode.
                 * @return true the seek operation is supported in the current mode
                 * @return false otherwise
                 */
                virtual bool IsSeekableMode () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23614]
                 * Processe initial parts of message aligned to the block-size boundary. It is a copy-optimized
                 * method that doesn’t use the internal cache buffer! It can be used only before processing of any
                 * non-aligned to the block-size boundary data. Pointers to the input and output buffers must be
                 * aligned to the block-size boundary! The input and output buffers may completely coincide, but
                 * they must not partially intersect!
                 * 
                 * @param[in] in an input data buffer
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > an output data buffer
                 * @exception CryptoErrorDomain::kIncompatibleArguments if sizes of the input and output buffers are not equal
                 * @exception CryptoErrorDomain::kInvalidInputSize if size of the input buffer is not divisible by the block size (see GetBlockSize())
                 * @exception CryptoErrorDomain::kInOutBuffersIntersect if the input and output buffers partially intersect
                 * @exception CryptoErrorDomain::kInvalidUsageOrder if this method is called after processing of non-aligned data (to the block-size boundary)
                 * @exception CryptoErrorDomain::kProcessingNotStarted if data processing was not started by a call of the Start() method
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ProcessBlocks (ReadOnlyMemRegion in) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23615]
                 * Processe initial parts of message aligned to the block-size boundary. It is a copy-optimized
                 * method that doesn’t use internal cache buffer! It can be used up to first non-block aligned data
                 * processing. Pointer to the input-output buffer must be aligned to the block-size boundary!
                 * @param[in,out] inOut an input and output data buffer, i.e. the whole buffer should be updated
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kInvalidInputSize if size of the inOut buffer is not divisible by the block size (see GetBlockSize())
                 * @exception CryptoErrorDomain::kInvalidUsageOrder if this method is called after processing of non-aligned data (to the block-size boundary)
                 * @exception CryptoErrorDomain::kProcessingNotStarted if data processing was not started by a call of the Start() method
                 */
                virtual ara::core::Result<void> ProcessBlocks (ReadWriteMemRegion inOut) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23616]
                 * Processe a non-final part of message (that is not aligned to the block-size boundary). If (Is
                 * BytewiseMode() == false) then it must be: bs = GetBlockSize(), out.size() >= (((in.size() + bs -
                 * 1) / bs) * bs) If (IsBytewiseMode() == true) then it must be: out.size() >= in.size() The input and
                 * output buffers must not intersect! This method is "copy inefficient", therefore it should be used
                 * only in conditions when an application cannot control the chunking of the original message!
                 * @param[in] in an input data buffer
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > an output data buffer
                 * @exception CryptoErrorDomain::kInsufficientCapacity if the output buffer has capacity insufficient for placing of the transformation result
                 * @exception CryptoErrorDomain::kInOutBuffersIntersect if the input and output buffers intersect
                 * @exception CryptoErrorDomain::kProcessingNotStarted if data processing was not started by a call of the Start() method
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ProcessBytes (ReadOnlyMemRegion in) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23617]
                 * Processes a non-final part of message (that is not aligned to the block-size boundary). This
                 * method sets size of the output container according to actually saved value. If (IsBytewiseMode()
                 * == false) then it must be: bs = GetBlockSize(), out.capacity() >= (((in.size() + bs - 1) / bs) * bs) If
                 * (IsBytewiseMode() == true) then it must be: out.capacity() >= in.size() This method is "copy
                 * inefficient", therefore it should be used only in conditions when an application cannot control the
                 * chunking of the original message! The input buffer must not point inside the output container!
                 * @tparam Alloc a custom allocator type of the output container
                 * @param[in] in an input data buffer
                 * @return ara::core::Result<ByteVector<Alloc> > a managed container for the output data
                 * @exception CryptoErrorDomain::kInsufficientCapacity if capacity of the output container is not enough
                 * @exception CryptoErrorDomain::kInOutBuffersIntersect if the input buffer points inside of the preallocated output container
                 * @exception CryptoErrorDomain::kProcessingNotStarted if data processing was not started by a call of the Start() method
                 */
//                template <typename Alloc = <implementation-defined>>
//                ara::core::Result<ByteVector<Alloc> > ProcessBytes (ReadOnlyMemRegion in) noexcept;

                /**
                 * @brief [SWS_CRYPT_23627]
                 * Clear the crypto context.
                 * @return ara::core::Result<void> 
                 */
                virtual ara::core::Result<void> Reset () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23613]
                 * Set the position of the next byte within the stream of the encryption/decryption gamma.
                 * @param offset the offset value in bytes, relative to begin or current position in the gamma stream
                 * @param fromBegin the starting point for positioning within the stream: from begin (if true) or from current position (if false)
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kUnsupported if the seek operation is not supported by the current mode
                 * @exception CryptoErrorDomain::kProcessingNotStarted if data processing was not started by a call of the Start() method
                 * @exception CryptoErrorDomain::kBelowBoundary if the offset value is incorrect (in context of the the fromBegin argument), i.e. it points before begin of the stream (note: it is an optional error condition)
                 * @exception CryptoErrorDomain::kInvalidArgument if the offset is not aligned to the required boundary (see IsBytewiseMode())
                 */
                virtual ara::core::Result<void> Seek (std::int64_t offset, bool fromBegin=true) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23623]
                 * Set (deploy) a key to the stream chiper algorithm context.
                 * @param[in] key the source key object
                 * @param[in] transform the "direction" indicator: deploy the key for direct transformation (if true) or for reverse one (if false)
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kIncompatibleObject if the provided key object is incompatible with this symmetric key context
                 * @exception CryptoErrorDomain::kUsageViolation if the transformation type associated with this context (taking into account the direction specified by transform) is prohibited by the "allowed usage" restrictions of provided key object
                 */
                virtual ara::core::Result<void> SetKey (const SymmetricKey &key, CryptoTransform transform=CryptoTransform::kEncrypt) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23625]
                 * Initialize the context for a new data stream processing or generation (depending from the
                 * primitive). If IV size is greater than maximally supported by the algorithm then an
                 * implementation may use the leading bytes only from the sequence.
                 * @param iv an optional Initialization Vector (IV) or "nonce" value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by deploying a key
                 * @exception CryptoErrorDomain::kInvalidInputSize if the size of provided IV is not supported (i.e. if it is not enough for the initialization)
                 * @exception CryptoErrorDomain::kUnsupported if the base algorithm (or its current implementation) principally doesn’t support the IV variation, but provided IV value is not empty, i.e. if (iv.empty() == false)
                 */
                virtual ara::core::Result<void> Start (ReadOnlyMemRegion iv=ReadOnlyMemRegion()) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_23626]
                 * Initialize the context for a new data stream processing or generation (depending from the
                 * primitive). If IV size is greater than maximally supported by the algorithm then an
                 * implementation may use the leading bytes only from the sequence.
                 * @param iv the Initialization Vector (IV) or "nonce" object
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kUninitializedContext if the context was not initialized by deploying a key
                 * @exception CryptoErrorDomain::kInvalidInputSize if the size of provided IV is not supported (i.e. if it is not enough for the initialization)
                 * @exception CryptoErrorDomain::kUnsupported if the base algorithm (or its current implementation) principally doesn’t support the IV variation, but provided IV value is not empty, i.e. if (iv.empty() == false)
                 * @exception CryptoErrorDomain::kUsageViolation if this transformation type is prohibited by the "allowed usage" restrictions of the provided Secret Seed object
                 */
                virtual ara::core::Result<void> Start (const SecretSeed &iv) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_STREAM_CIPHER_CTX_H