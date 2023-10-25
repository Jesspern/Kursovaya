#ifndef COMP
#define COMP

class contest_info;

class comparer {

public:

	virtual int comparate(contest_info* first, contest_info* second) = 0;

	virtual ~comparer() = default;

};

#endif // !COMP
