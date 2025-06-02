simple SecureRouter
{
    parameters:
        int id;             // Router ID (0..numRouters-1)
        bool malicious;     // If true, this router behaves maliciously
        string sharedKey;   // Shared secret key for HMAC
    gates:
        input in[];         // Input gates (one per neighbor)
        output out[];       // Output gates (one per neighbor)
}
