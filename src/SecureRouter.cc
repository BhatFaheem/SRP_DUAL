#include "SecureRouter.h"
#include "SecRoutingUpdate_m.h"
#include <sstream>

using namespace omnetpp;

Define_Module(SecureRouter);

void SecureRouter::initialize()
{
    // Read parameters
    id = par("id");
    malicious = par("malicious");
    sharedKey = par("sharedKey").stdstringValue();

    // Initialize routing table with self-route (distance 0)
    routes[id] = {0.0, id};

    // Schedule first update event in 1s
    sendUpdateEvent = new cMessage("sendUpdate");
    scheduleAt(simTime() + 1.0, sendUpdateEvent);
}

void SecureRouter::handleMessage(cMessage *msg)
{
    // Timer event: send updates
    if (msg == sendUpdateEvent) {
        if (malicious) {
            // Malicious behavior: send a fake (invalid) update
            sendFakeUpdate();
        } else {
            // Normal behavior: send real routing updates
            sendRoutingUpdates();
        }
        // Schedule next update in 5 seconds
        scheduleAt(simTime() + 5.0, sendUpdateEvent);
        return;
    }

    // Handle incoming routing update message
    SecRoutingUpdate *pkt = check_and_cast<SecRoutingUpdate *>(msg);
    int origin = pkt->getOrigin();
    int dest = pkt->getDest();
    double metric = pkt->getMetric();
    std::string receivedHash = pkt->getHash();

    // Compute expected HMAC for this message
    std::string expectedHash = computeHMAC(origin, dest, metric);
    EV << "Router[" << id << "] received update from Router[" << origin << "] for dest "
       << dest << " with metric " << metric << "\n";

    if (receivedHash != expectedHash) {
        // Hash mismatch: malicious or corrupted update
        EV << "Router[" << id << "] detected INVALID hash (malicious) - dropping update\n";
        failCount++;
        delete pkt;
        return;
    }
    // Valid update
    successCount++;
    EV << "Router[" << id << "] hash valid; processing update.\n";
    updateRoute(origin, dest, metric);
    delete pkt;
}

void SecureRouter::sendRoutingUpdates()
{
    // For each neighbor (out gate), send all known routes
    for (int i = 0; i < gateSize("out"); i++) {
        for (auto &entry : routes) {
            int dest = entry.first;
            double cost = entry.second.cost;
            // Create update packet
            SecRoutingUpdate *upd = new SecRoutingUpdate("SecRouteUpd");
            upd->setOrigin(id);
            upd->setDest(dest);
            upd->setMetric(cost);
            // Compute HMAC hash for the packet
            std::string hmac = computeHMAC(id, dest, cost);
            upd->setHash(hmac.c_str());
            send(upd, "out", i);
        }
    }
    EV << "Router[" << id << "] sent routing updates to neighbors.\n";
}

void SecureRouter::sendFakeUpdate()
{
    // Malicious: send a single fake update with invalid hash
    SecRoutingUpdate *fake = new SecRoutingUpdate("MaliciousUpdate");
    fake->setOrigin(id);
    // Choose a random destination (e.g., (id+1) mod N or random)
    int n = getParentModule()->par("numRouters");
    int fakeDest = (id + 1) % n;
    double fakeMetric = simTime().dbl();  // nonsense metric, e.g., current time
    fake->setDest(fakeDest);
    fake->setMetric(fakeMetric);
    // Set an invalid hash (e.g., empty or random string)
    fake->setHash("BAD_HASH");

    // Broadcast fake update to all neighbors
    for (int i = 0; i < gateSize("out"); i++) {
        send(fake->dup(), "out", i);
    }
    delete fake;
    EV << "Router[" << id << "] (malicious) sent a fake update for dest "
       << fakeDest << " with INVALID hash.\n";
}

std::string SecureRouter::computeHMAC(int origin, int dest, double metric)
{
    // Simple simulation of HMAC: hash the concatenation of fields and key
    std::ostringstream ss;
    ss << origin << ":" << dest << ":" << metric << ":" << sharedKey;
    std::string data = ss.str();
    // Use std::hash for demonstration (not cryptographically secure in real life)
    std::size_t h = std::hash<std::string>{}(data);
    return std::to_string(h);
}

void SecureRouter::updateRoute(int origin, int dest, double metric)
{
    // Distance-vector update: new cost via 'origin' = metric + 1 (link cost = 1)
    double newCost = metric + 1.0;
    bool updated = false;

    // If dest is self, ignore (we already have cost 0 to self)
    if (dest == id) return;

    auto it = routes.find(dest);
    if (it == routes.end()) {
        // New destination learned
        routes[dest] = {newCost, origin};
        EV << "Router[" << id << "] added new route: dest=" << dest
           << " via=" << origin << " cost=" << newCost << "\n";
        updated = true;
    } else {
        // Compare with existing route cost
        if (newCost < it->second.cost) {
            it->second = {newCost, origin};
            EV << "Router[" << id << "] updated route: dest=" << dest
               << " via=" << origin << " cost=" << newCost << "\n";
            updated = true;
        }
    }

    if (updated) {
        // Record convergence info
        lastUpdateTime = simTime().dbl();
        // Optionally, trigger immediate updates (already periodic)
    }
}

void SecureRouter::finish()
{
    // Record metrics as scalars
    recordScalar("UpdateSuccess", successCount);
    recordScalar("UpdateFail", failCount);
    recordScalar("ConvergenceTime", lastUpdateTime);

    // Log final routing table
    EV << "\nRouter[" << id << "] Final Routing Table (dest : cost via nextHop):\n";
    for (auto &entry : routes) {
        int dest = entry.first;
        double cost = entry.second.cost;
        int nh = entry.second.nextHop;
        EV << "  " << dest << " : cost=" << cost << " via Router[" << nh << "]\n";
    }
}
