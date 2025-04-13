package ned;

network SecureDualNetwork {
    submodules:
        router1: DUALRouter { @display("p=100,200"); }
        router2: DUALRouter { @display("p=300,200"); }
        router3: DUALRouter { @display("p=500,200"); }
    connections allowunconnected:
        router1.out --> { delay = 10ms; datarate = 10Mbps; } --> router2.in;
        router2.out --> { delay = 10ms; datarate = 10Mbps; } --> router3.in;
        router3.out --> { delay = 10ms; datarate = 10Mbps; } --> router1.in;
}