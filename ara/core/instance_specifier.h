#ifndef ARA_CORE_INSTANCE_SPECIFIER_H
#define ARA_CORE_INSTANCE_SPECIFIER_H

#include "ara/core/string_view.h"
#include "ara/core/result.h"
namespace ara
{
    namespace core
    {
        /**
         * @brief [SWS_CORE_08001]
         * class representing an AUTOSAR Instance Specifier, which is basically an AUTOSAR
         * shortname-path wrapper.
         */
        class InstanceSpecifier final
        {
        private:
            StringView gMetaModelIdentifier;
        public:
            /**
             * @brief [SWS_CORE_08021]
             * throwing ctor from meta-model string
             * @param[in] metaModelIdentifier stringified meta model identifier (short name path) where path separator is ’/’. Lifetime of underlying string has to exceed the lifetime of the constructed InstanceSpecifier.
             * @exception CoreExecption in case the given metaModelIdentifier is not a valid meta-model identifier/short name path.
             */
            explicit InstanceSpecifier (StringView metaModelIdentifier)
            {
                gMetaModelIdentifier = metaModelIdentifier;
            }
            
            /// @uptrace{SWS_CORE_08022}
            /// @brief Copy constructor.
            /// @param[in] other the other instance
            InstanceSpecifier (const InstanceSpecifier &other)
            {
                gMetaModelIdentifier = other.gMetaModelIdentifier;
            }

             /// @uptrace{SWS_CORE_08023}
            /// @brief Copy constructor.
            /// @param[in] other the other instance
            InstanceSpecifier (const InstanceSpecifier &&other)
            {
                gMetaModelIdentifier = other.gMetaModelIdentifier;
            }

            /// @uptrace{SWS_CORE_08024}
            InstanceSpecifier& operator= (const InstanceSpecifier &other)
            {
                gMetaModelIdentifier.swap(other.gMetaModelIdentifier);
                return *this;
            }

            /// @uptrace{SWS_CORE_08024}
            InstanceSpecifier& operator= (const InstanceSpecifier &&other)
            {
                gMetaModelIdentifier.swap(other.gMetaModelIdentifier);
                return *this;
            }

           ~InstanceSpecifier () noexcept;

           /// @uptrace{SWS_CORE_08032} Create a new instance of this class
           static Result<InstanceSpecifier> Create (StringView metaModelIdentifier);

           /// @uptrace{SWS_CORE_08042} eq operator to compare with other InstanceSpecifier instance.
           bool operator== (const InstanceSpecifier &other) const noexcept
           {
               return gMetaModelIdentifier == other.gMetaModelIdentifier;
           }

           /// @uptrace{SWS_CORE_08043} eq operator to compare with other InstanceSpecifier instance.
           bool operator== (StringView other) const noexcept
           {
               return gMetaModelIdentifier == other;
           }

           /// @uptrace{SWS_CORE_08044} uneq operator to compare with other InstanceSpecifier instance.
           bool operator!= (const InstanceSpecifier &other) const noexcept
           {
               return gMetaModelIdentifier != other.gMetaModelIdentifier;
           }

           /// @uptrace{SWS_CORE_08045} uneq operator to compare with other InstanceSpecifier instance.
           bool operator!= (StringView other) const noexcept
           {
               return gMetaModelIdentifier != other;
           }

           /// @uptrace{SWS_CORE_08046} lower than operator to compare with other InstanceSpecifier for ordering purposes (f.i. when
           /// collecting identifiers in maps).
           bool operator< (const InstanceSpecifier &other) const noexcept
           {
               return gMetaModelIdentifier < other.gMetaModelIdentifier;
           }

           /// @uptrace{SWS_CORE_08041} method to return the stringified form of InstanceSpecifier
           StringView ToString () const noexcept
           {
               return gMetaModelIdentifier;
           }

        };
        
        InstanceSpecifier ::~InstanceSpecifier ()
        {
        }

        /// @uptrace{SWS_CORE_08081} Non-member function operator== to allow StringView on lhs.
        bool operator== (StringView lhs, const InstanceSpecifier &rhs) noexcept
        {
            return lhs == rhs.ToString();
        }

        /**
         * @brief [SWS_CORE_08082]
         * Non-member function operator!= to allow StringView on lhs.
         * @param lhs stringified form of a InstanceSpecifier
         * @param rhs an InstanceSpecifier
         * @return true in case rhs string representation not equals lhs
         * @return false 
         */
        bool operator!= (StringView lhs, const InstanceSpecifier &rhs) noexcept
        {
            return lhs == rhs.ToString();
        }
    }
}

#endif // ARA_CORE_INSTANCE_SPECIFIER_H
