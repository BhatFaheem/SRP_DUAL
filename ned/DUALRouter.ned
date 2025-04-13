package ned;

module DUALRouter {
    parameters:
        @display("i=device/router");
    gates:
        input in;
        output out;
    submodules:
        dualRouting: DUALRouting {
            @display("p=100,100");
        };
    connections:
        // Connect parent gates to submodule gates
        in --> dualRouting.in;        // Parent's 'in' → submodule's 'in'
        dualRouting.out --> out;      // Submodule's 'out' → parent's 'out'
}