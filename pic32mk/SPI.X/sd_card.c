
#include "sd_card.h"
#include "integer.h"

BYTE send_cmd (
	BYTE cmd,		/* Command byte */
	DWORD arg		/* Argument */
)
{
	BYTE n, res;
	if (cmd & 0x80) {	/* ACMD<n> is the command sequense of CMD55-CMD<n> */
		cmd &= 0x7F;
		res = send_cmd(CMD55, 0);
		if (res > 1) return res;
	}
    
    /* Select the card and wait for ready except to stop multiple block read */
	if (cmd != CMD12) {
		deselect();
		if (!select()) return 0xFF;
	}

	/* Send command packet */
	xmit_spi(0x40 | cmd);			/* Start + Command index */
	xmit_spi((BYTE)(arg >> 24));	/* Argument[31..24] */
	xmit_spi((BYTE)(arg >> 16));	/* Argument[23..16] */
	xmit_spi((BYTE)(arg >> 8));		/* Argument[15..8] */
	xmit_spi((BYTE)arg);			/* Argument[7..0] */
	n = 0x01;						/* Dummy CRC + Stop */
	if (cmd == CMD0) n = 0x95;		/* Valid CRC for CMD0(0) */
	if (cmd == CMD8) n = 0x87;		/* Valid CRC for CMD8(0x1AA) */
	xmit_spi(n);

	/* Receive command response */
	if (cmd == CMD12) rcvr_spi();	/* Skip a stuff byte when stop reading */
	n = 10;							/* Wait for a valid response in timeout of 10 attempts */
	do
		res = rcvr_spi();
	while ((res & 0x80) && --n);

	return res;			/* Return with the response value */
}



