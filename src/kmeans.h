#ifndef _KMEANS_H_
#define _KMEANS_H_

#include <vector>
#include <string>
#include <time.h>

class Point
{

private:
	int id_point, id_cluster, total_values;
	std::vector<double> values;
	std::string header, name;

public:

	// constructor
	Point(int id_point, std::vector<double> & values, std::string & name, std::string & header);

	// get ID of the point
	int getID();

	// get cluster of the point
	int getCluster();

	// set a cluster to the point
	void setCluster(int id_cluster);

	// get a value by index
	double getValue(int index);

	// get name of the point
	std::string & getName();

	// get header of the point
	std::string & getHeader();

	// get the total values of the point
	int getTotalValues();
};


class Cluster
{

private:
	int id_cluster;
	std::vector<double> central_values;
	std::vector<Point> points;

public:

	// constructor
	Cluster(int id_cluster, Point & point);

	// add a new point
	void addPoint(Point & point);

	// remove a point
	bool removePoint(int id_point);

	// get a central value by index
	double getCentralValue(int index);

	// set a central value by index
	void setCentralValue(int index, double value);

	// get a point by index
	Point getPoint(int index);

	// get all points
	int getTotalPoints();

	// get ID of the cluster
	int getID();
};


class KMeans
{

private:
	int total_clusters, total_points, total_attributes;
	int max_iterations, iter, total_outliers, knn;
	std::vector<Cluster> clusters;
	std::vector<Point> points;
	std::vector<std::string> sequences;
	std::vector<std::string> headers;
	std::vector<int> outliers_points;
	bool kmeansplusplus, hybrid, elbow, odin;
	std::string method, outliers_content;
	clock_t t_begin, t_end;
	double elapsed_secs, odin_threshold;

private:

	// convert strings to points
	void generatesPoints(std::string & method);

	// return ID of nearest center (uses euclidean distance)
	int getIDNearestCenter(Point & point);

	// generates the results
	void generateResults();

public:

	// constructor
	KMeans(int total_clusters, int total_points, int total_attributes,
		   std::vector<std::string> & sequences, std::vector<std::string> & headers,
		   int max_iterations = 100, std::string method = "LCS",
		   bool kmeansplusplus = true, bool hybrid = false, bool odin = false,
		   double odin_threshold = 0.89, int knn = 3, bool elbow = false);

	// get sequences of a certain cluster
	void getClusterSequences(int index_cluster, std::vector<std::string> & sequences);

	// returns the central value of a certain cluster
	double getCentralValue(int index_cluster, int index_central_value);

	// returns the value of datapoint of a certain cluster
	double getValuePoint(int index_cluster, int index_point, int index_value);

	// returns the amount of datapoints of a certain cluster
	int getSizeCluster(int index_cluster);

	// runs the k-means algorithm
	void run();
};

#endif
