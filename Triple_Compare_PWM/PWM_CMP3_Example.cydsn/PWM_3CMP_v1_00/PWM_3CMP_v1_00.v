
//`#start header` -- edit after this line, do not edit this line
/* ========================================
 *
 * The following firmware was developed by Cypress Semiconductor
 * This work is licensed under a Creative Commons Attribution 3.0 Unported License.
 * 
 * http://creativecommons.org/licenses/by/3.0/deed.en_US
 * 
 * You are free to:
 * -To Share — to copy, distribute and transmit the work 
 * -To Remix — to adapt the work 
 * -To make commercial use of the work
 *
 * ========================================
 */
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 06/13/2013 at 10:56
// Component: PWM_3CMP_v1_00
module PWM_3CMP_v1_00 (
	output  pwm0,
	output  pwm1,
	output  pwm2,
	input   clock,
	input   reset
);

//`#start body` -- edit after this line, do not edit this line

localparam STATE_0 = 3'h0;
localparam STATE_1 = 3'h1;
localparam STATE_2 = 3'h2;
localparam STATE_3 = 3'h3;
localparam STATE_4 = 3'h4;
localparam STATE_5 = 3'h5;
localparam STATE_6 = 3'h6;
localparam STATE_7 = 3'h7;

/* State controls the Datapath CFGRAM - it is passed to the datapath's cs_addr() below */
reg [2:0] State;

wire z0, pwm2_n;

assign pwm2 = ~pwm2_n;

always @ (posedge clock)
begin
	if(reset == 1'b1)
	begin
		State <= STATE_3;
	end
	else
	begin
		case(State)
		
			STATE_0:	// Decrement A0
			begin
				if(pwm2_n != 1'b1)
				begin
					State <= STATE_1;
				end
				else
				begin
					State <= STATE_2;
				end
			end
			
			STATE_1:	// Decrement A1
			begin
				if(z0 != 1'b1)
				begin
					State <= STATE_0;
				end
				else
				begin
					State <= STATE_3;
				end
			end
			
			STATE_2:	// Dummy 
			begin
				if(z0 != 1'b1)
				begin
					State <= STATE_0;
				end
				else
				begin
					State <= STATE_3;
				end
			end
			
			STATE_3:	// Reload
			begin
				if(z0 != 1'b1)
				begin
					State <= STATE_0;
				end
				else
				begin
					State <= STATE_3;
				end
			end
			
			STATE_4:
			begin
				State <= STATE_0;
			end
			
			STATE_5:
			begin
				State <= STATE_0;
			end
			
			STATE_6:
			begin
				State <= STATE_0;
			end
			
			STATE_7:
			begin
				State <= STATE_0;
			end
			
		endcase
	end
end

cy_psoc3_dp8 #(.a0_init_a(1), .a1_init_a(1), .d0_init_a(1), 
.d1_init_a(1), 
.cy_dpconfig_a(
{
    `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:   Decrement A0*/
    `CS_ALU_OP__DEC, `CS_SRCA_A1, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:   Decrement A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:   Dummy*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___F0, `CS_A1_SRC___F1,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:   Reload*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:      */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:      */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:      */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:      */
    8'hFF, 8'h00,  /*CFG9:      */
    8'hFF, 8'hFF,  /*CFG11-10:      */
    `SC_CMPB_A1_D1, `SC_CMPA_A0_D1, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:    Shift A LS, Shift B = Arith RS*/
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    `SC_SR_SRC_MSB, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:      */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:      */
}
)) datapath(
        /*  input                   */  .reset(reset),
        /*  input                   */  .clk(clock),
        /*  input   [02:00]         */  .cs_addr(State),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(1'b0),
        /*  input                   */  .f1_load(1'b0),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output                  */  .ce0(),
        /*  output                  */  .cl0(pwm0),
        /*  output                  */  .z0(z0),
        /*  output                  */  .ff0(),
        /*  output                  */  .ce1(),
        /*  output                  */  .cl1(pwm1),
        /*  output                  */  .z1(pwm2_n),
        /*  output                  */  .ff1(),
        /*  output                  */  .ov_msb(),
        /*  output                  */  .co_msb(),
        /*  output                  */  .cmsb(),
        /*  output                  */  .so(),
        /*  output                  */  .f0_bus_stat(),
        /*  output                  */  .f0_blk_stat(),
        /*  output                  */  .f1_bus_stat(),
        /*  output                  */  .f1_blk_stat()
);
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line


