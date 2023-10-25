#ifndef ASSOCIATIVE_CONTAINER
#define ASSOCIATIVE_CONTAINER
// !ASSOCIATIVA_CONTAINER


template<
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
class associative_container
{

public:

	virtual ~associative_container() = default;

public:

	virtual tvalue find(tkey key) = 0;

	virtual void insert(tkey key, tvalue& value) = 0;

	virtual tvalue remove(tkey key) = 0;

};
#endif