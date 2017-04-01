#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <random>
#include <ctime>
#include <stdexcept>

template< typename _T1, typename _T2 >
class _DeramidNode {
public:

	///////////////////////////////////////////////////////////////////////////////

	_DeramidNode* left;
	_DeramidNode* right;

	_T1 key;
	_T2	priority;

	///////////////////////////////////////////////////////////////////////////////

	_DeramidNode(_T1 key, _T2 priority) :
		key(key), priority(priority), left(NULL), right(NULL)
	{}
	_DeramidNode(_T1 key, _T2 priority, _DeramidNode* left, _DeramidNode* rigth) :
		key(key), priority(priority), left(left), right(right)
	{}
	_DeramidNode(_DeramidNode& other) :
		key(other.key), priority(other.priority), left(other.left), right(other.right)
	{}
	_DeramidNode(_DeramidNode&& other) :
		key(other.key), priority(other.priority), left(other.left), right(other.right)
	{}

	~_DeramidNode() {}

	///////////////////////////////////////////////////////////////////////////////

    static constexpr inline _DeramidNode* Merge(_DeramidNode< _T1, _T2 >* leftSubtree,
								_DeramidNode< _T1, _T2 >* rightSubtree) {
        if (leftSubtree == NULL)
			return rightSubtree;
		if (rightSubtree == NULL)
			return leftSubtree;
		if (leftSubtree->priority > rightSubtree->priority) {
            leftSubtree->right = Merge(leftSubtree->right, rightSubtree);
            return leftSubtree;
		}
		else {
			rightSubtree->left = Merge(leftSubtree, rightSubtree->left);
			return rightSubtree;
		}
    }

    static constexpr inline void Split(_DeramidNode< _T1, _T2 >* tree, _T1 splitKey,
										_DeramidNode< _T1, _T2 >** leftSubtree,
										_DeramidNode< _T1, _T2 >** rightSubtree) {
		if (tree->key <= splitKey) {
			if (tree->right == NULL) {
				*rightSubtree = NULL;
				*leftSubtree = tree;
				return;
			}
			else {
				_DeramidNode< _T1, _T2 >* tmp = NULL;
                Split(tree->right, splitKey, &tmp, rightSubtree);
                *leftSubtree = tree;
                (*leftSubtree)->right = tmp;
                return;
			}
		}
		else {
            if (tree->left == NULL) {
				*leftSubtree = NULL;
				*rightSubtree = tree;
				return;
            }
            else {
				_DeramidNode< _T1, _T2 >* tmp = NULL;
                Split(tree->left, splitKey, leftSubtree, &tmp);
                *rightSubtree = tree;
                (*rightSubtree)->left = tmp;
                return;
			}
		}
	}

	static constexpr inline _DeramidNode* Insert(_DeramidNode< _T1, _T2 >* tree, _T1 key)
	{
		if (tree == NULL)
			return new _DeramidNode< _T1, _T2 >(key, rand());

		_DeramidNode< _T1, _T2 >* l = NULL;
		_DeramidNode< _T1, _T2 >* r = NULL;
		Split(tree, key, &l, &r);
		_DeramidNode< _T1, _T2 >* m = new _DeramidNode< _T1, _T2 >(key, rand());
		return Merge(Merge(l, m), r);
	}

	static constexpr inline _DeramidNode* Remove(_DeramidNode< _T1, _T2 >* tree, _T1 key)
	{
		_DeramidNode< _T1, _T2 >* l = NULL;
		_DeramidNode< _T1, _T2 >* m = NULL;
		_DeramidNode< _T1, _T2 >* r = NULL;
		Split(tree, key - 1, &l, &r);
		Split(r, key, &m, &r);
		delete m;
		return Merge(l, r);
	}

	///////////////////////////////////////////////////////////////////////////////
	static void Destroy(_DeramidNode< _T1, _T2 >* tree)
	{
		if (tree == NULL)
			return;
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}


    void Dump(int depth) {
    	if (this->left != NULL)
			this->left->Dump(depth + 1);
        for (int i = 0; i < depth; i++)
			std::cout << "   |";
		std::cout << this->key << " : " << this->priority << std::endl;
		if (this->right != NULL)
			this->right->Dump(depth + 1);
    }

};



template< typename _T >
class _ImplicitNode {

public:
	///////////////////////////////////////////////////////////////////////////////

