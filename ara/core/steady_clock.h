#ifndef APD_ARA_CORE_STEADY_CLOCK_H_
#define APD_ARA_CORE_STEADY_CLOCK_H_
#include <chrono>
#include <cinttypes>

namespace ara
{
    namespace core
    {
        class SteadyClock
        {
        private:
            /* data */
        public:
            SteadyClock(/* args */);
            ~SteadyClock();

            /// @uptrace{SWS_CORE_06412} An arithmetic type representing the number of ticks in the clock’s duration 
            using rep = std::int64_t;

            /// @uptrace{SWS_CORE_06413} A std::ratio type representing the tick period of the clock, in seconds
            using period = std::nano;

            /// @uptrace{SWS_CORE_06411} std::chrono::duration<rep, period>
            using duration = std::chrono::duration<rep, period>;

            /// @uptrace{SWS_CORE_06414} std::chrono::time_point<ara::core::SteadyClock>
            using time_point = std::chrono::time_point<SteadyClock, duration>;

            /// @uptrace{SWS_CORE_06431} steady clock flag, always true
            static constexpr bool is_steady = true;

            /// @uptrace{SWS_CORE_06432} Return a time_point representing the current value of the clock.
            static time_point now () noexcept;
        };
        
        SteadyClock::SteadyClock(/* args */)
        {
        }
        
        SteadyClock::~SteadyClock()
        {
        }

        SteadyClock::time_point SteadyClock::now()
        {
            return std::chrono::steady_clock::now();
        }
        
    }
}

#endif // APD_ARA_CORE_STEADY_CLOCK_H_