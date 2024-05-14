#include "Package.h"
#include "vector"
#include "queue"
#include <iostream>
#include "random"
#include "algorithm"
#include "Windows.h"

void print(std::vector<Package>& vector)
{
	for (int i = 0; i < vector.size() - 1; i++)
		std::cout << vector[i].getNo() << ",";
	std::cout << vector[vector.size() - 1].getNo() << "\n";
}

void read(int& noPackages, std::vector<Package>& source)
{
	int x;
	std::cout << "Insert the number of packages in the source:";
	std::cin >> x;
	noPackages = x;
	for (int i = 0; i < x; i++)
		source.push_back(Package(i, false, false, false));
	std::cout << "Source:\n";
	print(source);
}

void deletePos(std::vector<Package>& window, Package& package)
{
	for (int i = 0; i < window.size(); i++)
		if (window[i].getNo() == package.getNo())window.erase(window.begin() + i);
}

void slide(std::vector<Package>& window, std::vector<Package>& source, const int& windowSize, const int& noPackages, int& i, int& j)
{
	deletePos(window, window[j]);
	++i;
	if (!window.empty() && window[window.size() - 1].getNo() != source[noPackages - 1].getNo() && window.size() < windowSize)
	{
		window.push_back(source[windowSize - 1 + i]);
		window[windowSize - 1].setSent(true);
		std::cout << "Package " << window[windowSize - 1].getNo() << " sent.\n";
	}
	--j;
}

void function(std::vector<Package>& window, std::vector<Package>& source, std::vector<Package>& destination, const int& windowSize, const int& noPackages)
{
	int i = 0;
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> rand1(0, windowSize-1);
	std::uniform_int_distribution<std::mt19937::result_type> rand2(rand1(rng)+windowSize, source.size()-1);
	int rand1no = rand1(rng);
	int rand2no = rand2(rng);

	while (!window.empty())
	{
		// Send all packages in the window
		for (Package& package : window)
		{
			package.setSent(true);
			std::cout << "Package " << package.getNo() << " sent.\n";
		}

		bool unreceivedPresent = false;
		bool unacknowledgedPresent = false;

		// Iterate through the window
		for (int j = 0; j < windowSize; j++)
		{
			if (window[window.size() - 1].getAcknowledged())
				break;
			if (window.size() == 1)
			{
				std::cout << "Package " << window[window.size() - 1].getNo() << " not received.\n";
				unreceivedPresent = true;
				break;
			}

			std::cout << "Window:";
			print(window);

			// If the package is the one not received
			if (window[j].getNo() == rand1no && !window[j].getReceived())
			{
				std::cout << "Package " << window[j].getNo() << " not received. Timeout started.\n";
				unreceivedPresent = true;
			}
			// If the package is received
			else
			{
				if (!window[j].getReceived())
				{
					window[j].setReceived(true);
					std::cout << "Package " << window[j].getNo() << " received.\n";
					destination.push_back(window[j]);
				}

				std::cout << "Destination:";
				print(destination);
				window[j].setAcknowledged(true);
				destination[destination.size() - 1].setAcknowledged(true);
				std::cout << "Package " << window[j].getNo() << " acknowledged.\n";
				if (!unreceivedPresent && !unacknowledgedPresent)
				{
					slide(window, source, windowSize, noPackages, i, j);
				}
			}
		}

		// Resend unreceived package after acknowledging others
		if (unreceivedPresent)
		{
			Sleep(3000);
			std::cout << "Timeout expired.\n";
			Sleep(1000);

			for (int j = 0; j < window.size(); j++)
			{
				if (window[window.size() - 1].getAcknowledged()&&unacknowledgedPresent)
					break;

				std::cout << "Window:";
				print(window);

				// If the package is the one that needs resending
				if (!window[j].getReceived() && unreceivedPresent)
				{
					window[j].setSent(true);
					std::cout << "Resending package " << window[j].getNo() << ".\n";
					window[j].setReceived(true);
					std::cout << "Package " << window[j].getNo() << " received.\n";
					destination.push_back(window[j]);
					std::cout << "Package " << window[j].getNo() << " acknowledged.\n";
					window[j].setAcknowledged(true);
					destination[destination.size() - 1].setAcknowledged(true);
					
					slide(window, source, windowSize, noPackages, i, j);
					unreceivedPresent = false;
				}
				// If it's a package that has just been sent
				else if (!window[j].getReceived() && !unreceivedPresent)
				{
					window[j].setReceived(true);
					std::cout << "Package " << window[j].getNo() << " received.\n";
					destination.push_back(window[j]);
					if (window[j].getNo() == rand2no && !window[j].getAcknowledged())
					{
						std::cout << "Acknowledgement " << window[j].getNo() << " not received. Timeout started.\n";
						unacknowledgedPresent = true;
					}
					else
					{
						std::cout << "Package " << window[j].getNo() << " acknowledged.\n";
						window[j].setAcknowledged(true);
						destination[destination.size() - 1].setAcknowledged(true);
						deletePos(window, window[j]);
						++i;
						if (!window.empty() && window[window.size() - 1].getNo() != source[noPackages - 1].getNo() && window.size() < windowSize && windowSize - 1 + i<windowSize)
						{
							window.push_back(source[windowSize - 1 + i]);
							window[windowSize - 1].setSent(true);
							std::cout << "Package " << window[windowSize - 1].getNo() << " sent.\n";
						}
						--j;
					}
				}
				// If it's a package that has been received and acknowledged already
				else if (window[j].getReceived())
					slide(window, source, windowSize, noPackages, i, j);

				std::cout << "Destination:";
				print(destination);
			}
		}

		// Resend unacknowledged package after acknowledging others
		if (unacknowledgedPresent)
		{
			Sleep(3000);
			std::cout << "Timeout expired.\n";
			Sleep(1000);

			for (int j = 0; j < window.size(); j++)
			{
				std::cout << "Window:";
				print(window);

				// If the package is the one that needs resending
				if (!window[j].getAcknowledged() && unacknowledgedPresent)
				{
					std::cout << "Resending package " << window[j].getNo() << ".\n";
					std::cout << "Package " << window[j].getNo() << " received.\n";
					window[j].setAcknowledged(true);
					destination[destination.size() - 1].setAcknowledged(true);
					std::cout << "Package " << window[j].getNo() << " acknowledged.\n";
					
					slide(window, source, windowSize, noPackages, i, j);
					unacknowledgedPresent = false;
				}
				// If it's a package that has just been sent
				else if (!window[j].getReceived() && !unacknowledgedPresent)
				{
					window[j].setReceived(true);
					std::cout << "Package " << window[j].getNo() << " received.\n";
					destination.push_back(window[j]);
					std::cout << "Package " << window[j].getNo() << " acknowledged.\n";
					window[j].setAcknowledged(true);
					destination[destination.size() - 1].setAcknowledged(true);
					
					slide(window, source, windowSize, noPackages, i, j);
				}
				// If it's a package that has been received and acknowledged already
				else if (window[j].getReceived())
					slide(window, source, windowSize, noPackages, i, j);

				std::cout << "Destination:";
				print(destination);
			}
		}
	}
}


int main()
{
	std::vector<Package> source;
	std::vector<Package> destination;
	int noPackages = 0;
	read(noPackages, source);

	std::vector<Package> window;
	int windowSize = noPackages / 2;
	// Insert the first values into the window
	for (int i = 0; i < windowSize; i++)
	{
		window.push_back(source[i]);
	}

	function(window, source, destination, windowSize, noPackages);
	std::sort(destination.begin(), destination.end());

	std::cout << "Final destination:";
	print(destination);
	return 0;
}