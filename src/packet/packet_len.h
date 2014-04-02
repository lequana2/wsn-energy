/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: Packet length of 802.15.4 Zigbee standard
 */

#ifndef PACKET_LEN_H_
#define PACKET_LEN_H_

#define  PHY_HEADER               6   // PHY 802.15.4 header 6 bytes

#define  PACKET_802154          127   // MAC 802.15.4 payload 127 bytes
#define  ACK_HEADER_FOOTER_LEN    5   // MAC 802.15.4 ACK 5 bytes  (header + footer)
#define  MAC_HEADER_FOOTER_LEN   25   // MAC 802.15.4 ACK 25 bytes (address long)

#define  DIO_LEN                 24   // ICMPv6 RPL DODAG INFORMATION OBJECT
#define  DIS_LEN                 10   // ICMPv6 RPL DODAG INFORMATION SOLICITATION

#endif /* PACKET_LEN_H_ */