	_T cost;
    unsigned long long int priority;
    _ImplicitNode* left;
    _ImplicitNode* right;
	unsigned sz;

    ///////////////////////////////////////////////////////////////////////////////

	_ImplicitNode(_T cost, unsigned long long int priority) :
		cost(cost), priority(priority), left(NULL), right(NULL), sz(1)
	{}
	_ImplicitNode(_T cost, unsigned long long int priority,
						_ImplicitNode* left, _ImplicitNode* right) :
		cost(cost), priority(priority), left(left), right(right), sz(1)
	{}
    _ImplicitNode(_ImplicitNode& other) :
		cost(other.cost), priority(other.priority),
		left(other.left), right(other.right), sz(other.sz)
	{}
	_ImplicitNode(_ImplicitNode&& other) :
		cost(other.cost), priority(other.priority),
		left(other.left), right(other.right), sz(other.sz)
	{}

	///////////////////////////////////////////////////////////////////////////////

	static constexpr inline unsigned getSize(_ImplicitNode< _T >* tree) {
		return tree == NULL ? 0 : tree->sz;
	}

	static constexpr inline unsigned recalc(_ImplicitNode< _T >* tree) {
		tree->sz = getSize(tree->left) + getSize(tree->right) + 1;
		return tree->sz;
	}

	///////////////////////////////////////////////////////////////////////////////

	static constexpr inline _ImplicitNode* Merge(
							_ImplicitNode< _T >* leftSubtree,
							_ImplicitNode< _T >* rightSubtree) {
        if (leftSubtree == NULL)
			return rightSubtree;
		if (rightSubtree == NULL)
			return leftSubtree;
		if (leftSubtree->priority > rightSubtree->priority) {
            leftSubtree->right = Merge(leftSubtree->right, rightSubtree);
            recalc(leftSubtree);
            return leftSubtree;
		}
		else {
			rightSubtree->left = Merge(leftSubtree, rightSubtree->left);
			recalc(rightSubtree);
			return rightSubtree;
		}
    }

    static constexpr inline void Split(_ImplicitNode< _T >* tree, unsigned position,
										_ImplicitNode< _T >** leftSubtree,
										_ImplicitNode< _T >** rightSubtree) {

        int curIndex = getSize(tree->left) + 1;

		if (curIndex <= position) {
			if (tree->right == NULL) {
				*rightSubtree = NULL;
				*leftSubtree = tree;
				return;
			}
			else {
				_ImplicitNode< _T >* tmp = NULL;
                Split(tree->right, position - curIndex, &tmp, rightSubtree);
                *leftSubtree = tree;
                (*leftSubtree)->right = tmp;
                recalc(*leftSubtree);
                return;
			}
		}
		else {
            if (tree->left == NULL) {
				*leftSubtree = NULL;
				*rightSubtree = tree;
				return;
            }
            else {
				_ImplicitNode< _T >* tmp = NULL;
                Split(tree->left, position, leftSubtree, &tmp);
                *rightSubtree = tree;
                (*rightSubtree)->left = tmp;
                recalc(*rightSubtree);
                return;
			}
		}
	}

	static constexpr inline _ImplicitNode* Insert(_ImplicitNode< _T >* tree,
				unsigned pos, _T cost, unsigned long long int priority)
	{
		if (tree == NULL)
			return new _ImplicitNode< _T >(cost, priority);

		_ImplicitNode< _T >* l = NULL;
		_ImplicitNode< _T >* r = NULL;
		Split(tree, pos, &l, &r);
		_ImplicitNode< _T >* m = new _ImplicitNode< _T >(cost, priority);
		return Merge(Merge(l, m), r);
	}

	static constexpr inline _ImplicitNode< _T >* Remove(_ImplicitNode< _T >* tree, unsigned pos)
	{
		_ImplicitNode< _T >* l = NULL;
		_ImplicitNode< _T >* m = NULL;
		_ImplicitNode< _T >* r = NULL;
		Split(tree, pos - 1, &l, &r);
		Split(r, 1, &m, &r);
		delete m;
		return Merge(l, r);
	}

	static constexpr inline _ImplicitNode< _T >* Copy(_ImplicitNode< _T >* tree)
	{
        if (tree == NULL)
			return NULL;

		_ImplicitNode< _T >* result =
			new _ImplicitNode< _T >(tree->cost, tree->priority, Copy(tree->left), Copy(tree->right));
		result->sz = tree->sz;

		return result;
	}

