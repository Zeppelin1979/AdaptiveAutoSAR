#ifndef ARA_CRYPTO_CRYPTO_ERROR_DOMAIN_H
#define ARA_CRYPTO_CRYPTO_ERROR_DOMAIN_H

#include "ara/core/error_domain.h"
#include "ara/core/error_code.h"
#include "ara/core/exception.h"

#include <cstdint>

namespace ara
{
    namespace crypto
    {
        /**
         * @brief [SWS_CRYPT_19905]
         * Exception type thrown for CRYPTO errors.
         */
        class CryptoException : public ara::core::Exception
        {
        public:
            
            /**
             * @brief [SWS_CRYPT_19906]
             * Construct a new CryptoException from an ErrorCode.
             * @param[in] err the ErrorCode
             */
            explicit CryptoException (ara::core::ErrorCode err) noexcept : Exception(err)
            {
            }
        }; 

        /**
         * @brief [SWS_CRYPT_19900]
         * Crypto Error Domain class that provides interfaces as defined by ara::core::ErrorDomain such
         * as a name of the Crypto Error Domain or messages for each error code. This class represents
         * an error domain responsible for all errors that may be reported by public APIs in ara::crypto
         * namespace.
         */
        class CryptoErrorDomain final : public ara::core::ErrorDomain
        {
            constexpr static ErrorDomain::IdType kId = 0x8000000000000801;
        public:
            /**
             * @brief [SWS_CRYPT_19903]
             * crypto error
             */
            using Errc = CryptoErrc;

            /**
             * @brief [SWS_CRYPT_19904]
             * Alias for the exception base class.
             */
            using Exception = CryptoException;

            /**
             * @brief [SWS_CRYPT_19902]
             * Ctor of the CryptoErrorDomain.
             */
            constexpr CryptoErrorDomain () noexcept
            : ErrorDomain(kId)
            {

            }

            /**
             * @brief [SWS_CRYPT_19954]
             * throws exception of error code
             * @param[in] errorCode an error code identifier from the CryptoErrc enumeration
             */
            void ThrowAsException (const ara::core::ErrorCode &errorCode) const override
            {
                ara::core::ErrorCode::ThrowAsException<Exception>(errorCode);

            }
                
            /**
             * @brief [SWS_CRYPT_19950]
             * returns Text "Crypto"
             * @return const char* "Crypto" text
             */
            const char* Name () const noexcept override
            {
                return "Crypto";
            }
            
