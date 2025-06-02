#ifndef SECUREROUTER_H_
#define SECUREROUTER_H_

#include <omnetpp.h>
#include <string>
#include <unordered_map>

/**
 * SecureRouter implements a DUAL-based distance-vector router with HMAC authentication.
 * It maintains a routing table and exchanges SecRoutingUpdate messages with neighbors.
 */
class SecureRouter : public omnetpp::cSimpleModule
{
  private:
    int id;                             // Router ID
    bool malicious;                     // Malicious behavior flag
    std::string sharedKey;              // Shared secret for HMAC
    omnetpp::cMessage *sendUpdateEvent; // Self-timer for sending updates

    // Routing table: maps destination ID -> (cost, nextHop)
    struct Route { double cost; int nextHop; };
    std::unordered_map<int, Route> routes;

    // Metrics to record
    int successCount = 0;
    int failCount = 0;
    double lastUpdateTime = 0;  // Last time a valid route was updated

  protected:
    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;
    virtual void finish() override;

    void sendRoutingUpdates();
    void sendFakeUpdate();
    std::string computeHMAC(int origin, int dest, double metric);

    void updateRoute(int origin, int dest, double metric);
};

#endif /* SECUREROUTER_H_ */