	///////////////////////////////////////////////////////////////////////////////
	static void Destroy(_ImplicitNode< _T >* tree)
	{
		if (tree == NULL)
			return;
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}


    void Dump(int depth) {
    	if (this->left != NULL)
			this->left->Dump(depth + 1);
        for (int i = 0; i < depth; i++)
			std::cout << "   |";
		std::cout << this->sz << " : " << this->cost << " : " << this->priority << std::endl;
		if (this->right != NULL)
			this->right->Dump(depth + 1);
    }
	///////////////////////////////////////////////////////////////////////////////


};



template< typename T >
class AdvancedVector {

private:
	_ImplicitNode< T >* head;
	std::mt19937_64 mt;

public:
	AdvancedVector();
	AdvancedVector(unsigned n);
	AdvancedVector(unsigned n, T&& value);

	~AdvancedVector();
	AdvancedVector(AdvancedVector&);
	AdvancedVector(AdvancedVector&&);
	AdvancedVector(std::vector< T >&);

	unsigned 	size		() const;
	void 		swap		(AdvancedVector< T >& other);

	void 		push_back	(T&& value);
	void		push_back	(const T& value);

	void		push_front	(T&& value);
	void		push_front	(const T& value);

	void		insert		(unsigned index, T&& value);
	void		insert		(unsigned index, const T& value);
	void		insert		(unsigned index, const AdvancedVector< T >& src);

	void		erase		(unsigned index);
	void		erase		(unsigned from, unsigned to);

	void		clear		();

	typename AdvancedVector< T >::iterator			begin	();
	typename AdvancedVector< T >::iterator			end		();
	typename AdvancedVector< T >::reverse_iterator	rbegin	();
	typename AdvancedVector< T >::reverse_iterator	rend	();

	void split(AdvancedVector& right, unsigned index);

	T& 			operator [] (unsigned index);
	void 		operator += (AdvancedVector& other);

	void		operator += (T&& value);
	void		operator += (const T& value);


	class iterator : public std::iterator< std::random_access_iterator_tag, T > {
	private:
		int index;
        AdvancedVector< T >* parent;
	public:
		typedef T value_type;
        iterator (const iterator&);
        iterator (AdvancedVector< T >* parent);
        iterator (AdvancedVector< T >* parent, unsigned index);

        iterator& operator++();
        iterator& operator--();
        int operator -		(iterator& other);
        bool operator == 	(iterator& other);
        bool operator != 	(iterator& other);
		T& operator* ();
	};

	class reverse_iterator : public std::iterator< std::random_access_iterator_tag, T >  {
	private:
		int index;
        AdvancedVector< T >* parent;
	public:
        reverse_iterator (const reverse_iterator&);
        reverse_iterator (AdvancedVector< T >* parent);
        reverse_iterator (AdvancedVector< T >* parent, unsigned index);

        reverse_iterator& operator++();
		reverse_iterator& operator--();
		int operator -		(reverse_iterator& other);
        bool operator == 	(reverse_iterator& other);
        bool operator != 	(reverse_iterator& other);
		T& operator* ();
	};
};

template< typename T >
AdvancedVector< T >::AdvancedVector () : head(NULL) {
	std::random_device rd;
	mt = std::mt19937_64(rd());
}

template< typename T >
AdvancedVector< T >::AdvancedVector (unsigned n) {
	std::random_device rd;
	mt = std::mt19937_64(rd());
	head = NULL;
	for (int i = 0; i < n; i++)
		head = _ImplicitNode< T >::Merge(head, new _ImplicitNode< T >(T(), mt()));
}

template< typename T >
AdvancedVector< T >::AdvancedVector (unsigned n, T&& value) {
	std::random_device rd;
	mt = std::mt19937_64(rd());
	head = NULL;
	for (unsigned i = 0; i < n; i++)
		head = _ImplicitNode< T >::Merge(head, new _ImplicitNode< T >(value, mt()));
}

template< typename T >
AdvancedVector< T >::AdvancedVector (AdvancedVector< T >& other) {
    std::random_device rd;
	mt = std::mt19937_64(rd());
	head = _ImplicitNode< T >::Copy(other.head);
}

template< typename T >
AdvancedVector< T >::AdvancedVector (AdvancedVector< T >&& other) {
    std::random_device rd;
	mt = std::mt19937_64(rd());
	head = _ImplicitNode< T >::Copy(other.head);
}

