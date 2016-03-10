/*
 * main.cpp
 *
 *  Created on: 04.10.2013
 *      Author: downtimes
 */

#include <iostream>
#include <stdexcept>

#include "header/dbciterator.hpp"

const std::string usage = ""
		"This parser is meant to be used via CLI at the moment\n"
		"	./parser <FILE>\n"
		"	\n"
		"example:\n"
		"	./parser /home/downtimes/kit13.dbc\n";

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << usage << std::endl;
		return 0;
	}

	try {
		DBCIterator dbc(argv[1]);
//		 std::cout << dbc[0].getName() << "\n" << dbc[0].getDlc() << " " << dbc[0].getId() << " " << dbc[0].getFrom() << "\n";
//		 for(auto sig : dbc[0]) {
//		 	std::cout << sig.second.getName() << " " << sig.second.getUnit() << std::endl;
//		 	std::cout << sig.second.getStartbit() << "," << sig.second.getLength() << std::endl;
//		 	std::cout << "(" << sig.second.getFactor() << ", " << sig.second.getOffset() << ")" << std::endl;
//		 	std::cout << "[" << sig.second.getMinimum() << "," << sig.second.getMaximum() << "]" << std::endl;
//		 	if (sig.second.getMultiplexor() == Multiplexor::MULTIPLEXED) {
//		 		std::cout << "#" << sig.second.getMultiplexedNumber() << "#" << std::endl;
//		 	} else if (sig.second.getMultiplexor() == Multiplexor::MULTIPLEXOR) {
//		 		std::cout << "+Multiplexor+" << std::endl;
//		 	}
//		 };
//		 for(auto msg : dbc)
//		 {
//		 	std::cout << msg.second.getName() << "\n";
//		 }

		std::vector<unsigned char> msgdata = {0x3F, 0x9F, 0x46, 0xB0, };

		auto msg = dbc["DAS_steeringControl"];
		auto sig = msg["DAS_steeringAngleRequest"];
		double val;
		sig.getValue<double>(msgdata, val);
		std::cout << val << "\n";

		std::cout << std::endl;

		//
		//	std::cout << messages[30].getName() << std::endl;
		//	for(auto sig : messages[30]) {
		//		std::cout << "Signal: " << sig.getName() << "  ";
		//		std::cout << "To: ";
		//		for (auto to : sig.getTo()) {
		//			std::cout << to << ", ";
		//		}
		//		std::cout << std::endl;
		//	};
	} catch (std::invalid_argument& ex) {
		std::cout << ex.what() << std::endl;
	}

//	return 0;
}
