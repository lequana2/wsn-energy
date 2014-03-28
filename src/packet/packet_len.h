/*
 * packet_len.h
 *
 *  Created on: Mar 27, 2014
 *      Author: quan
 *  
 *  Functioning:
 */

#ifndef PACKET_LEN_H_
#define PACKET_LEN_H_

#define  PHY_HEADER               6   // PHY 802.15.4 header 6 bytes

#define  PACKET_802154          127   // MAC 802.15.4 payload 127 bytes
#define  ACK_HEADER_FOOTER_LEN    5   // MAC 802.15.4 ACK 5 bytes  (header + footer)
#define  MAC_HEADER_FOOTER_LEN   25   // MAC 802.15.4 ACK 25 bytes (address long)

#define  DIO_LEN                 24   // ICMPv6 RPL DODAG INFORMATION OBJECT
#define  DIS_LEN                 10   // ICMPv6 RPL DODAG INFORMATION SOLICITATION
#define  DATA                     1   // 1 bytes ????

#endif /* PACKET_LEN_H_ */
