module counter #(
  parameter A_WIDTH = 8
)(
  // interface signals
  input  logic             clk,      // clock
  input  logic             rst,      // reset
  input  logic             en,       // load counter from data
  input  logic [A_WIDTH-1:0] incr,        // value to preload
  output logic [A_WIDTH-1:0] count     // count output
);

always_ff @ (posedge clk)
  if (rst) count <= {A_WIDTH{1'b0}};
  else if (en) count <= count + incr;


endmodule
