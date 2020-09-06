#pragma once

namespace StripeBridge
{
    class StripeBridge
    {
    private:
        static bool _environmentSetupDone;
        static int _totalStripeInstances;

    public:
        /** Prepares the esp32 system for an optimal NeoBus environment.  */
        static void EnvironmentSetup();
        /** Used to generate uniqe loop registrationkeys. */
        static int GetNewStripeInstanceId(); // TODO: Find cleaner solution.
    };
} // namespace StripeBridge