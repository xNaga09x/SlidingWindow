#pragma once
class Package
{
public:
	Package();
	Package(const int& no, const bool& sent, const bool& received, const bool& acknowledged);

	int getNo();
	bool getSent();
	bool getReceived();
	bool getAcknowledged();

	void setNo(const int& number);
	void setSent(const bool& boolean);
	void setReceived(const bool& boolean);
	void setAcknowledged(const bool& boolean);

	bool operator<(const Package& p1) const;
private:
	int no;
	bool sent;
	bool received;
	bool acknowledged;
};

