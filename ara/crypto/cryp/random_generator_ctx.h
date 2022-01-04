#ifndef ARA_CRYPTO_CRYP_RANDOM_GENERATOR_CTX_H
#define ARA_CRYPTO_CRYP_RANDOM_GENERATOR_CTX_H

#include "ara/crypto/cryp/cryobj/crypto_context.h"

namespace ara
{
    namespace crypto
    {
        namespace cryp
        {
            /**
             * @brief [SWS_CRYPT_22900]
             * Interface of Random Number Generator Context.
             */
            class RandomGeneratorCtx : public CryptoContext
            {
            public:

                /**
                 * @brief [SWS_CRYPT_22901]
                 * Shared smart pointer of the interface.
                 */
                using Uptr = std::unique_ptr<RandomGeneratorCtx>;

                /**
                 * @brief [SWS_CRYPT_22914]
                 * Update the internal state of the RNG by mixing it with the provided additional entropy. This
                 * method is optional for implementation. An implementation of this method may "accumulate"
                 * provided entropy for future use.
                 * @param[in] entropy a memory region with the additional entropy value
                 * @return true if the method is supported and the entropy has been updated successfully
                 * @return false otherwise
                 */
                virtual bool AddEntropy (ReadOnlyMemRegion entropy) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22915]
                 * Return an allocated buffer with a generated random sequence of the requested size.
                 * @param[in] count number of random bytes to generate
                 * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > a buffer filled with the generated random sequence
                 * @exception CryptoErrorDomain::kUninitializedContext if this context implements a local RNG (i.e., the RNG state is controlled by the application), and has to be seeded by the application because it either has not already been seeded or ran out of entropy.
                 * @exception CryptoErrorDomain::kBusyResource if this context implements a global RNG (i.e., the RNG state is controlled by the stack and not the application) that is currently out-of-entropy and therefore cannot provide the requested number of random bytes
                 */
                virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > Generate (std::uint32_t count) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22902]
                 * Get ExtensionService instance.
                 * @return ExtensionService::Uptr 
                 */
                virtual ExtensionService::Uptr GetExtensionService () const noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22911]
                 * Set the internal state of the RNG using the provided seed.
                 * @param[in] seed a memory region with the seed value
                 * @return true if the method is supported and the state has been set successfully
                 * @return false otherwise
                 */
                virtual bool Seed (ReadOnlyMemRegion seed) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22912]
                 * Set the internal state of the RNG using the provided seed.
                 * @param[in] seed a memory region with the seed value
                 * @return true if the method is supported and the state has been set successfully
                 * @return false otherwise
                 */
                virtual bool Seed (const SecretSeed &seed) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_22913]
                 * Set the internal state of the RNG using the provided seed.
                 * @param[in] key a SymmetricKey with the key used as seed value
                 * @return true if the method is supported and the key has been set successfully
                 * @return false otherwise 
                 */
                virtual bool SetKey (const SymmetricKey &key) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_CRYP_RANDOM_GENERATOR_CTX_H
