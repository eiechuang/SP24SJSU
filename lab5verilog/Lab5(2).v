

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2025 10:58:12 AM
// Design Name: 
// Module Name: counter_decoder
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
 
 
 
module counter_decoder(
    input clk,
    input rst,
    input Stop,
    output reg [2:0] CountOut,
    output reg Out
);
 
// Define states
localparam s0 = 3'b000,
           s1 = 3'b001,
           s2 = 3'b010,
           s3 = 3'b011,
           s4 = 3'b100,
           s5 = 3'b101,
           s6 = 3'b110,
           s7 = 3'b111;
 
reg [2:0] current_state, next_state;
 
// State register (state update)
always @(posedge clk or posedge rst) begin
    if (rst)
        current_state <= s0;
    else
        current_state <= next_state;
end
 
// Next state logic
always @(*) begin
    if (Stop)
        next_state = current_state; // stay in same state
    else begin
        case (current_state)
            s0: next_state = s1;
            s1: next_state = s2;
            s2: next_state = s3;
            s3: next_state = s4;
            s4: next_state = s5;
            s5: next_state = s6;
            s6: next_state = s7;
            s7: next_state = s0;
            default: next_state = s0;
        endcase
    end
end
 
// Output logic
always @(*) begin
    CountOut = current_state;
    if (current_state == s2)
        Out = 1;
    else
        Out = 0;
end
 
endmodule
 




//tb below

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/28/2025 10:47:56 AM
// Design Name: 
// Module Name: tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
 
 
module tb();
 
reg clk; 
reg rst; 
reg Stop; 
wire [2:0] CountOut; 
wire Out; 
 
counter_decoder uut (
.clk (clk), 
.rst(rst), 
.Stop(Stop), 
.CountOut(CountOut),
.Out(Out)
); 
 
initial begin 
clk = 0; 
forever #5 clk = ~clk; 
 
end
 
initial begin 
rst = 1; Stop = 0; 
 
#12; 
rst = 0; 
 
//testing stop = 0's .
#10; Stop = 0; //s 0 -> s1 
#10; Stop = 0; //1 - 2
#10; Stop = 0; //2 - 3
#10; Stop = 0; //3 - 4
#10; Stop = 0; //4 - 5
#10; Stop = 0; //5 - 6
#10; Stop = 0; //6 - 7
#10; Stop = 0; //7 - 0
 
#10; Stop = 1; //s0 hold
#10; Stop = 0; //move to 1
#10; Stop = 0; //move 2
#10; Stop = 1; //hold s2, out should be 1 in this particular instance
 
#50; 
 
$finish; 
end
 
endmodule