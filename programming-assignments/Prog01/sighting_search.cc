#include <algorithm>
#include <chrono> // NOLINT (build/c++11)
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// TODO: Define your Sighting class here
// The class should store speed, brightness, and calculated signature
// Signature formula: ceil((speed * brightness) / 10)
// Include constructor, destructor, and necessary operators
class Sighting
{
private:
	int speed_;
	int brightness_;

public:
	Sighting() : speed_(0), brightness_(0) {}
	Sighting(int speed, int brightness) : speed_(speed), brightness_(brightness) {}

	int speed() const
	{
		return speed_;
	}

	int brightness() const
	{
		return brightness_;
	}

	int Signature() const
	{
		return ceil((speed_ * brightness_) / 10);
	}

	bool operator<(const Sighting &rhs) const
	{
		int mySig = Signature();
		int otherSig = rhs.Signature();

		if (mySig < otherSig)
			return true;
		if (mySig > otherSig)
			return false;
		return speed_ < rhs.speed_;
	}

	friend ostream &operator<<(ostream &out, const Sighting &rhs)
	{
		out << "(" << rhs.speed() << ", " << rhs.brightness() << ") => " << rhs.Signature();
		return out;
	}
};

bool readSightings(const string &filename, vector<Sighting> *outVec)
{
	if (outVec == nullptr)
		return false;

	outVec->clear();
	ifstream fin(filename.c_str());
	if (!fin.is_open())
		return false;

	int spd = 0, bri = 0;
	while (fin >> spd >> bri)
	{
		outVec->push_back(Sighting(spd, bri));
	}

	fin.close();
	return true;
}

bool readSignatures(const string &filename, vector<int> *outVec)
{
	if (outVec == nullptr)
		return false;

	outVec->clear();
	ifstream fin(filename.c_str());
	if (!fin.is_open())
		return false;

	int sig = 0;
	while (fin >> sig)
	{
		outVec->push_back(sig);
	}

	fin.close();
	return true;
}

// TODO: Implement linear search function
int linearSearch(const std::vector<Sighting> sightings, const std::vector<int> signatures)
{
	int count = 0;

	for (unsigned int i = 0; i < signatures.size(); i++)
	{
		int target = signatures.at(i);
		bool found = false;

		for (unsigned int j = 0; j < sightings.size(); j++)
		{
			if (sightings.at(j).Signature() == target)
			{
				found = true;
				break;
			}
		}

		if (found)
			count++;
	}

	return count;
}

bool binarySearchOne(const vector<Sighting> &sortedSightings, int target)
{
	int left = 0;
	int right = sortedSightings.size();

	while (left < right)
	{
		int mid = left + (right - left) / 2;
		int midSig = sortedSightings.at(mid).Signature();

		if (midSig == target)
			return true;
		else if (midSig < target)
			left = mid + 1;
		else
			right = mid;
	}

	return false;
}

// TODO: Implement binary search function
int binarySearch(const std::vector<Sighting> sorted_sightings, std::vector<int> signatures)
{
	int count = 0;

	for (unsigned int i = 0; i < signatures.size(); i++)
	{
		if (binarySearchOne(sorted_sightings, signatures.at(i)))
			count++;
	}

	return count;
}

int main(int argc, char *argv[])
{
	// TODO: Check command line arguments
	if (argc != 4)
	{
		cerr << "Usage: " << argv[0] << " <sighting_file.dat> <signature_file.dat> <result_file.dat>" << endl;
		return 1;
	}

	string sightingFilename = argv[1];
	string signatureFilename = argv[2];
	string resultFilename = argv[3];

	// TODO: Open and validate input files
	vector<Sighting> sightings;
	vector<int> signatures;

	// TODO: Read sighting data from file
	// Parse each line containing speed and brightness values
	// Create Sighting objects and store in vector
	if (!readSightings(sightingFilename, &sightings))
	{
		cerr << "Error: cannot open file " << sightingFilename << endl;
		return 1;
	}

	// TODO: Read signature data from file
	// Parse each line containing signature values
	// Store in vector of integers
	if (!readSignatures(signatureFilename, &signatures))
	{
		cerr << "Error: cannot open file " << signatureFilename << endl;
		return 1;
	}

	// User prompt for search method
	std::cout
			<< "Choice of search method ([l]inear, [b]inary)?" << std::endl;
	char search_type;
	bool validSelection = false;

	// Input validation loop
	while (!validSelection)
	{
		std::cin >> search_type;
		if (search_type != 'l' && search_type != 'b')
		{
			std::cerr << "Incorrect choice" << std::endl;
		}
		else
		{
			validSelection = true;
		}
	}

	// TODO: Initialize timing variables
	std::chrono::high_resolution_clock::time_point start;
	int count = 0;

	// TODO: Implement search logic based on user choice
	switch (search_type)
	{
	case 'l':
		start = std::chrono::high_resolution_clock::now();
		count = linearSearch(sightings, signatures);
		break;
	case 'b':
		// TODO: Sort sightings vector first
		// TODO: Call binary search function
		start = std::chrono::high_resolution_clock::now();
		sort(sightings.begin(), sightings.end());
		count = binarySearch(sightings, signatures);
		break;
	}

	// TODO: Calculate and display timing
	auto now = chrono::high_resolution_clock::now();
	double elapsed_us = chrono::duration<double, micro>(now - start).count();
	cout << "CPU time: " << elapsed_us << " microseconds" << endl;

	// TODO: Write result to output file
	ofstream fout(resultFilename.c_str());
	if (!fout.is_open())
	{
		cerr << "Error: cannot open file " << resultFilename << endl;
		return 1;
	}

	fout << count << endl;

	// TODO: Close files and clean up
	fout.close();

	return 0;
}