            /**
             * @brief [SWS_CRYPT_19953]
             * Translate an error code value into a text message.
             * @param[in] errorCode an error code identifier from the CryptoErrc enumeration
             * @return const char* message text of error code
             */
            const char* Message (ara::core::ErrorDomain::CodeType errorCode) const noexcept override
            {
                switch((CryptoErrc)errorCode)
                {
                    case CryptoErrc::kResourceFault:
                        return "ResourceException: Generic resource fault!";
                    case CryptoErrc::kBusyResource:
                        return "ResourceException: Specified resource is busy!";
                    case CryptoErrc::kInsufficientResource:
                        return "ResourceException: Insufficient capacity of specified resource!";
                    case CryptoErrc::kUnreservedResource:
                        return "ResourceException: Specified resource was not reserved!";
                    case CryptoErrc::kModifiedResource:
                        return "ResourceException: Specified resource has been modified!";
                    case CryptoErrc::kLogicFault:
                        return "LogicException: Generic logic fault!";
                    case CryptoErrc::kInvalidArgument:
                        return "InvalidArgumentException: An invalid argument value is provided!";
                    case CryptoErrc::kUnknownIdentifier:
                        return "InvalidArgumentException: Unknown identifier is provided!";
                    case CryptoErrc::kInsufficientCapacity:
                        return "InvalidArgumentException: Insufficient capacity of the output buffer!";
                    case CryptoErrc::kInvalidInputSize:
                        return "InvalidArgumentException: Invalid size of an input buffer!";
                    case CryptoErrc::kIncompatibleArguments:
                        return "InvalidArgumentException: Provided values of arguments are incompatible!";
                    case CryptoErrc::kInOutBuffersIntersect:
                        return "InvalidArgumentException: Input and output buffers are intersect!";
                    case CryptoErrc::kBelowBoundary:
                        return "InvalidArgumentException: Provided value is below the lower boundary!";
                    case CryptoErrc::kAboveBoundary:
                        return "InvalidArgumentException: Provided value is above the upper boundary!";
                    case CryptoErrc::kAuthTagNotValid:
                        return "AuthTagNotValidException: Provided authentication-tag cannot be verified!";
                    case CryptoErrc::kUnsupported:
                        return "UnsupportedException: Unsupported request (due to limitations of the implementation)!";
                    case CryptoErrc::kInvalidUsageOrder:
                        return "InvalidUsageOrderException: Invalid usage order of the interface!";
                    case CryptoErrc::kUninitializedContext:
                        return "InvalidUsageOrderException: Context of the interface was not initialized!";
                    case CryptoErrc::kProcessingNotStarted:
                        return "InvalidUsageOrderException: Data processing was not started yet!";
                    case CryptoErrc::kProcessingNotFinished:
                        return "InvalidUsageOrderException: Data processing was not finished yet!";
                    case CryptoErrc::kRuntimeFault:
                        return "RuntimeException: Generic runtime fault!";
                    case CryptoErrc::kUnsupportedFormat:
                        return "RuntimeException: Unsupported serialization format for this object type!";
                    case CryptoErrc::kBruteForceRisk:
                        return "RuntimeException: Operation is prohibitted due to a risk of a brute force attack!";
                    case CryptoErrc::kContentRestrictions:
                        return "RuntimeException: The operation violates content restrictions of the target container!";
                    case CryptoErrc::kBadObjectReference:
                        return "RuntimeException: Incorrect reference between objects!";
                    case CryptoErrc::kContentDuplication:
                        return "RuntimeException: Provided content already exists in the target storage!";
                    case CryptoErrc::kUnexpectedValue:
                        return "UnexpectedValueException: Unexpected value of an argument is provided!";
                    case CryptoErrc::kIncompatibleObject:
                        return "UnexpectedValueException: The provided object is incompatible with requested operation or its configuration!";
                    case CryptoErrc::kIncompleteArgState:
                        return "UnexpectedValueException: Incomplete state of an argument!";
                    case CryptoErrc::kEmptyContainer:
                        return "UnexpectedValueException: Specified container is empty!";
                    case CryptoErrc::kMissingArgument:
                        return "kMissingArgumentException: Expected argument, but none provided!";
                    case CryptoErrc::kBadObjectType:
                        return "BadObjectTypeException: Provided object has unexpected type!";
                    case CryptoErrc::kUsageViolation:
                        return "UsageViolationException: Violation of allowed usage for the object!";
                    case CryptoErrc::kAccessViolation:
                        return "AccessViolationException: Access rights violation!";
                    default:
                        return "Unknown Error";

                }
            }
        };

