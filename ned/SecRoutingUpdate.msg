message SecRoutingUpdate
{
    int origin;     // ID of sender router
    int dest;       // Destination router ID being advertised
    double metric;  // Distance (cost) to dest from origin
    string hash;    // HMAC hash string for authentication
}
