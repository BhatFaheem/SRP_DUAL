#include "DUALRouting.h"

Define_Module(DUALRouting);

void DUALRouting::initialize()
{
    // Set default metric weights (K1=1, K3=1)
    k1 = 1.0;
    k3 = 1.0;

    // Initialize a dummy routing table entry for destination "DestA"
    RoutingEntry entry;
    entry.feasibleDistance = 1000;   // Initial cost metric
    entry.reportedDistance = 1000;
    entry.nextHop = "None";
    routingTable["DestA"] = entry;

    EV << "DUALRouting initialized. Routing table size: "
       << routingTable.size() << "\n";

    // Schedule a self-message to trigger sending a routing update after 1 second.
    scheduleAt(simTime() + 1.0, new cMessage("sendUpdate"));
}

void DUALRouting::handleMessage(cMessage *msg)
{
    // Distinguish between the self-scheduled "sendUpdate" message and update messages.
    if (strcmp(msg->getName(), "sendUpdate") == 0)
    {
        // Send a simulated routing update
        sendRoutingUpdate();
        // Reschedule the next update in 5 seconds.
        scheduleAt(simTime() + 5.0, new cMessage("sendUpdate"));
    }
    else
    {
        // Process any routing update message from a neighbor (simulated).
        processRoutingUpdate(msg);
    }
    delete msg;
}

void DUALRouting::processRoutingUpdate(cMessage *msg)
{
    // Message format: "update:DestA:900" (destination and new reported distance).
    std::string messageStr(msg->getName());
    std::vector<std::string> tokens;
    size_t pos = 0, found;
    while((found = messageStr.find(":" , pos)) != std::string::npos)
    {
        tokens.push_back(messageStr.substr(pos, found - pos));
        pos = found + 1;
    }
    tokens.push_back(messageStr.substr(pos));

    if(tokens.size() >= 3 && tokens[0] == "update")
    {
        std::string dest = tokens[1];
        double newReportedDistance = atof(tokens[2].c_str());

        EV << "Processing update for destination " << dest
           << " with new reported distance: " << newReportedDistance << "\n";

        // Check feasibility condition: RD < current FD
        if(newReportedDistance < routingTable[dest].feasibleDistance)
        {
            EV << "Feasibility condition met for " << dest
               << ". Updating routing entry.\n";
            routingTable[dest].reportedDistance = newReportedDistance;
            // For this simplified version, we set FD equal to RD.
            routingTable[dest].feasibleDistance = newReportedDistance;
            routingTable[dest].nextHop = "NeighborX";
        }
        else
        {
            EV << "Feasibility condition not met for " << dest
               << ". No update performed.\n";
        }
        // After processing, update the routing table (e.g., print current table)
        updateRoutingTable();
    }
}

void DUALRouting::updateRoutingTable()
{
    // Print out the contents of the routing table.
    EV << "----- Current Routing Table -----\n";
    for (auto it = routingTable.begin(); it != routingTable.end(); ++it)
    {
        EV << "Destination: " << it->first
           << ", Feasible Distance (FD): " << it->second.feasibleDistance
           << ", Reported Distance (RD): " << it->second.reportedDistance
           << ", Next Hop: " << it->second.nextHop << "\n";
    }
    EV << "---------------------------------\n";
}

void DUALRouting::sendRoutingUpdate()
{
    // For simulation, create a dummy update message for "DestA" with a new cost.
    // Here, we simulate that a neighbor reports a lower cost (e.g., 900).
    double simulatedUpdate = 900.0;
    char msgName[50];
    sprintf(msgName, "update:DestA:%.0f", simulatedUpdate);
    EV << "Sending simulated routing update: " << msgName << "\n";

    // Create the update message.
    cMessage *updateMsg = new cMessage(msgName);

    // Schedule the update message to be delivered to ourselves immediately.
    scheduleAt(simTime(), updateMsg);
}