template< typename T >
AdvancedVector< T >::AdvancedVector (std::vector< T >& src) {
    head = NULL;
    for (auto & iter: src)
		push_back(iter);
}

template< typename T >
AdvancedVector< T >::~AdvancedVector () {
	_ImplicitNode< T >::Destroy(head);
}


template< typename T >
unsigned AdvancedVector< T >::size () const {
	return _ImplicitNode< T >::getSize(head);
}

template< typename T >
void AdvancedVector< T >::swap (AdvancedVector< T >& other) {
    std::swap (head, other.head);
}


template< typename T >
T& AdvancedVector< T >::operator[] (unsigned index) {
    if (index >= size())
		throw std::range_error("index must not be greater than array size");

	index++;

    _ImplicitNode< T >* iter = head;
    while (true) {
		if ( _ImplicitNode< T >::getSize(iter->left) + 1 == index )
			return iter->cost;

		if ( _ImplicitNode< T >::getSize(iter->left) + 1 > index ) {
			iter = iter->left;
		}
		else {
			index -= _ImplicitNode< T >::getSize(iter->left) + 1;
			iter = iter->right;
		}
    }
}

template< typename T >
void AdvancedVector< T >::operator += (AdvancedVector< T >& other) {
    head = _ImplicitNode< T >::Merge(head, _ImplicitNode< T >::Copy(other.head));
}

template< typename T >
void AdvancedVector< T >::operator += (T&& value) {
    insert(size(), value);
}

template< typename T >
void AdvancedVector< T >::operator += (const T& value) {
    insert(size(), value);
}

template< typename T >
void AdvancedVector< T >::push_back (T&& value) {
	head = _ImplicitNode< T >::Merge(head, new _ImplicitNode< T >(value, mt()));
}

template< typename T >
void AdvancedVector< T >::push_back (const T& value) {
	head = _ImplicitNode< T >::Merge(head, new _ImplicitNode< T >(value, mt()));
}

template< typename T >
void AdvancedVector< T >::push_front (T&& value) {
	head = _ImplicitNode< T >::Merge(new _ImplicitNode< T >(value, mt()), head);
}

template< typename T >
void AdvancedVector< T >::push_front (const T& value) {
	head = _ImplicitNode< T >::Merge(new _ImplicitNode< T >(value, mt()), head);
}

template< typename T >
void AdvancedVector< T >::insert (unsigned index, T&& value) {
    if (index > size())
		throw std::range_error("index must not be greater then size");

    _ImplicitNode< T >::Insert(head, index, value, mt());
}

template< typename T >
void AdvancedVector< T >::insert (unsigned index, const T& value) {
    if (index > size())
		throw std::range_error("index must not be greater then size");
	index += 1;

    _ImplicitNode< T >::Insert(head, index, value, mt());
}

template< typename T >
void AdvancedVector< T >::insert (unsigned index, const AdvancedVector< T >& src) {
	if (index > size())
		throw std::range_error("index must not be greater then size");

    _ImplicitNode< T >* left, *right, *mid;
	_ImplicitNode< T >::Split (head, index, &left, &right);
	mid = _ImplicitNode< T >::Copy(src.head);

    head = _ImplicitNode< T >::Merge(left, _ImplicitNode< T >::Merge(mid, right));
}

template< typename T >
void AdvancedVector< T >::erase	(unsigned index) {
	if (index > size())
		throw std::range_error("index must be less then size");

	index += 1;
	_ImplicitNode< T >::Remove(head, index);
}

template< typename T >
void AdvancedVector< T >::erase (unsigned from, unsigned to) {
    if (from >= size())
		throw std::range_error("from must be less then size");
	if (to > size())
		throw std::range_error("to must not be greater then size");
    if (from > to)
		throw std::range_error("from must not be greater then to");

    _ImplicitNode< T > *left, *mid, *right;

    from += 1;
    to += 1;

    _ImplicitNode< T >::Split(head, from - 1, &left, &mid);
	_ImplicitNode< T >::Split(mid, to - from, &mid, &right);
	_ImplicitNode< T >::Destroy(mid);

	head = _ImplicitNode< T >::Merge(left, right);
}


template< typename T >
void AdvancedVector< T >::clear () {
	_ImplicitNode< T >::Destroy(head);
	head = NULL;
}

///////////////////////////////////////////////////////////////////////////////

