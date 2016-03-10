/*
 * signal.hpp
 *
 *  Created on: 04.10.2013
 *      Author: downtimes
 */

#ifndef SIGNAL_HPP_
#define SIGNAL_HPP_

#include <vector>
#include <string>
#include <iosfwd>
#include <set>
#include <iostream>

enum class ByteOrder {
	MOTOROLA,
	INTEL
};

enum class Sign {
	UNSIGNED,
	SIGNED
};

enum class Multiplexor {
	NONE,
	MULTIPLEXED,
	MULTIPLEXOR
};


/**
 * This class represents a Signal contained in a Message of a DBC-File.
 * One can Query all the necessary information from this class to define
 * a Signal
 */
class Signal {

	typedef std::set<std::string> toList;
	//The name of the Signal in the DBC-File
	std::string name;
	//The Byteorder of the Signal (@see: endianess)
	ByteOrder order;
	//The Startbit inside the Message of this Signal. Allowed values are 0-63
	unsigned short startBit;
	//The Length of the Signal. It can be anything between 1 and 64
	unsigned short length;
	//If the Data contained in the Signal is signed or unsigned Data
	Sign sign;
	//Depending on the information given above one can calculate the minimum of this Signal
	double minimum;
	//Depending on the inforamtion given above one can calculate the maximum of this Signal
	double maximum;
	//The Factor for calculating the physical value: phys = digits * factor + offset
	double factor;
	//The offset for calculating the physical value: phys = digits * factor + offset
	double offset;
	//String containing an associated unit.
	std::string unit;
	//Contains weather the Signal is Multiplexed and if it is, multiplexNum contains multiplex number
	Multiplexor multiplexor;
	//Contains the multiplex Number if the Signal is multiplexed
	unsigned short multiplexNum;
	//Contains to which Control Units in the CAN-Network the Signal shall be sent
	toList to;

public:
	//Overload of operator>> to allow parsing from DBC Streams
	friend std::istream& operator>>(std::istream& in, Signal& sig);

	//Getter for all the Values contained in a Signal
	std::string getName() const { return name; }
	ByteOrder getByteOrder() const { return order; }
	unsigned short getStartbit() const { return startBit; }
	unsigned short getLength() const { return length; }
	Sign getSign() const { return sign; }
	double getMinimum() const { return minimum; }
	double getMaximum() const { return maximum; }
	double getFactor() const { return factor; }
	double getOffset() const { return offset; }
	std::string getUnit() const { return unit; }
	Multiplexor getMultiplexor() const { return multiplexor; }
	unsigned short getMultiplexedNumber() const { return multiplexNum; }
	toList getTo() const { return to; }
	template <typename T> bool getValue( const std::vector<unsigned char> & msg, T & val) const
	{
		if(startBit + length > msg.size()*8)
			return false;
		unsigned int raw = 0;
		if(order == ByteOrder::INTEL)
		{
			for(unsigned short len = length; len > 0; len--)
			{
				unsigned short bit = startBit + len - 1;
				unsigned char byte = msg[bit/8];
				unsigned short shift = bit%8;
				unsigned char mask = 1 << shift;
				raw |= ((byte & mask) >> shift);
				raw <<= 1;				
			}
			raw >>= 1;

			if(sign == Sign::SIGNED)
			{
				std::cerr << "Signed signals not implemented yet!";
			}
		}
		else
		{
			for(unsigned short len = 0; len < length; len++)
			{
				unsigned short bit = (startBit/8)*8 + (7 - startBit%8) + len;
				unsigned char byte = reverse(msg[bit/8]);
				unsigned short shift = bit%8;
				unsigned char mask = 1 << shift;
				raw |= ((byte & mask) >> shift);
				raw <<= 1;
			}
			raw >>= 1;

			if(sign == Sign::SIGNED)
			{
				std::cerr << "Signed signals not implemented yet!";
			}
		}

		std::cout << raw << "\n";

		val = raw * factor + offset;

		return true;
	}

private:
	unsigned char reverse(const unsigned char in) const
	{
		unsigned char b = in;
		b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
		b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
		b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
		return b;
	}
};


#endif /* SIGNAL_HPP_ */
