network SecureNetwork
{
    parameters:
        int numRouters;     // Total number of routers
        int numMalicious;   // Number of malicious routers (IDs 0..numMalicious-1)
        string topology;    // "full", "ring", or "line"
        string sharedKey;   // Shared HMAC key (propagated to all routers)
    
    submodules:
        for i=0..numRouters-1 {
            router[i]: SecureRouter {
                parameters:
                    id = i;
                    malicious = (i < numMalicious);
                    sharedKey = sharedKey;
            }
        }
    
    connections allowunconnected:
        // FULL‐MESH: connect every pair (i,j) with i<j
        if topology=="full" {
            for i=0..numRouters-2, j=i+1..numRouters-1 {
                router[i].out++ --> router[j].in++;
                router[j].out++ --> router[i].in++;
            }
        }
        
        // RING: each i connects to (i+1)%numRouters
        if topology=="ring" {
            for i=0..numRouters-1 {
                router[i].out++ --> router[(i+1) % numRouters].in++;
                router[(i+1) % numRouters].out++ --> router[i].in++;
            }
        }
        
        // LINE: connect 0–1, 1–2, …, (numRouters-2)–(numRouters-1)
        if topology=="line" {
            for i=0..numRouters-2 {
                router[i].out++ --> router[i+1].in++;
                router[i+1].out++ --> router[i].in++;
            }
        }
}