template< typename T >
typename AdvancedVector< T >::iterator AdvancedVector< T >::begin() {
	return AdvancedVector< T >::iterator(this, 0);
}

template< typename T >
typename AdvancedVector< T >::iterator AdvancedVector< T >::end() {
	return AdvancedVector< T >::iterator(this, size());
}



template< typename T >
AdvancedVector< T >::iterator::iterator (const iterator& other) {
	parent = other.parent;
	index = other.index;
}

template< typename T >
AdvancedVector< T >::iterator::iterator (AdvancedVector< T >* parent_arg) {
	parent = parent_arg;
	index = 0;
}

template< typename T >
AdvancedVector< T >::iterator::iterator (AdvancedVector< T >* parent_arg, unsigned index_arg) {
	parent = parent_arg;
	index = index_arg;
}


template< typename T >
typename AdvancedVector< T >::iterator&  AdvancedVector< T >::iterator::operator++() {
	index++;
}

template< typename T >
typename AdvancedVector< T >::iterator& AdvancedVector< T >::iterator::operator--() {
	index--;
}

template< typename T >
bool AdvancedVector< T >::iterator::operator == (AdvancedVector< T >::iterator& other) {
	return parent == other.parent && index == other.index;
}

template< typename T >
bool AdvancedVector< T >::iterator::operator != (AdvancedVector< T >::iterator& other) {
	return parent != other.parent || index != other.index;
}

template< typename T >
int AdvancedVector< T >::iterator::operator - (AdvancedVector< T >::iterator& other) {
	if (parent != other.parent)
		throw std::logic_error("iterators must have common parent");

	return index - other.index;
}

template< typename T >
T& AdvancedVector< T >::iterator::operator * () {
	return (*parent)[index];
}


//////////////////////////////////////////////////////////////////////////////////////////

template< typename T >
typename AdvancedVector< T >::reverse_iterator AdvancedVector< T >::rbegin() {
	return AdvancedVector< T >::reverse_iterator(this, 0);
}

template< typename T >
typename AdvancedVector< T >::reverse_iterator AdvancedVector< T >::rend() {
	return AdvancedVector< T >::reverse_iterator(this, size());
}



template< typename T >
AdvancedVector< T >::reverse_iterator::reverse_iterator (const reverse_iterator& other) {
	parent = other.parent;
	index = other.index;
}

template< typename T >
AdvancedVector< T >::reverse_iterator::reverse_iterator (AdvancedVector< T >* parent_arg) {
	parent = parent_arg;
	index = (*parent_arg).size() - 1;
}

template< typename T >
AdvancedVector< T >::reverse_iterator::reverse_iterator (AdvancedVector< T >* parent_arg, unsigned index_arg) {
	parent = parent_arg;
	index = index_arg;
}


template< typename T >
typename AdvancedVector< T >::reverse_iterator&  AdvancedVector< T >::reverse_iterator::operator++() {
	index--;
}

template< typename T >
typename AdvancedVector< T >::reverse_iterator& AdvancedVector< T >::reverse_iterator::operator--() {
	index++;
}

template< typename T >
bool AdvancedVector< T >::reverse_iterator::operator == (AdvancedVector< T >::reverse_iterator& other) {
	return parent == other.parent && index == other.index;
}

template< typename T >
bool AdvancedVector< T >::reverse_iterator::operator != (AdvancedVector< T >::reverse_iterator& other) {
	return parent != other.parent || index != other.index;
}

template< typename T >
int AdvancedVector< T >::reverse_iterator::operator - (AdvancedVector< T >::reverse_iterator& other) {
	if (parent != other.parent)
		throw std::logic_error("iterators must have common parent");

	return index - other.index;
}

template< typename T >
T& AdvancedVector< T >::reverse_iterator::operator * () {
	return (*parent)[index];
}


int main(int argc, char** argv, char** env)
{
	srand(time(0));
	std::vector< int > V = {1,2,3,4,5,6,7,8,9,0};
	AdvancedVector< int > A(V);
	//typedef std::iterator_traits< AdvancedVector< int >::iterator >::value_type  tt;

	std::copy(A.begin(), A.end(), std::ostream_iterator< int >(std::cout, " "));
	std::cout << std::endl;
	std::reverse_copy(A.begin(), A.end(), std::ostream_iterator< int >(std::cout, " "));
	std::cout << std::endl;
//*/

	std::cout << std::endl;
	return 0;
}
