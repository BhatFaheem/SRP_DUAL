#ifndef DUAL_ROUTING_H
#define DUAL_ROUTING_H

#include <omnetpp.h>
#include <map>
#include <string>

using namespace omnetpp;

struct RoutingEntry {
    double feasibleDistance;
    double reportedDistance;
    std::string nextHop;
};

class DUALRouting : public cSimpleModule {
  private:
    std::map<std::string, RoutingEntry> routingTable;
    double k1, k3;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void processRoutingUpdate(cMessage *msg);
    virtual void updateRoutingTable();
    virtual void sendRoutingUpdate();
};

#endif // DUAL_ROUTING_H