        /**
         * @brief [SWS_CRYPT_10099]
         * Enumeration of all Crypto Error Code values that may be reported by ara::crypto
         */
        enum class CryptoErrc : ara::core::ErrorDomain::CodeType
        {
            kErrorClass= 0x1000000,         // Reserved (a multiplier of error class IDs)
            kErrorSubClass= 0x10000,        // Reserved (a multiplier of error sub-class IDs)
            kErrorSubSubClass= 0x100,       // Reserved (a multiplier of error sub-sub-class IDs)
            kResourceFault= 1 * kErrorClass,// ResourceException: Generic resource fault!
            kBusyResource= kResourceFault + 1,  // ResourceException: Specified resource is busy!
            kInsufficientResource= kResourceFault + 2,  // ResourceException: Insufficient capacity of specified resource!
            kUnreservedResource= kResourceFault + 3,    // ResourceException: Specified resource was not reserved!
            kModifiedResource= kResourceFault + 4,      // ResourceException: Specified resource has been modified!
            kLogicFault= 2 * kErrorClass,               // LogicException: Generic logic fault!
            kInvalidArgument= kLogicFault + 1 * kErrorSubClass, // InvalidArgumentException: An invalid argument value is provided!
            kUnknownIdentifier= kInvalidArgument + 1,           // InvalidArgumentException: Unknown identifier is provided!
            kInsufficientCapacity= kInvalidArgument + 2,        // InvalidArgumentException: Insufficient capacity of the output buffer!
            kInvalidInputSize= kInvalidArgument + 3,            // InvalidArgumentException: Invalid size of an input buffer!
            kIncompatibleArguments= kInvalidArgument + 4,       // InvalidArgumentException: Provided values of arguments are incompatible!
            kInOutBuffersIntersect= kInvalidArgument + 5,       // InvalidArgumentException: Input and output buffers are intersect!
            kBelowBoundary= kInvalidArgument + 6,               // InvalidArgumentException: Provided value is below the lower boundary!
            kAboveBoundary= kInvalidArgument + 7,               // InvalidArgumentException: Provided value is above the upper boundary!
            kAuthTagNotValid= kInvalidArgument + 8,             // AuthTagNotValidException: Provided authentication-tag cannot be verified!
            kUnsupported= kInvalidArgument + 1 * kErrorSubSubClass, // UnsupportedException: Unsupported request (due to limitations of the implementation)!
            kInvalidUsageOrder= kLogicFault + 2 * kErrorSubClass,   // InvalidUsageOrderException: Invalid usage order of the interface!
            kUninitializedContext= kInvalidUsageOrder + 1,      // InvalidUsageOrderException: Context of the interface was not initialized!
            kProcessingNotStarted= kInvalidUsageOrder + 2,      // InvalidUsageOrderException: Data processing was not started yet!
            kProcessingNotFinished= kInvalidUsageOrder + 3,     // InvalidUsageOrderException: Data processing was not finished yet!
            kRuntimeFault= 3 * kErrorClass,                     // RuntimeException: Generic runtime fault!
            kUnsupportedFormat= kRuntimeFault + 1,              // RuntimeException: Unsupported serialization format for this object type!
            kBruteForceRisk= kRuntimeFault + 2,                 // RuntimeException: Operation is prohibitted due to a risk of a brute force attack!
            kContentRestrictions= kRuntimeFault + 3,            // RuntimeException: The operation violates content restrictions of the target container!
            kBadObjectReference= kRuntimeFault + 4,             // RuntimeException: Incorrect reference between objects!
            kContentDuplication= kRuntimeFault + 6,             // RuntimeException: Provided content already exists in the target storage!
            kUnexpectedValue= kRuntimeFault + 1 * kErrorSubClass,   // UnexpectedValueException: Unexpected value of an argument is provided!
            kIncompatibleObject= kUnexpectedValue + 1,          // UnexpectedValueException: The provided object is incompatible with requested operation or its configuration!
            kIncompleteArgState= kUnexpectedValue + 2,          // UnexpectedValueException: Incomplete state of an argument!
            kEmptyContainer= kUnexpectedValue + 3,              // UnexpectedValueException: Specified container is empty!
            kMissingArgument= kUnexpectedValue + 4,             // kMissingArgumentException: Expected argument, but none provided!
            kBadObjectType= kUnexpectedValue + 1 * kErrorSubSubClass,   // BadObjectTypeException: Provided object has unexpected type!
            kUsageViolation= kRuntimeFault + 2 * kErrorSubClass,    // UsageViolationException: Violation of allowed usage for the object!
            kAccessViolation= kRuntimeFault + 3 * kErrorSubClass    // AccessViolationException: Access rights violation!
        };

        /**
         * @brief [SWS_CRYPT_19951]
         * Makes Error Code instances from the Crypto Error Domain. The returned ErrorCode instance
         * always references to CryptoErrorDomain.
         * @param[in] code an error code identifier from the CryptoErrc enumeration
         * @param[in] data supplementary data for the error description
         * @return constexpr ara::core::ErrorCode an instance of ErrorCode created according the arguments
         */
        constexpr ara::core::ErrorCode MakeErrorCode (CryptoErrorDomain::Errc code, ara::core::ErrorDomain::SupportDataType data) noexcept;
    }
}

#endif //ARA_CRYPTO_CRYPTO_ERROR_DOMAIN_H