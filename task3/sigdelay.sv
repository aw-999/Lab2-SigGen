module sigdelay #(
    parameter ADDRESS_WIDTH = 9,
            DATA_WIDTH = 8
)(
    input logic clk,
    input logic rst,
    input logic rd,
    input logic wr,
    input logic [DATA_WIDTH-1:0] offset,
    input logic [DATA_WIDTH-1:0] mic_signal,
    output logic [DATA_WIDTH-1:0] del_sig
);

    logic [ADDRESS_WIDTH-1:0] address;

counter addrcounter (
    .clk(clk),
    .rst(rst),
    .count(address)
);

ram2ports ram (
    .clk(clk),
    .rd_en(rd),
    .wr_en(wr),
    .wr_addr(address),
    .rd_addr(address + offset),
    .din(mic_signal),
    .dout(del_sig)
);

endmodule
