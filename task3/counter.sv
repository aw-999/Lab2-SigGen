module counter #(
  parameter A_WIDTH = 8
)(
  // interface signals
  input  logic             clk,      // clock
  input  logic             rst,      // reset
  output logic [A_WIDTH-1:0] count     // count output
);

always_ff @ (posedge clk)
  if (rst) count <= {A_WIDTH{1'b0}};
  else count <= count + 1;


endmodule
