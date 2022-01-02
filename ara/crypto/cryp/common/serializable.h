#ifndef ARA_CRYPTO_SERIALIZABLE_H
#define ARA_CRYPTO_SERIALIZABLE_H

#include <cinttypes>
#include "ara/core/result.h"
#include "ara/core/vector.h"

namespace ara
{
    namespace crypto
    {
        /**
         * @brief [SWS_CRYPT_10700]
         * Serializable object interface.
         */
        class Serializable
        {
        public:
            /**
             * @brief [SWS_CRYPT_10701]
             * A container type for the encoding format identifiers.
             */
            using FormatId = std::uint32_t;

            /**
             * @brief [SWS_CRYPT_10751]
             * Export only raw value of an object.
             */
            static const FormatId kFormatRawValueOnly = 1;

            /**
             * @brief [SWS_CRYPT_10753]
             * Export PEM-encoded value of an object.
             */
            static const FormatId kFormatPemEncoded = 3;

            /**
             * @brief [SWS_CRYPT_10752]
             * Export DER-encoded value of an object.
             */
            static const FormatId kFormatDerEncoded = 2;

            /**
             * @brief [SWS_CRYPT_10750]
             * Default serialization format.
             */
            static const FormatId kFormatDefault = 0;

            /**
             * @brief [SWS_CRYPT_30204]
             * Copy-assign another Serializable to this instance.
             * @param[in] other the other instance
             * @return Serializable& *this, containing the contents of other
             */
            Serializable& operator= (const Serializable &other)=default;

            /**
             * @brief [SWS_CRYPT_30205]
             * Move-assign another Serializable to this instance.
             * @param[in] other the other instance
             * @return Serializable& *this, containing the contents of other
             */
            Serializable& operator= (Serializable &&other)=default;

            /**
             * @brief [SWS_CRYPT_10711]
             * Serialize itself publicly.
             * @param formatId the Crypto Provider specific identifier of the output format
             * @return ara::core::Result<ara::core::Vector<ara::core::Byte> > a buffer with the serialized object
             * @exception CryptoErrorDomain::kInsufficientCapacity if (output.empty() == false), but it’s capacity is less than required
             * @exception CryptoErrorDomain::kUnknownIdentifier if an unknown format ID was specified
             * @exception CryptoErrorDomain::kUnsupportedFormat if the specified format ID is not supported for this object type
             */
            virtual ara::core::Result<ara::core::Vector<ara::core::Byte> > ExportPublicly (FormatId formatId=kFormatDefault) const noexcept=0;
            
            /**
             * @brief [SWS_CRYPT_10712]
             * Serialize itself publicly. This method sets the size of the output container according to actually
             * saved value!
             * @tparam Alloc custom allocator type of the output container
             * @param[in] formatId the Crypto Provider specific identifier of the output format
             * @return ara::core::Result<ByteVector<Alloc> > pre-reserved managed container for the serialization output
             * @exception CryptoErrorDomain::kInsufficientCapacity if capacity of the output buffer is less than required
             * @exception CryptoErrorDomain::kUnknownIdentifier if an unknown format ID was specified
             * @exception CryptoErrorDomain::kUnsupportedFormat if the specified format ID is not supported for this object type
             */
            template <typename Alloc = <implementation-defined>>
            ara::core::Result<ByteVector<Alloc> > ExportPublicly (FormatId formatId=kFormatDefault) const noexcept;

            /**
             * @brief [SWS_CRYPT_10710]
             * Destroy the Serializable object
             * 
             */
            virtual ~Serializable () noexcept=default;
        };
    }
}

#endif // ARA_CRYPTO_SERIALIZABLE_H
