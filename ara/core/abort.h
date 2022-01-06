#ifndef ARA_CORE_ABORT_H
#define ARA_CORE_ABORT_H

namespace ara
{
    namespace core
    {
        /**
         * @brief [SWS_CORE_00053]
         * A function declaration with the correct prototype for SetAbortHandler().
         * This declaration exists only for providing a function type that includes "noexcept" and that acts
         * as base type for a type alias, which is defined in SWS_CORE_00050.
         * This compensates for the fact that the C++ standard (up to and including C++14) prohibits that
         * "noexcept" appears in an alias-declaration.
         * There is no implementation of this function.
         */
        void AbortHandlerPrototype () noexcept;

        /// @uptrace{SWS_CORE_00050} The type of a handler for SetAbortHandler().
        using AbortHandler = decltype(&AbortHandlerPrototype);

        /**
         * @brief [SWS_CORE_00051]
         * Set a custom global Abort handler function and return the previously installed one.
         * By setting nullptr, the implementation may restore the default handler instead.
         * This function can be called from multiple threads simultaneously; these calls are performed in
         * an implementation-defined sequence.
         * @param handler a custom Abort handler (or nullptr)
         * @return AbortHandler the previously installed Abort handler (or nullptr if none was installed)
         */
        AbortHandler SetAbortHandler (AbortHandler handler) noexcept;

        /**
         * @brief [SWS_CORE_00052]
         * Abort the current operation.
         * This function will never return to its caller. The stack is not unwound: destructors of variables
         * with automatic storage duration are not called.
         * @param text a custom text to include in the log message being output
         */
        void Abort (const char *text) noexcept;
    }
}


#endif // ARA_CORE_ABORT_H
