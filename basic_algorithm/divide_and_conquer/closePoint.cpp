struct Point{
	int x;
	int y;
}

float dist(Point p1, Point p2){
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
		(p1.y - p2.y)*(p1.y - p1.y));
}

// bruse force
// O(n^2)
float bruse_closeUtil(Point *p, int size)
{
	float min_distance = std::numeric_limits<float>::max();
	for(int i = 0; i < size; i++)
		for(int j = i+1; j < size; j++){
			if(dist(p[i], p[j]) < min_distance)
				min_distance = dist(p[i], p[j]);
		}
	return min_distance;
}

// divide and conquer

float stripClosest(Point *strip, int size, float d)
{
	// sort p[] with Point.y;
	sort(strip, size, sizeof(Point), compareY);         //O(logN)

	// Pick all points one by one and try the next points till the difference
    // between y coordinates is smaller than d.
    // This is a proven fact that this loop runs at most 6 times
    float min = d;
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);
}

// assume that p[] is sorted with Point.x;
// O(n * logn * logn)
float closeUtil(Point *p, int size){
	
	if(size <= 3)                      // base case.
		bruse_closeUtil(p, size);

	int middle = size/2;               // divide
	Point midP = p[middle];

	int dl, dr;
	dl = closeUtil(p, mid);             // conquer left
	dr = closeUtil(p+mid, size - mid);  // conquer right

	int d = min(dl, dr);
	// combine
	Point stripP[size];
	int k = 0;
	for(int i = 0; i < size; i++)
		if(abs(p[i].x - midP.x) < d)
			stripP[k++] = p[i];

	return min(d, stripClosest(stripP, k, d));
}
