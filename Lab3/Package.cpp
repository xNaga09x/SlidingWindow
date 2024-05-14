#include "Package.h"

Package::Package()
{
	no = 0;
	received = false;
	sent = false;
	acknowledged = false;
}

Package::Package(const int& no, const bool& sent, const bool& received, const bool& acknowledged)
	:no(no), sent(sent), received(received), acknowledged(acknowledged)
{
}

int Package::getNo()
{
	return no;
}

bool Package::getSent()
{
	return sent;
}

bool Package::getReceived()
{
	return received;
}

bool Package::getAcknowledged()
{
	return acknowledged;
}

void Package::setNo(const int& number)
{
	no = number;
}

void Package::setSent(const bool& boolean)
{
	sent=boolean;
}

void Package::setReceived(const bool& boolean)
{
	received=boolean;
}

void Package::setAcknowledged(const bool& boolean)
{
	acknowledged=boolean;
}

bool Package::operator<(const Package& p1) const
{
	return this->no<p1.no;
}
