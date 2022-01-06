#ifndef ARA_CRYPTO_X509_X509_CUSTOM_EXTENSION_PARSER_H
#define ARA_CRYPTO_X509_X509_CUSTOM_EXTENSION_PARSER_H

#include <utility>

#include "ara/core/string_view.h"
#include "ara/core/result.h"

#include "ara/crypto/cryp/common/mem_region.h"

namespace ara
{
    namespace crypto
    {
        namespace x509
        {
            /**
             * @brief [SWS_CRYPT_40932]
             * X.509 custom extensions parser Callback class to be implemented by user. Implemented
             * functions get called by X509Provider::ParseCustomCertExtensions when parsing a certificate.
             * If any function of this class returns an error, the parsing will stop.
             */
            class X509CustomExtensionsParser
            {
            public:

                /**
                 * @brief [SWS_CRYPT_40934]
                 * Type alias
                 */
                using NumberOfUnusedBits = std::uint8_t;

                /**
                 * @brief [SWS_CRYPT_40935]
                 * Type alias 
                 */
                using BitString = std::pair<ara::crypto::ReadOnlyMemRegion, NumberOfUnusedBits>;

                /**
                 * @brief [SWS_CRYPT_40941]
                 * Type alias
                 */
                using GeneralizedTime = ara::core::StringView;

                /**
                 * @brief [SWS_CRYPT_40940]
                 * Type alias
                 */
                using Ia5String = ara::core::StringView;

                /**
                 * @brief [SWS_CRYPT_40933]
                 * Type alias
                 */
                using Integer = ara::crypto::ReadOnlyMemRegion;

                /**
                 * @brief [SWS_CRYPT_40936]
                 * Type alias
                 */
                using OctetString = ara::crypto::ReadOnlyMemRegion;

                /**
                 * @brief [SWS_CRYPT_40937]
                 * Type alias
                 */
                using Oid = ara::core::StringView;

                /**
                 * @brief [SWS_CRYPT_40939]
                 * Type alias
                 */
                using PrintableString = ara::core::StringView;

                /**
                 * @brief [SWS_CRYPT_40942]
                 * Type alias
                 */
                using UtcTime = ara::core::StringView;

                /**
                 * @brief [SWS_CRYPT_40938]
                 * Type alias
                 */
                using Utf8String = ara::crypto::ReadOnlyMemRegion;

                /**
                 * @brief [SWS_CRYPT_40922]
                 * Called when a bit string is encountered.
                 * @param[in] parsed_bit_string Parsed bit string value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnBitString (BitString parsed_bit_string) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40920]
                 * Called when a boolean is encountered.
                 * @param[in] parsed_bool Parsed boolean value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnBool (bool parsed_bool) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40929]
                 * Called when a generalized time is encountered.
                 * @param[in] parsed_generalized_time Parsed generalized time value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnGeneralizedTime (GeneralizedTime parsed_generalized_time) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40928]
                 * Called when an IA5 string is encountered.
                 * @param[in] parsed_ia5_string Parsed IA5 string value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnIa5String (Ia5String parsed_ia5_string) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40921]
                 * Called when an integer is encountered.
                 * @param[in] parsed_integer Parsed integer value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnInteger (Integer parsed_integer) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40924]
                 * Called when a NULL is encountered.
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnNull () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40923]
                 * Called when an octet string is encountered.
                 * @param[in] parsed_octet_string Parsed octet string value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnOctetString (OctetString parsed_octet_string) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40925]
                 * Called when an oid is encountered.
                 * @param[in] parsed_oid Parsed oid value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnOid (Oid parsed_oid) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40931]
                 * Called when the parsing is completed.
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnParsingEnd () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40927]
                 * Called when a printable string is encountered.
                 * @param parsed_printable_string Parsed printable string value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnPrintableString (PrintableString parsed_printable_string) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40917]
                 * Called when a sequence ends.
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnSequenceEnd () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40916]
                 * Called when a sequence starts.
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnSequenceStart () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40919]
                 * Called when a set ends.
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnSetEnd () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40918]
                 * Called when a set starts.
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnSetStart () noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40930]
                 * Called when a UTC time is encountered.
                 * @param[in] parsed_utc_time Parsed UTC time value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnUtcTime (UtcTime parsed_utc_time) noexcept=0;

                /**
                 * @brief [SWS_CRYPT_40926]
                 * Called when an UTF8 string is encountered.
                 * @param[in] parsed_utf8_string Parsed UTF8 string value
                 * @return ara::core::Result<void> 
                 * @exception CryptoErrorDomain::kRuntimeFault Indicates an error to the parser to stop parsing
                 */
                virtual ara::core::Result<void> OnUtf8String (Utf8String parsed_utf8_string) noexcept=0;
            };
        }
    }
}

#endif // ARA_CRYPTO_X509_X509_CUSTOM_EXTENSION_PARSER_H